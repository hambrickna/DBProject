#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <mysql/mysql.h>
#include <string>

class User_;
class Collection;
class Entry;
class Track;
class Artist;
class Entry_Genre;
class Track_Genre;
class Artist_members;


using namespace std;
class Functions
{
  public:
    Functions(string host, string user, string password, string database);
    ~Functions();
    void createUser(User_* user);
    void createCollection(Collection* collection);
    void createEntry(Entry* entry);
    void createTrack(Track* track);
    void createArtist(Artist* artist);
    void createEntryGenre(Entry_Genre* egen);
    void createTrackGenre(Track_Genre* tgen);
    void createArtistMembers(Artist_members* amem);


    void deleteUser(int uid);
    void deleteCollection(int cid);
    void deleteEntry(int eid);
    void deleteTrack(int tid);
    void deleteArtist(int aid);
    void deleteEntryGenre(int eid);
    void deleteTrackGenre(int tid);
    void deleteArtistMembers(int aid);
    void deleteOneArtistMember(string name);
    void deleteOneEntryGenre(string genre, int eid);
    void deleteOneTrackGenre(string genre, int tid);


    void deleteAllCollectionFromUser(int uid);
    void deleteAllEntryFromCollection(int cid);
    void deleteAllTrackFromEntry(int eid);
    void deleteAllTrackGenreFromEntry(int eid);
    void deleteAllArtistFromEntry(int eid);

    User_* getUser(int uid);
    Collection* getCollection(int cid);
    Entry* getEntry(int eid);
    Track* getTrack(int tid);
    Artist* getArtist(int aid);
    Entry_Genre* getEntryGenre(int eid);
    Track_Genre* getTrackGenre(int tid);
    Artist_members* getArtistMembers(int aid);


    void printAllUser();
    void printAllCollection();
    void printAllEntry();
    void printAllTrack();
    void printAllArtist();
    void printAllEntryGenre();
    void printAllTrackGenre();
    void printAllArtistMembers();

    void printUser(int uid);
    void printCollectionsFromUser(int uid);
    void printEntriesFromCollection(int cid);//Add collectionid into entry on sql
    void printTracksFromEntry(int eid);
    void printArtistFromEntry(int eid);//Add eid into artist
    void printEntryGenre(int eid);
    void printTrackGenre(int tid);
    void printArtistMembersFromArtist(int aid);

    void message(string);
    MYSQL* getConnection() {return db_conn;}
    string h; // Testing/debugging variable IGNORE
  private:
    MYSQL* db_conn;
};



#endif
