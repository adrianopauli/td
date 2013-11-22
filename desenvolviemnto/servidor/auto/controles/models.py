# coding: utf-8
from django.db import models
from django.contrib.auth.models import User

class Bloco(models.Model):
	description = models.CharField("Descrição",max_length=200)
	ip = models.IPAddressField(blank=False)
	def __unicode__(self):
		return self.description
		
class Marca(models.Model):
	description = models.CharField("Descrição",max_length=200)
	def __unicode__(self):
		return self.description

class Controle(models.Model):
	marca = models.ForeignKey(Marca)
	modelo = models.CharField(max_length=200)
	description = models.CharField("Descrição",max_length=200)
	
	def __unicode__(self):
		return self.modelo+' - '+self.description+' - '+self.marca.description
	def setComandos(self,comandos):
		self.comandos = comandos

	def getComandos(seld):
		self.comandos
		
class Comando(models.Model):
	controle = models.ForeignKey(Controle)
	description = models.CharField("Descrição",max_length=200)
	comando = models.CharField(max_length=200)

	def __unicode__(self):
		return self.description

class Sala(models.Model):
	bloco = models.ForeignKey(Bloco)
	description = models.CharField("Descrição",max_length=200)
	NE = models.PositiveIntegerField()
	controles = models.ManyToManyField(Controle)
	user = models.ManyToManyField(User)
	issensor = models.BooleanField("Sensores instalados")

	def __unicode__(self):
		return self.description

class Sensor(models.Model):
	sala = models.ForeignKey(Sala)
	temperatura = models.DecimalField(max_digits=2,decimal_places=2)
	umidade = models.DecimalField(max_digits=2,decimal_places=2)
	data = models.DateTimeField();

class Interuptor(models.Model):
	description = models.CharField("Descrição",max_length=200)
	porta = models.PositiveIntegerField()
	status = models.BooleanField("Situação")
	sala = models.ForeignKey(Sala)

	def __unicode__(self):
		return self.description

class Rotina(models.Model):
	description = models.CharField("Descrição",max_length=200)
	comandos = models.ManyToManyField(Comando)
	salas = models.ManyToManyField(Sala)
	data = models.DateField(blank=True)
	allData = models.BooleanField(blank=True)
	semana = models.CharField(max_length=10, choices=(('seg', 'Segunda'), ('ter', 'Terça')))
	hora = models.DateTimeField(blank=True)
	horaInicio = models.DateTimeField(blank=True)
	horaFim = models.DateTimeField(blank=True)
	temperatura = models.DecimalField(max_digits=2,decimal_places=2,blank=True)
	umidade = models.DecimalField(max_digits=2,decimal_places=2,blank=True)
