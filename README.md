# Arduino electromagnetic counter eraser

After disassembling this electromechanical counter and breaking it, I decided to apply a simple blink with arduino and advance the counter until it reaches all zeros.
The counter can advance at a maximum speed of 18 steps per second therefore starting from 1 to get to 000000 it will take almost 16 hours! Not very efficient solution!

Aniway...
set the initial value of the electromagnetic counter in order to save the value in the arduino EPROM then comment out the aforementioned line and upload the sketch again.
To start the counter use a button, when the button is pressed again the counter stops and the current value is written to the EPROM.
For the connections, follow the wiring diagram.

You can see a short video on my youtube channel https://www.youtube.com/watch?v=MPNWV18nY3Y&ab_channel=Matteo

Have fun!

Matteo

![electromagnetic_counter](https://github.com/matt199394/electromagnetic_counter_eraser/assets/65487240/b6e6ac69-8cba-4a01-b71d-4fd298d3c073)
