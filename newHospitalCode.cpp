#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

// CLASS 1: PATIENT

class Patient {
private:
    int id;
    string name;
    int age;
    string phoneNumber;
    string address;
    string diagnosis;
    double billBalance;
    
    string customFeeName;
    double customFeeAmount;

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
        
        // Initialize default custom fee state
        customFeeName = "None Assigned";
        customFeeAmount = 0.0;
    }

    //  function to display complete patient details including custom fees
    void displayPatientDetails() {
        cout << "           PATIENT RECORD CARD            \n";
        cout << " Patient ID   : " << id << endl;
        cout << " Full Name    : " << name << endl;
        cout << " Age          : " << age << " years old" << endl;
        cout << " Phone Number : " << phoneNumber << endl;
        cout << " Home Address : " << address << endl;
        cout << " Diagnosis    : " << diagnosis << endl;
        cout << " Base Bill    : $" << billBalance << endl;
        if (customFeeAmount > 0.0) {
            cout << " Fee Item     : " << customFeeName << " ($" << customFeeAmount << ")\n";
            cout << " Total Balance: $" << (billBalance + customFeeAmount) << endl;
        } else {
            cout << " Fee Item     : None\n";
            cout << " Total Balance: $" << billBalance << endl;
        }
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

    // Function to assign a custom named fee and its cost
    void assignCustomFee(string feeName, double feeCost) {
        if (feeCost < 0.0) {
            throw invalid_argument("Error: Fee cost cannot be a negative value.");
        }
        customFeeName = feeName;
        customFeeAmount = feeCost;
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


// CLASS 2: DOCTOR

class Doctor {
private:
    int id;
    string name;
    string specialization;
    string officeRoom;
    int yearsExperience;
    bool available;

public:
    Doctor(int dId, string dName, string dSpec, string dRoom, int dExp) {
        if (dId <= 0 || dExp < 0) {
            throw invalid_argument("Error: Doctor ID must be positive and experience cannot be negative.");
        }

        id = dId;
        name = dName;
        specialization = dSpec;
        officeRoom = dRoom;
        yearsExperience = dExp;
        available = true;
    }

    void displayDoctorDetails() {
        cout << " Doctor ID    : " << id << endl;
        cout << " Name         : Dr. " << name << endl;
        cout << " Speciality   : " << specialization << endl;
        cout << " Office Room  : " << officeRoom << endl;
        cout << " Experience   : " << yearsExperience << " years" << endl;
        cout << " Status       : " << (available ? "Available for Consultation" : "Currently Busy") << endl;

    }

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

    void setAvailability(bool status) {
        available = status;
    }
};

// CLASS 3: APPOINTMENT

class Appointment {
private:
    int appointmentId;
    int patientId;
    int doctorId;
    string appointmentDate;
    string timeSlot;
    string consultationStatus;

public:
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

    void displayAppointmentInfo() {
        cout << " APPOINTMENT #" << appointmentId << endl;
        cout << " Patient ID   : " << patientId << endl;
        cout << " Doctor ID    : " << doctorId << endl;
        cout << " Date         : " << appointmentDate << endl;
        cout << " Time Slot    : " << timeSlot << endl;
        cout << " Status       : " << consultationStatus << endl;
    }

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

    void setConsultationStatus(string status) {
        consultationStatus = status;
    }
};


// CLASS 4: HOSPITAL SYSTEM

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
    HospitalSystem() {
        patientCount = 0;
        doctorCount = 0;
        appointmentCount = 0;

        doctors[doctorCount++] = new Doctor(101, "Grace", "Diagnostics", "Suite 302", 15);
        doctors[doctorCount++] = new Doctor(102, "Matthew", "General Surgery", "Suite 405", 10);
        doctors[doctorCount++] = new Doctor(103, "Judah", "Neurosurgery", "Suite 108", 20);
    }

    // --- PATIENT MANAGEMENT METHODS ---

    void registerNewPatient(int id, string name, int age, string phone, string addr, string diag, double balance) {
        if (patientCount >= MAX_PATIENTS) {
            throw overflow_error("Error: Patient database has reached maximum capacity (100 records).");
        }

        for (int i = 0; i < patientCount; i++) {
            if (patients[i]->getId() == id) {
                throw invalid_argument("Error: A patient with this identification number already exists.");
            }
        }

        patients[patientCount] = new Patient(id, name, age, phone, addr, diag, balance);
        patientCount++;
        cout << "\nPatient successfully registered in the system database!\n";
    }

    void displayAllPatients() {
        if (patientCount == 0) {
            cout << "\nNo patient records currently stored in the database.\n";
            return;
        }


        cout << "        COMPLETE PATIENT DIRECTORY        \n";
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

    // NEW FUNCTION: Assign a custom named fee to a specific patient
    void addCustomFeeToPatient(int targetId, string feeName, double feeCost) {
        bool found = false;
        for (int i = 0; i < patientCount; i++) {
            if (patients[i]->getId() == targetId) {
                patients[i]->assignCustomFee(feeName, feeCost);
                cout << "\nCustom fee '" << feeName << "' successfully assigned to patient.\n";
                patients[i]->displayPatientDetails();
                found = true;
                break;
            }
        }

        if (!found) {
            throw runtime_error("Error: Target Patient ID could not be found for custom fee assignment.");
        }
    }

    // --- DOCTOR MANAGEMENT METHODS ---

    void registerNewDoctor(int id, string name, string specialization, string room, int experience) {
        if (doctorCount >= MAX_DOCTORS) {
            throw overflow_error("Error: Doctor staff directory has reached maximum capacity (50 records).");
        }

        for (int i = 0; i < doctorCount; i++) {
            if (doctors[i]->getId() == id) {
                throw invalid_argument("Error: A doctor with this identification number already exists.");
            }
        }

        doctors[doctorCount] = new Doctor(id, name, specialization, room, experience);
        doctorCount++;
        cout << "\nNew doctor successfully added to the medical staff directory!\n";
    }

    void displayAllDoctors() {
        cout << "         MEDICAL STAFF DIRECTORY          \n";
        cout << "Total Active Physicians: " << doctorCount << "\n";

        for (int i = 0; i < doctorCount; i++) {
            doctors[i]->displayDoctorDetails();
        }
    }

    // --- APPOINTMENT MANAGEMENT METHODS ---

    void scheduleAppointment(int apptId, int patId, int docId, string date, string time) {
        if (appointmentCount >= MAX_APPOINTMENTS) {
            throw overflow_error("Error: Appointment schedule buffer is full.");
        }

        for (int i = 0; i < appointmentCount; i++) {
            if (appointments[i]->getAppointmentId() == apptId) {
                throw invalid_argument("Error: Appointment ID already exists in the system.");
            }
        }

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

        appointments[appointmentCount] = new Appointment(apptId, patId, docId, date, time);
        appointmentCount++;
        cout << "\nAppointment successfully scheduled and confirmed!\n";
    }

    void displayAllAppointments() {
        if (appointmentCount == 0) {
            cout << "\nNo active appointments currently booked.\n";
            return;
        }

        cout << "       SCHEDULED APPOINTMENTS LOG         \n";
        cout << "Total Booked Appointments: " << appointmentCount << "\n\n";

        for (int i = 0; i < appointmentCount; i++) {
            appointments[i]->displayAppointmentInfo();
        }
    }

    // --- HOSPITAL METRICS & STATISTICS ---

    void displaySystemStatistics() {

        cout << "      HOSPITAL SYSTEM STATUS     \n";
        cout << " Registered Patients   : " << patientCount << " / " << MAX_PATIENTS << endl;
        cout << " Active Physicians     : " << doctorCount << " / " << MAX_DOCTORS << endl;
        cout << " Booked Appointments   : " << appointmentCount << " / " << MAX_APPOINTMENTS << endl;
        cout << " System Status         : ONLINE & OPERATIONAL" << endl;
    }
};


// MAIN FUNCTION & INTERACTIVE MENU LOOP

int main() {
    HospitalSystem hms;
    int menuChoice = 0;
cout << "\n";
    cout << "HOSPITAL MANAGEMENT SYSTEM\n";
    do {;
        cout << "\n\n";
        cout << "MAIN MENU\n";
        cout << "\n";
        cout << " 1. Register New Patient                  \n";
        cout << " 2. View All Patient Records              \n";
        cout << " 3. Search Patient by ID                  \n";
        cout << " 4. Update Patient Billing Balance        \n";
        cout << " 5. View Doctor Staff Directory           \n";
        cout << " 6. Register New Doctor                   \n";
        cout << " 7. Schedule New Appointment              \n";
        cout << " 8. View All Scheduled Appointments       \n";
        cout << " 9. View Hospital System Statistics       \n";
        cout << "10. Add Custom Named Fee to Patient       \n";
        cout << "11. Exit Program                          \n";
        cout << "\n";
        cout << "Enter your selection (1-11): ";

        if (!(cin >> menuChoice)) {
            cout << "\n[INPUT ERROR] Invalid data type entered. Please enter a valid integer number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        try {
            switch (menuChoice) {
                case 1: {
                    int id, age;
                    string name, phone, address, diagnosis;
                    double balance;

                    cout << "\nREGISTER NEW PATIENT\n";
                    cout << "Enter Patient ID (Integer): ";
                    cin >> id;
                    cout << "Enter Full Name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter Age: ";
                    cin >> age;
                    cout << "Enter Phone Number: ";
                    cin.ignore();
                    getline(cin, phone);
                    cout << "Enter Home Address: ";
                    getline(cin, address);
                    cout << "Enter Initial Diagnosis: ";
                    getline(cin, diagnosis);
                    cout << "Enter Initial Bill Balance ($): ";
                    cin >> balance;

                    hms.registerNewPatient(id, name, age, phone, address, diagnosis, balance);
                    break;
                }
                case 2: {
                    hms.displayAllPatients();
                    break;
                }
                case 3: {
                    int searchId;
                    cout << "\nSEARCH PATIENT\n";
                    cout << "Enter Patient ID to locate: ";
                    cin >> searchId;
                    hms.searchPatientById(searchId);
                    break;
                }
                case 4: {
                    int targetId;
                    double amount;
                    cout << "\nUPDATE PATIENT BILLING\n";
                    cout << "Enter Patient ID: ";
                    cin >> targetId;
                    cout << "Enter Amount to Add/Subtract (use negative for payments): ";
                    cin >> amount;
                    hms.updatePatientBilling(targetId, amount);
                    break;
                }
                case 5: {
                    hms.displayAllDoctors();
                    break;
                }
                case 6: {
                    int id, experience;
                    string name, specialization, officeRoom;

                    cout << "\nREGISTER NEW DOCTOR\n";
                    cout << "Enter Doctor ID (Integer): ";
                    cin >> id;
                    cout << "Enter Doctor Last Name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter Specialization (e.g., Pediatrics): ";
                    getline(cin, specialization);
                    cout << "Enter Office Room (e.g., Suite 204): ";
                    getline(cin, officeRoom);
                    cout << "Enter Years of Experience: ";
                    cin >> experience;

                    hms.registerNewDoctor(id, name, specialization, officeRoom, experience);
                    break;
                }
                case 7: {
                    int apptId, patId, docId;
                    string date, timeSlot;

                    cout << "\nSCHEDULE APPOINTMENT\n";
                    cout << "Enter Appointment ID: ";
                    cin >> apptId;
                    cout << "Enter Patient ID: ";
                    cin >> patId;
                    cout << "Enter Doctor ID: ";
                    cin >> docId;
                    cout << "Enter Date (MM/DD/YYYY): ";
                    cin.ignore();
                    getline(cin, date);
                    cout << "Enter Time Slot (e.g., 10:30 AM): ";
                    getline(cin, timeSlot);

                    hms.scheduleAppointment(apptId, patId, docId, date, timeSlot);
                    break;
                }
                case 8: {
                    hms.displayAllAppointments();
                    break;
                }
                case 9: {
                    hms.displaySystemStatistics();
                    break;
                }
                case 10: {
                    int targetId;
                    string feeName;
                    double feeCost;

                    cout << "\nADD EXTREMELY NEEDED FEE\n";
                    cout << "Enter Patient ID: ";
                    cin >> targetId;
                    cout << "Enter Custom Fee Name (e.g., 'Emergency Facility Surcharge'): ";
                    cin.ignore();
                    getline(cin, feeName);
                    cout << "Enter Fee Cost ($): ";
                    cin >> feeCost;

                    hms.addCustomFeeToPatient(targetId, feeName, feeCost);
                    break;
                }
                case 11: {
                    cout << "\nExiting Hospital Management System.\n";
                    break;
                }
                default: {
                    cout << "\nInvalid menu choice selected. Please select a valid option between 1 and 11.\n";
                    break;
                }
            }
        }
        catch (const exception& ex) {
            cout << "\n\n";
            cout << " an exception happened: " << ex.what() << endl;
            cout << "\n";
        }

    } while (menuChoice != 11);

    return 0;
}