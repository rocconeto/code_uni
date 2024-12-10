# -*- coding: utf-8 -*-
"""

@author:
"""

#PRÁCTICA 7: COMBINATORIA 2024-2025

# Repasemos los conjuntos y el paquete sympy

from sympy import FiniteSet, EmptySet
A = EmptySet #defino un conjunto vacio
A = FiniteSet('a', 'b', 'c', 'd') #conjunto finito
A

#otra forma

A1=set(['a', 'b', 'c', 'd'])

#TÉCNICAS DE CONTEO

#NÚMERO DE SUBCONJUNTOS

A = FiniteSet(1, 2, 3)
P=A.powerset() #genera el conjunto de todos los subconjuntos posibles
P
list(P) #para verlo en su totalidad
len(P) #es el cardinal, dos elevado al número de elementos en A

#PERMUTACIONES SIN REPETICIÓN

from itertools import permutations
A = FiniteSet(1, 2, 3)
per=set(permutations(A, 3)) #A es el conjunto, 3 es el número de elementos que se consideran para permutar (todos)
per
len(per)

#otra forma

from sympy.utilities.iterables import variations
per1=set(variations(A, 3))
per1
len(per1) #calcula las variaciones sin repeticón tomando todos los elementos (3). Son lo mismo

per==per1 #son lo mismo

#PERMUTACIONES CON REPETICIÓN

A=[1,2,2,3,3] #hay que definir el multiconjunto mediante una lista, si se hace con set eliminará los repetidos

per_r=list(variations([1,2,2,3,3], 5))
per_r
len(per_r) #ojo porque es una lista donde aparecen todas las permutaciones con repetición, incluye las repetidas 5!
set(per_r) #convertimos a set para eliminar elementos repetidos
len(set(per_r))
#ahora sí, son 30 en lugar de 120, hemos eliminado las que eran iguales

#VARIACIONES SIN REPETICIÓN

from sympy.utilities.iterables import variations
var=set(variations([1,2,3], 2))
var
len(var)# 3!/1!=6

#VARIACIONES CON REPETICIÓN

var_r=set(variations([1,2,3], 2, True)) #True indica repetición
var_r
len(var_r) #3**2=9

#otra forma

F=FiniteSet(1,2,3)
set(F**2) #producto cartesiano de F con F

#COMBINACIONES SIN REPETICIÓN

from itertools import combinations

comb=set(combinations([1,2,3], 2)) ##subconjuntos de A con 2 elementos
comb
len(comb) #3!/2!1!=3

#otra forma si sólo se quiere el nr de posibilidades, utilizando el cardinal del conjunto original

from sympy import *
binomial(3,2) #número combinatorio (binomial). 4 elementos seleccionados de 2 en 2 sin importar orden

#COMBINACIONES CON REPETICIÓN

from itertools import combinations_with_replacement

combr=set(combinations_with_replacement([1,2,3], 2)) 
combr
len(combr) # (n+r+1/r) = 6


#EJERCICIOS: 

#1) Resuelve el problema de la hamburguesería de las hojas de problemas (Ej. 2), añadiendo dos ingredientes más a tu gusto.

#2) Resuelve el problema de los programas que se compilan (Ej. 3a), pero considerando sólo 6 programas.
#Obtén en un conjunto todas las posibilidades y su cardinal.

#3) Resuelve el problema de las 10 personas que se sientan en una fila de 6 sillas (ej. 6). Obtén todas las posibilidades
#en un conjunto

#4) Resuelve el problema del equipo de fútbol sala (ej. 13). Obtén un conjunto con todas las posibilidades

#5) Construye una función que tome como input el número de filas de una matriz cuadrada y devuelva en una 
#matriz diagonal inferior el Triángulo de Pascal. 

# 1               # C(0,0) 
# 1 1             # C(1,0) C(1,1)  
# 1 2 1           # C(2,0) C(2,1) C(2,2)  
# 1 3 3 1         # C(3,0) C(3,1) C(3,2) C(3,3)
# 1 4 6 4 1       # C(4,0) C(4,1) C(4,2) C(4,3) C(4,4)
# 1 5 10 10 5 1   # C(5,0) C(5,1) C(5,2) C(5,3) C(5,4) C(5,5)

#AYUDA: Crea primero una matriz vacía con 0s, y posteriormente rellénala mediante bucles.

from numpy import *

matriz=zeros((5,5)) #Ojo con el doble paréntesis, debe aparecer siempre. Es un error común olvidarlo.

#la posición i (filas), j (columnas) de una matriz se indica como matriz[i,j]







