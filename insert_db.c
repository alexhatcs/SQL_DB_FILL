#include <stdio.h>
#include "sqlite3.c"
#include <time.h>
#include <stdlib.h>


static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char* argv[]) {
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char* sql;

   rc = sqlite3_open("d", &db);

   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }

   int i;
   for (i = 0;i < 99; i++) {

   		sql = "INSERT INTO Event(event_id, event_name, event_date, host_id, host_zip, host_country, host_telephone, host_state, host_city) "
   			  "VALUES (abs(random() % 10000), 'First', '2020-12-02 17:30', 5555, 32901, 'US', abs(random()) % 9000000000 + 95000000, 'FL', 'Melbourne');"
			  "INSERT INTO Venue(venue_id, venue_name, venue_address, venue_contact, zip_code, country, state, city, event_id) "
			  "VALUES (abs(random() % 10000), 'Civic Ctr', '500 Main St', abs(random()) % 9000000000 +95000000, abs(random()) % 90000 + 9950, 'US', 'CA', 'Los Angeles', last_insert_rowid());"
			  "INSERT INTO Author(author_id, author_name, author_company, author_address, zip_code, country, state, city, venue_id) "
			  "VALUES (abs(random() % 10000), 'George R.R. Martin', 'Dragon Publishing LLC', '200 Main St', abs(random()) % 90000 + 9950, 'US', 'CA', 'Los Angeles', last_insert_rowid()); "
			  "INSERT INTO Paper(paper_id, paper_word_count, paper_name, paper_title, author_id, editor_id, editor_contact, zip_code) "
			  "VALUES (abs(random() % 10000), 2003, 'Game of Thrones I', 'Let the Games Begin', last_insert_rowid(), abs(random()) % 10000, abs(random()) % 9000000000 + 95000000, abs(random()) % 90000 + 9950);"
			  "INSERT INTO Reviewer(reviewer_id, reviewer_address, reviewer_name, reviewer_contact, zip_code, country, state, city, paper_id) "
			  "VALUES (abs(random() % 10000), '1321 State Rd', 'David', abs(random()) % 9000000000 +95000000, abs(random()) % 90000 + 9950, 'US', 'ME', 'Eliot', last_insert_rowid());"
			  "INSERT INTO Chair(chair_name, committee, responsibility, head, reviewer_id) "
			  "VALUES ('Setup', 'Alex, Parthil', 'Setup event', 'Dr. Silaghi', last_insert_rowid());";
			  
			  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   }
   

	if(rc != SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Records created successfully\n");
	}
   sqlite3_close(db);
   return 0;
}