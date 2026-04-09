import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.ArrayList;

public class Practica4 extends JFrame {
    private static final int WIDTH = 600;
    private static final int HEIGHT = 400;
    private static final int TIMER_DELAY = 50;

    private int ballX = 100, ballY = 100;
    private int stepSize = 5;
    private boolean movingRight = true;
    private boolean movingDown = true;
    private int currentFrame = 0;

    private Timer timer;
    private final DrawCanvas canvas;
    private final JLabel labelCoords;
    private final ArrayList<Point> trail = new ArrayList<>();

    private ImageIcon[] framesRight;
    private ImageIcon[] framesLeft;

    public Practica4() {
        setTitle("Práctica 4");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(false);
        setLayout(new BorderLayout());

        cargarImagenes();

        canvas = new DrawCanvas();
        canvas.setPreferredSize(new Dimension(WIDTH, HEIGHT));
        add(canvas, BorderLayout.CENTER);

        JPanel controlPanel = new JPanel(new GridLayout(2, 1));
        JPanel topRow = new JPanel(new FlowLayout());
        JButton btnStart = new JButton("Iniciar");
        JButton btnPause = new JButton("Pausar");
        labelCoords = new JLabel("Coordenadas: (X: 100, Y: 100)");

        btnStart.addActionListener(e -> timer.start());
        btnPause.addActionListener(e -> timer.stop());

        topRow.add(btnStart);
        topRow.add(btnPause);
        topRow.add(labelCoords);

        JPanel bottomRow = new JPanel(new FlowLayout());
        JSlider sliderSpeed = new JSlider(1, 20, stepSize);
        sliderSpeed.setMajorTickSpacing(5);
        sliderSpeed.setPaintTicks(true);
        sliderSpeed.setPaintLabels(true);
        sliderSpeed.addChangeListener(e -> stepSize = sliderSpeed.getValue());

        bottomRow.add(new JLabel("Velocidad (1-20): "));
        bottomRow.add(sliderSpeed);

        controlPanel.add(topRow);
        controlPanel.add(bottomRow);
        add(controlPanel, BorderLayout.SOUTH);

        timer = new Timer(TIMER_DELAY, e -> updateLogic());

        pack();
        setLocationRelativeTo(null);
        setVisible(true);
    }

    private void cargarImagenes() {
        // Carga de sprites
        framesRight = new ImageIcon[]{
                new ImageIcon(getClass().getResource("/resources/pacman.gif")),
                new ImageIcon(getClass().getResource("/resources/right1.gif")),
                new ImageIcon(getClass().getResource("/resources/right2.gif")),
                new ImageIcon(getClass().getResource("/resources/right3.gif"))
        };

        // Movimiento a la izquierda
        framesLeft = framesRight;
    }

    private void updateLogic() {
        // Rastro si hay movimiento
        trail.add(new Point(ballX, ballY));
        if (trail.size() > 10) trail.remove(0);

        // Logica de rebote en los 4 bordes
        int spriteW = (framesRight[0] != null) ? framesRight[0].getIconWidth() : 50;
        int spriteH = (framesRight[0] != null) ? framesRight[0].getIconHeight() : 50;

        if (movingRight) {
            if (ballX + spriteW + stepSize < WIDTH) ballX += stepSize;
            else movingRight = false;
        } else {
            if (ballX - stepSize > 0) ballX -= stepSize;
            else movingRight = true;
        }

        if (movingDown) {
            if (ballY + spriteH + stepSize < HEIGHT) ballY += stepSize;
            else movingDown = false;
        } else {
            if (ballY - stepSize > 0) ballY -= stepSize;
            else movingDown = true;
        }

        currentFrame = (currentFrame + 1) % framesRight.length;
        labelCoords.setText("Coordenadas: (X: " + ballX + ", Y: " + ballY + ")");
        canvas.repaint();
    }

    private class DrawCanvas extends JPanel {
        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            Graphics2D g2d = (Graphics2D) g;
            g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
            setBackground(Color.BLACK);

            if (framesRight[0] == null) return;

            int spriteW = framesRight[0].getIconWidth();
            int spriteH = framesRight[0].getIconHeight();

            // Dibujo de la estela
            for (int i = 0; i < trail.size(); i++) {
                Point p = trail.get(i);
                float alpha = (i + 1) * 0.07f; // Opacidad creciente 
                int size = (spriteW * (i + 1)) / 12; // Tamaño creciente

                g2d.setColor(new Color(1.0f, 1.0f, 0.0f, alpha));
                g2d.fillOval(p.x + (spriteW - size) / 2, p.y + (spriteH - size) / 2, size, size);
            }

            // Selección de set de imágenes según dirección
            ImageIcon[] currentSet = movingRight ? framesRight : framesLeft;
            currentSet[currentFrame].paintIcon(this, g2d, ballX, ballY);
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(Practica4::new);
    }
}