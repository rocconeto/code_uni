# -*- coding: utf-8 -*-
"""

"""

#PRÁCTICA 3: ARITMÉTICA ENTERA Y MODULAR 2024-2025

# funciones de interés sobre números primos

from sympy import nextprime, randprime, isprime

nextprime(7) #calcula el siguiente número primo
nextprime(200)
p = randprime(1,100) #obtiene un número primo pseudoaleatorio en el rango
print(p)
isprime(p) #indica si el número p es primo
isprime(4)

# repaso de números aleatorios
from random import random, randint

# número real aleatorio en [0, 1]
random()

# número entero aleatorio en [a,b]
randint(1,100)

# factorización completa de enteros
from sympy import factorint

factorint(2000) #devuelve bases y exponentes

factorint(1859)

11*13**2 #comprobación

#si queremos guardar en una lista solo las bases

factores=list(factorint(2000))
factores

# función Phi de Euler (totient)
#Se debe repasar la teoría. Número total de enteros menores que un valor y coprimos con éste.

from sympy import totient

totient(10)

#de la teoría, sabemos que primero se ha de factorizar

factores=list(factorint(10))

phi=10

for i in range(len(factores)):
    phi *= (1-1/factores[i])
    
print(phi)

phi==totient(10) #verificamos si son lo mismo

#φ(10) = 4, ya que los números 1, 3, 7, 9 son coprimos con 10.

#Calculo de MCD

from sympy import gcd
gcd(15,6)

#Definición de función: Algoritmo de Euclides

#es preciso primero compilar las funciones, una vez compiladas, se hace una llamada
#con los datos de entrada que considere el usuario. La asignación de variables tiene
#lugar es un espacio de trabajo local.

def mcd(a,b):
    while b>0:
        r=a%b
        a=b
        b=r
    return (a)

mcd(15,6)

# Algoritmo de Euclides Extendido

def egcd(a, b):
    x, X = 0, 1 #inicialización de x1, x0 (según teoría)
    y, Y = 1, 0 #ídem de y1, y0
    while (b != 0):
        B = b
        q = a // b
        a, b = b, a % b
        x, X = X - q * x, x
        y, Y = Y - q * y, y
    return ([B, X, Y])

# ejemplo
egcd(4, 10) #ecuacion 4x + 10y = 2

#verificación del Teorema de Bézout
(egcd(4, 10)[1]*4 + egcd(4, 10)[2]*10) == egcd(4, 10)[0]

# inverso modular a*x ≡ 1 (mod m) - ES PRECISO REPASAR TEORÍA
#ecuación a*x + m*y = 1

def modInverse(a,m):
    L = egcd(a,m)
    assert L[0] == 1 #para que se verifique el inverso este valor debe ser 1, es el B de egcd (a y m han de ser coprimos)
    return L[1] % m #es el valor de x, lo retorna el egcd en posición 1 (se ha de dar en mod m, por eso se calcula el resto)

#ejemplo
#modInverse(2, 6) #AssertionError (¡no son coprimos!)
modInverse(2, 11) #(a * x) % m = 1
2*6 % 11 == 1 

modInverse(2,11)

#Ecuaciones Diofánticas

from sympy.solvers.diophantine import diophantine
from sympy import symbols

#como se trabaja con incógnitas en ecuaciones, hay que definirlas en cálculo simbólico
x, y, z, t = symbols("x, y, z, t", integer=True)

#resuelve ecuaciones diofánticas sencillas

#12x + 8y= 44

diophantine(12*x+8*y-44) #devuelve solución general

gcd(12,8) #como el mcd es 4 (divide a 44), existen 4 soluciones (t=0,1,2,3)

diophantine(12*x+8*y-44)

# Teorema Chino de los Restos

from sympy.ntheory.modular import crt
help(crt)
# ([lista de módulos], [lista de restos])
# devuelve la solución más pequeña, y el módulo M

crt([99, 97, 95], [49, 76, 65])

# exponenciación modular (eficiente)

pow(123, 456, 789) #es análogo a calcular 123**456 (mod 789)

#EJERCICIOS

#RESOLVER CON PYTHON LOS EJERCICIOS 1, 3, 4, 5, 9, 10, 12, 13, 14 y 15 DEL TEMA 1 (ARITMÉTICA ENTERA Y MODULAR)
