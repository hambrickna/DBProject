
#include "tables.h"

#include <string>
using std::string;
#include <cstring>

User_::User_(int id,string name)
{
  setUserID(id);
  setUserName(name);
}
void User_::setUserID(int id)
{
  UserID=id;
}
void User_::setUserName(string name)
{
  const char* fn = name.data();
  int len = name.size();
  len = (len < MAX_SIZE ? len : MAX_SIZE - 1);
  strncpy(UserName, fn, len);
  UserName[len] = '\0';
}
int User_::getUserID() const
{
  return UserID;
}
string User_::getUserName() const
{
  return UserName;
}

Collection::Collection(string name, int cid, int uid)
{
  setCollectionTitle(name);
  setCollectionID(cid);
  setUserID(uid);
}
void Collection::setCollectionTitle(string name)
{
  const char* fn = name.data();
  int len = name.size();
  len = (len < MAX_SIZE ? len : MAX_SIZE - 1);
  strncpy(CollectionTitle, fn, len);
  CollectionTitle[len] = '\0';
}
void Collection::setCollectionID(int id)
{
  CollectionID=id;
}
void Collection::setNumEntries(int num)
{
  NumEntries=num;
}
void Collection::setUserID(int id)
{
  UserID=id;
}
string Collection::getCollectionTitle()
{
  return CollectionTitle;
}
int Collection::getCollectionID()
{
  return CollectionID;
}
int Collection::getNumEntries()
{
  return NumEntries;
}
int Collection::getUserID()
{
  return UserID;
}
Entry::Entry(string title, int year, string format, string condition, int upc, string label, int cid)
{
  setEntryTitle(title);
  setYear(year);
  setEntryFormat(format);
  setEntryCondition(condition);
  setEntryUPC(upc);
  setEntryLabel(label);
  setCollectionID(cid);
}
void Entry::setEntryTitle(string title)
{
  const char* fn = title.data();
  int len = title.size();
  len = (len < MAX_SIZE ? len : MAX_SIZE - 1);
  strncpy(EntryTitle, fn, len);
  EntryTitle[len] = '\0';
}
void Entry::setYear(int year)
{
  EntryYear=year;
}

void Entry::setCollectionID(int cid)
{
  CollectionID = cid;
}
void Entry::setEntryFormat(string format)
{
  const char* fn = format.data();
  int len = format.size();
  len = (len < MAX_SIZE ? len : MAX_SIZE - 1);
  strncpy(EntryFormat, fn, len);
  EntryFormat[len] = '\0';
}
void Entry::setEntryCondition(string condition)
{
  const char* fn = condition.data();
  int len = condition.size();
  len = (len < 9 ? len : 9 - 1);
  strncpy(EntryCondition, fn, len);
  EntryCondition[len] = '\0';
}
void Entry::setEntryUPC(int upc)
{
  EntryUPC=upc;
}
void Entry::setEntryLabel(string label)
{
  const char* fn = label.data();
  int len = label.size();
  len = (len < MAX_SIZE ? len : MAX_SIZE - 1);
  strncpy(EntryLabel, fn, len);
  EntryLabel[len] = '\0';
}

int Entry::getCollectionID()
{
  return CollectionID;
}
string Entry::getEntryTitle()
{
  return EntryTitle;
}
int Entry::getYear()
{
  return EntryYear;
}
string Entry::getEntryFormat()
{
  return EntryFormat;
}
string Entry::getEntryCondition()
{
  return EntryCondition;
}
int Entry::getEntryUPC()
{
  return EntryUPC;
}
string Entry::getEntryLabel()
{
  return EntryLabel;
}

Track::Track(int id, string title, int length, int num, int upc)
{
  setTrackID(id);
  setTrackTitle(title);
  setTrackLength(length);
  setTrackNumber(num);
  setEntryUPC(upc);
}
void Track::setTrackID(int id)
{
  TrackID=id;
}
void Track::setTrackTitle(string title)
{
  const char* ln = title.data();
  int len = title.size();
  len = (len < MAX_SIZE ? len : MAX_SIZE - 1);
  strncpy(TrackTitle, ln, len);
  TrackTitle[len] = '\0';
}
void Track::setTrackLength(int length)
{
  TrackLength=length;
}
void Track::setTrackNumber(int num)
{
  TrackNumber=num;
}
void Track::setEntryUPC(int upc)
{
  EntryUPC=upc;
}
int Track::getTrackID()
{
  return TrackID;
}
string Track::getTrackTitle()
{
  return TrackTitle;
}
int Track::getTrackLength()
{
  return TrackLength;
}
int Track::getTrackNumber()
{
  return TrackNumber;
}
int Track::getEntryUPC()
{
  return EntryUPC;
}

Artist::Artist(int id, string name, int upc)
{
  setArtistID(id);
  setArtistName(name);
  setEntryUPC(upc);
}
void Artist::setArtistID(int id)
{
  ArtistID=id;
}
void Artist::setArtistName(string name)
{
  const char* ln = name.data();
  int len = name.size();
  len = (len < MAX_SIZE ? len : MAX_SIZE - 1);
  strncpy(ArtistName, ln, len);
  ArtistName[len] = '\0';
}
void Artist::setEntryUPC(int upc)
{
  EntryUPC = upc;
}
int Artist::getEntryUPC()
{
  return EntryUPC;
}
int Artist::getArtistID()
{
  return ArtistID;
}
string Artist::getArtistName()
{
  return ArtistName;
}

Entry_Genre::Entry_Genre(int upc, string genre)
{
  setEntryUPC(upc);
  setGenre(genre);
}
void Entry_Genre::setEntryUPC(int upc)
{
  EntryUPC=upc;
}
void Entry_Genre::setGenre(string genre)
{
  const char* ln = genre.data();
  int len = genre.size();
  len = (len < MAX_SIZE ? len : MAX_SIZE - 1);
  strncpy(Genre, ln, len);
  Genre[len] = '\0';
}
int Entry_Genre::getEntryUPC()
{
  return EntryUPC;
}
string Entry_Genre::getGenre()
{
  return Genre;
}

Track_Genre::Track_Genre(int id, string genre)
{
  setTrackID(id);
  setTrack(genre);
}
void Track_Genre::setTrackID(int id)
{
  TrackID=id;
}
void Track_Genre::setTrack(string genre)
{
  const char* ln = genre.data();
  int len = genre.size();
  len = (len < MAX_SIZE ? len : MAX_SIZE - 1);
  strncpy(Genre, ln, len);
  Genre[len] = '\0';
}
int Track_Genre::getTrackID()
{
  return TrackID;
}
string Track_Genre::getGenre()
{
  return Genre;
}

Artist_members::Artist_members(int ID, string members)
{
  setArtistID(ID);
  setArtistMembers(members);
}

void Artist_members::setArtistID(int ID)
{
  ArtistID = ID;
}

void Artist_members::setArtistMembers(string members)
{
  const char* m = members.data();
  int len = members.size();
  len = (len < MAX_SIZE ? len : MAX_SIZE - 1);
  strncpy(ArtistMembers, m, len);
  ArtistMembers[len] = '\0';
}

int Artist_members::getArtistID()
{
  return ArtistID;
}

string Artist_members::getArtistMembers()
{
  return ArtistMembers;
}

Collection_contains_entry::Collection_contains_entry(int CollectionID, int EntryUPC)
{
  setCollectionID(CollectionID);
  setEntryUPC(EntryUPC);
}

void Collection_contains_entry::setCollectionID(int id)
{
  CollectionID = id;
}

void Collection_contains_entry::setEntryUPC(int upc)
{
  EntryUPC = upc;
}

int Collection_contains_entry::getCollectionID()
{
  return CollectionID;
}

int Collection_contains_entry::getEntryUPC()
{
  return EntryUPC;
}
 //Collection Contains Entry

//am back
//ok
