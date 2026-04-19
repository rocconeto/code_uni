package librerias.excepcionesDeUsuario;

public class ColaVacia extends Exception {
    public ColaVacia() {
        super("Error: La cola está vacía y no se pueden extraer elementos.");
    }

    public ColaVacia(String mensaje) {
        super(mensaje);
    }
}