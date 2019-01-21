package com.alex.digitMessenger.services;

import java.io.IOException;
import javax.inject.Singleton;
import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import org.apache.juneau.json.JsonSerializer;
import org.apache.juneau.serializer.SerializeException;
import org.ardulink.core.events.CustomEvent;
import org.ardulink.core.events.CustomListener;
import org.glassfish.jersey.media.sse.EventOutput;
import org.glassfish.jersey.media.sse.OutboundEvent;
import org.glassfish.jersey.media.sse.SseBroadcaster;
import org.glassfish.jersey.media.sse.SseFeature;

import com.alex.digitMessenger.dataStruct.CardState;;

@Singleton
@Path("/")
public class SseRessource {
	  private  Messenger msger=Messenger.getInstance();
	  private SseBroadcaster broadcaster = new SseBroadcaster();
	  public SseRessource() {
	  try {
			msger.addCustomListener(new CustomListener() {
	  			@Override
	  	  		public	void customEventReceived(CustomEvent e) {
	  				JsonSerializer jsonSerializer = JsonSerializer.DEFAULT_READABLE;
	  				
					try {
						String json;
						CardState pojo=new CardState(e.getMessage());
						json = jsonSerializer.serialize(pojo);
						System.out.println(broadcastMessage(json));
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
	  }
	  
	   public String broadcastMessage(String string) {
		
	        OutboundEvent.Builder eventBuilder = new OutboundEvent.Builder();
	        OutboundEvent event = eventBuilder.name("message")
	            .mediaType(MediaType.APPLICATION_JSON_TYPE)
	            .data(String.class, string)
	            .build();

	        broadcaster.broadcast(event);

	        return "Message '" + string + "' has been broadcast.";
	    }
	   	
	    @GET
	    @Path("sse")
	    @Produces(SseFeature.SERVER_SENT_EVENTS)
	    public EventOutput listenToBroadcast() {
	        final EventOutput eventOutput = new EventOutput();
	        this.broadcaster.add(eventOutput);
	        return eventOutput;
	   }
	    @POST
	    @Path("message/{message}")
	    public Response postM(@PathParam("message") String message){
	    	 return postMessage("m/"+message);
	    }
	    
	    @POST
	    @Path("base/{message}")
	    public Response postB(@PathParam("message") String message){
	         		
	           return postMessage("b/"+message);
	    }
	    
	   public Response postMessage(String message) {
            try {		
            	msger.sendMessage(message);
            	
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
            return Response.status(200).entity(message).build();
	    	
	    }
}
