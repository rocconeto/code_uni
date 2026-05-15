import java.awt.Color;

public class Model {
    private int vX1, vY1, vX2, vY2; // Línea vertical
    private int hX1, hY1, hX2, hY2; // Línea horizontal
    private Color lineColor = Color.BLACK;
    private Color canvasColor = new Color(180, 185, 200);

    public Model(int width, int height) {
        vX1 = width / 2; vY1 = 20;
        vX2 = vX1; vY2 = height - 20;
        hX1 = 20; hY1 = height / 2;
        hX2 = width - 20; hY2 = hY1;
    }

    // Métodos de lógica de negocio (Mover)
    public void moverHorizontal(int delta) { vX1 += delta; vX2 += delta; }
    public void moverVertical(int delta) { hY1 += delta; hY2 += delta; }

    // Getters y Setters
    public int getvX1() { return vX1; } public int getvY1() { return vY1; }
    public int getvX2() { return vX2; } public int getvY2() { return vY2; }
    public int gethX1() { return hX1; } public int gethY1() { return hY1; }
    public int gethX2() { return hX2; } public int gethY2() { return hY2; }
    public Color getLineColor() { return lineColor; }
    public void setLineColor(Color c) { this.lineColor = c; }
    public Color getCanvasColor() { return canvasColor; }
    public void setCanvasColor(Color c) { this.canvasColor = c; }
}