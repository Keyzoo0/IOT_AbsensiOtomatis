void setup_wifi(){
  // Menghubungkan ke jaringan WiFi
  WiFi.setAutoReconnect(true);
  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan ke WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    lcd.print(".");

  }
  Serial.println(" terhubung!");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connecting to");
  lcd.setCursor(0, 1);
  lcd.print(ssid);
  delay(2000);
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

}