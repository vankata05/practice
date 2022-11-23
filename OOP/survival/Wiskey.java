public class Wiskey extends Consumables {
    public Wiskey(Integer level){
        if(level >= 1 && level <= 5)
            this.level = level;
        this.initial = "W";
    }

    @Override
    public void apply(Hero hero) {
        hero.powerDown(15);
    }
    
}
