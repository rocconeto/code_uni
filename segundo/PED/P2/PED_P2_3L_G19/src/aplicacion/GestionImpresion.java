package aplicacion;
import librerias.estructurasDeDatos.lineales.LECola;

public class GestionImpresion {
    private LECola<Trabajo>[] colas;

    public GestionImpresion() {
        colas = new LECola[10];
        for (int i = 1; i <= 9; i++) colas[i] = new LECola<>();
    }

    public void enviarTrabajo(int id, String tit, int peso) {
        Trabajo t = new Trabajo(id, tit, peso);
        colas[t.getPrioridad()].encolar(t);
    }

    public Trabajo imprimirSiguiente() {
        for (int i = 1; i <= 9; i++) {
            if (!colas[i].esVacia()) return colas[i].desencolar();
        }
        return null;
    }

    public boolean quedanTrabajos() {
        for (int i = 1; i <= 9; i++) {
            if (!colas[i].esVacia()) return true;
        }
        return false;
    }

    public Trabajo buscarMasPesado() {
        Trabajo max = null;
        for (int i = 1; i <= 9; i++) {
            LECola<Trabajo> aux = copiar(i);
            while (!aux.esVacia()) {
                Trabajo actual = aux.desencolar();
                if (max == null || actual.getPeso() > max.getPeso() ||
                        (actual.getPeso() == max.getPeso() && actual.getPrioridad() <= max.getPrioridad())) {
                    max = actual;
                }
            }
        }
        return max;
    }

    public int tiempoEspera(int id) {
        int cont = 0; boolean enc = false;
        for (int i = 1; i <= 9; i++) {
            LECola<Trabajo> aux = copiar(i);
            while (!aux.esVacia()) {
                Trabajo t = aux.desencolar();
                if (!enc && t.getIdUsuario() == id) enc = true;
                else if (!enc) cont++;
            }
        }
        return enc ? cont : -1;
    }

    public LECola<Trabajo> obtenerCopia(int p) { return copiar(p); }

    public LECola<Trabajo> ejecutarReduccion(int p) {
        LECola<Trabajo> eliminados = new LECola<>();
        int d = 2;
        while (colas[p].contarElemCola() >= d) {
            LECola<Trabajo> aux = new LECola<>();
            int pos = 1;
            while (!colas[p].esVacia()) {
                Trabajo t = colas[p].desencolar();
                if (pos % d == 0) aux.encolar(t);
                else eliminados.encolar(t);
                pos++;
            }
            colas[p] = aux; d++;
        }
        return eliminados;
    }

    public LECola<Trabajo> vaciar() {
        LECola<Trabajo> todos = new LECola<>();
        for (int i = 1; i <= 9; i++) {
            while (!colas[i].esVacia()) todos.encolar(colas[i].desencolar());
        }
        return todos;
    }

    private LECola<Trabajo> copiar(int p) {
        LECola<Trabajo> c = new LECola<>(), a = new LECola<>();
        while (!colas[p].esVacia()) { Trabajo t = colas[p].desencolar(); c.encolar(t); a.encolar(t); }
        colas[p] = a; return c;
    }
}