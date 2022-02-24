package task0;

interface Engine {
    int getFuelCapacity();
}

class Car_Test {
    class OttoEngine implements Engine {
        private int fuelCapacity;

        public OttoEngine(int fuelCapacity) {
            this.fuelCapacity = fuelCapacity;
        }

        public int getFuelCapacity() {
            return fuelCapacity;
        }
    }

    public OttoEngine getEngine() {
        OttoEngine engine = new OttoEngine(11);
        return engine;
    }
}

public class Test {
    public static void main(String[] args) {
        Car_Test car = new Car_Test();

        Car_Test.OttoEngine firstEngine = car.getEngine();
        Car_Test.OttoEngine secondEngine = car.new OttoEngine(10);

        System.out.println(firstEngine.getFuelCapacity());
        System.out.println(secondEngine.getFuelCapacity());
    }
}