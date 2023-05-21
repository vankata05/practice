package practice.OOP.shawarma;

import java.util.Map;

public class Main {
    public static void main(String[] args) {
        shop diner = new shop(1000, Map.of("tomato", 1000, "cucumber", 1000, "onion", 1000, "pepper", 1000));
        Thread helperThread = new Thread(new helper(diner));
        Thread shishThread = new Thread(new shish(diner));
        helperThread.start();
        shishThread.start();
        cook cook = new cook(diner);
        while (true) {
            try {
                Thread.sleep((long)(Math.random() * 4000) + 1000); // between 1 and 5 seconds
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
            try {
                cook.makeDuner(Map.of("meat", 1, "tomato", 1, "cucumber", 1, "onion", 1, "pepper", 1));
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }
}
