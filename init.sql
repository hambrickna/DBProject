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
		FOREIGN KEY(Entry_ID) REFERENCES Track(Entry_ID)
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
   values ("Bob", 001), ("Dave", 002), ("PianoMan", 003), ("Music Store", 004);

INSERT INTO Collection(Collection_Title, Collection_ID, User_ID)
   values ("Vinyls", 200, 001), ("Rock Mix", 201, 001), ("Pop Mix",
		        202, 001), ("Emo Mix", 203, 001), ("My mix", 204, 002),
					("Store1 Collection", 205, 004);
