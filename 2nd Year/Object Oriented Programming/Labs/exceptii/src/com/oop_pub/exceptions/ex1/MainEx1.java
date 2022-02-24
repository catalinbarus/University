package com.oop_pub.exceptions.ex1;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MainEx1 {
    private static void readAndPrintLine() throws IOException {

        BufferedReader reader = null;
        String final_string = null;

        try {
             reader = new BufferedReader(new InputStreamReader(System.in));

            // TODO: Read a line from stdin and print it to stdout
            // TODO: Don't forget to close the reader (Hint: try-with-resources, try-finally)

            char[] string = new char[10];
            int numofcharacters = reader.read(string, 0, 10);

            if (numofcharacters != -1) {
                final_string = new String(string, 0, numofcharacters);
            } else {
                final_string = "";
            }

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (reader != null) {

                try {
                    reader.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }

        System.out.println(final_string);
    }

    public static void main(String[] args) throws IOException {

        readAndPrintLine();
    }
}
