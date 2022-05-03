#include <cstdlib>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "functions.h"
#include "tables.h"

Functions::Functions(string host, string user, string password, string database)
{
  h = host;
  db_conn = mysql_init(NULL);
  if (!db_conn)
      message("MySQL initialization failed! ");
  db_conn = mysql_real_connect(db_conn, host.c_str(), user.c_str(), password.c_str(),
                               database.c_str(), 0, NULL, 0);
  if(!db_conn)
    message("Connection Error! ");
}

Functions::~Functions()
{
  mysql_close(db_conn);
}

void Functions::createUser(User_* user)
{
  stringstream ss;
  ss << "INSERT INTO User_(User_name, User_ID)"
     << " values ('" << user->getUserName() << "', "
     << user->getUserID() << ")";
  if (mysql_query(db_conn, ss.str().c_str()))
      message("Failure");
  else
      message("Success");
}
void Functions::createCollection(Collection* collection)
{
  stringstream ss;
  ss << "INSERT INTO Collection(Collection_Title, Collection_ID, User_ID)"
     << " values ('" << collection->getCollectionTitle() << "', "
     << collection->getCollectionID() << ", " << collection->getUserID()
     << ")";
  if (mysql_query(db_conn, ss.str().c_str()))
      message("Failure");
  else
      message("Success");
}
void Functions::createEntry(Entry* entry)
{
  stringstream ss;
  ss << "INSERT INTO Entry(Entry_title, Entry_year, Entry_format, Entry_condition, Entry_ID, Entry_label, Collection_ID)"
     << " values ('"
     << entry->getEntryTitle() << "', "
     << entry->getYear() << ", '"
     << entry->getEntryFormat() << "', '"
     << entry->getEntryCondition() << "', "
     << entry->getEntryID() << ", '"
     << entry->getEntryLabel() << "', "
     << entry->getCollectionID()
     << ")";
  if (mysql_query(db_conn, ss.str().c_str()))
  {
      message("Failure");
      cout << entry->getEntryTitle();
      cout << entry->getYear() << ", '";
      cout << entry->getEntryFormat() << "', '";
      cout << entry->getEntryCondition() << "', ";
      cout << entry->getEntryID() << ", '";
      cout << entry->getEntryLabel() << "', ";
      cout << entry->getCollectionID();
  }
  else
      message("Success");
}
void Functions::createTrack(Track* track)
{
  stringstream ss;
  ss << "INSERT INTO Track(Track_ID, Track_title, Track_length, Track_number, Entry_ID)"
     << " values ("
     << track->getTrackID() << ", '"
     << track->getTrackTitle() << "', "
     << track->getTrackLength() << ", "
     << track->getTrackNumber() << ", "
     << track->getEntryID()
     << ")";
  if (mysql_query(db_conn, ss.str().c_str()))
      message("Failure");
  else
      message("Success");
}
void Functions::createArtist(Artist* artist)
{
  stringstream ss;
  ss << "INSERT INTO Artist(Artist_ID, Artist_name, Entry_ID)"
     << " values ("
     << artist->getArtistID() << ", '"
     << artist->getArtistName() << "', "
     << artist->getEntryID()
     << ")";
  if (mysql_query(db_conn, ss.str().c_str()))
      message("Failure");
  else
      message("Success");
}
void Functions::createEntryGenre(Entry_Genre* egen)
{
  stringstream ss;
  ss << "INSERT INTO Entry_Genre(Entry_ID, Genre)"
     << " values ("
     << egen->getEntryID() << ", '"
     << egen->getGenre()
     << "')";
  if (mysql_query(db_conn, ss.str().c_str()))
      message("Failure");
  else
      message("Success");
}
void Functions::createTrackGenre(Track_Genre* tgen)
{
  stringstream ss;
  ss << "INSERT INTO Track_Genre(Track_ID, Genre)"
     << " values ("
     << tgen->getTrackID() << ", '"
     << tgen->getGenre()
     << "')";
  if (mysql_query(db_conn, ss.str().c_str()))
      message("Failure");
  else
      message("Success");
}
void Functions::createArtistMembers(Artist_members* amem)
{
  stringstream ss;
  ss << "INSERT INTO Artist_members(Artist_ID, Member_name)"
     << " values ("
     << amem->getArtistID() << ", '"
     << amem->getArtistMembers()
     << "')";
  if (mysql_query(db_conn, ss.str().c_str()))
      message("Failure");
  else
      message("Success");
}




//Delete Functions

void Functions::deleteUser(int uid)
{
  stringstream ss;
  ss << "DELETE FROM User_ WHERE User_ID=" << uid;
  if (mysql_query(db_conn, ss.str().c_str()))
      message("Failed to remove User!");
  else
      message("User removed successfully.");
}

void Functions::deleteCollection(int cid)
{
  stringstream ss;
  ss << "DELETE FROM Collection WHERE Collection_ID=" << cid;
  if (mysql_query(db_conn, ss.str().c_str()))
      message("Failed to remove collection!");
  else
      message("Collection removed successfully.");
}

void Functions::deleteEntry(int eid)
{
  stringstream ss;
  ss << "DELETE FROM Entry WHERE Entry_ID=" << eid;
  if (mysql_query(db_conn, ss.str().c_str()))
      message("Failed to remove Entry!");
  else
      message("Entry removed successfully.");
}

void Functions::deleteTrack(int tid)
{
  stringstream ss;
  ss << "DELETE FROM Track WHERE Track_ID=" << tid;
  if (mysql_query(db_conn, ss.str().c_str()))
      message("Failed to remove track!");
  else
      message("Track removed successfully.");
}

void Functions::deleteArtist(int aid)
{
  stringstream ss;
  ss << "DELETE FROM Artist WHERE Artist_ID=" << aid;
  if (mysql_query(db_conn, ss.str().c_str()))
      message("Failed to remove Artist!");
  else
      message("Artist removed successfully.");
}

void Functions::deleteEntryGenre(int eid)
{
  stringstream ss;
  ss << "DELETE FROM Entry_Genre WHERE Entry_ID=" << eid;
  if (mysql_query(db_conn, ss.str().c_str()))
      message("Failed to remove entry_genre!");
  else
      message("Entry_Genre removed successfully.");
}

void Functions::deleteTrackGenre(int tid)
{
  stringstream ss;
  ss << "DELETE FROM Track_Genre WHERE Track_ID=" << tid;
  if (mysql_query(db_conn, ss.str().c_str()))
      message("Failed to remove track genre!");
  else
      message("Track genre removed successfully.");
}

void Functions::deleteArtistMembers(int aid)
{
  stringstream ss;
  ss << "DELETE FROM Artist_members WHERE Artist_ID=" << aid;
  if (mysql_query(db_conn, ss.str().c_str()))
      message("Failed to remove artist_member!");
  else
      message("Artist_member removed successfully.");
}
void Functions::deleteOneArtistMember(string name)
{
  stringstream ss;
  ss << "DELETE FROM Artist_members WHERE Member_name='" << name << "'";
  if (mysql_query(db_conn, ss.str().c_str()))
      message("Failed to remove artist_member!");
  else
      message("Artist_member removed successfully.");
}

void Functions::deleteAllCollectionFromUser(int uid)
{
  //DELETE
  //FROM Collection
  //WHERE User_ID={uid}
  stringstream ss;
  ss << "DELETE "
     << "FROM Collection "
     << "WHERE User_ID=" << uid;
  if (mysql_query(db_conn, ss.str().c_str()))
      message("Fail.");
  else
      message("Success!");
}
void Functions::deleteAllEntryFromCollection(int cid)
{
  //DELETE
  //FROM Entry
  //WHERE Collection_ID={cid}
  stringstream ss;
  ss << "DELETE "
     << "FROM Entry "
     << "WHERE Collection_ID=" << cid;
  if (mysql_query(db_conn, ss.str().c_str()))
      message("Fail.");
  else
      message("Success!");
}
void Functions::deleteAllTrackFromEntry(int eid)
{
  //DELETE
  //FROM Track
  //WHERE Entry_ID={eid}
  stringstream ss;
  ss << "DELETE "
     << "FROM Track "
     << "WHERE Entry_ID=" << eid;
  if (mysql_query(db_conn, ss.str().c_str()))
      message("Fail.");
  else
      message("Success!");
}
void Functions::deleteAllArtistFromEntry(int eid)
{
  //DELETE
  //FROM Artist
  //WHERE Entry_ID={eid}
  stringstream ss;
  ss << "DELETE "
     << "FROM Artist "
     << "WHERE Entry_ID=" << eid;
  if (mysql_query(db_conn, ss.str().c_str()))
      message("Fail.");
  else
      message("Success!");
}
void Functions::deleteAllTrackGenreFromEntry(int eid)
{
  //SQL COMMAND
  //DELETE
  //FROM TrackGenre
  //WHERE TrackGenre.Track_ID IN
  //(
  //  SELECT Track.Track_ID FROM Track
  //  WHERE Track.Entry_ID={eid}
  //)
  stringstream ss;
  ss << "DELETE "
     << "FROM TrackGenre "
     << "WHERE TrackGenre.Track_ID IN "
     << "( "
     << "SELECT Track.Track_ID FROM Track "
     << "WHERE Track.Entry_ID=" << eid
     << " )";
  if (mysql_query(db_conn, ss.str().c_str()))
      message("Fail.");
  else
      message("Success!");
}
//Get Functions
User_* Functions::getUser(int uid)
{
  User_* U = NULL;
  MYSQL_RES* rset;
  MYSQL_ROW row;
  stringstream sql;
  sql << "SELECT * FROM User_ WHERE User_ID=" << uid;

  if (!mysql_query(db_conn, sql.str().c_str())) {
    U = new User_();
    rset = mysql_use_result(db_conn);
    row = mysql_fetch_row(rset);
    U->setUserName(row[0]);
    U->setUserID(atoi(row[1]));
  }
  mysql_free_result(rset);
  return U;
}

Collection* Functions::getCollection(int cid)
{
  Collection* C = NULL;
  MYSQL_RES* rset;
  MYSQL_ROW row;
  stringstream sql;
  sql << "SELECT * FROM Collection WHERE Collection_ID=" << cid;

  if (!mysql_query(db_conn, sql.str().c_str())) {
    C = new Collection();
    rset = mysql_use_result(db_conn);
    row = mysql_fetch_row(rset);
    C->setCollectionTitle(row[0]);
    C->setCollectionID(atoi(row[1]));
    C->setUserID(atoi(row[2]));
  }
  mysql_free_result(rset);
  return C;
}

Entry* Functions::getEntry(int eid)
{
  Entry* E = NULL;
  MYSQL_RES* rset;
  MYSQL_ROW row;
  stringstream sql;
  sql << "SELECT * FROM Entry WHERE Entry_ID=" << eid;

  if (!mysql_query(db_conn, sql.str().c_str())) {
    E = new Entry();
    rset = mysql_use_result(db_conn);
    row = mysql_fetch_row(rset);
    E->setEntryTitle(row[0]);
    E->setYear(atoi(row[1]));
    E->setEntryFormat(row[2]);
    E->setEntryCondition(row[3]);
    E->setEntryID(atoi(row[4]));
    E->setEntryLabel(row[5]);
    E->setCollectionID(atoi(row[6]));
  }
  mysql_free_result(rset);
  return E;
}

Track* Functions::getTrack(int tid)
{
  Track* T = NULL;
  MYSQL_RES* rset;
  MYSQL_ROW row;
  stringstream sql;
  sql << "SELECT * FROM Track WHERE Track_ID=" << tid;

  if (!mysql_query(db_conn, sql.str().c_str())) {
    T = new Track();
    rset = mysql_use_result(db_conn);
    row = mysql_fetch_row(rset);
    T->setTrackID(atoi(row[0]));
    T->setTrackTitle(row[1]);
    T->setTrackLength(atoi(row[2]));
    T->setTrackNumber(atoi(row[3]));
    T->setEntryID(atoi(row[4]));
  }
  mysql_free_result(rset);
  return T;
}

Artist* Functions::getArtist(int aid)
{
  Artist* A = NULL;
  MYSQL_RES* rset;
  MYSQL_ROW row;
  stringstream sql;
  sql << "SELECT * FROM Artist WHERE Artist_ID=" << aid;

  if (!mysql_query(db_conn, sql.str().c_str())) {
    A = new Artist();
    rset = mysql_use_result(db_conn);
    row = mysql_fetch_row(rset);
    A->setArtistID(atoi(row[0]));
    A->setArtistName(row[1]);
    A->setEntryID(atoi(row[2]));
  }
  mysql_free_result(rset);
  return A;
}

Entry_Genre* Functions::getEntryGenre(int eid)
{
  Entry_Genre* E = NULL;
  MYSQL_RES* rset;
  MYSQL_ROW row;
  stringstream sql;
  sql << "SELECT * FROM Entry_Genre WHERE Entry_ID=" << eid;

  if (!mysql_query(db_conn, sql.str().c_str())) {
    E = new Entry_Genre();
    rset = mysql_use_result(db_conn);
    row = mysql_fetch_row(rset);
    E->setEntryID(atoi(row[0]));
    E->setGenre(row[1]);
  }
  mysql_free_result(rset);
  return E;
}

Track_Genre* Functions::getTrackGenre(int tid)
{
  Track_Genre* T = NULL;
  MYSQL_RES* rset;
  MYSQL_ROW row;
  stringstream sql;
  sql << "SELECT * FROM Track_Genre WHERE Track_ID=" << tid;

  if (!mysql_query(db_conn, sql.str().c_str())) {
    T = new Track_Genre();
    rset = mysql_use_result(db_conn);
    row = mysql_fetch_row(rset);
    T->setTrackID(atoi(row[0]));
    T->setTrack(row[1]);
  }
  mysql_free_result(rset);
  return T;
}

Artist_members* Functions::getArtistMembers(int aid)
{
  Artist_members* A = NULL;
  MYSQL_RES* rset;
  MYSQL_ROW row;
  stringstream sql;
  sql << "SELECT * FROM Artist_members WHERE Artist_ID=" << aid;

  if (!mysql_query(db_conn, sql.str().c_str())) {
    A = new Artist_members();
    rset = mysql_use_result(db_conn);
    row = mysql_fetch_row(rset);
    A->setArtistID(atoi(row[0]));
    A->setArtistMembers(row[1]);
  }
  mysql_free_result(rset);
  return A;
}

/////////////////////////////////////////////////////////////////////
void Functions::printAllUser()
{
  MYSQL_RES* rset;
  MYSQL_ROW rows;
  string sql = "SELECT * FROM User_";
  if(mysql_query(db_conn, sql.c_str()))
  {
    message("Error printing! ");
    return;
  }
  rset = mysql_use_result(db_conn);
  cout << "UserName | UserID" << endl;
  if(rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
       cout << rows[0]
            << " | " << rows[1]
            << endl;
    }
  }
  mysql_free_result(rset);
}

void Functions::printAllCollection()
{
  MYSQL_RES* rset;
  MYSQL_ROW rows;
  string sql = "SELECT * FROM Collection";
  if(mysql_query(db_conn, sql.c_str()))
  {
    message("Error printing! ");
    return;
  }
  rset = mysql_use_result(db_conn);
  cout << "Collection_Title | Collection_ID | User_ID" << endl;
  if(rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
       cout << rows[0]
            << " | " << rows[1]
            << " | " << rows[2]
            << endl;
    }
  }
  mysql_free_result(rset);
}
void Functions::printAllEntry()
{
  MYSQL_RES* rset;
  MYSQL_ROW rows;
  string sql = "SELECT * FROM Entry";
  if(mysql_query(db_conn, sql.c_str()))
  {
    message("Error printing! ");
    return;
  }
  rset = mysql_use_result(db_conn);
  cout << "Entry_title | Entry_year | Entry_format | Condition | ID | Label" << endl;
  if(rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
       cout << rows[0]
            << "| " << rows[1]
            << "| " << rows[2]
            << "| " << rows[3]
            << "| " << rows[4]
            << "| " << rows[5]
            << endl;
    }
  }
  mysql_free_result(rset);
}
void Functions::printAllTrack()
{
  MYSQL_RES* rset;
  MYSQL_ROW rows;
  string sql = "SELECT * FROM Track";
  if(mysql_query(db_conn, sql.c_str()))
  {
    message("Error printing! ");
    return;
  }
  rset = mysql_use_result(db_conn);
  cout << "Track_ID | Track_title | Track_length | Track_number | Entry_ID" << endl;
  if(rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
       cout << rows[0]
            << " | " << rows[1]
            << " | " << rows[2]
            << " | " << rows[3]
            << " | " << rows[4]
            << endl;
    }
  }
  mysql_free_result(rset);
}
void Functions::printAllArtist()
{
  MYSQL_RES* rset;
  MYSQL_ROW rows;
  string sql = "SELECT * FROM Artist";
  if(mysql_query(db_conn, sql.c_str()))
  {
    message("Error printing! ");
    return;
  }
  rset = mysql_use_result(db_conn);
  cout << "Artist_ID | Artist_name" << endl;
  if(rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
       cout << rows[0]
            << " | " << rows[1]
            << endl;
    }
  }
  mysql_free_result(rset);
}
void Functions::printAllEntryGenre()
{
  MYSQL_RES* rset;
  MYSQL_ROW rows;
  string sql = "SELECT * FROM Entry_Genre";
  if(mysql_query(db_conn, sql.c_str()))
  {
    message("Error printing! ");
    return;
  }
  rset = mysql_use_result(db_conn);
  cout << "Entry_ID | Genre" << endl;
  if(rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
       cout << rows[0]
            << " | " << rows[1]
            << endl;
    }
  }
  mysql_free_result(rset);
}
void Functions::printAllTrackGenre()
{
  MYSQL_RES* rset;
  MYSQL_ROW rows;
  string sql = "SELECT * FROM Track_Genre";
  if(mysql_query(db_conn, sql.c_str()))
  {
    message("Error printing! ");
    return;
  }
  rset = mysql_use_result(db_conn);
  cout << "Track_ID | Genre" << endl;
  if(rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
       cout << rows[0]
            << " | " << rows[1]
            << endl;
    }
  }
  mysql_free_result(rset);
}
void Functions::printAllArtistMembers()
{
  MYSQL_RES* rset;
  MYSQL_ROW rows;
  string sql = "SELECT * FROM Artist_members";
  if(mysql_query(db_conn, sql.c_str()))
  {
    message("Error printing! ");
    return;
  }
  rset = mysql_use_result(db_conn);
  cout << "Artist_ID | Member_name" << endl;
  if(rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
       cout << rows[0]
            << " | " << rows[1]
            << endl;
    }
  }
  mysql_free_result(rset);
}

///////////////////////////////////////////////////////////

void Functions::printCollectionsFromUser(int uid)
{
  MYSQL_RES* rset;
  MYSQL_ROW rows;
  string sql = "SELECT * FROM Collection WHERE User_ID=";
  sql += to_string(uid);

  if (mysql_query(db_conn, sql.c_str()))
  {
    message("Error Printing! ");
    return;
  }
  rset = mysql_use_result(db_conn);
  cout << "\nCollection_Title | Collection_ID | User_ID" << endl;
  if (rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
      cout << rows[0] << " \t\t|\t  " << rows[1] << " \t|\t " << rows[2] << endl;
    }
  }
  mysql_free_result(rset);
}
void Functions::printEntriesFromCollection(int cid)
{
  MYSQL_RES* rset;
  MYSQL_ROW rows;
  string sql = "SELECT * FROM Entry WHERE Collection_ID=";
  sql += to_string(cid);
  if (mysql_query(db_conn, sql.c_str()))
  {
    message("Error Printing! ");
    return;
  }
  rset = mysql_use_result(db_conn);
  cout << "\nEntry_title | Entry_year | Entry_format | Entry_condition | Entry_ID | Entry_label" << endl;
  if (rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
      cout << rows[0] << " \t\t|\t  " << rows[1] << " \t|\t " << rows[2] <<  " \t\t|\t" << rows[3] << " \t\t|\t  " << rows[4] << " \t|\t " << rows[5] << endl;
    }
  }
  mysql_free_result(rset);
}
void Functions::printTracksFromEntry(int eid)
{
  MYSQL_RES* rset;
  MYSQL_ROW rows;
  string sql = "SELECT * FROM Track WHERE Entry_ID=";
  sql += to_string(eid);
  if (mysql_query(db_conn, sql.c_str()))
  {
    message("Error Printing! ");
    return;
  }
  rset = mysql_use_result(db_conn);
  cout << "\nTrack_ID | Track_title | Track_length | Track_number | Entry_ID" << endl;
  if (rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
      cout << rows[0] << " \t\t|\t  " << rows[1] << " \t|\t " << rows[2] <<" \t\t|\t" << rows[3] << " \t\t|\t  " << rows[4] << endl;
    }
  }
  mysql_free_result(rset);
}
void Functions::printArtistFromEntry(int eid)
{
  MYSQL_RES* rset;
  MYSQL_ROW rows;
  string sql = "SELECT * FROM Artist WHERE Entry_ID=";
  sql += to_string(eid);

  if (mysql_query(db_conn, sql.c_str()))
  {
    message("Error Printing! ");
    return;
  }
  rset = mysql_use_result(db_conn);
  cout << "\nArtist_ID | Artist_name | Entry_ID" << endl;
  if (rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
      cout << rows[0] << " \t\t|\t  " << rows[1] << " \t|\t " << rows[2] << endl;
    }
  }
  mysql_free_result(rset);
}
void Functions::printEntryGenre(int eid)
{
  MYSQL_RES* rset;
  MYSQL_ROW rows;
  string sql = "SELECT * FROM EntryGenre WHERE Entry_ID=";
  sql += to_string(eid);

  if (mysql_query(db_conn, sql.c_str()))
  {
    message("Error Printing! ");
    return;
  }
  rset = mysql_use_result(db_conn);
  cout << "\nEntry_ID | Genre" << endl;
  if (rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
      cout << rows[0] << " \t\t|\t  " << rows[1] << endl;
    }
  }
  mysql_free_result(rset);
}
void Functions::printTrackGenre(int tid)
{
  MYSQL_RES* rset;
  MYSQL_ROW rows;
  string sql = "SELECT * FROM TrackGenre WHERE Track_ID=";
  sql += to_string(tid);

  if (mysql_query(db_conn, sql.c_str()))
  {
    message("Error Printing! ");
    return;
  }
  rset = mysql_use_result(db_conn);
  cout << "\nTrack_ID | Genre" << endl;
  if (rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
      cout << rows[0] << " \t\t|\t  " << rows[1] << endl;
    }
  }
  mysql_free_result(rset);
}
//
void Functions::printArtistMembersFromArtist(int aid)
{
  MYSQL_RES* rset;
  MYSQL_ROW rows;
  string sql = "SELECT * FROM Artist_members WHERE Artist_ID=";
  sql += to_string(aid);

  if (mysql_query(db_conn, sql.c_str()))
  {
    message("Error Printing! ");
    return;
  }
  rset = mysql_use_result(db_conn);
  cout << "\nArtist_ID | Member_name" << endl;
  if (rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
      cout << rows[0] << " \t\t|\t  " << rows[1] << endl;
    }
  }
  mysql_free_result(rset);
}
//////////////////////////////////////////////////////////


void Functions::message(string msg)
{
  cout << msg << endl;
}
