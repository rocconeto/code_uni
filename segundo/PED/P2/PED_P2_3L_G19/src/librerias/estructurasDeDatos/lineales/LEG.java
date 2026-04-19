package librerias.estructurasDeDatos.lineales;

public class LEG<E> {
    protected NodoLEG<E> primero;
    protected NodoLEG<E> ultimo;

    public LEG() {
        primero = ultimo = null;
    }

    public void insertarFinal(E x) {
        NodoLEG<E> nuevo = new NodoLEG<>(x);
        if (primero == null) primero = nuevo;
        else ultimo.siguiente = nuevo;
        ultimo = nuevo;
    }

    public E eliminarInicio() {
        if (primero == null) return null;
        E dato = primero.dato;
        primero = primero.siguiente;
        if (primero == null) ultimo = null;
        return dato;
    }

    public E getPrimero() {
        return (primero == null) ? null : primero.dato;
    }

    public boolean esVacia() {
        return primero == null;
    }

    // Encapsulamos la recursividad aquí para no exponer nodos fuera
    public int talla() {
        return contarRecursivo(primero);
    }

    private int contarRecursivo(NodoLEG<E> actual) {
        if (actual == null) return 0;
        return 1 + contarRecursivo(actual.siguiente);
    }

    // Método para poder iterar sin romper la encapsulación (usado en informes)
    public NodoLEG<E> getNodoPrimero() {
        return primero;
    }
}