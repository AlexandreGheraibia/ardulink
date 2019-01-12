#include <Arduino.h>

    
class ArduLinkJssc
{
	public:
	ArduLinkJssc(HardwareSerial*);
	void eventSerialListener();
	void parseMessage();
	bool getMsgState() const;
	bool haveToResponds() const;
	void response();
	int  getType() const;
	void setCustomDeal(void (*fct)(String commande,String value));
  
	private:
	void flushMsg();
	void (*custDeal)(String commande,String value);
	int idPosition;
	bool msgRecognized;
	bool answerWait;
	String _inputString;         
  	boolean _stringComplete;
	HardwareSerial *_serial;
};
