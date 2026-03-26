import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Ej2_MovRebote extends JFrame {
    // Constantes
    private static final int WINDOW_WIDTH = 400;
    private static final int WINDOW_HEIGHT = 250;
    private static final int STEP_SIZE = 5;
    private static final int TIMER_DELAY = 10;

    private Timer timer;
    private int ballX = 200;
    private int ballY = 100;
    private boolean movingRight = true;
    private ImageIcon ballIcon;
    private int ballWidth, ballHeight;
    private final DrawCanvas canvas;

    public Ej2_MovRebote() {
        // Carga de la imagen de la pelota
        ballIcon = new ImageIcon(getClass().getResource("/pacman.gif"));
        ballWidth = ballIcon.getIconWidth();
        ballHeight = ballIcon.getIconHeight();

        canvas = new DrawCanvas();
        add(canvas);

        // Configuración del JFrame
        setTitle("Pelota con Rebote");
        setSize(WINDOW_WIDTH + 20, WINDOW_HEIGHT + 40);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);

        // Configuración del temporizador
        timer = new Timer(TIMER_DELAY, e -> updateBallPosition());
    }

    private void updateBallPosition() {
        if (movingRight) {
            // Lógica de rebote derecha
            if (ballX < WINDOW_WIDTH - ballWidth - STEP_SIZE) {
                ballX += STEP_SIZE;
            } else {
                movingRight = false;
            }
        } else {
            // Lógica de rebote izquierda
            if (ballX >= STEP_SIZE) {
                ballX -= STEP_SIZE;
            } else {
                movingRight = true;
            }
        }
        repaint();
    }

    public void startAnimation() {
        timer.start(); //
    }

    private class DrawCanvas extends JPanel {
        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            setBackground(Color.GRAY); //
            g.setColor(Color.BLACK);
            g.fillRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); //
            ballIcon.paintIcon(this, g, ballX, ballY); //
        }
    }

    public static void main(String[] args) {
        // Inicio de la aplicación
        EventQueue.invokeLater(() -> new Ej2_MovRebote().startAnimation());
    }
}