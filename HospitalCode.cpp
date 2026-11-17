#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class Patient {
private:
    int id;
    string name;
    int age;
    string phoneNumber;
    string address;
    string diagnosis;
    double billBalance;

public:
    // Constructor with input validation throwing standard exceptions
    Patient(int pId, string pName, int pAge, string pPhone, string pAddr, string pDiag, double pBalance) {
        if (pId <= 0 || pAge < 0 || pAge > 120) {
            throw invalid_argument("Error: Patient ID must be positive and age must be between 0 and 120.");
        }
        
        id = pId;
        name = pName;
        age = pAge;
        phoneNumber = pPhone;
        address = pAddr;
        diagnosis = pDiag;
        billBalance = pBalance;
    }

    // Member function to display complete patient details
    void displayPatientDetails() {
        cout << "\n";
        cout << "PATIENT RECORD CARD\n";
        cout << "\n";
        cout << " Patient ID   : " << id << endl;
        cout << " Full Name    : " << name << endl;
        cout << " Age          : " << age << " years old" << endl;
        cout << " Phone Number : " << phoneNumber << endl;
        cout << " Home Address : " << address << endl;
        cout << " Diagnosis    : " << diagnosis << endl;
        cout << " Bill Balance : $" << billBalance << endl;
        cout << "\n";
    }

    // Getter functions
    int getId() {
        return id;
    }

    string getName() {
        return name;
    }

    int getAge() {
        return age;
    }

    string getPhoneNumber() {
        return phoneNumber;
    }

    string getAddress() {
        return address;
    }

    string getDiagnosis() {
        return diagnosis;
    }

    double getBillBalance() {
        return billBalance;
    }

    // Setter and updater functions
    void setDiagnosis(string newDiag) {
        diagnosis = newDiag;
    }

    void updateBillBalance(double amount) {
        billBalance += amount;
        if (billBalance < 0.0) {
            billBalance = 0.0;
        }
    }
};

class Doctor {
private:
    int id;
    string name;
    string specialization;
    string officeRoom;
    int yearsExperience;
    bool available;

public:
    // Constructor for Doctor class
    Doctor(int dId, string dName, string dSpec, string dRoom, int dExp) {
        if (dId <= 0) {
            throw invalid_argument("Error: Doctor ID must be a positive integer.");
        }

        id = dId;
        name = dName;
        specialization = dSpec;
        officeRoom = dRoom;
        yearsExperience = dExp;
        available = true;
    }

    // function to display doctor profile
    void displayDoctorDetails() {
        cout << "\n";
        cout << " Doctor ID    : " << id << endl;
        cout << " Name         : Dr. " << name << endl;
        cout << " Speciality   : " << specialization << endl;
        cout << " Office Room  : " << officeRoom << endl;
        cout << " Experience   : " << yearsExperience << " years" << endl;
        cout << " Status       : " << (available ? "Available for Consultation" : "Currently Busy") << endl;
        cout << "\n";
    }

    // Getters
    int getId() {
        return id;
    }

    string getName() {
        return name;
    }

    string getSpecialization() {
        return specialization;
    }

    string getOfficeRoom() {
        return officeRoom;
    }

    int getYearsExperience() {
        return yearsExperience;
    }

    bool isAvailable() {
        return available;
    }

    // Setter for availability status
    void setAvailability(bool status) {
        available = status;
    }
};

class Appointment {
private:
    int appointmentId;
    int patientId;
    int doctorId;
    string appointmentDate;
    string timeSlot;
    string consultationStatus;

public:
    // Constructor for Appointment class
    Appointment(int aId, int pId, int dId, string aDate, string aTime) {
        if (aId <= 0) {
            throw invalid_argument("Error: Appointment ID must be greater than zero.");
        }

        appointmentId = aId;
        patientId = pId;
        doctorId = dId;
        appointmentDate = aDate;
        timeSlot = aTime;
        consultationStatus = "Scheduled";
    }

    //  function to display appointment record
    void displayAppointmentInfo() {
        cout << "\n";
        cout << " APPOINTMENT #" << appointmentId << endl;
        cout << "\n";
        cout << " Patient ID   : " << patientId << endl;
        cout << " Doctor ID    : " << doctorId << endl;
        cout << " Date         : " << appointmentDate << endl;
        cout << " Time Slot    : " << timeSlot << endl;
        cout << " Status       : " << consultationStatus << endl;
        cout << "\n";
    }

    // Getters
    int getAppointmentId() {
        return appointmentId;
    }

    int getPatientId() {
        return patientId;
    }

    int getDoctorId() {
        return doctorId;
    }

    string getAppointmentDate() {
        return appointmentDate;
    }

    string getTimeSlot() {
        return timeSlot;
    }

    string getConsultationStatus() {
        return consultationStatus;
    }

    // Setter for status update
    void setConsultationStatus(string status) {
        consultationStatus = status;
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