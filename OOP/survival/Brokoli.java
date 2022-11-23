public class Brokoli extends Consumables {
    public Brokoli(Integer level){
        if(level >= 1 && level <= 5)
            this.level = level;
        this.initial = "B";
    }

    @Override
    public void apply(Hero hero) {
        hero.addHealth(level*2);
    }
    
}
