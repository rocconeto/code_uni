# -*- coding: utf-8 -*-
"""

"""
#PRÁCTICA 2: PROGRAMACIÓN-BUCLES 2024-2025

# archivo: division.py EJEMPLO DE INTERACCIÓN CON CONSOLA
D = input("Introduzca el dividendo: ")
d = input("Introduzca el divisor: ")
q = int(D) // int(d)
r = int(D) % int(d)
print("El cociente es ",q,"\nEl resto es ",r)

# archivo: opciones.py EJEMPLO DE CONDICIONALES
entrada = input('Elige entre 1 y 2: ')
if entrada == "1":
    print ("Estimado usuario.")
    print ("¿Cómo estás?")
elif entrada == "2":
    print ("¡Python mola!")
    print ("Me encanta el Python.")
else:
    print ("Vuelve a intentarlo.")
    
    
#MÁS EJEMPLOS DE SENTENCIAS, IF, ELIF Y ELSE

#IF

x = 5

if x > 4:
  print("¡La condición era verdadera!") #Esta sentencia se ejecuta
  
#ELSE

y = 3

if y > 4:
  print("¡No voy a imprimir!") #esta sentencia no se ejecuta
else:
  print("¡La condición no era verdadera!") #esta sentencia se ejecuta
  
#ELIF
#solo se ejecutará la primera condición que se evalúe como true

z = 7

if z > 8:
  print("¡No voy a imprimir!") #esta sentencia no se ejecuta
elif z > 5:
  print("¡Yo lo haré!") #esta sentencia se ejecuta
elif z > 6:
  print("¡Tampoco voy a imprimir!") #esta sentencia no se ejecuta
else:
  print("¡Yo tampoco!") #esta sentencia no se ejecuta
  
    
# BUCLE FOR

animales = ['perro', 'gato', 'caballo', 'vaca']
for x in animales:
    print (x)
    
# bucle a partir de un string
mensaje = "Hola"
for i in mensaje:
    print (i)
    
# rangos, o secuencias de números
range(5)
list(_)

range(3, 10)
list(_)

range(4, 10, 2)
list(_)

# bucle for a partir de un rango
for i in range(4):
    print (i)
    
# bucle for en orden inverso
for i in reversed(range(1, 10, 2)):
    print(i)
    
# bucle for a partir de una lista ordenada
canasta = ['manzana', 'naranja', 'manzana', 'pera', 'naranja', 'banana']
for f in sorted(set(canasta)):
    print(f)
    
# listas por comprehensión
cuadrados = [x ** 2 for x in range(10)]
cuadrados

# bucles while
contador = 3
while contador > 0:
    print ("Contador = ", contador)
    contador = contador -1

#while que se para al encontrar un múltiplo de 13 superior a 30
i = 30
while i % 13 != 0:
    i += 1 #esto equivale a i=i+1
    print(i)
    
# sentencia break
# buscamos si hay algún 1 en L, y queremos saber en qué posición
L = [2, 3, 4, 1, 0, 5, 7]
for i in range(len(L)):
    if L[i] == 1:
        break
    # resultado del bucle
print("posición = ",i)

# sentencia continue
# imprimimos los números impares en L, y saltamos los pares
L = [2, 3, 4, 1, 0, 5, 7]
for x in L:
    if x % 2 == 0:
        continue
    else:
        print(x)
    
#NOTA: se aconseja no usar break / continue, y usar en su lugar un bucle while.

# condiciones lógicas que se pueden implementar en bucles (doble condición, una de varias, etc.)
1 < 2 or 3 < 2
1 < 2 and 3 < 2
not (1 < 2 and 3 < 2)
not 1 < 2 and 3 < 2

#Ejemplo

L = [2, 3, 4, 1, 0, 5, 7]
for x in L:
    if x % 2 == 0 or x % 3 == 0:
        continue
    else:
        print(x) 
        
#
        
L = [2, 3, 4, 1, 0, 5, 7]
for x in L:
    if x % 2 == 0 and x % 3 == 0:
        continue
    else:
        print(x)

# números aleatorios (para ej #4)
from random import random, randint

# número real aleatorio en [0, 1]
random()

# número entero aleatorio en [a,b]
randint(1,100)

#EJERCICIOS (para realizar en clase y terminar en casa si se precisa):
    
#1 Escribe un bucle que calcule la suma de todos los números pares entre 300 y 3000.


#2 Mediante un bucle, haz una lista con todos los números enteros entre 1 y 300 que sean
#múltiplos de 7 y cuyo cuadrado esté comprendido entre 300 y 100000. 

        
#3. Usar un bucle while para hallar el menor múltiplo de 137 mayor que 1200.
  

#4. El juego infantil “piedra, papel o tijera” consiste en que dos jugadores eligen
#una de estas tres opciones, y el resultado es que el papel gana a la piedra
#(envolviéndola), la piedra gana a la tijera (rompiéndola), y la tijera gana al
#papel (cortándolo).
#Escribe un código en Python que decida el ganador a partir del valor de dos
#variables jugador (input), ordenador (aleatorio) que pueden tomar los
#valores “piedra”, “papel”, o “tijera”, y que imprima por pantalla un mensaje
#(print) diciendo si el jugador ha ganado o perdido, y la elección efectuada
#por el ordenador.




