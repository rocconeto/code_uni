import javax.swing.*;
import java.io.*;
import java.net.URL;
import java.net.URLConnection;
import java.util.List;

public class DownloadWorker extends SwingWorker<Void, Integer> {

    private String urlString;
    private JProgressBar progressBar;
    private JLabel lblStatus;
    private JButton btnDownload;

    public DownloadWorker(String urlString, JProgressBar progressBar, JLabel lblStatus, JButton btnDownload) {
        this.urlString = urlString;
        this.progressBar = progressBar;
        this.lblStatus = lblStatus;
        this.btnDownload = btnDownload;
    }

    @Override
    protected Void doInBackground() throws Exception {
        // Extraer el nombre del fichero tomando la parte final tras la última barra '/'[cite: 4]
        String fileName = urlString.substring(urlString.lastIndexOf('/') + 1);

        // Abrir conexión y obtener tamaño del fichero[cite: 4]
        URL downloadUrl = new URL(urlString);
        URLConnection connection = downloadUrl.openConnection();
        int fileSize = connection.getContentLength();

        // Abrir flujos de entrada y salida[cite: 4]
        InputStream input = new BufferedInputStream(downloadUrl.openStream());
        OutputStream output = new FileOutputStream(fileName);

        // Leer el fichero y calcular progreso[cite: 4]
        byte[] buffer = new byte[1024];
        int bytesRead;
        long totalBytesRead = 0; // Usar long para evitar desbordamiento en ficheros grandes

        while ((bytesRead = input.read(buffer)) != -1) {
            if (isCancelled()) { //[cite: 4]
                input.close();
                output.close();
                return null;
            }
            output.write(buffer, 0, bytesRead); //[cite: 4]
            totalBytesRead += bytesRead;

            // Calcular y publicar el progreso[cite: 4]
            if (fileSize > 0) {
                // Cálculo de porcentaje: (bytesLeídosTotales / tamañoFichero) * 100[cite: 4]
                int progress = (int) (((double) totalBytesRead / fileSize) * 100);
                publish(progress);
            }
        }

        // Cerrar flujos[cite: 4]
        input.close();
        output.close();

        return null;
    }

    @Override
    protected void process(List<Integer> chunks) {
        // Se ejecuta en el EDT. Actualiza el valor de la JProgressBar[cite: 4]
        // Tomamos el último valor reportado en este lote de procesado
        int latestProgress = chunks.get(chunks.size() - 1);
        progressBar.setValue(latestProgress);
    }

    @Override
    protected void done() {
        // Se ejecuta en el EDT al terminar.[cite: 4]
        try {
            get(); // Captura cualquier excepción que haya ocurrido en doInBackground
            lblStatus.setText("Download completed"); //[cite: 4]
            progressBar.setValue(100);
        } catch (Exception e) {
            lblStatus.setText("Error: " + e.getMessage()); // Mostrar mensaje descriptivo en caso de error[cite: 4]
        } finally {
            // Vuelve a habilitar el botón Download siempre al terminar[cite: 4]
            btnDownload.setEnabled(true);
        }
    }
}