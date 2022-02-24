package fileloader;

import humaninstances.Contract;
import humaninstances.InstanceConsumer;
import humaninstances.InstanceDistributor;
import humaninstances.MonthlyTurnUpdates;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

/* Class used for reading the json data */
public class DataLoader {

    private final String path;

    public DataLoader(final String path) {
        this.path = path;
    }

    /**
     *
     */
    public String getPath() {
        return path;
    }

    /**
     *
     */
    public Data parseInput() {

        ArrayList<InstanceConsumer> finalconsumers = new ArrayList<>();
        ArrayList<InstanceDistributor> finaldistributors = new ArrayList<>();
        ArrayList<MonthlyTurnUpdates> finalmonthlyupdates = new ArrayList<>();
        long numOfturns = 0;

        JSONParser parser = new JSONParser();

        try {

            Object object
                    = parser.parse(new FileReader(path));

            JSONObject jsonObject = (JSONObject) object;
            numOfturns = (long) jsonObject.get("numberOfTurns");
            JSONObject initialData = (JSONObject) jsonObject.get("initialData");
            JSONArray consumers = (JSONArray) initialData.get("consumers");


            for (int i = 0; i < consumers.size(); i++) {
                JSONObject consumerObject = (JSONObject) consumers.get(i);
                long id = (long) consumerObject.get("id");
                long initialBudget = (long) consumerObject.get("initialBudget");
                long monthlyIncome = (long) consumerObject.get("monthlyIncome");

                InstanceConsumer consumer = new InstanceConsumer(id, initialBudget, monthlyIncome,
                        false, 0, 0, 0, 0);
                finalconsumers.add(consumer);
            }

            JSONArray distributors = (JSONArray) initialData.get("distributors");

            for (int i = 0; i < distributors.size(); i++) {
                JSONObject distributorObject = (JSONObject) distributors.get(i);
                long id = (long) distributorObject.get("id");
                long contractLength = (long) distributorObject.get("contractLength");
                long initialBudget = (long) distributorObject.get("initialBudget");
                long initialInfrastructureCost
                        = (long) distributorObject.get("initialInfrastructureCost");
                long initialProductionCost = (long) distributorObject.get("initialProductionCost");
                ArrayList<Contract> initialcontracts = new ArrayList<>();

                InstanceDistributor distributor
                        = new InstanceDistributor(id, contractLength,
                        initialBudget, initialInfrastructureCost, initialProductionCost,
                        0,false, initialcontracts);

                finaldistributors.add(distributor);
            }

            JSONArray monthlyUpdates = (JSONArray) jsonObject.get("monthlyUpdates");

            for (int i = 0; i < monthlyUpdates.size(); i++) {

                JSONObject getmonthlyData = (JSONObject) monthlyUpdates.get(i);

                JSONArray newConsumers = (JSONArray) getmonthlyData.get("newConsumers");
                ArrayList<InstanceConsumer> monthlyconsumers = new ArrayList<>();
                ArrayList<InstanceDistributor> monthlydistirbutors = new ArrayList<>();


                for (int j = 0; j < newConsumers.size(); j++) {
                    JSONObject consumerObject = (JSONObject) newConsumers.get(j);
                    long id = (long) consumerObject.get("id");
                    long initialBudget = (long) consumerObject.get("initialBudget");
                    long monthlyIncome = (long) consumerObject.get("monthlyIncome");

                    InstanceConsumer consumer
                            = new InstanceConsumer(id, initialBudget,
                            monthlyIncome, false, 0, 0, 0,
                            0);
                    monthlyconsumers.add(consumer);
                }

                JSONArray costsChanges = (JSONArray) getmonthlyData.get("costsChanges");

                for (int j = 0; j < costsChanges.size(); j++) {
                    JSONObject distributorObject = (JSONObject) costsChanges.get(j);
                    long id = (long) distributorObject.get("id");

                    long infrastructureCost
                            = (long) distributorObject.get("infrastructureCost");
                    long productionCost = (long) distributorObject.get("productionCost");
                    ArrayList<Contract> dummycontracts = new ArrayList<>();

                    InstanceDistributor distributor
                            = new InstanceDistributor(id, 0,
                            0, infrastructureCost, productionCost, 0,
                            false, dummycontracts);
                    monthlydistirbutors.add(distributor);
                }

                MonthlyTurnUpdates finalupdates
                        = new MonthlyTurnUpdates(monthlyconsumers, monthlydistirbutors);
                finalmonthlyupdates.add(finalupdates);
            }

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ParseException e) {
            e.printStackTrace();
        }

        return new Data(numOfturns, finalconsumers, finaldistributors, finalmonthlyupdates);
    }

}
