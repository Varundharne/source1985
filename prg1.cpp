#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Student {
private:
    int rollNumber;
    string name;
    string course;
    float marks;

public:
    Student() {}
    Student(int roll, string n, string c, float m) {
        rollNumber = roll;
        name = n;
        course = c;
        marks = m;
    }

    void display() const {
        cout << left << setw(10) << rollNumber
             << setw(20) << name
             << setw(15) << course
             << setw(10) << marks << endl;
    }

    int getRollNumber() const {
        return rollNumber;
    }

    void update(string n, string c, float m) {
        name = n;
        course = c;
        marks = m;
    }

    string toFileString() const {
        return to_string(rollNumber) + "," + name + "," + course + "," + to_string(marks);
    }

    static Student fromFileString(const string &line) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);

        int roll = stoi(line.substr(0, pos1));
        string n = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string c = line.substr(pos2 + 1, pos3 - pos2 - 1);
        float m = stof(line.substr(pos3 + 1));

        return Student(roll, n, c, m);
    }
};

class StudentManagementSystem {
private:
    vector<Student> students;
    string filename;

public:
    StudentManagementSystem(const string &file) : filename(file) {
        loadFromFile();
    }

    void addStudent() {
        int roll;
        string name, course;
        float marks;

        cout << "Enter Roll Number: ";
        cin >> roll;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Course: ";
        getline(cin, course);
        cout << "Enter Marks: ";
        cin >> marks;

        students.push_back(Student(roll, name, course, marks));
        cout << "Student added successfully!\n";
    }

    void displayAll() const {
        if (students.empty()) {
            cout << "No records to display.\n";
            return;
        }

        cout << left << setw(10) << "Roll No"
             << setw(20) << "Name"
             << setw(15) << "Course"
             << setw(10) << "Marks" << endl;
        cout << string(55, '-') << endl;

        for (const auto &s : students) {
            s.display();
        }
    }

    void searchStudent() const {
        int roll;
        cout << "Enter Roll Number to search: ";
        cin >> roll;

        for (const auto &s : students) {
            if (s.getRollNumber() == roll) {
                cout << "Student found:\n";
                s.display();
                return;
            }
        }
        cout << "Student not found.\n";
    }

    void deleteStudent() {
        int roll;
        cout << "Enter Roll Number to delete: ";
        cin >> roll;

        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->getRollNumber() == roll) {
                students.erase(it);
                cout << "Student deleted successfully.\n";
                return;
            }
        }
        cout << "Student not found.\n";
    }

    void updateStudent() {
        int roll;
        string name, course;
        float marks;

        cout << "Enter Roll Number to update: ";
        cin >> roll;
        cin.ignore();

        for (auto &s : students) {
            if (s.getRollNumber() == roll) {
                cout << "Enter New Name: ";
                getline(cin, name);
                cout << "Enter New Course: ";
                getline(cin, course);
                cout << "Enter New Marks: ";
                cin >> marks;

                s.update(name, course, marks);
                cout << "Student updated successfully.\n";
                return;
            }
        }
        cout << "Student not found.\n";
    }

    void saveToFile() {
        ofstream outFile(filename);
        for (const auto &s : students) {
            outFile << s.toFileString() << endl;
        }
        outFile.close();
        cout << "Data saved to file.\n";
    }

    void loadFromFile() {
        ifstream inFile(filename);
        string line;
        while (getline(inFile, line)) {
            students.push_back(Student::fromFileString(line));
        }
        inFile.close();
    }
};

int main() {
    StudentManagementSystem sms("students.txt");
    int choice;

    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: sms.addStudent(); break;
            case 2: sms.displayAll(); break;
            case 3: sms.searchStudent(); break;
            case 4: sms.updateStudent(); break;
            case 5: sms.deleteStudent(); break;
            case 6: sms.saveToFile(); cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 6);

    return 0;
}
