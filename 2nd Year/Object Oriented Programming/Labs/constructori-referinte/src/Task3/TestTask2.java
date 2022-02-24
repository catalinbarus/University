package Task3;

public class TestTask2 {
    public static void main(String[] args) {

        int i;

        float[] edges = new float[] {2, 5, 10, 4, 89, 1, 32, 4, 91, 21};

        Polygon polygon = new Polygon(edges);

        polygon.showPolygon();
    }
}
