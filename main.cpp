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
void UserMenu(Functions* f);
void CollectionMenu(int uid, Functions* f);
void EntryMenu(int cid, Functions* f);
void TrackMenu(int upc, Functions* f);
void ArtistMenu(int upc, int aid, Functions* f);

void UserMenu(Functions* f)
{
  string userName;
  stringstream sql;
  User_* U = NULL;
  MYSQL_RES* rset;
  MYSQL_ROW row;
  int User_ID;
  int cid;
  int uid;

  f->printAllUser();
  cout << "Select User (Enter User_ID or -1 for New User): ";
  cin >> uid;

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
    //Say something
    CollectionMenu(uid, f);
  }

  return;
}

void CollectionMenu(int uid, Functions* f)
{
  int cid;
  string collectionTitle;
  Collection* C = NULL;
  stringstream sql;
  MYSQL_RES* rset;
  MYSQL_ROW row;



  f->printCollectionsFromUser(uid);
  cout << "\nSelect Collection (Enter Collection_ID or\n"
       << "-1 to make a new collection): ";
  cin >> cid;



  if (cid == -1)
  {
    cout << "\nEnter New Collection Title: ";
    cin >> collectionTitle;
    sql << "SELECT MAX(Collection_ID) FROM Collection";
    if (!mysql_query(f->getConnection(), sql.str().c_str()))
    {
      C = new Collection();
      rset = mysql_use_result(f->getConnection());
      row = mysql_fetch_row(rset);
      cid = stoi(row[0]);
      mysql_free_result(rset); //Dont forget this
    }
    C->setCollectionTitle(collectionTitle);
    C->setCollectionID(cid + 1);
    C->setUserID(uid);
    f->createCollection(C);
  }

  else
  {
    EntryMenu(cid, f);
  }

}

void EntryMenu(int cid, Functions* f)
{
  int uid;
  int option;
  int upc;
  int Entry_ID;
  int Artist_ID;
  string title;
  int year;
  string condition;
  string label;
  string format;
  string entryTitle;

  stringstream sql;
  Entry* E = NULL;
  MYSQL_RES* rset;
  MYSQL_ROW row;

  f->printEntriesFromCollection(cid);

  cout << "Options:-1 - Go Back\n"
       << "         0 - Delete Entry\n"
       << "         1 - Add Entry\n"
       << "         2 - Select Entry\n"
       << "         3 - Select Artist\n";
  cin >> option;

  switch(option)
  {
    case -1:
      //stuff
      sql << "SELECT User_ID FROM Collection WHERE Collection_ID="
          << to_string(cid);
      if (!mysql_query(f->getConnection(), sql.str().c_str()))
      {
        rset = mysql_use_result(f->getConnection());
        row = mysql_fetch_row(rset);
        uid = stoi(row[0]);
        mysql_free_result(rset);
      }
      CollectionMenu(uid, f);

    case 0:
      cout << "\nWhich Entry? (Enter Entry_UPC): ";
      cin >> upc;
      f->deleteEntry(upc);
      EntryMenu(cid, f);

    case 1:
      cout << "\nEnter Entry Title: ";
      cin  >> entryTitle;
      cout << "\nEnter Entry year: ";
      cin >> year;
      cout << "\nEnter Entry format (Vinyl, Tape, CD, Digital): ";
      cin >> format;
      cout << "\nEnter Entry condition (Very Good, Good, Fair, Poor,\n"
           <<    "                      Very Poor): ";
      cin >> condition;


      sql << "SELECT MAX(Entry_UPC) FROM Entry";
      if (!mysql_query(f->getConnection(), sql.str().c_str()))
      {
        E = new Entry();
        rset = mysql_use_result(f->getConnection());
        row = mysql_fetch_row(rset);
        upc = stoi(row[0]);
        mysql_free_result(rset); //Dont forget this
      }
      E->setEntryUPC(upc + 1);
      E->setEntryLabel(label);
      E->setEntryTitle(title);
      E->setEntryFormat(format);
      E->setEntryCondition(condition);
      E->setYear(year);
      f->createEntry(E);
      EntryMenu(cid, f);

    case 2:
      cout << "Enter Entry_ID: ";
      cin >> Entry_ID;
      TrackMenu(Entry_ID, f);

    case 3:
      cout << "Enter Artist_ID: ";
      cin >> Artist_ID;
      ArtistMenu(upc, Artist_ID, f);




  }



}

void TrackMenu(int upc, Functions* f)
{

}

void ArtistMenu(int Entry_UPC, int aid, Functions* f)
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

  UserMenu(f);

  return 0;

}
