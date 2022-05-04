#include <iostream>
#include <sstream>
#include <iomanip>

#include <cstdlib>
#include <mysql/mysql.h>

#include "functions.h"
#include "tables.h"

using namespace std;

void UserMenu(Functions* f);
void CollectionMenu(int uid, Functions* f);
void EntryMenu(int cid, Functions* f);
void TrackMenu(int eid, Functions* f);
void ArtistMenu(int eid, Functions* f);
void ArtistMembersMenu(int aid, Functions* f);
void EntryGenreMenu(int eid, Functions* f);
void TrackGenreMenu(int tid, Functions* f);

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
       << "         2 - Select User\n"
       << "         3 - Modify User\n";
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
    case 3:
      cout << "\nEnter User ID: ";
      cin >> uid;
      cout << "\nEnter New Username: ";
      cin >> userName;
      sql << "UPDATE User_ "
          << " SET User_name=" << userName
          << " WHERE User_ID=" << uid;
      if (!mysql_query(f->getConnection(), sql.str().c_str()))
      {
        cout << "\nSuccess!";
      }
      else
      {
        cout << "\nFailed";
      }
      UserMenu(f);
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
       << "         2 - Select Collection\n"
       << "         3 - Modify Collection\n";
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
      if (!mysql_query(f->getConnection(), sql.str().c_str()))
      {
        if(rset)
        {
          int i=0;
          int j=0;
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
    case 3:
      cout << "\nEnter Collection_ID: ";
      cin >> cid;
      cout << "\nEnter New Collection Title: ";
      cin.ignore();
      getline(cin, collectionTitle);
      sql << "UPDATE Collection "
          << " SET Collection_Title='" << collectionTitle
          << "' WHERE Collection_ID=" << cid;
      if (!mysql_query(f->getConnection(), sql.str().c_str()))
      {
        cout << "\nSuccess!";
      }
      else
      {
        cout << "\nFailed";
      }
      CollectionMenu(uid,f);
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
       << "         4 - See Entry Genres\n"
       << "         5 - Modify Entry\n";
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
      cout << "\nEnter Entry format (Album, ep, single, etc..): ";
      cin >> format;
      cout << "\nEnter Entry condition (Very Good, Good, Fair, Poor,\n"
           <<    "                      Very Poor): ";
      cin.ignore();
      getline(cin, condition);
      cout << "\nEnter Entry label: ";
      getline(cin, label);
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
      cout << "Enter Entry_ID: ";
      cin >> Entry_ID;
      ArtistMenu(Entry_ID, f);
    case 4:
      cout << "Enter Entry_ID: ";
      cin >> Entry_ID;
      EntryGenreMenu(Entry_ID, f);
    case 5:
      cout << "\nEnter Entry_ID: ";
      cin >> eid;
      cout << "\nEnter Entry Title: ";
      cin.ignore();
      getline(cin,entryTitle);
      cout << "\nEnter Entry year: ";
      cin >> year;
      cout << "\nEnter Entry format (Album, ep, single, etc..): ";
      cin >> format;
      cout << "\nEnter Entry condition (Very Good, Good, Fair, Poor,\n"
           <<    "                      Very Poor): ";
      cin.ignore();
      getline(cin, condition);
      cout << "\nEnter Entry label: ";
      getline(cin, label);
      sql << "UPDATE Entry "
          << " SET Entry_title=" << title
          << " ,Entry_year=" << year
          << " ,Entry_format=" << format
          << " ,Entry_condition=" << condition
          << " ,Entry_label=" << label
          << " ,Collection_ID=" << cid
          << " WHERE Entry_ID=" << eid;
      if (!mysql_query(f->getConnection(), sql.str().c_str()))
      {
        cout << "\nSuccess!";
      }
      else
      {
        cout << "\nFailed";
      }
      EntryMenu(cid, f);
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
       << "         2 - See Track Genres\n"
       << "         3 - Modify Track\n";
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
      TrackGenreMenu(tid, f);
    case 3:
      cout << "\nEnter Track_ID: ";
      cin >> tid;
      cout << "\nEnter Track Title: ";
      cin.ignore();
      getline(cin,title);
      cout << "\nEnter Track length: ";
      cin >> length;
      sql << "UPDATE Track "
          << " SET Track_title=" << title
          << " ,Track_length=" << length
          << " WHERE Track_ID=" << tid;
      if (!mysql_query(f->getConnection(), sql.str().c_str()))
      {
        cout << "\nSuccess!";
      }
      else
      {
        cout << "\nFailed";
      }
      TrackMenu(eid, f);
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
       << "         2 - Select Artist Members\n"
       << "         3 - Modify Artist\n";
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
    case 3:
      cout << "\nEnter Artist ID: ";
      cin >> aid;
      cout << "\nEnter New Artist Name: ";
      cin.ignore();
      getline(cin,name);
      sql << "UPDATE Artist "
          << " SET Artist_name=" << name
          << " WHERE Artist_ID=" << aid;
      if (!mysql_query(f->getConnection(), sql.str().c_str()))
      {
        cout << "\nSuccess!";
      }
      else
      {
        cout << "\nFailed";
      }
      ArtistMenu(eid, f);
  }
  return;
}

void ArtistMembersMenu(int aid, Functions* f)
{
  int option, amid;
  int eid;
  string name, newname;
  stringstream sql;
  MYSQL_RES* rset;
  MYSQL_ROW row;
  Artist_members* Am = NULL;
  f->printArtistMembersFromArtist(aid);
  cout << "\nOptions:-1 - Go Back\n"
       << "         0 - Delete Member\n"
       << "         1 - Add Member\n"
       << "         2 - Modify Member\n";
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
    case 2:
      cout << "\nEnter Old Artist Name: ";
      cin.ignore();
      getline(cin,name);
      cout << "\nEnter New Artist Name: ";
      cin.ignore();
      getline(cin,newname);
      sql << "UPDATE Artist_members "
          << " SET Member_name=" << newname
          << " WHERE Member_name=" << name;
      if (!mysql_query(f->getConnection(), sql.str().c_str()))
      {
        cout << "\nSuccess!";
      }
      else
      {
        cout << "\nFailed";
      }
      ArtistMembersMenu(aid, f);
  }
  return;
}

void EntryGenreMenu(int eid, Functions* f)
{
  int option;
  int cid;
  string genre, newgenre;
  stringstream sql;
  MYSQL_RES* rset;
  MYSQL_ROW row;
  Entry_Genre* Eg = NULL;
  f->printEntryGenre(eid);
  cout << "\nOptions:-1 - Go Back\n"
       << "         0 - Delete Genre\n"
       << "         1 - Add Genre\n"
       << "         2 - Modify Genre\n";
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
      cout << "\nEnter Genre to Delete: ";
      cin.ignore();
      getline(cin, genre);
      f->deleteOneEntryGenre(genre, eid);
      cout << "\nGenre Deleted" << endl;
      EntryGenreMenu(eid, f);
    case 1:
      cout << "\nEnter Genre to Add: ";
      cin.ignore();
      getline(cin, genre);
      Eg = new Entry_Genre();
      Eg->setEntryID(eid);
      Eg->setGenre(genre);
      f->createEntryGenre(Eg);
      EntryGenreMenu(eid, f);
    case 2:
      cout << "\nEnter Old Genre: ";
      cin.ignore();
      getline(cin,genre);
      cout << "\nEnter New Genre: ";
      cin.ignore();
      getline(cin,newgenre);
      sql << "UPDATE Entry_Genre "
          << " SET Genre=" << newgenre
          << " WHERE Genre=" << genre;
      if (!mysql_query(f->getConnection(), sql.str().c_str()))
      {
        cout << "\nSuccess!";
      }
      else
      {
        cout << "\nFailed";
      }
      EntryGenreMenu(eid, f);
  }
  return;
}

void TrackGenreMenu(int tid, Functions* f)
{
  int option;
  int eid;
  string genre, newgenre;
  stringstream sql;
  MYSQL_RES* rset;
  MYSQL_ROW row;
  Track_Genre* Tg = NULL;
  f->printTrackGenre(tid);
  cout << "\nOptions:-1 - Go Back\n"
       << "         0 - Delete Genre\n"
       << "         1 - Add Genre\n"
       << "         2 - Modify Genre\n";
  cin >> option;
  switch(option)
  {
    case -1:
      sql << "SELECT Entry_ID FROM Track WHERE Track_ID="
          << to_string(tid);
      if (!mysql_query(f->getConnection(), sql.str().c_str()))
      {
        rset = mysql_use_result(f->getConnection());
        row = mysql_fetch_row(rset);
        eid = stoi(row[0]);
        mysql_free_result(rset);
      }
      TrackMenu(eid, f);
    case 0:
      cout << "\nEnter Genre to Delete: ";
      cin.ignore();
      getline(cin, genre);
      f->deleteOneTrackGenre(genre, tid);
      cout << "\nTrack Genre Deleted" << endl;
      TrackGenreMenu(tid, f);
    case 1:
      cout << "\nEnter Track Genre to add: ";
      cin.ignore();
      getline(cin, genre);
      Tg = new Track_Genre();
      Tg->setTrackID(tid);
      Tg->setTrack(genre);
      f->createTrackGenre(Tg);
      TrackGenreMenu(tid, f);
    case 2:
      cout << "\nEnter Old Genre: ";
      cin.ignore();
      getline(cin,genre);
      cout << "\nEnter New Genre: ";
      cin.ignore();
      getline(cin,newgenre);
      sql << "UPDATE Track_Genre "
          << " SET Genre=" << newgenre
          << " WHERE Genre=" << genre;
      if (!mysql_query(f->getConnection(), sql.str().c_str()))
      {
        cout << "\nSuccess!";
      }
      else
      {
        cout << "\nFailed";
      }
      TrackGenreMenu(tid, f);
  }
  return;
}

int main(int argc, char** argv) {


  Functions* f = new Functions("localhost", "root",
                                "Na228513!", "MusicCollection");

  UserMenu(f);

  return 0;

}
