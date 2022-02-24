import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.SerializationFeature;
import displayinstances.FinalConsumers;
import displayinstances.FinalContracts;
import displayinstances.FinalDistributors;
import displayinstances.FinalPrint;
import fileloader.Data;
import fileloader.DataLoader;
import humaninstances.Contract;
import humaninstances.InstanceConsumer;
import humaninstances.InstanceDistributor;
import humaninstances.MonthlyTurnUpdates;

import java.io.File;
import java.io.IOException;
import java.lang.reflect.Array;
import java.util.ArrayList;


public class Main {

    /**
     * The entrypoint of the implementation
     */
    public static void main(final String[] args) throws Exception {


        DataLoader loader = new DataLoader("./checker/resources/in/basic_1.json");
        Data inputdata = loader.parseInput();

        /* Allocating memory for the consumer and distributor changes. */
        InstanceConsumer consumer = InstanceConsumer.getInstance();
        InstanceDistributor distributor = InstanceDistributor.getInstance();

        ArrayList<InstanceConsumer> initialconsumers = new ArrayList<>();
        ArrayList<InstanceDistributor> initialdistributors = new ArrayList<>();
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

            initialdistributors.add(distributor);
            distributor = new InstanceDistributor();
        }

        /* Adding the parsed data into the monthly updates list. */
        for (int i = 0; i < inputdata.getInputmonthlyupdates().size(); i++) {

            MonthlyTurnUpdates updates =
                    new MonthlyTurnUpdates(inputdata.getInputmonthlyupdates().get(i)
                            .getNewconsumers(),
                            inputdata.getInputmonthlyupdates().get(i).getDistributorchanges());

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

        //System.out.println(initialconsumers);
        //System.out.println(initialdistributors);

        // The actual beginning of the rounds
        for (int i = 0; i < (int) inputdata.getNumOfTurns(); i++) {

            // Update the cost changes monthly
            if (monthlyupdates.get(i).getDistributorchanges().size() != 0) {
                for (int j = 0; j < monthlyupdates.get(i).getDistributorchanges().size(); j++) {
                    for (int k = 0; k < initialdistributors.size(); k++) {
                        if (initialdistributors.get(k).isBankrupt() == false) {
                            if (initialdistributors.get(k).getId()
                                    == monthlyupdates.get(i).getDistributorchanges().get(j).getId()) {
                                initialdistributors.get(k)
                                        .setInfrastructureCost(monthlyupdates.get(i)
                                                .getDistributorchanges()
                                                .get(j).getInfrastructureCost());

                                initialdistributors.get(k).setProductionCost(monthlyupdates.get(i)
                                        .getDistributorchanges().get(j).getProductionCost());
                            }
                        }
                    }
                }
            }


            MAXIMUM_CONTRACT_PRICE = 999999999;
            chosenidx = -1;
            for (int j = 0; j < initialdistributors.size(); j++) {
                if (initialdistributors.get(j).isBankrupt() == false) {

                    long profit
                            = Math.round(Math.floor(0.2 * initialdistributors.get(j)
                            .getProductionCost()));

                    long infrastucturecost = initialdistributors.get(j).getInfrastructureCost();
                    long productioncost = initialdistributors.get(j).getProductionCost();

                    long numberofConsumers = 1;
                    if (initialdistributors.get(j).getContracts().size() != 0) {
                        numberofConsumers = initialdistributors.get(j).getContracts().size();
                    }

                    initialdistributors.get(j)
                            .setContractprice(infrastucturecost / numberofConsumers
                                    + productioncost + profit);

                    if (initialdistributors.get(j).getContractprice() < MAXIMUM_CONTRACT_PRICE) {
                        chosenidx = j;
                        MAXIMUM_CONTRACT_PRICE = initialdistributors.get(j).getContractprice();
                    }
                    //System.out.println(initialdistributors);
                }

            }

            // Add new consumers, if any, to the consumer list
            /*if (monthlyupdates.get(i).getNewconsumers().size() != 0) {
                for (int j = 0; j < monthlyupdates.get(i).getNewconsumers().size(); j++) {
                    initialconsumers.add(monthlyupdates.get(i).getNewconsumers().get(j));
                   // System.out.println(monthlyupdates.get(i).getNewconsumers().get(j));
                }
            }*/


            for (int j = 0; j < initialdistributors.size(); j++) {

                if (initialdistributors.get(j).isBankrupt() == false) {
                    if (initialdistributors.get(j).getContracts().size() != 0) {
                        for (int k = 0; k < initialdistributors.get(j).getContracts().size(); k++) {

                            if (initialdistributors.get(j).getContracts()
                                    .get(k).getRemaindermonths() == 0) {

                                for (int l = 0; l < initialconsumers.size(); l++) {
                                    if (initialconsumers.get(l).getId() == initialdistributors
                                            .get(j).getContracts().get(k).getClientId()) {
                                        discharged.add(initialconsumers.get(l));
                                    }
                                }
                                initialdistributors.get(j).getContracts().remove(k);
                                k--;
                            }
                        }
                    }
                } else {
                    if (initialdistributors.get(j).getContracts().size() != 0) {
                        for (int k = 0; k < initialdistributors.get(j).getContracts().size(); k++) {
                            for (int l = 0; l < initialconsumers.size(); l++) {
                                if (initialconsumers.get(l).getId() == initialdistributors
                                        .get(j).getContracts().get(k).getClientId()) {
                                    discharged.add(initialconsumers.get(l));
                                }
                            }
                            initialdistributors.get(j).getContracts().remove(k);
                            k--;
                        }
                    }
                }
            }

            for (int j = 0; j < discharged.size(); j++) {

                long contractprice = initialdistributors.get(chosenidx).getContractprice();

                Contract newcontract = new Contract(discharged.get(j).getId(), contractprice,
                        initialdistributors.get(chosenidx).getContractLength(), false);

                initialdistributors.get(chosenidx).getContracts().add(newcontract);
            }


            //forul mare
            for (int j = 0; j < initialdistributors.size(); j++) {

                long incomeDistributor = 0;
                long distributorBudget = initialdistributors.get(j).getBudget();
                long mandatoryPayments = 0;

                if (initialdistributors.get(j).isBankrupt() == false) {

                    if (initialdistributors.get(j).getContracts().size() != 0) {

                        for (int k = 0; k < initialdistributors.get(j).getContracts().size(); k++) {

                            for (int l = 0; l < initialconsumers.size(); l++) {
                                if (initialconsumers.get(l).getId() == initialdistributors
                                        .get(j).getContracts().get(k).getClientId()) {

                                    long budget = initialconsumers.get(l).getBudget();

                                    long monthlyIncome = initialconsumers.get(l).getMonthlyIncome();

                                    long contractPrice =
                                            initialconsumers.get(l).getCurrentcontract();

                                    long contractDuration =
                                            initialconsumers.get(l).getRemainderMonths();

                                    if ((budget + monthlyIncome - contractPrice) < 0) {

                                        long warningStatus = initialconsumers.get(l).getWarnings();

                                        long debt = initialconsumers.get(l).getDebt();

                                        if (warningStatus == 0) {

                                            //System.out.println("works");
                                            initialdistributors.get(j).getContracts().get(k)
                                                    .setDelayed(true);

                                            initialdistributors.get(j).getContracts().get(k)
                                                    .setRemaindermonths(contractDuration - 1);

                                            initialconsumers.get(l)
                                                    .setBudget(budget + monthlyIncome);

                                            initialconsumers.get(l).setWarnings(warningStatus + 1);

                                            initialconsumers.get(l).setDebt(contractPrice);

                                            initialconsumers.get(l)
                                                    .setRemainderMonths(contractDuration - 1);

                                            mandatoryPayments =
                                                    mandatoryPayments + initialdistributors
                                                            .get(j).getProductionCost();


                                        } else {

                                            long payments =
                                                    Math.round(Math.floor(1.2 * debt))
                                                            + contractPrice;

                                            if ((budget + monthlyIncome - payments) < 0) {
                                                initialconsumers.get(l).setBankrupt(true);
                                                initialconsumers.get(l)
                                                        .setBudget(budget + monthlyIncome);
                                                initialconsumers.get(l).setWarnings(0);
                                                initialconsumers.get(l).setDebt(0);
                                                initialdistributors.get(j).getContracts().remove(k);

                                                mandatoryPayments =
                                                        mandatoryPayments + initialdistributors
                                                                .get(j).getProductionCost();
                                                k--;
                                            } else {

                                                initialconsumers.get(l)
                                                        .setBudget(budget
                                                                + monthlyIncome - payments);

                                                initialconsumers.get(l).setDebt(0);
                                                initialconsumers.get(l).setWarnings(0);
                                                initialconsumers.get(l)
                                                        .setRemainderMonths(contractDuration - 1);

                                                initialdistributors.get(j).getContracts().get(k)
                                                        .setRemaindermonths(contractDuration - 1);

                                                initialdistributors.get(j).getContracts()
                                                        .get(k).setDelayed(false);

                                                mandatoryPayments =
                                                        mandatoryPayments + initialdistributors
                                                                .get(j).getProductionCost();

                                            }
                                        }
                                    } else {
                                        initialconsumers.get(l)
                                                .setBudget(budget + monthlyIncome - contractPrice);

                                        long warningStatus = initialconsumers.get(l).getWarnings();

                                        long debt = initialconsumers.get(l).getDebt();

                                        if (warningStatus == 1) {
                                            long payments = Math.round(Math.floor(1.2 * debt));

                                            if ((budget - debt) < 0) {

                                                initialconsumers.get(l).setBankrupt(true);
                                                initialconsumers.get(l)
                                                        .setBudget(budget + monthlyIncome);
                                                initialconsumers.get(l).setWarnings(0);
                                                initialconsumers.get(l).setDebt(0);

                                                initialdistributors.get(j).getContracts().remove(k);

                                                mandatoryPayments =
                                                        mandatoryPayments + initialdistributors
                                                                .get(j).getProductionCost();
                                                k--;
                                            } else {

                                                initialconsumers.get(l).setBudget(budget
                                                        + monthlyIncome - contractPrice - debt);

                                                initialconsumers.get(l).setWarnings(0);
                                                initialconsumers.get(l).setDebt(0);
                                                initialconsumers.get(l)
                                                        .setRemainderMonths(contractDuration - 1);
                                                initialdistributors.get(j).getContracts().get(k)
                                                        .setRemaindermonths(contractDuration - 1);
                                                initialdistributors.get(j).getContracts()
                                                        .get(k).setDelayed(false);

                                                mandatoryPayments =
                                                        mandatoryPayments + initialdistributors
                                                                .get(j).getProductionCost();

                                            }
                                        } else {

                                            initialconsumers.get(l).setBudget(budget
                                                    + monthlyIncome -  contractPrice);

                                            mandatoryPayments =
                                                    mandatoryPayments + initialdistributors
                                                            .get(j).getProductionCost();

                                            incomeDistributor = incomeDistributor + contractPrice;

                                        }
                                    }
                                }
                            }

                            distributorBudget = initialdistributors.get(j).getBudget();

                            initialdistributors.get(j).setBudget(distributorBudget
                                    - mandatoryPayments - incomeDistributor);


                        }
                    }

                }


            }


            /*for (int j = 0; j < initialconsumers.size(); j++) {
                long budget = initialconsumers.get(j).getBudget();
                long salary = initialconsumers.get(j).getMonthlyIncome();

                initialconsumers.get(j).setBudget(budget + salary);
            }*/

        }
        System.out.println(initialconsumers);
        System.out.println(discharged);
        System.out.println(initialdistributors);

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

        // Preparing the contracts for the jackson output
        FinalContracts contract;
        ArrayList<FinalContracts> contracts = new ArrayList<>();
        for (int i = 0; i < initialdistributors.size(); i++) {

            if (initialdistributors.get(i).getContracts().size() == 0) {
                contract
                        = new FinalContracts();
                contracts.add(contract);
                contracts.clear();
            }
        }


        // Preparing the distributors for the jackson output
        ArrayList<FinalDistributors> distributors = new ArrayList<>();

        for (int i = 0; i < initialdistributors.size(); i++) {
            FinalDistributors finaldistributor =
                    new FinalDistributors(initialdistributors.get(i).getId(),
                            initialdistributors.get(i).getBudget(),
                            initialdistributors.get(i).isBankrupt(), contracts);
            distributors.add(finaldistributor);
        }

        // Putting it all together in the print object
        FinalPrint print = new FinalPrint(consumers, distributors);

        try {
            mapper.writeValue(new File("./checker/resources/result/basic_1.json"), print);
        } catch (IOException e) {
            e.printStackTrace();
        }


    }
}
