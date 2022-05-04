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
  cout << artist->getArtistID() << " "
       << artist->getArtistName() << " "
       << artist->getEntryID() << endl;
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

void Functions::deleteOneEntryGenre(string genre, int eid)
{
  stringstream ss;
  ss << "DELETE FROM Entry_Genre WHERE Genre='" << genre << "' AND Entry_ID=" << eid;
  if (mysql_query(db_conn, ss.str().c_str()))
      message("Failed to remove Genre!");
  else
      message("Genre removed successfully.");
}
void Functions::deleteOneTrackGenre(string genre, int tid)
{
  stringstream ss;
  ss << "DELETE FROM Track_Genre WHERE Genre='" << genre << "' AND Track_ID=" << tid;
  if (mysql_query(db_conn, ss.str().c_str()))
      message("Failed to remove Genre!");
  else
      message("Genre removed successfully.");
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
  stringstream sql;
  sql << "SELECT User_name, User_.User_ID FROM User_";
  if(mysql_query(db_conn, sql.str().c_str()))
  {
    message("Error printing! ");
    return;
  }
  rset = mysql_use_result(db_conn);
  cout << setw(58) << setfill('-') << "-" << endl;
  cout << "|" << left << setw(50) << setfill(' ') << "User Name" <<  "|"
       << left << setw(5) << setfill(' ') << "UID" <<  "|" << endl;
  cout << setw(58) << setfill('-') << "-" << endl;
  if(rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
       cout << "|" << left << setw(50) << setfill(' ') << rows[0] <<  "|"
            << left << setw(5) << setfill(' ') << rows[1] <<  "|" << endl;
    }
  }
  cout << setw(58) << setfill('-') << "-" << endl;
  mysql_free_result(rset);
}

void Functions::printAllCollection()
{
  MYSQL_RES* rset;
  MYSQL_ROW rows;
  stringstream sql;
  sql << "SELECT Collection_Title, Collection_ID, User_name FROM Collection, User_ WHERE Collection.User_ID=User_.User_ID";
  if(mysql_query(db_conn, sql.str().c_str()))
  {
    message("Error printing! ");
    return;
  }
  rset = mysql_use_result(db_conn);
  cout << setw(100) << setfill('-') << "-" << endl;
  cout << "|" << left << setw(50) << setfill(' ') << "Collection Title" <<  "|"
       << left << setw(5) << setfill(' ') << "CID" <<  "|"
       << left << setw(50) << setfill(' ') << "User Name" << "|" <<endl;
  cout << setw(100) << setfill('-') << "-" << endl;
  if(rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
       cout << "|" << left << setw(50) << setfill(' ') << rows[0] <<  "|"
            << left << setw(5) << setfill(' ') << rows[1] <<  "|"
            << left << setw(50) << setfill(' ') << rows[2] << "|" <<endl;
    }
  }
  cout << setw(100) << setfill('-') << "-" << endl;
  mysql_free_result(rset);
}
void Functions::printAllEntry()
{
  MYSQL_RES* rset;
  MYSQL_ROW rows;
  stringstream sql;
  sql << "SELECT Entry_title, Entry_year, Entry_format, Entry_ID, Entry_label, Collection_Title FROM Entry, Collection "
                   << "WHERE Collection.Collection_ID=Entry.Collection_ID";
  if(mysql_query(db_conn, sql.str().c_str()))
  {
    message("Error printing! ");
    return;
  }
  rset = mysql_use_result(db_conn);
  cout << setw(165) << setfill('-') << "-" << endl;
  cout << "|" << left << setw(50) << setfill(' ') << "Entry Title" <<  "|"
       << left << setw(5) << setfill(' ') << "Year" <<  "|"
       << left << setw(15) << setfill(' ') << "Entry Format" << "|"
       << left << setw(5) << setfill(' ') << "EID" << "|"
       << left << setw(50) << setfill(' ') << "Entry Label" << "|"
       << left << setw(50) << setfill(' ') << "Collection Title" << "|" << endl;
  cout << setw(165) << setfill('-') << "-" << endl;
  if(rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
       cout << "|" << left << setw(50) << setfill(' ') << rows[0] <<  "|"
       << left << setw(5) << setfill(' ') << rows[1] <<  "|"
       << left << setw(15) << setfill(' ') << rows[2] << "|"
       << left << setw(5) << setfill(' ') << rows[3] << "|"
       << left << setw(50) << setfill(' ') << rows[4] << "|"
       << left << setw(50) << setfill(' ') << rows[5] << "|" << endl;
    }
  }
  cout << setw(165) << setfill('-') << "-" << endl;
  mysql_free_result(rset);
}
void Functions::printAllTrack()
{
  MYSQL_RES* rset;
  MYSQL_ROW rows;
  stringstream sql;
  sql << "SELECT Track_number, Track_title, Track_length, Track_ID, Entry_title FROM Track,Entry WHERE Entry.Entry_ID=Track.Entry_ID";
  if(mysql_query(db_conn, sql.str().c_str()))
  {
    message("Error printing! ");
    return;
  }
  rset = mysql_use_result(db_conn);
  cout << setw(108) << setfill('-') << "-" << endl;
  cout << "|" << left << setw(3) << setfill(' ') << "Track Number" <<  "|"
       << left << setw(50) << setfill(' ') << "Track Title" <<  "|"
       << left << setw(7) << setfill(' ') << "Length" << "|"
       << left << setw(5) << setfill(' ') << "TID" << "|"
       << left << setw(50) << setfill(' ') << "Entry Title" << "|" << endl;
  cout << setw(108) << setfill('-') << "-" << endl;
  if(rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
       cout << "|" << left << setw(3) << setfill(' ') << rows[0] <<  "|"
       << left << setw(50) << setfill(' ') << rows[1] <<  "|"
       << left << setw(7) << setfill(' ') << rows[2] << "|"
       << left << setw(5) << setfill(' ') << rows[3] << "|"
       << left << setw(45) << setfill(' ') << rows[4] << "|" << endl;
    }
  }
  cout << setw(108) << setfill('-') << "-" << endl;
  mysql_free_result(rset);
}
void Functions::printAllArtist()
{
  MYSQL_RES* rset;
  MYSQL_ROW rows;
  stringstream sql;
  sql << "SELECT Artist.Artist_name, Artist.Artist_ID, Entry.Entry_title FROM Entry,Artist WHERE Entry.Entry_ID=Artist.Entry_ID";
  if(mysql_query(db_conn, sql.str().c_str()))
  {
    message("Error printing! ");
    return;
  }
  rset = mysql_use_result(db_conn);
  cout << setw(106) << setfill('-') << "-" << endl;
  cout << "|" << left << setw(50) << setfill(' ') << "Artist Name" <<  "|"
       << left << setw(5) << setfill(' ') << "AID" <<  "|"
       << left << setw(50) << setfill(' ') << "Entry Title" << "|" <<endl;
  cout << setw(106) << setfill('-') << "-" << endl;
  if(rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
       cout << "|" << left << setw(50) << setfill(' ') << rows[0] <<  "|"
           << left << setw(5) << setfill(' ') << rows[1] <<  "|"
           << left << setw(50) << setfill(' ') << rows[2] << "|" << endl;
    }
  }
  cout << setw(106) << setfill('-') << "-" << endl;
  mysql_free_result(rset);
}
void Functions::printAllEntryGenre()
{
  MYSQL_RES* rset;
  MYSQL_ROW rows;
  stringstream sql;
  sql << "SELECT Entry.Entry_title, Entry.Entry_ID, Entry_Genre.Genre FROM Entry,Entry_Genre WHERE Entry.Entry_ID=Entry_Genre.Entry_ID";
  if(mysql_query(db_conn, sql.str().c_str()))
  {
    message("Error printing! ");
    return;
  }
  rset = mysql_use_result(db_conn);
  cout << setw(106) << setfill('-') << "-" << endl;
  cout << "|" << left << setw(50) << setfill(' ') << "Entry Title" <<  "|"
       << left << setw(5) << setfill(' ') << "EID" <<  "|"
       << left << setw(50) << setfill(' ') << "Entry Genre" << "|" <<endl;
  cout << setw(106) << setfill('-') << "-" << endl;
  if(rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
       cout << "|" << left << setw(50) << setfill(' ') << rows[0] <<  "|"
           << left << setw(5) << setfill(' ') << rows[1] <<  "|"
           << left << setw(50) << setfill(' ') << rows[2] << "|" << endl;
    }
  }
  cout << setw(106) << setfill('-') << "-" << endl;
  mysql_free_result(rset);
}
void Functions::printAllTrackGenre()
{
  MYSQL_RES* rset;
  MYSQL_ROW rows;
  stringstream sql;
  sql << "SELECT Track.Track_title, Track.Track_ID, Track_Genre.Genre FROM Track,Track_Genre WHERE Track.Track_ID=Track_Genre.Track_ID";
  if(mysql_query(db_conn, sql.str().c_str()))
  {
    message("Error printing! ");
    return;
  }
  rset = mysql_use_result(db_conn);
  cout << setw(106) << setfill('-') << "-" << endl;
  cout << "|" << left << setw(50) << setfill(' ') << "Track Title" <<  "|"
       << left << setw(5) << setfill(' ') << "TID" <<  "|"
       << left << setw(50) << setfill(' ') << "Track Genre" << "|" <<endl;
  cout << setw(106) << setfill('-') << "-" << endl;
  if(rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
       cout << "|" << left << setw(50) << setfill(' ') << rows[0] <<  "|"
           << left << setw(5) << setfill(' ') << rows[1] <<  "|"
           << left << setw(50) << setfill(' ') << rows[2] << "|" << endl;
    }
  }
  cout << setw(106) << setfill('-') << "-" << endl;
  mysql_free_result(rset);
}
void Functions::printAllArtistMembers()
{
  MYSQL_RES* rset;
  MYSQL_ROW rows;
  stringstream sql;
  sql << "SELECT Artist.Artist_name, Artist.Artist_ID, Artist_members.Member_name FROM Artist, Artist_members WHERE Artist.Artist_ID=Artist_members.Artist_ID";
  if(mysql_query(db_conn, sql.str().c_str()))
  {
    message("Error printing! ");
    return;
  }
  rset = mysql_use_result(db_conn);
  cout << setw(106) << setfill('-') << "-" << endl;
  cout << "|" << left << setw(50) << setfill(' ') << "Artist Name" <<  "|"
       << left << setw(5) << setfill(' ') << "AID" <<  "|"
       << left << setw(50) << setfill(' ') << "Artist Member" << "|" <<endl;
  cout << setw(106) << setfill('-') << "-" << endl;
  if(rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
      cout << "|" << left << setw(50) << setfill(' ') << rows[0] <<  "|"
           << left << setw(5) << setfill(' ') << rows[1] <<  "|"
           << left << setw(50) << setfill(' ') << rows[2] << "|" << endl;
    }
  }
  cout << setw(106) << setfill('-') << "-" << endl;
  mysql_free_result(rset);
}

///////////////////////////////////////////////////////////

void Functions::printCollectionsFromUser(int uid)
{
  MYSQL_RES* rset;
  MYSQL_ROW rows;
  stringstream sql;
  sql << "SELECT Collection_Title, Collection.Collection_ID, User_name FROM Collection, User_"
      << " WHERE Collection.User_ID=User_.User_ID AND Collection.User_ID=" << uid;
  if(mysql_query(db_conn, sql.str().c_str()))
  {
    message("Error printing! ");
    return;
  }
  rset = mysql_use_result(db_conn);
  cout << setw(109) << setfill('-') << "-" << endl;
  cout << "|" << left << setw(50) << setfill(' ') << "Collection Title" <<  "|"
       << left << setw(5) << setfill(' ') << "CID" <<  "|"
       << left << setw(50) << setfill(' ') << "User Name" << "|" << endl;
  cout << setw(109) << setfill('-') << "-" << endl;
  if(rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
       cout << "|" << left << setw(50) << setfill(' ') << rows[0] <<  "|"
            << left << setw(5) << setfill(' ') << rows[1] <<  "|"
            << left << setw(50) << setfill(' ') << rows[2] << "|" << endl;
    }
  }
  cout << setw(109) << setfill('-') << "-" << endl;
  mysql_free_result(rset);
}
void Functions::printEntriesFromCollection(int cid)
{
  MYSQL_RES* rset;
  MYSQL_ROW rows;
  stringstream sql;
  sql << "SELECT Entry_title, Entry_year, Entry_format, Entry_ID, Entry_label, Collection_Title FROM Entry, Collection "
                   << "WHERE Collection.Collection_ID=Entry.Collection_ID AND Collection.Collection_ID=" << cid;
  if(mysql_query(db_conn, sql.str().c_str()))
  {
    message("Error printing! ");
    return;
  }
  rset = mysql_use_result(db_conn);
  cout << setw(122) << setfill('-') << "-" << endl;
  cout << "|" << left << setw(30) << setfill(' ') << "Entry Title" <<  "|"
       << left << setw(5) << setfill(' ') << "Year" <<  "|"
       << left << setw(15) << setfill(' ') << "Entry Format" << "|"
       << left << setw(5) << setfill(' ') << "EID" << "|"
       << left << setw(30) << setfill(' ') << "Entry Label" << "|"
       << left << setw(30) << setfill(' ') << "Collection Title" << "|" << endl;
  cout << setw(122) << setfill('-') << "-" << endl;
  if(rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
       cout << "|" << left << setw(30) << setfill(' ') << rows[0] <<  "|"
       << left << setw(5) << setfill(' ') << rows[1] <<  "|"
       << left << setw(15) << setfill(' ') << rows[2] << "|"
       << left << setw(5) << setfill(' ') << rows[3] << "|"
       << left << setw(30) << setfill(' ') << rows[4] << "|"
       << left << setw(30) << setfill(' ') << rows[5] << "|" << endl;
    }
  }
  cout << setw(122) << setfill('-') << "-" << endl;
  mysql_free_result(rset);
}
void Functions::printTracksFromEntry(int eid)
{
  MYSQL_RES* rset;
  MYSQL_ROW rows;
  stringstream sql;
  sql << "SELECT Track_number, Track_title, Track_length, Track_ID, Entry_title FROM Track,Entry "
                   << "WHERE Entry.Entry_ID=Track.Entry_ID AND Entry.Entry_ID=" << eid;
  if(mysql_query(db_conn, sql.str().c_str()))
  {
    message("Error printing! ");
    return;
  }
  rset = mysql_use_result(db_conn);
  cout << setw(124) << setfill('-') << "-" << endl;
  cout << "|" << left << setw(13) << setfill(' ') << "Track Number" <<  "|"
       << left << setw(50) << setfill(' ') << "Track Title" <<  "|"
       << left << setw(7) << setfill(' ') << "Length" << "|"
       << left << setw(5) << setfill(' ') << "TID" << "|"
       << left << setw(43) << setfill(' ') << "Entry Title" << "|" << endl;
  cout << setw(124) << setfill('-') << "-" << endl;
  if(rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
       cout << "|" << left << setw(13) << setfill(' ') << rows[0] <<  "|"
       << left << setw(50) << setfill(' ') << rows[1] <<  "|"
       << left << setw(7) << setfill(' ') << rows[2] << "|"
       << left << setw(5) << setfill(' ') << rows[3] << "|"
       << left << setw(43) << setfill(' ') << rows[4] << "|" << endl;
    }
  }
  cout << setw(124) << setfill('-') << "-" << endl;
  mysql_free_result(rset);
}


void Functions::printArtistFromEntry(int eid)
{
  MYSQL_RES* rset;
  MYSQL_ROW rows;
  stringstream sql;
  sql << "SELECT Artist.Artist_name, Artist.Artist_ID, Entry.Entry_title FROM Entry,Artist "
                   << "WHERE Entry.Entry_ID=Artist.Entry_ID AND Artist.Entry_ID=" << eid;
  if(mysql_query(db_conn, sql.str().c_str()))
  {
    message("Error printing! ");
    return;
  }
  rset = mysql_use_result(db_conn);
  cout << setw(105) << setfill('-') << "-" << endl;
  cout << "|" << left << setw(48) << setfill(' ') << "Artist Name" <<  "|"
       << left << setw(5) << setfill(' ') << "AID" <<  "|"
       << left << setw(48) << setfill(' ') << "Entry Title" << "|" <<endl;
  cout << setw(105) << setfill('-') << "-" << endl;
  if(rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
       cout << "|" << left << setw(48) << setfill(' ') << rows[0] <<  "|"
           << left << setw(5) << setfill(' ') << rows[1] <<  "|"
           << left << setw(48) << setfill(' ') << rows[2] << "|" << endl;
    }
  }
  cout << setw(105) << setfill('-') << "-" << endl;
  mysql_free_result(rset);
}


void Functions::printEntryGenre(int eid)
{
  MYSQL_RES* rset;
  MYSQL_ROW rows;
  stringstream sql;
  sql << "SELECT Entry.Entry_title, Entry.Entry_ID, Entry_Genre.Genre FROM Entry, Entry_Genre"
                   << " WHERE Entry.Entry_ID=Entry_Genre.Entry_ID AND Entry.Entry_ID=" << eid;
  if(mysql_query(db_conn, sql.str().c_str()))
  {
    message("Error printing! ");
    return;
  }
  rset = mysql_use_result(db_conn);
  cout << setw(109) << setfill('-') << "-" << endl;
  cout << "|" << left << setw(50) << setfill(' ') << "Entry Title" <<  "|"
       << left << setw(5) << setfill(' ') << "EID" <<  "|"
       << left << setw(50) << setfill(' ') << "Entry Genre" << "|" <<endl;
  cout << setw(109) << setfill('-') << "-" << endl;
  if(rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
       cout << "|" << left << setw(50) << setfill(' ') << rows[0] <<  "|"
           << left << setw(5) << setfill(' ') << rows[1] <<  "|"
           << left << setw(50) << setfill(' ') << rows[2] << "|" << endl;
    }
  }
  cout << setw(109) << setfill('-') << "-" << endl;
  mysql_free_result(rset);
}


void Functions::printTrackGenre(int tid)
{
  MYSQL_RES* rset;
  MYSQL_ROW rows;
  stringstream sql;
  sql << "SELECT Track.Track_title, Track.Track_ID, Track_Genre.Genre FROM Track,Track_Genre "
                   << " WHERE Track.Track_ID=Track_Genre.Track_ID AND Track.Track_ID=" << tid;
  if(mysql_query(db_conn, sql.str().c_str()))
  {
    message("Error printing! ");
    return;
  }
  rset = mysql_use_result(db_conn);
  cout << setw(109) << setfill('-') << "-" << endl;
  cout << "|" << left << setw(50) << setfill(' ') << "Track Title" <<  "|"
       << left << setw(5) << setfill(' ') << "TID" <<  "|"
       << left << setw(50) << setfill(' ') << "Track Genre" << "|" <<endl;
  cout << setw(109) << setfill('-') << "-" << endl;
  if(rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
       cout << "|" << left << setw(50) << setfill(' ') << rows[0] <<  "|"
           << left << setw(5) << setfill(' ') << rows[1] <<  "|"
           << left << setw(50) << setfill(' ') << rows[2] << "|" << endl;
    }
  }
  cout << setw(109) << setfill('-') << "-" << endl;
  mysql_free_result(rset);
}


void Functions::printArtistMembersFromArtist(int aid)
{
  MYSQL_RES* rset;
  MYSQL_ROW rows;
  stringstream sql;
  sql << "SELECT Artist.Artist_name, Artist.Artist_ID, Artist_members.Member_name FROM Artist, Artist_members "
                   << " WHERE Artist.Artist_ID=Artist_members.Artist_ID AND Artist.Artist_ID=" << aid;
    if(mysql_query(db_conn, sql.str().c_str()))
  {
    message("Error printing! ");
    return;
  }
  rset = mysql_use_result(db_conn);
  cout << setw(109) << setfill('-') << "-" << endl;
  cout << "|" << left << setw(50) << setfill(' ') << "Artist Name" <<  "|"
       << left << setw(5) << setfill(' ') << "AID" <<  "|"
       << left << setw(50) << setfill(' ') << "Artist Member" << "|" <<endl;
  cout << setw(109) << setfill('-') << "-" << endl;
  if(rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
      cout << "|" << left << setw(50) << setfill(' ') << rows[0] <<  "|"
           << left << setw(5) << setfill(' ') << rows[1] <<  "|"
           << left << setw(50) << setfill(' ') << rows[2] << "|" << endl;
    }
  }
  cout << setw(109) << setfill('-') << "-" << endl;
  mysql_free_result(rset);
}


//////////////////////////////////////////////////////////


void Functions::message(string msg)
{
  cout << msg << endl;
}
