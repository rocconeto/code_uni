def anagrama():
    palabra1 = input("Pon la palabra 1: ")
    palabra2 = input("Pon la palabra 2: ")
    lista_p1 = []
    lista_p2 = []
    anagrama = True

    if palabra1.strip().lower() == palabra2.strip().lower():
        print("No son anagramas palabras iguales")
    elif len(palabra1.strip()) != len(palabra2.strip()):
        print("No son anagramas porque no tienen la misma cantidad de letras")

    for i in palabra1:
        lista_p1.append(i)
    for i in palabra2:
        lista_p2.append(i)


    for i in range(len(lista_p1)):
        if lista_p1[i] != lista_p2[-i-1]:
            print(f"{lista_p1[i]} | {lista_p2[-i-1]}")
            anagrama = False

    if anagrama:
        print(f"{palabra1} y {palabra2} son anagramas")
    else:
        print(f"{palabra1} y {palabra2} no son anagramas")
    
