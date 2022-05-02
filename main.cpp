#include <iostream>
#include <sstream>
#include <iomanip>

#include <cstdlib>
#include <mysql.h>

#include "functions.h"
#include "tables.h"

using namespace std;

enum Options {...};

int mainMenu()
{
  Collection* C = NULL;
  Functions* f = new Functions("localhost", "root", 
                             "passwd123", "mybank");

  f->printAllCollection();
  int collectionID;
  cout <<"\nEnter Collection_ID you want to select";
  cin >> collectionID;
  C = f->getCollection(collectionID);
  

  cout <<"\nShowing all entries for collection";
}


int main(int argc, char** argv) {
  std::cout << "Hello World!\n";

  int choice;
  int UID;

  choice = mainMenu();
  if (choice == END)
    break;
  switch(choice) {

    case 
  }
}