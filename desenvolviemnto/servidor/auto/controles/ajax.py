from django.http import HttpResponse
from django.http import HttpRequest
from django.core import serializers
from controles.models import Controle
from django.utils import simplejson
from django.shortcuts import render_to_response
from comunicacao import rs485

def sendIR(request):
	if request.is_ajax(): 
		data = request.GET['comando']
		rs = rs485()
		return HttpResponse(rs.sendComand(data),content_type = 'application/javascript; charset=utf8' )
	else :
		return render_to_response('controles/404.html')