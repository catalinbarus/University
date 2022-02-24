package com.poo.lab12.reports;

import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import com.poo.lab12.entities.Account;
import com.poo.lab12.entities.Bank;
import com.poo.lab12.entities.Business;
import com.poo.lab12.entities.Disability;
import com.poo.lab12.entities.Employee;
import com.poo.lab12.entities.Gender;
import com.poo.lab12.entities.Project;
import com.poo.lab12.entities.Religion;

public class BusinessReport {

    public static Map<Disability, List<Employee>> getEmployeesOnSameDisability(Business business) {

       Set<Employee> employees = business.getEmployees();

       List<Employee> employees_list = employees.stream().collect(Collectors.toList());

       Map<Disability, List<Employee>> final_map = new HashMap<>();

       final_map = employees_list.stream().collect(Collectors.groupingBy(s -> s.getDisability(),
               Collectors.mapping(t -> t, Collectors.toList())));

        System.out.println(final_map);

        return final_map;
    }

    public static int getNumberOfProjectsWorkedByCurrentEmployees(Business business) {

        Set<Employee> employees = business.getEmployees();

        Stream<List<Project>> projects = employees.stream().map(Employee::getProjects);

        Integer dim = projects.map(s -> s.size()).reduce(0, (x, y) -> x + y);

        System.out.println(dim);

        return dim;
    }

    public static SortedSet getEmployeesMaxByReligionMaxByGenderSortedByCitySortedByAge(Business business) {

        return null;
    }

    public static Religion getReligionOfEmployeesWithMostAccounts(Business business) {

        Set<Employee> employees = business.getEmployees();

        SortedSet<Employee> sorted_employees =
                new TreeSet<Employee>(Comparator.comparing(s -> s.getAccounts().size()));

        Optional.ofNullable(employees).ifPresent(sorted_employees::addAll);

        List<Employee> sorted_employee_list = new ArrayList<>(sorted_employees);

        Religion desired_religion =
                sorted_employee_list.get(sorted_employee_list.size() - 1).getReligion();

        System.out.println(desired_religion);

        return desired_religion;
    }

    public static Map<Project, Map<String, List<Employee>>> getEmployeesOnSameProjectAndCity(Business business) {

        Set<Employee> employees = business.getEmployees();

        List<Employee> employee_list = new ArrayList<>(employees);

        Map<String, List<Employee>> city_map = new HashMap<>();

        city_map = employee_list.stream().collect(Collectors.groupingBy(s -> s.getCity(),
                Collectors.mapping(t -> t, Collectors.toList())));

        Map<Project, Map<String, List<Employee>>> final_map = new HashMap<>();



        return null;
    }

    public static Map<Religion, Map<Gender, List<Employee>>> getEmployeesOnSameReligionAndGender(Business business) {

        return null;
    }
}
