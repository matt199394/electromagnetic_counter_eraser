// my trivial solution to erase (000000 --> six zero on the counter) an electromagnetic counter
// have fun!
// Matteo


#include <EEPROM.h>
#include "HD44780_LCD_PCF8574.h"  //by Gavin Lyons

HD44780LCD lcd(2, 16, 0x27, &Wire);


int stato = LOW;
bool stato2 = false;

unsigned long c, counter;

char buf[16];


//write word to EEPROM
 void EEPROM_writeint(int address, int value) 
{
 EEPROM.write(address,highByte(value));
 EEPROM.write(address+1 ,lowByte(value));
}
 
 //write long integer into EEPROM
 void EEPROM_writelong(int address, unsigned long value) 
{
 //truncate upper part and write lower part into EEPROM
 EEPROM_writeint(address+2, word(value));
 //shift upper part down
 value = value >> 16;
 //truncate and write
 EEPROM_writeint(address, word(value));
}

// read double word from EEPROM, give starting address
 unsigned long EEPROM_readlong(int address)
 {
 //use word read function for reading upper part
 unsigned long dword = EEPROM_readint(address);
 //shift read word up
 dword = dword << 16;
 // read lower word from EEPROM and OR it into double word
 dword = dword | EEPROM_readint(address+2);
 return dword;
}

unsigned int EEPROM_readint(int address) 
{
 unsigned int word = word(EEPROM.read(address), EEPROM.read(address+1));
 return word;
}


void setup() {
  lcd.PCF8574_LCDInit(lcd.LCDCursorTypeOff);
  lcd.PCF8574_LCDClearScreen();
  lcd.PCF8574_LCDBackLightSet(true);
  lcd.PCF8574_LCDGOTO(1, 0);  //LCDLineNumberOne
  pinMode(13, OUTPUT);
  pinMode(A0, INPUT);

  //EEPROM_writelong(0x00, 882074); //put the current counter value , flash, comment and flash again
  c = counter = EEPROM_readlong(0x00); 
  
  lcd.PCF8574_LCDGOTO(1, 0);
  sprintf(buf, "%06lu", counter);
  lcd.PCF8574_LCDSendString(buf);

}

void loop() {
  if(digitalRead(A0)){
  delay(100);  
  stato2 = true; 
   
  lcd.PCF8574_LCDGOTO(1, 0);
  sprintf(buf, "%06lu", counter);
  lcd.PCF8574_LCDSendString(buf);
  
  stato = !stato;
  digitalWrite(13, stato);

  if (counter == 1000000) {
    EEPROM_writelong(0x00, counter);
    while(1);
  }
  
  c++;
  if ( c%2 )counter++ ;
   
  }

else{
  if (stato2)
  EEPROM_writelong(0x00, counter); 
}
}
