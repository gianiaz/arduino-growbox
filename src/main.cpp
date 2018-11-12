#include <Arduino.h>
#include <LedLib.h>
#include <DayNight.h>
#include <Servo.h>
#include <DHT.h>
#include <DHT_U.h>
#include <HumidityCO2Relay.h>
#include <LcdWrapper.h>
#include <Time.h>
#include <Button.h>

#define LED_RED_STATUS_PIN 3
#define LED_RED_STATUS_DATA 4
#define DAY_NIGHT_PIN_SERVO 10
#define DAY_NIGHT_PIN_RESISTOR A0
#define DAY_NIGHT_PIN_SERVO 10
#define HUMIDITY_TEMPERATURE_RELAY_PIN 6
#define HUMIDITY_TEMPERATURE_DHT_PIN 5
#define MODE_BUTTON_PIN 7
#define PLUS_BUTTON_PIN 8
#define MINUS_BUTTON_PIN 9


#define MENU_COPYRIGHT      0
#define MENU_TEMPERATURE    1
#define MENU_HYGROMETERS    2
#define MENU_MODIFY_UMIDITY 3
#define MENU_MODIFY_TEMPERATURE 4

int actualMenuEntry = 0;
String line1;
String line2;
LedLib ledRedStatus(LED_RED_STATUS_PIN);
LedLib ledRedData(LED_RED_STATUS_DATA);
DayNight disk(DAY_NIGHT_PIN_SERVO, DAY_NIGHT_PIN_RESISTOR, 500);
HumidityCO2Relay temperatureControl(HUMIDITY_TEMPERATURE_DHT_PIN, HUMIDITY_TEMPERATURE_RELAY_PIN, 40);
LcdWrapper lcd;
Button modeButton(MODE_BUTTON_PIN, 1000);
Button plusButton(PLUS_BUTTON_PIN, 1000);
Button minusButton(MINUS_BUTTON_PIN, 1000);
int position = 0;
bool modifiersButtonActive = false;
void printMenu() {
  switch (actualMenuEntry) {
    case MENU_COPYRIGHT:
      lcd.printLines("Growbox 1.1", "(c) gianiaz");
      modifiersButtonActive = false;
    break;
    case MENU_TEMPERATURE:
      line1 = "Temp.: "+temperatureControl.getTemperature()+" *C";
      line2 = "Hum. : "+temperatureControl.getHumidity()+ " %";
      lcd.printLines(line1, line2);
      modifiersButtonActive = false;
    break;
    case MENU_HYGROMETERS:
      line1 = "Hygrometers:";
      line2 = "NOTHING TO SHOW";
      lcd.printLines(line1, line2);
      modifiersButtonActive = false;
    break;
    case MENU_MODIFY_UMIDITY:
      line1 = "Hum. threshold";
      line2 = "Actual: "+String(temperatureControl.getHumidityThreshold());
      lcd.printLines(line1, line2);
      modifiersButtonActive = true;
    break;
    deault:
      Serial.println("Di qua non dovrei passarci");
  }
}

void substract() {
  switch (actualMenuEntry) {
    case MENU_MODIFY_UMIDITY:
      if(temperatureControl.getHumidityThreshold() >= 5) {
        temperatureControl.setHumidityThreshold(temperatureControl.getHumidityThreshold() - 5);
      }
    break;
  }
  printMenu();

}

void add() {
  switch (actualMenuEntry) {
    case MENU_MODIFY_UMIDITY:
      if(temperatureControl.getHumidityThreshold() <= 95) {
        temperatureControl.setHumidityThreshold(temperatureControl.getHumidityThreshold() + 5);
      }
    break;
    // case MENU_MODIFY_TEMPERATURE:
    //   if(temperatureControl.getTemperatureThreshold() <= 95) {
    //     temperatureControl.setThreshold(temperatureControl.getTemperatureThreshold() + 5);
    //   }
    // break;
  }
  printMenu();

}

void setup() {
  modeButton.setUp(false);
  plusButton.setUp(false);
  minusButton.setUp(false);
  Serial.begin(9600);
  disk.setDebug(false);
  disk.setUp();
  temperatureControl.setUp(false);
  ledRedData.blink(10, 50);
  ledRedStatus.powerOn();
  lcd.setUp(true);
  printMenu();
}

void loop() {
  ledRedData.updateStatus();
  ledRedStatus.updateStatus();
  temperatureControl.updateStatus();
  disk.updateStatus();

  if(modeButton.isPressed()) {
    Serial.println("Clicked");
    actualMenuEntry++;
    if(actualMenuEntry > 3) {
      actualMenuEntry = 0;
    }
    printMenu();
  }
  if(modifiersButtonActive) {
    if(plusButton.isPressed()) {
      add();
    }
    if(minusButton.isPressed()) {
      substract();
    }
  }
}
