/* ArduLinkJssc Library
 *
 * Copyright 2017 Dean Reading
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "./lib/ArduLinkJssc.h"

 

ArduLinkJssc::ArduLinkJssc(HardwareSerial *serial):_serial(serial),idPosition(-1),msgRecognized(false),answerWait(false),_inputString(""),_stringComplete(false) {
  _serial->begin(115200);
	_serial->print("alp://rply/");//F pour passer les variable en ram et non en sd ram  
	_serial->print("ok?id=0");
	_serial->print("\n"); // End of Message
}

bool ArduLinkJssc::getMsgState() const{
	return _stringComplete;
}

void ArduLinkJssc::eventSerialListener(){
 while (_serial->available() && !_stringComplete) {
    // get the new byte:
    char inChar = (char)_serial->read();
    // add it to the inputString:
    _inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      _stringComplete = true;
    }
  }
}

bool ArduLinkJssc::haveToResponds() const{
	return answerWait;
}

void ArduLinkJssc::setCustomDeal(void (*fct)(String commande,String value)){
	this->custDeal=fct;
}

void ArduLinkJssc::parseMessage(){
	if(_inputString.startsWith(F("alp://"))) {
		// OK is a message I know (this is general code you can reuse)
       msgRecognized = true;
      if(_inputString.substring(6,10) == F("cust")) { // Custom Message
        // here you can write your own code.
        int separatorPosition = _inputString.indexOf('/', 11 );
        int messageIdPosition = _inputString.indexOf('?', 11 );
        String customId = _inputString.substring(11,separatorPosition);
        String value = _inputString.substring(separatorPosition + 1, messageIdPosition);
        if(customId.length()!=0) {
			    this->custDeal(customId,value);
        } else {
          msgRecognized = false;
          // this sketch doesn't know other messages in this case command is ko (not ok)
        }
      } else {
        msgRecognized = false;
        // this sketch doesn't know other messages in this case command is ko (not ok)
      }
	  idPosition=_inputString.indexOf("?id=");
	  answerWait=idPosition!=-1;
      flushMsg();
	}
 
}

void ArduLinkJssc::flushMsg(){
	 // clear the string:
	if(haveToResponds()){
    response();
  }
  _inputString = "";
  _stringComplete = false;
}


void ArduLinkJssc::response(){
	 if(answerWait) {
        String id = _inputString.substring(idPosition + 4);
        // print the reply
        _serial->print(F("alp://rply/"));
        if(msgRecognized) { // this sketch doesn't know other messages in this case command is ko (not ok)
          _serial->print(F("ok?id="));
        } else {
          _serial->print(F("ko?id="));
        }
		    _serial->print(id);
        _serial->write(255); // End of Message
        _serial->flush();
      }
}


   
  
