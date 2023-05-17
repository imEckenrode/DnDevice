public class DeviceModel {
    Player owner;
    Battle battle;

    enum screen{START, WAITING_TURN, ATTACK, OOC};

    public DeviceModel(Player owner) {
        this.owner = owner;
    }

    public Player getOwner() {
        return owner;
    }

    public void setOwner(Player owner) {
        this.owner = owner;
    }

    public Battle getBattle() {
        return battle;
    }

    public void setBattle(Battle battle) {
        this.battle = battle;
    }

    //public void addToBattle(){}   //This can be defined within Battle

}
