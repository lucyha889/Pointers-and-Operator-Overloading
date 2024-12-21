#include "ContactBook.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
//default constructor for Contact class with name and number declared as strings
Contact::Contact(const string& name, const string& number)
    : name(name), number(number) {}
//retrieve name 
string Contact::GetName() const {
    return name;
}
//retrieve number
string Contact::GetNumber() const {
    return number;
}
//display method for contact
void Contact::Display() const {
    cout << name << ", " << number << endl;
}

//iterate integers through contacts inside the ContactBook class
ContactBook::ContactBook() : curr_size(0) {
    for (unsigned int i = 0; i < MAX_SIZE; i++) {
        contacts[i] = nullptr;
    }
}

ContactBook::ContactBook(const ContactBook& book1) : curr_size(book1.curr_size) {
    for (unsigned int i = 0; i < curr_size; i++) {
        contacts[i] = new Contact(*book1.contacts[i]);
    }
}

ContactBook& ContactBook::operator=(const ContactBook& book1) {
    //if (this == &book1) {

        for (unsigned int i = 0; i < curr_size; i++) {
        //delete contacts[i];
        contacts[i] = nullptr;
        }

        curr_size = book1.curr_size;
        for (unsigned int i = 0; i < curr_size; i++) {
        contacts[i] = new Contact(*book1.contacts[i]);
        }

        for (unsigned int i = curr_size; i < MAX_SIZE; ++i) {
            contacts[i] = nullptr;
        }
    //}  
    return *this;
}
//deconstructor for ContactBook 
ContactBook::~ContactBook() {
    for (unsigned int i = 0; i < curr_size; i++) {
        //delete contacts[i]; deletes the entire array
        contacts[i] = nullptr;
    }
}

Contact* ContactBook::Find(const string& search) const {
    for (unsigned int i = 0; i < curr_size; i++) {
        // If either name or number matches, return the contact
        if (contacts[i]->GetName() == search || contacts[i]->GetNumber() == search) {
            return contacts[i];
        }
    }
    return nullptr;
}

void ContactBook::Add(Contact& contact) {
    if (curr_size < MAX_SIZE) {
        contacts[curr_size++] = &contact;
    }
}
//add multiple contacts from a vector
void ContactBook::AddContacts(const vector<Contact*>& contactList) {
    for (auto contact : contactList) {
        if (curr_size < MAX_SIZE) {
            contacts[curr_size++] = contact;
        }
    }
}
// Remove Contact Method to remove a contact from the ContactBook
void ContactBook::Remove(Contact& contact) {
    for (unsigned int i = 0; i < curr_size; i++) {
        if (contacts[i]== &contact) {
            //delete contacts[i]; deletes the entire array
            for (unsigned int j = i; j < curr_size - 1; j++) {
                contacts[j] = contacts[j + 1];
            }
            contacts[--curr_size] = nullptr;
            break;
        }
    }
}
//display methods for ContactBook
void ContactBook::Display() const {
    for (unsigned int i = 0; i < curr_size; i++) {
        contacts[i]->Display();//call display method on each contact
    }
}

void ContactBook::Alphabetize() {
    //create a lambda sort function to compare contacts by name 
    sort(contacts, contacts + curr_size, [](Contact* first, Contact* second) {
        return first->GetName() < second->GetName();
    });
}

// Overloaded operator to add a single contact using +=
ContactBook& ContactBook::operator+=(Contact& contact) {
    Add(contact);
}
// Overloaded operator to merge two ContactBooks using +=
ContactBook& ContactBook::operator+=(ContactBook& book1) {
    for (unsigned int i = 0; i < book1.curr_size; i++) {
        Add(*book1.contacts[i]);
    }
    return *this;
}
// Overloaded operator to combine two ContactBooks using +
ContactBook ContactBook::operator+(const ContactBook& book1) const {
    ContactBook newContactBook(*this);
    for (unsigned int i = 0; i < book1.curr_size; i++) {
        newContactBook.Add(*book1.contacts[i]);
    }
    return newContactBook;
}
// Overloaded operator to remove a single contact using -=
/*ContactBook& ContactBook::operator-=(Contact& contact) {
    Remove(contact);
    return *this; (did not work for -= operator)
}*/

ContactBook& ContactBook::operator-=(Contact& contact) {
    // Iterate through the contacts to find the one to remove by comparing names (or number)
    for (unsigned int i = 0; i < curr_size; i++) {
        // Compare by name (or number) to find the contact to remove
        if (contacts[i]->GetName() == contact.GetName() && contacts[i]->GetNumber() == contact.GetNumber()) {
            // Remove the contact by shifting elements left
            for (unsigned int j = i; j < curr_size - 1; j++) {
                contacts[j] = contacts[j + 1];
            }
            contacts[--curr_size] = nullptr; // Decrease size and nullify the last element
            break;  // Exit after removing the contact
        }
    }
    return *this;
}

// Overloaded operator to remove multiple contacts using -=
ContactBook& ContactBook::operator-=(ContactBook& book1) {
    for (unsigned int i = 0; i < book1.curr_size; i++) {
        Contact* contactToRemove = book1.contacts[i];
        // Iterate through the current ContactBook to find the matching contact
        for (unsigned int j = 0; j < curr_size; j++) {
            // Compare contacts by name (or you can use number as well for stricter matching)
            if (contacts[j]->GetName() == contactToRemove->GetName()) {
                // Remove the contact by shifting elements left
                for (unsigned int k = j; k < curr_size - 1; k++) {
                    contacts[k] = contacts[k + 1];
                }
                contacts[--curr_size] = nullptr; // Decrease the size and nullify the last element
                j--;  // Adjust the index to account for the shift
                break;
            }
        }
    }
    return *this;
}
// Overloaded operator to subtract the contacts of one ContactBook from another using -
/*ContactBook ContactBook::operator-(const ContactBook& book1) const {
    ContactBook newContactBook(*this);
    for (unsigned int i = 0; i < book1.curr_size; i++) {
        newContactBook.Remove(*book1.contacts[i]);
    }
    return newContactBook; (did not work for - operator)
}*/

// Overloaded operator to subtract the contacts of one ContactBook from another using -
ContactBook ContactBook::operator-(const ContactBook& book1) const {
    ContactBook result(*this);  // Create a copy of the current ContactBook

    // Iterate over the contacts in book1
    for (unsigned int i = 0; i < book1.curr_size; i++) {
        Contact* contactToRemove = book1.contacts[i];

        // Find and remove the contact in the result ContactBook
        for (unsigned int j = 0; j < result.curr_size; j++) {
            // Compare by name (or both name and number, if needed)
            if (result.contacts[j]->GetName() == contactToRemove->GetName()) {
                // Remove the contact by shifting elements left
                for (unsigned int k = j; k < result.curr_size - 1; k++) {
                    result.contacts[k] = result.contacts[k + 1];
                }
                result.contacts[--result.curr_size] = nullptr; // Decrease size and nullify
                j--;  // Adjust the index to account for the shift
                break;
            }
        }
    }

    return result;  // Return the updated ContactBook
}

// Overloaded equality operator to check if two Contactothers are equal
bool ContactBook::operator==(const ContactBook& book1) const {
    if (curr_size != book1.curr_size)
        return false;

    for (unsigned int i = 0; i < curr_size; i++) {
        if (Find(contacts[i]->GetName()) == nullptr)
            return false;
    }

    return true;
}
// Overloaded inequality operator to check if two Contactothers are not equal
bool ContactBook::operator!=(const ContactBook& book1) const {
    return !(*this == book1);
}