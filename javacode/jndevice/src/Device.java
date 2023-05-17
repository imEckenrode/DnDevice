import javax.swing.*;

public class Device {
    private JTabbedPane tabbedPane;
    private JPanel mainPanel;
    private JPanel healthPanel;
    private JButton healthUp;
    private JButton healthDown;
    private JLabel healthLabel;
    private JPanel hpPanel;

    public JTabbedPane getTabbedPane() {
        return tabbedPane;
    }

    public void setTabbedPane(JTabbedPane tabbedPane) {
        this.tabbedPane = tabbedPane;
    }

    public JPanel getMainPanel() {
        return mainPanel;
    }

    public void setMainPanel(JPanel mainPanel) {
        this.mainPanel = mainPanel;
    }

    public JPanel getHealthPanel() {
        return healthPanel;
    }

    public void setHealthPanel(JPanel healthPanel) {
        this.healthPanel = healthPanel;
    }

    public JButton getHealthUp() {
        return healthUp;
    }

    public void setHealthUp(JButton healthUp) {
        this.healthUp = healthUp;
    }

    public JButton getHealthDown() {
        return healthDown;
    }

    public void setHealthDown(JButton healthDown) {
        this.healthDown = healthDown;
    }

    public JLabel getHealthLabel() {
        return healthLabel;
    }

    public void setHealthLabel(JLabel healthLabel) {
        this.healthLabel = healthLabel;
    }

    public JPanel getHpPanel() {
        return hpPanel;
    }

    public void setHpPanel(JPanel hpPanel) {
        this.hpPanel = hpPanel;
    }
}
