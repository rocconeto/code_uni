package librerias.estructurasDeDatos.lineales;

public class NodoLEG<E> {
    public E dato;
    public NodoLEG<E> sig;
    public NodoLEG<E> ant;

    public NodoLEG(E dato) {
        this.dato = dato;
        this.sig = null;
        this.ant = null;
    }
}