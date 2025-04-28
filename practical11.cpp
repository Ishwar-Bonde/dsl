#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
struct Student
{
    int id;
    string name;
    int age;
    string course;
    void inputStudent()
    {
        cout << "Enter student ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter student name: ";
        getline(cin, name);
        cout << "Enter student age: ";
        cin >> age;
        cin.ignore();
        cout << "Enter student course: ";
        getline(cin, course);
    }
    void displayStudent()
    {
        cout << "ID: " << id << ", Name: " << name << ", Age: " << age << ", Course: " << course
             << endl;
    }
};
class StudentInfoSystem
{
private:
    string filename;

public:
    StudentInfoSystem(const string &file) : filename(file) {}
    void addStudent()
    {
        Student student;
        student.inputStudent();
        ofstream fileOut(filename, ios::app);
        if (fileOut.is_open())
        {
            fileOut << student.id << "," << student.name << "," << student.age << "," << student.course << endl;
            fileOut.close();
            cout << "Student added successfully!" << endl;
        }
        else
        {
            cout << "Unable to open file for adding student." << endl;
        }
    }
    void deleteStudent()
    {
        int id;
        cout << "Enter student ID to delete: ";
        cin >> id;
        ifstream fileIn(filename);
        if (!fileIn.is_open())
        {
            cout << "Unable to open file." << endl;
            return;
        }
        vector<Student> students;
        string line;
        bool found = false;
        while (getline(fileIn, line))
        {
            Student student;
            size_t pos = 0;
            pos = line.find(",");
            student.id = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find(",");
            student.name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(",");
            student.age = stoi(line.substr(0, pos));
            student.course = line.substr(pos + 1);
            if (student.id != id)
            {
                students.push_back(student);
            }
            else
            {
                found = true;
            }
        }
        fileIn.close();
        if (!found)
        {
            cout << "Student with ID " << id << " not found!" << endl;
            return;
        }
        ofstream fileOut(filename);
        for (const auto &student : students)
        {
            fileOut << student.id << "," << student.name << "," << student.age << "," << student.course << endl;
        }
        fileOut.close();
        cout << "Student deleted successfully!" << endl;
    }
    void displayStudents()
    {
        ifstream fileIn(filename);
        if (!fileIn.is_open())
        {
            cout << "Unable to open file." << endl;
            return;
        }
        string line;
        while (getline(fileIn, line))
        {
            Student student;
            size_t pos = 0;
            pos = line.find(",");
            student.id = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find(",");
            student.name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(",");
            student.age = stoi(line.substr(0, pos));
            student.course = line.substr(pos + 1);
            student.displayStudent();
        }
        fileIn.close();
    }
};
int main()
{
    StudentInfoSystem system("students.txt");
    int choice;
    do
    {
        cout << "\n--- Student Information System ---\n";
        cout << "1. Add student\n";
        cout << "2. Delete student\n";
        cout << "3. Display all students\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            system.addStudent();
            break;
        case 2:
            system.deleteStudent();
            break;
        case 3:
            system.displayStudents();
            break;
        case 4:
            cout << "Exiting the system.\n";
            break;
        default:
            cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 4);
    return 0;
}
