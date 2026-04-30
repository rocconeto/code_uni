import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class FileDownloaderFrame extends JFrame {

    private JTextField txtUrl;
    private JButton btnDownload;
    private JProgressBar progressBar;
    private JLabel lblStatus;

    public FileDownloaderFrame() {
        setTitle("File Downloader"); //
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(550, 150);
        setLocationRelativeTo(null); // Centrar en pantalla

        // Layout principal: BoxLayout vertical
        getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));

        // Panel superior con BorderLayout
        JPanel topPanel = new JPanel(new BorderLayout(5, 5));
        topPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10)); // Margen

        JLabel lblUrl = new JLabel("URL:");
        txtUrl = new JTextField();
        btnDownload = new JButton("Download");

        topPanel.add(lblUrl, BorderLayout.WEST); //[cite: 4]
        topPanel.add(txtUrl, BorderLayout.CENTER); //[cite: 4]
        topPanel.add(btnDownload, BorderLayout.EAST); //[cite: 4]

        // Componentes inferiores añadidos directamente al BoxLayout[cite: 4]
        progressBar = new JProgressBar(0, 100);
        progressBar.setStringPainted(false); // En las capturas no se ve el % en texto

        // Panel para dar margen a la barra
        JPanel progressPanel = new JPanel(new BorderLayout());
        progressPanel.setBorder(BorderFactory.createEmptyBorder(0, 10, 10, 10));
        progressPanel.add(progressBar, BorderLayout.CENTER);

        lblStatus = new JLabel(" ");
        lblStatus.setBorder(BorderFactory.createEmptyBorder(0, 10, 10, 10));

        // Añadir todo al frame
        add(topPanel);
        add(progressPanel);
        add(lblStatus);

        // Acción del botón Download
        btnDownload.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                iniciarDescarga();
            }
        });
    }

    private void iniciarDescarga() {
        String urlStr = txtUrl.getText().trim();

        // Validación: Si el campo está vacío, mostrar error[cite: 4]
        if (urlStr.isEmpty()) {
            JOptionPane.showMessageDialog(this,
                    "Please enter a valid URL",
                    "Error",
                    JOptionPane.ERROR_MESSAGE); //[cite: 4]
            return;
        }

        // Estado 2 (Descargando): Deshabilitar botón y actualizar etiqueta[cite: 4]
        btnDownload.setEnabled(false);
        lblStatus.setText("Downloading..."); //[cite: 4]
        progressBar.setValue(0);

        // Instanciar y lanzar el SwingWorker[cite: 4]
        DownloadWorker worker = new DownloadWorker(urlStr, progressBar, lblStatus, btnDownload);
        worker.execute();
    }
}