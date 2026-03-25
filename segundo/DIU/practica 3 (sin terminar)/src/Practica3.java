import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.util.Random;

public class Practica3 extends JFrame {
    // Proporciones para forma de rectángulo tumbado
    private static final int CANVAS_WIDTH = 550;
    private static final int CANVAS_HEIGHT = 300;
    private JPanel panelIzquierdo;
    private DrawCanvas canvas;

    private JButton btnRojo, btnVerde, btnAzul;
    private Color currentLineColor = Color.BLACK;

    private int vX1 = CANVAS_WIDTH / 2, vY1 = 20;
    private int vX2 = vX1, vY2 = CANVAS_HEIGHT - 20;
    private int hX1 = 20, hY1 = CANVAS_HEIGHT / 2;
    private int hX2 = CANVAS_WIDTH - 20, hY2 = hY1;

    public Practica3() {
        setTitle("Ejercicio 1"); // Título según captura
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        // Panel izquierdo con márgenes para que los botones no peguen a los bordes
        panelIzquierdo = new JPanel(new GridLayout(3, 1, 15, 15));
        panelIzquierdo.setPreferredSize(new Dimension(220, 0));
        panelIzquierdo.setBackground(Color.GRAY);
        panelIzquierdo.setBorder(new EmptyBorder(15, 15, 15, 15));

        Font fuenteBotones = new Font("Arial", Font.PLAIN, 22);

        btnRojo = new JButton("Rojo");
        btnRojo.setBackground(Color.RED);
        btnRojo.setForeground(Color.WHITE);
        btnRojo.setFont(fuenteBotones);
        btnRojo.setToolTipText("Cambia a rojo");
        btnRojo.addActionListener(e -> cambiarFondo(Color.RED, btnRojo));

        btnVerde = new JButton("Verde");
        btnVerde.setBackground(Color.GREEN);
        btnVerde.setForeground(Color.WHITE);
        btnVerde.setFont(fuenteBotones);
        btnVerde.setToolTipText("Cambia a verde");
        btnVerde.addActionListener(e -> cambiarFondo(Color.GREEN, btnVerde));

        btnAzul = new JButton("Azul");
        btnAzul.setBackground(Color.BLUE);
        btnAzul.setForeground(Color.WHITE);
        btnAzul.setFont(fuenteBotones);
        btnAzul.setToolTipText("Cambia a azul");
        btnAzul.addActionListener(e -> cambiarFondo(Color.BLUE, btnAzul));

        panelIzquierdo.add(btnRojo);
        panelIzquierdo.add(btnVerde);
        panelIzquierdo.add(btnAzul);

        canvas = new DrawCanvas();
        canvas.setPreferredSize(new Dimension(CANVAS_WIDTH, CANVAS_HEIGHT));
        canvas.setBackground(new Color(180, 185, 200)); // Gris azulado similar a la captura

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