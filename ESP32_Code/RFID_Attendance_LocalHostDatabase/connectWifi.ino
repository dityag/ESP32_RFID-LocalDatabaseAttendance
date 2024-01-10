//********************connect to the WiFi******************
void connectToWiFi() {
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SH110X_WHITE);        // Draw SH110X_WHITEE text
  display.setCursor(0, 0);             // Start at top-left corner
  display.print(F("Connecting to \n"));
  display.setCursor(0, 50);
  display.setTextSize(1);
  display.print(ssid);
  display.drawBitmap( 73, 10, Wifi_start_bits, Wifi_start_width, Wifi_start_height, SH110X_WHITE);
  display.display();
  delay(3000);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected");

  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SH110X_WHITE);        // Draw SH110X_WHITEE text
  display.setCursor(8, 0);             // Start at top-left corner
  display.print(F("Connected \n"));
  display.drawBitmap( 33, 15, Wifi_connected_bits, Wifi_connected_width, Wifi_connected_height, SH110X_WHITE);
  display.display();

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
  player.play(1);
  delay(5000);
}
//=======================================================================