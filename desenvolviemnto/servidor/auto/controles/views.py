from django.template import Context, loader
from django.http import HttpResponse
from controles.models import Controle,Comando

def index(request):
	teste = 'teste muito loko'
	t = loader.get_template('controles/index.html')
	c = Context({
		'teste': teste,
    })
	return HttpResponse(t.render(c))
def controles(request):
	controles = Controle.objects.all()
	t = loader.get_template('controles/controles.html')
	c = Context({
		'controles':controles,
		})
	return HttpResponse(t.render(c))

def controle(request,controle_id):
	comandos = Comando.objects.all().filter(controle_id=controle_id)
	t = loader.get_template('controles/comandos.html')
	c = Context({
		'comandos':comandos,
		})
	return HttpResponse(t.render(c))