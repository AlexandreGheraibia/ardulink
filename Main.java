import org.ardulink.core.Link;
import org.ardulink.core.events.CustomEvent;
import org.ardulink.core.events.CustomListener;


public class Main{
//receive message from the Arduino Card    
static private CustomListener eventCustListener() {
  return new CustomListener() {
	  @Override
	  public void customEventReceived(CustomEvent e) {
		System.out.println(e.getMessage());
	  }
  }
}

public static void main(String[] args) throws InterruptedException {
    Link link=Links.getDefault();
    link.addCustomListener(eventCustListener);
    if(link!=null) {
    //send message to the Arduino Card    
    link.sendCustomMessage("cmd/value");
    }
  }
}
