import javax.sound.sampled.*;
import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;

public class Ejercicio7_2 extends JFrame {
    private JLabel lblPortada, lblTitulo, lblCompositor, lblTiempoTranscurrido, lblTiempoRestante;
    private JSlider slider;
    private JButton btnPrev, btnPlayPause, btnNext;
    private ArrayList<String> canciones;
    private int currSong = 0;

    private Clip clip;
    private long totalDurationMicros = 0;
    private Thread updateThread;

    public Ejercicio7_2() {
        setTitle("Reproductor");
        setSize(300, 360);
        setResizable(false);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new FlowLayout(FlowLayout.CENTER, 5, 10));

        // Lista de canciones
        canciones = new ArrayList<>();
        canciones.add("Sonata No.13 - Ludwig Van Beethoven.wav");
        canciones.add("Double Violin Concerto 1st Movement - Johann Sebastian Bach.wav");
        canciones.add("Nocturne in E flat major Op.9 No.2 - Frédéric François Chopin.wav");

        // Componentes
        lblPortada = new JLabel();
        lblPortada.setPreferredSize(new Dimension(280, 200));
        lblPortada.setHorizontalAlignment(SwingConstants.CENTER);

        JPanel panelTextos = new JPanel(new GridLayout(2, 1));
        lblTitulo = new JLabel("", SwingConstants.CENTER);
        lblTitulo.setFont(lblTitulo.getFont().deriveFont(Font.BOLD));
        lblCompositor = new JLabel("", SwingConstants.CENTER);
        panelTextos.add(lblTitulo);
        panelTextos.add(lblCompositor);
        panelTextos.setPreferredSize(new Dimension(280, 40));

        JPanel panelSlider = new JPanel(new BorderLayout());
        lblTiempoTranscurrido = new JLabel("00:00");
        lblTiempoRestante = new JLabel("-00:00");
        slider = new JSlider(0, 100, 0);
        slider.setEnabled(false);
        panelSlider.add(lblTiempoTranscurrido, BorderLayout.WEST);
        panelSlider.add(slider, BorderLayout.CENTER);
        panelSlider.add(lblTiempoRestante, BorderLayout.EAST);
        panelSlider.setPreferredSize(new Dimension(280, 30));

        JPanel panelBotones = new JPanel(new GridLayout(1, 3, 10, 0));
        btnPrev = new JButton(new ImageIcon(getClass().getResource("/backward.png")));
        btnPlayPause = new JButton(new ImageIcon(getClass().getResource("/play.png")));
        btnNext = new JButton(new ImageIcon(getClass().getResource("/forward.png")));
        panelBotones.add(btnPrev);
        panelBotones.add(btnPlayPause);
        panelBotones.add(btnNext);

        add(lblPortada);
        add(panelTextos);
        add(panelSlider);
        add(panelBotones);

        // Listeners
        btnPlayPause.addActionListener(e -> togglePlayPause());
        btnPrev.addActionListener(e -> cambiarPista(-1));
        btnNext.addActionListener(e -> cambiarPista(1));

        cargarCancion();
    }

    private void cargarCancion() {
        detenerActual();
        String archivo = canciones.get(currSong);

        // Extraer metadatos separando por el guion " - "
        String nombreBase = archivo.substring(0, archivo.lastIndexOf("."));
        String[] partes = nombreBase.split(" - ");
        if(partes.length == 2) {
            lblTitulo.setText(partes[0]);
            lblCompositor.setText(partes[1]);
        }

        // Cargar Portada
        String imgPath = "/" + nombreBase + ".png";
        ImageIcon icono = new ImageIcon(getClass().getResource(imgPath));
        Image imgEscalada = icono.getImage().getScaledInstance(200, 200, Image.SCALE_SMOOTH);
        lblPortada.setIcon(new ImageIcon(imgEscalada));

        // Preparar Audio
        try {
            AudioInputStream stream = AudioSystem.getAudioInputStream(getClass().getResource("/" + archivo));
            clip = AudioSystem.getClip();
            clip.open(stream);
            totalDurationMicros = clip.getMicrosecondLength();
            actualizarEtiquetasTiempo(0);
        } catch (Exception ex) {
            System.err.println("Error cargando " + archivo);
        }
        btnPlayPause.setIcon(new ImageIcon(getClass().getResource("/play.png")));
    }

    private void togglePlayPause() {
        if (clip != null) {
            if (clip.isRunning()) {
                clip.stop();
                btnPlayPause.setIcon(new ImageIcon(getClass().getResource("/play.png")));
            } else {
                clip.start();
                btnPlayPause.setIcon(new ImageIcon(getClass().getResource("/pause.png")));
                iniciarHiloActualizacion();
            }
        }
    }

    private void cambiarPista(int direccion) {
        currSong += direccion;
        if (currSong < 0) currSong = canciones.size() - 1;
        if (currSong >= canciones.size()) currSong = 0;
        cargarCancion();
        togglePlayPause(); // Auto-play
    }

    private void detenerActual() {
        if (clip != null) {
            clip.stop();
            clip.flush();
            clip.close();
        }
        if (updateThread != null) {
            updateThread.interrupt();
        }
    }

    private void iniciarHiloActualizacion() {
        updateThread = new Thread(() -> {
            while (clip != null && clip.isRunning()) {
                long pos = clip.getMicrosecondPosition();
                SwingUtilities.invokeLater(() -> {
                    actualizarEtiquetasTiempo(pos);
                    slider.setValue((int) (100 * pos / totalDurationMicros));
                });
                try { Thread.sleep(100); } catch (InterruptedException ignored) {}
            }
        });
        updateThread.start();
    }

    private void actualizarEtiquetasTiempo(long posMicros) {
        long secTrans = (posMicros / 1000000);
        long secRest = ((totalDurationMicros - posMicros) / 1000000);
        lblTiempoTranscurrido.setText(String.format("%02d:%02d", secTrans / 60, secTrans % 60));
        lblTiempoRestante.setText(String.format("-%02d:%02d", secRest / 60, secRest % 60));
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new Ejercicio7_2().setVisible(true));
    }
}