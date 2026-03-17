package dominio;

import librerias.estructurasDeDatos.lineales.LEG;
import librerias.estructurasDeDatos.lineales.NodoLEG;
import java.util.Scanner;

public class GestionBus {
    // La lista principal
    static LEG<Autobus> empresa = new LEG<>();
    static Scanner sc = new Scanner(System.in);

    public static void main(String[] args) {
        System.out.println("Bienvenido a la aplicación GEST_BUS");
        int opcion;
        do {
            System.out.println("\nMENÚ PRINCIPAL");
            System.out.println("1.- Mantenimiento");
            System.out.println("2.- Listados");
            System.out.println("0.- Salir");
            System.out.print("Opción: ");
            opcion = Integer.parseInt(sc.nextLine());

            if (opcion == 1) menuMantenimiento();
            else if (opcion == 2) menuListados();

        } while (opcion != 0);
        System.out.println("Gracias por utilizar la aplicación GEST_BUS");
    }

    private static void menuMantenimiento() {
        int op;
        do {
            System.out.println("\nMENÚ MANTENIMIENTO");
            System.out.println("1.- Alta de autobús");
            System.out.println("2.- Baja de autobús");
            System.out.println("0.- Volver al menú principal"); // Simplificado para longitud
            System.out.print("Opción: ");
            op = Integer.parseInt(sc.nextLine());

            if (op == 1) altaAutobus();
            else if (op == 2) bajaAutobus();
            // Aquí irían las llamadas a opciones 3, 4, 5 y 6
        } while (op != 0);
    }

    private static void altaAutobus() {
        System.out.print("Introduzca matrícula: ");
        String mat = sc.nextLine();
        Autobus dummy = new Autobus(mat, 0, 0); // Usado solo para buscar

        if (empresa.buscar(dummy) != null) {
            System.out.println("Error: ya existe un autobús registrado con esa matrícula");
            return;
        }

        System.out.print("Año de compra: ");
        int anio = Integer.parseInt(sc.nextLine());
        System.out.print("Número de plazas: ");
        int plazas = Integer.parseInt(sc.nextLine());

        Autobus nuevo = new Autobus(mat, anio, plazas);
        insertarAutobusOrdenadoPorPlazas(nuevo);
        System.out.println("Autobús registrado correctamente.");
    }

    private static void bajaAutobus() {
        System.out.print("Introduzca matrícula a dar de baja: ");
        String mat = sc.nextLine();
        Autobus bus = empresa.buscar(new Autobus(mat, 0, 0));

        if (bus == null) {
            System.out.println("Error: esta matrícula no está registrada en la aplicación");
        } else {
            System.out.print("¿Desea realmente dar de baja a este autobús? (S/N): ");
            String conf = sc.nextLine();
            if (conf.equalsIgnoreCase("S")) {
                empresa.eliminar(bus);
                System.out.println("Baja registrada");
            } else {
                System.out.println("Proceso de baja abortado");
            }
        }
    }

    // EL NÚCLEO ALGORÍTMICO PARA EVITAR ORDENAR LUEGO
    private static void insertarAutobusOrdenadoPorPlazas(Autobus nuevo) {
        if (empresa.esVacia()) {
            empresa.insertar(nuevo);
            return;
        }

        NodoLEG<Autobus> aux = empresa.primero;
        while (aux != null && aux.dato.getPlazas() < nuevo.getPlazas()) {
            aux = aux.sig;
        }

        NodoLEG<Autobus> nodoNuevo = new NodoLEG<>(nuevo);
        if (aux == empresa.primero) { // Insertar al principio
            nodoNuevo.sig = empresa.primero;
            empresa.primero.ant = nodoNuevo;
            empresa.primero = nodoNuevo;
        } else if (aux == null) { // Insertar al final
            nodoNuevo.ant = empresa.ultimo;
            empresa.ultimo.sig = nodoNuevo;
            empresa.ultimo = nodoNuevo;
        } else { // Insertar en medio
            nodoNuevo.sig = aux;
            nodoNuevo.ant = aux.ant;
            aux.ant.sig = nodoNuevo;
            aux.ant = nodoNuevo;
        }
    }

    private static void menuListados() {
        System.out.println("\nMENÚ LISTADOS");
        System.out.println("1.- General de autobuses (ascendente)");
        System.out.println("2.- General de autobuses (descendente)");
        System.out.print("Opción: ");
        int op = Integer.parseInt(sc.nextLine());

        if (op == 1) {
            System.out.println("\nLISTADO GENERAL DE AUTOBUSES POR NÚMERO DE PLAZAS (Orden Ascendente)");
            System.out.printf("%-15s %-15s %-10s\n", "Matrícula", "Año Compra", "Plazas");
            System.out.println("---------------------------------------------");
            NodoLEG<Autobus> aux = empresa.primero;
            while (aux != null) {
                System.out.printf("%-15s %-15d %-10d\n", aux.dato.getMatricula(), aux.dato.getAnioCompra(), aux.dato.getPlazas());
                aux = aux.sig;
            }
        } else if (op == 2) {
            System.out.println("\nLISTADO GENERAL DE AUTOBUSES POR NÚMERO DE PLAZAS (Orden Descendente)");
            System.out.printf("%-15s %-15s %-10s\n", "Matrícula", "Año Compra", "Plazas");
            System.out.println("---------------------------------------------");
            NodoLEG<Autobus> aux = empresa.ultimo; // Usamos el puntero final
            while (aux != null) {
                System.out.printf("%-15s %-15d %-10d\n", aux.dato.getMatricula(), aux.dato.getAnioCompra(), aux.dato.getPlazas());
                aux = aux.ant; // Retrocedemos sin recursividad ni algoritmos de ordenación
            }
        }
    }
}