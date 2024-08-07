//=================library==============
// #include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <MFRC522.h> 
#include <SPI.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <HTTPClient.h>
#include <ESP_Google_Sheet_Client.h>
#include <GS_SDHelper.h>

//=============rfid============================
#define CS_RFID 5
#define RST_RFID 15
MFRC522 rfid(CS_RFID, RST_RFID); 
//===============lcd=============================
LiquidCrystal_I2C lcd(0x27 , 16 , 2);


//==============================uid====================
int logic_read_rfid = true ;
#define max_user 4 // tambahkan user
String zuhar = "17 130 133 28";
String MasR = "4 121 132 250";
String rasyid = "159 76 183 43";
String amri = "63 139 181 43";


String card_id[max_user] = {zuhar , MasR, rasyid, amri} ;
String name_id[max_user] = {"Ahmad Zuhar" , "Mas R" , "Rasyid" , "Amri"} ;
String status_id[2] = {"Pulang" , "Masuk"} ;
// String keterangan_id[2] ={"Tepat Waktu" , "Terlambat"};
bool index_id[max_user];
String id;
String sendNama ;
String sendId ;
String send_status ;
// String sendKeterangan;


// ========================time==========================

// Mendefinisikan alamat waktu NTP
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 25200; // GMT+1, sesuaikan dengan zona waktu Anda
const int   daylightOffset_sec = 3600;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntpServer, gmtOffset_sec, 60000);

const int checkInHour = 14;
const int checkInMinute = 5;

int userCheckInHour;
int userCheckInMinute;

int day ;
int month ;
int year ;
int hour ;
int minute ;
int second ;
  // Mendapatkan dan mencetak hari dalam seminggu
String weekDay;

String current_day ;
String current_month ;
String current_year ;
String current_hour ;
String current_minute ;
String current_second ;

String current_time = "";
String send_current_time = "";


//=================wifi================
const char* ssid       = "Mas R";
const char* password   = "bbbbbbbb";

//========================datasheet=========
bool ready ;

// Your email to share access to the spreadsheet
#define USER_EMAIL "firdausy001@gmail.com"

// Google Project ID
#define PROJECT_ID "esp32-absensi-424411"

// Service Account's client email
#define CLIENT_EMAIL "esp32-absensi@esp32-absensi-424411.iam.gserviceaccount.com" 
// Service Account's private key
const char PRIVATE_KEY[] PROGMEM = "-----BEGIN PRIVATE KEY-----\nMIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQCnkd0G69PGyWY4\n/Rc+mCUhEoYcWnyyuhPEMnbPVWcghRjWHCNePRXm0QY9jhzea5RgslQYFVDkoG9a\nnr3+TkrQ//+TLO7g8nE5vybu7oRiYTKoK/Fy0gOIeG4rQYCQBr9sGhaly2uEZHCG\no7n4xbWCSxI58GLPx82637roHPgbGbBLHkWKoYW129WSTBJSqEakdJ/g+PSRdmiZ\n0OhqVdPWrG8uuyLvd3PHbqZcBzguDuf13lNsIS98bQHMa5mC1jzQnGZNUt7ZFGXR\nfkcatLTFhh/deNiIHXQ2m+A3hXJuBbyVgm7Ta8ARenU01A+QTsQNUAVLwUvdwJEj\nTLGDrj/DAgMBAAECggEAPC9ZDfvUr/C1LOHGH/7AUy0Wiwd7AyxvHggsARLA+/6h\n6YDouRfCjojjr2cj+kT0YXibWJ0LVVpENG2Qes6+82sG7eL1F0ksnpuHzchQNw+H\nBLzntyA0EaeDljisBs7NoPOLz9eMkdwLSGh0yqOkKhxxeuraaptuSmDB/k0tVXni\nv8UaOKTMIqdHi8vjiziOaln2trc65cMoJEy66PAPg1Ns9aIlE3iIU5aJpwqqUn4A\nN4OwzI1OTzFNnyTKHHxQU4nlMG9AGVlEQKSh+QIsUNhnmOqj/+9R1enfwhTYmQR8\nBH9hqS1Ph6FjsM6JeTYtt/Ps6lJxuYy5bSDbRFFtLQKBgQDgtpHVn64xdGnJhJHa\n8TUKBt2v1swluS1PW9aEx3dPzJpgobpPj5Khv2WhJp/pNd/fqADKK36hNUxNxlon\nxjGL8ZeFldB87iYE/2SIEWQxvJ3dHPcJk+ogsaDmUwPGj8ZZCnaoZf2S4RMcEzRr\ngbnYjY7zeXOMpuHZoD02Xvf7tQKBgQC+5omTskxa+jiHO2rXTt+JWGjy2WRqKuy5\n3gRRCAUXwA+3JviFDR9UOWmv8QS8tcL+02N5QGUC2aEEljYlt63pAhoa2Y6A0fkA\ntPGc/8DKQpyi8ecA0ZGHi/c+brAXvycefi5XlKd9Xx27WTqlJxgX/C1cg4gk3tjm\nB4OFgZKolwKBgHGTVTpHrt9IG3/DBYVHjKs4tSt+wUf/xCrsHAyYVHF81DorA+Pa\niR4/grpkr0ZL+I8udte4DBSmv54/tqmLvtcgkJjwE6RRKd40xzcOszmAP7nWPfYV\nUKydmtlO9AWT/YhbhYWvpu5p3CLAgiokMy6Evc/JfuGEJ3q7RrUIYwZRAoGBAIBq\nqKWYTVDt/dTKnYaU4j6MIJ0srCXXFkO6HAE+ed6OLoQwTQGD4E1SCcx3P46KXs/4\n93N7Y/fU2kIxod8hfnW+Gj1xmDEEDpLxJY9NZC0rPh9GxvSABXu/JeTzpLV0uyYC\nD76Om1T1BRUgYxjyAX0xAHq5aH4VAqdK6qiGj1elAoGAKYZ2mh/1chDTY+DQObGl\nmKG4A94pSDT7GPqKmLwrd1/FeOgbQm0V/Cgs/z8WywePEdo2lg1qktFE17gwzE1I\nfRSxljNbU0Pqvrw4gkdlSkn1MUu7487ZOyW2F/7u61FJhVSJGZmHuZFxMdc5Rv21\nyPxNNbG3ggyB8C8fgdf6QI0=\n-----END PRIVATE KEY-----\n";
// The ID of the spreadsheet where you'll publish the data
const char spreadsheetId[] = "17l-PWeJ466Fc7ovhQwswP2-lDMgEuFwErs_iChmE3OU";

bool taskComplete = false;

void tokenStatusCallback(TokenInfo info);

int send_data = false ;