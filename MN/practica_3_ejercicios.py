# -*- coding: utf-8 -*-
"""
Created on Tue Wed 19 17:25:43 2025

"""

#EJERCICIO 1 - Aproximar las 3 primeras derivadas de una función f en x0
import numpy as np
from numpy import linalg as LA
import sympy as sp
x = sp.symbols("x") 

def derivadas(h, x0, n, f): 
    """h es la distancia, x0 el punto, f la función y n la lista que contiene cuántas veces se quiere derivar, en nuestro caso 3
    Muestra el valor desde la primera hasta la tercera derivada de la función en un punto."""
    for k in n:
        #Elaboramos los nodos en función de x0 y h
        nds = [x0 - 2*h, x0 - h, x0, x0 + h, x0 + 2*h]
        m = len(nds)
        
        X = np.zeros((m, m)) 
        for j in range(m): #columnas
            for i in range(m): #iteración filas
                X[i, j] = nds[j] ** i #coge el punto xj y lo eleva al indice fila
        M = np.asmatrix(X) #convierte a matrix
        
        #Elaboramos la lista que contiene los alphas en función de qué derivada estemos aproximando
        if k == 1:
            b = np.array([0, 1, 2*x0, 3*x0**2, 4*x0**3])
            alphas = LA.solve(M, b)
            
            #Aproximamos la función
            F = 0
            for i in range(5): 
                F = F + alphas[i] * f(nds[i]) 
            print("Primera derivada es: ", F)
        elif k == 2:
            b = np.array([0, 0, 2, 6*x0, 12*x0**2])
            alphas = LA.solve(M, b)
            
            #Aproximamos la función
            F = 0
            for i in range(5): 
                F = F + alphas[i] * f(nds[i]) 
            print("Segunda derivada es: ", F)
        else:
            b = np.array([0, 0, 0, 6, 24*x0])
            alphas = LA.solve(M, b)
            
            #Aproximamos la función
            F = 0
            for i in range(5): 
                F = F + alphas[i] * f(nds[i]) 
            print("Tercera derivada es: ", F)
    
h = 0.1
f = sp.lambdify(x, sp.sin(x))
derivadas(h, 0, [1, 2, 3], f)

#EJERCICIO 2 - Adaptar el procedimiento anterior para aproximar la derivada dadas una lista con los nodos y otra con los valores de la función
import numpy as np
def der_nodos(nds, f, x0):
    """Dados los nodos y sus valores, aproxima la derivada en el punto dado, x0. 
    Esta aproximación será realizada con las fórmulas de dos y tres puntos"""
    #Calculo la distancia entre nodos, suponiendo que la distancia entre todos ellos es la misma
    h = nds[1] - nds[0]
    
    #Busco el índice de x0 en la lista de los nodos
    idx = nds.index(x0)
    
    #Elaboro la primera derivada
    print("Primera derivada -> f'( ", x0, ")")
    if idx >= 1: #Comprueba que hay, al menos, un nodo inferior para calcular en 2-puntos regresiva
        d_2p_regr = (f[idx] - f[idx - 1]) / h
        print("2-puntos regresiva = ", d_2p_regr)
    if idx < len(nds) - 1: #Comprueba que hay, al menos, un nodo superior
        d_2p_progr = (f[idx + 1] - f[idx]) / h
        print("2-puntos progresiva = ", d_2p_progr)
    if 0 < idx < len(nds) - 1: #Compruebo que hay, al menos, un nodo superior y otro inferior
        d_3p_c = (f[idx + 1] - f[idx - 1]) / (2*h)
        print("3-puntos central = ", d_3p_c)
    if idx < len(nds) - 2: #Compruebo que hay, al menos, 2 nodos superiores
        d_3p_progr = (4*f[idx + 1] - f[idx + 2] - 3*f[idx]) / (2*h)
        print("3-puntos progresiva = ", d_3p_progr)
    if 1 < idx: #Compruebo que hay, al menos, 2 nodos inferiores
        d_3p_regr = (4*f[idx - 1] - f[idx - 2] - 3*f[idx]) / (2*h)
        print("3-puntos regresiva = ", d_3p_regr)
    if 1 < idx < len(nds) - 2: #Compureba que hay, al menos, dos nodos superiores e inferiores
        d_5p_c = (-f[idx + 2] + 8*f[idx + 1] - 8*f[idx-1] + f[idx-2]) / (12*h)
        print("5-puntos central = ", d_5p_c)
    
    #Elaboro la segunda derivada
    print("Segunda derivada -> f''( ", x0, ")")
    if 0 < idx < len(nds) - 1: #Compruebo que hay, al menos, un nodo superior y otro inferior
        d2_3p_c = (f[idx + 1] - 2*f[idx] + f[idx - 1]) / (h**2)
        print("3-puntos central = ", d2_3p_c)
    if 1 < idx < len(nds) - 2:
        d2_5p_c = (-f[idx + 2] + 16*f[idx + 1] - 30*f[idx] + 16*f[idx-1] - f[idx-2]) / (12*h**2)
        print("5-puntos central = ", d2_5p_c)
        

nds = [0.2, 0.4, 0.6, 0.8, 1.0]
f = [0.9798652, 0.9177710, 0.8080348, 0.6386093, 0.38437335]
der_nodos(nds, f, 0.4)
der_nodos(nds, f, 0.6)


#EJERCICIO 3 - Igual que el primero pero para integrales
import math as mt
import numpy as np
from numpy import linalg as LA
import sympy as sp
x = sp.symbols("x") 
def integrales(f, a, b): 
    """Se usa para fórmulas de cuadratura y derivación numéricas meidante el método de coeficientes indeterminados.
    #h es la distancia, x0 el punto, f la función y n la lista que contiene cuántas veces se quiere derivar, en nuestro caso 3"""
    #Elaboramos los nodos en función de x0 y h
    nds = [a, (2*a+b)/3, (a+2*b)/3, b]
    n = len(nds)
            
    #Elabora la matriz de Vandermonde y el vector p, de la fórmula M*alpha = b, pero b = p
    X = np.zeros((n, n)) 
    p = np.zeros(n)
    for j in range(n): #columnas
        for i in range(n): #filas
            X[i, j] = nds[j] ** i #eleva el punto xj al índice i
            p[i] = sp.integrate(x**i, (x, a, b))
    M = np.asmatrix(X) #convierte a matriz
    
    #Resuelve el sistema de ecuaciones y, para evitar errores, pasa la función a función numérica.También aproxima la integral
    alphas = LA.solve(M, p)
    f_num = sp.lambdify('x', f, "numpy")
    int_aprox = 0
    for i in range(n):
        int_aprox += alphas[i] * f_num(nds[i])
    
    #Muestra el resultado y también lo devuelve
    print("tres_octavos( ", f, ",", a, ",", b, "). Sol = ", int_aprox)
    return int_aprox
    
integrales(x, 0, 1)

f1 = sp.cos(x)
a1 = -mt.pi/2
b1 = mt.pi/2
integrales(f1, a1, b1)

f2 = sp.exp(x)
integrales(f2, 0, 1)

#EJERCICIO 4 - Aproximar integrales por rectángulo, punto medio, trapecio y Simpson
import math as mt
import sympy as sp
x = sp.symbols("x") 
def cuadr_comp(f, a, b, n):
    """Dados la función, los extremos del intervalo y la cantidad n de subintervalos
    calcula la integral de la función por las fórmulas de cuadratura compuesta."""
    #Calculamos la distancia entre los puntos del intervalo
    h = (b-a)/n
    
    #Calculamos el valor de la función en cada extremos de los subintervalos
    i = a
    img = []
    while i <= b:
        f1 = f.subs(x, i)
        img.append(f1)
        
    #Sumamos todos los valores de la función y luego los multiplica por h
    suma = 0
    for i in range(img):
        suma += img[i]
    
    rect = h * suma
    print("Rectángulos compuesta: ", rect)
    
f = x**2 * (mt.e)**(-x)**2
cuadr_comp(f, 0, 2, 9)
