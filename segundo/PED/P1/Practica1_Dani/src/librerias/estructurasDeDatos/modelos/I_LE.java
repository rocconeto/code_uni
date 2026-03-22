package librerias.estructurasDeDatos.modelos;

public interface I_LE<E> {
    void insertar(E e);
    boolean eliminar(E e);
    E buscar(E e);
    boolean esVacia();
    int talla();
}