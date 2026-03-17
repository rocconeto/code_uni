package librerias.estructurasDeDatos.lineales;
import librerias.estructurasDeDatos.modelos.I_LE;

public class LEG<E> implements I_LE<E> {
    public NodoLEG<E> primero;
    public NodoLEG<E> ultimo;
    private int talla;

    public LEG() {
        this.primero = null;
        this.ultimo = null;
        this.talla = 0;
    }

    @Override
    public void insertar(E e) {
        NodoLEG<E> nuevo = new NodoLEG<>(e);
        if (esVacia()) {
            primero = ultimo = nuevo;
        } else {
            ultimo.sig = nuevo;
            nuevo.ant = ultimo;
            ultimo = nuevo;
        }
        talla++;
    }

    @Override
    public boolean eliminar(E e) {
        NodoLEG<E> aux = primero;
        while (aux != null && !aux.dato.equals(e)) {
            aux = aux.sig;
        }
        if (aux != null) {
            if (aux == primero) primero = aux.sig;
            else aux.ant.sig = aux.sig;

            if (aux == ultimo) ultimo = aux.ant;
            else aux.sig.ant = aux.ant;

            talla--;
            return true;
        }
        return false;
    }

    @Override
    public E buscar(E e) {
        NodoLEG<E> aux = primero;
        while (aux != null) {
            if (aux.dato.equals(e)) return aux.dato;
            aux = aux.sig;
        }
        return null;
    }

    @Override
    public boolean esVacia() { return talla == 0; }

    @Override
    public int talla() { return talla; }
}