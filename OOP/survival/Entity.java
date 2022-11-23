public abstract class Entity {
    String initial;

    public Entity() {
        this.initial = "Empty";
    }

    public String getInitial(){
        return initial;
    }

    public abstract void apply(Hero hero);
}
