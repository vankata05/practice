import java.util.HashMap;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SmartCoffeMachine extends CoffeMachine{
    public void brewRecipe(Recipe recipe){
        HashMap<String, Integer> temp = recipe.getIngredients();
        for (HashMap.Entry<String, Integer> set : temp.entrySet()) {
            if(!this.ingredients.containsKey(set.getKey())){
                throw new ArithmeticException("Ingredient doesnt exist!");
            }else{
                this.ingredients.replace(set.getKey(), this.ingredients.get(set.getKey())-set.getValue());
                turnover+=recipe.getPrice();
                if(this.ingredients.get(set.getKey()) <= 1000){
                    try {
                        File file = new File("notofocations.txt");
                        file.createNewFile();
                        FileWriter wr = new FileWriter("filename.txt");
                        wr.write("Ingredient"+ set.getKey() +" is almost over. Current amount" + this.ingredients.get(set.getKey()));
                        wr.close();
                    }catch (IOException e) {
                        System.out.println("An error occurred.");
                    }
                }
            }
        }
    }
}
