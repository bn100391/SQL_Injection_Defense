#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sqlite3.h"

int q(sqlite3 *db, const char *param);

int main(int argc, char *argv[])
{
	int rc, exitcode = EXIT_FAILURE;
	sqlite3 *db = NULL;
	char insert[BUFSIZ], param[BUFSIZ];
	sqlite3_stmt *stmt = NULL;

	rc = sqlite3_open(":memory:", &db);	
	if (rc != SQLITE_OK) {
		fprintf(stderr, "error opening database: %s\n", sqlite3_errmsg(db));
		goto done;
	}

	rc = sqlite3_exec(db, "CREATE TABLE public ( user STRING, password STRING )", 0, 0, 0);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "error creating public table: %s\n", sqlite3_errmsg(db));
		goto done;
	}

	if (argc == 2) {
		/* Allow setting password for testing by Aquinas. */
		snprintf(insert, sizeof insert, "INSERT INTO public (user, password) VALUES ( 'admin', '%s' );", argv[1]);
	} else {
		strcpy(insert, "INSERT INTO public (user, password) VALUES ( 'admin', '***' );");
	}

	rc = sqlite3_exec(db, insert, 0, 0, 0);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "error inserting into public table: %s\n", sqlite3_errmsg(db));
		goto done;
	}

	rc = sqlite3_exec(db, "CREATE TABLE secret ( user STRING, password STRING )", 0, 0, 0);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "error creating secret table: %s\n", sqlite3_errmsg(db));
		goto done;
	}

	if (argc == 2) {
		/* Allow setting password for testing by Aquinas. */
		snprintf(insert, sizeof insert, "INSERT INTO secret (user, password) VALUES ( 'admin', '%s' );", argv[1]);
	} else {
		strcpy(insert, "INSERT INTO secret (user, password) VALUES ( 'admin', 'password' );");
	}

	rc = sqlite3_exec(db, insert, 0, 0, 0);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "error inserting into secret table: %s\n", sqlite3_errmsg(db));
		goto done;
	}

	printf("Enter user: ");
	fflush(stdout);
	fgets(param, sizeof param, stdin);
	param[strlen(param) - 1] = '\0';

	rc = q(db, param);
	if (-1 == rc) {
		goto done;
	}

	exitcode = EXIT_SUCCESS;

done:
	if (db != NULL) {
	}

	if (stmt != NULL) {
		sqlite3_finalize(stmt);
	}

	exit(exitcode);
}
