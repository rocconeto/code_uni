import javax.swing.SwingUtilities;
import java.awt.event.*;
import java.awt.*;
import javax.swing.*;

public class Ej1_ClickMe extends JFrame implements ActionListener {
    JButton b = new JButton("Click me!");

    public Ej1_ClickMe() {
        setTitle("Ejemplo 1");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        b.addActionListener(this);
        add(b);

        pack();
        setVisible(true);
    }

    public void actionPerformed(ActionEvent e) {
        b.setBackground(Color.CYAN);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(Ej1_ClickMe::new);
    }
}