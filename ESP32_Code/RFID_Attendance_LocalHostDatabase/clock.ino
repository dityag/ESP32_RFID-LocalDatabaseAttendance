static const char* const wd[7] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu"};
static const char* const md[12] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli",
                                   "Agustus", "September", "Oktober", "November", "Desember"
                                  };

void ui_clock() {
  display.clearDisplay();

  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
  // Serial.println(p_tm);
  display.fillRect(0, 0, 128, 18, SH110X_WHITE);
  display.fillRect(0, 19, 128, 19, SH110X_BLACK);
  display.fillRect(0, 35, 128, 43, SH110X_WHITE);

  display.setTextColor(SH110X_BLACK);        // Draw SH110X_WHITEE text
  display.setTextSize(2);             // Normal 2:2 pixel scale
  display.setCursor(5, 1);
  display.print(wd[p_tm->tm_wday]);

  t = dht.readTemperature();
  display.setTextColor(SH110X_BLACK);
  display.setTextSize(1);
  display.setCursor(82, 5);
  display.print(t);
  display.print(" C");

  display.setTextColor(SH110X_WHITE);
  display.setTextSize(1);             // Normal 2:2 pixel scale
  display.setCursor(18, 23);
  if ((p_tm->tm_mday) < 10) {
    display.print("0");
    display.print(p_tm->tm_mday);
  }
  else display.print(p_tm->tm_mday);
  display.print(" ");
  display.print(md[p_tm->tm_mon]);
  display.setCursor(90, 23);
  display.print(p_tm->tm_year + 1900);

  display.setTextSize(3);             // Normal 2:2 pixel scale
  display.setTextColor(SH110X_BLACK);        // Draw SH110X_WHITEE text
  display.setCursor(4, 40);
  if ((p_tm->tm_hour) < 10) {
    display.print("0");
    display.print(p_tm->tm_hour);
  }
  else display.print(p_tm->tm_hour);
  display.print(":");
  if ((p_tm->tm_min) < 10) {
    display.print("0");
    display.print(p_tm->tm_min);
  }
  else display.print(p_tm->tm_min);
  display.setTextSize(1);
  display.print(" ");
  display.setTextSize(2);
  if ((p_tm->tm_sec) < 10) {
    display.print("0");
    display.println(p_tm->tm_sec);
  }
  else display.println(p_tm->tm_sec);
  display.display();
}