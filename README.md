Introducción
============

Este é o repositorio Git para a interface Arduino <--> WebFront que vamos a montar.

Python
======

A idea de usar [Python][1] é pola súa sinxeleza respecto a C (coma o ano pasado)
e debido ao pouco tempo que temos para programar, para non ter que preocuparnos da xestión
da memoria a baixo nivel e tan só xeralizar a xestión das tarefas.

Python ten dúas bibliotecas (threading e multiprocessing) que nos poden axudar a traballar
en paralelo cos tes arduinos.

Tal vez sexa mellor threading porque mantén un mutex do código en python, co que xa nos aforra
ter que escribir código con seccións críticas tamén.

Isto é debido ao _[Global Interpreter Lock][2]_.

[1]: http://www.python.org
[2]: http://docs.python.org/glossary.html#term-global-interpreter-lock

