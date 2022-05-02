#include <iostream>
#include <sstream>
#include <iomanip>

#include <cstdlib>
#include <mysql/mysql.h>

#include "functions.h"
#include "tables.h"

using namespace std;



// int mainMenu()
// {
//   Collection* C = NULL;
//   Functions* f = new Functions("localhost", "root",
//                              "Na228513!", "init.sql");
//
//   f->printAllCollection();
//   int collectionID;
//   cout <<"\nEnter Collection_ID you want to select";
//   cin >> collectionID;
//   C = f->getCollection(collectionID);
//
//
//   cout <<"\nShowing all entries for collection";
// }


int main(int argc, char** argv) {
  std::cout << "Hello World!\n";

  int choice;
  int UID;

  Functions* f = new Functions("localhost", "root",
                                "Na228513!", "DBProject");

  f->printAllCollection();
  return 0;

}
