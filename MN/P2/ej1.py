# Usando la librería sympy de python, calcula los tres primeros polinomios de Taylor (hasta
# grado 5) para la función f (x) = sen(x) en x = 0. Haz una gráfica conjunta de los tres polinomios y la
# función original para comprobar visualmente el grado de aproximación de cada uno de ellos.


#version chatGPT (funciona)
import sympy as sp
import numpy as np
import matplotlib.pyplot as plt

# Definir la variable y la función
x = sp.Symbol('x')
f = sp.sin(x)

# Calcular los polinomios de Taylor de orden 1, 3 y 5 en x = 0
taylor_1 = sp.series(f, x, 0, 2).removeO()
taylor_3 = sp.series(f, x, 0, 4).removeO()
taylor_5 = sp.series(f, x, 0, 6).removeO()

# Convertir los polinomios a funciones utilizables en numpy
t1 = sp.lambdify(x, taylor_1, 'numpy')
t3 = sp.lambdify(x, taylor_3, 'numpy')
t5 = sp.lambdify(x, taylor_5, 'numpy')
sin_func = sp.lambdify(x, f, 'numpy')

# Crear valores de x para graficar
x_vals = np.linspace(-2*np.pi, 2*np.pi, 400)

# Graficar la función original y las aproximaciones
plt.figure(figsize=(8, 6))
plt.plot(x_vals, sin_func(x_vals), label='sin(x)', linewidth=2, color='black')
plt.plot(x_vals, t1(x_vals), label='Taylor grado 1', linestyle='dashed')
plt.plot(x_vals, t3(x_vals), label='Taylor grado 3', linestyle='dashed')
plt.plot(x_vals, t5(x_vals), label='Taylor grado 5', linestyle='dashed')

# Configuración del gráfico
plt.axhline(0, color='gray', linewidth=0.5)
plt.axvline(0, color='gray', linewidth=0.5)
plt.legend()
plt.xlabel('x')
plt.ylabel('f(x)')
plt.title('Aproximaciones de Taylor de sin(x) en x=0')
plt.grid()
plt.show()
