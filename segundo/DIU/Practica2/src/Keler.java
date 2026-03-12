import javax.swing.*;
import java.awt.*;

//Daniel Atanasov Angelov y Raul Sanz Tomé
public class Keler extends JFrame {
    public Keler() {
        setTitle("Lab 2. Ej");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(false);
        add(new KelerPanel());
        pack();
        setLocationRelativeTo(null);
        setVisible(true);
    }
    public static void main(String[] args) {
        SwingUtilities.invokeLater(Keler::new);
    }
}

class KelerPanel extends JPanel {
    private static final Color PETER_RED = new Color(198, 58, 33);
    private static final Color PETER_YELLOW = new Color(230, 183, 31);
    private static final Color PETER_BLUE = new Color(63, 75, 148);
    private static final Color PETER_DARK_GREY = new Color(76, 76, 76);
    private static final Color PETER_MID_GREY = new Color(130, 130, 130);
    private static final Color PETER_LIGHT_GREY = new Color(162, 162, 162);
    private static final Color HEADER_BG = new Color(245, 245, 245);

    private final int W = 315;
    private final int H_CANVAS = 440;
    private final int H_HEAD = 40;

    public KelerPanel() {
        setPreferredSize(new Dimension(W, H_HEAD + H_CANVAS));
        setBackground(Color.WHITE);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D) g;
        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

        // Fondo del header
        g2d.setColor(HEADER_BG);
        g2d.fillRect(0, 0, W, H_HEAD); // Rellena el área del encabezado

        // Texto del header
        g2d.setColor(Color.BLACK);
        g2d.setFont(new Font("Arial", Font.BOLD, 18));
        g2d.drawString("Peter Keler", 10, 22);
        g2d.setFont(new Font("Arial", Font.PLAIN, 10));
        g2d.drawString("De Stijl 1", 10, 32);

        // Grid 15x18
        double cw = W / 15.0;
        double ch = H_CANVAS / 18.0;

        int x6 = r(6 * cw);
        int y12 = r(12 * ch);
        int y17 = r(17 * ch);

        // Amarillo y rojo
        int x2 = r(2 * cw);
        g2d.setColor(PETER_YELLOW);
        g2d.fillRect(x2, H_HEAD, x6 - x2, y12);

        g2d.setColor(PETER_RED);
        g2d.fillRect(x6, H_HEAD, W - x6, y12);

        // azul
        g2d.setColor(PETER_BLUE);
        g2d.fillRect(0, H_HEAD + y12, x6, H_CANVAS - y12);

        // Zona de cuadrados grises
        int gap = y17 - y12;
        int hGris = gap / 2;
        int yGris = H_HEAD + y12 + (gap - hGris);

        int wG = (W - x6) / 3;
        g2d.setColor(PETER_DARK_GREY);
        g2d.fillRect(x6, yGris, wG, hGris);

        g2d.setColor(PETER_MID_GREY);
        g2d.fillRect(x6 + wG, yGris, wG, hGris);

        g2d.setColor(PETER_LIGHT_GREY);
        g2d.fillRect(x6 + 2 * wG, yGris, (W - x6) - 2 * wG, hGris);

        // Barra negra
        g2d.setColor(Color.BLACK);
        g2d.fillRect(x6, H_HEAD + y17, W - x6, H_CANVAS - y17);
    }

    private int r(double val) {
        return (int) Math.round(val);
    }
}