from django.http import HttpResponse
from django.http import HttpRequest
from django.core import serializers
from controles.models import Controle
from django.utils import simplejson

def sendIR(request):
	if request.method == 'POST': 
		data = serializers.serialize('json',Controle.objects.all())
		return HttpResponse("Loko",content_type = 'application/javascript; charset=utf8' )
	else :
		data = serializers.serialize('json',Controle.objects.all())
		return HttpResponse(data,content_type = 'application/javascript; charset=utf8' )