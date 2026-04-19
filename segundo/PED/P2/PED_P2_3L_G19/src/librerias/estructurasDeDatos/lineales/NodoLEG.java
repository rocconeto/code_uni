package librerias.estructurasDeDatos.lineales;

class NodoLEG<E> {
    E dato;
    NodoLEG<E> siguiente;

    NodoLEG(E dato) {
        this(dato, null);
    }

    NodoLEG(E dato, NodoLEG<E> siguiente) {
        this.dato = dato;
        this.siguiente = siguiente;
    }
}