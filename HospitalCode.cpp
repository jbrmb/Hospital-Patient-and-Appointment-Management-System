#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class Patient {
private:
    int id;
    string name;
    int age;
    string diagnosis;
    double billBalance;

public:
    // Constructor
    Patient(int pId, string pName, int pAge, string pDiag, double pBalance) {
        if (pId <= 0 || pAge < 0) {
            throw invalid_argument("Invalid ID or age entered for patient");
        }
        id = pId;
        name = pName;
        age = pAge;
        diagnosis = pDiag;
        billBalance = pBalance;
    }

// function to display patient details
    void display() {
        cout << "Patient ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Diagnosis: " << diagnosis << endl;
        cout << "Bill Balance: $" << billBalance << endl;
        cout << "--" << endl;
    }

    int getId() {
        return id;
    }
};

class Doctor {
private:
    int id;
    string name;
    string specialization;
    bool available;

public:
    // Constructor for creating a doctor
    Doctor(int dId, string dName, string dSpec) {
        id = dId;
        name = dName;
        specialization = dSpec;
        available = true;
    }

    // function to display doctor details
    void display() {
        cout << "Doctor ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Specialization: " << specialization << endl;
        cout << "Status: " << (available ? "Available" : "Busy") << endl;
        cout << "--" << endl;
    }

    int getId() {
        return id;
    }
};

class Appointment {
private:
    int appointmentId;
    int patientId;
    int doctorId;
    string date;

public:
    // Constructor
    Appointment(int aId, int pId, int dId, string aDate) {
        appointmentId = aId;
        patientId = pId;
        doctorId = dId;
        date = aDate;
    }

    void display() {
        cout << "Appointment ID: " << appointmentId 
             << " | Patient ID: " << patientId 
             << " | Doctor ID: " << doctorId 
             << " | Date: " << date << endl;
    }
};

class HospitalSystem {
private:
    // Arrays and Pointers
    Patient* patients[50];
    int patientCount;

    Doctor* doctors[20];
    int doctorCount;

    Appointment* appointments[50];
    int appointmentCount;

    public:
    // Constructor initializes counts and adds default doctors
    HospitalSystem() {
        patientCount = 0;
        doctorCount = 0;
        appointmentCount = 0;

        // Pre-load a couple of doctors using pointers
        doctors[doctorCount++] = new Doctor(101, "Judah", "Cardiology");
        doctors[doctorCount++] = new Doctor(102, "Grace", "Pediatrics");
    }

    // Add Patient function with exception handling
    void addPatient(int id, string name, int age, string diag, double balance) {
        if (patientCount >= 50) {
            throw overflow_error("Patient array is full!");
        }

        // Check for duplicate ID using a loop
        for (int i = 0; i < patientCount; i++) {
            if (patients[i]->getId() == id) {
                throw invalid_argument("A patient with this ID already exists!");
            }
        }

        patients[patientCount] = new Patient(id, name, age, diag, balance);
        patientCount++;
        cout << "Patient added successfully!\n";
    }

// Show all patients using a loop
    void listPatients() {
        if (patientCount == 0) {
            cout << "No patients found in the system\n";
            return;
        }
        cout << "\nPATIENT LIST\n";
        for (int i = 0; i < patientCount; i++) {
            patients[i]->display();
        }
    }

    // Show all doctors using a loop
    void listDoctors() {
        cout << "\nDOCTOR LIST\n";
        for (int i = 0; i < doctorCount; i++) {
            doctors[i]->display();
        }
    }

    // Schedule appointment with validation
    void bookAppointment(int aId, int pId, int dId, string date) {
        // Verify patient exists using pointer check
        bool patientFound = false;
        for (int i = 0; i < patientCount; i++) {
            if (patients[i]->getId() == pId) {
                patientFound = true;
                break;
            }
        }
        if (!patientFound) {
            throw runtime_error("Error: Patient ID not found");
        }

        // Verify doctor exists
        bool doctorFound = false;
        for (int i = 0; i < doctorCount; i++) {
            if (doctors[i]->getId() == dId) {
                doctorFound = true;
                break;
            }
        }
        if (!doctorFound) {
            throw runtime_error("Error: Doctor ID not found");
        }

        appointments[appointmentCount] = new Appointment(aId, pId, dId, date);
        appointmentCount++;
        cout << "Appointment booked successfully\n";
    }

    void listAppointments() {
        if (appointmentCount == 0) {
            cout << "No appointments scheduled\n";
            return;
        }
        cout << "\nAPPOINTMENTS\n";
        for (int i = 0; i < appointmentCount; i++) {
            appointments[i]->display();
        }
    }
};

int main() {
    HospitalSystem system;
    int choice = 0;

    cout << "Welcome to the Hospital Management System\n";

    do {
        cout << "\nMenu:\n";
        cout << "1. Add New Patient\n";
        cout << "2. View All Patients\n";
        cout << "3. View All Doctors\n";
        cout << "4. Book Appointment\n";
        cout << "5. View Appointments\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        // Basic input check
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        // exception handling
        try {
            if (choice == 1) {
                int id, age;
                string name, diag;
                double balance;

                cout << "Enter Patient ID: ";
                cin >> id;
                cout << "Enter Name: ";
                cin >> name;
                cout << "Enter Age: ";
                cin >> age;
                cout << "Enter Diagnosis: ";
                cin >> diag;
                cout << "Enter Balance Due: ";
                cin >> balance;

                system.addPatient(id, name, age, diag, balance);
            }
            else if (choice == 2) {
                system.listPatients();
            }
            else if (choice == 3) {
                system.listDoctors();
            }
            else if (choice == 4) {
                int aId, pId, dId;
                string date;

                cout << "Enter Appointment ID: ";
                cin >> aId;
                cout << "Enter Patient ID: ";
                cin >> pId;
                cout << "Enter Doctor ID: ";
                cin >> dId;
                cout << "Enter Date (MM/DD/YYYY): ";
                cin >> date;

                system.bookAppointment(aId, pId, dId, date);
            }
            else if (choice == 5) {
                system.listAppointments();
            }
            else if (choice == 6) {
                cout << "Exiting program.\n";
            }
            else {
                cout << "Invalid choice. Please select between 1 and 6.\n";
            }
        }
        catch (exception& e) {
            cout << "EXCEPTION CAUGHT: " << e.what() << endl;
        }

    } while (choice != 6);

    return 0;
}