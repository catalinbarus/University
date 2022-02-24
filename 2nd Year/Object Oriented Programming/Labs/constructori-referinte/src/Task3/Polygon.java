package Task3;

public class Polygon {
    Point[] points;

    /** Constrcutor ce aloca spatiu pentru puncte **/
    public Polygon(int n) {

        this.points = new Point[n];
        for(int i = 0; i<n; i++)
            this.points[i] = new Point();
    }

    /** Constructor ce completeaza vectorul de puncte **/
    public Polygon(float[] edges) {
        this((edges.length) / 2);

            int i, k = 0;

            for (i = 0; i < edges.length; i += 2) {

                this.points[k].changeCoords(edges[i], edges[i + 1]);
                k++;
            }
        }

   /** Metoda ce afiseaza colturile unui poligon **/
   void showPolygon() {
      int i;
      for(i = 0; i < points.length; i++)
          this.points[i].showCoords(points[i]);
   }
}

