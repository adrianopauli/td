function sendComand(comando,node){
	 $.ajax({
        url: "/ajax/ir/",
        dataType: "text",
        type: 'POST',
        data:{'comando':comando,'node':node},
	success: function(data) {
		messages('Comando eviado com sucesso','ok');
        },
        error: function(data) {
		messages('Não foi possivel enviar o comando!','error');
        },
        
    });
}
function messages(message,type){
	if(type == 'ok'){
		sendHTML('#message','<div id="message_alert" class="alert alert-success">'+message+'</div>');
	}else if(type == 'info'){
		sendHTML('#message','<div id="message_alert" class="alert alert-info">'+message+'</div>');		
	}else if(type == 'error'){
		sendHTML('#message','<div id="message_alert" class="alert alert-warning">'+message+'</div>');
	}
	setTimeout('fade_out()',2000);
}

function sendHTML(id,html){
	$(id).html(html);
}
function  fade_out(){
	$('#message_alert').fadeOut(500);	

}

