# -*- coding: utf-8 -*-
"""
Editor de Spyder

Este es un archivo temporal.
"""

#EJERCICIO 1 - RESOLVER ECUACIONES POR EL MÉTODO DE LA BISECCIÓN
#Empezamos dibujando la gráfica
from sympy import *
x = symbols("x")
import numpy as np
import matplotlib.pyplot as plt

ejex=np.linspace(1, 2, 100); #Establezco el eje x

f = lambdify(x, (x**3 + 4*x**2 - 10), 'numpy')
ejey1 = f(ejex)

#Dibujo las gráficas
plt.plot(ejex, ejey1, label="f(x)")
plt.plot([1, 2], [0, 0], color = 'orange', linewidth = 2, label = 'y=0')
plt.legend()
plt.show()


#Creamos la función que itera N veces
def Biseccion_N(f, a, b, N):
    print(f"{'n':<2} {'an':<12} {'bn':<12} {'cn':<12} {'fcn':<25} {'In':<12}")
    for n in range(0, N+1):
        c = (a+b)/2
        fc = f.subs(x, c)
        In = abs(a - b)
        print(f"{n:<2} {a:<12.8f} {b:<12.8f} {c:<12.8f} {fc:<25.15f} {In:<12.8f}")
        fa = f.subs(x, a)
        fb = f.subs(x, b)
        if((fa < 0 and fc >0) or (fa > 0 and fc < 0)):
            b = c
        elif((fc < 0 and fb >0) or (fc > 0 and fb < 0)):
            a = c
    return c

f = (x**3 + 4*x**2 - 10)
Biseccion_N(f, 1, 2, 13)

#Creamos la función que itera hasta que se cumpla la condición del TOL
def Biseccion_TOL(f, a, b, TOL):
    print(f"{'n':<2} {'an':<12} {'bn':<12} {'cn':<12} {'fcn':<25} {'In':<12}")
    contador = 0
    In = abs(a - b)
    while (In > TOL):
        c = (a+b)/2
        fc = f.subs(x, c)
        In = abs(a - b)
        print(f"{contador:<2} {a:<12.8f} {b:<12.8f} {c:<12.8f} {fc:<25.15f} {In:<12.8f}")
        fa = f.subs(x, a)
        fb = f.subs(x, b)
        contador += 1
        if((fa < 0 and fc >0) or (fa > 0 and fc < 0)):
            b = c
        elif((fc < 0 and fb >0) or (fc > 0 and fb < 0)):
            a = c
    return c

f = (x**3+4*x**2 - 10)
Biseccion_TOL(f, 1, 2, 0.01)

#Ejercicio 2 - Resolver la ecuación de Kepler para e = 0,5 y b = 0,7 en el intervalo [0,2]
#Por los métodos de la bisección, punto fijo, Newton-Raphson y de la secante
#Primero dibujamos la función

ejex=np.linspace(0, 2, 100); #Establezco el eje x

f = lambdify(x, (x - 0.5*sin(x) - 0.7), 'numpy')
ejey1 = f(ejex)

#Dibujo las gráficas
plt.plot(ejex, ejey1, label="f(x)")
plt.plot([0, 2], [0, 0], color = 'orange', linewidth = 2, label = 'y=0')
plt.legend()
plt.show()

#Resolvemos por bisección
def Biseccion_N(f, a, b, N):
    print(f"{'n':<2} {'an':<12} {'bn':<12} {'cn':<12} {'fcn':<25} {'In':<12}")
    for n in range(0, N+1):
        c = (a+b)/2
        fc = f.subs(x, c)
        In = abs(a - b)
        print(f"{n:<2} {a:<12.8f} {b:<12.8f} {c:<12.8f} {fc:<25.15f} {In:<12.8f}")
        fa = f.subs(x, a)
        fb = f.subs(x, b)
        if((fa < 0 and fc >0) or (fa > 0 and fc < 0)):
            b = c
        elif((fc < 0 and fb >0) or (fc > 0 and fb < 0)):
            a = c
    return c

def Biseccion_TOL(f, a, b, TOL):
    print(f"{'n':<2} {'an':<12} {'bn':<12} {'cn':<12} {'fcn':<25} {'In':<12}")
    contador = 0
    In = abs(a - b)
    while (In > TOL):
        c = (a+b)/2
        fc = f.subs(x, c)
        In = abs(a - b)
        print(f"{contador:<2} {a:<12.8f} {b:<12.8f} {c:<12.8f} {fc:<25.15f} {In:<12.8f}")
        fa = f.subs(x, a)
        fb = f.subs(x, b)
        contador += 1
        if((fa < 0 and fc >0) or (fa > 0 and fc < 0)):
            b = c
        elif((fc < 0 and fb >0) or (fc > 0 and fb < 0)):
            a = c
    return c

f = (x - 0.5*sin(x) - 0.7)
Biseccion_N(f, 0, 2, 5)
Biseccion_TOL(f, 0, 2, 0.001)

#Resolvemos por punto fijo
def puntoFijoN(f, x0, N):
    print(f"{'n':<2} {'xn':<17}")
    xn = x0
    for n in range(N+1):
        print(f"{n:<2} {xn:<17.15f}")
        if(n < N):
            xn = f(xn)
    return xn

def puntoFijoTOL(f, x0, TOL):
    print(f"{'n':<2} {'xn':<17} {'|xn-xn-1|':<22}")
    xn = x0
    contador = 0
    resta = 0
    if(contador == 0):
        print(f"{contador:<2} {xn:<17.15f} {resta:<22.20f}")
        xn1 = xn
        xn = f(xn)
        resta = abs(xn--xn1)
        contador += 1
    while(resta > TOL):
        print(f"{contador:<2} {xn:<17.15f} {resta:<22.20f}")
        xn1 = xn
        xn = f(xn)
        resta = abs(xn-xn1)
        contador += 1
    print(f"{contador:<2} {xn:<17.15f} {resta:<22.20f}")
    return xn

g = lambdify(x, (0.5*sin(x) + 0.7), 'numpy')
puntoFijoN(g, 0, 5)
puntoFijoTOL(g, 0, 0.001)

#Resolvemos por Newton-Raphson. Necesitamos la derivada
def NewtonRaphsonN(f, x0, N):
    """Dados la función, un punto y la cantidad de iteraciones, primero calcula la derivada y después busca el
    punto cuyo valor es lo más cercano posible a 0"""
    df = diff(f, x)
    print(f"{'n':<2} {'xn':<17}")
    xn = x0
    print(f"{0:<2} {xn:<17.15f}")
    for n in range(1, N+1):
        xn1 = xn
        xn = xn1 - (f.subs(x, xn1) / df.subs(x, xn1))
        print(f"{n:<2} {xn:<17.15f}")
    return xn

def NewtonRaphsonTOL(f, x0, TOL):
    """Dados la función, un punto y cuándo se detiene el proceso, calcula la derivada y después busca el
    punto cuyo valor es lo más cercano posible a 0"""
    df = diff(f, x)
    print(f"{'n':<2} {'xn':<17} {'|xn-xn-1|':<22}")
    xn = x0
    resta = 0
    contador = 0
    print(f"{contador:<2} {xn:<17.15f} {resta:<22.20f}")
    if(contador == 0):
        xn1 = xn
        xn = xn1 - (f.subs(x, xn1) / df.subs(x, xn1))
        resta = abs(xn-xn1)
        contador += 1
        print(f"{contador:<2} {xn:<17.15f} {resta:<22.20f}")
    while(resta > TOL):
        xn1 = xn
        xn = xn1 - (f.subs(x, xn1) / df.subs(x, xn1))
        resta = abs(xn-xn1)
        contador += 1
        print(f"{contador:<2} {xn:<17.15f} {resta:<22.20f}")
    return xn
    
f = (x - 0.5*sin(x) - 0.7)
NewtonRaphsonN(f, 0, 4)
NewtonRaphsonTOL(f, 0, 0.001)

#Resolvemos por el método de la secante
def SecanteN(f, x0, x1, N):
    """Dados la función, dos puntos y la cantidad de iteraciones, busca el punto cuyo valor es lo más cercano
    posible a cero."""
    xn = x0
    resta = 0
    print(f"{'n':<2} {'xn':<10} {'|xn-xn-1|':<10}")
    print(f"{0:<2} {xn:<10.8f} {resta:<10.8f}")
    xn1 = x0
    xn = x1
    resta = abs(xn-xn1)
    print(f"{1:<2} {xn:<10.8f} {resta:<10.8f}")
    for n in range(2, N+1):
        xn2 = xn1
        xn1 = xn
        xn = xn1 - f(xn1) * ((xn1-xn2) / (f(xn1) - f(xn2)))
        resta = abs(xn-xn1)
        print(f"{n:<2} {xn:<10.8f} {resta:<10.8f}")
    return xn

def SecanteTOL(f, x0, x1, TOL):
    """Dados la función, dos puntos y cuándo se detienen las iteraciones, busca el punto cuyo valor es lo más cercano
    posible a cero."""
    xn = x0
    resta = 0
    print(f"{'n':<2} {'xn':<10} {'|xn-xn-1|':<10}")
    print(f"{0:<2} {xn:<10.8f} {resta:<10.8f}")
    xn1 = x0
    xn = x1
    resta = abs(xn-xn1)
    print(f"{1:<2} {xn:<10.8f} {resta:<10.8f}")
    contador = 2
    while(resta > TOL):
        xn2 = xn1
        xn1 = xn
        xn = xn1 - f(xn1) * ((xn1-xn2) / (f(xn1) - f(xn2)))
        resta = abs(xn-xn1)
        print(f"{contador:<2} {xn:<10.8f} {resta:<10.8f}")
        contador += 1
    return xn

f = lambdify(x, (x - 0.5*sin(x) - 0.7), 'numpy')
SecanteTOL(f, 0, 2, 0.001)
SecanteN(f, 0, 2, 4)    
        