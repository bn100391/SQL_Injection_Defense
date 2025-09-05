#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

#include "sqlite3.h"


int q(sqlite3 *db, const char *param)
{
	int fnval = -1;
	const char s[] = "SELECT password FROM PUBLIC WHERE user = ?"; 

	//Create prepared statement. 
	sqlite3_stmt *ppStmt = NULL;  
	const char *pzTail = NULL;  
	int ps_r = sqlite3_prepare_v2(db, s, -1, &ppStmt, &pzTail);  
	if(ps_r != 0){
		printf("ERROR, creating prepared statemnt. Code: %d\n", ps_r);
	       	exit(1); 
	}
	if(ppStmt == NULL){
		printf("ERROR, prepared statement pointer NULL\n"); 
		exit(1); 
	}

	//Bind input value to prepared statement. 
	int bt = sqlite3_bind_text(ppStmt, 1, param, -1, SQLITE_STATIC);
	if(bt != 0){
		printf("ERROR, binding value to statment. Code: %d\n", bt); 
		exit(1); 
	}

	//Execute statement and retrieve data. 
	int exec_code = sqlite3_step(ppStmt);	
	if(exec_code != SQLITE_DONE && exec_code != SQLITE_ROW && exec_code != SQLITE_OK){
		printf("ERROR, executing statement: Code: %d\n", bt);
		exit(1); 
	
	}

	while(exec_code == SQLITE_DONE || exec_code == SQLITE_ROW || exec_code == SQLITE_OK){
		for(int c = 0; c < sqlite3_column_count(ppStmt); c++){	
			const unsigned char *psswd = sqlite3_column_text(ppStmt, c); 
			if(psswd != NULL){
				printf("password = %s\n", psswd); 
			}
		}
		if(exec_code == SQLITE_DONE || SQLITE_OK){
			break; 
		}
		exec_code = sqlite3_step(ppStmt); 
	}
			

	fnval = 0;

	return fnval;
}
