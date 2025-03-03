import sympy as sp
import numpy as np
import matplotlib.pyplot as plt

def lagrange_basis(x, nodes):
    """
    Calcula los polinomios base de Lagrange l_i(x) para los nodos dados.
    """
    basis = []
    n = len(nodes)
    for i in range(n):
        L = 1
        for j in range(n):
            if i != j:
                L *= (x - nodes[j]) / (nodes[i] - nodes[j])
        basis.append(sp.simplify(L))
    return basis

def lagrange_interpolator(x, nodes, values):
    """
    Calcula el polinomio interpolador de Lagrange para una función dada en los nodos especificados.
    """
    basis = lagrange_basis(x, nodes)
    P = sum(values[i] * basis[i] for i in range(len(nodes)))
    return sp.simplify(P)

def approximate_value(p, nodes, values):
    """
    Calcula el valor aproximado de f en el punto p usando interpolación de Lagrange.
    """
    x = sp.Symbol('x')
    P = lagrange_interpolator(x, nodes, values)
    return P.subs(x, p)

# Definir los nodos y la función
nodes = [2, 5/2, 4]
values = [1/n for n in nodes]

# Construcción del polinomio interpolador
x = sp.Symbol('x')
P2 = lagrange_interpolator(x, nodes, values)
print("Polinomio interpolador de Lagrange:", P2)

# Aproximación de f(3)
approx_f3 = approximate_value(3, nodes, values)
print("Aproximación de f(3):", approx_f3)

# Graficar la función original y el polinomio interpolador
P2_func = sp.lambdify(x, P2, 'numpy')
f_func = sp.lambdify(x, 1/x, 'numpy')

x_vals = np.linspace(1.5, 4.5, 400)
plt.figure(figsize=(8, 6))
plt.plot(x_vals, f_func(x_vals), label='f(x) = 1/x', linewidth=2, color='black')
plt.plot(x_vals, P2_func(x_vals), label='Interpolación de Lagrange', linestyle='dashed')
plt.scatter(nodes, values, color='red', label='Nodos')

plt.axhline(0, color='gray', linewidth=0.5)
plt.axvline(0, color='gray', linewidth=0.5)
plt.legend()
plt.xlabel('x')
plt.ylabel('f(x)')
plt.title('Interpolación de Lagrange para f(x) = 1/x')
plt.grid()
plt.show()
