# -*- coding: utf-8 -*-
"""
Created on Fri May 16 17:32:40 2025

@author: Miguel raúl y David
"""
from sympy.matrices import *
A = Matrix([[2, 3, 4, 5], [6, 15, 19, 23], [8, 42, 60, 70], [12, 60, 1, 17]])
R = Matrix([5, 30, 98, 144])
def subrutinas(A, R):
    """Dadas las matrices A y R, siendo R la de los resultados, resuelve el sistema por las subrutinas
    de factorización, progresiva y regresiva"""
    A = A.evalf()
    R = R.evalf()
    n = A.rows
    
    #Creamos las matrices necesarias
    L = zeros(n, n)
    U = zeros(n,n)
    
    #Factorización
    for i in range(n):
        #Matriz U
        for j in range(i, n):
            suma = sum(L[i, k] * U[k, j] for k in range(i))
            U[i, j] = (A[i, j] - suma).evalf()
        
        #Matriz L
        L[i, i] = 1.0
        for j in range(i + 1, n):
            suma = sum(L[j, k] * U[k, i] for k in range(i))
            L[j, i] = ((A[j, i] - suma) / U[i, i]).evalf()
    
    #Progresiva
    y = zeros(1, n)
    for i in range(n):
        suma = sum(L[i, j] * y[j] for j in range(i))
        y[i] = (R[i] - suma).evalf()
    
    #Regresiva
    x = zeros(1, n)
    for i in reversed(range(n)):
        suma = sum(U[i, j] * x[j] for j in range(i + 1, n))
        x[i] = ((y[i] - suma) / U[i, i]).evalf()
    
    return L, U, y, x
        
L, U, x, y = subrutinas(A, R)

def inversa(A, L, U):
    """Dada una matriz A calcula la inversa y su determinante después de haber realizado la resolución
    del sistema por subrutinas. L y U es los resultados de la subrutina de facctorización.
    Para calcular det(A) usa que det(A) = det(L)*det(U)"""
    #Calculo de la inversa
    #Construimos la matrices necesarias
    n = A.rows
    I = eye(n)
    A1 = zeros(n,n) #Matriz inversa
    
    #Resolvemos los sistemas Ly = ej y Uxj = y
    for c in range(n):
        R = I[:, c]
        y = zeros(n, 1)
        for i in range(n):
            suma = sum(L[i, j] * y[j] for j in range(i))
            y[i] = (R[i] - suma).evalf()
        x = zeros(n, 1)
        for i in reversed(range(n)):
            suma = sum(U[i, j] * x[j] for j in range(i + 1, n))
            x[i] = ((y[i] - suma) / U[i, i]).evalf()
        A1[:, c] = x
    
    #Calculo del determinante
    #det(L) = 1 por que su diagonal son 1, det(U) son los elementos de la diagonal porque es triangular
    dA = 1
    for i in range(n):
        d = U[i, i]
        dA = dA * d
    
    return dA, A1

dA, A1 = inversa(A, L, U)
dA

#Comprobamos que la matriz inversa es correcta
C = A * A1
print(C)

