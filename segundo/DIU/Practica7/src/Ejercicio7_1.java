import javax.sound.sampled.*;
import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.*;
import java.io.File;

public class Ejercicio7_1 extends JFrame {
    private JButton btnAbrir, btnPlay, btnPause, btnStop;
    private JSlider slider;
    private JLabel labelDuration;
    private Clip clip;
    private long totalDurationMicros = 0;
    private long currentPosition = 0;
    private Thread updateThread;

    public Ejercicio7_1() {
        setTitle("Reproductor de Audio");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new FlowLayout());

        // Inicializar componentes
        btnAbrir = new JButton(new ImageIcon(getClass().getResource("/abrir.png")));
        btnPlay = new JButton(new ImageIcon(getClass().getResource("/play.png")));
        btnPause = new JButton(new ImageIcon(getClass().getResource("/pausa.png")));
        btnStop = new JButton(new ImageIcon(getClass().getResource("/stop.png")));

        slider = new JSlider(0, 100, 0);
        slider.setEnabled(false); // Nunca activo para el usuario en el Ej 7.1

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

        // Listeners
        btnAbrir.addActionListener(e -> abrirArchivo());
        btnPlay.addActionListener(e -> reproducir());
        btnPause.addActionListener(e -> pausar());
        btnStop.addActionListener(e -> detener());

        pack();
        setLocationRelativeTo(null);
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

            updateThread = new Thread(() -> {
                while (clip != null && clip.isRunning()) {
                    long remaining = totalDurationMicros - clip.getMicrosecondPosition();
                    SwingUtilities.invokeLater(() -> {
                        labelDuration.setText(String.format("%d seg", remaining / 1000000));
                        slider.setValue((int) (100 * clip.getMicrosecondPosition() / totalDurationMicros));
                    });
                    try { Thread.sleep(100); } catch (InterruptedException ignored) {}
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