package dominio;

public class Viaje {
    private int codigo;
    private String origen;
    private String destino;
    private String hora;

    public Viaje(int codigo, String origen, String destino, String hora) {
        this.codigo = codigo;
        this.origen = origen;
        this.destino = destino;
        this.hora = hora;
    }

    public int getCodigo() { return codigo; }
    public String getOrigen() { return origen; }
    public String getDestino() { return destino; }
    public String getHora() { return hora; }

    public void setOrigen(String origen) { this.origen = origen; }
    public void setDestino(String destino) { this.destino = destino; }
    public void setHora(String hora) { this.hora = hora; }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (!(obj instanceof Viaje)) return false;
        return this.codigo == ((Viaje) obj).codigo;
    }

    @Override
    public String toString() {
        return "Viaje " + codigo + ": " + origen + " -> " + destino + " (" + hora + ")";
    }
}