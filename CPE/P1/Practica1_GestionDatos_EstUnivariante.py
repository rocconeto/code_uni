#Importamos las librerías que vamos a utilizar
import numpy  as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

#1a. Creamos una lista de datos para la Estatura y el Sexo correspondiente
estatura = [1.62, 1.71, 1.57, 1.61, 1.80, 1.91, 1.58, 1.63, 1.62, 1.70, 1.75, 1.68, 1.54, 1.79, 1.72, 1.68, 1.90, 1.69, 1.73, 1.85, 1.60, 1.60, 1.62, 1.77, 1.71, 1.89, 1.92, 1.65, 1.99, 2.05, 1.41, 1.67, 1.93, 1.55, 2.04, 1.73, 1.80, 1.83, 1.75, 1.66, 1.93, 1.85, 1.84, 1.68, 1.63, 1.75, 1.77, 1.84, 1.85, 1.90, 2.00, 1.83, 2.01, 1.82, 1.65, 1.72, 1.68, 1.73, 1.54, 1.65]
sexo = [2, 1, 2, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2, 2, 1, 1, 2, 2, 2]

#1b. Reemplazamos el valor numérico por texto
for i in range(len(sexo)):
    if int(sexo[i]) == 1:
        sexo[i] = "Hombre"
    else:
        sexo[i] = "Mujer"
    
print(sexo)

#1c. Generamos un DataFrame con pd.DataFrame()
df = pd.DataFrame({'Estatura': estatura,
                  'Sexo': sexo})
print(df)

#2a. Realizamos el resumen estadístico. PISTA: hay una función que genera las 
#    variables básicas que necesitamos. 
df.groupby(['Sexo']).describe()

#2b. Generamos una tabla de frecuencias. 
df.groupby(['Sexo']).agg(frequency=("Sexo", "count"))

#2c. Generamos un gráfico de dispersión.
plt.scatter(x=df.Sexo, y=df.Estatura)
plt.title('Gráfico de Dispersión')
plt.xlabel('Eje X')
plt.ylabel('Eje Y')

#2d. Generamos un gráfico de cajas y bigotes.259629529252
sns.boxplot(data=df, x='Sexo', y='Estatura')

df.hist(by='Sexo')

#3a. Realizamos el resumen estadístico. PISTA: hay una función que genera las 
#    variables básicas que necesitamos. 
print(df['Estatura'].describe())

#3b. Generamos una tabla de frecuencias. 
print(df['Sexo'].value_counts())

#3c. Generamos un diagrama de barras. 
plt.bar(df.Sexo,df.Estatura)

#3d. Generamos un diagrama de sectores.
sect = df.groupby(['Sexo']).agg(frequency=("Sexo", "count"))
#plt.pie(sect.frequency,labels=sect.index) Esto es el codigo para que esté junto
desfase=(0, 0.1)
plt.pie(sect.frequency,labels=sect.index,autopct="%0.1f %%", explode = desfase)

#4a. Halla la estatura media por sexo
media = df.groupby(['Sexo']).mean()
print(media)

#4b. Genera los histogramas de alturas por sexo y poder compararlos. 
df.hist(by='Sexo')

#4c. Manipula el gráfico anterior en la forma que desees para poder ser presentado. 
df.hist(by='Sexo', color='green')

#5x. Carga el dataset mpg. 
mpg = sns.load_dataset('mpg')

#5a. Genera una tabla de frecuencias, un diagrama de barras y un diagrama de sectores de la variable
#    'model_year' (año de fabricación)
"""Tabla de frecuencias"""
tabla_frecuencias = pd.DataFrame({
    'model_year': mpg['model_year'].value_counts().index,
    'frecuencia': mpg['model_year'].value_counts().values
}).sort_values(by='model_year')

tabla_frecuencias

"""Diagrama de barras"""
plt.figure(figsize=(10,5))
sns.barplot(x=tabla_frecuencias['model_year'], y=tabla_frecuencias['frecuencia'], palette="viridis")
plt.xlabel("Año del modelo")
plt.ylabel("Frecuencia")
plt.title("Diagrama de barras de model_year")
plt.show()

"""Diagrama de sectores"""
plt.figure(figsize=(8,8))
plt.pie(tabla_frecuencias['frecuencia'], labels=tabla_frecuencias['model_year'], autopct='%1.1f%%', colors=sns.color_palette("viridis", len(tabla_frecuencias)))
plt.title("Diagrama de sectores de model_year")
plt.show()

#5b. Genera una tabla de frecuencias de la variable 'mpg'. 
#    ¿Qué porcentaje de coches consumenos menos de 22 mpg (usa intervalos de 22)?
intervalos = np.arange(0, max(mpg['mpg']) + 22, 22)
mpg['mpg_intervalo'] = pd.cut(mpg['mpg'], bins=intervalos, right=False)
tabla_frecuencia_mpg = mpg['mpg_intervalo'].value_counts().sort_index()

print("Tabla de frecuencias de mpg:")
print(tabla_frecuencia_mpg)

# Calcular el porcentaje de coches que consumen menos de 22 mpg
total_coches = len(mpg)
coches_menos_22 = tabla_frecuencia_mpg.loc[tabla_frecuencia_mpg.index[0]]
porcentaje_menos_22 = (coches_menos_22 / total_coches) * 100

print(f"Porcentaje de coches que consumen menos de 22 mpg: {porcentaje_menos_22:.2f}%")

#5c. Genera un box-and-whisker plot de alguna de las variables cuantitativas y 
#    comenta sus características más importantes (concentraciones, asimetrías, atípicos...)
plt.figure(figsize=(8,6))
sns.boxplot(y=mpg['mpg'])
plt.ylabel("Millas por galón (mpg)")
plt.title("Box-and-whisker de mpg")
plt.show()

#    BONUS: hay un tipo de gráfico que representa también la función de distribución. Intenta encontrarlo. 
plt.figure(figsize=(8,6))
sns.ecdfplot(mpg['mpg'], color='blue')
plt.xlabel("mpg")
plt.ylabel("Probabilidad acumulada")
plt.title("Función de distribución acumulada de mpg")
plt.show()

#5d. Genera un polígono de frecuencias RELATIVAS acumuladas de la variable 'horsepower' (potencia - caballos).
mpg = mpg.dropna(subset=['horsepower']) 

# Frecuencia acumulada relativa
tabla_frecuencia_hp = mpg['horsepower'].value_counts().sort_index().cumsum()
tabla_frecuencia_hp_relativa = tabla_frecuencia_hp / tabla_frecuencia_hp.max()

# Graficar las frecuencias relativas acumuladas
plt.figure(figsize=(8,6))
plt.plot(tabla_frecuencia_hp_relativa.index, tabla_frecuencia_hp_relativa.values, marker='o', linestyle='-', color='pink')
plt.xlabel("Caballos de fuerza (horsepower)")
plt.ylabel("Frecuencia relativa acumulada")
plt.title("Polígono de frecuencias relativas acumuladas de horsepower")
plt.grid()
plt.show()

#5e. Utilizando la figura previa, di aproximadamente la proporción de vehículos que tienen una
#    potencia menor o igual a 100 CV.
# Obtenemos la frecuencia relativa acumulada para los coches con 100 cv
frecuencia_relativa_100cv = tabla_frecuencia_hp_relativa.loc[100]

# Calcular el número de vehículos con 100 cv o menos
numero_vehiculos_100cv_o_menos = frecuencia_relativa_100cv * len(mpg)
print(f"Número de vehículos con 100 cv o menos: {numero_vehiculos_100cv_o_menos:.0f}")