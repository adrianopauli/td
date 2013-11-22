# coding: utf-8
from controles.models import *
from django.contrib import admin

class ComandosInlines(admin.TabularInline):
	model = Comando
	extra = 1

class ControleAdmin(admin.ModelAdmin):
	fieldsets=[
		('Dados do controle',{'fields':['description','modelo','marca']}),
	]
	list_display = ('description','modelo','marca')
	inlines = [ComandosInlines]
	list_filter = ('marca',)
	search_fields = ('description','modelo',)

class SalaAdmin(admin.ModelAdmin):
	filter_horizontal = ('controles','user',) 
	fieldsets=[
		('Dados da sala',{
			'fields':['bloco','description','NE',],
		}),
		('Adição de controntroles',{
			'fields':['controles',],
			'classes':('collapse',),
		}),
		('Controle de acesso dos usuários',{
			'fields':['user',],
			'classes':('collapse',),
		}),
	]
	list_filter = ('bloco','controles')
	search_fields = ('description',)

class BlocoAdmin(admin.ModelAdmin):
	fieldsets=[
		('Dados do bloco',{
			'fields':['description','ip']},
		),	
	]
	list_display = ('description','ip')
	search_fields = ('description','ip')

class MarcaAdmin(admin.ModelAdmin):
	fieldsets=[
		('Dados da marca',
			{'fields':['description',],},
		),		
	]
	search_fields = ('description',)

class InteruptorAdmin(admin.ModelAdmin):
	fieldsets=[
		('Dados do interuptor',
			{'fields':['description','porta','status',],},
		),		
	]
	list_display = ('description','porta','status',)
	search_fields = ('description',)

class RotinaAdmin(admin.ModelAdmin):
	fieldsets=[
		('Dados da Rotina',
			{'fields':['description',],},
		),		
		('Regras para data',
			{'fields':['hora','data','semana','horaInicio','horaFim','allData'],},
		),
		('Regras para sensores',
			{'fields':['teperatura','umidade'],},
		),	
		('Salas',{
			'fields':['salas',],
			'classes':('collapse',),
		}),
		('Comandos',{
			'fields':['comandos',],
			'classes':('collapse',),
		}),
		('Interuptor',{
			'fields':['interuptores',],
			'classes':('collapse',),
		}),
	]
	list_display = ('description','hora','data',)
	search_fields = ('description',)

admin.site.register(Bloco,BlocoAdmin)
admin.site.register(Sala,SalaAdmin)
admin.site.register(Marca,MarcaAdmin)
admin.site.register(Controle,ControleAdmin)
admin.site.register(Interuptor,InteruptorAdmin)
admin.site.register(Rotina,RotinaAdmin)
