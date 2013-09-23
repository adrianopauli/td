function sendComand(comando,node){
	 $.ajax({
        url: "/ajax/ir/",
        dataType: "text",
        data:{'comando':comando,'node':node},
        error: function(XMLHttpRequest, textStatus, errorThrown) {
		$('#message').html('<h3 id="message_alert">ERROR</h3>');
		setTimeout('fade_out()',2000);
        },
        success: function(data, textStatus, XMLHttpRequest) {
		$('#message').html('<h3 id="message_alert">Comando Enviado</h3>');
		setTimeout('fade_out()',2000);
        }
    });
}
function  fade_out(){
	$('#message_alert').fadeOut(500);	
}
