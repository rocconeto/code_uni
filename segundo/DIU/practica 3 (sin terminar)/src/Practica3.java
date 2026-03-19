import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.Random;

public class Practica3 extends JFrame {
    // Constantes de tamaño
    private static final int CANVAS_WIDTH = 400;
    private static final int CANVAS_HEIGHT = 400;
    private JPanel panelIzquierdo;
    private DrawCanvas canvas; // El canvas es nuestro panel de la derecha

    // Color de las líneas
    private Color currentLineColor = Color.BLACK;

    // Línea Vertical y Horizontal
    private int vX1 = CANVAS_WIDTH / 2, vY1 = 20;
    private int vX2 = vX1, vY2 = CANVAS_HEIGHT - 20;
    private int hX1 = 20, hY1 = CANVAS_HEIGHT / 2;
    private int hX2 = CANVAS_WIDTH - 20, hY2 = hY1;

    public Practica3() {
        setTitle("Práctica 3 - Integración");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        //Zona izquierda para los botones
        panelIzquierdo = new JPanel(new GridLayout(3, 1, 5, 5));
        panelIzquierdo.setPreferredSize(new Dimension(250, 0));
        panelIzquierdo.setBackground(Color.GRAY);

        panelIzquierdo.add(new JLabel("Espacio Botón Rojo", SwingConstants.CENTER));
        panelIzquierdo.add(new JLabel("Espacio Botón Verde", SwingConstants.CENTER));
        panelIzquierdo.add(new JLabel("Espacio Botón Azul", SwingConstants.CENTER));

        //Zona derecha en la que se cambia de color y mueven las lineas
        canvas = new DrawCanvas();
        canvas.setPreferredSize(new Dimension(CANVAS_WIDTH, CANVAS_HEIGHT));
        canvas.setBackground(Color.LIGHT_GRAY);

        //Panel inferior con los botones para las lineas
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

        //Añadir todo al JFrame
        add(panelIzquierdo, BorderLayout.WEST);
        add(canvas, BorderLayout.CENTER);
        add(btnPanel, BorderLayout.SOUTH);

        //Para que funcionen las teclas del teclado
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
        setLocationRelativeTo(null);
        setVisible(true);
        requestFocus();
    }

    private void actualizar() {
        canvas.repaint();
        requestFocus();
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new Practica3());
    }

    // Clase para el dibujo
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