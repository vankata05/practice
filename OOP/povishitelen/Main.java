package practice.OOP.povishitelen;
import java.util.Scanner;

public class Main {
    public static void main(){
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter winter resort name:");
        WinterResort winterResort = new WinterResort(scanner.nextLine());
        System.out.println("Enter lifts in format:<LiftType>,<Name>,<Capacity>,<ManufactureYear>,<Speed>:");
        String input = scanner.nextLine();
        while(!input.equals("")){
            String[] inputParts = input.split(",");
            Lift lift = null;
            switch(inputParts[0]){
                case "ChairLift":
                    lift = new ChairLift(inputParts[1], Integer.parseInt(inputParts[2]), Integer.parseInt(inputParts[3]), Integer.parseInt(inputParts[4]));
                    break;
                case "TBarLift":
                    lift = new TBarLift(inputParts[1], Integer.parseInt(inputParts[2]), Integer.parseInt(inputParts[3]), Integer.parseInt(inputParts[4]));
                    break;
                case "GondolaLift":
                    lift = new GondolaLift(inputParts[1], Integer.parseInt(inputParts[2]), Integer.parseInt(inputParts[3]), Integer.parseInt(inputParts[4]));
                    break;
                default:
                    System.out.println("Invalid lift type");
            }
            winterResort.addLift(lift);
            input = scanner.nextLine();
        }
        scanner.close();
    }
}