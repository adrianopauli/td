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
		return self.modelo

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
	def __unicode__(self):
		return self.description

	
class Sensor(models.Model):
	sala = models.ForeignKey(Sala)
	temperatura = models.DecimalField(max_digits=2,decimal_places=2)
	umidade = models.DecimalField(max_digits=2,decimal_places=2)
	data = models.DateTimeField();
