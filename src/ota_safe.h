#ifndef OTA_SAFE_H
#define OTA_SAFE_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <Update.h>
#include <WiFiClientSecure.h>
#include <mbedtls/sha256.h>

class OTASafe {
public:
    OTASafe() {}
    bool begin(const char* url, const char* expectedSha256);
    bool download_and_verify();
    void perform_update();

private:
    const char* _url;
    const char* _expectedSha256;
    bool verifySHA256();
};

#endif
