import javax.swing.SwingUtilities;
import java.awt.event.*;
import javax.swing.*;

public class Ej2_ContadorClicks extends JFrame {
    private static String labelPrefijo = "Número de clicks sobre el botón: ";
    private int numClicks = 0;
    private JLabel label = new JLabel(labelPrefijo + "0 ");

    public Ej2_ContadorClicks() {
        setTitle("Ejemplo 2");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JButton button = new JButton("Cuenta");
        button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                label.setText(labelPrefijo + ++numClicks);
            }
        });

        JPanel panel = new JPanel();
        panel.add(button);
        panel.add(label);
        add(panel);

        pack();
        setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(Ej2_ContadorClicks::new);
    }
}