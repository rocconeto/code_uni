import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.time.LocalTime;
import javax.swing.*;

public class Ej1_Reloj extends JFrame {

    private static final int FIELD_WIDTH = 2;
    private static final int TIMER_INTERVAL = 1000;

    private JTextField hourField = new JTextField(FIELD_WIDTH);
    private JTextField minuteField = new JTextField(FIELD_WIDTH);
    private JTextField secondField = new JTextField(FIELD_WIDTH);
    private JLabel hourLabel = new JLabel("h :");
    private JLabel minuteLabel = new JLabel("m :");
    private JLabel secondLabel = new JLabel("s");
    private Timer timer;

    public Ej1_Reloj() {
        setLayout(new FlowLayout());
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(false);
        setSize(200, 100);

        add(hourField);
        add(hourLabel);
        add(minuteField);
        add(minuteLabel);
        add(secondField);
        add(secondLabel);

        // El objeto ActionListener se asocia con el Timer en el constructor
        timer = new Timer(TIMER_INTERVAL, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                updateClock(); // Se llamará a la función cada segundo
            }
        });

        setVisible(true);
    }

    private void updateClock() {
        LocalTime time = LocalTime.now();
        hourField.setText(formatNumber(time.getHour()));
        minuteField.setText(formatNumber(time.getMinute()));
        secondField.setText(formatNumber(time.getSecond()));
    }

    private String formatNumber(int number) {
        return String.format("%02d", number);
    }

    public void startClock() {
        timer.start();
    }

    public static void main(String[] args) {
        EventQueue.invokeLater(() -> new Ej1_Reloj().startClock());
    }
}