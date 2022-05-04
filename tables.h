#ifndef TABLES_H
#define TABLES_H

#include <string>
using std::string;

const int MAX_SIZE = 50;
const string HEADER = "--------------------------------------------------------------------";

class User_
{
  public:
    User_(int id=0,string name="");
    ~User_();
    void setUserID(int id);
    void setUserName(string name);
    int getUserID() const;
    string getUserName() const;

  private:
    int UserID;
    char UserName[MAX_SIZE];
};

class Collection
{
  public:
    Collection(string name="", int cid=0, int uid=0);
    ~Collection();
    void setCollectionTitle(string name);
    void setCollectionID(int id);
    void setNumEntries(int num);
    void setUserID(int id);
    string getCollectionTitle();
    int getCollectionID();
    int getNumEntries();
    int getUserID();
  private:
    char CollectionTitle[MAX_SIZE];
    int CollectionID;
    int NumEntries;
    int UserID;
};

class Entry
{
  public:
    Entry(string title="", int year=0, string format="", string condition="Fair", int eid=0, string label="", int cid=0);
    ~Entry();
    void setEntryTitle(string title);
    void setYear(int year);
    void setEntryFormat(string format);
    void setEntryCondition(string condition);
    void setEntryID(int eid);
    void setEntryLabel(string label);
    void setCollectionID(int cid);
    string getEntryTitle();
    int getYear();
    string getEntryFormat();
    string getEntryCondition();
    int getEntryID();
    string getEntryLabel();
    int getCollectionID();

  private:
    char EntryTitle[MAX_SIZE];
    int EntryYear;
    char EntryFormat[MAX_SIZE];
    char EntryCondition[9];
    int EntryID;
    char EntryLabel[MAX_SIZE];
    int CollectionID;
};

class Track
{
  public:
    Track(int id=0, string title="", int length=0, int num=0, int eid=0);
    ~Track();
    void setTrackID(int id);
    void setTrackTitle(string title);
    void setTrackLength(int length);
    void setTrackNumber(int num);
    void setEntryID(int eid);
    int getTrackID();
    string getTrackTitle();
    int getTrackLength();
    int getTrackNumber();
    int getEntryID();
  private:
    int TrackID;
    char TrackTitle[MAX_SIZE];
    int TrackLength;
    int TrackNumber;
    int EntryID;
};

class Artist
{
  public:
    Artist(int id=0, string name="", int eid=0);
    ~Artist();
    void setArtistID(int id);
    void setArtistName(string name);
    void setEntryID(int eid);
    int getEntryID();
    int getArtistID();
    string getArtistName();
  private:
    int ArtistID;
    char ArtistName[MAX_SIZE];
    int EntryID;
};

class Entry_Genre
{
  public:
    Entry_Genre(int eid=0, string genre="");
    ~Entry_Genre();
    void setEntryID(int eid);
    void setGenre(string genre);
    int getEntryID();
    string getGenre();
  private:
    int EntryID;
    char Genre[MAX_SIZE];
};

class Track_Genre
{
  public:
    Track_Genre(int id=0, string genre="");
    ~Track_Genre();
    void setTrackID(int id);
    void setTrack(string genre);
    int getTrackID();
    string getGenre();
  private:
    int TrackID;
    char Genre[MAX_SIZE];
};

class Artist_members
{
  public:
    Artist_members(int ID=0, string members="");
    ~Artist_members();
    void setArtistID(int ID);
    void setArtistMembers(string member);
    int getArtistID();
    string getArtistMembers();
  private:
    int ArtistID;
    char ArtistMembers[MAX_SIZE];
};


#endif
