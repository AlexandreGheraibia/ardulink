package com.alex.digitMessenger.app;
import java.io.IOException;

import org.apache.juneau.json.JsonSerializer;
import org.apache.juneau.serializer.SerializeException;
import org.ardulink.core.events.CustomEvent;
import org.ardulink.core.events.CustomListener;

import com.alex.digitMessenger.dataStruct.CardState;
import com.alex.digitMessenger.services.Messenger;

public class Main{
	static private  Messenger msger=Messenger.getInstance();
	
	public static void main(String[] args) throws InterruptedException {
		// TODO Auto-generated method stub	
		
		try {
			msger.addCustomListener(new CustomListener() {
	  			@Override
	  	  		public	void customEventReceived(CustomEvent e) {
	  				JsonSerializer jsonSerializer = JsonSerializer.DEFAULT_READABLE;
	  				
					try {
						String json;
						CardState pojo=new CardState(e.getMessage());
						json = jsonSerializer.serialize(pojo);
						System.out.println(json);
		  				System.out.println("cust "+e.getMessage());
					} catch (SerializeException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
	  			
	  	  			}
	  	  		});
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		while(true) {
		Thread.sleep(1000);	
		
		}
	}
}
