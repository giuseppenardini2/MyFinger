/**
 * This source file contains implementations of the "users_finder.h" functions.
 *
 * @author peppo02
 */

#include "users_finder.h"


/**
 * This function searches for logged users, populates a 'User' struct with found
 * user information of each logged user and add each 'User' struct to a 'Users' struct.
 *
 * @param args The 'Arguments' struct for the 'finger' command arguments.
 * @param users The 'Users' struct to store 'User' struct of the logged users.
 */
void find_logged_users(struct Arguments *args, struct Users *users){
	struct utmp* utmp_entry;
	setutent();
	utmp_entry=getutent();
	while(utmp_entry!=NULL){ //Iterate through each entry in the utmp file to find logged-in users.
		if(utmp_entry->ut_type!=USER_PROCESS){ //Ignore non-user processes
			utmp_entry=getutent();
			continue;
		}
		struct passwd *passwd_entry=find_user_passwd(utmp_entry->ut_user, !args->m_argument); //Retrieve the user entry from the passwd file.

		char *email_path=NULL;
		email_path=find_user_email(passwd_entry->pw_name); //Retrieve the path of the user's .mail file.

		char *pgpkey_path=NULL;
		char *project_path=NULL;
		char *plan_path=NULL;
		if(args->formatting==LONG_F && args->p_argument==false){ //If the formatting type is 'l' and 'p' argument has not been provided.
			pgpkey_path=find_user_pgpkey(passwd_entry->pw_name); //Retrieve the path of the user's .pgpkey file.
			project_path=find_user_project(passwd_entry->pw_name); //Retrieve the path of the user's .project file.
			plan_path=find_user_plan(passwd_entry->pw_name); //Retrieve the path of the user's .plan file.
		}

		struct User *user=initialize_user(); //Initialize a 'User' struct.
		set_user_information(args, user, passwd_entry, utmp_entry, email_path, pgpkey_path, project_path, plan_path); //Populate the 'User' struct with found user information.
		add_user(users, user); //Add the 'User' struct to 'Users' struct.

		free(email_path);
		free(pgpkey_path);
		free(project_path);
		free(plan_path);

		utmp_entry=getutent();
	}
	endutent();
}

/**
 * This function searches for the users to find, populates a 'User' struct with found
 * user information of each logged user and add each 'User' struct to a 'Users' struct.
 *
 * @param args The 'Arguments' struct for the 'finger' command arguments.
 * @param users The 'Users' struct for the users found.
 * @param users_not_found The 'Usernames' struct for the users not found.
 */
void find_users(struct Arguments *args, struct Users *users, struct Usernames *users_not_found){
	for(size_t i=0; i<args->users_to_find->size; i++){
		struct passwd *passwd_entry=find_user_passwd(args->users_to_find->usernames[i], !args->m_argument); //Retrieve the user entry from the passwd file.
		if(passwd_entry==NULL){ //If the user entry from passwd file has not been found, I add the user to the 'Usernames' struct for the users not found.
			add_username(users_not_found, args->users_to_find->usernames[i]);
			continue;
		}
		if(is_user_in_users(users, passwd_entry->pw_name)==true) //Else if the user has been already added to the 'Users' struct for the users found, continue.
			continue;
		struct utmp *utmp_entry=find_user_utmp(passwd_entry->pw_name); //Retrieve the user entry from the passwd file.

		char *email_path=NULL;
		email_path=find_user_email(passwd_entry->pw_name); //Retrieve the path of the user's .mail file.

		char *pgpkey_path=NULL;
		char *project_path=NULL;
		char *plan_path=NULL;
		if(args->formatting==LONG_F && args->p_argument==false){ //If the formatting type is 'l' and 'p' argument has not been provided.
			pgpkey_path=find_user_pgpkey(passwd_entry->pw_name); //Retrieve the path of the user's .pgpkey file.
			project_path=find_user_project(passwd_entry->pw_name); //Retrieve the path of the user's .project file.
			plan_path=find_user_plan(passwd_entry->pw_name); //Retrieve the path of the user's .plan file.
		}

		struct User *user=initialize_user(); //Initialize a 'User' struct.
		set_user_information(args, user, passwd_entry, utmp_entry, email_path, pgpkey_path, project_path, plan_path); //Populate the 'User' struct with found user information.
		add_user(users, user); //Add the 'User' struct to 'Users' struct.

		free(email_path);
		free(pgpkey_path);
		free(project_path);
		free(plan_path);
	}
}

/**
 * This functions searches for the user entry from the passwd file in a
 * case-insensitive way using a username or name.
 *
 * @param username The user username.
 * @param bool name If including the name in the search.
 * @return A pointer to the 'passwd' struct for the user entry.
 */
struct passwd *find_user_passwd(char *username, bool name){
	setpwent();
	struct passwd *passwd_entry=getpwnam(username); //Search for the user entry through getpawnam().
	if(passwd_entry!=NULL){ //If the user entry has been found, return it.
		endpwent();
		return passwd_entry;
	}
	setpwent();
	passwd_entry=getpwent();
	while(passwd_entry!=NULL){ //Else iterate the passwd file to search the user entry.
		if(compare_case_insensitive_strings(username, passwd_entry->pw_name)) //Search for the user entry in a case-insensitive way using its username.
			return passwd_entry;
		char gecos_copy[strlen(passwd_entry->pw_gecos)];
		strcpy(gecos_copy, passwd_entry->pw_gecos);
		if(name==true && compare_case_insensitive_strings(username, strtok(gecos_copy, ","))) //If the 'm' argument is false, search for the user entry in a case-insensitive way using its username.
			return passwd_entry;
		passwd_entry=getpwent();
	}
	endpwent();
	return NULL;
}

/**
 * This functions retrieves the user entry from the utmp file based on a
 * username.
 *
 * @param username The user username.
 * @return A pointer to the 'utmp' struct for the user entry.
 */
struct utmp *find_user_utmp(char *username){
	setutent();
	struct utmp *utmp_entry=getutent();
	while(utmp_entry!=NULL){ //Iterate the utmp file to search for the user entry.
		if(strcmp(username, utmp_entry->ut_user)==0)
			return utmp_entry;
		utmp_entry=getutent();
	}
	endutent();
	return NULL;
}

/**
 * This function retrieves the path of a user's .mail file.
 *
 * @param username The user username.
 * @return A pointer to the path of the user's .mail file. If
 * the file does not exists, the return value is NULL.
 */
char *find_user_email(char *username){
	char *mail_path=(char*)malloc(256*sizeof(char));
	if(mail_path==NULL){
		perror("malloc() error for mail_path");
		exit(EXIT_FAILURE);
	}
	strcpy(mail_path, "/var/mail/"); //Build the file path.
	strcat(mail_path, username);
	if(access(mail_path, F_OK)!=-1) //Checks if the file exists.
		return mail_path;
	free(mail_path);
	return NULL;
}

/**
 * This function retrieves the path of a user's .pgpkey file.
 *
 * @param username The user username.
 * @return A pointer to the path of the user's .pgpkey file. If
 * the file does not exists, the return value is NULL.
 */
char *find_user_pgpkey(char *username){
	char *pgpkey_path=(char*)malloc(256*sizeof(char));
	if(pgpkey_path==NULL){
		perror("malloc() error for pgpkey_path");
		exit(EXIT_FAILURE);
	}
	strcpy(pgpkey_path, "/home/"); //Build the file path.
	strcat(pgpkey_path, username);
	strcat(pgpkey_path, "/.pgpkey");
	if(access(pgpkey_path, R_OK)!=-1) //Check if the file exists.
		return pgpkey_path;
	return NULL;
}

/**
 * This function retrieves the path of a user's .project file.
 *
 * @param username The user username.
 * @return A pointer to the path of the user's .project file. If
 * the file does not exists, the return value is NULL.
 */
char *find_user_project(char *username){
	char *project_path=(char*)malloc(256*sizeof(char));
	if(project_path==NULL){
		perror("malloc() error for project_path");
		exit(EXIT_FAILURE);
	}
	strcpy(project_path, "/home/"); //Build the file path.
	strcat(project_path, username);
	strcat(project_path, "/.project");
	if(access(project_path, R_OK)!=-1) //Check if the file path exists.
			return project_path;
	return NULL;
}

/**
 * This function retrieves the path of a user's .plan file.
 *
 * @param username The user username.
 * @return A pointer to the path of the user's .plan file. If
 * the file does not exists, the return value is NULL.
 */
char *find_user_plan(char *username){
	char *plan_path=(char*)malloc(256*sizeof(char));
	if(plan_path==NULL){
		perror("malloc() error for plan_path");
		exit(EXIT_FAILURE);
	}
	strcpy(plan_path, "/home/"); //Build the file path.
	strcat(plan_path, username);
	strcat(plan_path, "/.plan");
	if(access(plan_path, R_OK)!=-1) //Check the file path.
		return plan_path;
	return NULL;
}
