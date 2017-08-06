package lab07;
    
    public class Student implements Comparable<Student> {
    String studentSubject;
    String studentLastName;
    String studentFirstName;
    double studentGpa;
    
    public Student(String subject, String lastName, String firstName, double gpa) {
        studentSubject = subject;
        studentLastName = lastName;
        studentFirstName = firstName;
        studentGpa = gpa;
    }
    
    public int compareTo(Student stud) {
        return Double.compare(this.studentGpa, stud.studentGpa);        
    }
    
    public String toString() {
        return studentGpa + " " + studentSubject + " " + studentLastName + " " + studentFirstName;
    }
    
}
