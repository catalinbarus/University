import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.LineNumberReader;

import java.util.ArrayList;

/* Clasa folosita pentru reprezentarea actiunilor */
class AvailableStocks {

	long stockPrice;
	long minValue;
	long maxValue;

	public AvailableStocks(long stockPrice, long minValue, long maxValue) {
		this.stockPrice = stockPrice;
		this.minValue = minValue;
		this.maxValue = maxValue;
	}

	public long getStockPrice() {
		return stockPrice;
	}

	public void setStockPrice(long stockPrice) {
		this.stockPrice = stockPrice;
	}

	public long getMinValue() {
		return minValue;
	}

	public void setMinValue(long minValue) {
		this.minValue = minValue;
	}

	public long getMaxValue() {
		return maxValue;
	}

	public void setMaxValue(long maxValue) {
		this.maxValue = maxValue;
	}

	@Override
	public String toString() {
		return "availableStocks{"
				+ "stockPrice="
				+ stockPrice
				+ ", minValue="
				+ minValue
				+ ", maxValue="
				+ maxValue
				+ '}';
	}
}


public class Stocks {

	public static void main(String[] args) throws IOException {

		Integer numOfstocks = 0, budget = 0, maxLoss = 0;
		ArrayList<AvailableStocks> stocks = new ArrayList<>();

		String currentLine;
		LineNumberReader objReader
				= new LineNumberReader(new FileReader("stocks.in"));

		/* Citesc pe rand numarul de actiuni, bugetul si max loss */
		while ((currentLine = objReader.readLine()) != null) {

			String[] values = currentLine.split(" ");
			if (objReader.getLineNumber() == 1) {
				numOfstocks = Integer.parseInt(values[0]);
				budget = Integer.parseInt(values[1]);
				maxLoss = Integer.parseInt(values[2]);
			} else {
				/* Citesc pentru fiecare actiune pretul ei, si catigul maxim
				si minim */
				AvailableStocks stock
						= new AvailableStocks(Integer.parseInt(values[0]),
						Integer.parseInt(values[1]), Integer.parseInt(values[2]));
				stocks.add(stock);
			}
		}

		/* Initializez un array tridimensioal pentru a retine exact modificarile pentru
		fiecare actiune */
		long[][][] maximumStocks
				= new long[(int) (numOfstocks + 1)][(int) (budget + 1)][(int) (maxLoss + 1)];

		for (int i = 1; i <= numOfstocks; i++) {
			for (int j = 1; j <= budget; j++) {
				for (int k = 1; k <= maxLoss; k++) {

					/* Daca am bugetul suficient, iar pierderile sunt mai mici decat max loss
					actualizez profitul obtinut */
					if ((j >= stocks.get(i - 1).getStockPrice())
							&& ((stocks.get(i - 1).getStockPrice()
									- stocks.get(i - 1).getMinValue()) <= k)) {

						maximumStocks[i][j][k] = Math.max(maximumStocks[i - 1][j][k],
								maximumStocks[i - 1]
										[(int) (j - stocks.get(i - 1).getStockPrice())]
										[(int) (k - (stocks.get(i - 1).getStockPrice()
										- stocks.get(i - 1).getMinValue()))]
											+ (stocks.get(i - 1).getMaxValue()
											- stocks.get(i - 1).getStockPrice()));

					} else {

						maximumStocks[i][j][k] = maximumStocks[i - 1][j][k];
					}
				}
			}
		}

		/* Returnez profitul maxim obtinut */
		long r = maximumStocks[numOfstocks][budget][maxLoss];

		/* Convertesc rezultatul la String si il afisez in BufferedWriter */
		String result = Long.toString(r);

		BufferedWriter writer
				= new BufferedWriter(new FileWriter("stocks.out"));
		writer.write(result);
		writer.close();
	}
}
