public class Hero extends Entity{
    String name;
    Integer health;
    Integer power;

    public Hero(String name, Integer health, Integer power) {
        this.name = name;
        this.initial = name.substring(0, 2);
        if(health > 0)
            this.health = health;
        if(power > 0)
            this.power = power;
    }

    public void takeDamage(Integer damage) {
        this.health -= damage;
    }

    public void addHealth(Integer health) {
        this.health += health;
    }

    public void powerDown(Integer debuff) {
        this.power-= debuff;
    }

    public void addPower(Integer power) {
        this.power += power;
    }

    public Integer getPower(){
        return this.power;
    }

    public Integer getHealth(){
        return this.health;
    }
    public void apply(Hero hero){
    }
}