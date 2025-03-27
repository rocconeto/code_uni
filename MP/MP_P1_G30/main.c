/*  Asigantura: Metodología de la programación Curso: 1
    Tarea que realiza el programa: Gestión de clientes, habitaciones y reservas de un hotel
    Alumno 1: Atanasov Angelov, Daniel
    Alumno 2: Sanz Tomé, Raúl
    Grupo de laboratorio: 30
    Fecha: 24/02/2025 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define MAX_CLIENTES 100

typedef struct{
    int dni;
    char nombre[50];
    int tipo;
    char reservas[7];
}Clientes;

void menu_princ();
void gest_clientes();
void gest_hab();
void gest_reservas();

int main()
{
    Clientes clientes[MAX_CLIENTES];
    setlocale(LC_ALL, "spanish");
    printf("\n\t¡Bienvenido a la aplicación GEST_HOTEL!\n");
    printf("\n--------------------------------------------------------\n\n");
    system("pause");
    system("cls");

    //Cargamos los datos de los ficheros
    int cont_clientes = 0;
    FILE *fich;
    fich = fopen("clientes.dat", "r");
    if(fich == NULL){
        printf("Error al abrir el fichero");
        exit(1);
    }else{
        while (fscanf(fich, "%d%s%d%s", &clientes[cont_clientes].dni, &clientes[cont_clientes].nombre, &clientes[cont_clientes].tipo, &clientes[cont_clientes].reservas) == 4){
            cont_clientes ++;
            if(cont_clientes >= MAX_CLIENTES){
                break;
            }
        }
        fclose(clientes);
    }

    menu_princ();
    return 0;
}

/********************************************************************************/
/*Subprograma:              Menú principal                                      */
/*Tipo:                     Procedimiento (función tipo void)                   */
/*Parámetros de entrada:    ---                                                 */
/*Parámetros de salida:     ---                                                 */
/*Prerrequisitos:           ---                                                 */
/*Objetivo:                 Muestra por pantalla el menú principal del programa */
/********************************************************************************/
void menu_princ(Clientes clientes[], int cont_clientes){
    int opc;
    do{
        printf("--------------------------------------------------------\n");
        printf("\n\t\tMENÚ PRINCIPAL\n");
        printf("\n------------------------------------------------------\n");
        printf("\n\t1.- Gestión de Clientes\n");
        printf("\n\t2.- Gestión de Habitaciones\n");
        printf("\n\t3.- Gestión de Reservas\n");
        printf("\n\t4.- Informes Económicos\n");
        printf("\n\t5.- Importar Habitaciones desde Fichero\n");
        printf("\n\t0.- Salir\n");

        printf("\n\tSelecciona una opción: ");
        scanf("%d", &opc);

        system("pause");
        system("cls");

        switch(opc){
            case 1:
                gest_clientes();
                break;
            case 2:
                gest_hab();
                break;
            case 3:
                gest_reservas();
                break;
            case 4:
                printf("\n\tInformes\n\n");
                system("pause");
                system("cls");
                break;
            case 5:
                printf("\n\tImportar\n\n");
                system("pause");
                system("cls");
                break;
            case 0:
                printf("\n\tGuardando los datos...\n");
                printf("\n--------------------------------------------------------\n\n");

                //Guarda los cambios realizados en los registros
                FILE *fich;
                fich = fopen("clientes.dat", "w");
                if(fich == NULL){
                    printf("Error al guardar los clientes.");
                    return 1;
                }
                for(int i=0; i<cont_clientes; i++){
                    fprintf(fich, "\n\t%d%s%d%s\n", &clientes[i].dni, &clientes[i].nombre, &clientes[i].tipo, &clientes[i].reservas);
                }

                fclose(fich);
                printf("\n\tDatos guardados correctamente.\n");
                printf("¡Gracias por usar nuestro programa!");

                break;
        }
    }while(opc != 0);
}

/********************************************************************************************/
/*Subprograma:              Gestión clientes                                                */
/*Tipo:                     Procedimiento (función tipo void)                               */
/*Parámetros de entrada:    ---                                                             */
/*Parámetros de salida:     ---                                                             */
/*Prerrequisitos:           ---                                                             */
/*Objetivo:                 Se encarga de todas las opciones relacionadas con los clientes  */
/********************************************************************************************/
void gest_clientes(){
    void submenu_cl();

    submenu_cl();

    system("cls");
}

/****************************************************************************/
/*Subprograma:              Menú del subprograma                            */
/*Tipo:                     Procedimiento (función tipo void)               */
/*Parámetros de entrada:    ---                                             */
/*Parámetros de salida:     ---                                             */
/*Prerrequisitos:           ---                                             */
/*Objetivo:                 Muestra por pantalla el menú del subprograma    */
/****************************************************************************/
void submenu_cl(){
    int opc;
    do{
        printf("\n------------------------------------------------------\n");
        printf("\n\t\tGESTIÓN DE CLIENTES\n");
        printf("\n------------------------------------------------------\n");
        printf("\n\t1.- Alta\n");
        printf("\n\t2.- Baja\n");
        printf("\n\t3.- Modificación\n");
        printf("\n\t4.- Consulta\n");
        printf("\n\t5.- Listado General\n");
        printf("\n\t6.- Listado por Categoría\n");
        printf("\n\t0.- Salir\n");

        printf("\n\tSelecciona una opción: ");
        scanf("%d", &opc);

        system("pause");
        system("cls");

        switch(opc){
            case 1:
                printf("\n\tAltas\n\n");
                system("pause");
                system("cls");
                break;
            case 2:
                printf("\n\tBajas\n\n");
                system("pause");
                system("cls");
                break;
            case 3:
                printf("\n\tModificación\n\n");
                system("pause");
                system("cls");
                break;
            case 4:
                printf("\n\tConsulta\n\n");
                system("pause");
                system("cls");
                break;
            case 5:
                printf("\n\tListado\n\n");
                system("pause");
                system("cls");
                break;
            case 6:
                printf("\n\tListado-categoria\n\n");
                system("pause");
                system("cls");
                break;
            case 0:
                break;
        }
    }while(opc != 0);
}

/************************************************************************************************/
/*Subprograma:              Gestión habitaciones                                                */
/*Tipo:                     Procedimiento (función tipo void)                                   */
/*Parámetros de entrada:    ---                                                                 */
/*Parámetros de salida:     ---                                                                 */
/*Prerrequisitos:           ---                                                                 */
/*Objetivo:                 Se encarga de todas las opciones relacionadas con las habitaciones  */
/************************************************************************************************/
void gest_hab(){
    void submenu_hab();

    submenu_hab();
    typedef struct {
        char codigo[10];
        char tipo[20];
        float precio;
        int ocupada;
    } Habitacion;

    Habitacion habitaciones[MAX_HABITACIONES];
    int total_habitaciones = 0;

    void alta_habitacion();
    void baja_habitacion();
    void modificar_habitacion();
    void consultar_habitacion();
    void listar_habitaciones();
    char *obtener_fecha_actual();

    int main() {
        int opcion;
        do {
            printf("\n--- GESTIÓN DE HABITACIONES ---\n");
            printf("1. Alta de habitación\n");
            printf("2. Baja de habitación\n");
            printf("3. Modificación de habitación\n");
            printf("4. Consulta de habitación\n");
            printf("5. Listado general\n");
            printf("0. Salir\n");
            printf("Seleccione una opción: ");
            scanf("%d", &opcion);

            switch (opcion) {
                case 1: alta_habitacion(); break;
                case 2: baja_habitacion(); break;
                case 3: modificar_habitacion(); break;
                case 4: consultar_habitacion(); break;
                case 5: listar_habitaciones(); break;
                case 0: printf("Saliendo...\n"); break;
                default: printf("Opción inválida.\n");
            }
        } while (opcion != 0);
        return 0;
    }

    void alta_habitacion() {
        if (total_habitaciones >= MAX_HABITACIONES) {
            printf("No hay espacio para nuevas habitaciones.\n");
            return;
        }
        Habitacion nueva;
        printf("Ingrese el tipo de habitación: ");
        scanf("%s", nueva.tipo);
        printf("Ingrese el precio por noche: ");
        scanf("%f", &nueva.precio);
        nueva.ocupada = 0;
        sprintf(nueva.codigo, "HAB_%03d", total_habitaciones + 1);
        habitaciones[total_habitaciones++] = nueva;
        printf("Habitación registrada con código: %s\n", nueva.codigo);
    }

    void baja_habitacion() {
        char codigo[10];
        printf("Ingrese el código de la habitación: ");
        scanf("%s", codigo);

        for (int i = 0; i < total_habitaciones; i++) {
            if (strcmp(habitaciones[i].codigo, codigo) == 0) {
                if (habitaciones[i].ocupada) {
                    printf("ERROR: No se puede dar de baja la habitación %s ya que está ocupada.\n", codigo);
                    return;
                }
                FILE *f = fopen("bajaHCoHabitaciones.txt", "a");
                fprintf(f, "%s-%s-%s\n", habitaciones[i].codigo, habitaciones[i].tipo, obtener_fecha_actual());
                fclose(f);
                habitaciones[i] = habitaciones[--total_habitaciones];
                printf("Habitación %s dada de baja.\n", codigo);
                return;
            }
        }
        printf("ERROR: La habitación no figura en nuestro registro de datos.\n");
    }

    void modificar_habitacion() {
        char codigo[10];
        printf("Ingrese el código de la habitación: ");
        scanf("%s", codigo);
        for (int i = 0; i < total_habitaciones; i++) {
            if (strcmp(habitaciones[i].codigo, codigo) == 0) {
                printf("Ingrese el nuevo tipo: ");
                scanf("%s", habitaciones[i].tipo);
                printf("Ingrese el nuevo precio: ");
                scanf("%f", &habitaciones[i].precio);
                printf("Habitación modificada correctamente.\n");
                return;
            }
        }
        printf("ERROR: La habitación no figura en nuestro registro de datos.\n");
    }

    void consultar_habitacion() {
        char codigo[10];
        printf("Ingrese el código de la habitación: ");
        scanf("%s", codigo);
        for (int i = 0; i < total_habitaciones; i++) {
            if (strcmp(habitaciones[i].codigo, codigo) == 0) {
                printf("Código: %s\nTipo: %s\nPrecio/Noche: %.2f€\nEstado: %s\n",
                    habitaciones[i].codigo, habitaciones[i].tipo, habitaciones[i].precio,
                    habitaciones[i].ocupada ? "Ocupada" : "Libre");
                return;
            }
        }
        printf("ERROR: La habitación no figura en nuestro registro de datos.\n");
    }

    void listar_habitaciones() {
        printf("\nLISTADO GENERAL DE HABITACIONES\n");
        printf("----------------------------------------------------------\n");
        printf("Código\tTipo\t	Precio/Noche (€)\n");
        printf("----------------------------------------------------------\n");
        for (int i = 0; i < total_habitaciones; i++) {
            printf("%s\t%s\t%.2f\n", habitaciones[i].codigo, habitaciones[i].tipo, habitaciones[i].precio);
        }
        printf("TOTAL: %d habitaciones registradas.\n", total_habitaciones);
    }

    char *obtener_fecha_actual() {
        static char fecha[11];
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        sprintf(fecha, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
        return fecha;
}
    system("cls");
}

/****************************************************************************/
/*Subprograma:              Menú del subprograma                            */
/*Tipo:                     Procedimiento (función tipo void)               */
/*Parámetros de entrada:    ---                                             */
/*Parámetros de salida:     ---                                             */
/*Prerrequisitos:           ---                                             */
/*Objetivo:                 Muestra por pantalla el menú del subprograma    */
/****************************************************************************/
void submenu_hab(){
    int opc;
    do{
        printf("\n------------------------------------------------------\n");
        printf("\n\tGESTIÓN DE CLIENTES\n");
        printf("\n------------------------------------------------------\n");
        printf("\n\t1.- Alta\n");
        printf("\n\t2.- Baja\n");
        printf("\n\t3.- Modificación\n");
        printf("\n\t4.- Consulta\n");
        printf("\n\t5.- Listado General\n");
        printf("\n\t0.- Salir\n");

        printf("\n\tSelecciona una opción: ");
        scanf("%d", &opc);

        system("pause");
        system("cls");

        switch(opc){
            case 1:
                printf("\n\tAltas\n\n");
                system("pause");
                system("cls");
                break;
            case 2:
                printf("\n\tBajas\n\n");
                system("pause");
                system("cls");
                break;
            case 3:
                printf("\n\tModificación\n\n");
                system("pause");
                system("cls");
                break;
            case 4:
                printf("\n\tConsulta\n\n");
                system("pause");
                system("cls");
                break;
            case 5:
                printf("\n\tListado\n\n");
                system("pause");
                system("cls");
                break;
            case 0:
                break;
        }
    }while(opc != 0);
}

/********************************************************************************************/
/*Subprograma:              Gestión reservas                                                */
/*Tipo:                     Procedimiento (función tipo void)                               */
/*Parámetros de entrada:    ---                                                             */
/*Parámetros de salida:     ---                                                             */
/*Prerrequisitos:           ---                                                             */
/*Objetivo:                 Se encarga de todas las opciones relacionadas con las reservas  */
/********************************************************************************************/
void gest_reservas(){
    void submenu_res();

    submenu_res();

    system("cls");
}

/****************************************************************************/
/*Subprograma:              Menú del subprograma                            */
/*Tipo:                     Procedimiento (función tipo void)               */
/*Parámetros de entrada:    ---                                             */
/*Parámetros de salida:     ---                                             */
/*Prerrequisitos:           ---                                             */
/*Objetivo:                 Muestra por pantalla el menú del subprograma    */
/****************************************************************************/
void submenu_res(){
    int opc;
    do{
        printf("\n------------------------------------------------------\n");
        printf("\n\tGESTIÓN DE RESERVAS\n");
        printf("\n------------------------------------------------------\n");
        printf("\n\t1.- Realizar Reserva\n");
        printf("\n\t2.- Cancelar Reserva\n");
        printf("\n\t3.- Consultar Reservas de un Cliente\n");
        printf("\n\t4.- Listado General de Reservas\n");
        printf("\n\t0.- Salir\n");

        printf("\n\tSelecciona una opción: ");
        scanf("%d", &opc);

        system("pause");
        system("cls");

        switch(opc){
            case 1:
                printf("\n\tRealizar reservas\n\n");
                system("pause");
                system("cls");
                break;
            case 2:
                printf("\n\tCancelar reservas\n\n");
                system("pause");
                system("cls");
                break;
            case 3:
                printf("\n\tConsultar reservas\n\n");
                system("pause");
                system("cls");
                break;
            case 4:
                printf("\n\tListado\n\n");
                system("pause");
                system("cls");
                break;
            case 0:
                break;
        }
    }while(opc != 0);
}
