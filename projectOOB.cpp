#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <ctime>
#include <sstream>

using namespace std;

// Donor class to encapsulate donor data and operations
class Donor
{
public:
    string id, name, email, password, gender, bloodType, diseaseInfo, otherDiseaseInfo, latestDonationDate;
    int age;

    void registerDonor();
    void login();
    void updateData();
    void deleteAccount(map<string, Donor> &donors);
    void requestDonation();
    static void loadDonors(map<string, Donor> &donors);
    static void saveDonors(const map<string, Donor> &donors);
};

// Recipient class to encapsulate recipient data and operations
class Recipient
{
public:
    string id, name, email, password, gender, bloodType, hospital, doctor;
    int age;

    void registerRecipient();
    void login();
    void updateData();
    void deleteAccount(map<string, Recipient> &recipients);
    void searchBloodType(const map<string, Donor> &donors);
    void displayAllBloodData(const map<string, Donor> &donors);
    void requestBlood();
    static void loadRecipients(map<string, Recipient> &recipients);
    static void saveRecipients(const map<string, Recipient> &recipients);
};

// Map to store donors and recipients using their ID as the key
map<string, Donor> donors;
map<string, Recipient> recipients;

// Function prototypes
void donorMenu();
void recipientMenu();

int main()
{
    Donor::loadDonors(donors);
    Recipient::loadRecipients(recipients);

    int choice;
    do
    {
        cout << "\nBlood Bank Management System\n";
        cout << "1. Donor\n2. Recipient\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            donorMenu();
            break;
        case 2:
            recipientMenu();
            break;
        case 3:
            Donor::saveDonors(donors);
            Recipient::saveRecipients(recipients);
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}

// Donor class methods
void Donor::registerDonor()
{
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter Email: ";
    cin >> email;
    cout << "Enter Password: ";
    cin >> password;
    cout << "Enter Age: ";
    cin >> age;
    cout << "Enter Gender: ";
    cin >> gender;
    cout << "Enter Blood Type: ";
    cin >> bloodType;
    cout << "Do you suffer from any disease (blood pressure disorders, thyroid disease, diabetes, cancer, heart disorders, hepatitis)? ";
    cin >> diseaseInfo;
    cout << "Do you suffer from any other disease or take any medicine? ";
    cin >> otherDiseaseInfo;
    cout << "Enter Date of Latest Donation: ";
    cin >> latestDonationDate;

    donors[id] = *this;
    cout << "Registration successful!\n";
}

void Donor::login()
{
    string inputId, inputPassword;
    cout << "Enter ID: ";
    cin >> inputId;
    cout << "Enter Password: ";
    cin >> inputPassword;

    if (donors.find(inputId) != donors.end() && donors[inputId].password == inputPassword)
    {
        cout << "Login successful!\n";
        int choice;
        do
        {
            cout << "\nDonor Menu\n";
            cout << "1. Donation Request\n2. Update Data\n3. Delete Account\n4. Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                donors[inputId].requestDonation();
                break;
            case 2:
                donors[inputId].updateData();
                break;
            case 3:
                donors[inputId].deleteAccount(donors);
                return;
            case 4:
                return;
            default:
                cout << "Invalid choice! Please try again.\n";
            }
        } while (true);
    }
    else
    {
        cout << "Invalid ID or Password! Please try again.\n";
    }
}

void Donor::updateData()
{
    cout << "Enter new data (leave empty to keep current value):\n";
    cout << "Name (" << name << "): ";
    cin.ignore();
    getline(cin, name);
    cout << "Email (" << email << "): ";
    getline(cin, email);
    cout << "Password (" << password << "): ";
    getline(cin, password);
    cout << "Age (" << age << "): ";
    string ageInput;
    getline(cin, ageInput);
    if (!ageInput.empty())
        age = stoi(ageInput);
    cout << "Gender (" << gender << "): ";
    getline(cin, gender);
    cout << "Blood Type (" << bloodType << "): ";
    getline(cin, bloodType);
    cout << "Disease Info (" << diseaseInfo << "): ";
    getline(cin, diseaseInfo);
    cout << "Other Disease Info (" << otherDiseaseInfo << "): ";
    getline(cin, otherDiseaseInfo);
    cout << "Latest Donation Date (" << latestDonationDate << "): ";
    getline(cin, latestDonationDate);

    cout << "Data updated successfully!\n";
}

void Donor::deleteAccount(map<string, Donor> &donors)
{
    donors.erase(id);
    cout << "Donor account deleted successfully!\n";
}

void Donor::requestDonation()
{
    cout << "Donation request for Donor ID: " << id << " recorded.\n";
    // Here you can implement further logic for handling the donation request.
}

void Donor::loadDonors(map<string, Donor> &donors)
{
    ifstream file("donors.txt");
    if (!file)
        return;

    Donor donor;
    while (file >> donor.id >> donor.name >> donor.email >> donor.password >> donor.age >> donor.gender >> donor.bloodType >> donor.diseaseInfo >> donor.otherDiseaseInfo >> donor.latestDonationDate)
    {
        donors[donor.id] = donor;
    }
    file.close();
}

void Donor::saveDonors(const map<string, Donor> &donors)
{
    ofstream file("donors.txt");
    for (const auto &entry : donors)
    {
        const Donor &donor = entry.second;
        file << donor.id << " " << donor.name << " " << donor.email << " " << donor.password << " " << donor.age << " "
             << donor.gender << " " << donor.bloodType << " " << donor.diseaseInfo << " " << donor.otherDiseaseInfo << " "
             << donor.latestDonationDate << "\n";
    }
    file.close();
}

// Recipient class methods
void Recipient::registerRecipient()
{
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter Email: ";
    cin >> email;
    cout << "Enter Password: ";
    cin >> password;
    cout << "Enter Age: ";
    cin >> age;
    cout << "Enter Gender: ";
    cin >> gender;
    cout << "Enter Blood Type: ";
    cin >> bloodType;
    cout << "Enter Hospital: ";
    cin >> hospital;
    cout << "Enter Doctor of the Case: ";
    cin >> doctor;

    recipients[id] = *this;
    cout << "Registration successful!\n";
}

void Recipient::login()
{
    string inputId, inputPassword;
    cout << "Enter ID: ";
    cin >> inputId;
    cout << "Enter Password: ";
    cin >> inputPassword;

    if (recipients.find(inputId) != recipients.end() && recipients[inputId].password == inputPassword)
    {
        cout << "Login successful!\n";
        int choice;
        do
        {
            cout << "\nRecipient Menu\n";
            cout << "1. Update Data\n2. Delete Account\n3. Search for Blood Type\n4. Display All Blood Data\n5. Request Blood\n6. Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                recipients[inputId].updateData();
                break;
            case 2:
                recipients[inputId].deleteAccount(recipients);
                return;
            case 3:
                recipients[inputId].searchBloodType(donors);
                break;
            case 4:
                recipients[inputId].displayAllBloodData(donors);
                break;
            case 5:
                recipients[inputId].requestBlood();
                break;
            case 6:
                return;
            default:
                cout << "Invalid choice! Please try again.\n";
            }
        } while (true);
    }
    else
    {
        cout << "Invalid ID or Password! Please try again.\n";
    }
}

void Recipient::updateData()
{
    cout << "Enter new data (leave empty to keep current value):\n";
    cout << "Name (" << name << "): ";
    cin.ignore();
    getline(cin, name);
    cout << "Email (" << email << "): ";
    getline(cin, email);
    cout << "Password (" << password << "): ";
    getline(cin, password);
    cout << "Age (" << age << "): ";
    string ageInput;
    getline(cin, ageInput);
    if (!ageInput.empty())
        age = stoi(ageInput);
    cout << "Gender (" << gender << "): ";
    getline(cin, gender);
    cout << "Blood Type (" << bloodType << "): ";
    getline(cin, bloodType);
    cout << "Hospital (" << hospital << "): ";
    getline(cin, hospital);
    cout << "Doctor (" << doctor << "): ";
    getline(cin, doctor);

    cout << "Data updated successfully!\n";
}

void Recipient::deleteAccount(map<string, Recipient> &recipients)
{
    recipients.erase(id);
    cout << "Recipient account deleted successfully!\n";
}

void Recipient::searchBloodType(const map<string, Donor> &donors)
{
    string bloodType;
    cout << "Enter Blood Type to search: ";
    cin >> bloodType;

    bool found = false;
    for (const auto &entry : donors)
    {
        if (entry.second.bloodType == bloodType)
        {
            cout << "Donor ID: " << entry.second.id << ", Name: " << entry.second.name << ", Email: " << entry.second.email << "\n";
            found = true;
        }
    }

    if (!found)
    {
        cout << "No donors found with Blood Type: " << bloodType << "\n";
    }
}

void Recipient::displayAllBloodData(const map<string, Donor> &donors)
{
    cout << "\nAll Blood Data:\n";
    for (const auto &entry : donors)
    {
        cout << "Blood Type: " << entry.second.bloodType << ", Quantity: Available, "
             << "Received Date: NA, Expiry Date: NA\n"; // Simplified for this example
    }
}

void Recipient::requestBlood()
{
    string bloodType, hospital;
    int quantity;
    cout << "Enter Blood Type: ";
    cin >> bloodType;
    cout << "Enter Quantity: ";
    cin >> quantity;
    cout << "Confirm Hospital: ";
    cin >> hospital;

    cout << "Blood request for Recipient ID: " << id << " recorded.\n";
    // Here you can implement further logic for handling the blood request.
}

void Recipient::loadRecipients(map<string, Recipient> &recipients)
{
    ifstream file("recipients.txt");
    if (!file)
        return;

    Recipient recipient;
    while (file >> recipient.id >> recipient.name >> recipient.email >> recipient.password >> recipient.age >> recipient.gender >> recipient.bloodType >> recipient.hospital >> recipient.doctor)
    {
        recipients[recipient.id] = recipient;
    }
    file.close();
}

void Recipient::saveRecipients(const map<string, Recipient> &recipients)
{
    ofstream file("recipients.txt");
    for (const auto &entry : recipients)
    {
        const Recipient &recipient = entry.second;
        file << recipient.id << " " << recipient.name << " " << recipient.email << " " << recipient.password << " " << recipient.age << " "
             << recipient.gender << " " << recipient.bloodType << " " << recipient.hospital << " " << recipient.doctor << "\n";
    }
    file.close();
}

// Function definitions for donor and recipient menus
void donorMenu()
{
    int choice;
    Donor donor;
    do
    {
        cout << "\nDonor Menu\n";
        cout << "1. Register\n2. Login\n3. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            donor.registerDonor();
            break;
        case 2:
            donor.login();
            break;
        case 3:
            return;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (true);
}

void recipientMenu()
{
    int choice;
    Recipient recipient;
    do
    {
        cout << "\nRecipient Menu\n";
        cout << "1. Register\n2. Login\n3. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            recipient.registerRecipient();
            break;
        case 2:
            recipient.login();
            break;
        case 3:
            return;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (true);
}
