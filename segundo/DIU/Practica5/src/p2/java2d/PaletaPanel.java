package p2.java2d;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class PaletaPanel extends JPanel {
    private Color colorSeleccionado = new Color(237, 28, 36);
    private SpritePanelRef target;

    public PaletaPanel(SpritePanelRef target) {
        this.target = target;
        setLayout(new GridLayout(6, 1)); // [cite: 34]
        setPreferredSize(new Dimension(120, 0));

        Color[] colores = {
                new Color(237, 28, 36), new Color(0, 56, 168), new Color(255, 221, 51), // Obligatorios [cite: 43]
                Color.GREEN, Color.MAGENTA, Color.BLACK
        };

        for (Color c : colores) {
            JPanel celda = new JPanel() {
                @Override
                protected void paintComponent(Graphics g) {
                    super.paintComponent(g);
                    Graphics2D g2d = (Graphics2D) g;
                    g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
                    g2d.setColor(c);
                    g2d.fillRect(5, 5, getWidth()-10, getHeight()-10);
                    if (colorSeleccionado.equals(c)) {
                        g2d.setColor(Color.BLACK);
                        g2d.setStroke(new BasicStroke(3)); // REQUISITO: Borde 3px [cite: 66]
                        g2d.drawRect(5, 5, getWidth()-10, getHeight()-10);
                    }
                }
            };
            celda.addMouseListener(new MouseAdapter() {
                public void mousePressed(MouseEvent e) {
                    colorSeleccionado = c;
                    target.setColorActivo(c);
                    repaint();
                    getParent().repaint();
                }
            });
            add(celda);
        }
    }
}