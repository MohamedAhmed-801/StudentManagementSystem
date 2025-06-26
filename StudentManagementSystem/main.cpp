#include "User.h"
#include "Entity.h"
#include <vector>

int main() {
    unordered_map<string, User*> users;
    users["admin"] = new Admin("admin", "adminpass");
    users["teacher"] = new Teacher("teacher", "teacherpass");
    users["student"] = new StudentUser("student", "studentpass");

    string username, password;
    User* loggedInUser = nullptr;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (users.find(username) != users.end() && users[username]->Authenticate(username, password)) {
        loggedInUser = users[username];
        cout << "Login successful!" << endl;
        loggedInUser->DisplayRole();
    } else {
        cout << "Login failed!" << endl;
        return 1;
    }

    vector<Student> students;
    vector<Course> courses;
    vector<Enrollment> enrollments;
    vector<Entity*> entities;

    int choice;
    do {
        cout << "\nStudent Management System\n";
        cout << "1. Add Student\n";
        cout << "2. Edit Student\n";
        cout << "3. Display Student Info\n";
        cout << "4. Add Course\n";
        cout << "5. Edit Course\n";
        cout << "6. Display Course Info\n";
        cout << "7. Enroll Student\n";
        cout << "8. Withdraw Student\n";
        cout << "9. Search Student\n";
        cout << "10. Search Course\n";
        cout << "11. Remove Student\n";
        cout << "12. Remove Course\n";
        cout << "13. Update Grade\n";
        cout << "14. Display All Courses\n";
        cout << "15. Display All Students\n";
        cout << "16. Display All Enrollments\n";
        cout << "17. Calculate and Display GPA\n";
        cout << "18. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            if (dynamic_cast<Admin*>(loggedInUser) == nullptr) {
                cout << "You do not have permission to add students!" << endl;
                break;
            }
            int id;
            string name, dob, contact;
            float gpa;
            int completedCourses;
            cout << "Enter Student ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter DOB: ";
            getline(cin, dob);
            cout << "Enter Contact: ";
            getline(cin, contact);
            cout << "Enter CGPA: ";
            cin >> gpa;
            cout << "Enter Completed Courses: ";
            cin >> completedCourses;
            Student newStudent;
            newStudent.AddStudent(id, name, dob, contact, gpa, completedCourses);
            students.push_back(newStudent);
            entities.push_back(&students.back());
            cout << "Student added successfully!" << endl;
            break;
        }
        case 2: {
            if (dynamic_cast<Admin*>(loggedInUser) == nullptr) {
                cout << "You do not have permission to edit students!" << endl;
                break;
            }
            int id;
            string name, dob, contact;
            float gpa;
            int completedCourses;
            cout << "Enter Student ID to Edit: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter DOB: ";
            getline(cin, dob);
            cout << "Enter Contact: ";
            getline(cin, contact);
            cout << "Enter CGPA: ";
            cin >> gpa;
            cout << "Enter Completed Courses: ";
            cin >> completedCourses;
            for (auto& student : students) {
                if (student.GetStudentID() == id) {
                    student.EditStudent(id, name, dob, contact, gpa, completedCourses);
                    cout << "Student edited successfully!" << endl;
                    break;
                }
            }
            break;
        }
        case 4: {
            if (dynamic_cast<Admin*>(loggedInUser) == nullptr && dynamic_cast<Teacher*>(loggedInUser) == nullptr) {
                cout << "You do not have permission to add courses!" << endl;
                break;
            }
            int id, credits;
            string name, instructor, description;
            cout << "Enter Course ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Course Name: ";
            getline(cin, name);
            cout << "Enter Instructor Name: ";
            getline(cin, instructor);
            cout << "Enter Credits: ";
            cin >> credits;
            cin.ignore();
            cout << "Enter Description: ";
            getline(cin, description);
            Course newCourse;
            newCourse.AddCourse(id, name, instructor, credits, description);
            courses.push_back(newCourse);
            entities.push_back(&courses.back());
            cout << "Course added successfully!" << endl;
            break;
        }
        case 5: {
            if (dynamic_cast<Admin*>(loggedInUser) == nullptr && dynamic_cast<Teacher*>(loggedInUser) == nullptr) {
                cout << "You do not have permission to edit courses!" << endl;
                break;
            }
            int id, credits;
            string name, instructor, description;
            cout << "Enter Course ID to Edit: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Course Name: ";
            getline(cin, name);
            cout << "Enter Instructor Name: ";
            getline(cin, instructor);
            cout << "Enter Credits: ";
            cin >> credits;
            cin.ignore();
            cout << "Enter Description: ";
            getline(cin, description);
            for (auto& course : courses) {
                if (course.GetCourseID() == id) {
                    course.EditCourse(name, instructor, credits, id, description);
                    cout << "Course edited successfully!" << endl;
                    break;
                }
            }
            break;
        }
        case 6: {
            for (const auto& course : courses) {
                course.DisplayInfo();
            }
            break;
        }
        case 7: {
            int studentID, courseID;
            string date;
            cout << "Enter Student ID: ";
            cin >> studentID;
            cout << "Enter Course ID: ";
            cin >> courseID;
            cout << "Enter Enrollment Date: ";
            cin.ignore();
            getline(cin, date);
            Enrollment newEnrollment;
            newEnrollment.EnrollStudent(studentID, courseID, date);
            enrollments.push_back(newEnrollment);
            entities.push_back(&enrollments.back());
            cout << "Student enrolled successfully!" << endl;
            break;
        }
        case 8: {
            int studentID, courseID;
            cout << "Enter Student ID: ";
            cin >> studentID;
            cout << "Enter Course ID: ";
            cin >> courseID;
            for (auto& enrollment : enrollments) {
                if (enrollment.GetStudentID() == studentID && enrollment.GetCourseID() == courseID) {
                    enrollment.WithdrawStudent();
                    cout << "Student withdrawn successfully!" << endl;
                    break;
                }
            }
            break;
        }
        case 9: {
            int id;
            cout << "Enter Student ID to Search: ";
            cin >> id;
            SearchEntity(id, entities);
            break;
        }
        case 10: {
            int id;
            cout << "Enter Course ID to Search: ";
            cin >> id;
            SearchEntity(id, entities);
            break;
        }
        case 11: {
            if (dynamic_cast<Admin*>(loggedInUser) == nullptr) {
                cout << "You do not have permission to remove students!" << endl;
                break;
            }
            int studentID;
            cout << "Enter Student ID to Remove: ";
            cin >> studentID;
            for (auto& student : students) {
                student.RemoveStudent(studentID, students);
            }
            break;
        }
        case 12: {
            if (dynamic_cast<Admin*>(loggedInUser) == nullptr) {
                cout << "You do not have permission to remove courses!" << endl;
                break;
            }
            int courseID;
            cout << "Enter Course ID to Remove: ";
            cin >> courseID;
            for (auto& course : courses) {
                course.RemoveCourse(courseID, courses);
            }
            break;
        }
        case 13: {
            int studentID, courseID;
            string grade;
            cout << "Enter Student ID: ";
            cin >> studentID;
            cout << "Enter Course ID: ";
            cin >> courseID;
            cout << "Enter Grade: ";
            cin >> grade;
            for (auto& enrollment : enrollments) {
                if (enrollment.GetStudentID() == studentID && enrollment.GetCourseID() == courseID) {
                    enrollment.UpdateGrade(grade);
                    cout << "Grade updated successfully!" << endl;
                    break;
                }
            }
            break;
        }
        case 14: {
            for (const auto& course : courses) {
                course.DisplayInfo();
            }
            break;
        }
        case 15: {
            for (const auto& student : students) {
                student.DisplayInfo();
            }
            break;
        }
        case 16: {
            for (const auto& enrollment : enrollments) {
                enrollment.DisplayInfo();
            }
            break;
        }
        case 17: {
            int studentID;
            cout << "Enter Student ID to Calculate GPA: ";
            cin >> studentID;
            float totalGPA = 0;
            int count = 0;
            for (const auto& enrollment : enrollments) {
                if (enrollment.GetStudentID() == studentID) {
                    for (const auto& student : students) {
                        if (student.GetStudentID() == studentID) {
                            totalGPA += student.GetCGPA();
                            count++;
                        }
                    }
                }
            }
            if (count > 0) {
                float avgGPA = totalGPA / count;
                cout << "Average GPA for Student ID " << studentID << " is: " << avgGPA << endl;
            } else {
                cout << "No enrollments found for Student ID " << studentID << endl;
            }
            break;
        }
        case 18:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 18);

    
    for (auto& pair : users) {
        delete pair.second;
    }

    return 0;
}
