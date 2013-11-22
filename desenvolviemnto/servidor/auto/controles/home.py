# coding: utf-8
from django.template import Context, loader
from django.template.response import TemplateResponse
from django.http import HttpResponse
from controles.models import Controle,Comando,Sala,Bloco
from controles.protocolo import Protocolo,Weather 
from django.contrib.sites.models import get_current_site
from django.contrib.auth.decorators import login_required

@login_required
def index(request):
	
	blocos = Bloco.objects.all()
	t = loader.get_template('controles/home.html')
	c = Context({
		'blocos': blocos,
		'user':request.user,
		'token':request.COOKIES['csrftoken']
    	})
	return TemplateResponse(request,t,c)
