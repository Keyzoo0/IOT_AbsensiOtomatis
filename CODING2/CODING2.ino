#include "variabel.h"

void setup() {
  setup_lcd();
  setup_rfid();
  setup_wifi();
  setup_datasheet();
  display_start();
  setup_time();
  
}

void loop() {
  scan_time();
  scan_rfid();
  send_datasheet();
}

