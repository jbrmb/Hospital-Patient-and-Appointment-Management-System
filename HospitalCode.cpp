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
    
    static const int MAX_PATIENTS = 100;
    static const int MAX_DOCTORS = 50;
    static const int MAX_APPOINTMENTS = 100;

    Patient* patients[MAX_PATIENTS];
    int patientCount;

    Doctor* doctors[MAX_DOCTORS];
    int doctorCount;

    Appointment* appointments[MAX_APPOINTMENTS];
    int appointmentCount;

public:
    // Constructor to track amount of people. Also adding doctors in myself
    HospitalSystem() {
        patientCount = 0;
        doctorCount = 0;
        appointmentCount = 0;

        // list of already added doctors
        doctors[doctorCount++] = new Doctor(101, "Judah", "Cardiology", "Suite 302", 15);
        doctors[doctorCount++] = new Doctor(102, "Grace", "Physiology", "Suite 405", 10);
        doctors[doctorCount++] = new Doctor(103, "Matthew", "Morale Support", "Suite 108", 20);
    }

    
    // PATIENT MANAGEMENT

    void registerNewPatient(int id, string name, int age, string phone, string addr, string diag, double balance) {
        // Check capacity limit
        if (patientCount >= MAX_PATIENTS) {
            throw overflow_error("Error: Patient database has reached maximum capacity (100 records).");
        }

        // Check for duplicate patient IDs using a loop
        for (int i = 0; i < patientCount; i++) {
            if (patients[i]->getId() == id) {
                throw invalid_argument("Error: A patient with this identification number already exists.");
            }
        }

        // add new patient into array
        patients[patientCount] = new Patient(id, name, age, phone, addr, diag, balance);
        patientCount++;
        cout << "\nPatient successfully registered in the system database!\n";
    }

    void displayAllPatients() {
        if (patientCount == 0) {
            cout << "\nNo patient records currently stored in the database.\n";
            return;
        }

        cout << "\n\n";
        cout << "COMPLETE PATIENT DIRECTORY\n";
        cout << "\n";
        cout << "Total Registered Patients: " << patientCount << "\n\n";

        for (int i = 0; i < patientCount; i++) {
            patients[i]->displayPatientDetails();
        }
    }

    void searchPatientById(int searchId) {
        bool found = false;
        for (int i = 0; i < patientCount; i++) {
            if (patients[i]->getId() == searchId) {
                cout << "\nPatient record located:\n";
                patients[i]->displayPatientDetails();
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "\nNo patient record matched ID: " << searchId << "\n";
        }
    }

    void updatePatientBilling(int targetId, double amountToAdd) {
        bool found = false;
        for (int i = 0; i < patientCount; i++) {
            if (patients[i]->getId() == targetId) {
                patients[i]->updateBillBalance(amountToAdd);
                cout << "\nPatient billing balance updated successfully.\n";
                patients[i]->displayPatientDetails();
                found = true;
                break;
            }
        }

        if (!found) {
            throw runtime_error("Error: Target Patient ID could not be found for billing update.");
        }
    }

    void registerNewDoctor(int id, string name, string specialization, string room, int experience) {
        if (doctorCount >= MAX_DOCTORS) {
            throw overflow_error("Error: Doctor staff directory has reached maximum capacity (50 records).");
        }

        // Check for duplicate doctor IDs using a standard loop
        for (int i = 0; i < doctorCount; i++) {
            if (doctors[i]->getId() == id) {
                throw invalid_argument("Error: A doctor with this identification number already exists.");
            }
        }

        // add new doctor to array
        doctors[doctorCount] = new Doctor(id, name, specialization, room, experience);
        doctorCount++;
        cout << "\nNew doctor successfully added to the medical staff directory!\n";
    }


    void displayAllDoctors() {
        cout << "\n\n";
        cout << "MEDICAL STAFF DIRECTORY\n";
        cout << "\n";
        cout << "Total Active Physicians: " << doctorCount << "\n";

        for (int i = 0; i < doctorCount; i++) {
            doctors[i]->displayDoctorDetails();
        }
    }

    // APPOINTMENT MANAGEMENT METHOD

    void scheduleAppointment(int apptId, int patId, int docId, string date, string time) {
        if (appointmentCount >= MAX_APPOINTMENTS) {
            throw overflow_error("Error: Appointment schedule buffer is full.");
        }

        // Verify that the appointment ID is unique
        for (int i = 0; i < appointmentCount; i++) {
            if (appointments[i]->getAppointmentId() == apptId) {
                throw invalid_argument("Error: Appointment ID already exists in the system.");
            }
        }

        // Validate that the Patient exists
        bool patientExists = false;
        for (int i = 0; i < patientCount; i++) {
            if (patients[i]->getId() == patId) {
                patientExists = true;
                break;
            }
        }
        if (!patientExists) {
            throw runtime_error("Error: Patient ID not found. Please register the patient first.");
        }

        // Validate that the Doctor exists
        bool doctorExists = false;
        for (int i = 0; i < doctorCount; i++) {
            if (doctors[i]->getId() == docId) {
                doctorExists = true;
                break;
            }
        }
        if (!doctorExists) {
            throw runtime_error("Error: Doctor ID not found in the staff directory.");
        }

        // Create appintment
        appointments[appointmentCount] = new Appointment(apptId, patId, docId, date, time);
        appointmentCount++;
        cout << "\n[SUCCESS] Appointment successfully scheduled and confirmed!\n";
    }

    void displayAllAppointments() {
        if (appointmentCount == 0) {
            cout << "\n[NOTIFICATION] No active appointments currently booked.\n";
            return;
        }

        cout << "\n\n";
        cout << "SCHEDULED APPOINTMENTS LOG\n";
        cout << "\n";
        cout << "Total Booked Appointments: " << appointmentCount << "\n\n";

        for (int i = 0; i < appointmentCount; i++) {
            appointments[i]->displayAppointmentInfo();
        }
    }

    // HOSPITAL STATS

    void displaySystemStatistics() {
        cout << "\n\n";
        cout << "HOSPITAL SYSTEM STATUS REPORT\n";
        cout << "\n";
        cout << " Registered Patients   : " << patientCount << " / " << MAX_PATIENTS << endl;
        cout << " Active Physicians     : " << doctorCount << " / " << MAX_DOCTORS << endl;
        cout << " Booked Appointments   : " << appointmentCount << " / " << MAX_APPOINTMENTS << endl;
        cout << " System Status         : ONLINE & OPERATIONAL" << endl;
        cout << "\n";
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

        // input check
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