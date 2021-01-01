#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <SparkFunHTU21D.h>
#include <config.h>

HTU21D htu21d;

WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);


Adafruit_MQTT_Publish temperaturePub = Adafruit_MQTT_Publish(&mqtt, TEMPERATURE_FEED);
Adafruit_MQTT_Publish humidityPub = Adafruit_MQTT_Publish(&mqtt, HUMIDITY_FEED);

Adafruit_MQTT_Subscribe switchTrigger = Adafruit_MQTT_Subscribe(&mqtt, SWITCH_FEED);

#include <functions.h>

void setup() {

  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);

  delay(10);

  Serial.println(F("Starting"));

  Serial.println(); Serial.println();

  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  pinMode(RELAY_PIN, OUTPUT);

  relaySwitch(false);

  mqtt.subscribe(&switchTrigger);

  htu21d.begin();
}

void loop() {

  MQTT_connect();

  Adafruit_MQTT_Subscribe *subscription;


  float temperature = htu21d.readTemperature();
  float humidity = htu21d.readHumidity();

  Serial.print(" Temperature:");
  Serial.print(temperature, 1);
  Serial.print("C");
  Serial.print(" Humidity:");
  Serial.print(humidity, 1);
  Serial.print("%");

  Serial.println();

  temperaturePub.publish(temperature);

  humidityPub.publish(humidity);

  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &switchTrigger) {
      Serial.print(F("Got: "));
      Serial.println((char *)switchTrigger.lastread);

      relaySwitch(strcmp((char *)switchTrigger.lastread, "on") == 0);

    }
  }

}
