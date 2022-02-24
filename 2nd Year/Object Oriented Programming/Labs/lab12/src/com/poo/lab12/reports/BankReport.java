package com.poo.lab12.reports;

import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import com.poo.lab12.entities.*;

import javax.swing.text.html.Option;

public class BankReport {

    public static int getNumberOfCustomers(Bank bank) {
        // A customer is an Employee that works for a Business (client of the bank)

        int customers = 0;
        Stream<Integer> map = bank.getClients().stream().map(s -> s.getEmployees().size());
        customers = map.reduce(0, (x, y) -> x + y);

        System.out.println(customers);

        return customers;
    }

    public static int getNumberOfAccounts(Bank bank) {
        // Accounts of all the customers of the bank

        int accounts = 0;

        Stream<Set<Employee>> map = bank.getClients().stream().map(Business::getEmployees);
        Stream<Integer> dim = map.map(s -> s.stream().map(t -> t.getAccounts().size()).reduce(0,
                (x, y) -> x + y));

        accounts = dim.reduce(0, (x, y) -> x + y);

        System.out.println(accounts);

        return accounts;
    }

    public static SortedSet getCustomersSorted(Bank bank) {
        // Display the set of customers in alphabetical order

        Stream<Set<Employee>> map = bank.getClients().stream().map(Business::getEmployees);

        Set<Employee> empmap = map.flatMap(Set::stream).collect(Collectors.toSet());

        SortedSet<Employee> sortedEmp =
                new TreeSet<Employee>(Comparator.comparing(Employee::getName));

        Optional.ofNullable(empmap).ifPresent(sortedEmp::addAll);

        System.out.println(sortedEmp.toString());


        return sortedEmp;
    }

    public static double getTotalSumInAccounts(Bank bank) {
        // Sum of all customers' accounts balances

        double sum = 0;

        Stream<Set<Employee>> map = bank.getClients().stream().map(Business::getEmployees);

        Set<Employee> empmap = map.flatMap(Set::stream).collect(Collectors.toSet());

        Stream<Set<Account>> account = empmap.stream().map(Employee::getAccounts);

        Stream<Double> balances = account.map(s -> s.stream().map(t -> t.getBalance()).reduce(Double.valueOf(0),
                (x, y) -> x + y));

        sum = balances.reduce(Double.valueOf(0), (x, y) -> x + y);

        System.out.println(sum);

        return sum;
    }

    public static SortedSet getAccountsSortedBySum(Bank bank) {
        // The set of all accounts, ordered by current account balance

        Stream<Set<Employee>> map = bank.getClients().stream().map(Business::getEmployees);

        Set<Employee> empmap = map.flatMap(Set::stream).collect(Collectors.toSet());

        Stream<Set<Account>> account = empmap.stream().map(Employee::getAccounts);

        Set<Account> initial_accounts = account.flatMap(Set::stream).collect(Collectors.toSet());

        ArrayList<Account> sort_test = new ArrayList<>(initial_accounts);

        Collections.sort(sort_test, new Comparator<Account>(){
            public int compare(Account o1, Account o2){
                if(o1.getBalance() == o2.getBalance())
                    return 0;
                return o1.getBalance() < o2.getBalance() ? -1 : 1;
            }
        });

        /*SortedSet<Account> sorted_accounts = new TreeSet<>(new Comparator<Account>() {
            @Override
            public int compare(Account o1, Account o2) {
                return Integer.valueOf((int)o1.getBalance()).compareTo(Integer.valueOf((int)o2.getBalance()));
            }
        });*/

        //SortedSet<Account> sorted_accounts = new TreeSet<>((a, b) -> a.)



        sorted_accounts.addAll(initial_accounts);

        System.out.println(sorted_accounts);

        return sorted_accounts;
    }

    public static Map<Employee, Collection<Account>> getCustomerAccounts(Bank bank) {
        // Return a map of all the customers with their respective accounts

        Stream<Set<Employee>> map = bank.getClients().stream().map(Business::getEmployees);

        Set<Employee> empmap = map.flatMap(Set::stream).collect(Collectors.toSet());

        Stream<Set<Account>> account = empmap.stream().map(Employee::getAccounts);

        Set<Account> initial_accounts = account.flatMap(Set::stream).collect(Collectors.toSet());

        Map<Employee, Collection<Account>> final_map = new HashMap<>();

        empmap.forEach(a -> final_map.put(a, a.getAccounts()));

        System.out.println(final_map);

        return final_map;
    }

    public static Map<String, List<Employee>> getCustomersByCity(Bank bank) {
        // Map all the customers to their respective cities

        Stream<Set<Employee>> map = bank.getClients().stream().map(Business::getEmployees);

        List<Employee> empmap = map.flatMap(Set::stream).collect(Collectors.toList());

        Map<String, List<Employee>> final_map = new HashMap<>();

        final_map = empmap.stream().collect(Collectors.groupingBy(s -> s.getCity(),
                Collectors.mapping(t -> t, Collectors.toList())));

        System.out.println(final_map);

        return final_map;
    }

    public static Project getProjectWorkedOnByMostCustomers(Bank bank) {

        Stream<List<Project>> map = bank.getClients().stream().map(Business::getProjects);

        List<Project> projects = map.flatMap(List::stream).collect(Collectors.toList());

        Comparator<Project> projectComparator = Comparator.comparing(Project::getWorkers);

        projects.sort(projectComparator);

        Project desired_project = projects.get(projects.size() - 1);

        System.out.println(desired_project);


        return desired_project;
    }

    public static Gender getGenderWhoWorkedOnMostProjects(Bank bank) {

        Stream<Set<Employee>> map = bank.getClients().stream().map(Business::getEmployees);

        Set<Employee> empmap = map.flatMap(Set::stream).collect(Collectors.toSet());

        Stream<List<Project>> projects = empmap.stream().map(Employee::getProjects);

        List<Project> final_projects = projects.flatMap(List::stream).collect(Collectors.toList());

        Set<Employee> males = new HashSet<>();
        Set<Employee> females = new HashSet<>();

        empmap.stream().forEach(i -> {
            if(i.getGender().equals(Gender.MALE)) {
                males.add(i);
            }
        });

        empmap.stream().forEach(i -> {
            if(i.getGender().equals(Gender.FEMALE)) {
                females.add(i);
            }
        });

        int sum_males = 0, sum_females = 0;
        Gender desired_gender;
        Stream<Integer> males_projects = males.stream().map(s -> s.getProjects().size());

        Stream<Integer> females_projects = females.stream().map(s -> s.getProjects().size());

        sum_males = males_projects.reduce(0, (x, y) -> x + y);

        sum_females = females_projects.reduce(0, (x, y) -> x + y);

       if(sum_males > sum_females) {
           desired_gender = Gender.MALE;
       } else {
           desired_gender = Gender.FEMALE;
       }

        System.out.println(desired_gender);

        return desired_gender;
    }
}
