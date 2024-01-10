//ESP32----------------------------
#include <WiFi.h>
#include <HTTPClient.h>
#include <time.h>
/* Set these to your desired credentials. */
const char *ssid = "Pejuang Sarjana";
const char *password = "kontrakanpanass";
const char *device_token = "99161b8db02e967f";
int timezone = 7 * 3600;  //Replace "x" your timezone.
int time_dst = 0;
String getData, Link;
String OldCardID = "";

unsigned long previousMillis1 = 0;
const long interval1 = 1000;  // interval at which to blink (milliseconds)
int ledState = LOW;           // ledState used to set the LED

unsigned long previousMillis2 = 0;

const long intervalLock = 200;
unsigned long currentMillisLock;

String URL = "http://192.168.18.11/rfidattendance/getdata.php";

//RFID-----------------------------
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 5
#define RST_PIN 27
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.

//MP3------------------------------
#include "HardwareSerial.h"
#include "DFRobotDFPlayerMini.h"
const byte RXD2 = 16;    // Connects to module's RX
const byte TXD2 = 17;    // Connects to module's TX
HardwareSerial dfSD(1);  // Use UART channel 1
DFRobotDFPlayerMini player;

//DHT11----------------------------
#include "DHT.h"
#define DHTPIN 13
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float t;

//OLED-----------------------------
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "icon.h"
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 0
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Door
#define door 12
int lock_door;

void setup() {

  Serial.begin(9600);

  pinMode(door, OUTPUT);

  SPI.begin();         // Init SPI bus
  mfrc522.PCD_Init();  // Init MFRC522 card
  dht.begin();
  dfSD.begin(9600, SERIAL_8N1, RXD2, TXD2);  // 16,17
  if (player.begin(dfSD)) {
    Serial.println("OK");
    player.volume(30);  //30 is very loud
  }
  //-----------initiate OLED display-------------
  if (!display.begin(0x3C, true)) {  // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }
  connectToWiFi();
  configTime(timezone, time_dst, "pool.ntp.org", "time.nist.gov");
}
//************************************************************************
void loop() {
  //check if there's a connection to Wi-Fi or not
  if (!WiFi.isConnected()) {
    connectToWiFi();  //Retry to connect to Wi-Fi
  }

  ui_clock();

  if (lock_door == 1) {
    digitalWrite(door, LOW);
    currentMillisLock++;
  } else {
    digitalWrite(door, HIGH);
  }

  if (currentMillisLock > intervalLock) {
    lock_door = 0;
    currentMillisLock = 0;
  }


  Serial.print(lock_door);
  Serial.println(currentMillisLock);
  //---------------------------------------------
  if (millis() - previousMillis2 >= 5000) {
    previousMillis2 = millis();
    OldCardID = "";
  }
  //---------------------------------------------
  //look for new card
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;  //got to start of loop if there is no card present
  }
  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;  //if read card serial(0) returns 1, the uid struct contians the ID of the read card.
  }
  String CardID = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    CardID += mfrc522.uid.uidByte[i];
  }
  //---------------------------------------------
  if (CardID == OldCardID) {
    return;
  } else {
    OldCardID = CardID;
  }
  //---------------------------------------------
  //  Serial.println(CardID);
  SendCardID(CardID);

  display.clearDisplay();
}