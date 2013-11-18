from controles.models import *
from django.contrib import admin

class ComandosInlines(admin.TabularInline):
	model = Comando
	extra = 1

class ControleAdmin(admin.ModelAdmin):
	inlines = [ComandosInlines]

#admin.site.register(Bloco)
admin.site.register(Sala)
admin.site.register(Marca)
admin.site.register(Controle,ControleAdmin)