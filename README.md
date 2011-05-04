Introducción
============

Este é o repositorio Git para a interface Arduino <--> WebFront que vamos a montar.

Python
======

A idea de usar [Python][1] é pola súa sinxeleza respecto a C (coma o ano
pasado) e debido ao pouco tempo que temos para programar, para non ter que
preocuparnos da xestión da memoria a baixo nivel e tan só xeralizar a xestión
das tarefas.

Python ten dúas bibliotecas (threading e multiprocessing) que nos poden axudar
a traballar en paralelo cos tes arduinos.

Tal vez sexa mellor threading porque mantén un mutex do código en python, co
que xa nos aforra ter que escribir código con seccións críticas tamén.

Isto é debido ao _[Global Interpreter Lock][2]_.

[1]: http://www.python.org
[2]: http://docs.python.org/glossary.html#term-global-interpreter-lock

Funcionamiento dos controladores
================================

Os controladores non poden esperar que cada acción de put que fagan sobre o
arduino lles devolva un dato no momento que o esperan, sobre module.recv_msg()
senón que poden recibir outros datos (irrelevantes) ata que o dato que precisan
é enviado polo procesamento secuencial na cola de recepción de datos do porto
serie.

Por tanto, se unha rutina require agardar polo dato de volta do arduino para
unha entrada determinada aconséllase a utilización de semáforos/Locks para a
xestión do bloqueo das funcións dentro de cada controlador.

Non podemos facer funcións que agarden por datos do arduino de forma directa
porque descoñecemos se outros procesos puideron haber pedido tamén datos ao
mesmo arduino entre peticións nosas.

En calquera xeito, para coñecer o estado dun arduino pódese consultar ao
ArduinoHandler (aínda non, pero esa sería a idea).

