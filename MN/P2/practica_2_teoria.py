# -*- coding: utf-8 -*-
"""

@author: I Gomara based on JI Farran notes
"""

#PRÁCTICA 2: INTERPOLACIÓN POLINÓMICA  

# Vamos a obtener los polinomios de Taylor para interpolar  
# Usamos la librería sympy  

from sympy import *  

#definimos x como incógnita

x = symbols("x") 

# Desarrollo en serie de Taylor hasta orden 3 en x=1  
#función series de numpy (x es incógnita, 
#1 punto donde se construye Taylor, 4 número de términos - orden 3)

s = (x * exp(x)).series(x, 1, 4) 
print(s) 

r= (sin(x)).series(x, 0, 4) 
print(r) 

# Obtenemos una aproximación eliminando O() y sustituyendo
# 0() es el error (resto), hay que quitarlo para evaluar polinomio  

s = s.removeO() 
print(s)

s1=s.subs(x, 3) 
float(s1)

# Evaluación númerica (no simbólica) con evalf  

s.evalf(subs={x: 3}) 

# Se podrían ir calculando los coeficientes de Taylor y construyendo el polinomio  

from sympy import diff, factorial 

f = x * exp(x) 
a0= f.subs(x, 1) 
print(a0)
a1 = diff(f, x).subs(x, 1) 
print(a1)
a2 = diff(f, x, 2).subs(x, 1) / factorial(2) 
print(a2)
a3 = diff(f, x, 3).subs(x, 1) / factorial(3) 
print(a3)
P = a0 + a1*(x-1) + a2*(x-1)**2 + a3*(x-1)**3 
print(P) 
P.subs(x, 3) 
P.evalf(subs={x: 3}) 

P==s

# Interpolación polinómica automática con numpy (lineal) 

import numpy as np 
import sympy as sp
import matplotlib.pyplot as plt

# nodos y valores de la función  

xp = [1, 2, 3] 
fp = [3, 2, 0] 

# Interpolamos en el punto x = 2.5  

np.interp(2.5, xp, fp) 

# Recordar que se pueden dibujar funciones con matplotlib.pyplot  

#esto es para discretizar el eje x (cuanta mayor resolución más suave el ploteado)

t=np.arange(1,3.1,0.1)
t2=np.linspace(1,3,21)

print(t)
print(t2)

#vamos a dibujar funcion seno

ejex=np.linspace(-np.pi, np.pi, 100);

#comando para que funciones de sympy admitan evaluación introduciendo un array 
#en lugar de un dato

fsin = sp.lambdify(x, sp.sin(x), 'numpy')
fcos = sp.lambdify(x, sp.cos(x), 'numpy')

#ahora ya se puede introducir el array en la función, y devuelve un array (las f(y))

ejey1=fsin(ejex)
ejey2=fcos(ejex)

print(ejex)
print(ejey1)

plt.plot(ejex,ejey1,label="sin(x)")
plt.plot(ejex,ejey2,label="cos(x)")
plt.legend()
plt.show()
    
#########################
#ANOTACIONES ADICIONALES SOBRE FUNCIONES - REPASO


#Una función en python es un conjunto de intrucciones escritas en código cuya 
#finalidad es realizar una tarea específica.

#las funciones generalmente poseen uno o varios input y uno o varios output


#EJEMPLO, VAMOS A CONSTRUIR UNA FUNCIÓN QUE REALICE LA SUMA DE 3 NÚMEROS

import numpy as np
import sympy as sp
import math as mt

def suma3(a,b,c):
    """Esta función realiza la suma de los valores a, b y c que indica el usuario"""
    suma=a+b+c
    return [a, b, c, suma]

#Si se ejecuta hasta aquí la función no hace nada. Python lee las instrucciones
#de la misma y la compila. Para ejecutarla, ha de ser llamada, indicando los valores
#de a, b y c (hasta ahora variables genéricas)

suma3(1,2,3)[3]


#si ejecutamos de este modo la función devuelve los output, pero no los guarda en una variable

output=suma3(1,2,3)
output

#ahora ya sí hemos guardado los output.

#SE DESACONSEJA LA COMUNICACIÓN POR CONSOLA CON LA FUNCIÓN UTILIZANDO EL COMANDO INPUT

#supongamos que creamos la misma función, pero indicamos los datos por consola

def suma3_input():
    """Esta función realiza la suma de los valores a, b y c que indica el usuario"""
    a = input("Introduzca el primer número: \n")
    a=float(a)
    b = input("Introduzca el segundo número: \n")
    b=float(b)
    c = input("Introduzca el tercer número: \n")
    c=float(c)
    suma=a+b+c
    return [a, b, c, suma]

suma3_input()

#como vemos, realiza la misma función, pero es mucho menos versátil, ya que se precisa
#comunicación por pantalla.

#supongamos ahora que se pide calcular la suma de 3 números consecutivos, empezando por
#el 1 y terminando en el 100

#con la primera versión es bastante directo

sumas=[]
for i in range(1,101):
    sumas.append(suma3(i, i+1, i+2)[3])
sumas
    
#pero con la segunda sería inviable, habría que meter 300 números a mano

sumas=[]
for i in range(1,101):
    sumas.append(suma3_input()[3])   
    
#POR TANTO, PARA EVITAR PROBLEMAS EN ESTE SENTIDO, SE RECOMIENDA UTILIZAR SIEMPRE
#LA PRIMERA VERSIÓN (A NO SER QUE SE INDIQUE EXPRESAMENTE LO CONTRARIO)

#TRABAJO CON TABLAS

#se puede crear una tabla con 0 o 1s

Y=np.ones((2,2))
Y

T=np.zeros((3,4))

#para meter datos en filas, columnas y posiciones

T

#filas

T[:,0]=[1,2,3]    
T

#filas a partir de una posición hasta el final

T[1,1:]=[2,2,2]

T

#filas desde posición inicial hasta final (recordamos que siempre que queda en 
#la anterior a la final)

T[2,2:4]=[3,3]

T
