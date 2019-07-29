#include <EEPROM.h>
#include <Wire.h>
#include <DHT.h>
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
String idText = "Id: ";

String ID;
int check = 2000;
float temp;
float hum;


// Generate a 14 characters id. Example: "r6d9-i2na-nox8".
String generateId() {
  char alphanumeric[] = {"abcdefghijklmnopqrstuvwxyz0123456789"};
  String id;
  for (int i = 1; i <= 12; i++) {
    if (i != 1 && i % 4 == 1) {
      id += "-";
    }
    id += alphanumeric[random(0, 35)];
  }
  return id;
}


String readId() {
  if (EEPROM.read(42) != '$') {
    return "";
  }
  char id[14];
  for (int address = 0; address <= 15; address++) {
    id[address] = EEPROM.read(address);
  }
  return String(id);
}


void writeId(String id) {
  EEPROM.write(42, '$');
  for (int address = 0; address <= 15; address++) {
    EEPROM.write(address, id[address]);
  }
}


/*
  Check if an id is stored in the EEPROM.
  If not, generate one and save it in the EEPROM.
*/
String getBoardId() {
  String id = readId();
  if (id == "") {
    id = generateId();
    writeId(id);
  }
  return id;
}


void displayClimate(float temp, float hum) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(temperatureText + temp + temperatureUnit);
  display.setCursor(0, 11);
  display.println(humidityText + hum + humidityUnit);
  display.setCursor(0, 22);
  display.println(idText + ID);
  display.display();
}


void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  delay(2000);

  display.setTextSize(1);
  display.setTextColor(WHITE);

  dht.begin();

  // Generate random seed based on analog noise.
  randomSeed(analogRead(0));
  ID = getBoardId();
}


void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  displayClimate(temp, hum);
  delay(check);
}
