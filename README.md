# home-automation-using-esp8266

Using this complete setup, we will be able to control home lights, electric fan and some other home appliances through a web brwoser using our PC or mobile. 
These AC mains appliances will be connected to relays which are controlled by the Arduino. ESP8266 and Arduino together acts as a Web Server and we will send control commands through a Web Browser like Google Chrome or Mozilla Firefox.

Components Required: 
1. Arduino UNO Board
2. ESP8266 WiFi module
3. Relay modules
4. connecting wires
5. AC power switch
6. 9v battery

ESP-01 is the one of the most popular ESP8266 module available in the market. ESP8266 is a self contained SoC with integrated TCP/IP stack which helps any microcontroller having UART to access a wifi network. It can act as both WiFi access point as well as a WiFi client. It is pre-programmed with AT commands, so we can easily access and configure it using a microcontroller.

ESP8266 runs on 3.3V and its input pins are not 5V tolerant. So we need to reduce the 5V output of the Arduino Tx pin to 3.3V by using voltage dividing resistors to connect to Rx pin of ESP8266 module. Arduino TTL input pins will detect 3.3V as logic high, so we can directly connect 3.3V output of ESP8266 Tx to Arduino Rx pin.

Steps To Connect the circuit:

1. connect ESP8266 with the Arduino Uno. The ESP8266 runs on 3.3V, it may damage if you connect it directly to 5V from Arduino.
2. Connect the VCC and CH_PD of the ESP8266 to the 3.3V output pin of Arduino. CH_PD is Chip Power Down pin, which is active low. So we will give 3.3V to it, which will enable the chip.
3. Then connect the TXD pin of the ESP8266 with the digital pin 2 of the Arduino. Then make a voltage divider to make 3.3V for the RXD of the ESP8266 which is connected to the pin 3 of Arduino. Here we are using software UART through digital pins 2 & 3 of Arduino. Lastly, connect the ground of the ESP8266 with the ground of the Arduino.
4. Now we can connect relays to Arduino. Connect three relays to pins 11, 12 and 13 of the Arduino
5. connect 5V and ground from the Arduino to power the relay. Note that here I am using relay modules which having built in transistor driver. So don’t forget to add driver when you are using bare relays.
6. Upload the code in control.ino file into the arduino board.
7. After uploading the code to the Arduino, open the serial monitor from the Arduino IDE. It will show you the IP address. Copy that IP address and paste it in the html file.
8.  First connect your system to the access point created by ESP8266 module (ESP_xxxxxx). Update the IP address in the webpage.html file created above. Now open the file using your web browser (Google Chrome or Mozilla Firefox). Now you can control your home appliances very easily.
