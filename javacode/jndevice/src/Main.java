public class Main {
    public static void main(String[] args) {

        Player firstPlayer = new Player("A",100,15);

        System.out.println("Hello world!");
        DeviceView view = new DeviceView();
        DeviceModel model = new DeviceModel(firstPlayer);
        DeviceController controller = new DeviceController(model, view);

        view.setVisible(true);
    }
}