import javax.swing.*;
import java.awt.event.*;

public class Ej3_WindowAdapter extends JFrame {
    public Ej3_WindowAdapter() {
        setTitle("Ejemplo 3");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JLabel label = new JLabel("Prueba con WindowAdapter");
        add(label);

        addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                System.exit(0);
            }
        });

        pack();
        setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(Ej3_WindowAdapter::new);
    }
}