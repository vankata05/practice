import java.util.HashMap;

public class CoffeMachine {
    double turnover;
    HashMap<String, Integer> ingredients = new HashMap<String, Integer>();

    public CoffeMachine(){
        turnover = 0;
    }

    public CoffeMachine(String[] ingredients){
        for(String current: ingredients){
            if(!this.ingredients.containsKey(current)){
                this.ingredients.put(current, 5000);
            }
        }
    }

    public void resupplyContainer(String ingredient){
        if(this.ingredients.containsKey(ingredient)){
            this.ingredients.replace(ingredient, 5000);
        }
    }

    public void resupply(){
        for (HashMap.Entry<String, Integer> set : ingredients.entrySet()) {
            this.ingredients.replace(set.getKey(), 5000);
        }
        this.turnover = 0d;
    }

    public Integer getIngredientSupply(String ingredient){
        if(!this.ingredients.containsKey(ingredient)){
            throw new ArithmeticException("Ingredient doesnt exist!");
        }
        return this.ingredients.get(ingredient);
    }

    public void useIngredient(String ingredient, int amount){
        if(!this.ingredients.containsKey(ingredient)){
            throw new ArithmeticException("Ingredient doesnt exist!");
        }else{
            this.ingredients.replace(ingredient, this.ingredients.get(ingredient)-amount);
        }
    }

    public void brewRecipe(Recipe recipe){
        HashMap<String, Integer> temp = recipe.getIngredients();
        for (HashMap.Entry<String, Integer> set : temp.entrySet()) {
            if(!this.ingredients.containsKey(set.getKey())){
                throw new ArithmeticException("Ingredient doesnt exist!");
            }else{
                this.ingredients.replace(set.getKey(), this.ingredients.get(set.getKey())-set.getValue());
                turnover+=recipe.getPrice();
            }
        }
    }
}
