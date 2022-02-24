import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.LineNumberReader;


import java.util.ArrayList;

/* Clasa folosita pentru reprezentarea muntilor */
class Mountains {

	long height;
	long excavatingCost;

	public Mountains(long height, long excavatingCost) {
		this.height = height;
		this.excavatingCost = excavatingCost;
	}

	public long getHeight() {
		return height;
	}

	public void setHeight(long height) {
		this.height = height;
	}

	public long getExcavatingCost() {
		return excavatingCost;
	}

	public void setExcavatingCost(long excavatingCost) {
		this.excavatingCost = excavatingCost;
	}

	@Override
	public String toString() {
		return "Mountains{"
				+ "height="
				+ height
				+ ", excavatingCost="
				+ excavatingCost
				+ '}';
	}
}

public class Ridge {

	public static void main(String[] args) throws IOException {

		Integer numOfmountains = 0;
		String currentLine;
		ArrayList<Mountains> mountains = new ArrayList<>();

		LineNumberReader objReader
				= new LineNumberReader(new FileReader("ridge.in"));

		while ((currentLine = objReader.readLine()) != null) {

			String[] values = currentLine.split(" ");
			if (objReader.getLineNumber() == 1) {
				numOfmountains = Integer.parseInt(values[0]);
			} else {
				Mountains mountain
						= new Mountains(Long.parseLong(values[0]), Long.parseLong(values[1]));
				mountains.add(mountain);
			}
		}


		/* Declar matricea pentru costurile minime pentru
		generarea muntelui in formatul dorit */
		long[][] minCost = new long[numOfmountains][3];

		/* Cele 3 cazuri de baza */

		/* Incrementam primul element cu i <==> i = 1,2 */
		minCost[0][0] = 0;
		minCost[0][1] = mountains.get(0).getExcavatingCost();
		minCost[0][2] = mountains.get(0).getExcavatingCost() * 2;

		for (int i = 1; i < numOfmountains; i++) {
			for (int j = 0; j < 3; j++) {

				long minEdge = Long.MAX_VALUE;

				if ((mountains.get(i).getHeight() - j) >= 0) {

					/* Daca elementul curent nu este egal cu elementul anterior ce nu a
					a fost decrementat */
					if (mountains.get(i).getHeight() - j != mountains.get(i - 1).getHeight()) {

						minEdge = Math.min(minEdge, minCost[i - 1][0]);
					}
				}

				if ((mountains.get(i).getHeight() - j) >= 0) {

					/* Daca elementul curent nu este egal cu elementul anterior dupa ce a
					fost sapat cu 1 */
					if (mountains.get(i).getHeight() - j != mountains.get(i - 1).getHeight() - 1) {

						minEdge = Math.min(minEdge, minCost[i - 1][1]);
					}
				}

				if ((mountains.get(i).getHeight() - j) >= 0) {

					/* Daca elementul curent nu este egal cu elementul anterior dupa ce a
					fost sapat cu 2 */
					if (mountains.get(i).getHeight() - j != mountains.get(i - 1).getHeight() - 2) {

						minEdge = Math.min(minEdge, minCost[i - 1][2]);
					}
				}

				/* Alegem minimul dintre cazurile de mai sus si ma asigur
				ca minimul nu a ramas */
				if (minEdge == Long.MAX_VALUE) {

					minCost[i][j] = minEdge;
				} else {

					minCost[i][j] = j * mountains.get(i).getExcavatingCost() + minEdge;
				}

			}
		}

		long finalMinedge = Long.MAX_VALUE;

		/* Costul minim pentru obtinerea unui munte cu criteriile
		din enunt */
		for (int i = 0; i < 3; i++) {

			finalMinedge = Math.min(finalMinedge,
					minCost[numOfmountains - 1][i]);
		}

		BufferedWriter writer
				= new BufferedWriter(new FileWriter("ridge.out"));
		writer.write(Long.toString(finalMinedge));
		writer.close();
	}
}
