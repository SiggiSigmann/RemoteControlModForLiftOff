
#include "Keyboard.h"

void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  Keyboard.begin();
  digitalWrite(12, HIGH);
}

//{not used, not used, right button, right button[up], right button[down], left button[up], left button[down], left button}

bool s[] = {false,false,false,false,false,false,false,false};
char c1[] = {0, 0, 'a',  KEY_RIGHT_ARROW, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_UP_ARROW, 'r'};
char c2[] = {0, 0, 't', 'f', 'c', KEY_DOWN_ARROW, KEY_UP_ARROW, 'r'};
char c3[] = {0, 0, 't', 'v', 'c', KEY_DOWN_ARROW, KEY_UP_ARROW, 'r'};
char c[8] = {0, 0, 'a',  KEY_RIGHT_ARROW, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_UP_ARROW, 'r'};
int switchTimer = 50;
int mode = 0;

void checkSwitch(int i){
  if(digitalRead(i) == HIGH){
    if(!s[i]){
       Keyboard.press(c[i]);
       s[i]=true;
       delay(10);
    }
  }else{
    if(s[i]){
      Keyboard.release(c[i]);
      s[i]=false;
      delay(10);
    }
  }
}

void resetSwitch(int i){
   Keyboard.release(c[i]);
   s[i]=false;
}

void copyArray(char* a){
  for(int i=0;i<8;i++){
    c[i] = a[i];
  }
}

void changeMode(){
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  
  switch(mode){
    case 0: copyArray(c1);
            digitalWrite(12, HIGH);
            break;
    case 1: copyArray(c2);
            digitalWrite(11, HIGH);
            break;
    case 2: copyArray(c3);
            digitalWrite(12, HIGH);
            digitalWrite(11, HIGH);
            break;
  }
}

void loop() {
  
  if(digitalRead(2) && digitalRead(7)){
    resetSwitch(2);
    resetSwitch(7);
    
    if(switchTimer){
      switchTimer--;
    }else{
      digitalWrite(10,HIGH);
      if(!s[0]){
        s[0] = true;
        if(mode == 2){
          mode = 0;
        }else{
          mode++;
        }
        changeMode();
      }
    }
    
  }else{
    s[0] = false;
    switchTimer = 50;
    digitalWrite(10, LOW);
    checkSwitch(7);
    checkSwitch(2);
  }
  
  checkSwitch(3);
  checkSwitch(4);
  checkSwitch(5);
  checkSwitch(6);
  
  delay(20);
}
