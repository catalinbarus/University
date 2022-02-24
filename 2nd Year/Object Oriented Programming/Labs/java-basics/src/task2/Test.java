package task2;

import java.util.Arrays;

public class Test {
    public static void main(String[] args) {

        Student[] students = new Student[3];
        Student[] listaStudenti = new Student[0];
        Student student1 = new Student();
        Student student2 = new Student();
        Student student3 = new Student();

        Student student4 = new Student();
        Student student5 = new Student();

        Course course1 = new Course();

        course1.setTitle("OOP");
        course1.setDescription("Object Oriented Programming in Java ^_^");

        student1.setYear(1);
        student1.setName("Gigel");
        student2.setYear(2);
        student2.setName("Dorel");
        student3.setYear(2);
        student3.setName("Mirel");
        students[0] = student1;
        students[1] = student2;
        students[2] = student3;

        listaStudenti = course1.filterYear(students, 2);

        System.out.println(Arrays.toString(listaStudenti));

        //Task 3

        student4.setYear(2);
        student4.setName("Dorel");
        student5.setYear(2);
        student5.setName("Dorel");

        System.out.println(student4.equals(student5));
    }
}
