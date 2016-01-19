#include "ESP8266.h"
#include "SoftwareSerial.h" 
#include <LiquidCrystal.h>

const int numRows = 2;
const int numCols = 16;
const double dBAnalogQuiet = 10; // envelope - calibrated value from analog input (48 dB equivalent)
const double dBAnalogModerate = 12;
const double dBAnalogLoud = 17;
int count;

// check your LCD connections
LiquidCrystal lcd(9, 8, 7, 6, 5, 4);

// replace with your WiFi connection info
#define WLAN_SSID "network"
#define WLAN_PASS "password"
#define PIN_ANALOG_IN A0

#define PIN_QUIET 10
#define PIN_MODERATE 11
#define PIN_LOUD 12

SoftwareSerial Serial1(2,3);

ESP8266 wifi(Serial1);

void setup() 
{
  Serial.begin(9600);
  
  Serial1.begin(9600);   

  pinMode(PIN_QUIET, OUTPUT);
  pinMode(PIN_MODERATE, OUTPUT);
  pinMode(PIN_LOUD, OUTPUT);

  lcdSetup();
  
  while (!Serial);      
  Serial.println("ESP is connected.");
  restartESP();
  
  pinMode(A0, INPUT);
  count = 0;
}

void loop() 
{
  int value, i;
  float decibelsValueQuiet = 49.5;
  float decibelsValueModerate = 65;
  float decibelsValueLoud = 70;
  float valueDb;
  
  // Check the envelope input
  
  value = analogRead(PIN_ANALOG_IN);
    
  if (value < 13)
  {
    digitalWrite(PIN_QUIET, HIGH);
    digitalWrite(PIN_MODERATE, LOW);
    digitalWrite(PIN_LOUD, LOW);

    Serial.print("Quiet. Value: ");
    Serial.print(value);
    Serial.print("  ");

    lcd.print("Status: ");
    lcd.setCursor(8,0);
    
    for (i = 8; i <= 16; i++)
      lcd.print(" ");

    lcd.setCursor(8,0);
    lcd.print("Quiet");
    lcd.setCursor(0, 1);
    lcd.print("Value: ");
    lcd.setCursor(9,1);

    for (i = 9; i <= 16; i++)
      lcd.print(" ");
    
    lcd.setCursor(9,1);

    decibelsValueQuiet += calculateDecibels(value, 'q');

    lcd.print(decibelsValueQuiet);
    lcd.print("dB");
    
    Serial.println(decibelsValueQuiet);
    valueDb = decibelsValueQuiet;
    count = count+1;
  }
  else if ((value > 13) && ( value <= 23) )
  {
    digitalWrite(PIN_QUIET, LOW);
    digitalWrite(PIN_MODERATE, HIGH);
    digitalWrite(PIN_LOUD, LOW);

    Serial.print("Moderate. Value: ");
    Serial.print(value);
    Serial.print("  ");
    
    lcd.print("Status: ");
    lcd.setCursor(8,0);
    
    for (i = 8; i <= 16; i++)
      lcd.print(" ");
    
    lcd.setCursor(8,0);
    lcd.print("Moderate");
    lcd.setCursor(0, 1);
    lcd.print("Value: ");
    lcd.setCursor(9, 1);
    
    for (i = 9; i <= 16; i++)
      lcd.print(" ");

    lcd.setCursor(9,1);
    
    decibelsValueModerate += calculateDecibels(value, 'm');

    lcd.print(decibelsValueModerate);
    lcd.print("dB");

    Serial.println(decibelsValueModerate);

    valueDb = decibelsValueModerate;
    count = count+1;
  }
  else if(value > 22)
  {
    digitalWrite(PIN_QUIET, LOW);
    digitalWrite(PIN_MODERATE, LOW);
    digitalWrite(PIN_LOUD, HIGH);

    Serial.print("Loud. Value: ");
    Serial.print(value);
    Serial.print("  ");

    lcd.print("Status: ");
    lcd.setCursor(8,0);
    
    for (i = 8; i <= 16; i++)
      lcd.print(" ");
    
    lcd.setCursor(8,0);
    lcd.print("Loud");
    lcd.setCursor(0, 1);
    lcd.print("Value: ");
    lcd.setCursor(9, 1);
    
    for (i = 9; i <= 16; i++)
      lcd.print(" ");
    lcd.setCursor(9, 1);
    
    decibelsValueLoud += calculateDecibels(value, 'l');

    lcd.print(decibelsValueLoud);
    lcd.print("dB");
    
    Serial.println(decibelsValueLoud);
    
    valueDb = decibelsValueLoud;
    count = count+1;
  }

  lcd.setCursor(0,0);
  delay(400);

  Serial.println(count);
  
  if (count == 50) {
    sendToThingSpeak(valueDb);
    count = 0;
  }
}

void restartESP (void) 
{  
  Serial.print("FW Version:");
  Serial.println(wifi.getVersion().c_str());

  if (wifi.setOprToStation()) {
    Serial.print("Station mode OK\r\n");
  } else {
    Serial.print("Station mode ERROR\r\n");
  }
  if (wifi.joinAP(WLAN_SSID, WLAN_PASS)) {
    Serial.print("Joining AP successfully\r\n");
    Serial.print("IP:");
    Serial.println( wifi.getLocalIP().c_str());       
  } else {
    Serial.print("Joining AP failed\r\n");
  }
  if (wifi.disableMUX()) {
    Serial.print("Single Con OK\r\n");
  } else {
    Serial.print("Single Error OK\r\n");
  }
  Serial.print("End of setup\r\n"); 
}

void lcdSetup()
{
  lcd.begin(numCols, numRows);
  lcd.clear();
  lcd.setCursor(4, 1); // goes to column 4, row 1
  lcd.print("Starting...");
  delay(1000);
  lcd.clear();
}

float calculateDecibels(int x, char c)
{
  float decibelsCalculated;
  
    if (c == 'q')
      decibelsCalculated = 20 * log10(x/dBAnalogQuiet);
    if (c == 'm')
      decibelsCalculated = 20 * log10(x/dBAnalogModerate);
    if (c == 'l')
      decibelsCalculated = 20 * log10(x/dBAnalogLoud);  
  
  return (decibelsCalculated);
}

void sendToThingSpeak(float valueInDecibels)
{
  String valueStr = "";
  valueStr += valueInDecibels;

  Serial.println(valueStr);

  static long startTime = millis();
  char getBuffer[256] = {'\0'};
  
  if (wifi.kick()) {
    // replace IP (this one is ThingSpeak)
    wifi.createTCP("184.106.153.149", 80);
    long thisTime = millis();
    // replace GET request KEY and FIELD
    sprintf(getBuffer, "GET /update?key=KEY&FIELD=%s\r\nHost: thingspeak\r\n\r\n", valueStr.c_str());
    Serial.print("Starting to send at "); Serial.println(millis());
    wifi.send((const uint8_t *)getBuffer, strlen(getBuffer));
    Serial.print("Ending at "); Serial.println(millis());
    Serial.print(getBuffer);
    delay(100);
    wifi.releaseTCP();
  } else {
    wifi.restart();
    Serial.println("ESP8266 died. Restarting...\n");
    delay(3000);
    restartESP();
    startTime = millis();
    Serial.println("");
  }

  delay(1600);
}
















