import javax.sound.sampled.*;
import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.*;
import java.io.File;
import java.util.ArrayList;

public class Ejercicio7_3 extends JFrame {
    private Clip clip;
    private long totalDurationMicros, currMicrosPosition;
    private Thread t;

    private DefaultListModel<String> listModel;
    private JList<String> songList;
    private ArrayList<File> files;

    private JButton addBtn, playBtn, pauseBtn, stopBtn;
    private JSlider slider;
    private JLabel labelDuration;
    private boolean sliderUpdating = false;

    public Ejercicio7_3() {
        setTitle("Reproductor con Lista");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        files = new ArrayList<>();

        // Panel Izquierdo (WEST)
        listModel = new DefaultListModel<>();
        songList = new JList<>(listModel);
        songList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        JScrollPane scrollPane = new JScrollPane(songList);

        addBtn = new JButton("Añadir");

        JPanel leftPanel = new JPanel(new BorderLayout());
        leftPanel.setPreferredSize(new Dimension(200, 0));
        leftPanel.add(scrollPane, BorderLayout.CENTER);
        leftPanel.add(addBtn, BorderLayout.SOUTH);

        // Panel Central (CENTER)
        JPanel centerPanel = new JPanel(new FlowLayout());
        playBtn = new JButton(new ImageIcon(getClass().getResource("/play.png")));
        pauseBtn = new JButton(new ImageIcon(getClass().getResource("/pausa.png")));
        stopBtn = new JButton(new ImageIcon(getClass().getResource("/stop.png")));
        slider = new JSlider(0, 100, 0);
        labelDuration = new JLabel("0 seg");

        playBtn.setEnabled(false);
        pauseBtn.setEnabled(false);
        stopBtn.setEnabled(false);

        centerPanel.add(playBtn);
        centerPanel.add(pauseBtn);
        centerPanel.add(stopBtn);
        centerPanel.add(slider);
        centerPanel.add(labelDuration);

        add(leftPanel, BorderLayout.WEST);
        add(centerPanel, BorderLayout.CENTER);

        // Listeners Panel Izquierdo
        addBtn.addActionListener(e -> {
            JFileChooser fc = new JFileChooser();
            fc.setFileFilter(new FileNameExtensionFilter("WAV Files", "wav"));
            if (fc.showOpenDialog(this) == JFileChooser.APPROVE_OPTION) {
                File f = fc.getSelectedFile();
                listModel.addElement(f.getName());
                files.add(f);
            }
        });

        songList.addListSelectionListener(e -> {
            if (e.getValueIsAdjusting()) return;
            int idx = songList.getSelectedIndex();
            if (idx < 0) return;
            loadAudio(files.get(idx));
        });

        // Listeners Controles
        playBtn.addActionListener(e -> reproducir());
        pauseBtn.addActionListener(e -> pausar());
        stopBtn.addActionListener(e -> detener());

        slider.addChangeListener(e -> {
            if (sliderUpdating || clip == null) return;
            long newPos = (long) (slider.getValue() / 100.0 * totalDurationMicros);
            clip.setMicrosecondPosition(newPos);
            currMicrosPosition = newPos;
        });

        pack();
        setLocationRelativeTo(null);
    }

    private void loadAudio(File f) {
        if (clip != null) {
            clip.stop();
            clip.close();
        }
        if (t != null) t.interrupt();

        currMicrosPosition = 0;

        try {
            clip = AudioSystem.getClip();
            AudioInputStream stream = AudioSystem.getAudioInputStream(f);
            clip.open(stream);
            totalDurationMicros = clip.getMicrosecondLength();

            labelDuration.setText(String.format("%d seg", totalDurationMicros / 1000000));
            slider.setValue(0);

            playBtn.setEnabled(true);
            pauseBtn.setEnabled(false);
            stopBtn.setEnabled(false);
        } catch (Exception ex) {
            JOptionPane.showMessageDialog(this, "Error al cargar el audio");
        }
    }

    private void reproducir() {
        if (clip != null) {
            clip.setMicrosecondPosition(currMicrosPosition);
            clip.start();
            playBtn.setEnabled(false);
            pauseBtn.setEnabled(true);
            stopBtn.setEnabled(true);

            t = new Thread(() -> {
                try {
                    while (clip != null && clip.isRunning()) {
                        long pos = clip.getMicrosecondPosition();
                        long remaining = totalDurationMicros - pos;

                        SwingUtilities.invokeLater(() -> {
                            labelDuration.setText(String.format("%d seg", remaining / 1000000));
                            sliderUpdating = true;
                            slider.setValue((int) (100 * pos / totalDurationMicros));
                            sliderUpdating = false;
                        });
                        Thread.sleep(100);
                    }
                } catch (InterruptedException ignored) {
                } finally {
                    // Si terminó naturalmente (llegó al final)
                    if (clip != null && clip.getMicrosecondPosition() >= totalDurationMicros) {
                        SwingUtilities.invokeLater(() -> {
                            playBtn.setEnabled(true);
                            pauseBtn.setEnabled(false);
                            stopBtn.setEnabled(false);

                            // Avance automático
                            int next = songList.getSelectedIndex() + 1;
                            if (next < listModel.size()) {
                                songList.setSelectedIndex(next);
                                SwingUtilities.invokeLater(() -> playBtn.doClick());
                            }
                        });
                    }
                }
            });
            t.start();
        }
    }

    private void pausar() {
        if (clip != null && clip.isRunning()) {
            currMicrosPosition = clip.getMicrosecondPosition();
            clip.stop();
            playBtn.setEnabled(true);
            pauseBtn.setEnabled(false);
        }
    }

    private void detener() {
        if (clip != null) {
            clip.stop();
            clip.setMicrosecondPosition(0);
            currMicrosPosition = 0;

            sliderUpdating = true;
            slider.setValue(0);
            sliderUpdating = false;

            labelDuration.setText(String.format("%d seg", totalDurationMicros / 1000000));

            playBtn.setEnabled(true);
            pauseBtn.setEnabled(false);
            stopBtn.setEnabled(false);
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new Ejercicio7_3().setVisible(true));
    }
}