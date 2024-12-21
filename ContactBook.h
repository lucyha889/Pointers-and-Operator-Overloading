#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Contact {
private:
    string name;
    string number;

public:
    //parameterized constructor with name and number as strings
    Contact(const string& name, const string& number);

    //accessors
    string GetName() const;
    string GetNumber() const;

    //display function 
    void Display() const;
};
//array of Contact pointers in Contact class
class ContactBook {
private:
    static const int MAX_SIZE = 100;
    Contact* contacts[MAX_SIZE];
    unsigned int curr_size;

public:
    //default Constructor
    ContactBook();

    //cop Constructor
    ContactBook(const ContactBook& book1);

    //assignment operator
    ContactBook& operator=(const ContactBook& book1);

    //destructor
    ~ContactBook();

    //find a contact by name or number
    Contact* Find(const string& search) const;

    //add a contact to the book
    void Add(Contact& contact);

    //add multiple contacts
    void AddContacts(const vector<Contact*>& contactList);

    //remove a contact
    void Remove(Contact& contact);

    //display all contacts
    void Display() const;

    //sort contacts alphabetically
    void Alphabetize();

    //operator overloads
    ContactBook& operator+=(Contact& contact);
    ContactBook& operator+=(ContactBook& book1);
    ContactBook operator+(const ContactBook& book1) const;
    ContactBook& operator-=(Contact& contact);
    ContactBook& operator-=(ContactBook& book1);
    ContactBook operator-(const ContactBook& book1) const;
    bool operator==(const ContactBook& book1) const;
    bool operator!=(const ContactBook& book1) const;
};