import java.util.Scanner;
import java.util.Random;

public class Survival{
    public static void printMap(Entity map[][], Integer size){
        for(Integer a = 0; a < size; a++){
            for(Integer b = 0; b < size; b++){
                if(map[a][b] != null){
                    if(map[a][b].getInitial().length() == 1)
                        System.out.print("|" + map[a][b].getInitial() + " ");
                    else
                        System.out.print("|" + map[a][b].getInitial());
                }else{
                    System.out.print("|  ");
                }
            }
            System.out.println("|");
            for(Integer i = 0; i < size; i++)
                System.out.print("_ _");
            System.out.println(" ");
        }
    }

    public static void addConsumable(Consumables c, Entity map[][], Integer size){
        Random rand = new Random();
        Integer x, y;
        x = rand.nextInt(size);
        y = rand.nextInt(size);
        while(map[x][y] != null){
            x = rand.nextInt(size);
            y = rand.nextInt(size);
        }
        map[x][y] = c;
    }

    public static void main(String[] args){ 
        Scanner sc = new Scanner(System.in);
        Random rand = new Random();
        Integer player_num, size;
        Integer[][] coords;
        String name = "Ivan";
        Entity map[][];

        System.out.println("Hello Adventurer!");

        System.out.println("Enter the map size:");
        size = sc.nextInt();
        map = new Entity[size][size];

        System.out.println("Enter the number of players in the game:");
        player_num = sc.nextInt();
        if(player_num > size*size){
            System.out.println("Invalid player number!!!");
        }
            coords = new Integer[player_num][2];
        for(Integer i = 0; i < player_num; i++){
            System.out.println("Enter the name of hero number " + i + ":");
            if(i == 0)
                sc.nextLine();
            name = sc.nextLine();
            coords[i][0] = rand.nextInt(size-1);
            coords[i][1] = rand.nextInt(size-1);
            while(map[coords[i][0]][coords[i][1]] != null){
                coords[i][1] = rand.nextInt(size);
                coords[i][0] = rand.nextInt(size);
            }
            map[coords[i][0]][coords[i][1]] = new Hero(name, rand.nextInt(500), rand.nextInt(500));
        }

        addConsumable(new Brokoli(rand.nextInt(5)), map, size);
        addConsumable(new Orange(rand.nextInt(5)), map, size);
        addConsumable(new Rice(rand.nextInt(5)), map, size);
        addConsumable(new Pizza(rand.nextInt(5)), map, size);
        addConsumable(new Mushroom(rand.nextInt(5)), map, size);
        addConsumable(new Wiskey(rand.nextInt(5)), map, size);

        printMap(map, size);

        System.out.println("\n");

        while(true){
            for(Integer i = 0; i < player_num; i++){
                String turn;
                System.out.println("\nIt's " + map[coords[i][0]][coords[i][1]].getInitial() + "'s turN");
                turn = sc.nextLine();
                if(!turn.equals("UP") && !turn.equals("DOWN") && !turn.equals("LEFT") && !turn.equals("RIGHT"))
                    System.out.println("Wrong input!!!");
                if(turn.equals("UP")){
                    if(coords[i][0] != 0){
                        if(map[coords[i][0]-1][coords[i][1]] == null){
                            map[coords[i][0]-1][coords[i][1]] = map[coords[i][0]][coords[i][1]];
                            map[coords[i][0]][coords[i][1]] = null;
                            coords[i][0]--;
                        }else{
                            if(map[coords[i][0]-1][coords[i][1]].getInitial().length() == 2)
                                System.out.println("Simulate FIGHT");
                            if(map[coords[i][0]-1][coords[i][1]].getInitial().length() == 1)
                                System.out.println("Simulate consuming");
                        }
                    }
                }

                if(turn.equals("DOWN")){
                    if(coords[i][0] != size){
                        if(map[coords[i][0]+1][coords[i][1]] == null){
                            map[coords[i][0]+1][coords[i][1]] = map[coords[i][0]][coords[i][1]];
                            map[coords[i][0]][coords[i][1]] = null;
                            coords[i][0]++;
                        }else{
                            if(map[coords[i][0]+1][coords[i][1]].getInitial().length() == 2)
                                System.out.println("Simulate FIGHT");
                            if(map[coords[i][0]+1][coords[i][1]].getInitial().length() == 1)
                                System.out.println("Simulate consuming");
                        }
                    }
                }

                if(turn.equals("LEFT")){
                    if(coords[i][1] != 0){
                        if(map[coords[i][0]][coords[i][1]-1] == null){
                            map[coords[i][0]][coords[i][1]-1] = map[coords[i][0]][coords[i][1]];
                            map[coords[i][0]][coords[i][1]] = null;
                            coords[i][1]--;
                        }else{
                            if(map[coords[i][0]][coords[i][1]-1].getInitial().length() == 2)
                                System.out.println("Simulate FIGHT");
                            if(map[coords[i][0]][coords[i][1]-1].getInitial().length() == 1)
                                System.out.println("Simulate consuming");
                        }
                    }
                }

                if(turn.equals("RIGHT")){
                    if(coords[i][1] != size){
                        if(map[coords[i][0]][coords[i][1]+1] == null){
                            map[coords[i][0]][coords[i][1]+1] = map[coords[i][0]][coords[i][1]];
                            map[coords[i][0]][coords[i][1]] = null;
                            coords[i][1]++;
                        }else{
                            if(map[coords[i][0]][coords[i][1]+1].getInitial().length() == 2)
                                System.out.println("Simulate FIGHT");
                            if(map[coords[i][0]][coords[i][1]+1].getInitial().length() == 1)
                                System.out.println("Simulate consuming");
                        }
                    }
                }
                printMap(map, size);
            }
            break;
        }

        sc.close();
    }

}