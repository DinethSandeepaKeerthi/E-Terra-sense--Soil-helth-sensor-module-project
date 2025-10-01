
#include <SPI.h>
#include <Wire.h>

#define RS485RX             16
#define RS485TX             17

unsigned char byteRequest[8] = {0X01, 0X03, 0X00, 0X00, 0X00, 0X07, 0X04, 0X08};
unsigned char byteResponse[19] = {};

void setup() {
  Serial.begin(9600);
  Serial2.begin(4800, SERIAL_8N1,RS485RX, RS485TX);

}

void loop() {
  Serial2.write(byteRequest, sizeof(byteRequest));

  if (Serial2.available() >= sizeof(byteResponse)) {        // Check if there are enough bytes available to read
    Serial2.readBytes(byteResponse, sizeof(byteResponse));  // Read the received data into the byteResponse array
    // Parse and print the received data in decimal format
    unsigned int soilHumidity = (byteResponse[3] << 8) | byteResponse[4];
    unsigned int soilTemperature = (byteResponse[5] << 8) | byteResponse[6];
    unsigned int soilConductivity = (byteResponse[7] << 8) | byteResponse[8];
    unsigned int soilPH = (byteResponse[9] << 8) | byteResponse[10];
    unsigned int nitrogen = (byteResponse[11] << 8) | byteResponse[12]; // N
    unsigned int phosphorus = (byteResponse[13] << 8) | byteResponse[14]; // P
    unsigned int potassium = (byteResponse[15] << 8) | byteResponse[16]; // K

    Serial.print("Soil Humidity: ");
    Serial.println((float)soilHumidity / 10.0);
    Serial.print("Soil Temperature: ");
    Serial.println((float)soilTemperature / 10.0);
    Serial.print("Soil Conductivity: ");
    Serial.println(soilConductivity);
    Serial.print("Soil pH: ");
    Serial.println((float)soilPH / 10.0);
    Serial.print("Nitrogen: ");
    Serial.println(nitrogen);
    Serial.print("Phosphorus: ");
    Serial.println(phosphorus);
    Serial.print("Potassium: ");
    Serial.println(potassium);
    Serial.println("\n\n");
  }
    delay(1000);
}

