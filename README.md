# What is RecNoise?
The **RecNoise** project is a IoT device that integrates hardware and software in order to map places that 
usually make noise above the adequate level. The hardware is assembled on a regular breadboard using the following components:

* Arduino UNO;
* SparkFun Sound Detector;
* ESP8266-1;
* LEDs, resistors and wires.

The hardware uses the SparkFun Sound Detector to capture the analog value representing the sound in the room while the Arduino reads it and calculates an equivalent in decibel. 

In addition to showing this data on the LCD and turning the LEDs on and off depending on the sound level (green for quiet, yellow for moderate and red for loud), the ESP8266 is used to connect the device to the local network and send it to a web server, where the iOS app reads it and shows it to the user from anywhere.

#The RecNoise iOS app
To test the system and demo the idea, I created some pins on Recife's map, simulating places that would have the hardware installed. 

As it constatly updates a web server with the value in decibels, the user that has the iOS on the phone could simply choose a location and see the noise level that it's emitting. Moreover, the location could be notified by a call or email.

#The ThingSpeak Web Server

In order to update the values on the iOS App, the hardware sends the last decibel value to a ThingSpeak channel after collecting it for 1 minute. The HTTP request returns a JSON object that is deserialized and printed on the screen for the user.

```
	{"channel":{"id":,"name":"","latitude":"","longitude":"","field1":"Decibeis","created_at":"2015-08-28T06:07:18Z","updated_at":"2016-01-11T14:48:31Z","last_entry_id":506},"feeds":[50.33]}
```
