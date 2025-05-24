# -*- coding: utf-8 -*-
"""
Created on Wed Feb 19 14:05:43 2025

@author: uva
"""

#EJERCICIO 3 - DEFINIR UNA FUNCIÓN QUE CALCULE LAS RAÍCES REALES DE UNA ECUACIÓN DE SEGUNDO GRADO
def raices_segundo_grado(a, b, c):
    import math as mt
    '''calcula las raices de una ecuación de segundo grado siendo a y b los coeficientes de x y c el termino independiente'''
    d = (b**2) - 4*a*c  #Calcula el discriminante(el interior de la raiz cuadrada)
    sol = []
    if a == 0 and b == 0:
        print("No se trata de una ecución.", sol)
    elif a == 0:
        result = c/b
        print("Se trata de una ecuación de primer grado.")
        print("Su solución es: ", result)
    elif b == 0:
        result1 = mt.sqrt(c/a)
        result2 = -result1
        sol.append(result1)
        sol.append(result2)
        print("Las soluciones de la ecuación son: ", sol)
    elif d < 0:
        print("La ecuación no tiene raices reales.")
    elif d == 0:
        print("La ecuación posee una raíz doble")
        if b > 0:
            sol = (-b-mt.sqrt((b**2)-4*a*c))/2*a
            print("La solución es: ", sol)
        elif b < 0:
            sol = (-b+mt.sqrt((b**2)-4*a*c))/2*a
            print("La solución es: ", sol)
    elif b > 0:
        sol1 = (-b-mt.sqrt((b**2)-4*a*c))/2*a
        sol2 = (2*c)/(-b-mt.sqrt((b**2)-4*a*c))
        sol.append(sol1)
        sol.append(sol2)
        print("Las soluciones de la ecuación son: ", sol)
    elif b < 0:
        sol1 = (-b+mt.sqrt((b**2)-4*a*c))/2*a
        sol2 = (2*c)/(-b+mt.sqrt((b**2)-4*a*c))
        sol.append(sol1)
        sol.append(sol2)
        print("Las soluciones de la ecuación son: ", sol)
    

raices_segundo_grado(1, 12345678987, 1)
raices_segundo_grado(1, -12345678987, 1)
raices_segundo_grado(1, -4, 4)
raices_segundo_grado(1, -4, 5)

#Ejemplo para comprobar que todos los casos restantes funcionan correctamente
raices_segundo_grado(0, 0, 4)
raices_segundo_grado(0, 1, 4)
raices_segundo_grado(1, 0, 4)
raices_segundo_grado(2, 1, 4)

#EJERCICIO 1
nums = []
contador = 0
for i in range(100):
    j = i + 1
    if j%5 == 0:
        k = j**2
        if k >= 200 and k <= 5000:
            nums.append(j)
            contador += 1

print(nums)
print("Cantidad de elementos en la lista (contador): ", contador)
print("Longitud de la lista: ", len(nums))
if len(nums) == contador:
    print("El contador coincide con la longitud de la lista.")
else:
    print("El contador y la longitud de la lista no coinciden.")
    
#EJERCICIO 2
suma = 0
for i in range(100, 201):
    if i%2 != 0:
        suma += i

print("La suma de los impares entre 100 y 200 es ", suma)