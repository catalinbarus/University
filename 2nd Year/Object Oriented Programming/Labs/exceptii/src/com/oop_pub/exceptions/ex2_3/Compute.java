package com.oop_pub.exceptions.ex2_3;

import java.util.Collection;

public class Compute implements Calculator {

    @Override
    public Double add(Double nr1, Double nr2) {

        if (nr1 == null || nr2 == null) {
            throw new NullParameterException();
        }

        Double result = 0.00;

        result = nr1 + nr2;

        if (result == Double.POSITIVE_INFINITY) {
            throw new OverflowException();
        }

        if (result == Double.NEGATIVE_INFINITY) {
            throw new UnderflowException();
        }

        return result;
    }

    @Override
    public Double divide(Double nr1, Double nr2) {

        if (nr1 == null || nr2 == null) {
            throw new NullParameterException();
        }

        Double result = nr1 / nr2;
        return result;
    }

    @Override
    public Double average(Collection<Double> numbers) {

        Double sum = 0.00;

        for (Double x : numbers) {

            if (x == null) {
                throw new NullParameterException();
            }

            sum += x;
        }


        if (sum == Double.POSITIVE_INFINITY) {
            throw new OverflowException();
        }

        if (sum == Double.NEGATIVE_INFINITY) {
            throw new UnderflowException();
        }

        sum = sum / numbers.size();
        return sum;
    }
}
