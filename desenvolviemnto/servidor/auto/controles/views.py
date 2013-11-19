# coding: utf-8
from django.template import Context, loader
from django.http import HttpResponse
from controles.models import Controle,Comando,Sala,Bloco
from controles.protocolo import Procolo

def index(request):
	teste = 'teste muito loko'
	t = loader.get_template('controles/index.html')
	c = Context({
		'teste': teste,
    })
	return HttpResponse(t.render(c))

def salas(request):
	bloco = Bloco.objects.filter(ip=request.META['SERVER_NAME'])
	if not bloco.exists():
		t = loader.get_template('controles/error.html')
		c = Context({
			'message':"O boco não existe",
		})
		return HttpResponse(t.render(c))
	else:
		salas = Sala.objects.all().filter(bloco_id=bloco[0].id)
		t = loader.get_template('controles/salas.html')
		c = Context({
			'salas':salas,
		})
		return HttpResponse(t.render(c))

def controles(request,sala_id):
	sala = Sala.objects.get(id=sala_id)
	controles = Controle.objects.all().filter(sala=sala)
	t = loader.get_template('controles/controles.html')
	c = Context({
		'controles':controles,
		'sala':sala,
	})
	return HttpResponse(t.render(c))

def controle(request,controle_id,sala_id):
	sala = Sala.objects.get(id=sala_id)
	comandos = Comando.objects.all().filter(controle_id=controle_id)
	t = loader.get_template('controles/comandos.html')
	c = Context({
		'comandos':comandos,
		'sala':sala,
	})
	return HttpResponse(t.render(c))

def temperatura(request):
	bloco = Bloco.objects.filter(ip=request.META['SERVER_NAME'])
	if not bloco.exists():
		t = loader.get_template('controles/error.html')
		c = Context({
			'message':"O boco não existe",
		})
		return HttpResponse(t.render(c))
	else:
		salas = Sala.objects.all().filter(bloco_id=bloco[0].id)
		pr = Procolo()
		for sala in salas:
			print(pr.sendWeather(sala.NE))
		t = loader.get_template('controles/temperatura.html')
		c = Context({
			'salas':salas,
		})
		return HttpResponse(t.render(c))