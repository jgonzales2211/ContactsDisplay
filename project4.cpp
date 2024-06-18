#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct Contact {
    string name;
    string email;
    string phone;
    int id;
};

void display();
void add();
void view();
void deleteContact();
void display_title();
void display_menu();
void saveToFile();

vector<Contact> contacts;
int main() {
    ifstream file("contacts.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            Contact contact;
            istringstream iss(line);
            iss >> contact.name >> contact.email >> contact.phone >> contact.id;
            contacts.push_back(contact);   
        }
        file.close();
    }
    while (true) {
        display_title();
        display_menu();
        string command;
        cout << "Command: ";
        cin >> command;
        
        if (command == "list") {
            display();
        } else if (command== "add"){
            add();
        } else if (command == "view") {
            view();
        } else if (command == "del") {
            deleteContact();
        } else if (command == "exit") {
            saveToFile();
            cout << "\nThank you for using my app.\n";
            break;
        } else {
            cout << "Invalid command. Try again. \n";
        }
    }
    return 0;
}

void display() {
    cout << "\nCONTACT LIST\n";
    for (size_t i=0; i< contacts.size(); ++i) {
        cout << i + 1 << ". " << contacts[i].name << ", " << contacts[i].id << endl;

    }
}

void add() {
    Contact newContact;
    cout << "Name: ";
    cin.ignore();
    getline(cin, newContact.name);
    cout << "Email: ";
    getline(cin, newContact.email);
    cout << "Phone: ";
    getline(cin, newContact.phone);
    cout << "ID: ";
    cin >> newContact.id;
    
    contacts.push_back(newContact);
    cout << newContact.name << ", " << newContact.id << " was added. \n";
    saveToFile();
}
void view() {
    cout << "\nVIEW CONTACT\n";
    display();
    size_t index;
    cout << "Number (1 - " << contacts.size() << "): ";
    cin>> index;
    
    if(index > 0 && index <= contacts.size()) {
        cout << contacts[index-1].name << ", " << contacts[index -1].id << endl;
    } else {
        cout << "Invalid number. Try again!\n";
    }
}

void deleteContact() {
    cout << "\nDELETE CONTACT\n";
    display();
    size_t index;
    cout << "Number (1 - " << contacts.size() << "): ";
    cin >> index;
    
    if(index > 0 && index <= contacts.size()){
        cout << contacts[index-1].name << ", " << contacts[index -1].id << " was deleted.\n";
        contacts.erase(contacts.begin() + index -1);

        saveToFile();
    } else {
        cout << "Invalid number. Try again!\n";
    }
}

void display_title() {
    cout << "Contact Management System\n\n";
    }

void display_menu() {
    cout << "COMMAND MENU\n";
    cout<< "list - Display all contacts\n";
    cout << "view - View a contact\n";
    cout << "add - Add a contact\n";
    cout << "del - Delete a contact\n";
    cout << "exit - Exit program\n";
}
void saveToFile() {
    ofstream file("contacts.txt");
    if (file.is_open()) {
        for (const auto &contact : contacts) {
            file<< contact.name << "\t" <<contact.email << "\t" << contact.phone << "\t" << contact.id << endl;
        }
        file.close();
    }
}