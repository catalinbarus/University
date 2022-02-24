package Task2;

import java.util.ArrayList;

public class MyVector3 implements Sumabil {

    /** Coordonatele vectorului **/
    private int x;
    private int y;
    private int z;

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public int getZ() {
        return z;
    }

    public MyVector3(int x, int y, int z) {

        this.x = x;
        this.y = y;
        this.z = z;
    }

    public void addTwoinstances(MyVector3 vector) {

        this.x += vector.getX();
        this.y += vector.getY();
        this.z += vector.getZ();
    }


    @Override
    public void addValue(Sumabil value) {

        addTwoinstances((MyVector3) value);
    }

    @Override
    public String toString() {
        return "MyVector3{" +
                "x=" + x +
                ", y=" + y +
                ", z=" + z +
                '}';
    }
}
