package aplicacion;
import java.util.Scanner;
import librerias.estructurasDeDatos.lineales.LECola;

public class Main {
    private static Scanner sc = new Scanner(System.in);
    private static GestionImpresion gestor = new GestionImpresion();

    public static void main(String[] args) {
        int op;
        do {
            cabecera("MENÚ PRINCIPAL");
            System.out.println("1.- Enviar un trabajo a la impresora");
            System.out.println("2.- Imprimir trabajos");
            System.out.println("3.- Mostrar trabajo más pesado");
            System.out.println("4.- Mostrar tiempo de espera de un usuario");
            System.out.println("5.- Informe de trabajos por prioridad");
            System.out.println("6.- Informe de trabajos de una prioridad");
            System.out.println("7.- Reducir espera en una prioridad");
            System.out.println("8.- Reiniciar el Sistema de impresión");
            System.out.println("0.- Salir");
            System.out.print("\nElija opción: ");
            op = sc.nextInt();
            procesar(op);
        } while (op != 0);
    }

    private static void cabecera(String t) {
        System.out.println("\n------------------------------------------------");
        System.out.println(" >>>  " + t + " <<<");
        System.out.println("------------------------------------------------");
    }

    private static void procesar(int op) {
        switch (op) {
            case 1:
                cabecera("Enviar Trabajo");
                System.out.print("ID Usuario: "); int id = sc.nextInt();
                System.out.print("Título: "); String tit = sc.next();
                System.out.print("Peso: "); int p = sc.nextInt();
                gestor.enviarTrabajo(id, tit, p);
                break;
            case 2:
                cabecera("Imprimir Trabajos");
                boolean continuar = true;

                do {
                    Trabajo t = gestor.imprimirSiguiente();

                    if (t == null) {
                        System.out.println("No quedan trabajos a la espera de impresión.");
                        continuar = false;
                    } else {
                        // Se imprime el trabajo actual
                        System.out.println("Imprimiendo: [" + t.getTitulo() + "] - Usuario: " + t.getIdUsuario());

                        // CORRECCIÓN AQUÍ:
                        // Solo preguntamos si REALMENTE queda algo más por imprimir
                        if (gestor.quedanTrabajos()) {
                            System.out.print("¿Desea imprimir otro trabajo? (S/N): ");
                            String resp = sc.next();
                            if (resp.equalsIgnoreCase("N")) {
                                continuar = false;
                            }
                        } else {
                            System.out.println("No quedan más trabajos a la espera.");
                            continuar = false;
                        }
                    }
                } while (continuar);
                break;
            case 3:
                cabecera("Trabajo Más Pesado");
                Trabajo m = gestor.buscarMasPesado();
                if (m != null) System.out.println("Máximo: " + m.getTitulo() + " (" + m.getPeso() + "Kb)");
                break;
            case 4:
                cabecera("Tiempo de Espera");
                System.out.print("ID Usuario: ");
                int d = gestor.tiempoEspera(sc.nextInt());
                System.out.println(d != -1 ? "Trabajos delante: " + d : "No encontrado.");
                break;
            case 5:
                cabecera("Informe General");
                for(int i=1; i<=9; i++)
                    System.out.println("Prioridad " + i + ": " + gestor.obtenerCopia(i).contarElemCola() + " trab.");
                break;
            case 6:
                cabecera("Informe de Prioridad");
                System.out.print("Prioridad (1-9): ");
                listar(gestor.obtenerCopia(sc.nextInt()));
                break;
            case 7:
                cabecera("Reducir Espera");
                System.out.print("Prioridad: ");
                listar(gestor.ejecutarReduccion(sc.nextInt()));
                System.out.println("Trabajos eliminados.");
                break;
            case 8:
                cabecera("Reinicio del Sistema");
                listar(gestor.vaciar());
                System.out.println("Sistema limpio.");
                break;
            case 0:
                System.out.println("Gracias por utilizar la aplicación PrintManagement");
                break;
            default:
                System.out.println("Opción no válida.");
        }
    }

    private static void listar(LECola<Trabajo> c) {
        if (c.esVacia()) { System.out.println("No hay datos."); return; }
        System.out.println("ID\tTÍTULO");
        while(!c.esVacia()) {
            Trabajo tr = c.desencolar();
            System.out.println(tr.getIdUsuario() + "\t" + tr.getTitulo());
        }
    }
}