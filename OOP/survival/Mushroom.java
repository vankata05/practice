public class Mushroom extends Consumables {
    public Mushroom(Integer level){
        if(level >= 1 && level <= 5)
            this.level = level;
        this.initial = "M";
    }

    @Override
    public void apply(Hero hero) {
        hero.takeDamage(20);
    }
    
}
