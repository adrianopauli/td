from django.conf.urls import patterns, include, url
from controles import *
from django.contrib import admin
admin.autodiscover()

urlpatterns = patterns('',
	url(r'^$','controles.views.index'),
	url(r'^admin/', include(admin.site.urls)),
	url(r'^controles/(?P<sala_id>\d+)$','controles.views.controles'),
	url(r'^controle/(?P<controle_id>\d+)/(?P<sala_id>\d+)$','controles.views.controle'),
	url(r'^salas/$','controles.views.salas'),
	url(r'^home/$','controles.home.index'),
	
	url(r'^ajax/ir/$','controles.ajax.sendIR'),
	url(r'^ajax/salas/$','controles.ajax.getSalass'),
)
