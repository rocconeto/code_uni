import javax.swing.*;
import java.awt.*;

//Daniel Atanasov Angelov y Raul Sanz Tomé
public class Mondrian extends JFrame {

    public Mondrian() {
        setTitle("Piet Mondrian");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(false);
        add(new MondrianPanel());
        pack();
        setLocationRelativeTo(null);
        setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new Mondrian());
    }
}

class MondrianPanel extends JPanel {
    private static final Color MONDRIAN_RED = new Color(237, 28, 36);
    private static final Color MONDRIAN_BLUE = new Color(0, 56, 168);
    private static final Color MONDRIAN_YELLOW = new Color(255, 221, 51);
    private static final Color HEADER_GRAY = new Color(225, 225, 225);

    public MondrianPanel() {
        setPreferredSize(new Dimension(400, 480));
    }

    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D) g;
        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

        //Ponemos el fondo en blanco
        g2d.setColor(Color.WHITE);
        g2d.fillRect(0, 40, 400, 440);

        //Bloque Rojo
        g2d.setColor(MONDRIAN_RED);
        g2d.fillRect(120, 40, 280, 290);

        //Bloque Azul
        g2d.setColor(MONDRIAN_BLUE);
        g2d.fillRect(0, 330, 120, 150);

        //Bloque Negro
        g2d.setColor(Color.BLACK);
        g2d.fillRect(340, 330, 60, 80);

        //Bloque amarillo
        g2d.setColor(MONDRIAN_YELLOW);
        g2d.fillRect(340, 410, 60, 70);

        //Líneas negras
        g2d.setStroke(new BasicStroke(10.0f));
        g2d.setColor(Color.BLACK);
        g2d.drawLine(120, 40, 120, 480);
        g2d.drawLine(340, 330, 340, 480);
        g2d.drawLine(0, 190, 120, 190);
        g2d.drawLine(0, 330, 400, 330);

        //Añadimos la cabecera en gris con los textos
        g2d.setColor(HEADER_GRAY);
        g2d.fillRect(0, 0, 400, 40);
        g2d.setColor(Color.BLACK);
        g2d.setFont(new Font("Arial", Font.BOLD, 16));
        g2d.drawString("Piet Mondrian", 10, 20);
        g2d.setFont(new Font("Arial", Font.PLAIN, 14));
        g2d.drawString("Composition II", 10, 35);
    }
}