#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Employee {
public:
    int id;
    string name;
    string department;

    Employee(int id, string name, string department)
        : id(id), name(name), department(department) {}

    void display() const {
        cout << "ID: " << id << ", Name: " << name << ", Department: " << department << "<br/>";
    }
};

class EmployeeManagementSystem {
private:
    vector<Employee> employees;

public:
    void addEmployee(int id, const string& name, const string& department) {
        employees.emplace_back(id, name, department);
    }

    void listEmployees() const {
        if (employees.empty()) {
            cout << "No employees to display.<br/>";
            return;
        }

        cout << "List of Employees:<br/>";
        for (const auto& emp : employees) {
            emp.display();
        }
    }

    bool searchEmployee(int id) const {
        for (const auto& emp : employees) {
            if (emp.id == id) {
                emp.display();
                return true;
            }
        }
        cout << "Employee not found.<br/>";
        return false;
    }
};

int main() {
    EmployeeManagementSystem ems;

    // For demo purposes, we add some employees
    ems.addEmployee(1, "John Doe", "HR");
    ems.addEmployee(2, "Jane Smith", "IT");

    cout << "Content-type: text/html\n\n";
    cout << "<html><body>";

    const char* requestMethod = getenv("REQUEST_METHOD");
    if (requestMethod && strcmp(requestMethod, "POST") == 0) {
        // Handle POST request (add employee)
        string contentLengthStr = getenv("CONTENT_LENGTH");
        int contentLength = stoi(contentLengthStr);
        char* postData = new char[contentLength + 1];
        cin.read(postData, contentLength);
        postData[contentLength] = '\0';

        // Parse POST data (e.g., id=1&name=John%20Doe&department=HR)
        string postStr(postData);
        delete[] postData;

        int id = 0;
        string name, department;
        size_t idPos = postStr.find("id=");
        size_t namePos = postStr.find("name=");
        size_t deptPos = postStr.find("department=");

        if (idPos != string::npos) {
            id = stoi(postStr.substr(idPos + 3, postStr.find('&', idPos) - idPos - 3));
        }
        if (namePos != string::npos) {
            name = postStr.substr(namePos + 5, postStr.find('&', namePos) - namePos - 5);
        }
        if (deptPos != string::npos) {
            department = postStr.substr(deptPos + 11);
        }

        ems.addEmployee(id, name, department);
        cout << "Employee added successfully.<br/>";
    }

    // Display employees
    ems.listEmployees();

    cout << "</body></html>";

    return 0;
}
