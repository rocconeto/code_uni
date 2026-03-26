import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.Random;

public class Ej4_KeyAdapter extends JFrame {

    private static final int CANVAS_WIDTH = 400, CANVAS_HEIGHT = 140;
    private static final Color BG_COLOR = Color.CYAN;

    // Color que cambiará con el botón
    private Color currentLineColor = Color.BLACK;

    // Línea 1 (Vertical - se mueve izq/der)
    private int vX1 = CANVAS_WIDTH / 2, vY1 = CANVAS_HEIGHT / 8;
    private int vX2 = vX1, vY2 = CANVAS_HEIGHT * 7 / 8;

    // Línea 2 (Horizontal - se mueve arriba/abajo)
    private int hX1 = CANVAS_WIDTH / 8, hY1 = CANVAS_HEIGHT / 2;
    private int hX2 = CANVAS_WIDTH * 7 / 8, hY2 = hY1;

    private DrawCanvas canvas;

    public Ej4_KeyAdapter() {
        setTitle("Mover Lineas y Color Aleatorio");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setLayout(new BorderLayout());

        JPanel btnPanel = new JPanel(new FlowLayout());

        // --- BOTONES IZQUIERDA / DERECHA ---
        JButton btnIzq = new JButton("Mover Izquierda");
        btnPanel.add(btnIzq);
        btnIzq.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                vX1 -= 10; vX2 -= 10;
                actualizar();
            }
        });

        JButton btnDer = new JButton("Mover Derecha");
        btnPanel.add(btnDer);
        btnDer.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                vX1 += 10; vX2 += 10;
                actualizar();
            }
        });

        // --- BOTONES ARRIBA / ABAJO ---
        JButton btnArriba = new JButton("Mover Arriba");
        btnPanel.add(btnArriba);
        btnArriba.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                hY1 -= 10; hY2 -= 10; // Restar sube en la pantalla
                actualizar();
            }
        });

        JButton btnAbajo = new JButton("Mover Abajo");
        btnPanel.add(btnAbajo);
        btnAbajo.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                hY1 += 10; hY2 += 10; // Sumar baja en la pantalla
                actualizar();
            }
        });

        // --- BOTÓN COLOR (¡Ahora añadido al panel!) ---
        JButton btnColor = new JButton("Color Aleatorio");
        btnPanel.add(btnColor); // ESTA LÍNEA FALTABA
        btnColor.addActionListener(e -> {
            Random rand = new Random();
            currentLineColor = new Color(rand.nextInt(256), rand.nextInt(256), rand.nextInt(256));
            actualizar();
        });

        canvas = new DrawCanvas();
        canvas.setPreferredSize(new Dimension(CANVAS_WIDTH, CANVAS_HEIGHT));

        add(canvas, BorderLayout.CENTER);
        add(btnPanel, BorderLayout.SOUTH);

        // --- TECLADO ---
        addKeyListener(new KeyAdapter() {
            public void keyPressed(KeyEvent evt) {
                switch (evt.getKeyCode()) {
                    case KeyEvent.VK_LEFT:  vX1 -= 10; vX2 -= 10; break;
                    case KeyEvent.VK_RIGHT: vX1 += 10; vX2 += 10; break;
                    case KeyEvent.VK_UP:    hY1 -= 10; hY2 -= 10; break;
                    case KeyEvent.VK_DOWN:  hY1 += 10; hY2 += 10; break;
                }
                canvas.repaint();
            }
        });

        pack();
        setVisible(true);
        requestFocus();
    }

    private void actualizar() {
        canvas.repaint();
        requestFocus();
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(Ej4_KeyAdapter::new);
    }

    class DrawCanvas extends JPanel {
        @Override
        public void paintComponent(Graphics g) {
            super.paintComponent(g);
            this.setBackground(BG_COLOR);
            g.setColor(currentLineColor);

            // Dibuja las dos líneas usando sus respectivas variables
            g.drawLine(vX1, vY1, vX2, vY2); // Línea Vertical
            g.drawLine(hX1, hY1, hX2, hY2); // Línea Horizontal
        }
    }
}