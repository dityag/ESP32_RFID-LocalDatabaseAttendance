//************send the Card UID to the website*************
void SendCardID(String Card_uid) {
  Serial.println("Sending the Card ID");
  if (WiFi.isConnected()) {

    HTTPClient http;  //Declare object of class HTTPClient
    //GET Data
    getData = "?card_uid=" + String(Card_uid) + "&device_token=" + String(device_token);  // Add the Card ID to the GET array in order to send it
    //GET methode
    Link = URL + getData;
    http.begin(Link);  //initiate HTTP request   //Specify content-type header

    int httpCode = http.GET();          //Send the request
    String payload = http.getString();  //Get the response payload

    //    Serial.println(Link);   //Print HTTP return code
    Serial.println(httpCode);  //Print HTTP return code
    Serial.println(Card_uid);  //Print Card ID
    Serial.println(payload);   //Print request response payload
    
    if (httpCode == 200) {
      if (payload.substring(0, 5) == "login") {
        String user_name = payload.substring(5);
        //  Serial.println(user_name);
        lock_door = 1;
        display.clearDisplay();
        display.setTextSize(3);              // Normal 2:2 pixel scale
        display.setTextColor(SH110X_WHITE);  // Draw SH110X_WHITEE text
        display.setCursor(15, 0);            // Start at top-left corner
        display.print(F("LOGIN"));
        display.setTextSize(2);
        display.setCursor(0, 30);
        display.print(user_name);
        display.display();
        player.play(3);
      } else if (payload.substring(0, 6) == "logout") {
        String user_name = payload.substring(6);
        //  Serial.println(user_name);
        lock_door = 1;
        display.clearDisplay();
        display.setTextSize(3);              // Normal 2:2 pixel scale
        display.setTextColor(SH110X_WHITE);  // Draw SH110X_WHITEE text
        display.setCursor(10, 0);            // Start at top-left corner
        display.print(F("LOGOUT"));
        display.setTextSize(2);
        display.setCursor(0, 30);
        display.print(user_name);
        display.display();
        player.play(4);
      } else if (payload == "succesful") {
        display.clearDisplay();
        display.setTextSize(1);              // Normal 2:2 pixel scale
        display.setTextColor(SH110X_WHITE);  // Draw SH110X_WHITEE text
        display.setCursor(20, 0);            // Start at top-left corner
        display.println(F("Berhasil"));
        display.setCursor(0, 20);  // Start at top-left corner
        display.println(F("Mendaftarkan"));
        display.setTextSize(1);
        display.println(F("Dengan nomor kartu :"));
        display.print(Card_uid);
        display.display();
        player.play(9);
      } else if (payload == "available") {
        display.clearDisplay();
        display.setTextSize(1);              // Normal 2:2 pixel scale
        display.setTextColor(SH110X_WHITE);  // Draw SH110X_WHITEE text
        display.setCursor(35, 0);            // Start at top-left corner
        display.println(F("Sudah"));
        display.setCursor(15, 20);  // Start at top-left corner
        display.println(F("Terdaftar"));
        display.setTextSize(1);
        display.println(F("Dengan nomor kartu :"));
        display.print(Card_uid);
        display.display();
        player.play(10);
      }
      delay(2000);
      http.end();  //Close connection
    }
  }
}
