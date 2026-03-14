#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct Student {
    string name;
    int id;
    vector<float> grades;
};

vector<Student> students;

void saveToFile() {
    ofstream file("students.txt");

    for (auto &s : students) {
        file << s.name << " " << s.id << " " << s.grades.size();

        for (float g : s.grades) {
            file << " " << g;
        }

        file << endl;
    }

    file.close();
}

void loadFromFile() {
    ifstream file("students.txt");

    if (!file)
        return;

    students.clear();

    while (!file.eof()) {
        Student s;
        int gradeCount;

        file >> s.name >> s.id >> gradeCount;

        if (file.fail())
            break;

        for (int i = 0; i < gradeCount; i++) {
            float g;
            file >> g;
            s.grades.push_back(g);
        }

        students.push_back(s);
    }

    file.close();
}

void addStudent() {
    Student s;

    cout << "Enter student name: ";
    cin >> s.name;

    cout << "Enter student ID: ";
    cin >> s.id;

    students.push_back(s);

    cout << "Student added successfully!\n";
}

void addGrade() {
    int id;
    float grade;

    cout << "Enter student ID: ";
    cin >> id;

    for (auto &s : students) {
        if (s.id == id) {
            cout << "Enter grade: ";
            cin >> grade;

            s.grades.push_back(grade);

            cout << "Grade added!\n";
            return;
        }
    }

    cout << "Student not found.\n";
}

void displayGrades() {
    for (auto &s : students) {
        cout << "\nName: " << s.name;
        cout << "\nID: " << s.id;
        cout << "\nGrades: ";

        for (float g : s.grades) {
            cout << g << " ";
        }

        cout << endl;
    }
}

void calculateAverage() {
    int id;

    cout << "Enter student ID: ";
    cin >> id;

    for (auto &s : students) {
        if (s.id == id) {

            if (s.grades.empty()) {
                cout << "No grades available.\n";
                return;
            }

            float sum = 0;

            for (float g : s.grades) {
                sum += g;
            }

            cout << "Average grade: " << sum / s.grades.size() << endl;
            return;
        }
    }

    cout << "Student not found.\n";
}

int main() {

    loadFromFile();

    int choice;

    do {
        cout << "\n---- Student Grade Book ----\n";
        cout << "1. Add Student\n";
        cout << "2. Add Grade\n";
        cout << "3. Display Grades\n";
        cout << "4. Calculate Average\n";
        cout << "5. Save and Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            addStudent();
            break;

        case 2:
            addGrade();
            break;

        case 3:
            displayGrades();
            break;

        case 4:
            calculateAverage();
            break;

        case 5:
            saveToFile();
            cout << "Data saved. Exiting program.\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return 0;
}