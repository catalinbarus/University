package tasks_1_2_3_4_5;
import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {
        Car toyota = new Car(10000, 2001, CarType.Toyota);
        Car honda = new Car(20000, 2019, CarType.Honda);
        Car mitsubishi = new Car(30000, 1998, CarType.Mitsubishi);

        Offer offer = new Offer() {
            public int getDiscount(Car car) {
                return 100;
            }
        };

        Dealership deal = new Dealership();
        deal.getFinalPrice(toyota);
        deal.negotiate(toyota, offer);
        System.out.println("\n");
        deal.getFinalPrice(honda);
        deal.negotiate(honda, offer);
        System.out.println("\n");
        deal.getFinalPrice(mitsubishi);
        deal.negotiate(mitsubishi, offer);
        System.out.println("\n");

        /** La compilare se genereaza 9 fisiere .class,
         * Car.class, CarType.class, Dealership.class,
         * Dealership$BrandOffer.class, Dealership$DealerOffer.class,
         * Dealership$SpecialOffer.class, Main.class, Main$1.class, Offer.class
         **/

        /** Pentru clasa anonima s-a generat fisierul Offer.class **/


        /** Task 5, testing of lambda expressions using an ArrayList. **/
        ArrayList<Car> cars = new ArrayList<>();
        cars.add(toyota);
        cars.add(honda);
        cars.add(mitsubishi);

        System.out.println(cars);

        cars.removeIf(v -> v.price > 15000);

        System.out.println(cars);

    }
}
