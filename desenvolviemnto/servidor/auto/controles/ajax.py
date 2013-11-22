from django.http import HttpResponse
from django.http import HttpRequest
from django.core import serializers
from controles.models import Controle,Bloco,Sala
from django.shortcuts import render_to_response
from controles.protocolo import Protocolo
from django.views.decorators.csrf import csrf_exempt, csrf_protect

@csrf_exempt
def sendIR(request):
	if request.method == 'POST': 
		data = request.POST['comando']
		node= request.POST['node']
		pr = Protocolo()
		message = "OK"		
		if not pr.sendIR(node,data):
			message = "ERROR"
		return HttpResponse(message,content_type = 'application/javascript; charset=utf8' )
	else :
		return render_to_response('controles/404.html')
