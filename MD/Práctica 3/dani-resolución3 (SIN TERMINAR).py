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
from sympy.solvers.diophantine import diophantine
from sympy import symbols
x, y = symbols("x, y", integer=True)

def resolver(n, r, m):
    print(f"La solución general como ec.diofántica de {n}x = r mod({m}) es:", diophantine(n*x-m*y-r))
    
#cada lista corresponde a una congruencia siendo [0] el numero que multiplica
# a x, [1] el resto y [2] el módulo
congruencias = [
        [6, 0, 15],
        [4, 1, 15],
        [6, 3, 15],
        [6, 5, 15],
        [6, 1, 15],
        [4, 0, 15],
        [4, 7, 15],
        [6, 9, 15]
    ]

for i in congruencias:
    resolver(n=i[0], r=i[1], m=i[2])
    
test = list(diophantine(6*x-15*y-0))
type(test[0])
#13 Halla todas las soluciones del sistema de congruencias
from sympy.solvers.diophantine import diophantine
from sympy import symbols

x, y = symbols("x, y", integer=True)

def get_x(n, r, m):
    ec = diophantine(n*x-m*y-r)
    ec = list(ec)
    return ec[0][0]

def resol_sist(sistema):
    resultados_indp = []
    for i in sistema:
        resultados_indp.append(get_x(i[0], i[1], i[2]))
    return print(resultados_indp)
    

#cada lista corresponde a una congruencia siendo [0] el numero que multiplica
# a x, [1] el resto y [2] el módulo
sist = [
        [1, 1, 2],
        [1, 2, 3],
        [1, 3, 5],
        [1, 4, 11]
    ]

resol_sist(sist)




#14
#15