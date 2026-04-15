package p4.animacion;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import p2.java2d.SpritePanelRef;

public class SpritePanel extends JPanel implements SpritePanelRef {
    private int x = 100, y = 100, dx = 5, dy = 5, grosor = 6;
    private Color colorActivo = new Color(237, 28, 36);
    private ArrayList<Point> estela = new ArrayList<>();
    private ArrayList<Trazo> trazos = new ArrayList<>();
    private Point lastPoint;
    private Timer timer;
    private JLabel lbl;

    public SpritePanel(JLabel lbl) {
        this.lbl = lbl;
        setFocusable(true);
        timer = new Timer(30, e -> mover());
    }

    private void mover() {
        estela.add(new Point(x, y));
        if (estela.size() > 10) estela.remove(0); // REQUISITO: 10 posiciones [cite: 104]
        x += dx; y += dy;
        if (x < 0 || x > getWidth()-40) dx *= -1;
        if (y < 0 || y > getHeight()-40) dy *= -1;
        actualizarEstado();
        repaint();
    }

    public void ajustarGrosor(int delta) {
        grosor = Math.max(2, Math.min(20, grosor + delta)); // [cite: 76, 89]
        actualizarEstado();
    }

    public void borrarTrazos() { trazos.clear(); repaint(); } // [cite: 76]

    public void setStepSize(int s) { dx = (dx > 0) ? s : -s; dy = (dy > 0) ? s : -s; }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D) g;

        // 1. LLAMADA AL FONDO MONDRIAN (Ubicado en p2)
        // Pasamos el ancho y alto actual para que sea relativo [cite: 56]
        p2.java2d.DibujoMondrian.pintar(g2d, getWidth(), getHeight());

        // 2. TRAZOS LIBRES (Orden de pintado requerido)
        for (Trazo t : trazos) {
            g2d.setColor(t.c);
            g2d.setStroke(new BasicStroke(t.g, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
            g2d.drawLine(t.p1.x, t.p1.y, t.p2.x, t.p2.y);
        }

        // 3. ESTELA CON OPACIDAD (AlphaComposite) [cite: 105, 106]
        for (int i = 0; i < estela.size(); i++) {
            float alpha = (i + 1) * 0.05f; // Opacidad creciente
            g2d.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER, alpha));
            g2d.setColor(Color.LIGHT_GRAY);
            g2d.fillOval(estela.get(i).x, estela.get(i).y, 25, 25);
        }
        g2d.setComposite(AlphaComposite.SrcOver); // Resetear opacidad

        // 4. SPRITE ANIMADO [cite: 99, 101]
        g2d.setColor(dx > 0 ? Color.ORANGE : Color.CYAN);
        // Alternancia de tamaño para ilusión de movimiento
        int pulso = (System.currentTimeMillis() % 600 < 300) ? 40 : 32;
        g2d.fillOval(x, y, pulso, pulso);
    }

    private void actualizarEstado() {
        lbl.setText(String.format("Coords: (%d,%d) | Grosor: %dpx", x, y, grosor)); // [cite: 102]
    }

    // Métodos auxiliares para dibujo
    public void setLastPoint(Point p) { this.lastPoint = p; }
    public void dibujarTrazo(Point p) {
        if (lastPoint != null) {
            trazos.add(new Trazo(lastPoint, p, colorActivo, grosor));
            lastPoint = p; repaint();
        }
    }
    public void setColorActivo(Color c) { this.colorActivo = c; }
    public Timer getTimer() { return timer; }
}

class Trazo {
    Point p1, p2; Color c; int g;
    Trazo(Point p1, Point p2, Color c, int g) { this.p1=p1; this.p2=p2; this.c=c; this.g=g; }
}