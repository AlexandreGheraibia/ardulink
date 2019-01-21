var adress="http://localhost:8080";
function sendGet(param,type){
                var self=this;
        		var data = {};
        		var xmlhttp = new XMLHttpRequest();
            	var request=adress+"/4digits/serv/base/"+param;
        		if(type==1){
        			request= adress+"/4digits/serv/message/"+param;	
        		}
        		
				xmlhttp.open("POST", request, true);
                var div=$("#tableId");

        		xmlhttp.onreadystatechange = function () {
        		  if (xmlhttp.readyState == 4 ){
                     div.html("envoyé");
        		  }

        		};
                xmlhttp.send(xmlhttp);
 }
 




