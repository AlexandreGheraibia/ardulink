package com.alex.digitMessenger.services;


import org.ardulink.core.Link;
import org.ardulink.core.convenience.Links;
import org.ardulink.core.events.CustomListener;

//r�f�rence
//http://thecodersbreakfast.net/index.php?post/2008/02/25/26-de-la-bonne-implementation-du-singleton-en-java
import java.io.IOException;
//creer un singleton
public class Messenger {//singleton
    
    private Link link=null;
    private boolean actifListener=false;
    private Messenger() {
    	 if(this.link==null) {
    		this.link = Links.getDefault();
    	 }
    }
    /*
	technique de classe holder
	la classe interne ne sera charger en mémoire qu'au premier appel de
	cette classe. par getInstance() et remplira les champs static
	 
    */
    private static class SingletonHolder
    {       
        /** Instance unique non préinitialisée */
    	
        private final static Messenger ourInstance = new Messenger();
    	
    }
    public static Messenger getInstance()  {
    	
    	return SingletonHolder.ourInstance;
    }
    
    public  void sendMessage(String message) throws IOException{
    	String msg=message; 
    	if(link!=null) {
    	   link.sendCustomMessage(msg);
    	}//launch an exception

    }
  
    public void addCustomListener(final CustomListener cl) throws IOException{
    	if(!actifListener) {
    		link.addCustomListener(cl);
    	}
    }
   
}
