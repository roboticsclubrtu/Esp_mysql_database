#include <ESP8266WiFi.h>
#include <Keypad.h>

const char* ssid = "dude";
const char* password = "dude@901";
const char* host = "192.168.43.82";

char key;
String stored; 
String names="", penalty,charge, amount_charged= "";
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
// connections: keypad from left to right -> Esp8366 from D7 to D0 correspondingly
byte rowPins[ROWS] = {D7, D6, D5, D4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {D3, D2, D1, D0}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  show_charges();
}
  
void loop(){
key = keypad.getKey();
  if (key){
    if (key=='1'){
      charge = "hey";
      penalty = "1000";
  }
  stored = (String)key;
  send_data();
}
}
void send_data(){
  Serial.print("connecting to ");
  Serial.println(host);
  
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
  return;
  }

  String url = "http://192.168.43.82/testcode/insertkey.php?abc="+stored;
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
  "Host: " + host + "\r\n" +
  "Connection: close\r\n\r\n");
  delay(500);
  
  while(client.available()){
  String line = client.readStringUntil('\r');
  Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
  delay(1000);
}

void show_charges(){
  Serial.println();
  Serial.println("Select Charge: ");
  Serial.println("1: Not wearing Helmet      2: Lack of Documents            3: Rash Driving           A: Breaking Signal");
  Serial.println("4: Not having Insurance    5: Overspeeding                 6: Drunk and Drive        B: Hit and Run");
  Serial.println("7: Not wearing Seatbelt    8: Unauthorised Parking         9: Obstructing traffic    C: Wrong side driving");
}
