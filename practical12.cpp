#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

struct Employee {
    string id, name, designation;
    float salary;
};

vector<Employee> employees;

void loadEmployees() {
    ifstream file("employee_data.txt");
    if (!file) {
        cout << "No existing data found. Starting fresh.\n";
        return;
    }
    string line;
    employees.clear();
    while (getline(file, line)) {
        stringstream ss(line);
        Employee e;
        getline(ss, e.id, ',');
        getline(ss, e.name, ',');
        getline(ss, e.designation, ',');
        ss >> e.salary;
        employees.push_back(e);
    }
    file.close();
}

void saveEmployees() {
    ofstream file("employee_data.txt");
    for (const auto& e : employees) {
        file << e.id << "," << e.name << "," << e.designation << "," << e.salary << endl;
    }
    file.close();
}

void addEmployee() {
    Employee e;
    cout << "Enter Employee ID: ";
    cin >> e.id;
    cin.ignore(); // Ignore newline character after ID input
    cout << "Enter Name: ";
    getline(cin, e.name);
    cout << "Enter Designation: ";
    getline(cin, e.designation);
    cout << "Enter Salary: ";
    cin >> e.salary;

    employees.push_back(e);
    sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
        return a.id < b.id;
    });
    saveEmployees();
    cout << "Employee information added successfully.\n";
}

void deleteEmployee() {
    string empId;
    cout << "Enter Employee ID to delete: ";
    cin >> empId;

    auto it = remove_if(employees.begin(), employees.end(), [&](const Employee& e) {
        return e.id == empId;
    });

    if (it != employees.end()) {
        employees.erase(it, employees.end());
        saveEmployees();
        cout << "Employee information deleted successfully.\n";
    } else {
        cout << "Employee record not found.\n";
    }
}

void displayEmployee() {
    string empId;
    cout << "Enter Employee ID to search: ";
    cin >> empId;
    bool found = false;

    for (const auto& e : employees) {
        if (e.id == empId) {
            cout << "ID: " << e.id
                 << ", Name: " << e.name
                 << ", Designation: " << e.designation
                 << ", Salary: " << e.salary << endl;
            found = true;
            break;
        }
    }
    if (!found)
        cout << "Employee record not found.\n";
}

int main() {
    loadEmployees();
    int choice;
    do {
        cout << "\n1. Add Employee\n2. Delete Employee\n3. Display Employee\n4. Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addEmployee(); break;
            case 2: deleteEmployee(); break;
            case 3: displayEmployee(); break;
            case 4: cout << "Exiting program.\n"; break;
            default: cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);
    return 0;
}