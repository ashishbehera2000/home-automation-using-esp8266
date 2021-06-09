#include <SoftwareSerial.h>  
#define DEBUG true
SoftwareSerial esp8266(2,3);
String sendData(String command, const int timeout, boolean debug) // Function to send the data to the esp8266
{
  String response = ""; 
  esp8266.print(command);           // Send the command to the ESP8266
  long int time = millis();
  while( (time+timeout) > millis()) // wait time for the data to receive
  {
    while(esp8266.available())      // Checking whether ESP8266 has received the data or not
    {
      char c = esp8266.read();      // Read the next character.
      response+=c;                  // Storing the response from the ESP8266
    }
  }
  if(debug)
  { 
    Serial.print(response);         // Printing the response of the ESP8266 on the serial monitor.
  }
  return response;
} 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);   
  esp8266.begin(9600);  
  pinMode(11,OUTPUT);   
  digitalWrite(11,LOW); 
  pinMode(12,OUTPUT);   
  digitalWrite(12,LOW); 
  pinMode(13,OUTPUT);   
  digitalWrite(13,LOW); 
  pinMode(10,OUTPUT);
  digitalWrite(10,LOW);
  sendData("AT+RST\r\n",2000,DEBUG);//reset cmd -> default
  sendData("AT+CWMODE=2\r\n",1000,DEBUG);// mode -> access point
  sendData("AT+CIFSR\r\n",1000,DEBUG);// command for displaying ip address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG);// configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // This will set the server on port 80
}
//http://192.168.4.1:80/"+pinNo
void loop() {
 
  if(esp8266.available()) 
  { 
    if(esp8266.find((char*)"+IPD,"))
    { 
      delay(1000);       
      int connectionId = esp8266.read()-48;   //ascii value - 48 = number
      esp8266.find((char*)"pin=");                   // Advancing the cursor to the "pin="
      int pinNumber = (esp8266.read()-48)*10; // Getting the first number which is pin 13
      pinNumber += (esp8266.read()-48);       // This will get the second number. For example, if the pin number is 13 then the 2nd number will be 3 and then add it to the first number
      digitalWrite(pinNumber, !digitalRead(pinNumber)); // This will toggle the pin
      // The following commands will close the connection 
      String closeCommand = "AT+CIPCLOSE="; 
      closeCommand+=connectionId; 
      closeCommand+="\r\n";
      sendData(closeCommand,1000,DEBUG);     // Sending the data to the ESP8266 to close the command
    } 
  } 
}
