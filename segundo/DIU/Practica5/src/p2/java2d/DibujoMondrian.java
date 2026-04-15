package p2.java2d;

import java.awt.*;

public class DibujoMondrian {
    private static final Color MONDRIAN_RED = new Color(237, 28, 36);
    private static final Color MONDRIAN_BLUE = new Color(0, 56, 168);
    private static final Color MONDRIAN_YELLOW = new Color(255, 221, 51);

    public static void pintar(Graphics2D g2d, int w, int h) {
        // Activación del anti-aliasing
        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

        // Bloque Rojo
        g2d.setColor(MONDRIAN_RED);
        g2d.fillRect((int)(w * 0.3), 0, (int)(w * 0.7), (int)(h * 0.5));

        // Bloque Azul
        g2d.setColor(MONDRIAN_BLUE);
        g2d.fillRect(0, (int)(h * 0.7), (int)(w * 0.3), (int)(h * 0.3));

        // Bloque Amarillo
        g2d.setColor(MONDRIAN_YELLOW);
        g2d.fillRect((int)(w * 0.85), (int)(h * 0.5), (int)(w * 0.15), (int)(h * 0.2));

        // Líneas negras
        g2d.setStroke(new BasicStroke(10.0f));
        g2d.setColor(Color.BLACK);

        // Líneas verticales
        g2d.drawLine((int)(w * 0.3), 0, (int)(w * 0.3), h);
        g2d.drawLine((int)(w * 0.85), (int)(h * 0.5), (int)(w * 0.85), h);

        // Líneas horizontales
        g2d.drawLine(0, (int)(h * 0.5), w, (int)(h * 0.5));
        g2d.drawLine(0, (int)(h * 0.7), w, (int)(h * 0.7));
    }
}