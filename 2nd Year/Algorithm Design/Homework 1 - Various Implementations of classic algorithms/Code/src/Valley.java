import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.LineNumberReader;

import java.util.ArrayList;


public class Valley {

	public static void main(String[] args) throws IOException {

		int N = 0;
		ArrayList<Integer> heights = new ArrayList<>();

		String currentLine;
		LineNumberReader objReader
				= new LineNumberReader(new FileReader("valley.in"));

		/* Citesc pe rand numarul de munti si inaltimile acestora */
		while ((currentLine = objReader.readLine()) != null) {

			String[] values = currentLine.split(" ");
			if (objReader.getLineNumber() == 1) {
				N = Integer.parseInt(values[0]);
			} else {

				for (int i = 0; i < N; i++) {
					heights.add(Integer.parseInt(values[i]));
				}
			}
		}

		/* Determin minim-ul din array si index-ul la care se gaseste */
		Integer minValley = Integer.MAX_VALUE;
		Integer minIdx = 0;

		for (int i = 0; i < N; i++) {
			if (heights.get(i) < minValley) {
				minValley = heights.get(i);
				minIdx = i;
			}
		}

		long r = 0;

		/* Daca minimul se intampla sa fie ultimul element din vector
		fac penultimul element sa fie egal cu el */
		if (minValley == heights.get(heights.size() - 1)) {

			r = heights.get(heights.size() - 2) - minValley;
			heights.set(heights.size() - 2, minValley);
			minIdx = heights.size() - 2;

			/* Parcurg array-ul si verific daca se respacta conditia ca
			array-ul sa fie vale */
			for (int i = 0; i < minIdx - 1; i++) {
				if (heights.get(i) < heights.get(i + 1)) {
					/* Updatez numarul de excavari si inaltimea vaii */
					r = r + (heights.get(i + 1) - heights.get(i));
					heights.set(i + 1, heights.get(i));
				}
			}
		} else if (minValley == heights.get(0)) {

			r = heights.get(1) - heights.get(0);
			heights.set(1, heights.get(0));
			minIdx = 1;

			/* Parcurg array-ul si verific daca se respacta conditia ca
			array-ul sa fie vale */
			for (int i = N - 1; i > minIdx; i--) {

				if (heights.get(i) < heights.get(i - 1)) {
					/* Updatez numarul de excavari si inaltimea vaii */
					r = r + (heights.get(i - 1) - heights.get(i));
					heights.set(i - 1, heights.get(i));
				}
			}
		} else {

			/* Parcurg array-ul si verific daca se respacta conditia ca
			array-ul sa fie vale */
			for (int i = 0; i < minIdx - 1; i++) {
				if (heights.get(i) < heights.get(i + 1)) {
					/* Updatez numarul de excavari si inaltimea vaii */
					r = r + (heights.get(i + 1) - heights.get(i));
					heights.set(i + 1, heights.get(i));
				}
			}

			/* Parcurg array-ul si verific daca se respacta conditia ca
			array-ul sa fie vale */
			for (int i = N - 1; i > minIdx; i--) {

				if (heights.get(i) < heights.get(i - 1)) {
					/* Updatez numarul de excavari si inaltimea vaii */
					r = r + (heights.get(i - 1) - heights.get(i));
					heights.set(i - 1, heights.get(i));
				}
			}
		}

		String result = Long.toString(r);
		BufferedWriter writer
				= new BufferedWriter(new FileWriter("valley.out"));
		writer.write(result);
		writer.close();

	}
}
