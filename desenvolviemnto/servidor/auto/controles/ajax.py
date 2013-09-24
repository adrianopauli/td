from django.http import HttpResponse
from django.http import HttpRequest
from django.core import serializers
from controles.models import Controle
from django.shortcuts import render_to_response
from controles.protocolo import Protocolo

def sendIR(request):
	if request.is_ajax(): 
		data = request.GET['comando']
		node= request.GET['node']
		pr = Protocolo()
		message = "OK"		
		if not pr.sendIR(node,data):
			message = "ERROR"
		return HttpResponse(message,content_type = 'application/javascript; charset=utf8' )
	else :
		return render_to_response('controles/404.html')
