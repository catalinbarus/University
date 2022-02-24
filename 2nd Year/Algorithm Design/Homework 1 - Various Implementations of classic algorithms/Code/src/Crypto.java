import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.LineNumberReader;

import java.util.ArrayList;
import java.util.Comparator;

/* Clasa folosita pentru reprezentarea calculatorului */
class ComputerRaid {
	long P;
	long U;

	public ComputerRaid(long p, long u) {
		P = p;
		U = u;
	}

	public long getP() {
		return P;
	}

	public long getU() {
		return U;
	}

	public void setP(long p) {
		P = p;
	}

	public void setU(long u) {
		U = u;
	}

	@Override
	public String toString() {
		return "ComputerRaid{"
				+ "P="
				+ P
				+ ", U="
				+ U
				+ '}';
	}
}

public class Crypto {

	public static void main(String[] args) throws IOException {

		ArrayList<ComputerRaid> computers = new ArrayList<>();

		long b = 0;

		String currentLine;
		LineNumberReader objReader
				= new LineNumberReader(new FileReader("crypto.in"));

		/* Citesc pe rand bugetul si puterea si costul de upgrade
		pentru fiecare calculator */
		while ((currentLine = objReader.readLine()) != null) {

			String[] values = currentLine.split(" ");
			if (objReader.getLineNumber() == 1) {
				b = Long.parseLong(values[1]);
			} else {
				/* Calculatoarele le voi adauga intr-un ArrayList */
				ComputerRaid computer
						= new ComputerRaid(Integer.parseInt(values[0]),
						Integer.parseInt(values[1]));
				computers.add(computer);
			}
		}

		/* Sortez crescator dupa puterea calcul elementele din array */
		computers.sort(Comparator.comparing((ComputerRaid c) -> c.P));

		for (int i = 0; i < computers.size() - 1; i++) {

			/* Upgradez singurul calculator daca mai am bani */
			if (computers.size() == 1 && b >= computers.get(0).getU()) {
				computers.get(0).setP(computers.get(0).getP() + 1);
				break;
			}

			/* Daca puterea primului calculator este mai mica decat a urmatorului
			incep procesul de upgrade pentru calculatorul curent */
			if (computers.get(i).getP() < computers.get(i + 1).getP()) {

				long powerDifference = computers.get(i + 1).getP() - computers.get(i).getP();

				/* Daca mai am bani dupa ce fac atatea upgradeuri primului calcualtor
				* cat sa fie la fel de performant ca urmatorul */
				if ((b - (computers.get(i).getU() * powerDifference)) >= 0) {
					computers.get(i).setP(computers.get(i + 1).getP());
					b = b - (computers.get(i).getU() * powerDifference);

					/* Upgradez primul PC si imi fac unul singur combinand primele doua
					calculatoare (au aceeasi performanta acum) */
					computers.get(i).setU(computers.get(i).getU() + computers.get(i + 1).getU());
					computers.remove(i + 1);

					i--;
				} else if (b >= computers.get(i).getU()) {

					/* Daca nu am suficienti bani incat sa fac primul calculator la fel de bun
					ca al doilea, dar mai am bani sa-i fac upgrade individual */
					computers.get(i).setP(computers.get(i).getP() + 1);
					b = b - computers.get(i).getU();
					i--;
				}
			} else if (computers.get(i).getP() == computers.get(i + 1).getP()) {

				/* Daca am doua calculatoare consecutive cu aceeasi putere
				le fac merge */
				computers.get(i).setU(computers.get(i).getU() + computers.get(i + 1).getU());
				computers.remove(i + 1);
				i--;
			}
			/* Daca ajung sa am un singur calculator, verific daca mai am bani
			* suficienti sa-i fac upgrade */
			if (computers.size() == 1 && b >= computers.get(0).getU()) {
				i--;
			}
		}

		/* Numarul minim de criptomonede pe ora va fi egal cu numarul primului
		calculator din array */
		long r = computers.get(0).getP();

		/* Convertesc rezultatul la String si il afisez in BufferedWriter */
		String result = Long.toString(r);

		BufferedWriter writer
				= new BufferedWriter(new FileWriter("crypto.out"));
		writer.write(result);
		writer.close();
	}
}
