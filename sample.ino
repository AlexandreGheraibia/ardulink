#include "./lib/ArduLinkJssc.h"
ArduLinkJssc* ardJssc;


void setup() {
  ardJssc= new ArduLinkJssc(&Serial);
  ardJssc->setCustomDeal(&customDeal);
}

//call back
//receive command from java app
void customDeal(String command,String value){
	if(command.indexOf("b")>0){//command identified by b
				//do something with the value
        
	}    
}

//event listener of serial port
void serialEvent() {
  ardJssc-> eventSerialListener();
}


void loop() {
 if (ardJssc->getMsgState()) {
    ardJssc->parseMessage();//parseMessage function call the callback define in setup
 }
 customSend("custom message to the java app")
}
