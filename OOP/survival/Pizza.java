public class Pizza extends Consumables {
    public Pizza(Integer level){
        if(level >= 1 && level <= 5)
            this.level = level;
        this.initial = "P";
    }

    @Override
    public void apply(Hero hero) {
        hero.addPower(13);
    }
    
}
