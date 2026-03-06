import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.*;

public class outlook extends JFrame {
    public outlook () {
        setTitle("GUI Outlook");
        setLayout(new BorderLayout(16, 16)); //Los números indican la separación entre las partes norte, sur...
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(280,570);
        setLocationRelativeTo(null);

        //Barra superior
        JPanel header = new JPanel(new FlowLayout(FlowLayout.LEFT, 0, 0));
        header.setPreferredSize(new Dimension(0, 20));
        header.add(createPanel(Color.GREEN, 25, 20));
        header.add(createPanel(Color.RED, 190, 20));
        header.add(createPanel(Color.GREEN, 25, 20));
        header.add(createPanel(Color.BLUE, 25, 20));

        // Contenido central
        JPanel center = new JPanel();

        // Pie de página
        JPanel footer = new JPanel();
        footer.setBackground(Color.DARK_GRAY);
        footer.setPreferredSize(new Dimension(0, 30));
        add(header, BorderLayout.NORTH);
        add(center, BorderLayout.CENTER);
        add(footer, BorderLayout.SOUTH);
        setVisible(true);
    }

    private JPanel createPanel(Color color, int w, int h) {
        JPanel p = new JPanel();
        p.setBackground(color);
        p.setPreferredSize(new Dimension(w, h));
        return p;
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(outlook::new);
    }
}
