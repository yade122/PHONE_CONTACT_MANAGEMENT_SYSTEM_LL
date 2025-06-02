//Phone contact management system
#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <regex>
#include <ctime>
#include <vector>
using namespace std;
struct Contact {
string name;
string phoneNumber;
string timestamp; // Tracks creation/update time for active contacts, deletion time for deleted contacts
bool isDeleted; // Flag to indicate if contact is deleted
Contact* next; // Pointer for linked list (used only for active contacts)
};
Contact* head = nullptr; // Linked list for active contacts
vector<Contact> deletedContacts; // Vector for deleted contacts
// Get current time as string
string getCurrentTime() {
time_t now = time(nullptr);
string timeStr = ctime(&now);
return timeStr.substr(0, timeStr.length() - 1); // Remove trailing newline
}
// Validate name (only letters and spaces allowed)
bool isValidName(const string& name) {
regex nameRegex("^[A-Za-z ]+$"); // Allows only letters and spaces
return regex_match(name, nameRegex) && !name.empty();
}
// Validate phone number (10-12 digits, no duplicates among active contacts)
bool isValidPhoneNumber(const string& phoneNumber) {
regex phoneRegex("^[0-9]{10,12}$");
if (!regex_match(phoneNumber, phoneRegex)) {
return false;
}
Contact* temp = head;
while (temp != nullptr) {
if (temp->phoneNumber == phoneNumber) {
return false;
}
temp = temp->next;
}
return true;
}
// Save active contacts to file
void saveContactsToFile() {
ofstream outFile("contacts.txt");
if (!outFile) {
cout << "Error opening file for writing.\n";
return;
}
Contact* temp = head;
while (temp != nullptr) {
outFile << temp->name << "\n" << temp->phoneNumber << "\n" << temp->timestamp << "\n";
temp = temp->next;
}
outFile.close();
cout << "Contacts saved to file.\n";

}
// Save deleted contacts to trash file
void saveDeletedContactsToFile() {

ofstream outFile("trash.txt");
if (!outFile) {
cout << "Error opening trash file for writing.\n";
return;
}
for (const auto& deleted : deletedContacts) {
outFile << deleted.name << "\n" << deleted.phoneNumber << "\n" << deleted.timestamp << "\n";
}
outFile.close();


}
// Load active contacts from file
void loadContactsFromFile() {



}
// Load deleted contacts from trash file
void loadDeletedContactsFromFile() {


}
// Create a new contact
void createContact() {
    string name, phoneNumber;
    cout << "Enter name (letters and spaces only): ";
    getline(cin, name);
    if (!isValidName(name)) {
    cout << "Invalid name. Must contain only letters and spaces.\n";
    return;
    }
    cout << "Enter phone number (10-12 digits): ";
    getline(cin, phoneNumber);
    if (!isValidPhoneNumber(phoneNumber)) {
    cout << "Invalid phone number or number already exists. Must be 10-12 digits.\n";
    return;
    }
    string currentTime = getCurrentTime();
    Contact* newContact = new Contact{name, phoneNumber, currentTime, false, nullptr};
    if (head == nullptr) {
    head = newContact;
    } else {
    Contact* temp = head;
    while (temp->next != nullptr) {
    temp = temp->next;
    }
    temp->next = newContact;
    }
    cout << "Contact added at " << currentTime << ".\n";
    saveContactsToFile();


}



// Retrieve all active contacts
void retrieveContacts() {


}
// Update contact by name
void updateContact() {
    string oldName;
cout << "Enter the name of the contact to update: ";
getline(cin, oldName);
Contact* temp = head;
while (temp != nullptr) {
if (temp->name == oldName) {
cout << "Enter new name (letters and spaces only): ";
string newName;
getline(cin, newName);
if (!isValidName(newName)) {
cout << "Invalid name. Must contain only letters and spaces. Update cancelled.\n";
return;
}
temp->name = newName;
cout << "Enter new phone number (10-12 digits): ";
string newPhoneNumber;
getline(cin, newPhoneNumber);
if (!isValidPhoneNumber(newPhoneNumber)) {
cout << "Invalid phone number or number already exists. Update cancelled.\n";
return;
}
temp->phoneNumber = newPhoneNumber;
temp->timestamp = getCurrentTime();
cout << "Contact updated at " << temp->timestamp << ".\n";
saveContactsToFile();
return;
}
temp = temp->next;
}
cout << "Contact not found.\n";




}
// Delete contact by name
void deleteContact() {



}
// Restore contact from trash
void restoreContact() {



}
// Search for contact by name
void searchContact() {



}
// Sort active contacts alphabetically by name
void sortContacts() {



}
// Display deletion count and details
void showDeleteCount() {



}
void clearInputBuffer() {
cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
int main() {
cout << "\n*************************************************\n";
cout << "*\t\t WELCOME TO *\n";
cout << "*\t--- PHONE CONTACT MANAGEMENT SYSTEM ----*\n";
cout << "\n*************************************************\n";
cout << " \t\t Enter your choice \n";
cout << "1. Create Contact\n";
cout << "2. Retrieve All Contacts\n";
cout << "3. Update Contact\n";
cout << "4. Delete Contact\n";
cout << "5. Search Contact\n";
cout << "6. Sort Contacts\n";
cout << "7. Show Delete Count\n";
cout << "8. Restore Contact from Trash\n";
cout << "0. Exit\n";
cout << "Choose an option: ";
loadContactsFromFile();
loadDeletedContactsFromFile();
int choice;
do {
// showMenu();
cin >> choice;
clearInputBuffer();
switch (choice) {
case 1:
createContact();
break;
case 2:
retrieveContacts();
break;
case 3:
updateContact();
break;
case 4:
deleteContact();
break;
case 5:
searchContact();
break;
case 6:
sortContacts();
break;
case 7:
showDeleteCount();
break;
case 8:
restoreContact();
break;
case 0:
cout << "Exiting program.\n";
break;
default:
cout << "Invalid option. Try again.\n";
}
} while (choice != 0);
// Cleanup memory
Contact* temp;
while (head != nullptr) {
temp = head;
head = head->next;
delete temp;
}
return 0;
}

