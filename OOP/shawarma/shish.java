package practice.OOP.shawarma;

public class shish implements Runnable {
    private shop diner;

    public shish(shop diner) {
        this.diner = diner;
    }

    public void run() {
        while (true) {
            try {
                Thread.sleep((long)(Math.random() * 4000) + 1000); // between 1 and 5 seconds
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
            synchronized (diner) {
                if (diner.useMeal(100)) {
                    diner.addMeal(100);
                    diner.notifyAll();
                }
            }
        }
    }
}