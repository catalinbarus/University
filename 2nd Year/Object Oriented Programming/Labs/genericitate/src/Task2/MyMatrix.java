package Task2;

import java.util.Arrays;

public class MyMatrix implements Sumabil {

    int [][] mymatrix;
    int i;
    int j;

    public MyMatrix(int i, int j) {

        mymatrix = new int[i][j];
    }

    @Override
    public String toString() {
        return "MyMatrix{" +
                "mymatrix=" + Arrays.toString(mymatrix) +
                '}';
    }

    public void addTwomatrix(MyMatrix matrix) {

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                this.mymatrix[i][j] += matrix.mymatrix[i][j];
            }
        }


    }

    @Override
    public void addValue(Sumabil value) {

        addTwomatrix((MyMatrix) value);
    }

}
