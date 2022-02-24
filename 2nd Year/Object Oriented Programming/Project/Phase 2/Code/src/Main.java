import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.SerializationFeature;
import entities.displayinstances.FinalConsumers;
import entities.humaninstances.*;
import fileloader.Data;
import fileloader.DataLoader;

import java.util.ArrayList;

/**
 * Entry point to the simulation
 */
public final class Main {

    private Main() { }

    /**
     * Main function which reads the input file and starts simulation
     *
     * @param args input and output files
     * @throws Exception might error when reading/writing/opening files, parsing JSON
     */
    public static void main(final String[] args) throws Exception {

        DataLoader loader = new DataLoader("./checker/resources/in/basic_10.json");
        Data inputdata = loader.parseInput();

        /* Allocating memory for the consumer and distributor changes. */
        InstanceConsumer consumer = InstanceConsumer.getInstance();
        InstanceDistributor distributor = InstanceDistributor.getInstance();

        ArrayList<InstanceConsumer> initialconsumers = new ArrayList<>();
        ArrayList<InstanceDistributor> initialdistributors = new ArrayList<>();
        ArrayList<InstanceProducer> initialproducers = new ArrayList<>();
        ArrayList<MonthlyTurnUpdates> monthlyupdates = new ArrayList<>();
        ArrayList<InstanceConsumer> discharged = new ArrayList<>();
        long MAXIMUM_CONTRACT_PRICE = 999999999;


        /* Adding the parsed data into the consumer list. */
        for (int i = 0; i < inputdata.getInputconsumers().size(); i++) {

            consumer.setId(inputdata.getInputconsumers().get(i).getId());
            consumer.setBudget(inputdata.getInputconsumers().get(i).getBudget());
            consumer.setMonthlyIncome(inputdata.getInputconsumers().get(i).getMonthlyIncome());
            consumer.setBankrupt(inputdata.getInputconsumers().get(i).isBankrupt());
            consumer.setWarnings(inputdata.getInputconsumers().get(i).getWarnings());
            consumer.setDebt(inputdata.getInputconsumers().get(i).getDebt());
            consumer.setRemainderMonths(inputdata.getInputconsumers().get(i).getRemainderMonths());
            consumer.setCurrentcontract(inputdata.getInputconsumers().get(i).getCurrentcontract());

            initialconsumers.add(consumer);
            consumer = new InstanceConsumer();

        }

        /* Adding the parsed data into the distributor list. */
        for (int i = 0; i < inputdata.getInputdistributors().size(); i++) {

            distributor.setId(inputdata.getInputdistributors().get(i).getId());
            distributor
                    .setContractLength(inputdata.getInputdistributors().get(i).getContractLength());
            distributor.setBudget(inputdata.getInputdistributors().get(i).getBudget());
            distributor
                    .setInfrastructureCost(inputdata
                            .getInputdistributors().get(i).getInfrastructureCost());
            distributor
                    .setProductionCost(inputdata.getInputdistributors().get(i).getProductionCost());
            distributor
                    .setContractprice(inputdata.getInputdistributors().get(i).getContractprice());
            distributor.setBankrupt(inputdata.getInputdistributors().get(i).isBankrupt());
            distributor.setContracts(inputdata.getInputdistributors().get(i).getContracts());
            distributor
                    .setEnergyNeededKW(inputdata.getInputdistributors().get(i).getEnergyNeededKW());
            distributor
                    .setProducerStrategy(inputdata
                            .getInputdistributors().get(i).getProducerStrategy());

            initialdistributors.add(distributor);
            distributor = new InstanceDistributor();
        }

        for (int i = 0; i < inputdata.getInputproducers().size(); i++) {

            InstanceProducer producer =
                    new InstanceProducer(inputdata.getInputproducers().get(i).getId(),
                            inputdata.getInputproducers().get(i).getEnergyType(),
                            inputdata.getInputproducers().get(i).getMaxDistributors(),
                            inputdata.getInputproducers().get(i).getPriceKW(),
                            inputdata.getInputproducers().get(i).getEnergyPerDistributor(),
                            inputdata.getInputproducers().get(i).isRenewable(),
                            inputdata.getInputproducers().get(i).getDistributorCapacity());

            initialproducers.add(producer);
        }

        /* Adding the parsed data into the monthly updates list. */
        for (int i = 0; i < inputdata.getInputmonthlyupdates().size(); i++) {

            MonthlyTurnUpdates updates =
                    new MonthlyTurnUpdates(inputdata.getInputmonthlyupdates().get(i)
                            .getNewconsumers(),
                            inputdata.getInputmonthlyupdates().get(i).getDistributorchanges(),
                            inputdata.getInputmonthlyupdates().get(i).getProducerchanges());

            monthlyupdates.add(updates);
        }

        // Round 0

        int chosenidx = -1;
        // Remember the index of the distributor with the lowest contract
        for (int i = 0; i < initialdistributors.size(); i++) {

            long profit
                    = Math.round(Math.floor(0.2 * initialdistributors.get(i).getProductionCost()));

            long infrastucturecost = initialdistributors.get(i).getInfrastructureCost();
            long productioncost = initialdistributors.get(i).getProductionCost();

            initialdistributors.get(i)
                    .setContractprice(infrastucturecost + productioncost + profit);

            if (initialdistributors.get(i).getContractprice() < MAXIMUM_CONTRACT_PRICE) {
                chosenidx = i;
                MAXIMUM_CONTRACT_PRICE = initialdistributors.get(i).getContractprice();
            }
        }

        // Reallocate the budget of the consumers accordingly
        for (int i = 0; i < initialconsumers.size(); i++) {

            long monthlyincome = initialconsumers.get(i).getMonthlyIncome();
            long budget = initialconsumers.get(i).getBudget();
            long contractprice = initialdistributors.get(chosenidx).getContractprice();

            initialconsumers.get(i).setBudget(budget + monthlyincome - contractprice);
            initialconsumers.get(i)
                    .setRemainderMonths(initialdistributors.get(chosenidx).getContractLength());
            initialconsumers.get(i).setCurrentcontract(contractprice);


            // Also add the clients to the list of contracts of the distributor
            Contract newcontract = new Contract(initialconsumers.get(i).getId(), contractprice,
                    initialdistributors.get(chosenidx).getContractLength(), false);

            initialdistributors.get(chosenidx).getContracts().add(newcontract);
        }

        // Set new budget for distributors
        for (int i = 0; i < initialdistributors.size(); i++) {

            if (initialdistributors.get(i).getContracts().size() == 0) {
                initialdistributors.get(i).setBudget(initialdistributors.get(i).getBudget()
                        - initialdistributors.get(i).getInfrastructureCost());
            } else {

                long infrastucture = initialdistributors.get(i).getInfrastructureCost();
                long finalproductioncost = initialdistributors.get(i).getProductionCost()
                        * initialdistributors.get(i).getContracts().size();
                long spendings = infrastucture + finalproductioncost;
                initialdistributors.get(i).setBudget(initialdistributors.get(i).getBudget()
                        - spendings + initialdistributors.get(i).getContractprice()
                        * initialdistributors.get(i).getContracts().size());
            }
        }

        // Used for formatting the output file adequately
        ObjectMapper mapper = new ObjectMapper().enable(SerializationFeature.INDENT_OUTPUT);
        mapper.enableDefaultTyping();

        // Preparing the consumers for the jackson output
        ArrayList<FinalConsumers> consumers = new ArrayList<>();
        for (int i = 0; i < initialconsumers.size(); i++) {
            FinalConsumers finalconsumer = new FinalConsumers(initialconsumers.get(i).getId(),
                    initialconsumers.get(i).isBankrupt(), initialconsumers.get(i).getBudget());

            consumers.add(finalconsumer);
        }


    }
}
