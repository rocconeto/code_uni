import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;

public class Practica5 extends JFrame {

    private Color colorActivo = new Color(237, 28, 36);
    private int grosorTrazo = 6;
    private final ArrayList<Trazo> trazosUsuario = new ArrayList<>();

    private Timer timer;
    private int spriteX = 400, spriteY = 300;
    private int stepSize = 5;
    private int dirX = 1, dirY = 1;
    private int currentFrame = 0;
    private final ArrayList<Point> estela = new ArrayList<>();

    private final CanvasPanel canvas;
    private JLabel lblEstado;
    private Point lastPoint = null;

    public Practica5() {
        setTitle("MiniEstudio de Diseño");
        setSize(800, 600);
        setResizable(false);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        configurarNorte();
        configurarSur();
        configurarOeste();

        canvas = new CanvasPanel();
        add(canvas, BorderLayout.CENTER);

        canvas.setFocusable(true);
        canvas.addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                if (e.getKeyCode() == KeyEvent.VK_C) {
                    trazosUsuario.clear();
                } else if (e.getKeyChar() == '+') {
                    grosorTrazo = Math.min(20, grosorTrazo + 2);
                } else if (e.getKeyChar() == '-') {
                    grosorTrazo = Math.max(2, grosorTrazo - 2);
                }
                actualizarBarraEstado();
                canvas.repaint();
            }
        });

        timer = new Timer(50, e -> actualizarAnimacion());

        actualizarBarraEstado();
    }

    private void configurarNorte() {
        JPanel panelNorte = new JPanel(new FlowLayout());
        panelNorte.setPreferredSize(new Dimension(800, 50));

        panelNorte.add(new JLabel("[Layout: FlowLayout] "));
        panelNorte.add(new JLabel("Herramientas: "));

        JButton btnIniciar = new JButton("Iniciar Animación");
        JButton btnPausar = new JButton("Pausar Animación");

        btnIniciar.addActionListener(e -> { timer.start(); canvas.requestFocus(); });
        btnPausar.addActionListener(e -> timer.stop());

        panelNorte.add(btnIniciar);
        panelNorte.add(btnPausar);

        add(panelNorte, BorderLayout.NORTH);
    }

    private void configurarSur() {
        JPanel panelSur = new JPanel(new FlowLayout());
        panelSur.setPreferredSize(new Dimension(800, 40));

        panelSur.add(new JLabel("[Layout: FlowLayout] "));

        lblEstado = new JLabel();
        panelSur.add(lblEstado);

        JSlider sliderVelocidad = new JSlider(1, 20, stepSize);
        sliderVelocidad.addChangeListener(e -> {
            stepSize = sliderVelocidad.getValue();
            canvas.requestFocus();
        });
        panelSur.add(new JLabel("  Velocidad:"));
        panelSur.add(sliderVelocidad);

        add(panelSur, BorderLayout.SOUTH);
    }

    private void configurarOeste() {
        JPanel panelOeste = new JPanel(new GridLayout(6, 1));
        panelOeste.setPreferredSize(new Dimension(120, 0));

        panelOeste.add(new JLabel("[Layout: GridLayout]", SwingConstants.CENTER));

        Color[] colores = {
                new Color(237, 28, 36),
                new Color(0, 56, 168),
                new Color(255, 221, 51),
                Color.GREEN,
                Color.MAGENTA,
                Color.DARK_GRAY
        };

        for (Color c : colores) {
            panelOeste.add(new CeldaColor(c));
        }

        add(panelOeste, BorderLayout.WEST);
    }

    private void actualizarBarraEstado() {
        String hex = String.format("#%02x%02x%02x", colorActivo.getRed(), colorActivo.getGreen(), colorActivo.getBlue());
        lblEstado.setText(String.format("Coords Sprite: (%d, %d) | Color: %s | Grosor: %d px", spriteX, spriteY, hex, grosorTrazo));
    }

    private void actualizarAnimacion() {
        estela.add(new Point(spriteX, spriteY));
        if (estela.size() > 10) estela.remove(0);

        spriteX += stepSize * dirX;
        spriteY += stepSize * dirY;

        int size = 40;
        if (spriteX <= 0 || spriteX + size >= canvas.getWidth()) dirX *= -1;
        if (spriteY <= 0 || spriteY + size >= canvas.getHeight()) dirY *= -1;

        currentFrame = (currentFrame + 1) % 2;

        actualizarBarraEstado();
        canvas.repaint();
    }

    private class Trazo {
        Point p1, p2;
        Color color;
        int grosor;

        Trazo(Point p1, Point p2, Color color, int grosor) {
            this.p1 = p1;
            this.p2 = p2;
            this.color = color;
            this.grosor = grosor;
        }
    }

    private class CanvasPanel extends JPanel {
        public CanvasPanel() {
            setBackground(Color.WHITE);
            setLayout(new BorderLayout());
            add(new JLabel("[Layout: BorderLayout.CENTER]"), BorderLayout.NORTH);

            addMouseListener(new MouseAdapter() {
                @Override
                public void mousePressed(MouseEvent e) {
                    lastPoint = e.getPoint();
                    requestFocus();
                }
            });

            addMouseMotionListener(new MouseMotionAdapter() {
                @Override
                public void mouseDragged(MouseEvent e) {
                    if (lastPoint != null) {
                        trazosUsuario.add(new Trazo(lastPoint, e.getPoint(), colorActivo, grosorTrazo));
                        lastPoint = e.getPoint();
                        repaint();
                    }
                }
            });
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            Graphics2D g2d = (Graphics2D) g;
            g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

            int w = getWidth();
            int h = getHeight();

            g2d.setColor(new Color(255, 221, 51));
            g2d.fillRect(0, 0, w/3, h/4);
            g2d.setColor(new Color(0, 56, 168));
            g2d.fillRect(w - w/4, h - h/3, w/4, h/3);
            g2d.setColor(new Color(237, 28, 36));
            g2d.fillRect(w/3, h/2, w/3, h/2);

            g2d.setColor(Color.BLACK);
            g2d.setStroke(new BasicStroke(10));
            g2d.drawLine(w/3, 0, w/3, h);
            g2d.drawLine(0, h/4, w, h/4);

            for (Trazo t : trazosUsuario) {
                g2d.setColor(t.color);
                g2d.setStroke(new BasicStroke(t.grosor, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
                g2d.drawLine(t.p1.x, t.p1.y, t.p2.x, t.p2.y);
            }

            for (int i = 0; i < estela.size(); i++) {
                Point p = estela.get(i);
                float alpha = (i + 1) * 0.08f;
                int trailSize = 10 + (i * 2);
                g2d.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER, alpha));
                g2d.setColor(Color.GRAY);
                g2d.fillOval(p.x + (40 - trailSize)/2, p.y + (40 - trailSize)/2, trailSize, trailSize);
            }
            g2d.setComposite(AlphaComposite.SrcOver);

            int animSize = currentFrame == 0 ? 40 : 34;
            int offset = (40 - animSize) / 2;
            g2d.setColor(dirX > 0 ? Color.ORANGE : Color.CYAN);
            g2d.fillOval(spriteX + offset, spriteY + offset, animSize, animSize);
        }
    }

    private class CeldaColor extends JPanel {
        private final Color miColor;

        public CeldaColor(Color c) {
            this.miColor = c;
            setPreferredSize(new Dimension(100, 80));

            addMouseListener(new MouseAdapter() {
                @Override
                public void mousePressed(MouseEvent e) {
                    colorActivo = miColor;
                    actualizarBarraEstado();
                    getParent().repaint();
                    canvas.requestFocus();
                }
            });
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            Graphics2D g2d = (Graphics2D) g;

            g2d.setColor(miColor);
            g2d.fillRect(10, 10, getWidth()-20, getHeight()-20);

            if (colorActivo.equals(miColor)) {
                g2d.setColor(Color.BLACK);
                g2d.setStroke(new BasicStroke(3));
                g2d.drawRect(10, 10, getWidth()-20, getHeight()-20);
            }
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new Practica5().setVisible(true));
    }
}