#include <iostream>
#include "ContactBook.h"

// DO NOT WRITE YOUR CLASS IN THIS FILE
// This file is only to debug your own class/code using the
// Code Visualizer buttons in the Guide
// The test cases below will completely ignore this file

int main() {

  ContactBook book;
  cout << "Start to test."<< endl;
  Contact contact1=Contact("Mike", "123456");
  Contact contact2=Contact("Peter", "234567");
  contact1.Display();
  cout<<contact1.GetName()<<endl;
  cout<<contact2.GetNumber()<<endl;

  book.Add(contact1);
  book.Add(contact2);
  book.Display();

  book.Remove(contact2);
  book.Display();

  return 0;
}