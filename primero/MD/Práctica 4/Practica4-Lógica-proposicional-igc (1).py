# -*- coding: utf-8 -*-
"""
"""

##PRÁCTICA 4: LÓGICA PROPOSICIONAL 2024-2025

from sympy import *

#OPERACIONES LÓGICAS

x=1
y=0

#AND

x & y

And(x,y)

#OR

x | y

Or (x,y)

#NOT

~x

#El comportamiento en Python puede ser algo distinto del esperado con respecto a la inversión a nivel de bits.
#Solo es preciso interiorizar que este simbolo se utilizará como negación más adelante.

x=0
not(x)

# operación de negación lógica.La negación lógica invierte el valor booleano actual. 
#Si x=True, Not(x) será False, y si x=False, Not(x) será True

#CONDICIONAL

x >> y 

Implies(True, False)
#operación de implicación lógica. Si la expresión A es verdadera, entonces la expresión B debe ser falsa

Implies(1,1)
Implies(1,0)
Implies(0,1)
Implies(0,0)

Implies(True,True)
Implies(True,False)
Implies(False,True)
Implies(False,False)

#BICONDICIONAL

Equivalent(x, y) #x=True e y=False
#doble implicación, si x es igual y será verdadero

Equivalent(1,1)
Equivalent(1,0)
Equivalent(0,1)
Equivalent(0,0)

#XOR
#Disyuncion exclusiva o XOR: se interpreta como “x o y pero no ambas” en bits

Xor(x, y) #x=5 e y=2

Xor(1,1)
Xor(1,0)
Xor(0,1)
Xor(0,0)

#NAND
#se interpreta como “no X e Y a la vez”, solo falso si (1,1)

Nand(x, y)#x=1 e y=1

Nand(1,1)
Nand(1,0)
Nand(0,1)
Nand(0,0)

#NOR
#se interpreta como “ni X ni Y”, solo verdadero si (0,0)

Nor(x, y)

Nor(1,1)
Nor(1,0)
Nor(0,1)
Nor(0,0)

# sustituir valores de verdad
#Definimos dos variables simbólicas, serán incógnitas.

x, y = symbols('x y')

#Después de calcular el resultado de la operación de AND, se realiza una sustitución de 
#variables. En este caso, se reemplaza x por True y y por True.

(y & x).subs({x: True, y: True})

#Aquí, en lugar de asignar valor y luego aplicar and, lo que se hace es definir como incógnitas,
#introducir el and y al final sustituir los valores


# SIMPLIFICACIÓN. LEYES LÓGICAS

from sympy.logic import simplify_logic 
from sympy.abc import x, y, z

#Esto último es lo mismo que 
#x,y,z = symbols('x,y,z') #Estamos definiendo variables simbólicas (incógnitas)

b = (~x & ~y & ~z) | ( ~x & ~y & z)
simplify_logic(b) #simplifica expresiones lógicas o booleanas

#simplify_logic(b) simplificará esta expresión lógica y devolverá una versión más 
#simplificada, manteniendo la equivalencia lógica.

#Para ver en consola los símbolos en formato.

p = (x | y) & ~ z
pprint(p) 

#pprint=muestra los simbolos de logica proposicional (pprint es pretty-print)

#Más ejemplos sobre simplificación

q = x | (x & y)
simplify_logic(q)
simplify(q) # otra forma de hacer uan simplificación logica

# Sustituir valores de verdad
p.xreplace({x:True})

#Es decir como x=True se cumple el parentesis y solo queda ~z. Si x=False, no se cumple
# el parentesis por tanto y & ~z

p.xreplace({x:False})

# CONSISTENCIA DE PREMISAS

#como comprobar la validez de una inferencia logica,asi como la consistencia de un conjunto
#de premisas.

from sympy.logic.inference import satisfiable 

#comprueba si es posible asignar valores de verdad a las variables logicas que la componen
# para que la expresion logica sea verdadera.
#Es decir, verifica si existe alguna combinación de valores de verdad para las variables
# que haga que la expresión sea verdadera

#(x | y) & (x | ~y) & (~x | y) >> (x >> y))

from sympy import Symbol #Siempre en mayuscula
x = Symbol('x') 
y = Symbol('y')
satisfiable(x & ~x) # False
satisfiable((x | y) & (x | ~y) & (~x | y)) # {y: True, x: True}

# validez de una conclusión, se añade su negación a las premisas y comprueba consistencia
# De las premisas anteriores deducimos Implies(x, y)

satisfiable(((x | y) & (x | ~y) & (~x | y)) & (x >> y))

satisfiable((x | y) & (x | ~y) & (~x | y) & ~(x >> y)) #(x >> y)) = implicación

#False: no existe ninguna asignación de valores de verdad que haga que la expresión sea verdadera.

#Por lo tanto, x>>y

#TABLAS DE VERDAD (PARA COPIAR Y EDITAR EN EJERCICIOS)
import itertools

p, q = symbols('p q')
variables = [p, q]

# Encabezado de la tabla de verdad
print("p | q | ~q | p & q | p or q")
print("-" * 36)

# Generar la tabla de verdad y evaluar la expresión (itertools genera todas las combinaciones
#posibles de 1s y 0s, como se hace a mano 2**nvariables)

for p, q in  list(itertools.product([True, False], repeat=len(variables))):
    not_q = not q
    p_and_q = p and q
    p_or_q = p or q

    print(f"{p} | {q} |  {not_q}  |  {p_and_q} |  {p_or_q}")
    
#la f es para sustituir valores en un string

#EJERCICIOS:
    
#1. Negar y simplificar la expresión (p v q) --> r 

#2 Simplificar la siguiente expresión lógica y mostrar la tabla de
#verdad en consola (término izda. problema 13 Tema 2)

#Problema 13: [[((p ∧ q) ∧ r) ∨ ((p ∧ r) ∧ ¬r)] ∨ ¬q]

#3. Comprobar las inferencias lógicas de los problemas 18, 22 y 25 (Tema 2)
