#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>

using namespace std;

// PERSON CLASS
class Person {
protected:
    int id;
    string name;
    int age;

public:
    // Constructor that checks for reasonable person age
    Person(int personId, string personName, int personAge) {
        if (personId <= 0 || personAge < 0 || personAge > 120) {
            throw invalid_argument("Error: Invalid ID or age range provided.");
        }
        id = personId;
        name = personName;
        age = personAge;
    }

    // Get the ID of the person
    int getId() const { return id; }
    // Get the name of the person
    string getName() const { return name; }
    // Get the age of the person
    int getAge() const { return age; }
};
// PATIENT CLASS
class Patient : public Person {
private:
    string diagnosis;
    double balanceDue;

public:
    Patient(int pId, string pName, int pAge, string pDiagnosis, double pBalance)
        : Person(pId, pName, pAge), diagnosis(pDiagnosis), balanceDue(pBalance) {}

    // Standard non-virtual display function for patients
    void displayPatient() const {
        cout << "[Patient] ID: " << setw(5) << id 
             << " | Name: " << setw(15) << left << name 
             << " | Age: " << setw(3) << age 
             << " | Diagnosis: " << setw(15) << diagnosis 
             << " | Balance: $" << fixed << setprecision(2) << balanceDue << endl;
    }

    double getBalance() const { return balanceDue; }
    void updateBalance(double amount) {
        balanceDue += amount;
        if (balanceDue < 0) balanceDue = 0;
    }
    string getDiagnosis() const { return diagnosis; }
};

class Doctor : public Person {
private:
    string specialization;
    bool isAvailable;

public:
    Doctor(int dId, string dName, int dAge, string dSpec)
        : Person(dId, dName, dAge), specialization(dSpec), isAvailable(true) {}

    // Standard non-virtual display function for doctors
    void displayDoctor() const {
        cout << "[Doctor]  ID: " << setw(5) << id 
             << " | Dr. " << setw(13) << left << name 
             << " | Spec: " << setw(15) << specialization 
             << " | Status: " << (isAvailable ? "Available" : "Busy") << endl;
    }

    bool getAvailability() const { return isAvailable; }
    void setAvailability(bool status) { isAvailable = status; }
    string getSpecialization() const { return specialization; }
};

class Appointment {
private:
    int appointmentId;
    int patientId;
    int doctorId;
    string date;

public:
    Appointment(int apptId, int patId, int docId, string apptDate)
        : appointmentId(apptId), patientId(patId), doctorId(docId), date(apptDate) {}

    void displayAppointment() const {
        cout << "[Appointment #" << appointmentId << "] Patient ID: " << patientId 
             << " scheduled with Doctor ID: " << doctorId 
             << " on Date: " << date << endl;
    }

    int getAppointmentId() const { return appointmentId; }
};