import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.*;

public class outlook extends JFrame {
    public outlook() {
        setTitle("GUI Outlook");
        setSize(280, 570);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        //JPanel principal
        JPanel principal = new JPanel(new BorderLayout(16, 16));
        this.add(principal);

        //Header
        JPanel header = new JPanel(new GridBagLayout());
        header.setPreferredSize(new Dimension(0, 20));
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.fill = GridBagConstraints.BOTH;
        gbc.weighty = 1.0;

        gbc.weightx = 0.1; header.add(createPanel(Color.GREEN), gbc);
        gbc.weightx = 0.7; header.add(createPanel(Color.RED), gbc);
        gbc.weightx = 0.1; header.add(createPanel(Color.GREEN), gbc);
        gbc.weightx = 0.1; header.add(createPanel(Color.BLUE), gbc);
        principal.add(header, BorderLayout.NORTH);

        //Center
        JPanel center = new JPanel(new GridLayout(0, 1, 0, 8));
        for(int i = 0; i < 6; i++) {
            center.add(crearBloqueCorreo());
        }

        principal.add(center, BorderLayout.CENTER);

        //Footer
        JPanel footer = new JPanel(new GridLayout(1, 4, 16, 0));
        footer.setPreferredSize(new Dimension(0, 60));

        footer.add(createPanel(Color.RED));
        footer.add(createPanel(Color.GREEN));
        footer.add(createPanel(Color.BLUE));
        footer.add(createPanel(Color.YELLOW));

        principal.add(footer, BorderLayout.SOUTH);
        setVisible(true);
    }

    private JPanel createPanel(Color color) {
        JPanel p = new JPanel();
        p.setBackground(color);
        return p;
    }

    private JPanel crearBloqueCorreo() {
        JPanel p = new JPanel(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.fill = GridBagConstraints.BOTH;
        gbc.weighty = 1.0;

        gbc.weightx = 0.2; p.add(createPanel(Color.DARK_GRAY), gbc);
        gbc.weightx = 0.8; p.add(bloques(), gbc);
        return p;
    }

    private JPanel bloques() {
        JPanel p = new JPanel(new GridLayout(3, 1));
        p.add(createPanel(Color.BLACK));
        p.add(createPanel(Color.LIGHT_GRAY));
        p.add(createPanel(Color.PINK));
        return p;
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(outlook::new);
    }
}