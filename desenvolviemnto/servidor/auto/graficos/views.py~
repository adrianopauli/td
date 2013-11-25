# coding: utf-8
from django.template import Context, loader
from django.template.response import TemplateResponse
from controles.models import Controle,Comando,Sala,Bloco,Interuptor
from controles.protocolo import Protocolo,Weather 
from django.contrib.sites.models import get_current_site
from django.contrib.auth.decorators import login_required

@login_required
def index(request):
	blocos = Bloco.objects.all()
	t = loader.get_template('graficos/home.html')
	c = Context({
		'title': 'grafico de temperatura',
		'user':request.user,
    	})
	return TemplateResponse(request,t,c)
def index(request):
    
