package task2;

import java.util.Arrays;

public class Course {
    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    private String title;
    private String description;

    public Student[] getStudents() {
        return students;
    }

    public void setStudents(Student[] students) {
        this.students = students;
    }

    private Student[] students = new Student[3];

    Student[] filterYear(Student[] students, int x) {
        int i, k=0;
        Student[] list = new Student[3];
        for(i=0; i < students.length; i++){
            if(x == students[i].getYear()){
                list[k] = students[i];
                k++;
            }
        }
        return list;
    }
}
