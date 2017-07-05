#ifndef pentesy_h
#define pentesy_h
#include "WProgram.h"

extern volatile uint8_t keyboard_leds;
extern const int ledPin;

extern int ledKeys();
extern bool isOnNumLock();
extern bool isOnCapsLock();

extern void popKey(int sleep);
extern void pushAndPopKey(uint8_t key_mod, uint8_t key, int sleep);

extern void raisingPrivileges();
extern void closeError();

extern bool isEngInput();
extern void changeLanguage();

extern void downloadAndExec(String url);
extern void ledBlink(int quantity, int time);

extern void minimizeWindows(bool minimize);
#endif
