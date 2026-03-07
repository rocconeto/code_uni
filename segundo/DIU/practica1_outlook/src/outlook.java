import javax.swing.*;
import java.awt.*;

public class outlook extends JFrame {
    public outlook() {
        //Creamos y delimitamos el tamaño del JFrame
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
        
        //Panel rojo del header con etiqueta
        JPanel headerRed = createPanel(Color.RED);
        headerRed.add(new JLabel("Header"));
        gbc.weightx = 0.7; header.add(headerRed, gbc);

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
        //Panel del footer con label
        JPanel foot = createPanel(Color.YELLOW);
        foot.add(new JLabel("Footer"));
        footer.add(foot);

        principal.add(footer, BorderLayout.SOUTH);
        setVisible(true);
    }

    //Método para crear panels
    private JPanel createPanel(Color color) {
        JPanel p = new JPanel();
        p.setBackground(color);
        return p;
    }

    //Método para crear los bloques de la parte central
    private JPanel crearBloqueCorreo() {
        JPanel c = new JPanel(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.fill = GridBagConstraints.BOTH;
        gbc.weighty = 1.0;

        //Panel del avatar o logo con label, para que se vea tengo que ponerlo en blanco
        JPanel avatar = createPanel(Color.DARK_GRAY);
        JLabel l = new JLabel("Avatar");
        l.setForeground(Color.WHITE);
        avatar.add(l);
        c.add(avatar,gbc);
        gbc.weightx = 0.8; c.add(bloques(), gbc);
        return c;
    }

    //Método auxiliar para crear los bloques tricolor de la parte central
    private JPanel bloques() {
        JPanel b = new JPanel(new GridLayout(3, 1));

        //Panel negro (asunto) con label, para que se vea tengo que ponerlo en blanco
        JPanel asunto = createPanel(Color.BLACK);
        JLabel l = new JLabel("Asunto");
        l.setForeground(Color.WHITE);
        asunto.add(l);
        b.add(asunto);
        b.add(createPanel(Color.LIGHT_GRAY));
        b.add(createPanel(Color.PINK));
        return b;
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(outlook::new);
    }
}