#define bluePin 2
#define redPin 4
#define buzzerPin 13

void setup_lcd() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.print("Prepare System");
}

void display_start(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Program  Absensi");
    lcd.setCursor(0,1);
    lcd.print("    Otomatis    ");
    delay(3000);
}

void display_tap(){
  while(1){
    lcd.setCursor(0,0);
    lcd.print("    SILAHKAN    ");
    lcd.setCursor(0,1);
    lcd.print("   TAP KARTU!   ");
    delay(50);
    if(!rfid.PICC_IsNewCardPresent()) break;
  }
}

void display_card_not_found(){
    lcd.clear();
    digitalWrite(redPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("  Kartu Tidak  ");
    lcd.setCursor(0, 1);
    lcd.print("    Dikenal!    ");
    sendNama = "";
    sendId = "";
    delay(3000);
    digitalWrite(redPin, LOW);  
    digitalWrite(buzzerPin, LOW);
}

void display_card_found(String nama = "", String waktu = "" , String status = ""){
    lcd.clear();
    digitalWrite(bluePin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(bluePin, LOW);
    digitalWrite(buzzerPin, LOW);
    lcd.setCursor(0, 0);
    if(status == "Masuk"){
      lcd.print(" Selamat Datang ");
      lcd.setCursor(8-(nama.length()/2), 1);
      lcd.print(nama);
      delay(3000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Status : " + status);
      lcd.setCursor(0, 1);
      lcd.print(waktu);
      delay(3000);   
      userCheckInHour = hour;
      userCheckInMinute = minute;
      verifyCheckIn();
    }
    else {
      lcd.print("  Sampai Jumpa  ");
      lcd.setCursor(8-(nama.length()/2), 1);
      lcd.print(nama);
      delay(3000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Status : " + status);
      lcd.setCursor(0, 1);
      lcd.print(waktu);
      delay(3000);
    }  
}

void verifyCheckIn(){
  if((userCheckInHour < checkInHour) || ((userCheckInHour == checkInHour) && (userCheckInMinute <= checkInMinute))){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("      ANDA      ");
    lcd.setCursor(0, 1);
    lcd.print("   TEPAT WAKTU  ");
    delay(1000);
  }
  else{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("      ANDA      ");
    lcd.setCursor(0, 1);
    lcd.print("    TERLAMBAT   ");
    delay(1000);
  }
}