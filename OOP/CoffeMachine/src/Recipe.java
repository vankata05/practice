import java.util.HashMap;

public class Recipe {
    String name;
    double price;
    HashMap<String, Integer> ingredients = new HashMap<String, Integer>();

    public Recipe(String name, double price){
        this.name = name;
        if(price < 0){
            throw new ArithmeticException("Price cant be less than 0!!!");
        }else{
            this.price = price;
        }
    }

    public void addIngredient(String name, int amount){
        if(ingredients.containsKey(name)){
            throw new ArithmeticException("The ingredient is already in the list!");
        }else{
            ingredients.put(name, amount);
        }
    }

    public HashMap<String, Integer> getIngredients(){
        return ingredients;
    }

    public double getPrice(){
        return price;
    }
}
