
// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h"

#define DHTPIN D3    // Digital pin connected to the DHT sensor
// Feather ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);


//ESP8266

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>


/* Set these to your desired credentials. */
const char *ssid = "wifi_name";  //ENTER YOUR WIFI SETTINGS
const char *password = "wifi_password";  

//Web/Server address to read/write from 
const char *host = "ip_address";   //website or IP address of server

//=======================================================================
//                    Power on setup
//=======================================================================

void setup() {
  Serial.begin(115200);

//temperature
 dht.begin();
 //wiFi
  pinMode(D2,OUTPUT); //led 
  delay(1000);
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(D2,HIGH);
    delay(500);
    digitalWrite(D2,LOW);
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}

//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop() {
   //temperature sensor
// Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  int h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  int t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  int f = dht.readTemperature(true);
   // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f) || f>100 || h>100 || t>100) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

 

  
  HTTPClient http;    //Declare object of class HTTPClient

String hh=String(h);
String tt=String(t);
String ff=String(f);

  //GET Data
 String  getData = "?temperature=" +tt + "&humidity=" +hh+"&HeatIndex="+ff; 
 //Note "?" added at front
String  Link = "http://ip_address/php_code/get_data.php" + getData;
  
  http.begin(Link);     //Specify request destination
  
  int httpCode = http.GET();            //Send the request
  String payload = http.getString();    //Get the response payload

  Serial.println(httpCode); //Print HTTP return code
  
  Serial.println(payload);    //Print request response payload
  
  Serial.println("");
  Serial.println("Temperature , Humidity , Heat Index");
  Serial.println("");
 Serial.println(tt); Serial.println(hh); Serial.println(ff);
 Serial.println("");


  http.end();  //Close connection
  
  delay(5000);  //GET Data at every 5 seconds

 
}
//=======================================================================
