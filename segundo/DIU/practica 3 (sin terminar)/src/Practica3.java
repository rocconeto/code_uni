import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.Random;

public class Practica3 extends JFrame {
    private static final int CANVAS_WIDTH = 400;
    private static final int CANVAS_HEIGHT = 400;
    private JPanel panelIzquierdo;
    private DrawCanvas canvas;

    private JButton btnRojo, btnVerde, btnAzul;
    private Color currentLineColor = Color.BLACK;

    private int vX1 = CANVAS_WIDTH / 2, vY1 = 20;
    private int vX2 = vX1, vY2 = CANVAS_HEIGHT - 20;
    private int hX1 = 20, hY1 = CANVAS_HEIGHT / 2;
    private int hX2 = CANVAS_WIDTH - 20, hY2 = hY1;

    public Practica3() {
        setTitle("Práctica 3 - Integración");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        panelIzquierdo = new JPanel(new GridLayout(3, 1, 5, 5));
        panelIzquierdo.setPreferredSize(new Dimension(250, 0));
        panelIzquierdo.setBackground(Color.GRAY);

        // Botón Rojo
        btnRojo = new JButton("Rojo");
        btnRojo.setBackground(Color.RED);
        btnRojo.setForeground(Color.WHITE);
        btnRojo.setToolTipText("Cambia a rojo");
        btnRojo.addActionListener(e -> cambiarFondo(Color.RED, btnRojo));

        // Botón Verde
        btnVerde = new JButton("Verde");
        btnVerde.setBackground(Color.GREEN);
        btnVerde.setToolTipText("Cambia a verde");
        btnVerde.addActionListener(e -> cambiarFondo(Color.GREEN, btnVerde));

        // Botón Azul
        btnAzul = new JButton("Azul");
        btnAzul.setBackground(Color.BLUE);
        btnAzul.setForeground(Color.WHITE);
        btnAzul.setToolTipText("Cambia a azul");
        btnAzul.addActionListener(e -> cambiarFondo(Color.BLUE, btnAzul));

        panelIzquierdo.add(btnRojo);
        panelIzquierdo.add(btnVerde);
        panelIzquierdo.add(btnAzul);

        canvas = new DrawCanvas();
        canvas.setPreferredSize(new Dimension(CANVAS_WIDTH, CANVAS_HEIGHT));
        canvas.setBackground(Color.LIGHT_GRAY);

        JPanel btnPanel = new JPanel(new FlowLayout());

        JButton btnIzq = new JButton("Mover Izquierda");
        btnIzq.addActionListener(e -> { vX1 -= 10; vX2 -= 10; actualizar(); });

        JButton btnDer = new JButton("Mover Derecha");
        btnDer.addActionListener(e -> { vX1 += 10; vX2 += 10; actualizar(); });

        JButton btnArriba = new JButton("Mover Arriba");
        btnArriba.addActionListener(e -> { hY1 -= 10; hY2 -= 10; actualizar(); });

        JButton btnAbajo = new JButton("Mover Abajo");
        btnAbajo.addActionListener(e -> { hY1 += 10; hY2 += 10; actualizar(); });

        JButton btnColor = new JButton("Color Aleatorio");
        btnColor.addActionListener(e -> {
            Random rand = new Random();
            currentLineColor = new Color(rand.nextInt(256), rand.nextInt(256), rand.nextInt(256));
            actualizar();
        });

        btnPanel.add(btnIzq);
        btnPanel.add(btnDer);
        btnPanel.add(btnArriba);
        btnPanel.add(btnAbajo);
        btnPanel.add(btnColor);

        add(panelIzquierdo, BorderLayout.WEST);
        add(canvas, BorderLayout.CENTER);
        add(btnPanel, BorderLayout.SOUTH);

        addKeyListener(new KeyAdapter() {
            @Override
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
        setLocationRelativeTo(null);
        setVisible(true);
        requestFocus();
    }

    private void cambiarFondo(Color c, JButton pulsado) {
        canvas.setBackground(c);
        btnRojo.setEnabled(pulsado != btnRojo);
        btnVerde.setEnabled(pulsado != btnVerde);
        btnAzul.setEnabled(pulsado != btnAzul);
        actualizar();
    }

    private void actualizar() {
        canvas.repaint();
        requestFocus();
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new Practica3());
    }

    class DrawCanvas extends JPanel {
        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            g.setColor(currentLineColor);
            g.drawLine(vX1, vY1, vX2, vY2);
            g.drawLine(hX1, hY1, hX2, hY2);
        }
    }
}