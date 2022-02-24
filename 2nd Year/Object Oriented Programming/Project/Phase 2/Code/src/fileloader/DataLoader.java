package fileloader;

import entities.humaninstances.*;
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
        ArrayList<InstanceProducer> finalproducers = new ArrayList<>();
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
                long energyNeededKW = (long) distributorObject.get("energyNeededKW");
                String producerStrategy = (String) distributorObject.get("producerStrategy");
                ArrayList<Contract> initialcontracts = new ArrayList<>();

                InstanceDistributor distributor
                        = new InstanceDistributor(id, contractLength,
                        initialBudget,
                        initialInfrastructureCost, 0, 0, false,
                        initialcontracts, producerStrategy, energyNeededKW);

                finaldistributors.add(distributor);
            }

            JSONArray producers = (JSONArray) initialData.get("producers");

            for (int i = 0; i < producers.size(); i++) {
                JSONObject producerObject = (JSONObject) producers.get(i);
                long id = (long) producerObject.get("id");
                String energyType = (String) producerObject.get("energyType");
                long maxDistributors = (long) producerObject.get("maxDistributors");
                double priceKW = (double) producerObject.get("priceKW");
                long energyPerDistributor = (long) producerObject.get("energyPerDistributor");

                InstanceProducer producer = new InstanceProducer(id, energyType, maxDistributors,
                        priceKW, energyPerDistributor, false, 0);

                finalproducers.add(producer);
            }

            JSONArray monthlyUpdates = (JSONArray) jsonObject.get("monthlyUpdates");

            for (int i = 0; i < monthlyUpdates.size(); i++) {

                JSONObject getmonthlyData = (JSONObject) monthlyUpdates.get(i);

                JSONArray newConsumers = (JSONArray) getmonthlyData.get("newConsumers");
                ArrayList<InstanceConsumer> monthlyconsumers = new ArrayList<>();
                ArrayList<InstanceDistributor> monthlydistirbutors = new ArrayList<>();
                ArrayList<InstanceProducer> monthlyproducers = new ArrayList<>();


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

                JSONArray distributorChanges
                        = (JSONArray) getmonthlyData.get("distributorChanges");

                for (int j = 0; j < distributorChanges.size(); j++) {
                    JSONObject distributorObject = (JSONObject) distributorChanges.get(i);
                    long id = (long) distributorObject.get("id");
                    long infrastructureCost = (long) distributorObject.get("infrastructureCost");
                    ArrayList<Contract> dummycontracts = new ArrayList<>();

                    InstanceDistributor distributor = new InstanceDistributor(id, 0,
                            0, infrastructureCost, 0, 0,
                            false, dummycontracts, null, 0);
                    monthlydistirbutors.add(distributor);
                }

                JSONArray producerChanges = (JSONArray) getmonthlyData.get("producerChanges");

                for (int j = 0; j < producerChanges.size(); j++) {
                    JSONObject producerObject = (JSONObject) producerChanges.get(i);
                    long id = (long) producerObject.get("id");
                    long energyPerDistributor = (long) producerObject.get("energyPerDistributor");

                    InstanceProducer producer = new InstanceProducer(id, null,
                            0, 0.00, energyPerDistributor,
                            false, 0);
                    monthlyproducers.add(producer);
                }



                MonthlyTurnUpdates finalupdates
                        = new MonthlyTurnUpdates(monthlyconsumers, monthlydistirbutors,
                        monthlyproducers);
                finalmonthlyupdates.add(finalupdates);
            }

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ParseException e) {
            e.printStackTrace();
        }

        return new Data(numOfturns, finalconsumers, finaldistributors, finalproducers,
                finalmonthlyupdates);
    }

}

