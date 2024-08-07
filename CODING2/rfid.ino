void setup_rfid(){
   while(!Serial); 
  SPI.begin(); 
  rfid.PCD_Init(); 
  

}

void readRFID() {
  rfid.PICC_ReadCardSerial();
  lcd.clear();
  id = String(rfid.uid.uidByte[0]) + " " + String(rfid.uid.uidByte[1]) + " " + String(rfid.uid.uidByte[2]) + " " + String(rfid.uid.uidByte[3]);
  Serial.println(id);
  compare();

}

void scan_rfid() {
  display_tap();
  if(rfid.PICC_IsNewCardPresent() && logic_read_rfid == true) {
    logic_read_rfid = false;
    readRFID();
    read_time();
  }else{
    logic_read_rfid = true;
  }
  delay(10);
}

void compare(){
  lcd.setCursor(0, 0);
bool card_found = false;

for (int i = 0; i < max_user; ++i) {
    if (id == card_id[i]) {
        lcd.print(name_id[i]);
        index_id[i] = !index_id[i];
        send_status = status_id[index_id[i]];  
        sendNama = name_id[i];
        sendId = card_id[i];
        // sendKeterangan = keterangan_id[i];
        send_data = true;
        card_found = true;
        display_card_found(sendNama , current_time , send_status);
        // verifyCheckIn();
        break; // Keluar dari loop setelah menemukan kartu yang cocok
    }

}
 
  if (!card_found) {
   display_card_not_found();
  }
}