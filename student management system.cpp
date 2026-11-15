#include <iostream>
#include <fstream>
using namespace std;

class Student {
    int roll;
    char name[30];
    float marks;

public:
    void input() {
        cout << "Enter Roll No: ";
        cin >> roll;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() {
        cout << roll << "\t" << name << "\t" << marks << endl;
    }

    int getRoll() {
        return roll;
    }

    void save() {
        ofstream file("students.dat", ios::binary | ios::app);
        file.write((char*)this, sizeof(Student));
        file.close();
    }

    static void displayAll() {
        Student s;
        ifstream file("students.dat", ios::binary);

        cout << "\nRoll\tName\tMarks\n";
        while (file.read((char*)&s, sizeof(Student))) {
            s.display();
        }

        file.close();
    }

    static void searchStudent(int r) {
        Student s;
        ifstream file("students.dat", ios::binary);
        bool found = false;

        while (file.read((char*)&s, sizeof(Student))) {
            if (s.getRoll() == r) {
                s.display();
                found = true;
                break;
            }
        }

        if (!found)
            cout << "Student not found!\n";

        file.close();
    }
};

int main() {
    Student s;
    int choice, roll;

    do {
        cout << "\n===== STUDENT RECORD SYSTEM =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display All\n";
        cout << "3. Search Student\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            s.input();
            s.save();
            cout << "Record saved!\n";
        }
        else if (choice == 2) {
            Student::displayAll();
        }
        else if (choice == 3) {
            cout << "Enter Roll No: ";
            cin >> roll;
            Student::searchStudent(roll);
        }
        else if (choice == 4) {
            cout << "Program closed.\n";
        }
        else {
            cout << "Invalid choice!\n";
        }

    } while (choice != 4);

    return 0;
}
