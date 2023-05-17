import javax.swing.*;

public class DeviceView extends JFrame{

    public Device form;

    public DeviceView(){
        form = new Device();
        JPanel content = form.getMainPanel();

        this.setContentPane(content);
        this.pack();
        this.setTitle("JNDTest");
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    public Device getForm() {
        return form;
    }

    public void setForm(Device form) {
        this.form = form;
    }
}
