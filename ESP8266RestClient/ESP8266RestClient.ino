#include <RestClient.h>

#include <WebSocketServer.h>
#include <MD5.h>
#include <Base64.h>
#include <WebSocketClient.h>
#include <global.h>
#include <sha1.h>

#include <ESP8266WiFi.h>

#include <DHT.h>

/* Private header file that holds my wifi ssid and password. 
 * Create this file in your libraries directory like so: 
 *  Arduion/librarires/private/private.h:
 *    #define WIFISSID "<your wifi ssid>"
 *    #define WIFIPASSWD "<your wifi password>"
 */ 
#include <private.h>

#define DHTPIN 5     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino


int chk;
float hum;
float temp; //Stores temperature value 
const char* ssid = WIFISSID;
const char* password = WIFIPASSWD;

void setup() {
  Serial.begin(115200);
  dht.begin();

  delay(10);
 
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected\n");
  Serial.println("local IP: ");
  Serial.print(WiFi.localIP());
}
 
void loop() {
  Serial.println("hit any key to continue");
  int garbage = Serial.read();
  RestClient client = RestClient("192.168.1.98", 5000);


  // Read from the DHT22
  /*
  hum = dht.readHumidity();
  temp= dht.readTemperature(1);
  */
  hum = 22.2;
  temp = 33.3;
  
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print(" %, Temp: ");
  Serial.print(temp);
  Serial.println(" F");

  String humidity = "humidity=";
  humidity = humidity + hum;
  String temperature = "temperature=";
  temperature = temperature + temp;

  String req = temperature + "&" + humidity;
  const char *request = req.c_str();
  
  // make post request to client
  String response = "";
  int statusCode = client.post("/add", request, &response);
  Serial.println(statusCode);
  Serial.println(response);
}
 
