import sympy as sp
import numpy as np
import matplotlib.pyplot as plt

# Definir la variable y la función
x = sp.Symbol('x')
f = 1/x

# Nodos dados
nodes = [2, 5/2, 4]
values = [1/n for n in nodes]

# Calcular el polinomio interpolador de Lagrange
def lagrange_interpolator(x, nodes, values):
    n = len(nodes)
    P = 0
    for i in range(n):
        L = 1
        for j in range(n):
            if i != j:
                L *= (x - nodes[j]) / (nodes[i] - nodes[j])
        P += values[i] * L
    return sp.simplify(P)

P2 = lagrange_interpolator(x, nodes, values)
print("Polinomio interpolador de Lagrange:", P2)

# Evaluar el polinomio en x = 3
f3_approx = P2.subs(x, 3)
print("Aproximación de f(3):", f3_approx)

# Convertir el polinomio en función de numpy
P2_func = sp.lambdify(x, P2, 'numpy')
f_func = sp.lambdify(x, f, 'numpy')

# Crear valores de x para graficar
x_vals = np.linspace(1.5, 4.5, 400)

# Graficar la función original y el polinomio interpolador
plt.figure(figsize=(8, 6))
plt.plot(x_vals, f_func(x_vals), label='f(x) = 1/x', linewidth=2, color='black')
plt.plot(x_vals, P2_func(x_vals), label='Interpolación de Lagrange', linestyle='dashed')
plt.scatter(nodes, values, color='red', label='Nodos')

# Configuración del gráfico
plt.axhline(0, color='gray', linewidth=0.5)
plt.axvline(0, color='gray', linewidth=0.5)
plt.legend()
plt.xlabel('x')
plt.ylabel('f(x)')
plt.title('Interpolación de Lagrange para f(x) = 1/x')
plt.grid()
plt.show()