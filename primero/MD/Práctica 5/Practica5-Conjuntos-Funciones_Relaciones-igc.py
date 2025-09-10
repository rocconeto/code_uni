#PRÁCTICA	5: CONJUNTOS, FUNCIONES y RELACIONES 2024-2025

#PARA CADENAS DE CARACTERES

# definición de conjuntos de caracteres	
A = set("abracadabra") #listas no ordenadas de datos distintos (no repetidos)
print(A) #vemos que los elementos repetidos los elimina

# pertenencia
"a" in A #devuelve true or false
"e" in A
"e" not in A

B = set("alacazam") #se define un segundo conjunto de caracteres

# diferencias conjuntistas

A - B #muestra los caracteres que hay en A pero no en B (diferencia de A con B)
B - A #muestra los caracteres que hay en B pero no en A (diferencia de B con A)

# diferencia simétrica
A ^ B #muestra los caracteres diferentes entre ambos conjuntos =B^A

# intersección
A & B #muestra los caracteres comunes =B&A (A∩B)  

# unión
A | B #muestra los caracteres presentes en ambos conjuntos (A∪B)

#complementario
#hay que definir el universo y luego calcular la diferencia del conjunto con U

U=set("xyz")
X=set("x")

U-X #esto es el complementario de X

# conjunto vacío	
V	=	set()
print(V)

#	inclusión	conjuntista e igualdad	
#A = set("abracadabra")
#B = set("alacazam")

A <= B 
not (A <	B)
A > A
A == B #si son iguales
C = set("cabra") #cabra es subconjunto de abracadabra
C < A
C < B

# cardinal o número de elementos	
len(A)
len(B)
len(C)

# añadir o eliminar elementos de un conjunto	
A.add('f')
print(A)
B.discard('c')
print(B)

#	vaciar un conjunto	
B.clear()
B	==	V #es igual al conjunto vacio V creado anteriormente

#PARA TRATAMIENTO DE NÚMEROS (LO MÁS COMÚN), SE RECOMIENDA {} EN LUGAR DE SET

A={1,2,3} #conjunto entre llaves. OPCIÓN MÁS SENCILLA
A

#ojo, porque si lo queremos crear con set hay que tener cuidado

A=set("123") #son números tratados como caracteres
A

# con	sympy tenemos opciones más sofisticadas para conjuntos	

from sympy import FiniteSet, EmptySet

A = EmptySet #Se crea un conjunto vacío
A
A = FiniteSet(1, 2, 3) #Conjunto finito de elementos
A #es lo mismo que cuando lo hemos creado con corchetes, pero posee algunas funcionalidades extra, como
A.powerset() #ojo porque se debe haber creado con FiniteSet, no con set ni con {} porque devolverá error


#	complementarios	e	intervalos	
from sympy import Interval,	S #S es de singleton

Interval(0, 1) #Intervalo cerrado, incluye 0 y 1. [0,1]

0 in Interval(0, 1)
1 in Interval(0, 1)
0.5 in Interval(0, 1)
2 in Interval(0, 1)

#calcula el complementario de un intervalo con respecto al conjunto de los números reales 
#Todos los numeros que no estan en el intervalo
Interval(0, 1).complement(S.Reals)

#Intervalos abiertos o semiabiertos
Interval(0, 1, False, True) #[0, 1) #False y True se refieren a intervalo abierto izda y dcha. Right open
#el programa devuelve por consola R o L, para referirse al lado en el que el intervalo es abierto
Interval(0, 1, True, False)

0 in Interval(0, 1,	False,	True)
1 in Interval(0, 1,	False,	True)

Interval(0,	1,	False,	False)#[0, 1]

Interval(0,	1,	True,	True)#(0, 1)
0 in Interval(0, 1,	True,	True)
1 in Interval(0, 1,	True,	True)


#	producto	cartesiano	
from sympy import ProductSet
I = FiniteSet(1, 2, 3)
F = FiniteSet(1, 2, 3) #conjunto finito de elementos

#	de	forma	alternativa	
lista = [1, 2, 3]	
F	=	FiniteSet(*lista) 
F

#	añadir	elementos	
F = F.union(FiniteSet(0))
F
F = F + FiniteSet(4)
F

P = ProductSet(I, F) # conjunto producto (conjunto formado por todas las posibles 
#combinaciones de elementos de varios conjuntos)
P
I
F

(2,	2)	in	ProductSet(I, F) #Estan ambos en I y F
(2,	0)	in	ProductSet(I, F)
(-1,	0)	in	ProductSet(I, F)
(-1,	1)	in	ProductSet(I, F)


#posibles resultados de dos lanzamientos de una moneda
moneda = FiniteSet("C", "X")
set(moneda**2) #Posibles combinaciones en 2 tiradas

U=ProductSet(moneda, moneda)
U

U = moneda * moneda # tambien se puede representar con el asterisco
U
("C", "C") in U

# número naturales, enteros, reales	
-1	in	S.Naturals #Representa el conjunto de números naturales (enteros no negativos)
-1	in	S.Integers #todos los enteros
0	in	S.Naturals
1	in	S.Naturals
1	in	S.Reals
1.5 in	S.Naturals
1.5	 in S.Reals

from sympy import I #definimos numeros complejos
I #unidad imaginaria, igual a la raíz cuadrada de -1.
I**2
I in S.Complexes

from sympy import oo #infinito
5 in Interval(1, oo)
oo in Interval(1, oo) #no se puede contener al infinito


#FUNCIONES E IMÁGENES

#	Lambda permite construir funciones anónimas (es una función interna)	
f = lambda x: x**2
g = lambda x: x+1
f(g(1)) #composición de funciones
g(f(1)) #composición inversa
gf = lambda x: g(f(x))
gf(1)

#	sympy también permite obtener imágenes de funciones. 

from sympy import Lambda,	ImageSet,	Symbol

x = Symbol("x")

f=x**2
f.subs(x,1)
g=x+1
g.subs(x,1)
f.subs(x,(g.subs(x,1))) #composición de funciones
g.subs(x,(f.subs(x,1))) #composición inversa

#otra forma

def f(x):
    return x**2

def g(x):
    return x+1

f(g(1)) #composición de funciones
g(f(1)) #composición inversa


#	ImageSet (conjunto imagen directa de una función)	

N = S.Naturals
N

cuadrados =	ImageSet(Lambda(x,	x**2),	N) # equivale a {x**2 for x in N}	
4 in cuadrados
5 in cuadrados
-2 in cuadrados
1000**2 in cuadrados #ha creado las imágenes de todos los naturales según la función

# relación	de	orden	léxico-gráfico con vectores (coordenadas)
# Espacio bidimensional. 1º compara componente x. 2º componente y
(1,	2)	<	(1,	3) 
(1,	2)	<	(2,	3)
(1,	2)	<	(1,	1)
(1,	2)	<	(2,	1)

# relación de orden léxico-gráfico con cadenas de caracteres
'a' < 'abracadabra'
'abracadabra' < 'bravo'
'a' < 'A'
'a'	 > 'A'
'a' < 'a'
'a' <= 'a'

#EJERCICIOS: RESOLVER CON PYTHON LOS PROBLEMAS 1, 6, 7 y 17 DEL TEMA 3.
#En el ejercicio 17, calcular para x=2.