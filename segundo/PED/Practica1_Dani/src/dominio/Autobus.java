package dominio;
import librerias.estructurasDeDatos.lineales.LEG;

public class Autobus {
    private String matricula;
    private int anioCompra;
    private int plazas;
    public LEG<Viaje> viajes; // Sublista de la multilista

    public Autobus(String matricula, int anioCompra, int plazas) {
        this.matricula = matricula;
        this.anioCompra = anioCompra;
        this.plazas = plazas;
        this.viajes = new LEG<>();
    }

    public String getMatricula() { return matricula; }
    public int getAnioCompra() { return anioCompra; }
    public int getPlazas() { return plazas; }

    public void setAnioCompra(int anioCompra) { this.anioCompra = anioCompra; }
    public void setPlazas(int plazas) { this.plazas = plazas; }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (!(obj instanceof Autobus)) return false;
        return this.matricula.equalsIgnoreCase(((Autobus) obj).matricula);
    }
}