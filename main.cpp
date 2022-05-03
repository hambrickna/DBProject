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
void TrackMenu(int eid, Functions* f);
void ArtistMenu(int eid, Functions* f);
void ArtistMembersMenu(int aid, Functions* f);

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
  int option;
  f->printAllUser();
  cout << "\nOptions:-1 - Exit\n"
       << "         0 - Delete User\n"
       << "         1 - Add User\n"
       << "         2 - Select User\n";
  cin >> option;
  switch(option)
  {
    case -1:
      exit(0);
    case 0:
      cout << "\nEnter User_ID to Delete: ";
      cin >> uid;
      //get all eid
      //SELECT Entry_ID FROM Collection,Entry
      //WHERE Entry.Collection_ID=Collection.Collection_ID AND Collection.User_ID={uid}
      sql << "SELECT Entry_ID FROM Collection,Entry "
          << "WHERE Entry.Collection_ID=Collection.Collection_ID AND Collection.User_ID="
          << uid;
      if(rset)
      {
        int i=0;
        while((row = mysql_fetch_row(rset)))
        {
          int j = stoi(row[i]);
          f->deleteAllTrackGenreFromEntry(j);
          f->deleteAllTrackFromEntry(j);
          f->deleteAllArtistFromEntry(j);
          f->deleteEntry(j);
          i++;
        }
      }
      mysql_free_result(rset);
      f->deleteAllCollectionFromUser(uid);
      f->deleteUser(uid);
      cout << "\nUser Deleted" << endl;
      UserMenu(f);
    case 1:
      cout << "\nEnter New Username: ";
      cin >> userName;
      sql << "SELECT MAX(User_ID) FROM User_";
      if (!mysql_query(f->getConnection(), sql.str().c_str()))
      {
        U = new User_();
        rset = mysql_use_result(f->getConnection());
        row = mysql_fetch_row(rset);
        if (row[0] != NULL)
          User_ID = stoi(row[0]);
        else
          User_ID = -1;
        mysql_free_result(rset);
      }
      U->setUserID(User_ID + 1);
      U->setUserName(userName);
      f->createUser(U);
      UserMenu(f);
    case 2:
      cout << "\nEnter User_ID: ";
      cin >> uid;
      CollectionMenu(uid, f);
  }
  return;
}

void CollectionMenu(int uid, Functions* f)
{
  int cid, eid;
  string collectionTitle;
  Collection* C = NULL;
  stringstream sql;
  MYSQL_RES* rset;
  MYSQL_ROW row;

  int option;
  f->printCollectionsFromUser(uid);
  cout << "\nOptions:-1 - Go Back To Users\n"
       << "         0 - Delete Collection\n"
       << "         1 - Add Collection\n"
       << "         2 - Select Collection\n";
  cin >> option;

  switch(option)
  {
    case -1:
      UserMenu(f);
    case 0:
      cout << "\nEnter Collection_ID to Delete: ";
      cin >> cid;
      //get all eid
      //SELECT Entry_ID FROM Entry
      //WHERE Collection.Collection_ID={id}
      sql << "SELECT Entry_ID FROM Entry "
          << "WHERE Collection.Collection_ID="
          << cid;
          cout << "Start Loop\n";
      if (!mysql_query(f->getConnection(), sql.str().c_str()))
      {
        if(rset)
        {
          int i=0;
          int j=0;
          cout << "Actually start loop\n";
          while((row = mysql_fetch_row(rset)))
          {
            j = stoi(row[i]);
            cout << j << endl;
            f->deleteAllTrackGenreFromEntry(j);
            f->deleteAllTrackFromEntry(j);
            f->deleteAllArtistFromEntry(j);
            f->deleteEntry(j);
            i++;
          }
        }
        mysql_free_result(rset);
      }
      cout << "post free result";
      //remove cid
      f->deleteCollection(cid);
      cout << "\nCollection Deleted" << endl;
      CollectionMenu(uid,f);
    case 1:
      cout << "\nEnter New Collection Name: ";
      cin.ignore();
      getline(cin,collectionTitle);
      sql << "SELECT MAX(Collection_ID) FROM Collection";
      if (!mysql_query(f->getConnection(), sql.str().c_str()))
      {
        C = new Collection();
        rset = mysql_use_result(f->getConnection());
        row = mysql_fetch_row(rset);
        if (row[0] != NULL)
          cid = stoi(row[0]);
        else
        {
          cid = 199;
        }
        mysql_free_result(rset);
      }
      C->setCollectionID(cid + 1);
      C->setCollectionTitle(collectionTitle);
      C->setUserID(uid);
      f->createCollection(C);
      CollectionMenu(uid,f);
    case 2:
      cout << "\nEnter Collection_ID: ";
      cin >> cid;
      EntryMenu(cid, f);
  }
  return;
}

void EntryMenu(int cid, Functions* f)
{
  int uid;
  int option;
  int eid = 300;
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

  cout << "\nOptions:-1 - Go Back\n"
       << "         0 - Delete Entry\n"
       << "         1 - Add Entry\n"
       << "         2 - Select Entry\n"
       << "         3 - Show Artists\n"
       << "         4 - See Entry Genres\n";
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
        if (row[0] != NULL)
          uid = stoi(row[0]);
        else
        {
          uid = -1;
        }
        mysql_free_result(rset);
      }
      CollectionMenu(uid, f);

    case 0:
      cout << "\nWhich Entry? (Enter Entry_ID): ";
      cin >> eid;
      f->deleteAllTrackGenreFromEntry(eid);
      f->deleteAllTrackFromEntry(eid);
      f->deleteAllArtistFromEntry(eid);
      f->deleteEntry(eid);
      EntryMenu(cid, f);

    case 1:
      cout << "\nEnter Entry Title: ";
      cin.ignore();
      getline(cin,entryTitle);
      cout << "\nEnter Entry year: ";
      cin >> year;
      cout << year;
      cout << "\nEnter Entry format (Album, ep, single, etc..): ";
      cin >> format;
      cout << format;
      cout << "\nEnter Entry condition (Very Good, Good, Fair, Poor,\n"
           <<    "                      Very Poor): ";
      cin.ignore();
      getline(cin, condition);
      cout << condition;
      cout << "\nEnter Entry label: ";
      getline(cin, label);
      cout << label;
      sql << "SELECT MAX(Entry_ID) FROM Entry";
      if (!mysql_query(f->getConnection(), sql.str().c_str()))
      {
        E = new Entry();
        rset = mysql_use_result(f->getConnection());
        row = mysql_fetch_row(rset);
        if (row[0] != NULL)
          eid = stoi(row[0]);
        else
        {
          eid = 299;
        }
        mysql_free_result(rset); //Dont forget this
      }

      E->setEntryID(eid + 1);
      E->setEntryLabel(label);
      E->setEntryTitle(entryTitle);
      E->setEntryFormat(format);
      E->setEntryCondition(condition);
      E->setYear(year);
      E->setCollectionID(cid);
      f->createEntry(E);
      EntryMenu(cid, f);

    case 2:
      cout << "Enter Entry_ID: ";
      cin >> Entry_ID;
      TrackMenu(Entry_ID, f);

    case 3:
      ArtistMenu(eid,f);
    case 4:
      f->printEntryGenre(eid);
  }
  return;
}

void TrackMenu(int eid, Functions* f)
{
  int option, length, number, cid;
  string title;
  int tid = 399;
  stringstream sql;
  stringstream sql2;
  MYSQL_RES* rset;
  MYSQL_ROW row;
  Track* T = NULL;
  f->printTracksFromEntry(eid);
  cout << "\nOptions:-1 - Go Back\n"
       << "         0 - Delete Track\n"
       << "         1 - Add Track\n"
       << "         2 - See Track Genres\n";
  cin >> option;
  switch(option)
  {
    case -1:
      sql << "SELECT Collection_ID FROM Entry WHERE Entry_ID="
          << to_string(eid);
      if (!mysql_query(f->getConnection(), sql.str().c_str()))
      {
        rset = mysql_use_result(f->getConnection());
        row = mysql_fetch_row(rset);
        cid = stoi(row[0]);
        mysql_free_result(rset);
      }
      EntryMenu(cid, f);
    case 0:
      cout << "\nEnter Track to Delete: ";
      cin >> tid;
      f->deleteTrack(tid);
      cout << "\nTrack Deleted" << endl;
      TrackMenu(eid,f);
    case 1:
      cout << "\nEnter Track Title: ";
      cin.ignore();
      getline(cin,title);
      cout << "\nEnter Track length (seconds): ";
      cin >> length;
      sql << "SELECT MAX(Track_ID) FROM Track";
      if (!mysql_query(f->getConnection(), sql.str().c_str()))
      {
        T = new Track();
        rset = mysql_use_result(f->getConnection());
        row = mysql_fetch_row(rset);
        if (row[0] != NULL)
          tid = stoi(row[0]);
        else
        {
          tid = 399;
        }
        mysql_free_result(rset); //Dont forget this
      }

      sql2 << "SELECT MAX(Track_Number) FROM Track WHERE Entry_ID=" << eid;
      if (!mysql_query(f->getConnection(), sql2.str().c_str()))
      {
        rset = mysql_use_result(f->getConnection());
        row = mysql_fetch_row(rset);
        if (row[0] != NULL)
          number = stoi(row[0]) + 1;
        else
        {
          number = 1;
        }
        mysql_free_result(rset); //Dont forget this
      }
      cout << eid << " " << title << " " << tid << " "
           << length << " " << number << " " << endl;

      T->setEntryID(eid);
      T->setTrackTitle(title);
      T->setTrackID(tid+1);
      T->setTrackLength(length);
      T->setTrackNumber(number);
      f->createTrack(T);
      TrackMenu(eid, f);
    case 2:
      cout << "\nEnter Track_ID: ";
      cin >> tid;
      f->printTrackGenre(tid);
  }
  return;
}

void ArtistMenu(int eid, Functions* f)
{
  int option;
  int aid = 499;
  int cid;
  string name;
  stringstream sql;
  MYSQL_RES* rset;
  MYSQL_ROW row;
  Artist* A = NULL;
  f->printArtistFromEntry(eid);
  cout << "\nOptions:-1 - Go Back\n"
       << "         0 - Delete Artist\n"
       << "         1 - Add Artist\n"
       << "         2 - Select Artist Members\n";
  cin >> option;
  switch(option)
  {
    case -1:
      sql << "SELECT Collection_ID FROM Entry WHERE Entry_ID="
          << to_string(eid);
      if (!mysql_query(f->getConnection(), sql.str().c_str()))
      {
        rset = mysql_use_result(f->getConnection());
        row = mysql_fetch_row(rset);
        cid = stoi(row[0]);
        mysql_free_result(rset);
      }
      EntryMenu(cid,f);
    case 0:
      cout << "\nEnter Artist to Delete: ";
      cin >> aid;
      f->deleteArtistMembers(aid);
      f->deleteArtist(aid);
      cout << "\nArtist Deleted" << endl;
      ArtistMenu(eid,f);
    case 1:
      cout << "\nEnter Artist Name: ";
      cin.ignore();
      getline(cin,name);
      sql << "SELECT MAX(Artist_ID) FROM Artist";
      if (!mysql_query(f->getConnection(), sql.str().c_str()))
      {
        A = new Artist();
        rset = mysql_use_result(f->getConnection());
        row = mysql_fetch_row(rset);
        if (row[0] != NULL)
          aid = stoi(row[0]);
        else
        {
          aid = 499;
        }
        mysql_free_result(rset); //Dont forget this
      }
      A->setEntryID(eid);
      A->setArtistName(name);
      A->setArtistID(aid+1);
      f->createArtist(A);
      ArtistMenu(eid, f);
    case 2:
      cout << "\nEnter Artist_ID: ";
      cin >> aid;
      ArtistMembersMenu(aid, f);
  }
  return;
}

void ArtistMembersMenu(int aid, Functions* f)
{
  int option, amid;
  int eid;
  string name;
  stringstream sql;
  MYSQL_RES* rset;
  MYSQL_ROW row;
  Artist_members* Am = NULL;
  f->printArtistMembersFromArtist(aid);
  cout << "\nOptions:-1 - Go Back\n"
       << "         0 - Delete Member\n"
       << "         1 - Add Member\n";
  cin >> option;
  switch(option)
  {
    case -1:
      sql << "SELECT Entry_ID FROM Artist WHERE Artist_ID="
          << to_string(aid);
      if (!mysql_query(f->getConnection(), sql.str().c_str()))
      {
        rset = mysql_use_result(f->getConnection());
        row = mysql_fetch_row(rset);
        eid = stoi(row[0]);
        mysql_free_result(rset);
      }
      ArtistMenu(eid, f);
    case 0:
      cout << "\nEnter Artist Member to Delete: ";
      cin.ignore();
      getline(cin, name);
      f->deleteOneArtistMember(name);
      cout << "\nArtist Deleted" << endl;
      ArtistMembersMenu(aid, f);
    case 1:
      cout << "\nEnter Artist Name: ";
      cin.ignore();
      getline(cin, name);
      Am = new Artist_members();
      Am->setArtistID(aid);
      Am->setArtistMembers(name);
      f->createArtistMembers(Am);
      ArtistMembersMenu(aid, f);
  }
  return;
}

int main(int argc, char** argv) {


  Functions* f = new Functions("localhost", "root",
                                "Na228513!", "MusicCollection");

  UserMenu(f);

  return 0;

}
