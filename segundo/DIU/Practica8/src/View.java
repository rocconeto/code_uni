import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.*;

public class View extends JFrame {
    public JButton btnRojo, btnVerde, btnAzul, btnIzq, btnDer, btnArriba, btnAbajo, btnColor;
    private DrawCanvas canvas;
    private Model model;

    public View(Model model) {
        this.model = model;
        setTitle("Práctica 8 - MVC");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        // Panel Izquierdo
        JPanel panelIzquierdo = new JPanel(new GridLayout(3, 1, 15, 15));
        panelIzquierdo.setPreferredSize(new Dimension(220, 0));
        panelIzquierdo.setBackground(Color.GRAY);
        panelIzquierdo.setBorder(new EmptyBorder(15, 15, 15, 15));

        btnRojo = new JButton("Rojo"); btnRojo.setBackground(Color.RED);
        btnVerde = new JButton("Verde"); btnVerde.setBackground(Color.GREEN);
        btnAzul = new JButton("Azul"); btnAzul.setBackground(Color.BLUE);
        panelIzquierdo.add(btnRojo); panelIzquierdo.add(btnVerde); panelIzquierdo.add(btnAzul);

        // Canvas
        canvas = new DrawCanvas();
        canvas.setPreferredSize(new Dimension(550, 300));

        // Panel Inferior
        JPanel btnPanel = new JPanel(new FlowLayout());
        btnIzq = new JButton("Mover Izquierda");
        btnDer = new JButton("Mover Derecha");
        btnArriba = new JButton("Mover Arriba");
        btnAbajo = new JButton("Mover Abajo");
        btnColor = new JButton("Color Aleatorio");
        btnPanel.add(btnIzq); btnPanel.add(btnDer); btnPanel.add(btnArriba);
        btnPanel.add(btnAbajo); btnPanel.add(btnColor);

        add(panelIzquierdo, BorderLayout.WEST);
        add(canvas, BorderLayout.CENTER);
        add(btnPanel, BorderLayout.SOUTH);
        pack();
        setLocationRelativeTo(null);
    }

    public void actualizar() {
        canvas.setBackground(model.getCanvasColor());
        canvas.repaint();
        requestFocus();
    }

    class DrawCanvas extends JPanel {
        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            g.setColor(model.getLineColor());
            g.drawLine(model.getvX1(), model.getvY1(), model.getvX2(), model.getvY2());
            g.drawLine(model.gethX1(), model.gethY1(), model.gethX2(), model.gethY2());
        }
    }
}