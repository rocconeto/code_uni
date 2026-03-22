package dominio;
import librerias.estructurasDeDatos.lineales.LEG;

public class Autobus {
    private String matricula;
    private int anioCompra;
    private int plazas;
    private LEG<Viaje> viajes; // AHORA ES PRIVADO

    public Autobus(String matricula, int anioCompra, int plazas) {
        // Validaciones defensivas
        if (matricula == null || matricula.trim().isEmpty()) {
            throw new IllegalArgumentException("La matrícula no puede estar vacía.");
        }
        if (plazas <= 0) {
            throw new IllegalArgumentException("El número de plazas debe ser mayor que 0.");
        }

        this.matricula = matricula;
        this.anioCompra = anioCompra;
        this.plazas = plazas;
        this.viajes = new LEG<>();
    }

    public String getMatricula() { return matricula; }
    public int getAnioCompra() { return anioCompra; }
    public int getPlazas() { return plazas; }

    // NUEVO GETTER PARA LA SUBLISTA
    public LEG<Viaje> getViajes() { return viajes; }

    public void setAnioCompra(int anioCompra) { this.anioCompra = anioCompra; }

    public void setPlazas(int plazas) {
        if (plazas <= 0) throw new IllegalArgumentException("Las plazas deben ser > 0.");
        this.plazas = plazas;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (!(obj instanceof Autobus)) return false;
        return this.matricula.equalsIgnoreCase(((Autobus) obj).matricula);
    }
}