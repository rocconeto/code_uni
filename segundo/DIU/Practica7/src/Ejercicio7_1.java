import javax.sound.sampled.*;
import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.*;
import java.io.File;

public class Ejercicio7_1 extends JFrame {
    // Declaradas como final (soluciona advertencias 'may be final')
    private final JButton btnAbrir, btnPlay, btnPause, btnStop;
    private final JSlider slider;
    private final JLabel labelDuration;

    private Clip clip;
    private long totalDurationMicros = 0;
    private long currentPosition = 0;

    public Ejercicio7_1() {
        setTitle("Reproductor de Audio");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new FlowLayout());

        // Usamos el método seguro para cargar iconos
        btnAbrir = crearIcono("/abrir.png", "Abrir");
        btnPlay = crearIcono("/play.png", "Play");
        btnPause = crearIcono("/pausa.png", "Pausa");
        btnStop = crearIcono("/stop.png", "Stop");

        slider = new JSlider(0, 100, 0);
        slider.setEnabled(false);

        labelDuration = new JLabel("0 seg");

        // Estado inicial de botones
        btnPlay.setEnabled(false);
        btnPause.setEnabled(false);
        btnStop.setEnabled(false);

        // Añadir componentes
        add(btnAbrir);
        add(btnPlay);
        add(btnPause);
        add(btnStop);
        add(slider);
        add(labelDuration);

        // Listeners (nombrando la variable 'e' por si se usara, aunque IntelliJ diga que no se usa)
        btnAbrir.addActionListener(e -> abrirArchivo());
        btnPlay.addActionListener(e -> reproducir());
        btnPause.addActionListener(e -> pausar());
        btnStop.addActionListener(e -> detener());

        pack();
        setLocationRelativeTo(null);
    }

    // --- MÉTODO SEGURO PARA CARGAR IMÁGENES ---
    private JButton crearIcono(String ruta, String textoFallback) {
        java.net.URL imgURL = getClass().getResource(ruta);
        if (imgURL != null) {
            return new JButton(new ImageIcon(imgURL));
        } else {
            // Si no encuentra la imagen, al menos crea un botón con texto y avisa en consola
            System.err.println("Advertencia: No se encontró la imagen: " + ruta);
            return new JButton(textoFallback);
        }
    }

    private void abrirArchivo() {
        if (clip != null && clip.isRunning()) {
            detener();
        }

        JFileChooser fc = new JFileChooser();
        fc.setFileFilter(new FileNameExtensionFilter("WAV Files", "wav"));
        if (fc.showOpenDialog(this) == JFileChooser.APPROVE_OPTION) {
            try {
                File audioFile = fc.getSelectedFile();
                AudioInputStream audioStream = AudioSystem.getAudioInputStream(audioFile);
                clip = AudioSystem.getClip();
                clip.open(audioStream);
                totalDurationMicros = clip.getMicrosecondLength();
                currentPosition = 0;

                labelDuration.setText(String.format("%d seg", totalDurationMicros / 1000000));
                btnPlay.setEnabled(true);
            } catch (Exception ex) {
                JOptionPane.showMessageDialog(this, "Error al cargar el audio.");
            }
        }
    }

    private void reproducir() {
        if (clip != null) {
            clip.setMicrosecondPosition(currentPosition);
            clip.start();

            btnPlay.setEnabled(false);
            btnPause.setEnabled(true);
            btnStop.setEnabled(true);

            // Corrección al bucle del Thread para mejorar el busy-waiting
            Thread updateThread = new Thread(() -> {
                try {
                    while (clip != null && clip.isRunning()) {
                        long remaining = totalDurationMicros - clip.getMicrosecondPosition();
                        SwingUtilities.invokeLater(() -> {
                            labelDuration.setText(String.format("%d seg", remaining / 1000000));
                            slider.setValue((int) (100 * clip.getMicrosecondPosition() / totalDurationMicros));
                        });
                        Thread.sleep(100);
                    }
                } catch (InterruptedException ex) {
                    Thread.currentThread().interrupt(); // Restablecer estado de interrupción
                }
            });
            updateThread.start();
        }
    }

    private void pausar() {
        if (clip != null && clip.isRunning()) {
            currentPosition = clip.getMicrosecondPosition();
            clip.stop();
            btnPlay.setEnabled(true);
            btnPause.setEnabled(false);
        }
    }

    private void detener() {
        if (clip != null) {
            clip.stop();
            clip.setMicrosecondPosition(0);
            currentPosition = 0;
            slider.setValue(0);
            labelDuration.setText(String.format("%d seg", totalDurationMicros / 1000000));

            btnPlay.setEnabled(true);
            btnPause.setEnabled(false);
            btnStop.setEnabled(false);
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new Ejercicio7_1().setVisible(true));
    }
}