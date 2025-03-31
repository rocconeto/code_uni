# -*- coding: utf-8 -*-
"""
Created on Wed Feb 26 13:48:03 2025

@author: uva
"""

#EJERCICIO 1 - LOS TRES PRIMEROS POLINOMIOS DE TAYLOR DE LA FUNCIÓN f(x) = sen(x), en x=0
from sympy import *
x = symbols("x")
def taylor(f, x0, n):
    'Polinomio de Taylor. f es la función, x0 es el número entorno al cual trabajas, n es el orden al que quieres llegar'
    #aqui ya yo
    x = symbols("x")
    p = []
    polinomio = 0
    for i in range(n+1):
        if i==0:
            a = f.subs(x, x0)
            if a != 0:
                polinomio.append(a)
        else:
            a = diff(f, x, i).subs(x, x0) / factorial(i)
            a = a * (x-x0)**i
            if a != 0:
                p.append(a)
    for i in p:
        polinomio += i
    return polinomio

P1 = taylor(sin(x), 0, 2)
P2 = taylor(sin(x), 0, 4)
P3 = taylor(sin(x), 0, 6)

#GRÁFICA
import sympy as sp
import numpy as np
import matplotlib.pyplot as plt

ejex=np.linspace(-np.pi, np.pi, 100); #Establezco el eje x

#Paso las funciones a numpy
fsin = sp.lambdify(x, sp.sin(x), 'numpy')
fp1 = sp.lambdify(x, P1, 'numpy')
fp2 = sp.lambdify(x, P2, 'numpy')
fp3 = sp.lambdify(x, P3, 'numpy')

#Establezco los valores de las funciones
ejey1 = fsin(ejex)
ejey2 = fp1(ejex)
ejey3 = fp2(ejex)
ejey4 = fp3(ejex)

#Dibujo las gráficas
plt.plot(ejex, ejey1, label="sin(x)")
plt.plot(ejex, ejey2, label="Taylor 1")
plt.plot(ejex, ejey3, label="Taylor 3")
plt.plot(ejex, ejey4, label="Taylor 5")
plt.legend()
plt.show()

#EJERCICIO 2 - Polinomio interpolador de Lagrange de f(x) = 1/x, en los nodos x0 = 2, x1 = 5/2 y x2 = 4
from sympy import *
x = symbols("x")
def polinomios(nd=[]):
    'esta función calcula los li que son necesarios para calcular el Polinomio Interpolador de Lagrange. nd es la lista de los nodos en los que se quiere aplicar la función'
    n = [] #Lista para los numeradores de los polinomios li
    d = [] #Lista para los denominadores de los li
    li = [] #Lista de los polinomios li
    for i in nd:
        temp = []
        temp1 = []
        for j in nd:
            if j != i:
                N = x - j #Crea los factores que luego se multiplican y los guarda en una lista "temporal"
                temp.append(N)
                D = i - j #Calcula los valores de los elementos que dividen en los polinomios y los guarda en otra lista temporal
                temp1.append(D)
            if len(temp) == (len(nd)-1): #Cuando la longitud de lista "temporal" es menor por 1 elemento a la lista dada
                t = temp[0]
                for k in range(1, len(nd)-1):
                    t = t * temp[k]
                n.append(t) #Crea la multiplicación con x y la guarda en la lista de los numeradores
                temp = [] #Vacío la lista temporal
            if len(temp1) == (len(nd)-1): #Cuando la longitud de lista "temporal1" es menor por 1 elemento a la lista dada
                ll = temp1[0]
                for k in range(1, len(nd)-1):
                    ll = ll * temp1[k] #Multiplica los elementos que luego van a dividir y los guarda en la lista de los denominadores
                d.append(ll)  
                temp1 = [] #Vacio la lista temporal
    for i in range(0, len(n)): 
        L = n[i]/d[i] #Divide los numeradores entre los denominadores y lo guarda en la lista de los polinomios
        li.append(L)
    return li

li = polinomios([2, 5/2, 4])
print(li)

def pol_interpol_lagrange(f, li=[], nd=[]):
    'dada la lista calculada con la función polinomios (p), la función (f) y la lista de nodos (nd), devuelve el polinomio interpolador en forma de Lagrange'
    fx = [] #Lista cuyos valores serán los f(x) según el valor para cada nodo
    p = [] #Lista que guardará los resultados de multiplicar los li y los f(x) correspondientes
    lagrange = 0 #Variable que guardará el polinomio interpolador en forma de Lagrange
    for i in range(len(nd)):
        a = f.subs(x, nd[i])
        fx.append(a)
    for i in range(len(fx)):
        b = fx[i]*li[i]
        p.append(b)
    for i in range(len(p)):
        lagrange += p[i]
    return lagrange

pol_interpol_lagrange(1/x, li, [2, 5/2, 4])

def Lagrange(f, P, nd=[]):
    'Dados una función (f), un punto (P) y una lista de nodos (nd), la función calcula la lista de polinomios li, después usa esto para calcular el polinomio interpolador en forma de Lagrange y, para terminar, sustituye en este último el Punto para aproximar la aproximación de la función en ese punto. Devuelve este último valor'
    n = [] #Lista para los numeradores de los polinomios li
    d = [] #Lista para los denominadores de los li
    li = [] #Lista de los polinomios li
    fx = [] #Lista cuyos valores serán los f(x) según el valor para cada nodo
    p = [] #Lista que guardará los resultados de multiplicar los li y los f(x) correspondientes
    lagrange = 0 #Variable que guardará el polinomio interpolador en forma de Lagrange
    for i in nd:
        temp = []
        temp1 = []
        for j in nd:
            if j != i:
                N = x - j #Crea los factores que luego se multiplican y los guarda en una lista "temporal"
                temp.append(N)
                D = i - j #Calcula los valores de los elementos que dividen en los polinomios y los guarda en otra lista temporal
                temp1.append(D)
            if len(temp) == (len(nd)-1): #Cuando la longitud de lista "temporal" es menor por 1 elemento a la lista dada
                t = temp[0]
                for k in range(1, len(nd)-1):
                    t = t * temp[k]
                n.append(t) #Crea la multiplicación con x y la guarda en la lista de los numeradores
                temp = [] #Vacío la lista temporal
            if len(temp1) == (len(nd)-1): #Cuando la longitud de lista "temporal1" es menor por 1 elemento a la lista dada
                ll = temp1[0]
                for k in range(1, len(nd)-1):
                    ll = ll * temp1[k] #Multiplica los elementos que luego van a dividir y los guarda en la lista de los denominadores
                d.append(ll)  
                temp1 = [] #Vacio la lista temporal
    for i in range(0, len(n)): 
        L = n[i]/d[i] #Divide los numeradores entre los denominadores y lo guarda en la lista de los polinomios
        li.append(L)
    for i in range(len(nd)):
        a = f.subs(x, nd[i])
        fx.append(a)
    for i in range(len(fx)):
        b = fx[i]*li[i]
        p.append(b)
    for i in range(len(p)):
        lagrange += p[i]
    r=lagrange.subs(x, P)
    return r

Lagrange(1/x, 3, [2, 5/2, 4])
help(Lagrange)

#EJERCICIO 3 - FUNCIÓN para polinomio interpolador en forma de Newton.
import numpy as np
#Empezamos con la función que creará la matriz de diferencias divididas
def matrizDifDiv(nds=[], img=[]):
    'Dadas las lista de nodos y valores, calcula la tabla de diferencias divididas'
    #Creamos la matriz de orden n, siendo n la longitud de la lista de los nodos y cambiamos la primera columna por los valores
    n = len(nds)
    dd = np.zeros((n, n)) 
    dd[:, 0] = img
    
    #Calculamos las diferencias divididas
    for j in range(1, n): #j indica el orden de la diferencia dividida (primera, segunda, ...)
        for i in range(n-j): #i se relaciona con los nodos. Como para calcular las diferencias divididas depende del orden de estas, i depende de j
            dd[i, j] = (dd[i+1, j-1] - dd[i, j-1]) / (nds[i+j] - nds[i])
    tdd = np.column_stack((nds, dd))
    return tdd

nds = [1.0, 1.3, 1.6, 1.9, 2.2]
img = [0.7865197, 0.6200860, 0.4554022, 0.2818186, 0.1103623]
tdd = matrizDifDiv(nds, img)
print(tdd)

from sympy import *
x = symbols("x")
def pol_Int(nds=[], img=[], tdd=[]):
    'Dados los nodos, los valores y la tabla de diferencias divididas, elabora el polinomio interpolador en forma de Newton'
    Polinomio = img[0] #El primer valor está tal cual en el polinomio, no hay que hacer nada con el
    K = []
    #Con unos bucles, elaboro los términos necesarios para elaborar el polinomio
    for i in range(len(nds)):
        k = (x-nds[i])
        K.append(k) #Esta lista contiene los (x-xi)
    M = []
    M.append(K[0])
    for i in range(1, len(K)-1):
        k = K[i]*M[i-1]
        M.append(k) #En esta lista se almacenan los términos (x-xi) multiplicados por los anteriores
    #Elabora el polinomio
    for i in range(len(M)):
        Polinomio += (M[i]*tdd[0, i+2]) #De la tabla de diferencias divididas me interesa la primera fila y todas las columnas menos las dos primeras (nodos y valores)
    return Polinomio

Polinomio = pol_Int(nds, img, tdd)
print(Polinomio)

#Para pasar a la forma general
import sympy as sp
Polinomio_exp = sp.expand(Polinomio)
#sustituyo el valor de x por el punto en el que quiero hallar el valor aproximado
Polinomio_exp.subs(x, 1.5)

#funcion definitiva
import numpy as np
import sympy as sp
from sympy import *
x = symbols("x")
def Newton(z, nds=[], img=[]):
    'Esta función ekabora el polinomio interpolador en forma de Newton dadas una lista con los nodos (nds) y otra con los valores (img). Después, halla el valor aproximado de la función en el punto dado(z)'
    #Creamos la matriz de orden n, siendo n la longitud de la lista de los nodos y cambiamos la primera columna por los valores
    n = len(nds)
    dd = np.zeros((n, n)) 
    dd[:, 0] = img
    
    #Calculamos las diferencias divididas
    for j in range(1, n): #j indica el orden de la diferencia dividida (primera, segunda, ...)
        for i in range(n-j): #i se relaciona con los nodos. Como para calcular las diferencias divididas depende del orden de estas, i depende de j
            dd[i, j] = (dd[i+1, j-1] - dd[i, j-1]) / (nds[i+j] - nds[i])
    
    #A la tabla de diferencias divididas le añadimos los nodos en la primera columna
    tdd = np.column_stack((nds, dd))
    print("Matrix: ")
    print(tdd)
    
    #Empezamos a elaborar el Polinomio
    Polinomio = img[0]
    K = []
    #Con unos bucles, elaboro los términos necesarios para elaborar el polinomio
    for i in range(len(nds)):
        k = (x-nds[i])
        K.append(k) #Esta lista contiene los (x-xi)
    M = [K[0]]
    for i in range(1, len(K)-1):
        k = K[i]*M[i-1]
        M.append(k) #En esta lista se almacenan los términos (x-xi) multiplicados por los anteriores
    #Elabora el polinomio
    for i in range(len(M)):
        Polinomio += (M[i]*tdd[0, i+2]) #De la tabla de diferencias divididas me interesa la primera fila y todas las columnas menos la primera
    Polinomio_exp = sp.expand(Polinomio)
    print("Polinomio = ") 
    print(Polinomio)
    print("\nPolinomio expresión general = ")
    print(Polinomio_exp)
    newton = Polinomio_exp.subs(x, z)
    return newton

nds = [1.0, 1.3, 1.6, 1.9, 2.2]
img = [0.7865197, 0.6200860, 0.4554022, 0.2818186, 0.1103623]
Newton(1.5, nds, img)

#EJERCICIO 4 - Polinomio interpolador de Hermite y aproximación en un punto
from sympy import *
import numpy as np
import sympy as sp
x = symbols("x")
def dif_div_Hermite(nds=[], f=[], df=[]):
    'Dados los nodos y el valor de la función y su derivada en dichos puntos, elabora la tabla de diferencias divididas.'
    nds2 = [] #Lista para los nodos duplicados
    f2 = [] #Creo una lista con los valores duplicados como los nodos para la primera columna de la tabla de diferencias divididas
    df2 = [] #Hago lo mismo con los valores de la derivada para evitar problemas
    n = len(nds)
    for i in range(n):
        nds2.append(nds[i])
        nds2.append(nds[i]) #Añade dos veces el valor
        f2.append(f[i])
        f2.append(f[i])
        df2.append(df[i])
        df2.append(df[i])
    ddH = np.zeros((2*n,2*n))
    ddH[:, 0] = f2
    for j in range(1, 2*n):
        for i in range((2*n)-j):
            if j==1:
                if nds2[i] == nds2[i+1]:
                    ddH[i, j] = df2[i]
                else:
                    ddH[i, j] = (ddH[i+1,0] - ddH[i,0])/(nds2[i+1]-nds2[i])
            else:
                ddH[i, j] = (ddH[i+1, j-1] - ddH[i, j-1]) / (nds2[i+j] - nds2[i])
    np.array(nds2).reshape(-1,1) #convertimos la lista en un array columna para que 
    tddH = np.column_stack((nds2, ddH))
    print("Matrix: ")
    print(tddH)
    return tddH

nds = [1.3, 1.6, 1.9]
f = [0.6200860,0.4554022, 0.2818186]
df = [-0.5220232, -0.5698959, -0.5811571]
ddH = dif_div_Hermite(nds, f, df)

#Segunda parte - elaboracion del polinomio
def pol_Hermite(nds=[], f=[], df=[], ddH=[]):
    'Dados los nodos, los valores en los nodos de la función y su derivada y la tabla de diferencias divididas elabora el polinomio interpolador de Hermite'
    #Calculo los (x-xi)
    Y = []
    nds2 = []
    for i in range(len(nds)):
        nds2.append(nds[i])
        nds2.append(nds[i]) #Añade dos veces el valor
    n = len(nds2)
    for i in range(n):
        y = (x-nds2[i])
        Y.append(y)
    
    #Elaboro la lista que multiplica los (x-xi) por todos los anteriores
    Y2 = [Y[0]]
    for i in range(1, len(Y)):
        z = (Y2[i-1]) * (Y[i])
        Y2.append(z)
    print("Y2 = ", Y2)
    
    #Empezamos la elaboración del polinomio interpolador
    H = ddH[0, 1]
    for i in range(1, n):
        H += Y2[i-1] * ddH[0, i+1]
    
    Herm = sp.expand(H)
    print(Herm)
    h = Herm.subs(x, 1.5)
    return h
    
polHermite = pol_Hermite(nds, f, df, ddH)
print(polHermite)

#FUNCIÓN GENERAL PARA HERMITE
from sympy import *
import numpy as np
import sympy as sp
x = symbols("x")
def Hermite(p, nds=[], f=[], df=[]):
    'Dadas las listas que contienen los nodos y los valores de la función y su derivada en esos puntos, la función elabora la tabla de diferencias divididas y el polinomio interpolador de Hermite, mostrando ambos por pantalla. Para terminar, aproxima el polinomio calculado en el punto dado, z, y devuelve ese valor'
    nds2 = [] #Lista para los nodos duplicados
    f2 = [] #Creo una lista con los valores duplicados como los nodos para la primera columna de la tabla de diferencias divididas
    df2 = [] #Hago lo mismo con los valores de la derivada para evitar problemas
    n = len(nds)
    for i in range(n):
        nds2.append(nds[i])
        nds2.append(nds[i]) #Añade dos veces el valor
        f2.append(f[i])
        f2.append(f[i])
        df2.append(df[i])
        df2.append(df[i])
        
    #Creo la tabla de diferencias y le doy a su primera columna los valores de la lista f
    ddH = np.zeros((2*n,2*n))
    ddH[:, 0] = f2
    
    #Completo el resto de la tabla
    for j in range(1, 2*n):
        for i in range((2*n)-j):
            if j==1:
                if nds2[i] == nds2[i+1]:
                    ddH[i, j] = df2[i]
                else:
                    ddH[i, j] = (ddH[i+1,0] - ddH[i,0])/(nds2[i+1]-nds2[i])
            else:
                ddH[i, j] = (ddH[i+1, j-1] - ddH[i, j-1]) / (nds2[i+j] - nds2[i])
                
    #Añadimos en la primera columna los nodos
    np.array(nds2).reshape(-1,1) #convertimos la lista en un array columna para que 
    tddH = np.column_stack((nds2, ddH))
    print("Matrix: ")
    print(tddH)
    
    #Elaboro una lista para los (x-xi)
    Y = []
    m = len(nds2)
    for i in range(m):
        y = (x-nds2[i])
        Y.append(y)
    
    #Elaboro la lista con los (x-xi) multiplicados por todos los anteriores
    Y2 = [Y[0]]
    for i in range(1, len(Y)):
        z = (Y2[i-1]) * (Y[i])
        Y2.append(z)
    
    #Elaboración del polinomio interpolador
    H = tddH[0, 1]
    for i in range(1, m):
        H += Y2[i-1] * tddH[0, i+1]
    
    #Lo pasamos a forma general y sustituimos en el punto
    Herm = sp.expand(H)
    print("Polinomio expresión general: ")
    print(Herm)
    h = Herm.subs(x, p)
    return h

nds = [1.3, 1.6, 1.9]
f = [0.6200860,0.4554022, 0.2818186]
df = [-0.5220232, -0.5698959, -0.5811571]
resultado = Hermite(1.5, nds, f, df)
print(resultado)
help(Hermite)
