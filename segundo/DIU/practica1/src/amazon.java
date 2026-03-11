import java.awt.*;
import javax.swing.*;
import javax.swing.border.EmptyBorder;

public class amazon extends JFrame {

    public amazon() {
        setTitle("Ej. Lab 1");
        setSize(280, 570);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel mainPanel = new JPanel(new BorderLayout(0, 8));
        mainPanel.setBorder(new EmptyBorder(16, 16, 16, 16));
        mainPanel.setBackground(Color.WHITE);

        // Header (verde y rojo)
        JPanel header = new JPanel(new GridBagLayout());
        header.setPreferredSize(new Dimension(280, 60));
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.fill = GridBagConstraints.BOTH;
        gbc.weighty = 1.0;

        gbc.weightx = 0.2;
        JPanel greenPanel = createPanel(Color.GREEN);
        greenPanel.setLayout(new BorderLayout());
        JLabel logo = new JLabel("Logo", SwingConstants.CENTER);
        logo.setForeground(Color.WHITE);
        greenPanel.add(logo);
        header.add(greenPanel, gbc);

        gbc.weightx = 0.8;
        header.add(createPanel(Color.RED), gbc);

        // Cuerpo central
        JPanel body = new JPanel(new GridLayout(1, 2, 8, 0));
        body.setOpaque(false);

        JPanel leftCol = new JPanel(new GridLayout(2, 1, 0, 8));
        leftCol.setOpaque(false);
        JPanel pNegro = createPanel(Color.BLACK);
        pNegro.setLayout(new BorderLayout());
        JLabel lProd = new JLabel("Producto", SwingConstants.CENTER);
        lProd.setForeground(Color.WHITE);
        pNegro.add(lProd);
        leftCol.add(pNegro);
        leftCol.add(createPanel(Color.BLACK));

        JPanel rightCol = new JPanel(new GridLayout(6, 1, 0, 8));
        rightCol.setOpaque(false);
        for (int i = 0; i < 6; i++) {
            JPanel p = createPanel(Color.GRAY);
            if (i == 0) {
                p.setLayout(new BorderLayout());
                JLabel info = new JLabel("info", SwingConstants.CENTER);
                info.setForeground(Color.WHITE);
                p.add(info);
            }
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

        JPanel pAzul = createPanel(Color.BLUE);
        pAzul.setLayout(new BorderLayout());
        JLabel lCar = new JLabel("Carrito", SwingConstants.CENTER);
        lCar.setForeground(Color.WHITE);
        pAzul.add(lCar);
        footer.add(pAzul);

        footer.add(createPanel(Color.YELLOW));

        mainPanel.add(header, BorderLayout.NORTH);
        mainPanel.add(body, BorderLayout.CENTER);
        mainPanel.add(footer, BorderLayout.SOUTH);

        add(mainPanel);
        setVisible(true);
    }

    private JPanel createPanel(Color color) {
        JPanel p = new JPanel();
        p.setBackground(color);
        return p;
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(amazon::new);
    }
}