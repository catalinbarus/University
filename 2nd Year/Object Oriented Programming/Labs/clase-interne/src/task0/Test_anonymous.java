package task0;

interface Engine_anonymous {
    int getFuelCapacity();
}

class Car_anonymous {
    public Engine_anonymous getEngine(int fuelCapacity) {
        return new Engine_anonymous () {
            private int fuelCapacity = 11;

            public int getFuelCapacity() {
                return fuelCapacity;
            }
        };
    }
}

public class Test_anonymous {
    public static void main(String[] args) {
        Car_anonymous car = new Car_anonymous();

        Engine_anonymous firstEngine = car.getEngine(10);

        System.out.println(firstEngine.getFuelCapacity());
    }
}
