package librerias.estructurasDeDatos.modelos;

public interface I_Cola<E> {
    void encolar(E x);
    E desencolar();
    E primero();
    boolean esVacia();
    // Requisito obligatorio: método recursivo
    int contarElemCola();
}