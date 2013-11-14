from django.conf.urls import patterns, include, url
from controles import *
from django.contrib import admin
admin.autodiscover()

urlpatterns = patterns('',
    url(r'^admin/', include(admin.site.urls)),
    url(r'^teste/$','controles.views.index'),
    url(r'^controles/$','controles.views.controles'),
)
