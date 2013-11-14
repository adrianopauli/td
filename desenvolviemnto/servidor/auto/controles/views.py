from django.template import Context, loader
from django.http import HttpResponse
from controles.models import Controle

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