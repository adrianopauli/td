# coding: utf-8
from django.template import Context, loader
from django.template.response import TemplateResponse
from django.http import HttpResponse
from controles.models import Controle,Comando,Sala,Bloco,Interuptor
from controles.protocolo import Protocolo,Weather 
from django.contrib.sites.models import get_current_site
from django.contrib.auth.decorators import login_required

@login_required
def index(request):
	blocos = Bloco.objects.all()
	t = loader.get_template('controles/index.html')
	c = Context({
		'blocos': blocos,
		'user':request.user,
    	})
	return TemplateResponse(request,t,c)

@login_required
def salas(request):
	#bloco = Bloco.objects.filter(ip=request.META['REMOTE_ADDR'])
	bloco = Bloco.objects.filter(ip=request.META['SERVER_NAME'])
	if not bloco.exists():
		t = loader.get_template('controles/error.html')
		c = Context({
			'message':"O boco não existe",
			'user':request.user,
		})
		return TemplateResponse(request,t,c)
	else:
		salas = Sala.objects.all().filter(bloco_id=bloco[0].id).filter(user = request.user)
		t = loader.get_template('controles/salas.html')
		c = Context({
			'salas':salas,
			'user':request.user,
		})
		return TemplateResponse(request,t,c)
@login_required
def controles(request,sala_id):
	salas = Sala.objects.filter(id=sala_id).filter(user = request.user)
	if salas :
		sala = salas[0]
		pr = Protocolo()
		weather = pr.sendWeather(str(sala.NE))
		controles = Controle.objects.all().filter(sala=sala)
		interuptores = Interuptor.objects.all().filter(sala=sala)
		for controle in controles:
			comandos = Comando.objects.all().filter(controle=controle)
			controle.setComandos(comandos)
		t = loader.get_template('controles/controles.html')
		c = Context({
			'controles':controles,
			'sala':sala,
			'weather':weather,
			'user':request.user,
			'interuptores':interuptores,
		})
		return TemplateResponse(request,t,c)
	else:
		t = loader.get_template('controles/error.html')
		c = Context({
			'message': 'Acesso negado',
			'user':request.user,
	    	})
		return TemplateResponse(request,t,c)
@login_required
def controle(request,controle_id,sala_id):
	sala = Sala.objects.get(id=sala_id)
	controle = Controle.objects.get(id=controle_id)
	comandos = Comando.objects.all().filter(controle_id=controle_id)
	t = loader.get_template('controles/comandos.html')
	c = Context({
		'comandos':comandos,
		'sala':sala,
		'controle':controle,
		'user':request.user,
	})
	return TemplateResponse(request,t,c)
