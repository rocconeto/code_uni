#Práctica 3. Ejercicios

#1 Expresión binaria, octal y hexadecimal de 12345 y 177130

# 12345
bin(12345)
oct(12345)
hex(12345)

#177130
bin(177130)
oct(177130)
hex(177130)

#3 Factorización en primos de los siguientes enteros:
import math as mt
from sympy import factorint
fact_10 = str(mt.factorial(10))

nums = ["39", "81", "88", "011", "126", "143", "289", "512", "729", "899", "1001", "1111", "909090", fact_10]
for i in nums:
    i = int(i)
    print(f"{i} ->", factorint(i))
    
#4 Utiliza el algoritmo de Euclides para mcd(1529, 14038) y mcd(11111, 111111)
from sympy import gcd

print(gcd(1529, 14038))
print(gcd(11111, 111111))

#5 Expresa el mcd de cada uno de los pares de enteros como combinación lineal (entera) de ellos:    
pares = [
            [56, 27],
            [721, 448],
            [3454, 4666]
        ]

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

for i in pares:
    resultados = egcd(i[0], i[1])
    print(f"{i[0]}·({resultados[1]}) + {i[1]}·({resultados[2]}) = {resultados[0]}")
    
#9 Calcula la función Phi de Euler para todos los enteros del problema 3
from sympy import totient
import math as mt
fact_10 = str(mt.factorial(10))
nums = ["39", "81", "88", "011", "126", "143", "289", "512", "729", "899", "1001", "1111", "909090", fact_10]

for i in nums:
    phi = totient(int(i))
    print(f"Aplicando la función Phi de Euler para {i}, se obtiene -> {phi}")

#10 Calcula el inverso de 13 mod(17) y mod(2436)
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

def modInverse(a,m):
    L = egcd(a,m)
    assert L[0] == 1 
    return L[1] % m 

modInverse(13, 17)
modInverse(13, 2436)

#12 Resolver las congruencias modulares:
def extended_euclidean(a, b):
    """
    Algoritmo extendido de Euclides.
    Devuelve una tupla (gcd, x, y) tal que gcd es el máximo común divisor de a y b,
    y x, y son los coeficientes que satisfacen la identidad de Bézout: ax + by = gcd(a, b).
    """
    if b == 0:
        return a, 1, 0
    else:
        gcd, x1, y1 = extended_euclidean(b, a % b)
        x = y1
        y = x1 - (a // b) * y1
        return gcd, x, y

def solve_linear_congruence(a, b, m):
    """
    Resuelve la congruencia lineal ax === b (mod m).
    Devuelve una lista con las soluciones, o una lista vacía si no hay soluciones.
    """
    # Paso 1: Calculamos gcd(a, m) y los coeficientes x e y usando el algoritmo extendido de Euclides
    gcd, x, _ = extended_euclidean(a, m)

    # Paso 2: Verificamos si la congruencia tiene solución
    if b % gcd != 0:
        return []  # No hay soluciones

    # Paso 3: Reducimos el problema dividiendo entre gcd
    a_reduced = a // gcd
    b_reduced = b // gcd
    m_reduced = m // gcd

    # Paso 4: Encontramos una solución particular
    x0 = (x * b_reduced) % m_reduced

    # Paso 5: Generamos todas las soluciones
    solutions = [(x0 + k * m_reduced) % m for k in range(gcd)]
    return solutions

# Ejemplo de uso
print("Resuelve la congruencia lineal ax ≡ b (mod m)")
a = int(input("Introduce a: "))
b = int(input("Introduce b: "))
m = int(input("Introduce m: "))

solutions = solve_linear_congruence(a, b, m)

if solutions:
    print(f"Las soluciones son: {solutions}")
else:
    print("No hay soluciones.")





#14
#15