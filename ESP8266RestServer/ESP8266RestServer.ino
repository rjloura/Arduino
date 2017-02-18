#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <DHT.h>
#include <RestClient.h>

/* Private header file that holds your wifi ssid and password. 
 * Create this file in your libraries directory like so: 
 *  Arduion/librarires/private/private.h:
 *    #define WIFISSID "<your wifi ssid>"
 *    #define WIFIPASSWD "<your wifi password>"
 */ 
#include <private.h>

#define DHTPIN 5     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

float hum;
float temp; //Stores temperature value 
const char* ssid = WIFISSID;
const char* password = WIFIPASSWD;
const char* SERVER_IP = "192.168.1.98";

ESP8266WebServer server;

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
  String myip = WiFi.localIP().toString();
  Serial.println("");
  Serial.println("WiFi connected\n");
  Serial.println("local IP: ");
  Serial.print(myip);

  Serial.println("");
  Serial.println("registering with server at: ");
  Serial.println(SERVER_IP);

  String req = "url=http://" + myip + "/read";
  const char *request = req.c_str();
  
  RestClient client = RestClient(SERVER_IP, 5000);

  String response = "";
  int statusCode = client.post("/register", request, &response);
  Serial.println(statusCode);
  Serial.println(response);

  server.on("/read", readSensor);
  server.begin();
}

void readSensor() {
  Serial.println("reading data....");
  hum = dht.readHumidity();
  temp= dht.readTemperature(1);
  
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print(" %, Temp: ");
  Serial.print(temp);
  Serial.println("°F");

  /*
   * Enclose property names in double quotes, because JSON.
   */
  String humidity = "\"humidity\": ";
  humidity = humidity + hum;
  String temperature = "\"temperature\": ";
  temperature = temperature + temp;
  
  String resp = "{" + temperature + ", " + humidity + "}";

  Serial.println(resp);
  Serial.println("Sending data");
  server.send(200, "application/json", resp);
}

void loop() {
  server.handleClient();
}
 
