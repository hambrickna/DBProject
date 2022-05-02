#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <mysql.h>
#include <string>

class User_;
class Collection;
class Entry;
class Track;
class Artist;
class Entry_Genre;
class Track_Genre;
class Artist_members;
class Collection_contains_entry;

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
    void createCollectionContainsEntry(Collection_contains_entry* cce);
    
    void deleteUser(int uid);
    void deleteCollection(int cid);
    void deleteEntry(int upc);
    void deleteTrack(int tid);
    void deleteArtist(int aid);
    void deleteEntryGenre(int upc);
    void deleteTrackGenre(int tid);
    void deleteArtistMembers(int aid);
    void deleteCollectionContainsEntry(int cid,int upc);

    User_* getUser(int uid);
    Collection* getCollection(int cid);
    Entry* getEntry(int upc);
    Track* getTrack(int tid);
    Artist* getArtist(int aid);
    Entry_Genre* getEntryGenre(int upc);
    Track_Genre* getTrackGenre(int tid);
    Artist_members* getArtistMembers(int aid);
    Collection_contains_entry* getCCE(int cid, int upc);

    void printAllUser();
    void printAllCollection();
    void printAllEntry();
    void printAllTrack();
    void printAllArtist();
    void printAllEntryGenre();
    void printAllTrackGenre();
    void printAllArtistMembers();
    void printAllCollectionContainsEntry();

    void printUser(int uid);
    void printCollectionsFromUser(int uid);
    void printEntriesFromCollection(int cid);//Add collectionid into entry on sql
    void printTracksFromEntry(int upc);
    void printArtistFromEntry(int upc);//Add upc into artist
    void printEntryGenre(int upc);
    void printTrackGenre(int tid);
    void printArtistMembersFromArtist(int aid);

    void message(string);
  private:
    MYSQL* db_conn;
};



#endif