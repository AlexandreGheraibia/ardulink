#include <Arduino.h>

    
class ArduLinkJssc
{
	public:
	
	ArduLinkJssc(HardwareSerial*);
	void eventSerialListener();
	void parseMessage();
	void setCustomDeal(void (*fct)(String commande,String value));
	void customSend(String message);
	bool getMsgState() const;
	virtual void customDeal(String commande,String value);
	
	private:
 
	bool haveToResponds() const;
	void flushMsg();
	void response();
	void (*custDeal)(String commande,String value);
	int idPosition;
	bool msgRecognized;
	bool answerWait;
	String _inputString;         
 	boolean _stringComplete;
  	HardwareSerial *_serial;
};
