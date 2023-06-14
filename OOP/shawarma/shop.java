package practice.OOP.shawarma;

import java.util.Map;

public class shop {
    int maxMeal;
    int currentMeal;
    Map <String, Integer> maxVegetables;
    Map <String, Integer> currentVegetables;

    public shop(int maxMeal, Map<String, Integer> maxVegetables) {
        this.maxMeal = maxMeal;
        this.maxVegetables = maxVegetables;
        this.currentMeal = maxMeal;
        this.currentVegetables = maxVegetables;
    }

    public void addMeal(int amount) {
        if (currentMeal + amount > maxMeal) {
            currentMeal = maxMeal;
        } else {
            currentMeal += amount;
        }
    }

    public void addVegetable(String vegetable, int amount) {
        if (currentVegetables.get(vegetable) + amount > maxVegetables.get(vegetable)) {
            currentVegetables.put(vegetable, maxVegetables.get(vegetable));
        } else {
            currentVegetables.put(vegetable, currentVegetables.get(vegetable) + amount);
        }
    }

    public String getVegetableThatNeedsLoading() {
        for (Map.Entry<String, Integer> entry : currentVegetables.entrySet()) {
            if (entry.getValue() < maxVegetables.get(entry.getKey())) {
                return entry.getKey();
            }
        }
        return null;
    }

    public boolean useMeal(int amount) {
        currentMeal -= amount;
        if(currentMeal < 0) {
            currentMeal = 0;
            return false;
        }else{
            return true;
        }
    }

    public void useVegetable(String vegetable, int amount) {
        currentVegetables.put(vegetable, currentVegetables.get(vegetable) - amount);
    }

    public int getMeal() {
        return currentMeal;
    }

    public int getVegetableQuantity(String key) {
        return currentVegetables.get(key);
    }

    public int getMaxVegetableQuantity(String vegetableToLoad) {
        return maxVegetables.get(vegetableToLoad);
    }
}