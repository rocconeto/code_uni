package p3.eventos;

import java.awt.event.*;
import p4.animacion.SpritePanel;

public class GestionEventos {
    public static void asignar(SpritePanel canvas) {
        canvas.addMouseListener(new MouseAdapter() {
            public void mousePressed(MouseEvent e) { canvas.setLastPoint(e.getPoint()); canvas.requestFocus(); }
        });

        canvas.addMouseMotionListener(new MouseMotionAdapter() {
            public void mouseDragged(MouseEvent e) { canvas.dibujarTrazo(e.getPoint()); }
        });

        canvas.addKeyListener(new KeyAdapter() {
            public void keyPressed(KeyEvent e) {
                if (e.getKeyCode() == KeyEvent.VK_C) canvas.borrarTrazos(); // [cite: 76]
                if (e.getKeyChar() == '+') canvas.ajustarGrosor(2); // [cite: 76]
                if (e.getKeyChar() == '-') canvas.ajustarGrosor(-2); // [cite: 89]
            }
        });
    }
}