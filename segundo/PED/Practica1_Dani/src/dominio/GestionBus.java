package dominio;

import librerias.estructurasDeDatos.lineales.LEG;
import librerias.estructurasDeDatos.lineales.NodoLEG;
import java.util.Scanner;

public class GestionBus {
    static LEG<Autobus> empresa = new LEG<>();
    static Scanner sc = new Scanner(System.in);

    // MENÚS SECUNDARIOS
    private static void menuMantenimiento() {
        int op = -1;
        do {
            System.out.println("\nMENÚ MANTENIMIENTO");
            System.out.println("1.- Alta de autobús");
            System.out.println("2.- Baja de autobús");
            System.out.println("3.- Modificación de autobús");
            System.out.println("4.- Registrar viaje");
            System.out.println("5.- Borrar viaje");
            System.out.println("6.- Modificar viaje");
            System.out.println("0.- Volver al menú principal");
            System.out.print("Opción: ");
            try {
                op = Integer.parseInt(sc.nextLine());
                if (op == 1) altaAutobus();
                else if (op == 2) bajaAutobus();
                else if (op == 3) modificarAutobus();
                else if (op == 4) altaViaje();
                else if (op == 5) bajaViaje();
                else if (op == 6) modificarViaje();
            } catch (Exception e) {
                System.out.println("Error: Introduzca un número válido.");
            }
        } while (op != 0);
    }

    public static void main(String[] args) {
        System.out.println("Bienvenido a la aplicación GEST_BUS");
        int opcion = -1;
        do {
            System.out.println("\nMENÚ PRINCIPAL");
            System.out.println("1.- Mantenimiento");
            System.out.println("2.- Listados");
            System.out.println("0.- Salir");
            System.out.print("Opción: ");
            try {
                opcion = Integer.parseInt(sc.nextLine());
                if (opcion == 1) menuMantenimiento();
                else if (opcion == 2) menuListados();
            } catch (Exception e) {
                System.out.println("Error: Introduzca un número válido.");
            }
        } while (opcion != 0);
        System.out.println("Gracias por utilizar la aplicación GEST_BUS");
    }

    private static void menuListados() {
        int op = -1;
        do {
            System.out.println("\nMENÚ LISTADOS");
            System.out.println("1.- General de autobuses (orden ascendente por plazas)");
            System.out.println("2.- General de autobuses (orden descendente por plazas)");
            System.out.println("3.- Listado general de viajes");
            System.out.println("4.- Listado de viajes que parten de una ciudad determinada");
            System.out.println("5.- Listado de viajes que llegan a una ciudad determinada");
            System.out.println("6.- Listado de autobuses con capacidad mayor o igual a la indicada");
            System.out.println("7.- Listado del autobús o autobuses que realizan la mayor cantidad de viajes");
            System.out.println("8.- Cantidad total de viajes que realizan los autobuses");
            System.out.println("9.- Cantidad total de pasajeros que viajan de una ciudad a otra");
            System.out.println("0.- Volver al menú principal");
            System.out.print("Opción: ");
            try {
                op = Integer.parseInt(sc.nextLine());
                if (op >= 1 && op <= 9) procesarListado(op);
            } catch (Exception e) {
                System.out.println("Error: Introduzca un número válido.");
            }
        } while (op != 0);
    }

    // OPERACIONES DE MANTENIMIENTO
    private static void altaAutobus() {
        String resp;
        do {
            System.out.print("Introduzca matrícula: ");
            String mat = sc.nextLine();
            Autobus dummy = new Autobus(mat, 1, 1); // Pasamos 1 en vez de 0 para sortear las validaciones del constructor

            if (empresa.buscar(dummy) != null) {
                System.out.println("Error: ya existe un autobús registrado con esa matrícula");
            } else {
                try {
                    System.out.print("Año de compra: ");
                    int anio = Integer.parseInt(sc.nextLine());
                    System.out.print("Número de plazas: ");
                    int plazas = Integer.parseInt(sc.nextLine());

                    Autobus nuevo = new Autobus(mat, anio, plazas);
                    insertarAutobusOrdenadoPorPlazas(nuevo);
                    System.out.println("Autobús añadido.");
                } catch (IllegalArgumentException e) {
                    System.out.println("Error en los datos del autobús: " + e.getMessage());
                }
            }
            System.out.print("¿Desea añadir un nuevo autobús? (S/N): ");
            resp = sc.nextLine();
        } while (resp.equalsIgnoreCase("S"));
    }

    private static void bajaAutobus() {
        String resp;
        do {
            System.out.print("Introduzca matrícula a dar de baja: ");
            String mat = sc.nextLine();
            Autobus bus = empresa.buscar(new Autobus(mat, 1, 1)); // Pasamos 1 para la búsqueda

            if (bus == null) {
                System.out.println("Error: esta matricula no está registrada en la aplicación");
            } else {
                System.out.println("Datos: Matrícula " + bus.getMatricula() + " | Año: " + bus.getAnioCompra() + " | Plazas: " + bus.getPlazas());
                System.out.print("¿Desea realmente dar de baja a este autobús? (S/N): ");
                String conf = sc.nextLine();
                if (conf.equalsIgnoreCase("S")) {
                    empresa.eliminar(bus);
                    System.out.println("Baja registrada");
                } else {
                    System.out.println("Proceso de baja abortado");
                }
            }
            System.out.print("¿Desea dar de baja otro autobús? (S/N): ");
            resp = sc.nextLine();
        } while (resp.equalsIgnoreCase("S"));
    }

    private static void modificarAutobus() {
        String resp;
        do {
            System.out.print("Introduzca matrícula: ");
            String mat = sc.nextLine();
            Autobus bus = empresa.buscar(new Autobus(mat, 1, 1)); // Pasamos 1 para la búsqueda

            if (bus == null) {
                System.out.println("Error: esta matricula no está registrada en la aplicación");
            } else {
                try {
                    System.out.print("Nuevo año de compra (actual " + bus.getAnioCompra() + "): ");
                    bus.setAnioCompra(Integer.parseInt(sc.nextLine()));
                    System.out.print("Nuevo número de plazas (actual " + bus.getPlazas() + "): ");
                    int nuevasPlazas = Integer.parseInt(sc.nextLine());

                    // Si se cambian las plazas, hay que reordenar el autobús en la lista.
                    if (nuevasPlazas != bus.getPlazas()) {
                        empresa.eliminar(bus);
                        bus.setPlazas(nuevasPlazas);
                        insertarAutobusOrdenadoPorPlazas(bus);
                    }
                    System.out.println("Autobús modificado correctamente.");
                } catch (IllegalArgumentException e) {
                    System.out.println("Error: " + e.getMessage());
                }
            }
            System.out.print("¿Desea modificar los datos de otro autobús? (S/N): ");
            resp = sc.nextLine();
        } while (resp.equalsIgnoreCase("S"));
    }

    private static void altaViaje() {
        String resp;
        do {
            System.out.print("Matrícula del autobús que realizará el viaje: ");
            String mat = sc.nextLine();
            Autobus bus = empresa.buscar(new Autobus(mat, 1, 1)); // Pasamos 1 para la búsqueda

            if (bus == null) {
                System.out.println("Error: esta matrícula no está registrada.");
            } else {
                try {
                    System.out.print("Código del viaje: ");
                    int codigo = Integer.parseInt(sc.nextLine());

                    if (existeCodigoViajeGlobal(codigo)) {
                        System.out.println("Error: El código de viaje ya existe en la aplicación.");
                    } else {
                        System.out.print("Ciudad de origen (Madrid/Segovia/Barcelona/Sevilla): ");
                        String origen = sc.nextLine();
                        System.out.print("Ciudad de destino: ");
                        String destino = sc.nextLine();
                        System.out.print("Hora del viaje (ej: 16:30): ");
                        String hora = sc.nextLine();

                        if (!ciudadesValidas(origen, destino)) {
                            System.out.println("Error: Ciudades inválidas o coinciden.");
                        } else if (conflictoViajeEnBus(bus, origen, destino, hora)) {
                            System.out.println("Error: El autobús ya realiza un viaje similar (mismo origen, destino y hora).");
                        } else {
                            bus.getViajes().insertar(new Viaje(codigo, origen, destino, hora)); // CAMBIO AQUÍ
                            System.out.println("Viaje registrado con éxito.");
                        }
                    }
                } catch (IllegalArgumentException e) {
                    System.out.println("Error: " + e.getMessage());
                }
            }
            System.out.print("¿Desea registrar otro viaje? (S/N): ");
            resp = sc.nextLine();
        } while (resp.equalsIgnoreCase("S"));
    }

    private static void bajaViaje() {
        System.out.print("Matrícula del autobús: ");
        String mat = sc.nextLine();
        Autobus bus = empresa.buscar(new Autobus(mat, 1, 1));

        if (bus != null) {
            System.out.print("Código del viaje a borrar: ");
            int cod = Integer.parseInt(sc.nextLine());
            Viaje v = bus.getViajes().buscar(new Viaje(cod, "a", "b", "")); // CAMBIO AQUÍ

            if (v != null) {
                System.out.println("Datos del viaje: " + v);
                System.out.print("¿Confirmar borrado? (S/N): ");
                if (sc.nextLine().equalsIgnoreCase("S")) {
                    bus.getViajes().eliminar(v); // CAMBIO AQUÍ
                    System.out.println("Viaje borrado.");
                } else {
                    System.out.println("Borrado cancelado.");
                }
            } else {
                System.out.println("Error: Viaje no encontrado en este autobús.");
            }
        } else {
            System.out.println("Error: Autobús no encontrado.");
        }
    }

    private static void modificarViaje() {
        System.out.print("Matrícula del autobús: ");
        String mat = sc.nextLine();
        Autobus bus = empresa.buscar(new Autobus(mat, 1, 1));

        if (bus != null && !bus.getViajes().esVacia()) { // CAMBIO AQUÍ
            System.out.println("Viajes del autobús:");
            NodoLEG<Viaje> aux = bus.getViajes().primero; // CAMBIO AQUÍ
            while(aux != null){
                System.out.println(aux.dato);
                aux = aux.sig;
            }

            System.out.print("¿Qué viaje desea modificar? (Introduzca código): ");
            int cod = Integer.parseInt(sc.nextLine());
            Viaje v = bus.getViajes().buscar(new Viaje(cod, "a", "b", "")); // CAMBIO AQUÍ

            if (v != null) {
                System.out.print("Nuevo origen: "); String ori = sc.nextLine();
                System.out.print("Nuevo destino: "); String des = sc.nextLine();
                System.out.print("Nueva hora: "); String hora = sc.nextLine();

                if (ciudadesValidas(ori, des)) {
                    v.setOrigen(ori);
                    v.setDestino(des);
                    v.setHora(hora);
                    System.out.println("Autobús " + mat + ": Viaje " + cod + " modificado correctamente");
                } else {
                    System.out.println("Error: Ciudades no válidas.");
                }
            } else {
                System.out.println("Viaje no encontrado.");
            }
        } else {
            System.out.println("Error: Autobús no encontrado o no tiene viajes.");
        }
    }

    // ==========================================
    // OPERACIONES DE LISTADOS
    // ==========================================
    private static void procesarListado(int op) {
        switch (op) {
            case 1:
                System.out.println("\nLISTADO GENERAL DE AUTOBUSES POR NÚMERO DE PLAZAS (Orden Ascendente)");
                System.out.printf("%-15s %-15s %-10s\n", "Matrícula", "Año Compra", "Plazas");
                System.out.println("---------------------------------------------");
                NodoLEG<Autobus> aux1 = empresa.primero;
                while (aux1 != null) {
                    System.out.printf("%-15s %-15d %-10d\n", aux1.dato.getMatricula(), aux1.dato.getAnioCompra(), aux1.dato.getPlazas());
                    aux1 = aux1.sig;
                }
                break;
            case 2:
                System.out.println("\nLISTADO GENERAL DE AUTOBUSES POR NÚMERO DE PLAZAS (Orden Descendente)");
                System.out.printf("%-15s %-15s %-10s\n", "Matrícula", "Año Compra", "Plazas");
                System.out.println("---------------------------------------------");
                NodoLEG<Autobus> aux2 = empresa.ultimo;
                while (aux2 != null) {
                    System.out.printf("%-15s %-15d %-10d\n", aux2.dato.getMatricula(), aux2.dato.getAnioCompra(), aux2.dato.getPlazas());
                    aux2 = aux2.ant;
                }
                break;
            case 3:
                System.out.println("\nLISTADO GENERAL DE VIAJES");
                NodoLEG<Autobus> a3 = empresa.primero;
                while (a3 != null) {
                    System.out.println("Autobús: " + a3.dato.getMatricula());
                    NodoLEG<Viaje> v3 = a3.dato.getViajes().primero; // CAMBIO AQUÍ
                    if (v3 == null) System.out.println("  Sin viajes asignados.");
                    while (v3 != null) {
                        System.out.println("  - " + v3.dato);
                        v3 = v3.sig;
                    }
                    a3 = a3.sig;
                }
                break;
            case 4:
                System.out.print("Introduzca ciudad de partida: ");
                String origen = sc.nextLine();
                System.out.println("\nVIAJES QUE PARTEN DE " + origen.toUpperCase());
                NodoLEG<Autobus> a4 = empresa.primero;
                while (a4 != null) {
                    NodoLEG<Viaje> v4 = a4.dato.getViajes().primero; // CAMBIO AQUÍ
                    while (v4 != null) {
                        if (v4.dato.getOrigen().equalsIgnoreCase(origen)) {
                            System.out.println("Bus: " + a4.dato.getMatricula() + " | " + v4.dato);
                        }
                        v4 = v4.sig;
                    }
                    a4 = a4.sig;
                }
        }
    }
}