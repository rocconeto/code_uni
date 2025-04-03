coches = []

while True:
    coches_juntos = input("Cochce: ")
    coches_juntos_lista = coches_juntos.split("  ")
    for i in coches_juntos_lista:
        coches.append(i.split("_"))

    print(coches)

    if coches_juntos = "x"

for i in coches:
    if len(i) < 3:
        coches.remove(i)

print(coches)