function sendComand(comando,node){
	 $.ajax({
        url: "/ajax/ir/",
        dataType: "text",
        data:{'comando':comando,'node':node},
        error: function(XMLHttpRequest, textStatus, errorThrown) {
		messages('Não foi possivel enviar o comando!','error');
        },
        success: function(data, textStatus, XMLHttpRequest) {
		messages('Comando eviado comsucesso','ok');
        }
    });
}

function  fade_out(){
	$('#message_alert').fadeOut(500);	
}

function messages(message,type){
	var element  = $('#message');
	if(type == 'ok'){
		element.html('<div id="message_alert" class="alert alert-success">'+message+'</div>');
	}else if(type == 'info'){
		element.html('<div id="message_alert" class="alert alert-info">'+message+'</div>');		
	}else{
		element.html('<div id="message_alert" class="alert alert-warning">'+message+'</div>');
	}
	setTimeout('fade_out()',2000);
}

function getSalas(id,token){
	$.ajax({
        url: "/ajax/salas/",
        dataType: "text",
        data:{'bloco':id,'csrftoken':toke},
        error: function(XMLHttpRequest, textStatus, errorThrown) {
		messages('Não foi possivel enviar o comando!','error');
        },
        success: function(data, textStatus, XMLHttpRequest) {
		messages('Comando eviado comsucesso',data);
        }
    });
}
