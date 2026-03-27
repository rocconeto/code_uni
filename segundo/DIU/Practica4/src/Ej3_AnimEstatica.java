import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Ej3_AnimEstatica extends JFrame {
    private static final int WINDOW_SIZE = 300;
    private static final int TIMER_DELAY = 100;
    private static final int IMAGE_X = 50;
    private static final int IMAGE_Y = 50;

    private final ImageIcon[] imageArray;
    private int currentImageIndex = 0;
    private final DrawCanvas canvas;
    private final Timer timer;

    public Ej3_AnimEstatica() {
        // Load images
        imageArray = new ImageIcon[] {
                new ImageIcon(getClass().getResource("resources/pacman.gif")),
                new ImageIcon(getClass().getResource("resources/right1.gif")),
                new ImageIcon(getClass().getResource("resources/right2.gif")),
                new ImageIcon(getClass().getResource("resources/right3.gif"))
        };

        // JFrame settings
        setTitle("Static Animation");
        setAlwaysOnTop(true);
        setSize(WINDOW_SIZE, WINDOW_SIZE);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);

        // Set up canvas
        canvas = new DrawCanvas();
        add(canvas, BorderLayout.CENTER);

        // Set up timer
        timer = new Timer(TIMER_DELAY, e -> updateAnimation());
    }

    private void updateAnimation() {
        currentImageIndex = (currentImageIndex + 1) % imageArray.length;
        repaint();
    }

    public void startAnimation() {
        timer.start();
    }

    private class DrawCanvas extends JPanel {
        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            setBackground(Color.GRAY);
            g.setColor(Color.BLACK);
            g.fillRect(0, 0, WINDOW_SIZE, WINDOW_SIZE);
            imageArray[currentImageIndex].paintIcon(this, g, IMAGE_X, IMAGE_Y);
        }
    }

    public static void main(String[] args) {
        EventQueue.invokeLater(() -> new Ej3_AnimEstatica().startAnimation());
    }
}