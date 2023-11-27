# Miniterminal
Send and receive serial messages without computer using PC keyboard, LCD and Teensy controller

![Picture](/miniterminal.jpeg)

This is something I wanted to have for a long time: being able to send and receive short messages (for example Gcode to my CNC) without having to boot a computer.
It uses a normal old PC keyboard connected to a Teensy that displays the outgoing and incoming messages on an LCD.
I use a slightly modified version of Paul Stoffregen's library, integrated as .cpp and .h file to my Arduino code.


<Enter> -> send message
<ESC>   -> clear display
<F1> to <F10> -> select baudrate between 115200 and 300

