function sendComand(comando,node){
	 $.ajax({
        url: "/ajax/ir/",
        dataType: "text",
        data:{'comando':comando,'node':node},
        error: function(XMLHttpRequest, textStatus, errorThrown) {
		$('#message').html('<div id="message_alert" class="alert alert-warning">ERROR</div>');
		setTimeout('fade_out()',2000);
        },
        success: function(data, textStatus, XMLHttpRequest) {
		$('#message').html('<div id="message_alert" class="alert alert-info">Comando Enviado</div>');
		setTimeout('fade_out()',2000);
        }
    });
}

function  fade_out(){
	$('#message_alert').fadeOut(500);	
}
