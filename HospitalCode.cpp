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