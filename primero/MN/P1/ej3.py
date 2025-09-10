from math import sqrt

def ej3(a,b,c):
    sol1 = 0
    sol2 = 0
    soluciones = []
    discriminante = b**2 - 4*a*c
        
    if a == 0 and b == 0:
        return print("No es un ecuación ya que a y b = 0")
    
    elif a == 0:
        sol1 = (-b + sqrt(b**2 - 4*a*c))/(2*a) 
        sol2 = (-b - sqrt(b**2 - 4*a*c))/(2*a) 
            
        soluciones.append(sol1)
        soluciones.append(sol2)
        return soluciones
    
    elif discriminante < 0:
        return print("La ecuación no tiene raices reales")
            
    elif discriminante == 0:
        sol1 = (-b + sqrt(b**2 - 4*a*c))/(2*a) 
        
        soluciones.append(sol1)
        soluciones.append(sol2)
        
        return soluciones
    
    elif b == 0:
        sol1 = (-b + sqrt(b**2 - 4*a*c))/(2*a) 
        sol2 = (-b - sqrt(b**2 - 4*a*c))/(2*a) 
            
        soluciones.append(sol1)
        soluciones.append(sol2)
        return soluciones
        
    elif b > 0:
        sol1 = (2*c)/(-b-sqrt(b**2-4*a*c))
        sol2 = (-b - sqrt(b**2 - 4*a*c))/(2*a) 
        
        soluciones.append(sol1)
        soluciones.append(sol2)
        return soluciones
        
    elif b < 0:
        sol1 = (2*c)/(-b+sqrt(b**2-4*a*c))
        sol2 = (-b + sqrt(b**2 - 4*a*c))/(2*a)
        
        soluciones.append(sol1)
        soluciones.append(sol2)
        return soluciones
                
    
test1 = ej3(1,12345678987,1)    
print(test1)
test2 = ej3(1,-12345678987,1)    
print(test2)
test3 = ej3(1,4,4)    
print(test3)
test4 = ej3(1,4,5)    
print(test4)
