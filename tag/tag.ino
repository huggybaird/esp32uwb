/*

For ESP32 UWB or ESP32 UWB Pro

*/

#include <SPI.h>
#include "DW1000Ranging.h"
#include <arduino-timer.h>

#define SPI_SCK 18
#define SPI_MISO 19
#define SPI_MOSI 23
#define DW_CS 4

#define ANCHOR_X "1786" 
#define ANCHOR_X_ADDRESS "86:17:5B:D5:A9:9A:E2:9C"
#define ANCHOR_Y "1787" 
#define ANCHOR_Y_ADDRESS "87:17:5B:D5:A9:9A:E2:9C"
#define ANCHOR_Z "1788" 
#define ANCHOR_Z_ADDRESS "88:17:5B:D5:A9:9A:E2:9C"

// connection pins
const uint8_t PIN_RST = 27; // reset pin
const uint8_t PIN_IRQ = 34; // irq pin
const uint8_t PIN_SS = 4;   // spi select pin

auto timer = timer_create_default();

float xDistance = 0.0f;
float yDistance = 0.0f;
float zDistance = 0.0f;

float xRfPower = 0.0f;
float yRfPower = 0.0f;
float zRfPower = 0.0f;

void setup()
{
    Serial.begin(115200);
    delay(1000);
    //init the configuration
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
    DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin
    //define the sketch as anchor. It will be great to dynamically change the type of module
    DW1000Ranging.attachNewRange(newRange);
    DW1000Ranging.attachNewDevice(newDevice);
    DW1000Ranging.attachInactiveDevice(inactiveDevice);
    //Enable the filter to smooth the distance
    //DW1000Ranging.useRangeFilter(true);

    //we start the module as a tag
    DW1000Ranging.startAsTag("7D:00:22:EA:82:60:3B:9C", DW1000.MODE_LONGDATA_RANGE_LOWPOWER);
    //Original value: DW1000Ranging.startAsTag("7D:00:22:EA:82:60:3B:9C", DW1000.MODE_LONGDATA_RANGE_LOWPOWER);

    timer.every(500, printXyzCoordinates);
}

void loop()
{
    timer.tick();
    DW1000Ranging.loop();
    //Serial.println("TAG: Loop is occuring fine");
    //delay(3000);
}


bool printXyzCoordinates(void *) { 
  Serial.print("TAG Position: X: ");
  Serial.print(xDistance);
  Serial.print("       Y: ");
  Serial.print(yDistance);
  Serial.print("       Z: ");
  Serial.println(zDistance);
  return true; // keep timer active? true
}


void newRange()
{
    String shortAddress =  String(DW1000Ranging.getDistantDevice()->getShortAddress(),HEX);
    if(shortAddress==ANCHOR_X){
      xDistance = DW1000Ranging.getDistantDevice()->getRange();
      xRfPower = DW1000Ranging.getDistantDevice()->getRXPower();
      // Serial.print("X = ");
      // Serial.println(shortAddress);
    } else if(shortAddress==ANCHOR_Y){
      yDistance = DW1000Ranging.getDistantDevice()->getRange();
      xRfPower = DW1000Ranging.getDistantDevice()->getRXPower();
      // Serial.print("Y = ");
      // Serial.println(shortAddress);
    } else if(shortAddress==ANCHOR_Z){
      zDistance = DW1000Ranging.getDistantDevice()->getRange();
      xRfPower = DW1000Ranging.getDistantDevice()->getRXPower();
      // Serial.print("Z = ");
      // Serial.println(shortAddress);
    }
    else{
      Serial.print("Unknown Axis = ");
      Serial.println(shortAddress);
    }

    // Serial.print("TAG: from: ");
    // Serial.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);
    // Serial.print("\t Range: ");
    // Serial.print(DW1000Ranging.getDistantDevice()->getRange());
    // Serial.print(" m");
    // Serial.print("\t RX power: ");
    // Serial.print(DW1000Ranging.getDistantDevice()->getRXPower());
    // Serial.println(" dBm");
}

void newDevice(DW1000Device *device)
{
    Serial.print("ranging init; 1 device added ! -> ");
    Serial.print(" short:");
    Serial.println(device->getShortAddress(), HEX);
}

void inactiveDevice(DW1000Device *device)
{
    Serial.print("delete inactive device: ");
    Serial.println(device->getShortAddress(), HEX);
}