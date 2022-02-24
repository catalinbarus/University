import java.util.*;
import java.lang.*;

public class Student implements Comparable<Student> {
    private long id;
    private String name;
    private String surname;
    private double averageGrade;

    public Student(long id, String name, String surname, double averageGrade) {
        this.id = id; 
        this.name = name;
        this.surname = surname;
        this.averageGrade = averageGrade;
    }

    public long getId() {
        return this.id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public String getName() {
        return this.name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getSurname() {
        return this.surname;
    }

    public void setSurname(String surname) {
        this.surname = surname;
    }

    public double getAverageGrade() {
        return this.averageGrade;
    }

    public void setAverageGrade(double averageGrade) {
        this.averageGrade = averageGrade;
    }

    // Task 1
    public int compareTo(Student student) {

        if(averageGrade == student.averageGrade) {
            if(surname.equals(student.surname)) {
                if(name.equals(student.name)) {
                    return 0;
                } else if(name.compareTo(student.name) > 0) {
                    return 1;
                } else {
                    return -1;
                }
            } else if(surname.compareTo(student.surname) > 0) {
                return 1;
            } else {
                return -1;
            }
        } else if(averageGrade > student.averageGrade) {
            return 1;
        }

        return -1;
    }

    @Override
    public String toString() {
        return "Student{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", surname='" + surname + '\'' +
                ", averageGrade=" + averageGrade +
                '}';
    }

    // For Task 5
    @Override
    public int hashCode() {
        return super.hashCode();
    }

    // For Task 5
    @Override
    public boolean equals(Object obj) {
        return super.equals(obj);
    }

    public static void main(String[] args) {

        Student student1 = new Student(1, "Bogdan", "Ionescu", 8);
        Student student2 = new Student(2, "Florian", "Ionescu", 9);
        Student student3 = new Student(3, "Daniel", "Kappa", 7);
        Student student4 = new Student(4, "Joseph", "Joestar", 10);
        Student student5 = new Student(5, "Dio", "Brando", 5);

        ArrayList<Student> students = new ArrayList<>();
        students.add(student1);
        students.add(student2);
        students.add(student3);
        students.add(student4);
        students.add(student5);

        // Task 2
        /** Before sorting. **/
        System.out.println("Before sorting: " + "\n");
        for(Student student : students) {
            System.out.println(student);
        }

        Collections.sort(students);

        /** After sorting. **/
        System.out.println("After sorting: " + "\n");
        for(Student student : students) {
            System.out.println(student);
        }

        //Task 3
        /** Descending after grade. **/
        students.sort(Comparator.comparing((Student s) -> s.averageGrade).reversed());
        System.out.println("Descending after grade: " + "\n");
        for(Student student : students) {
            System.out.println(student);
        }

        // Task 4
        System.out.println("Students queue:" + "\n");
        PriorityQueue<Student> studentsqueue
                = new PriorityQueue<>(new Comparator<Student>() {

            public int compare(Student o1, Student o2) {
                return Long.compare(o1.id, o2.id);
            }
        });
        studentsqueue.addAll(students);
        for(int i = 0; i < students.size(); i++) {
            System.out.println(studentsqueue.poll());
        }

        // Task 6
        LinkedList<String> subjectsCTI = new LinkedList<>();
        LinkedList<String> subjectsIS = new LinkedList<>();
        subjectsCTI.add("POO");
        subjectsCTI.add("AA");
        subjectsCTI.add("IOCLA");
        subjectsIS.add("TS");
        subjectsIS.add("Elth");
        subjectsIS.add("M4");

        Map<Student, LinkedList<String>> studentcurriculum = new HashMap<>();

        for(Student student : students) {
            if(student.id % 2 != 0) {
                studentcurriculum.put(student, subjectsCTI);
            } else {
                studentcurriculum.put(student, subjectsIS);
            }
        }

        System.out.println("Curriculum hashmap:" + "\n");
        for (Map.Entry<Student, LinkedList<String>> entry : studentcurriculum.entrySet()) {
            System.out.println(entry);
        }


    }


}