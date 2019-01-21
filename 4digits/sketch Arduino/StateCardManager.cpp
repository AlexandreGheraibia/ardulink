#include "StateCardManager.h"

StateCardManager::StateCardManager(HardwareSerial *serial,String crtMsg,String insMsg,float ang,long sp)
	:_serial(serial),stateChange(false),angle(ang),dSpeed(sp){
    sprintf(currentMsg,"%s",crtMsg.c_str());
    sprintf(instMsg,"%s",insMsg.c_str());
}
void StateCardManager::sendCurrentData() {
	stateChange=false;
  char  msg[200];
  sprintf(msg,"%s-%s-%s-%s",currentMsg,instMsg,String(angle).c_str(),String(dSpeed).c_str());
  _serial->print("alp://cevnt/");
  _serial->write(msg);
  _serial->print('\n');
  _serial->flush();
}

void StateCardManager::setCurrentMessage(String msg){
	sprintf(currentMsg,"%s",msg.c_str());
	stateChange=true;
};
void StateCardManager::setCurrentDisplaySpeed(long dSp){
   dSpeed=dSp;
   stateChange=true;
}
void StateCardManager:: setCurrentMotorAngle(float ang){
  angle=ang;
  stateChange=true;
};

void StateCardManager::setAutreMessage(String msg){ 
  sprintf(instMsg,"%s",msg.c_str());
	stateChange=true;
}

char * StateCardManager::getCurrentMsg() const{
	return currentMsg;
}

bool StateCardManager::isStateChange() const{
  return stateChange;
}
