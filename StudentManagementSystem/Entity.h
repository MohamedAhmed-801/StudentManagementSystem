#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Entity {
public:
    virtual void DisplayInfo() const = 0;
    virtual int GetID() const = 0;
    virtual ~Entity() {}
};

class Student : public Entity {
private:
    int StudentID;
    string Name;
    string DOB;
    string ContactInfo;
    float CGPA;
    int CompletedCourses;

public:
    void AddStudent(int id, const string& name, const string& dob, const string& contact, float gpa, int completedCourses) {
        StudentID = id;
        Name = name;
        DOB = dob;
        ContactInfo = contact;
        CGPA = gpa;
        CompletedCourses = completedCourses;
    }

    void EditStudent(int id, const string& name, const string& dob, const string& contact, float gpa, int completedCourses) {
        Name = name;
        DOB = dob;
        ContactInfo = contact;
        CGPA = gpa;
        CompletedCourses = completedCourses;
    }

    void RemoveStudent(int studentID, vector<Student>& students) {
        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->GetStudentID() == studentID) {
                students.erase(it);
                cout << "Student removed successfully." << endl;
                return;
            }
        }
        cout << "Student not found!" << endl;
    }

    void DisplayInfo() const override {
        cout << "Student ID: " << StudentID << endl;
        cout << "Name: " << Name << endl;
        cout << "DOB: " << DOB << endl;
        cout << "Contact: " << ContactInfo << endl;
        cout << "CGPA: " << CGPA << endl;
        cout << "Completed Courses: " << CompletedCourses << endl;
    }

    int GetID() const override {
        return StudentID;
    }

    int GetStudentID() const {
        return StudentID;
    }

    string GetName() const {
        return Name;
    }

    float GetCGPA() const {
        return CGPA;
    }

    void UpdateCGPA(float newCGPA) {
        CGPA = newCGPA;
    }
};

class Course : public Entity {
private:
    int CourseID;
    string CourseName;
    string InstructorName;
    int Credits;
    string Description;

public:
    void AddCourse(int id, const string& name, const string& instructor, int credits, const string& description) {
        CourseID = id;
        CourseName = name;
        InstructorName = instructor;
        Credits = credits;
        Description = description;
    }

    void EditCourse(const string& name, const string& instructor, int credits, int id, const string& description) {
        CourseID = id;
        CourseName = name;
        InstructorName = instructor;
        Credits = credits;
        Description = description;
    }

    void RemoveCourse(int courseID, vector<Course>& courses) {
        for (auto it = courses.begin(); it != courses.end(); ++it) {
            if (it->GetCourseID() == courseID) {
                courses.erase(it);
                cout << "Course removed successfully." << endl;
                return;
            }
        }
        cout << "Course not found!" << endl;
    }

    void DisplayInfo() const override {
        cout << "Course ID: " << CourseID << endl;
        cout << "Course Name: " << CourseName << endl;
        cout << "Instructor: " << InstructorName << endl;
        cout << "Credits: " << Credits << endl;
        cout << "Description: " << Description << endl;

    }

    int GetID() const override {
        return CourseID;
    }

    int GetCourseID() const {
        return CourseID;
    }
};

class Enrollment : public Entity {
private:
    static int nextEnrollmentID;
    int EnrollmentID;
    int StudentID;
    int CourseID;
    string EnrollmentDate;
    string Grade;

public:
    Enrollment() {
        EnrollmentID = ++nextEnrollmentID;
    }

    void EnrollStudent(int studentID, int courseID, const string& date) {
        StudentID = studentID;
        CourseID = courseID;
        EnrollmentDate = date;
        Grade = "Not Assigned";
    }

    void DisplayInfo() const override {
        cout << "Enrollment ID: " << EnrollmentID << endl;
        cout << "Student ID: " << StudentID << endl;
        cout << "Course ID: " << CourseID << endl;
        cout << "Enrollment Date: " << EnrollmentDate << endl;
        cout << "Grade: " << Grade << endl;
    }

    void WithdrawStudent() {
        EnrollmentDate = "Withdrawn";
        Grade = "Withdrawn";
    }

    void UpdateGrade(const string& grade) {
        Grade = grade;
    }

    int GetID() const override {
        return EnrollmentID;
    }

    int GetStudentID() const {
        return StudentID;
    }

    int GetCourseID() const {
        return CourseID;
    }

    string GetGrade() const {
        return Grade;
    }
};

int Enrollment::nextEnrollmentID = 0;

void SearchEntity(int id, const vector<Entity*>& entities) {
    for (const auto& entity : entities) {
        if (entity->GetID() == id) {
            entity->DisplayInfo();
            return;
        }
    }
    cout << "Entity not found!" << endl;
}
