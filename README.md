# What is Sound Monitoring?
The Sound Monitoring project is a IoT device that integrates hardware and software in order to map places that 
usually make noise above the adequate level. The hardware was assembled on a regular breadboard and used the following components:

* Arduino UNO;
* SparkFun Sound Detector;
* ESP8266-1;
* LEDs, resistors and wires.

The hardware assembled on the breadboard uses the SparkFun Sound Detector captures the analog value representing the sound in the room and the Arduino reads it and calculates an equivalent in decibel. 

In addition to showing this data on the LCD and turning the LEDs on and off depending on the sound level (green for quiet, yellow for moderate and red for loud), the ESP8266 is used to connect the device to the local network and send it to a web server, where the iOS app reads it and shows it to the user from anywhere.

<p><br/>
<img src="./static/img/slm.png" width="512" height="401" class="img-responsive center-block" />
<br/>

#The iOS app: Recife Sound Monitoring
To test the system and demo the idea, I created some pins on Recife's map, simulating places that would have the hardware installed. As it constatly updates a web server with the value in decibels, the user that has the iOS on the phone could simply choose a location and see the noise level that it's emitting. Moreover, the location could be notified by a call or email.


