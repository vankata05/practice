public class Orange extends Consumables {
    public Orange(Integer level){
        if(level >= 1 && level <= 5)
            this.level = level;
        this.initial = "O";
    }

    @Override
    public void apply(Hero hero) {
        hero.addHealth(level);
        hero.addPower(level);
    }
    
}
