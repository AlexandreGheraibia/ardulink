 $('#formMessage').submit( function(){
           var param=$( "#message" ).val();
           sendGet(param,1);
           return false;
 });
 
 $('#formBase').submit( function(){
     var param=$( "#base" ).val();
     sendGet(param,0);
     return false;
});
 
 //sse sur event
 var sse;
 sse=$.SSE(adress+'/4digits/serv/sse', {
		 onMessage: function(e){ 
		       var i=1;
		       var obj=JSON.parse(e.data);
		       for(var k in obj){
		       	$("#state"+i).html(obj[k]);
					i++;
				   //console.log(k);
		       }
		     
		    }
	 });
sse.start();

