
#include <Servo.h>

#include "./lib/ArduLinkJssc.h"
#include "StateCardManager.h"
#include "SevSeg.h"
/***************************** digit display***********************************************/
SevSeg sevseg; //Initiate a seven segment controller object



#define MAX_MESSAGE_SIZE 60
#define MAX_BASE_SIZE 30
#define MAX_NUMBER_STRINGS 4
#define MAX_STRING_SIZE 20

int patternChangeTime=400;
unsigned long timer = millis() - patternChangeTime;
char base[MAX_BASE_SIZE ];
char message[MAX_MESSAGE_SIZE];
char oldMessage[MAX_MESSAGE_SIZE];

/*****************************************************************************************/

const int servoPin=9;
const int buttonPin=A1;
const int minAngle=82,maxAngle=127;

int currentPos=0,oldPos=0;
bool inter=false;
bool reverse=false;
bool activated=false;
bool mustMove=false;
bool oldRev=false;

float position = 82;
float incremPandaPosition=0;

Servo monServomoteur;
StateCardManager *stateCard;
ArduLinkJssc* ardJssc;


void setup() {
  ardJssc= new ArduLinkJssc(&Serial);
  stateCard=new StateCardManager(&Serial,"message courant","message",position,patternChangeTime);

  /**************************************digit display******************************************/
  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8,A0, 10, 11, 12, 13};
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(90);
  adapteMessage((char *)&message,stateCard->getCurrentMsg());
  strcpy(oldMessage,message);
  ardJssc->setCustomDeal(&customDeal);
}

void changeDispState(bool rev,int speed,int size){
     if(inter&&!mustMove){
              inter=false;
              currentPos=oldPos;
              strcpy(message,oldMessage);        
              reverse=oldRev;
              if(reverse){
                patternChangeTime=90;               
              }
              else{
                patternChangeTime=400;               
              }
      }
      else{
            currentPos=size;
            reverse=rev;
            patternChangeTime=speed;
            
      }
       stateCard->setCurrentDisplaySpeed(patternChangeTime);
}

void displayUpdate(int incr){
    sevseg.setChars(&message[currentPos]);
    timer = millis();
    currentPos+=incr;
}

//clockwise
void displayLtoR(char message[60]){
   if(currentPos>-1){
       if (millis() > (timer + patternChangeTime)) {
                displayUpdate(-1);
               if(mustMove){
                 pandaMove();
                  if(currentPos==0){
                    position = minAngle;
                    monServomoteur.detach();
                    mustMove=false;
                   }
              }
       }
       sevseg.refreshDisplay(); // Must run repeatedly
      
   }else{
       changeDispState(false,400,0);
   }
}
//counterclockwise
void displayRtoL(char message[60]){
   if(currentPos<strlen(message)){
       if (millis() > (timer + patternChangeTime)) {
           displayUpdate(1);
           if(mustMove){
             float tailleTotal=strlen(message);
             incremPandaPosition=45.0/tailleTotal;//30 degres d'intervalle de deplacement
             pandaMove();
          }  
       }
       sevseg.refreshDisplay(); // Must run repeatedly
    }else{
          if(mustMove){
            incremPandaPosition=-incremPandaPosition;
          }
         changeDispState(true,90,strlen(message));
   }
}

void pandaMove(){ 
  if(mustMove){ 
    if(!monServomoteur.attached()){
       monServomoteur.attach(servoPin,minAngle,maxAngle);
       monServomoteur.write(position);
    }else{
       position=position+incremPandaPosition;
       stateCard->setCurrentMotorAngle(position);
       monServomoteur.write(position);
      }
  }
}

void serialEvent() {
  ardJssc-> eventSerialListener();
}

void customDeal(String command,String value){
	if(command.equals("b")){
				oldPos=0;
				stateCard->setCurrentMessage(value);
		  	stateCard->setAutreMessage(value);
  			adapteMessage((char*)&oldMessage,value);
  			strcpy(message,oldMessage);
  		  currentPos=0;
  			oldRev=false;
  			inter=true;
  			mustMove=true;
			}
  else if(command.equals("m")){
      				oldPos=currentPos;
      				stateCard->setAutreMessage(value);
          		strcpy(oldMessage,message);
          		currentPos=0;
          		oldRev=reverse;
          		inter=true;
          		mustMove=true;
      		    adapteMessage((char*)&message,value);
    }
}
void adapteMessage(char * base,String s){
   int j;
   for(j=0;j<4;j++){
      base[j]=' ';
   }
   for(int i=0 ;i<=s.length(); i++){
    if(s[i]=='m'||s[i]=='M'){
      base[j]='m';
      base[j+1]='&';
      j++; 
    }else if(s[i]=='w'||s[i]=='W'){
        base[j]='w';
        base[j+1]='$';
        j++; 
    }else{
      base[j]=s[i];      
    }
    j++;
  }
  base[j]=' ';
  base[j+1]='\0'; 
}

void webEntry(){
 if (ardJssc->getMsgState()&&!inter) {
	ardJssc->parseMessage();
 }
}

void loop() {
    webEntry();
    if(!reverse){
      displayRtoL(message);
    }
    else{
      displayLtoR(message);
    }
    if(stateCard->isStateChange()){
      stateCard->sendCurrentData();
    }
}
