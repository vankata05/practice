package practice.OOP.shawarma;

import java.util.Random;

public class helper implements Runnable{
    private shop diner;
    private Random random;

    public helper(shop diner) {
        this.diner = diner;
        this.random = new Random();
    }

    @Override
    public void run() {
        while (true) {
            String vegetableToLoad = diner.getVegetableThatNeedsLoading();
            if (vegetableToLoad != null) {
                int currentQuantity = diner.getVegetableQuantity(vegetableToLoad);
                int maxQuantity = diner.getMaxVegetableQuantity(vegetableToLoad);
                int quantityToAdd = random.nextInt(maxQuantity - currentQuantity + 1) + currentQuantity;
                diner.addVegetable(vegetableToLoad, quantityToAdd);
            } else {
                synchronized (diner) {
                    try {
                        diner.wait();
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt();
                    }
                }
            }
        }
    }
}
