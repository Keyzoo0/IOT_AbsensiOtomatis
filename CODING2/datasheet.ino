void setup_datasheet(){
    
    GSheet.printf("ESP Google Sheet Client v%s\n\n", ESP_GOOGLE_SHEET_CLIENT_VERSION);
    GSheet.setTokenCallback(tokenStatusCallback);
    GSheet.setPrerefreshSeconds(10 * 60); // 10 minute 
    GSheet.begin(CLIENT_EMAIL, PROJECT_ID, PRIVATE_KEY);
    taskComplete = true;
    lcd.clear();
    lcd.print("Preparing Finish!") ;
    delay(2000);

}
void send_datasheet(){
  ready = GSheet.ready();

    if (send_data == true){
        send_data = false ;
        
        FirebaseJson response;

        Serial.println("\nAppend spreadsheet values...");
        Serial.println("----------------------------");

        FirebaseJson valueRange;

       
        valueRange.add("majorDimension", "COLUMNS");
        valueRange.set("values/[0]/[0]", sendNama);
        valueRange.set("values/[1]/[0]", sendId);
        valueRange.set("values/[2]/[0]", send_current_time);
        valueRange.set("values/[3]/[0]", send_status);
        // valueRange.set("values/[4]/[0]", sendKeterangan);

        // For Google Sheet API ref doc, go to https://developers.google.com/sheets/api/reference/rest/v4/spreadsheets.values/append
        // Append values to the spreadsheet
        bool success = GSheet.values.append(&response /* returned response */, spreadsheetId /* spreadsheet Id to append */, "Sheet1!A1" /* range to append */, &valueRange /* data range to append */);
        if (success){
            response.toString(Serial, true);
            valueRange.clear();
        }
        else{
            Serial.println(GSheet.errorReason());
        }
        Serial.println();
        Serial.println(ESP.getFreeHeap());
    }

}


void tokenStatusCallback(TokenInfo info){
    if (info.status == token_status_error){
        GSheet.printf("Token info: type = %s, status = %s\n", GSheet.getTokenType(info).c_str(), GSheet.getTokenStatus(info).c_str());
        GSheet.printf("Token error: %s\n", GSheet.getTokenError(info).c_str());
        delay(5);
    }
    else{
        GSheet.printf("Token info: type = %s, status = %s\n", GSheet.getTokenType(info).c_str(), GSheet.getTokenStatus(info).c_str());
        delay(15);
    }
}
