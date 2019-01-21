package com.alex.digitMessenger.dataStruct;



public class CardState {
	private final String currentMessage;
	private final String lastMessageReceived;
	private final String currentAngle;
	private final String currentDspeed;
	
	public CardState(String message) {
		String[] attributes;
		attributes=message.split("-");
		currentMessage=attributes[0];
		lastMessageReceived=attributes[1];
		currentAngle=attributes[2];
		currentDspeed=attributes[3];
		
	}
	public String getCurrentMessage() {
		return currentMessage;
	}
	public String getLastMessageReceived() {
		return lastMessageReceived;
	}
	public String getCurrentAngle() {
		return currentAngle;
	}
	public String getCurrentDspeed() {
		return currentDspeed;
	}
	
	
}
