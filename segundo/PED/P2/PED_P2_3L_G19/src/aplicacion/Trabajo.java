package aplicacion;

public class Trabajo {
    private int idUsuario;
    private String titulo;
    private int peso;
    private int prioridad;

    public Trabajo(int idUsuario, String titulo, int peso) {
        this.idUsuario = idUsuario;
        this.titulo = titulo;
        this.peso = peso;
        this.prioridad = calcularPrioridad(idUsuario);
    }

    private int calcularPrioridad(int id) {
        if (id >= 100 && id <= 199) return 1;
        if (id >= 200 && id <= 299) return 2;
        if (id >= 800 && id <= 899) return 8;
        if (id >= 900 && id <= 999) return 9;
        return (id / 100); // Para otros rangos intermedios
    }

    // Getters necesarios para los informes
    public int getIdUsuario() { return idUsuario; }
    public String getTitulo() { return titulo; }
    public int getPeso() { return peso; }
    public int getPrioridad() { return prioridad; }
}