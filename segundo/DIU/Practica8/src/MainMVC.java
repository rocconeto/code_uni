import javax.swing.SwingUtilities;

public class MainMVC {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            Model model = new Model(550, 300);
            View view = new View(model);
            new Controller(model, view);
            view.setVisible(true);
        });
    }
}