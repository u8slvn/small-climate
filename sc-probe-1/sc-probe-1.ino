#include <DHT.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define DHTPIN 2
#define DHTTYPE DHT22

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

DHT dht(DHTPIN, DHTTYPE);

String temperatureText = "Temperature: ";
String temperatureUnit = String(char(247)) + "C";
String humidityText = "Humidity: ";
String humidityUnit = "%";

int check = 2000;
float temp;
float hum;

void displayClimate(float temp, float hum) {
  display.clearDisplay();
  display.setCursor(0, 3);
  display.println(temperatureText + temp + temperatureUnit);
  display.setCursor(0, 19);
  display.println(humidityText + hum + humidityUnit);
  display.display();
}

void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  delay(2000);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  dht.begin();
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  displayClimate(temp, hum);
  delay(check);
}
