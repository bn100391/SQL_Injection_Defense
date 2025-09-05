all: fixsqlinjection

fixsqlinjection: main.c fixsqlinjection.c sqlite3.c sqlite3.h
	$(CC) -g -Wall -Wextra -o $@ $^

clean:
	rm -f fixsqlinjection
