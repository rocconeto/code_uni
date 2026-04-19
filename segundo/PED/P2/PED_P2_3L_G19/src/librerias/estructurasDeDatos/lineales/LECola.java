package librerias.estructurasDeDatos.lineales;
import librerias.estructurasDeDatos.modelos.I_Cola;

public class LECola<E> implements I_Cola<E> {
    private LEG<E> lista;

    public LECola() {
        lista = new LEG<>();
    }

    @Override
    public void encolar(E x) { lista.insertarFinal(x); }

    @Override
    public E desencolar() { return lista.eliminarInicio(); }

    @Override
    public E primero() { return lista.getPrimero(); }

    @Override
    public boolean esVacia() { return lista.esVacia(); }

    @Override
    public int contarElemCola() {
        return lista.talla();
    }
}