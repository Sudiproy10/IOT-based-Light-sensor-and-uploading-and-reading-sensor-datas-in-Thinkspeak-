#include <SoftwareSerial_Class.h> // Software Serial Header File
SoftwareSerial ESP8266(2, 3);
#include <WiFi.h>
// replace with your channel's thingspeak API key, 
String apiKey = "V51XNKS5AJLI5E2L";
char ssid[] = "TP-LINK_97A58E";
char password[] = "inteldtl";
int status=WL_IDLE_STATUS;
char server[] = "api.thingspeak.com";

 WiFiClient client;

int analogPin=A0;   
int t=0;
void setup() {                
  Serial.begin(115200);
  delay(1000);
  
  WiFi.begin(ssid, password);
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
   
  WiFi.begin(ssid, password);
   
  while (status!= WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
}
 
 
void loop() {
  if (isnan(t)) {
    Serial.println("Failed to read from Light sensor!");
    return;
  }
  t=analogRead(analogPin);
  
  if (client.connect(server,80)) {  //   "184.106.153.149" or api.thingspeak.com
    String postStr = apiKey;
           postStr +="&field1=";
           postStr += String(t);
 
     client.print("POST /update HTTP/1.1\n"); 
     client.print("Host: api.thingspeak.com\n"); 
     client.print("Connection: close\n"); 
     client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n"); 
     client.print("Content-Type: application/x-www-form-urlencoded\n"); 
     client.print("Content-Length: "); 
     client.print(postStr.length()); 
     client.print("\n\n"); 
     client.print(postStr);
           
 
     Serial.print("Light Intensity: ");
     Serial.print(t);
     Serial.println("% send to Thingspeak");    
  }
  client.stop();
   
  Serial.println("Waiting...");    
  // thingspeak needs minimum 15 sec delay between updates
  delay(20);  
}

