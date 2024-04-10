String ssid     = "relame";  // SSID to connect to
String password = "123456789"; // Our virtual wifi has no password (so dont do your banking stuff on this network)
String host     = "api.thingspeak.com"; // Open Weather Map API
const int httpPort   = 80;
String uri     = "/update?api_key=GN0SJ0JE16TML8FQ&field1=";


int setupESP8266(void) {
  // Start our ESP8266 Serial Communication
  Serial.begin(115200);   // Serial connection over USB to computer
  Serial.println("AT");   // Serial connection on Tx / Rx port to ESP8266
  delay(10);        // Wait a little for the ESP to respond
  if (!Serial.find("OK")) return 1;
    
  // Connect to 123D Circuits Simulator Wifi
  Serial.println("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"");
  delay(100);        // Wait a little for the ESP to respond
  if (!Serial.find("OK")) return 2;
  
  // Open TCP connection to the host:
  Serial.println("AT+CIPSTART=\"TCP\",\"" + host + "\"," + httpPort);
  delay(500);        // Wait a little for the ESP to respond
  if (!Serial.find("OK")) return 3;
  
  return 0;
}
void send(float val, String seq) {
  String httpPacket = "GET " + seq + String(val) + " HTTP/1.1\r\nHost: " + host + "\r\n\r\n";
  int length = httpPacket.length();
  
  // Send our message length
  Serial.print("AT+CIPSEND=");
  Serial.println(length);
  delay(100); // Wait a little for the ESP to respond if (!Serial.find(">")) 

  // Send our http request
  Serial.print(httpPacket);
  delay(100); // Wait a little for the ESP to respond
  if (!Serial.find("SEND OK\r\n")) return;
}
void anydata(void) {
  
  int temp = map(analogRead(33),20,358,-40,125);
  temp = random(0,50);
  send(temp,"/update?api_key=GN0SJ0JE16TML8FQ&field1=");
  int Turbidity = map(analogRead(34),20,358,0,1000);
  temp = random(0,3000);
  send(Turbidity,"/update?api_key=GN0SJ0JE16TML8FQ&field2=");
  int PH = map(analogRead(35),20,358,0,10);
  temp = random(0,10);
  send(PH,"/update?api_key=GN0SJ0JE16TML8FQ&field3=");
  int TDS = map(analogRead(36),20,358,0,500);
  temp = random(0,1000);
  send(TDS,"/update?api_key=GN0SJ0JE16TML8FQ&field4=");
  
  
  
}


void setup() {
  
  setupESP8266();
               
}

void loop() {
  
 anydata();
 delay(1000);
}