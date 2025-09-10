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

#1
nums = []
for i in range(300, 3001):
    if i % 2 == 0:
        nums.append(i)

suma = 0
for i in nums:
    suma += i
    
print(suma)


#2
resultado = []
for i in range(1, 301):
    if i % 7 == 0 and i**2 > 300 and i**2 < 100000:
        resultado.append(i)
        
print(resultado)

300 <= i**2 <= 100000


#3
valores = []
i = 1200
while i % 137 != 0:
    i += 1
    valores.append(i)

resultado_3 = valores[-1]
print(resultado_3)


#4
#importo random
from random import randint 

#asigno a una variable las opciones en el juego
opciones = ["piedra", "papel", "tijera"]

#el jugador escoge una de las opciones, asegurandonos de que es válida
while True:
    jugador = input("Elige entre piedra, papel o tijera escribiendo una de las opciones: ").lower().strip()
    if jugador in opciones:
        break
    else:
        print(f"{jugador} no está entre las opciones, vuelve a intentarlo")

#el ordenador escoge una de las opciones de forma pseudoaleatoria
maquina = opciones[randint(0, 2)]

#buscamos cual ha sido el resultado


#hace lo mismo que el codigo comentado pero de forma mas eficiente
if jugador == maquina:
    print("empate")
elif (jugador == "piedra" and maquina == "tijera") or (jugador == "tijera" and maquina == "papel") or (jugador == "papel" and maquina == "piedra"):
    print("el jugador ha ganado")
else:
    print("el jugador ha perdido")
    