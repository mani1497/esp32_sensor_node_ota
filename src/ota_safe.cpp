#include "ota_safe.h"

bool OTASafe::begin(const char* url, const char* expectedSha256){
    _url = url;
    _expectedSha256 = expectedSha256;
    return true;
}

bool OTASafe::download_and_verify(){
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient https;
    https.begin(client, _url);

    int httpCode = https.GET();
    if(httpCode != HTTP_CODE_OK){
        Serial.printf("OTA HTTP GET failed: %d\n", httpCode);
        return false;
    }

    int len = https.getSize();
    if(!Update.begin(len)){
        Serial.println("OTA Begin failed");
        return false;
    }

    WiFiClient* stream = https.getStreamPtr();
    uint8_t buff[256];
    int bytesRead;
    while((bytesRead = stream->read(buff, sizeof(buff)))>0){
        Update.write(buff, bytesRead);
    }

    if(!Update.end()){
        Serial.printf("OTA End failed: %s\n", Update.errorString());
        return false;
    }

    if(!verifySHA256()){
        Serial.println("SHA256 mismatch, OTA aborted");
        return false;
    }

    return true;
}

void OTASafe::perform_update(){
    Serial.println("OTA update successful, rebooting...");
    ESP.restart();
}

bool OTASafe::verifySHA256(){
    // SHA256 verification logic
    // Can use mbedtls_sha256 or ArduinoSHA256
    return true; // placeholder, implement real verification
}
