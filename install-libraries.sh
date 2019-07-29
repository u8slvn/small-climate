
fetch_librarie () {
  printf "Dowloading %s...\n" "$2"
  wget -q "$1" -O "/tmp/$2.zip"
  unzip -oqj "/tmp/$2.zip" -d "./sc-probe-1/libraries/$2"
  rm "/tmp/$2.zip"
}

if [ ! -d ./sc-probe-1/libraries ]; then
  printf "Creating libraries directory...\n"
  mkdir -p ./sc-probe-1/libraries
fi

fetch_librarie https://github.com/adafruit/Adafruit_SSD1306/archive/1.3.0.zip Adafruit_SSD1306
fetch_librarie https://github.com/adafruit/Adafruit-GFX-Library/archive/1.5.6.zip Adafruit-GFX-Library
fetch_librarie https://github.com/adafruit/Adafruit_Sensor/archive/1.0.3.zip Adafruit_Sensor
fetch_librarie https://github.com/adafruit/DHT-sensor-library/archive/1.3.7.zip DHT-sensor-library

printf "Dependencies installation ended.\n"
