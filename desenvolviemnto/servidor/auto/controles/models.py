from django.db import models

class Bloco(models.Model):
	description = models.CharField(max_length=200)

	def __unicode__(self):
		return self.description

class Sala(models.Model):
	bloco = models.ForeignKey(Bloco)
	description = models.CharField(max_length=200)
	numeroDoEquipamento = models.IntegerField()

	def __unicode__(self):
		return self.description

class TipoControle(models.Model):
	description = models.CharField(max_length=200)
	numeroProtocolo = models.IntegerField()

	def __unicode__(self):
		return self.description

class Controle(models.Model):
	sala = models.ForeignKey(Sala)
	tipo = models.ForeignKey(TipoControle)
	description = models.CharField(max_length=200)
	
	def __unicode__(self):
		return self.description

class Comando(models.Model):
	controle = models.ForeignKey(Controle)
	description = models.CharField(max_length=200)
	comando = models.CharField(max_length=1000)

	def __unicode__(self):
		return self.description