import java.awt.Color;
import java.awt.event.*;
import java.util.Random;
import javax.swing.JButton;

public class Controller {
    private Model model;
    private View view;

    public Controller(Model model, View view) {
        this.model = model;
        this.view = view;

        // 1. Configurar que la ventana pueda recibir el foco para el teclado
        view.setFocusable(true);

        // --- LISTENERS DE BOTONES DE COLOR DE FONDO ---
        view.btnRojo.addActionListener(e -> {
            model.setCanvasColor(Color.RED);
            actualizarInterfaz(view.btnRojo);
        });

        view.btnVerde.addActionListener(e -> {
            model.setCanvasColor(Color.GREEN);
            actualizarInterfaz(view.btnVerde);
        });

        view.btnAzul.addActionListener(e -> {
            model.setCanvasColor(Color.BLUE);
            actualizarInterfaz(view.btnAzul);
        });

        // --- LISTENERS DE MOVIMIENTO ---
        view.btnIzq.addActionListener(e -> {
            model.moverHorizontal(-10);
            actualizarInterfaz(null);
        });

        view.btnDer.addActionListener(e -> {
            model.moverHorizontal(10);
            actualizarInterfaz(null);
        });

        view.btnArriba.addActionListener(e -> {
            model.moverVertical(-10);
            actualizarInterfaz(null);
        });

        view.btnAbajo.addActionListener(e -> {
            model.moverVertical(10);
            actualizarInterfaz(null);
        });

        // --- BOTÓN COLOR ALEATORIO ---
        view.btnColor.addActionListener(e -> {
            Random r = new Random();
            model.setLineColor(new Color(r.nextInt(256), r.nextInt(256), r.nextInt(256)));
            actualizarInterfaz(null);
        });

        // --- LISTENER DE TECLADO ---
        view.addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                switch (e.getKeyCode()) {
                    case KeyEvent.VK_LEFT:
                        model.moverHorizontal(-10);
                        break;
                    case KeyEvent.VK_RIGHT:
                        model.moverHorizontal(10);
                        break;
                    case KeyEvent.VK_UP:
                        model.moverVertical(-10);
                        break;
                    case KeyEvent.VK_DOWN:
                        model.moverVertical(10);
                        break;
                }
                view.actualizar(); // Repinta la vista con los nuevos datos del modelo
            }
        });

        // Estado inicial
        view.actualizar();
    }

    /**
     * Método auxiliar para refrescar la vista, gestionar el estado de los botones
     * y devolver el foco a la ventana para que el KeyListener siga funcionando.
     */
    private void actualizarInterfaz(JButton pulsado) {
        // Si se pulsó un botón de color, gestionamos su habilitación/deshabilitación
        if (pulsado != null) {
            view.btnRojo.setEnabled(pulsado != view.btnRojo);
            view.btnVerde.setEnabled(pulsado != view.btnVerde);
            view.btnAzul.setEnabled(pulsado != view.btnAzul);
        }

        // Refrescar el dibujo
        view.actualizar();

        // DEVOLVER EL FOCO A LA VENTANA
        // Esto es CRUCIAL para que las flechas del teclado funcionen tras hacer clic
        view.requestFocusInWindow();
    }
}