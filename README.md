# Smart-Dustbin

Smart Dustbin is an Arduino based device created during 6 days workshop at Grammar school. It shows the current garbage level inside the dustbin using coloured leds and open it's lid when waved at it from a close distance.

## Image

<div align="center">
   <img src="./images/dustbin.png" width="50%" height="50%" />
</div>

## Components Used

1. Arduino Uno
1. Servo Motor
1. Led *3
1. Ultrasonic sensor HC-SR04 *2
1. Lipo Battery
1. Bread Board

## Working

Two ultrasonic sensors are used for hand wave and garbage level detection. Data from the garbage level sensors are used to light the 3 leds. If the dustbin is empty leds will be off, one will glow when the garbage level is 30%, 2 for 60% and 3 if the bin is full. If the wave detector sensor detects something in its range then the lid will open with the help of servo motor. After few seconds the lid will close automatically. The state information can be seen in serial monitor.

## Watch The Video

<div align="center">
  <a href="https://youtu.be/d7i2lilJugs"><img src="https://img.youtube.com/vi/d7i2lilJugs/0.jpg"></a>
</div>