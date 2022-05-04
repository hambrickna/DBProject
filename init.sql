CREATE DATABASE MusicCollection;

USE DATABASE MusicCollection;

CREATE TABLE User_(
	User_name VARCHAR(50) NOT NULL,
    User_ID INT UNSIGNED NOT NULL,
    PRIMARY KEY(User_ID)
);

CREATE TABLE Collection(
    Collection_Title VARCHAR(50) NOT NULL,
    Collection_ID INT UNSIGNED NOT NULL,
    User_ID INT UNSIGNED NOT NULL,
    PRIMARY KEY(Collection_ID),
    FOREIGN KEY(User_ID) REFERENCES User_(User_ID)
);

CREATE TABLE Entry(
	Entry_title VARCHAR(50) NOT NULL,
    Entry_year INT UNSIGNED NOT NULL,
    Entry_format VARCHAR(50) NOT NULL,
    Entry_condition VARCHAR(10),
    Entry_ID INT UNSIGNED NOT NULL,
    Entry_label VARCHAR(50) NOT NULL,
		Collection_ID INT UNSIGNED NOT NULL,
    CHECK(Entry_condition='Very Good' OR Entry_condition='Good' OR Entry_condition='Fair'
			OR Entry_condition='Poor' OR Entry_condition='Very Poor'),
    PRIMARY KEY(Entry_ID),
		FOREIGN KEY(Collection_ID) REFERENCES Collection(Collection_ID)
);

CREATE TABLE Track(
	Track_ID INT UNSIGNED NOT NULL,
	Track_title VARCHAR(50) NOT NULL,
    Track_length INT UNSIGNED NOT NULL, #Unit Seconds
    Track_number INT UNSIGNED NOT NULL,
    Entry_ID INT UNSIGNED NOT NULL,
    PRIMARY KEY(Track_ID),
    FOREIGN KEY(Entry_ID) REFERENCES Entry(Entry_ID)
);

CREATE TABLE Artist(
	Artist_ID INT UNSIGNED NOT NULL,
    Artist_name VARCHAR(50) NOT NULL,
		Entry_ID INT UNSIGNED NOT NULL,
    PRIMARY KEY(Artist_ID),
		FOREIGN KEY(Entry_ID) REFERENCES Entry(Entry_ID)
);

CREATE TABLE Entry_Genre(
	Entry_ID INT UNSIGNED NOT NULL,
    Genre VARCHAR(50) NOT NULL,
    FOREIGN KEY(Entry_ID) REFERENCES Entry(Entry_ID)
);

CREATE TABLE Track_Genre(
	Track_ID INT UNSIGNED NOT NULL,
    Genre VARCHAR(50) NOT NULL,
    FOREIGN KEY(Track_ID) REFERENCES Track(Track_ID)
);

CREATE TABLE Artist_members(
	Artist_ID INT UNSIGNED NOT NULL,
    Member_name VARCHAR(50) NOT NULL,
    FOREIGN KEY(Artist_ID) REFERENCES Artist(Artist_ID)
);



#Example Data

INSERT INTO User_(User_name, User_ID)
   values ("Rock Shop", 1);

INSERT INTO Collection(Collection_Title, Collection_ID, User_ID)
   values ("Store's Collection", 200, 1);

INSERT INTO Entry(Entry_title, Entry_year, Entry_format, Entry_condition, Entry_ID, Entry_label, Collection_ID)
   values ("Dark Side of the Moon", 1973, "Album", 'Very Good', 300, "Harvester Records", 200),
	        ("The Wall", 1979, "Album", 'Fair', 301, "Harvester Records", 200),
					("Wish You Were Here", 1975, "Album", 'Good', 302, "Harvester Records", 200),
					("2112", 1976, "Album", 'Very Good', 303, "Toronto Sound", 200);

INSERT INTO Track(Track_ID, Track_title, Track_length, Track_number, Entry_ID)
   values (400, "Speak to Me / Breathe", 238, 1, 300),
	        (401, "On the Run", 205, 2, 300),
					(402, "Time", 425, 3, 300),
					(403, "The Great Gig in the Sky", 284, 4, 300),
					(404, "In the Flesh?", 200, 1, 301),
					(405, "The Thin Ice", 210, 2, 301),
					(406, "Another Brick in the Wall", 191, 3, 301);

INSERT INTO Artist(Artist_ID, Artist_name, Entry_ID)
   values (500, "Pink Floyd", 300),
	        (501, "Pink Floyd", 301),
					(502, "Pink Floyd", 302);

INSERT INTO Entry_Genre(Entry_ID, Genre)
   values (300, "Psychedelic Rock"),
	        (301, "Rock Opera");

INSERT INTO Track_Genre(Track_ID, Genre)
   values (400, "Psychedelic Rock"),
	        (401, "Rock Opera"),
					(402, "Progressive Rock");

INSERT INTO Artist_members(Artist_ID, Member_name)
   values (500, "David Gilmour"), (500, "Roger Waters"), (500, "Syd Barrett"),
	        (500, "Richard Wright"), (500, "Nick Mason"), (500, "Bob Klose");
