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

void UserMenu(int uid, Functions* f)
{
  string userName;
  stringstream sql;
  User_* U = NULL;
  MYSQL_RES* rset;
  MYSQL_ROW row;
  int User_ID;
  int cid;

  if (uid == -1) //Creating new User
  {
    cout << "\nEnter New Username: ";
    cin >> userName;
    sql << "SELECT MAX(User_ID) FROM User_";
    if (!mysql_query(f->getConnection(), sql.str().c_str()))
    {
      U = new User_();
      rset = mysql_use_result(f->getConnection());
      row = mysql_fetch_row(rset);
      User_ID = stoi(row[0]);
      mysql_free_result(rset); //Dont forget this
    }
    U->setUserID(User_ID + 1);
    U->setUserName(userName);
    f->createUser(U);
  }

  else
  {
    U = f->getUser(uid);
    f->printCollectionsFromUser(uid);
    cout << "\nSelect Collection (Enter Collection_ID or\n"
         << "-1 to make a new collection): ";
    cin >> cid;
  }



  return;

}

void CollectionMenu(int uid)
{

}

void EntryMenu(int cid)
{

}

void TrackMenu(int Entry_UPC)
{

}

void ArtistMenu(int Entry_UPC)
{

}

void Artist_members(int aid)
{

}

int main(int argc, char** argv) {
  int choice;
  int uid;
  string userName;
  stringstream ss;

  Functions* f = new Functions("localhost", "root",
                                "Na228513!", "MusicCollection");


  f->printAllUser();
  cout << "Select User (Enter User_ID or -1 for New User): ";
  cin >> uid;
  UserMenu(uid, f);

  return 0;

}
