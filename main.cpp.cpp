#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// ---------- PATIENT ----------
class Patient
{
public:
    int patientId;
    string name;
    string age;
    string phone;

    Patient()
    {
        patientId = 0;
    }

    Patient(int id, string n, string a, string p)
    {
        patientId = id;
        name = n;
        age = a;
        phone = p;
    }

    virtual void display()
    {
        cout << "Patient ID: " << patientId << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Phone: " << phone << endl;
    }

    virtual ~Patient() {}
};


// ---------- DENTIST ----------
class Dentist : public Patient
{
public:
    string dentistId;
    string specialization;

    Dentist()
    {
        dentistId = "";
        specialization = "";
    }

    Dentist(string id, string s)
    {
        dentistId = id;
        specialization = s;
    }

    void display() override
    {
        cout << "Dentist ID: " << dentistId << endl;
        cout << "Specialization: " << specialization << endl;
    }

    ~Dentist() {}
};


// ---------- APPOINTMENT ----------
class Appointment
{
public:
    int appointmentId;
    int patientId;
    string dentistId;
    string date;

    Appointment()
    {
        appointmentId = 0;
    }

    void book()
    {
        cout << "Appointment booked successfully." << endl;
    }

    void display()
    {
        cout << "Appointment ID: " << appointmentId << endl;
        cout << "Patient ID: " << patientId << endl;
        cout << "Dentist ID: " << dentistId << endl;
        cout << "Date: " << date << endl;
    }

    ~Appointment() {}
};


// ---------- TREATMENT ----------
class Treatment
{
public:
    int treatmentId;
    int appointmentId;
    string description;
    double cost;

    Treatment()
    {
        treatmentId = 0;
        cost = 0;
    }

    void calculate()
    {
        cout << "Treatment cost: " << cost << endl;
    }

    void display()
    {
        cout << "Treatment ID: " << treatmentId << endl;
        cout << "Description: " << description << endl;
        cout << "Cost: " << cost << endl;
    }

    ~Treatment() {}
};


// ---------- BILL ----------
class Bill
{
public:
    int billId;
    int patientId;
    double paid;

    Bill()
    {
        billId = 0;
        paid = 0;
    }

    void calculateTotal(double cost)
    {
        paid = cost;
    }

    void printBill()
    {
        cout << "Bill ID: " << billId << endl;
        cout << "Patient ID: " << patientId << endl;
        cout << "Total Bill: " << paid << endl;
    }

    ~Bill() {}
};


// ---------- FILE MANAGER ----------
class FileManager
{
public:
    string fileName;

    FileManager()
    {
        fileName = "dental_records.txt";
    }

    void save(Patient* p, int count)
    {
        ofstream file(fileName);

        for (int i = 0; i < count; i++)
        {
            file << p[i].patientId << " "
                 << p[i].name << " "
                 << p[i].age << " "
                 << p[i].phone << endl;
        }

        file.close();

        cout << "Records saved." << endl;
    }

    int load(Patient* p, int capacity)
    {
        ifstream file(fileName);

        if (!file)
        {
            cout << "No file found." << endl;
            return 0;
        }

        int loaded = 0;

        while (loaded < capacity &&
            file >> p[loaded].patientId
                >> p[loaded].name
                >> p[loaded].age
                >> p[loaded].phone)
        {
            loaded++;
        }

        file.close();

        cout << "Records loaded successfully." << endl;

        return loaded;
    }

    ~FileManager() {}
};


// ---------- SYSTEM ----------
class System
{
private:
    Patient* patients;
    int count;
    FileManager file;

public:

    System()
    {
        count = 0;

        // Dynamic Memory
        patients = new Patient[10];
    }

    void addRecord()
    {
        cout << "Enter Patient ID: ";
        cin >> patients[count].patientId;

        cout << "Enter Name: ";
        cin >> patients[count].name;

        cout << "Enter Age: ";
        cin >> patients[count].age;

        cout << "Enter Phone: ";
        cin >> patients[count].phone;

        count++;

        cout << "Record added successfully." << endl;
    }

    void displayRecords()
    {
        for (int i = 0; i < count; i++)
        {
            cout << "\nPatient " << i + 1 << endl;
            patients[i].display();
        }
    }

    void searchRecord()
    {
        int id;

        cout << "Enter Patient ID: ";
        cin >> id;

        for (int i = 0; i < count; i++)
        {
            if (patients[i].patientId == id)
            {
                patients[i].display();
                return;
            }
        }

        cout << "Record not found." << endl;
    }

    void updateRecord()
    {
        int id;

        cout << "Enter Patient ID: ";
        cin >> id;

        for (int i = 0; i < count; i++)
        {
            if (patients[i].patientId == id)
            {
                cout << "Enter New Name: ";
                cin >> patients[i].name;

                cout << "Enter New Age: ";
                cin >> patients[i].age;

                cout << "Enter New Phone: ";
                cin >> patients[i].phone;

                cout << "Record updated." << endl;
                return;
            }
        }

        cout << "Record not found." << endl;
    }

    void deleteRecord()
    {
        int id;

        cout << "Enter Patient ID: ";
        cin >> id;

        for (int i = 0; i < count; i++)
        {
            if (patients[i].patientId == id)
            {
                for (int j = i; j < count - 1; j++)
                {
                    patients[j] = patients[j + 1];
                }

                count--;

                cout << "Record deleted." << endl;
                return;
            }
        }

        cout << "Record not found." << endl;
    }

void mainTransaction()
{
    int id;
    bool found = false;

    cout << "Enter Patient ID for transaction: ";
    cin >> id;

    for (int i = 0; i < count; i++)
    {
        if (patients[i].patientId == id)
        {
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Patient record not found." << endl;
        return;
    }

    Appointment a;
    Treatment t;
    Bill b;

    static int nextAppointmentId = 1;
    static int nextBillId = 1;

    a.appointmentId = nextAppointmentId++;
    a.patientId = id;

    b.billId = nextBillId++;
    b.patientId = id;

    a.book();

    cout << "Appointment ID: "
         << a.appointmentId << endl;

    t.cost = 500;
    t.calculate();

    b.calculateTotal(t.cost);
    b.printBill();
}

    void report()
    {
        cout << "\nTotal Patients: " << count << endl;
    }

    void saveLoad()
    {
        int choice;

        cout << "1. Save" << endl;
        cout << "2. Load" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
            file.save(patients, count);
        else if (choice == 2)
        {
            count = file.load(patients, 10);
        }
    }

    void menu()
    {
        int choice;

        do
        {
            cout << "\n===== DENTAL CLINIC MANAGEMENT =====" << endl;
            cout << "1. Add Record" << endl;
            cout << "2. Display Records" << endl;
            cout << "3. Search Record" << endl;
            cout << "4. Update Record" << endl;
            cout << "5. Delete Record" << endl;
            cout << "6. Main Transaction / Process" << endl;
            cout << "7. Report" << endl;
            cout << "8. Save / Load" << endl;
            cout << "9. Exit" << endl;

            cout << "Enter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    addRecord();
                    break;

                case 2:
                    displayRecords();
                    break;

                case 3:
                    searchRecord();
                    break;

                case 4:
                    updateRecord();
                    break;

                case 5:
                    deleteRecord();
                    break;

                case 6:
                    mainTransaction();
                    break;

                case 7:
                    report();
                    break;

                case 8:
                    saveLoad();
                    break;

                case 9:
                    cout << "Thank you." << endl;
                    break;

                default:
                    cout << "Invalid choice." << endl;
            }

        } while (choice != 9);
    }

    ~System()
    {
        // Release dynamic memory
        delete[] patients;
    }
};


// ---------- MAIN ----------
int main()
{
    System s;

    s.menu();

    return 0;
}