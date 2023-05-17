public class Fighter {
    int initiative;
    boolean surprised;
    boolean unconscious;

    String name;
    int maxHP;
    int HP;
    int AC;

    public Fighter(int initiative, boolean surprised, String name, int maxHP, int HP, int AC) {
        this.initiative = initiative;
        this.surprised = surprised;
        this.name = name;
        this.maxHP = maxHP;
        this.HP = HP;
        this.AC = AC;
        this.unconscious = false;
    }

    public Fighter(String name, int maxHP, int AC){
        this(0,false, name, maxHP, maxHP, AC);
    }

    public int getInitiative() {
        return initiative;
    }

    public void setInitiative(int initiative) {
        this.initiative = initiative;
    }

    public boolean isSurprised() {
        return surprised;
    }

    public void setSurprised(boolean surprised) {
        this.surprised = surprised;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getMaxHP() {
        return maxHP;
    }

    public void setMaxHP(int maxHP) {
        this.maxHP = maxHP;
    }

    public int getHP() {
        return HP;
    }

    public void setHP(int HP) {
        this.HP = HP;
    }

    public int getAC() {
        return AC;
    }

    public void setAC(int AC) {
        this.AC = AC;
    }

    public void lowerHP(int damageTaken) {
        if(damageTaken>=HP){
            dropToZero(damageTaken);
        }else{
            HP-=damageTaken;
        }
    }

    public void raiseHP(int damageHealed){
        HP += damageHealed;
        if(HP>maxHP){
            HP = maxHP;
        }

        unconscious = false;
    }


    //TODO: Override this for players (death saves) vs. creatures
    private void dropToZero(int i) {
        if (i - HP > maxHP) {
            System.out.println("Yeah, "+name+" is dead...have fun.");
        }
        HP = 0;
        unconscious = true;
    }
}
