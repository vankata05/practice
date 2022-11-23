public class Rice extends Consumables {
    public Rice(Integer level){
        if(level >= 1 && level <= 5)
            this.level = level;
        this.initial = "R";
    }

    @Override
    public void apply(Hero hero) {
        hero.addPower(level*2);
    }
    
}
