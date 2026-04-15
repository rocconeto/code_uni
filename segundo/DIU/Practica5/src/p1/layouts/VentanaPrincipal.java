package p1.layouts;

import javax.swing.*;
import java.awt.*;
import p2.java2d.PaletaPanel;
import p4.animacion.SpritePanel;
import p3.eventos.GestionEventos;

public class VentanaPrincipal extends JFrame {
    private SpritePanel canvas;
    private PaletaPanel paleta;
    private JLabel lblEstado;

    public VentanaPrincipal() {
        setTitle("MiniEstudio de Diseño - Práctica 5");
        setResizable(false); // REQUISITO: No redimensionable
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        lblEstado = new JLabel("Coordenadas: (0,0) | Color: #000000 | Grosor: 6px");
        canvas = new SpritePanel(lblEstado);
        paleta = new PaletaPanel(canvas);

        // NORTH: Herramientas [cite: 34]
        JPanel panelNorte = new JPanel(new FlowLayout());
        panelNorte.setPreferredSize(new Dimension(800, 50));
        panelNorte.add(new JLabel("[Layout: FlowLayout] ")); // REQUISITO: Etiqueta [cite: 36]
        JButton btnIn = new JButton("Iniciar");
        JButton btnPa = new JButton("Pausar");
        btnIn.addActionListener(e -> { canvas.getTimer().start(); canvas.requestFocus(); });
        btnPa.addActionListener(e -> canvas.getTimer().stop());
        panelNorte.add(btnIn); panelNorte.add(btnPa);
        add(panelNorte, BorderLayout.NORTH);

        // SOUTH: Barra de estado y Slider [cite: 34, 103]
        JPanel panelSur = new JPanel(new FlowLayout());
        panelSur.setPreferredSize(new Dimension(800, 40));
        panelSur.add(new JLabel("[Layout: FlowLayout] "));
        panelSur.add(lblEstado);
        JSlider slider = new JSlider(1, 20, 5);
        slider.addChangeListener(e -> canvas.setStepSize(slider.getValue()));
        panelSur.add(new JLabel("Velocidad:"));
        panelSur.add(slider);
        add(panelSur, BorderLayout.SOUTH);

        add(paleta, BorderLayout.WEST);   // p2 [cite: 34]
        add(canvas, BorderLayout.CENTER); // p4 [cite: 34]

        GestionEventos.asignar(canvas); // p3

        pack();
        setSize(800, 600); // REQUISITO: Tamaño fijo
        setLocationRelativeTo(null);
    }
}