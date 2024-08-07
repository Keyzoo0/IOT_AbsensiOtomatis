void setup_time(){
   timeClient.begin();
   scan_time();
   read_time();

}

void scan_time(){
  timeClient.update();

  // Mendapatkan waktu sekarang
  unsigned long epochTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime ((time_t *)&epochTime);

  // Mendapatkan dan mencetak hari
  day = ptm->tm_mday;
  month = ptm->tm_mon + 1; // tm_mon adalah bulan sejak Januari (0-11), jadi tambahkan 1
  year = ptm->tm_year + 1900; // tm_year adalah tahun sejak 1900, jadi tambahkan 1900
  hour = ptm->tm_hour;
  minute = ptm->tm_min;
  second = ptm->tm_sec;

  switch (ptm->tm_wday) {
    case 0: weekDay = "Minggu"; break;
    case 1: weekDay = "Senin"; break;
    case 2: weekDay = "Selasa"; break;
    case 3: weekDay = "Rabu"; break;
    case 4: weekDay = "Kamis"; break;
    case 5: weekDay = "Jumat"; break;
    case 6: weekDay = "Sabtu"; break;
  }
  // print_time();

}

void print_time() {
  
  // Mencetak waktu lengkap
  Serial.print("Tanggal: ");
  Serial.print(day);
  Serial.print("/");
  Serial.print(month);
  Serial.print("/");
  Serial.print(year);
  Serial.print(" - ");
  Serial.print(weekDay);
  Serial.print(" ");
  Serial.print(hour);
  Serial.print(":");
  Serial.print(minute);
  Serial.print(":");
  Serial.println(second);
}

void read_time(){
   current_day = String(day) ; 
   current_month = String(month) ;
   current_year = String(year) ;
   current_hour = String(hour) ;
   current_minute = String(minute) ;
   current_second = String(second) ;
  
  current_time = weekDay + ", " + current_hour + ":" + current_minute; 
  send_current_time = weekDay + ", " + current_day + "/" + current_month + "/" + current_year + " - " + current_hour + ":" + current_minute + ":" + current_second; 
  
  
}