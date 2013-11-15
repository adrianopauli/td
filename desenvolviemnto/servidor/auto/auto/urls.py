from django.conf.urls import patterns, include, url
from controles import *
from django.contrib import admin
admin.autodiscover()

urlpatterns = patterns('',
	url(r'^$','controles.views.index'),
    url(r'^admin/', include(admin.site.urls)),
    url(r'^controles/$','controles.views.controles'),
    url(r'^ajax/ir/$','controles.ajax.sendIR'),
    url(r'^controle/(?P<controle_id>\d+)$','controles.views.controle'),
)
