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