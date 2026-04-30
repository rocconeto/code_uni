import javax.swing.SwingUtilities;

public class Main {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            FileDownloaderFrame frame = new FileDownloaderFrame();
            frame.setVisible(true);
        });
    }
}