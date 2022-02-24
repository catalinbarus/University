package com.oop_pub.exceptions.ex2_3;

import java.util.List;

public class MainEx2 {
    public static void main(String[] args) {
        // TODO: Initialize the calculator
        Calculator calculator = new Compute();

        System.out.println(calculator.add(2d, 3d));
        System.out.println(calculator.divide(9d, 4d));
        System.out.println(calculator.average(List.of(1d, 2d, 3d, 4d)));

        // TODO: Test edge cases that would throw exceptions

        //System.out.println(calculator.add(2d, null));
        //System.out.println(calculator.add(2d, Double.POSITIVE_INFINITY));
        //System.out.println(calculator.add(2d, Double.NEGATIVE_INFINITY));
        System.out.println(calculator.divide(2d, null));
        //System.out.println(calculator.average(List.of(1d, 2d, 3d, null)));

        /** Exerctiul 3 **/

        // Pentru exercitiul trecut, este firesc sa folosim exceptii de tipul unchecked, deoarece
        // am intalnit erori legate de Runtime.

    }
}
