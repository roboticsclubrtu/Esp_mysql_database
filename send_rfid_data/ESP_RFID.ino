#include <ESP8266WiFi.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN D4
#define RST_PIN D2

const char* ssid = "dude";
const char* password = "dude@901";
const char* host = "192.168.43.82";

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int readsuccess;  
byte readcard[4];
char str[32] = "";
String StrUID, charge, penalty, names, amount_charged;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
SPI.begin();
mfrc522.PCD_Init();
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
}

void loop() {
    // put your main code here, to run repeatedly:
  readsuccess = getid();
  if(readsuccess) {
  //  Serial.println(StrUID);
    if(StrUID=="3333C31A"){
        Serial.println("Vehicle no: RJ14-LC-1996");
  //      show_charges();
        names = "Aditya";
        send_data();
    }
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

  String url = "http://192.168.43.82/testcode/send_data.php?name="+names;
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
int getid() {  
  if(!mfrc522.PICC_IsNewCardPresent()) {
    return 0;
  }
  if(!mfrc522.PICC_ReadCardSerial()) {
    return 0;
  }
 
  for(int i=0;i<4;i++){
    readcard[i]=mfrc522.uid.uidByte[i]; //storing the UID of the tag in readcard
    array_to_string(readcard, 4, str);
    StrUID = str;
  }
  mfrc522.PICC_HaltA();
  return 1;
}
void array_to_string(byte array[], unsigned int len, char buffer[]) {
    for (unsigned int i = 0; i < len; i++)
    {
        byte nib1 = (array[i] >> 4) & 0x0F;
        byte nib2 = (array[i] >> 0) & 0x0F;
        buffer[i*2+0] = nib1  < 0xA ? '0' + nib1  : 'A' + nib1  - 0xA;
        buffer[i*2+1] = nib2  < 0xA ? '0' + nib2  : 'A' + nib2  - 0xA;
    }
    buffer[len*2] = '\0';
}
