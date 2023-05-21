package practice.OOP.shawarma;

import java.util.Map;

public class cook {
    private shop diner;

    public cook(shop diner) {
        this.diner = diner;
    }

    public void makeDuner(Map<String, Integer> ingredients) throws InterruptedException {
        int meatQuantity = ingredients.getOrDefault("meat", 0);
        if (meatQuantity > 0) {
            synchronized (diner) {
                while (diner.getMeal() < meatQuantity) {
                    diner.wait();
                }
                diner.useMeal(meatQuantity);
            }
        }

        for (Map.Entry<String, Integer> entry : ingredients.entrySet()) {
            if (!entry.getKey().equals("meat")) {
                int vegetableQuantity = entry.getValue();
                if (vegetableQuantity > 0) {
                    synchronized (diner) {
                        while (diner.getVegetableQuantity(entry.getKey()) < vegetableQuantity) {
                            diner.wait();
                        }
                        diner.useVegetable(entry.getKey(), vegetableQuantity);
                    }
                }
            }
        }
    }
    
}
