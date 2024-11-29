#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Employee {
    char name[30];
    char id[5];
    char designation[10];
    int age;
    int salary;
    char experience[20];
    Employee* next;
};

class EmployeeManagement {
private:
    Employee* head;

public:
    EmployeeManagement() {
        head = NULL;
        loadFromFile();
    }

    ~EmployeeManagement() {
        saveToFile();
    }

    void menu();
    void insert();
    void display();
    void modify();
    void search();
    void deleted();
    void loadFromFile();
    void saveToFile();
    void waitForEnter();
};

void EmployeeManagement::waitForEnter() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void EmployeeManagement::loadFromFile() {
    ifstream file("Employee_Record.txt");
    if (!file) {
        cout << "No existing records found. Starting fresh.\n";
        return;
    }
    while (file) {
        Employee* newEmployee = new Employee();
        file >> newEmployee->name >> newEmployee->id >> newEmployee->designation
             >> newEmployee->age >> newEmployee->salary >> newEmployee->experience;
        if (file.eof()) {
            delete newEmployee;
            break;
        }
        newEmployee->next = head;
        head = newEmployee;
    }
    file.close();
}

void EmployeeManagement::saveToFile() {
    ofstream file("Employee_Record.txt");
    Employee* temp = head;
    while (temp != NULL) {
        file << temp->name << " " << temp->id << " " << temp->designation << " "
             << temp->age << " " << temp->salary << " " << temp->experience << "\n";
        temp = temp->next;
    }
    file.close();
}

void EmployeeManagement::menu() {
    while (true) {
        int choice;
        system("cls");
        cout << "\n\tEmployee Management System\n";
        cout << "-----------------------------------------------\n";
        cout << "1. Add New Employee Record\n";
        cout << "2. Display All Employee Records\n";
        cout << "3. Modify Employee Record\n";
        cout << "4. Search Employee Record\n";
        cout << "5. Delete Employee Record\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: insert(); break;
            case 2: display(); break;
            case 3: modify(); break;
            case 4: search(); break;
            case 5: deleted(); break;
            case 6: return;
            default: cout << "Invalid choice. Please try again.\n";
        }
        waitForEnter();
    }
}

void EmployeeManagement::insert() {
    Employee* newEmployee = new Employee();
    cout << "\nEnter Employee Name: "; cin >> newEmployee->name;
    cout << "Enter Employee ID (max 4 characters): "; cin >> newEmployee->id;
    cout << "Enter Designation: "; cin >> newEmployee->designation;
    cout << "Enter Age: "; cin >> newEmployee->age;
    cout << "Enter Salary: "; cin >> newEmployee->salary;
    cout << "Enter Experience: "; cin >> newEmployee->experience;
    newEmployee->next = head;
    head = newEmployee;
    cout << "Employee record added successfully.\n";
    saveToFile();
}

void EmployeeManagement::display() {
    if (head == NULL) {
        cout << "No employee records found.\n";
        return;
    }
    Employee* temp = head;
    cout << "\nEmployee Records:\n";
    cout << "-------------------------------------------------------------\n";
    cout << "Name\tID\tDesignation\tAge\tSalary\tExperience\n";
    cout << "-------------------------------------------------------------\n";
    while (temp != NULL) {
        cout << temp->name << "\t" << temp->id << "\t" << temp->designation
             << "\t" << temp->age << "\t" << temp->salary << "\t" << temp->experience << "\n";
        temp = temp->next;
    }
}

void EmployeeManagement::modify() {
    char searchId[5];
    cout << "\nEnter Employee ID to modify: ";
    cin >> searchId;

    Employee* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->id, searchId) == 0) {
            cout << "Enter new details:\n";
            cout << "Name: "; cin >> temp->name;
            cout << "Designation: "; cin >> temp->designation;
            cout << "Age: "; cin >> temp->age;
            cout << "Salary: "; cin >> temp->salary;
            cout << "Experience: "; cin >> temp->experience;
            cout << "Record updated successfully.\n";
            saveToFile();
            return;
        }
        temp = temp->next;
    }
    cout << "Employee ID not found.\n";
}

void EmployeeManagement::search() {
    char searchId[5];
    cout << "\nEnter Employee ID to search: ";
    cin >> searchId;

    Employee* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->id, searchId) == 0) {
            cout << "\nEmployee Found:\n";
            cout << "Name: " << temp->name << "\nID: " << temp->id
                 << "\nDesignation: " << temp->designation << "\nAge: " << temp->age
                 << "\nSalary: " << temp->salary << "\nExperience: " << temp->experience << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Employee ID not found.\n";
}

void EmployeeManagement::deleted() {
    char searchId[5];
    cout << "\nEnter Employee ID to delete: ";
    cin >> searchId;

    Employee* temp = head;
    Employee* prev = NULL;

    while (temp != NULL) {
        if (strcmp(temp->id, searchId) == 0) {
            if (prev == NULL) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }
            delete temp;
            cout << "Employee record deleted successfully.\n";
            saveToFile();
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    cout << "Employee ID not found.\n";
}

int main() {
    EmployeeManagement system;
    system.menu();
    return 0;
}

