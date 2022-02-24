package tasks_1_2_3_4_5;

/** Class that initializes a car. **/
public class Car {
    int price;
    int production_year;
    CarType type;

    @Override
    public String toString() {
        return "Car{" +
                "price=" + price +
                ", production_year=" + production_year +
                ", type=" + type +
                '}';
    }

    public Car(int price, int production_year, CarType type) {
        this.price = price;
        this.production_year = production_year;
        this.type = type;
    }

}
