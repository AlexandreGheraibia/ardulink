#include <Arduino.h>

class StateCardManager{
	public:
	StateCardManager(HardwareSerial *,String,String,float,long);
	void sendCurrentData();
	void setCurrentMessage(String);
  void setCurrentMotorAngle(float);
  void setCurrentDisplaySpeed(long);
	void setAutreMessage(String);
	char* getCurrentMsg() const;
  bool isStateChange() const;
	private:
	HardwareSerial * _serial=NULL;
  float angle=0.0f;
  long dSpeed=0;
	char currentMsg[50];
	char instMsg[50];
	bool stateChange=false;
};
