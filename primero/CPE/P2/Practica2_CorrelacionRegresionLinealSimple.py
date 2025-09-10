#!/usr/bin/env python
# coding: utf-8

# ## PRÁCTICA 2 - Estadística Descriptiva Bivariante. Correlación y regresión lineal simple.
# 
# Objetivos:
# 
# Manejo básico de estadística en Python:
#     
# - Análisis descriptivo de una y dos variables
#     
# - Búsqueda de relación entre variables
#     
# - Realización de análisis estadísticos y generación de informes

# En esta práctica vamos a aprender a relacionar dos variables y analizar la regresión lineal simple entre dos variables. Para ello se va a utilizar el dataset `mpg`, utilizado en la Práctica 1 de estadística descriptiva básica. En esta práctica se va a aplicar la librería de Python `scipy` y sus módulos de correlación y regresión lineal.

# In[16]:


#Importamos las librerías que vamos a utilizar

import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt

from scipy.stats import pearsonr
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import r2_score
from sklearn.metrics import mean_squared_error
import statsmodels.api as sm
import statsmodels.formula.api as smf
from statsmodels.stats.anova import anova_lm


# #### 1. Regresión lineal simple y correlación de dos variables (presión y precipitación, peso y altura, potencia y aceleración). 

# In[17]:


#1a. Generar la matriz de dispersión

mpg = sns.load_dataset('mpg')

#Quitad los NaN que hay en el dataset
mpg.dropna(inplace=True)

plt.scatter(mpg.horsepower, mpg.acceleration)



# In[18]:


#1b. Regresión lineal simple.

# División de los datos en train y test

X = mpg.horsepower
y = mpg.acceleration

X_train, X_test, y_train, y_test = train_test_split(
                                        X.values.reshape(-1,1),
                                        y.values.reshape(-1,1),
                                        train_size   = 0.95,
                                        random_state = 1234,
                                        shuffle      = True
                                    )

# Creación del modelo

modelo = LinearRegression()
modelo.fit(X = X_train.reshape(-1, 1), y = y_train)

X_train = sm.add_constant(X_train, prepend=True)
modelo = sm.OLS(endog=y_train, exog=X_train,)
modelo = modelo.fit()
print(modelo.summary())





# In[19]:


#1c. Correlación entre dos variables

# Correlación lineal entre las dos variables

corr_test = pearsonr(x = mpg.horsepower, y =  mpg.acceleration)
print("Coeficiente de correlación de Pearson: ", corr_test[0])



# In[20]:


#1d. Calculamos el intervalo de confianza para los coeficientes del modelo 

# Intervalos de confianza para los coeficientes del modelo
# ==============================================================================
modelo.conf_int(alpha=0.05)


# In[21]:


#1e. Calculamos las predicciones con intervalo de confianza al 95% de nuestro modelo previamente calculado

# Predicciones con intervalo de confianza del 95%
# ==============================================================================
predicciones = modelo.get_prediction(exog = X_train).summary_frame(alpha=0.05)
predicciones.head(4)


# In[22]:


#1f. Ploteamos nuestro modelo con su linea de regresión


# Predicciones con intervalo de confianza del 95%
# ==============================================================================
predicciones = modelo.get_prediction(exog = X_train).summary_frame(alpha=0.05)
predicciones['x'] = X_train[:, 1]
predicciones['y'] = y_train
predicciones = predicciones.sort_values('x')

# Gráfico del modelo
# ==============================================================================
fig, ax = plt.subplots(figsize=(6, 3.84))

ax.scatter(predicciones['x'], predicciones['y'], marker='o', color = "gray")
ax.plot(predicciones['x'], predicciones["mean"], linestyle='-', label="OLS")
ax.plot(predicciones['x'], predicciones["mean_ci_lower"], linestyle='--', color='red', label="95% CI")
ax.plot(predicciones['x'], predicciones["mean_ci_upper"], linestyle='--', color='red')
ax.fill_between(predicciones['x'], predicciones["mean_ci_lower"], predicciones["mean_ci_upper"], alpha=0.1)
ax.legend();


# #### 2. El dataset `mpg` tiene varias variables sobre las características de un conjunto de coches:
# 
# 1. Haz un gráfico de dispersión con potencia y aceleración. ¿Es razonable predecir la potencia de un coche de esta muestra en función de su aceleración, o viceversa? Justifica tu respuesta. 
# 2. Utilizando la recta de regresión adecuada, ¿qué potencia se prevé para un coche que tenga una aceleración de 10 segundos?
# 3. Utilizando la recta de regresión adecuada, ¿qué aceleración se prevé para un coche que tenga una potencia de 10 Cv?
# 4. Un coche que tenga una aceleración de 17 segundos y una potencia de 130 Cv, ¿qué aceleración tendría un coche con una potencia de 300 Cv?
# 5. Distingamos ahora los coches con cuatro y ocho cilindros. ¿Qué potencia se prevé para un coche con cuatro cilindros? ¿Y para un coche de ocho cilindros? ¿Hay diferencia en la aceleración entre estos dos tipos de cilindros?
# 6. Analiza los residuos de los modelos anteriores
# 7. Identificar y eliminar los puntos extraños (outliers) en el modelo del apartado b, comprobando su efecto en el análisis estadístico. Guardar los datos en un fichero aparte. 
# 8. Repetir los apartados 2), 3), 4), 5) y 6) con el nuevo modelo simplificado, comparando los resultados con el modelo completo.
# 9. Realizar un estudio similar, a partir del modelo completo, para hallar una posible relación entre aceleración y peso. 
# 10. Repetir el apartado 9) con las variables desplazamiento y potencia. 

# In[23]:


#1.- Gráfico de dispersión con potencia y aceleración
sns.scatterplot(data=mpg, x='acceleration', y='horsepower')
plt.title("Relación aceleración-potencia")
plt.xlabel("Aceleración")
plt.ylabel("Potencia")
plt.show()

#Para ver si se puede predecir una con la otra estudiamos 
#el valor del coeficiente de correlación de Pearson
corr, pval = pearsonr(mpg['acceleration'], mpg['horsepower'])
print(f"Coeficiente de correlación de pearson: {corr:.4f}")
print("\nEl coeficiente de correlación de pearson es alto, por tanto si que se podría predecir con cierta precisión el valor de una de las variables con la otra")


# In[24]:


#2.- Utilizando la recta de regresión adecuada, ¿qué potencia se prevé 
# para un coche que tenga una aceleración de 10 segundos?
X = mpg[['acceleration']]
Y = mpg['horsepower']

model = LinearRegression()
model.fit(X, Y)

print(f"Coeficiente: {model.coef_[0]}, Intercepto: {model.intercept_}")

input_df = pd.DataFrame({'acceleration': [10]})
pred_10s = model.predict(input_df)[0]
print(f"Potencia estimada para aceleración una aceleración en 10s: {pred_10s:.0f}cv")


# In[25]:


#3.-Utilizando la recta de regresión adecuada, ¿qué aceleración 
#se prevé para un coche que tenga una potencia de 10 Cv?
X2 = mpg[['horsepower']]
Y2 = mpg[['acceleration']]

model2 = LinearRegression()
model2.fit(X2, Y2)

input_df = pd.DataFrame([[10]], columns=['horsepower'])
pred_10cv = model2.predict(input_df)[0]
print(f"Aceleración estimada para aceleración de un coche de 10cv: {pred_10cv[0]:.2f}s")


# In[26]:


#4.- Aceleración estimada para un coche de 300cv
input_df = pd.DataFrame([[300]], columns=['horsepower'])
pred_300cv = model2.predict(input_df)[0]
print(f"La aceleración que se predice para un coche de 300cv es: {pred_300cv[0]:.2f}s")


# In[29]:


#5.-Distingamos ahora los coches con cuatro y ocho cilindros. ¿Qué 
#potencia se prevé para un coche con cuatro cilindros? ¿Y para un coche 
#de ocho cilindros? ¿Hay diferencia en la aceleración entre estos dos 
#tipos de cilindros?
mpg_cyl = mpg[mpg['cylinders'].isin([4, 8])]
mpg_cyl.boxplot(column='horsepower', by='cylinders')
plt.suptitle('')
plt.title('Distribución de potencia por cilindros')
plt.show()

model_cyl = smf.ols('horsepower ~ C(cylinders)', data=mpg_cyl).fit()
potencia_4 = model_cyl.params['Intercept']
potencia_8 = potencia_4 + model_cyl.params['C(cylinders)[T.8]']

print(f'Potencia prevista para un coche con 4 cilindros: {potencia_4:0f}cv')
print(f'Potencia prevista para un coche con 8 cilindros: {potencia_8:0f}cv')

sns.boxplot(data=mpg[mpg['cylinders'].isin([4,8])], x='cylinders', y='acceleration')
plt.title('Distribución de aceleración por cilindros')
plt.xlabel('cilindros')
plt.ylabel('aceleración')
plt.show()


# In[30]:


#6.-Analiza los residuos de los modelos anteriores
#Modelo Potencia ~ Aceleración
y_pred = model.predict(X)
residuals = Y - y_pred

sns.scatterplot(x=y_pred, y=residuals)
plt.axhline(0, color='red', linestyle='--')
plt.title('Residuos del modelo Potencia ~ Aceleración')
plt.xlabel('Potencia predecida')
plt.ylabel('Residuo')
plt.show()

#Modelo Aceleración ~ Potencia
y2_pred = model2.predict(X2)
residuals2 = Y2.values.flatten() - y2_pred.flatten()

sns.scatterplot(x=y2_pred.flatten(), y=residuals2)
plt.axhline(0, color='red', linestyle='--')
plt.title('Residuos del modelo Aceleración ~ Potencia')
plt.xlabel('Aceleración predecida')
plt.ylabel('Residuo')
plt.show()

#Modelo Cilindros ~ Potencia
y_pred_cyl = model_cyl.predict(mpg_filtrado)
residuals_cyl = mpg['horsepower'] - y_pred_cyl

sns.scatterplot(x=y_pred_cyl, y=residuals_cyl)
plt.axhline(0, color='red', linestyle='--')
plt.title('Residuos del modelo: Potencia ~ Cilindros')
plt.xlabel('Potencia predecida')
plt.ylabel('Residuo')
plt.show()


# In[31]:


#7.-Identificar y eliminar los puntos extraños (outliers) en 
#el modelo del apartado b, comprobando su efecto en el análisis 
#estadístico. Guardar los datos en un fichero aparte.
y_pred = model2.predict(X2)
residuos = Y2.values.flatten() - y_pred.flatten()

#Calculo intercuartílico
q1 = mpg['horsepower'].quantile(0.25)
q3 = mpg['horsepower'].quantile(0.75)
iqr = q3-q1

#Límites para detectar outliers
Q1_hp = mpg['horsepower'].quantile(0.25)
Q3_hp = mpg['horsepower'].quantile(0.75)
IQR_hp = Q3_hp - Q1_hp
lim_inf_hp = Q1_hp - 1.5 * IQR_hp
lim_sup_hp = Q3_hp + 1.5 * IQR_hp

Q1_acc = mpg['acceleration'].quantile(0.25)
Q3_acc = mpg['acceleration'].quantile(0.75)
IQR_acc = Q3_acc - Q1_acc
lim_inf_acc = Q1_acc - 1.5 * IQR_acc
lim_sup_acc = Q3_acc + 1.5 * IQR_acc

mpg_limpio = mpg[
    (mpg['horsepower'] >= lim_inf_hp) & (mpg['horsepower'] <= lim_sup_hp) &
    (mpg['acceleration'] >= lim_inf_acc) & (mpg['acceleration'] <= lim_sup_acc)
]

Q1_hp = mpg['horsepower'].quantile(0.25)
Q3_hp = mpg['horsepower'].quantile(0.75)
IQR_hp = Q3_hp - Q1_hp
lim_inf_hp = Q1_hp - 1.5 * IQR_hp
lim_sup_hp = Q3_hp + 1.5 * IQR_hp

Q1_acc = mpg['acceleration'].quantile(0.25)
Q3_acc = mpg['acceleration'].quantile(0.75)
IQR_acc = Q3_acc - Q1_acc
lim_inf_acc = Q1_acc - 1.5 * IQR_acc
lim_sup_acc = Q3_acc + 1.5 * IQR_acc

mpg_limpio = mpg[
    (mpg['horsepower'] >= lim_inf_hp) & (mpg['horsepower'] <= lim_sup_hp) &
    (mpg['acceleration'] >= lim_inf_acc) & (mpg['acceleration'] <= lim_sup_acc)
]

#Modelo usando usando un nuevo dataset sin outliers
X2_limpio = mpg_limpio[['horsepower']]
Y2_limpio = mpg_limpio[['acceleration']]

model2_limpio = LinearRegression()
model2_limpio.fit(X2_limpio, Y2_limpio)

#Comparar modelos
r2_original = r2_score(Y2, model2.predict(X2))
r2_limpio = r2_score(Y2_limpio, model2_limpio.predict(X2_limpio))
print(f"R2 original: {r2_original:.2f}")
print(f"R2 sin outliers: {r2_limpio:.2f}")


# In[32]:


#8.-Repetir los apartados 2), 3), 4), 5) y 6) con el nuevo modelo simplificado, comparando los resultados con el modelo completo.
#Apartado 2
input_df_10s = pd.DataFrame({'acceleration': [10]})
pred_10s = model.predict(input_df_10s)[0]  

#modelo del apartado 2 pero con los datos de mpg_limpio
X_limpio = mpg_limpio[['acceleration']]
Y_limpio = mpg_limpio['horsepower']

model_limpio = LinearRegression()
model_limpio.fit(X_limpio, Y_limpio)
input_df_10s = pd.DataFrame({'acceleration': [10]})
pred_10s_limpio = model_limpio.predict(input_df_10s)[0]


print(f"Modelo completo: {pred_10s:.2f} cv")
print(f"Modelo limpio: {pred_10s_limpio} cv")

#Apartado 3
input_df_10cv = pd.DataFrame({'horsepower': [10]})
pred_10cv = model2.predict(input_df_10cv)[0][0]
pred_10cv_limpio = model2_limpio.predict(input_df_10cv)[0]

print(f"Modelo completo: {pred_10cv:.1f} s")
print(f"Modelo limpio: {pred_10cv_limpio[0]:.1f} s")

#Apartado 4
input_df_300cv = pd.DataFrame({'horsepower': [300]})
pred_300cv = model2.predict(input_df_300cv)[0][0]
pred_300cv_limpio = model2_limpio.predict(input_df_300cv)[0]

print(f"Modelo completo: {pred_300cv:.1f} s")
print(f"Modelo limpio: {pred_300cv_limpio[0]:.1f} s")

#Apartado 5
# Filtrar coches con 4 y 8 cilindros
mpg_cyl = mpg[mpg['cylinders'].isin([4, 8])]
mpg_limpio_cyl = mpg_limpio[mpg_limpio['cylinders'].isin([4, 8])]

# Modelo completo
model_cyl = smf.ols('horsepower ~ C(cylinders)', data=mpg_cyl).fit()
potencia_4 = model_cyl.params['Intercept']
potencia_8 = potencia_4 + model_cyl.params['C(cylinders)[T.8]']

# Modelo limpio
model_cyl_limpio = smf.ols('horsepower ~ C(cylinders)', data=mpg_limpio_cyl).fit()
potencia_4_limpio = model_cyl_limpio.params['Intercept']
potencia_8_limpio = potencia_4_limpio + model_cyl_limpio.params['C(cylinders)[T.8]']

print(f"Modelo completo - 4 cilindros: {potencia_4:.0f} cv, 8 cilindros: {potencia_8:.0f} cv")
print(f"Modelo limpio - 4 cilindros: {potencia_4_limpio:.0f} cv, 8 cilindros: {potencia_8_limpio:.0f} cv")

# Apartado 6 - Residuos

# Para el modelo completo
residuos = Y.values.flatten() - model.predict(X).flatten()  # Aseguramos que los residuos sean 1D

# Para el modelo limpio
residuos_limpio = Y_limpio.values.flatten() - model_limpio.predict(X_limpio).flatten()  # Aseguramos que los residuos sean 1D

# Graficando residuos para el modelo completo
sns.scatterplot(x=model.predict(X).flatten(), y=residuos)  # Aseguramos que la predicción sea 1D
plt.axhline(0, color='red', linestyle='--')
plt.title('Residuos - Potencia ~ Aceleración (completo)')
plt.show()

# Graficando residuos para el modelo limpio
sns.scatterplot(x=model_limpio.predict(X_limpio).flatten(), y=residuos_limpio)  # Aseguramos que la predicción sea 1D
plt.axhline(0, color='red', linestyle='--')
plt.title('Residuos - Potencia ~ Aceleración (limpio)')
plt.show()

# Aceleración ~ Potencia (residuos)
residuos2 = Y2.values.flatten() - model2.predict(X2).flatten()  # Aseguramos que los residuos sean 1D
residuos2_limpio = Y_limpio.values.flatten() - model_limpio.predict(X_limpio).flatten()  # Aseguramos que los residuos sean 1D

# Graficando residuos para el modelo completo (Aceleración ~ Potencia)
sns.scatterplot(x=model2.predict(X2).flatten(), y=residuos2)  # Aseguramos que la predicción sea 1D
plt.axhline(0, color='red', linestyle='--')
plt.title('Residuos - Aceleración ~ Potencia (completo)')
plt.show()

# Graficando residuos para el modelo limpio (Aceleración ~ Potencia)
sns.scatterplot(x=model_limpio.predict(X_limpio).flatten(), y=residuos2_limpio)  # Aseguramos que la predicción sea 1D
plt.axhline(0, color='red', linestyle='--')
plt.title('Residuos - Aceleración ~ Potencia (limpio)')
plt.show()

# Cilindros ~ Potencia
residuos_cyl = mpg_cyl['horsepower'] - model_cyl.predict(mpg_cyl)
residuos_cyl_limpio = mpg_limpio_cyl['horsepower'] - model_cyl_limpio.predict(mpg_limpio_cyl)

# Graficando residuos para el modelo de Cilindros ~ Potencia (completo)
sns.scatterplot(x=model_cyl.predict(mpg_cyl), y=residuos_cyl)
plt.axhline(0, color='red', linestyle='--')
plt.title('Residuos - Cilindros ~ Potencia (completo)')
plt.show()

# Graficando residuos para el modelo limpio de Cilindros ~ Potencia
sns.scatterplot(x=model_cyl_limpio.predict(mpg_limpio_cyl), y=residuos_cyl_limpio)
plt.axhline(0, color='red', linestyle='--')
plt.title('Residuos - Cilindros ~ Potencia (limpio)')
plt.show()


# In[ ]:


#9.-Realizar un estudio similar, a partir del modelo completo, 
#para hallar una posible relación entre aceleración y peso. 

X_acc = mpg[['acceleration']]  
y_peso = mpg['weight']  

modelo3 = LinearRegression()
modelo3.fit(X_acc, y_peso)

#Predicción y cálculo de residuos
predicciones = modelo3.predict(X_acc)
residuos = y_peso - predicciones

# Graficar los residuos
sns.scatterplot(x=predicciones, y=residuos)
plt.axhline(0, color='red', linestyle='--')
plt.title('Residuos del modelo Peso ~ Aceleración')
plt.xlabel('Peso predicho')
plt.ylabel('Residuo')
plt.show()

# Detectar outliers
Q1 = y_peso.quantile(0.25)
Q3 = y_peso.quantile(0.75)
IQR = Q3 - Q1

# Definir límites para outliers
limite_inferior = Q1 - 1.5 * IQR
limite_superior = Q3 + 1.5 * IQR

outliers = y_peso[(y_peso < limite_inferior) | (y_peso > limite_superior)]

# Eliminar outliers
mpg_sin_outliers = mpg[(y_peso >= limite_inferior) & (y_peso <= limite_superior)]

X_acc_sin_outliers = mpg_sin_outliers[['acceleration']]
y_peso_sin_outliers = mpg_sin_outliers['weight']

# Modelo sin outliers
modelo3_sin_outliers = LinearRegression()
modelo3_sin_outliers.fit(X_acc_sin_outliers, y_peso_sin_outliers)

# Predicción y cálculo de residuos sin outliers
predicciones_sin_outliers = modelo3_sin_outliers.predict(X_acc_sin_outliers)
residuos_sin_outliers = y_peso_sin_outliers - predicciones_sin_outliers

# Gráficar los residuos sin outliers
sns.scatterplot(x=predicciones_sin_outliers, y=residuos_sin_outliers)
plt.axhline(0, color='red', linestyle='--')
plt.title('Residuos del modelo Peso ~ Aceleración')
plt.xlabel('Peso predicho')
plt.ylabel('Residuo')
plt.show()

# Comparar modelos estadisticos con y sin outliers
mse_con_outliers = mean_squared_error(y_peso, predicciones)
r2_con_outliers = r2_score(y_peso, predicciones)

mse_sin_outliers = mean_squared_error(y_peso_sin_outliers, predicciones_sin_outliers)
r2_sin_outliers = r2_score(y_peso_sin_outliers, predicciones_sin_outliers)

print(f"MSE con outliers: {mse_con_outliers}")
print(f"R2 con outliers: {r2_con_outliers}")
print(f"MSE sin outliers: {mse_sin_outliers}")
print(f"R2 sin outliers: {r2_sin_outliers}")


# In[33]:


#10.- Repetir el apartado 9) con las variables desplazamiento y potencia.

X_desplazamiento = mpg[['displacement']]  
y_potencia = mpg['horsepower']  

modelo_desplazamiento_potencia = LinearRegression()
modelo_desplazamiento_potencia.fit(X_desplazamiento, y_potencia)

# Residuos
predicciones_potencia = modelo_desplazamiento_potencia.predict(X_desplazamiento)
residuos_potencia = y_potencia - predicciones_potencia

# Gráficar los residuos
sns.scatterplot(x=predicciones_potencia, y=residuos_potencia)
plt.axhline(0, color='red', linestyle='--')
plt.title('Residuos del modelo Potencia ~ Desplazamiento')
plt.xlabel('Potencia predicha')
plt.ylabel('Residuo')
plt.show()

# Detectar outliers
Q1_potencia = y_potencia.quantile(0.25)
Q3_potencia = y_potencia.quantile(0.75)
IQR_potencia = Q3_potencia - Q1_potencia

# Límites para outliers
limite_inferior_potencia = Q1_potencia - 1.5 * IQR_potencia
limite_superior_potencia = Q3_potencia + 1.5 * IQR_potencia

outliers_potencia = y_potencia[(y_potencia < limite_inferior_potencia) | (y_potencia > limite_superior_potencia)]

# Eliminar outliers 
mpg_sin_outliers_potencia = mpg[(y_potencia >= limite_inferior_potencia) & (y_potencia <= limite_superior_potencia)]

X_desplazamiento_sin_outliers = mpg_sin_outliers_potencia[['displacement']]
y_potencia_sin_outliers = mpg_sin_outliers_potencia['horsepower']

# Modelo sin outliers
modelo_sin_outliers_potencia = LinearRegression()
modelo_sin_outliers_potencia.fit(X_desplazamiento_sin_outliers, y_potencia_sin_outliers)

# Predicción y cálculo de residuos sin outliers
predicciones_sin_outliers_potencia = modelo_sin_outliers_potencia.predict(X_desplazamiento_sin_outliers)
residuos_sin_outliers_potencia = y_potencia_sin_outliers - predicciones_sin_outliers_potencia

# Gráficar de los residuos sin outliers
sns.scatterplot(x=predicciones_sin_outliers_potencia, y=residuos_sin_outliers_potencia)
plt.axhline(0, color='red', linestyle='--')
plt.title('Residuos del modelo Potencia ~ Desplazamiento (sin outliers)')
plt.xlabel('Potencia predicha')
plt.ylabel('Residuo')
plt.show()

# Comparar los resultados estadísticos con y sin outliers
mse_con_outliers_potencia = mean_squared_error(y_potencia, predicciones_potencia)
r2_con_outliers_potencia = r2_score(y_potencia, predicciones_potencia)

mse_sin_outliers_potencia = mean_squared_error(y_potencia_sin_outliers, predicciones_sin_outliers_potencia)
r2_sin_outliers_potencia = r2_score(y_potencia_sin_outliers, predicciones_sin_outliers_potencia)

print(f"MSE con outliers: {mse_con_outliers_potencia}")
print(f"R² con outliers: {r2_con_outliers_potencia}")
print(f"MSE sin outliers: {mse_sin_outliers_potencia}")
print(f"R² sin outliers: {r2_sin_outliers_potencia}")


# #### Realizar un informe con los análisis realizados de cada uno de los apartados anteriores y exportarlo en un fichero .PDF
# 
# - El informe se realizará en un grupos de dos personas analizando los resultados obtenidos en cada uno de los apartados anteriores. Todas las gráficas deberán estar bien maquetadas: título, titulo en los ejes, ejes con un intervalo lógico y leyenda (si es el caso). El código empleado también se deberá incluir. 
# 
# - En el Moodle se encuentra un trabajo tipo para que tengáis de referencia. El archivo incluirá los nombres de todos autores en el siguiente formato:
# 
# - Nombre del archivo: Practica2_ApellidosNombre1_ApellidosNombre2.pdf (extensión obligatoria en .pdf)
# 
# - Se avisará en Moodle la fecha límite de entrega de este informe.

# In[ ]:





# In[ ]:




