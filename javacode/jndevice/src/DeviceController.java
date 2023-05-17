public class DeviceController {

    private DeviceModel model;
    private DeviceView view;
    private Device gui;


    public DeviceController(DeviceModel model, DeviceView view) {
        this.model = model;
        this.view = view;

        gui = view.getForm();

        this.model.setOwner(new Player("EEE",50,10));

        refreshHealthLabel();

        gui.getHealthDown().addActionListener(e->{
            this.model.owner.lowerHP(1);
            refreshHealthLabel();
        });

        gui.getHealthUp().addActionListener(e->{
            this.model.owner.raiseHP(1);
            refreshHealthLabel();
        });

    }

    private void refreshHealthLabel() {
        boolean isMaxed = (model.getOwner().getHP() >= model.getOwner().getMaxHP());
        gui.getHealthLabel().setText(model.getOwner().getHP() + (isMaxed ? " (Full)" : ""));
    }


}
