public class Field {
    Entity map[][];

    public Field(Integer height, Integer width) {
        this.map = new Entity[height][width];
    }

    public Entity getBlock(Integer x, Integer y){
        return map[x][y];
    }
    
    public void addEntity(Entity entity, Integer x, Integer y){
        map[x][y] = entity;
    }
}
