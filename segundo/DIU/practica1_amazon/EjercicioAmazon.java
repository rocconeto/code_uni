import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.*;

public class EjercicioAmazon extends JFrame {

    public EjercicioAmazon() {
        // ventana 280x570
        setTitle("Ej. Lab 1");
        setSize(280, 570);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        // Panel principal
        JPanel mainPanel = new JPanel(new BorderLayout(0, 8));
        mainPanel.setBorder(new EmptyBorder(16, 16, 16, 16));
        mainPanel.setBackground(Color.WHITE);

        // Header
        JPanel header = new JPanel(new GridBagLayout());
        header.setPreferredSize(new Dimension(280, 60));
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.fill = GridBagConstraints.BOTH;
        gbc.weighty = 1.0;

        // Panel verde
        gbc.weightx = 0.2;
        JPanel greenPanel = createPanel(Color.GREEN); // Verde bosque
        greenPanel.add(createCenteredLabel("Logo", Color.WHITE));
        header.add(greenPanel, gbc);

        // Panel rojo
        gbc.weightx = 0.8;
        header.add(createPanel(Color.RED), gbc);

        // Centro
        JPanel body = new JPanel(new GridLayout(1, 2, 8, 0));
        body.setOpaque(false);

        // Columna izquierda
        JPanel leftCol = new JPanel(new GridLayout(2, 1, 0, 8));
        leftCol.setOpaque(false);

        // Cuadro negro con label
        JPanel blackPanel = createPanel(Color.BLACK);
        blackPanel.add(createCenteredLabel("Producto", Color.WHITE));
        leftCol.add(blackPanel);
        leftCol.add(createPanel(Color.BLACK));

        // Columna derecha
        JPanel rightCol = new JPanel(new GridLayout(6, 1, 0, 8));
        rightCol.setOpaque(false);
        for (int i = 0; i < 6; i++) {
            JPanel p = createPanel(Color.GRAY);
            if(i == 0) p.add(crearLabel("Info", Color.WHITE));
            rightCol.add(p);
        }

        body.add(leftCol);
        body.add(rightCol);

        // Footer
        JPanel footer = new JPanel(new GridLayout(1, 4, 8, 0));
        footer.setPreferredSize(new Dimension(280, 60));
        footer.setOpaque(false);

        footer.add(createPanel(Color.RED));
        footer.add(createPanel(Color.GREEN));

        // Panel azul
        JPanel bluePanel = createPanel(Color.BLUE);
        bluePanel.add(crearLabel("Carrito"));
        footer.add(bluePanel);

        footer.add(createPanel(Color.YELLOW));

        // Ensamblaje final
        mainPanel.add(header, BorderLayout.NORTH);
        mainPanel.add(body, BorderLayout.CENTER);
        mainPanel.add(footer, BorderLayout.SOUTH);

        add(mainPanel);
        setVisible(true);
    }

    // Método auxiliar para crear penels
    private JPanel crearPanel(Color color) {
        JPanel p = new JPanel(new BorderLayout());
        p.setBackground(color);
        return p;
    }

    // Método para crear labels
    private JLabel crearLabel(String text) {
        return new = JLabel(text, SwingConstants.CENTER);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(EjercicioAmazon::new);
    }
}