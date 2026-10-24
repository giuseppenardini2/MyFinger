/**
 * This source file contains implementations of the "users_builder.h" functions.
 *
 * @author peppo02
 */


#include <users_builder.h>

/**
 * This function populates a 'User' struct with user information retrieved
 * from the passwd file, utmp file, .mail file, .pgpkey file,
 * .project file and .plan file.
 *
 * @param args The 'Arguments' struct for the 'finger' command arguments.
 * @param user The 'User' struct to populate with user information.
 * @param passwd_entry The user entry from the passwd file.
 * @param utmp_entry The user entry from the utmp file.
 * @param email_path The path of the user's .mail file.
 * @param pgpkey_path The path of the user's .pgpkey file.
 * @param project_path The path of the user's .project file.
 * @param plan_path The path of the user's .plan file.
 */
void set_user_information(struct Arguments *args, struct User *user, struct passwd *passwd_entry, struct utmp *utmp_entry, char *email_path, char *pgpkey_path, char *project_path, char *plan_path){
	set_user_passwd_information(args->formatting, user, passwd_entry);
	set_user_utmp_information(user, utmp_entry);
	set_user_email(user, email_path);
	set_user_pgpkey(user, pgpkey_path);
	set_user_project(user, project_path);
	set_user_plan(user, plan_path);
}

/**
 * This function populates a 'User' struct with user information retrieved
 * from the passwd file.
 *
 * @param formatting The formatting type.
 * @param user The 'User' struct to populate with user information.
 * @param passwd_entry The user entry from the passwd file.
 */
void set_user_passwd_information(enum FormattingType formatting, struct User *user, struct passwd *passwd_entry){
	strcpy(user->username, passwd_entry->pw_name);
	char gecos_copy[strlen(passwd_entry->pw_gecos)];
	strcpy(gecos_copy, passwd_entry->pw_gecos);
	set_user_gecos(formatting, user, gecos_copy);
	if(formatting==LONG_F){ //If the formatting type is 'l', include the user directory and user shell as well.
		strcpy(user->directory, passwd_entry->pw_dir);
		strcpy(user->shell, passwd_entry->pw_shell);
	}
}

/**
 * This function populates a 'User' struct with the user information retrieved
 * from the gecos of the user entry from the passwd entry.
 *
 * @param formatting The formatting type.
 * @param user The 'User' struct to populate with user information.
 * @param gecos The user entry from the passwd file.
 */
void set_user_gecos(enum FormattingType formatting, struct User *user, char *gecos){
	user->real_name[0]='\0'; //Initialize the GECOS information to the 'User' struct.
	user->office_number[0]='\0';
	user->office_phone[0]='\0';
	user->home_phone[0]='\0';

	size_t gecos_part=0; //A counter that keeps track of the section of the GECOS field.
	char *field=strtok(gecos, ",");
	while(field!=NULL){
		if(gecos_part>2 && formatting==SHORT_F) //If the formatting type is 's', do not include the home phone number.
			return;
		switch(gecos_part){ //Set the GECOS information to the 'User' struct according to the current section of the GECOS field.
				case 0:
					strcpy(user->real_name, field);
					break;
				case 1:
					strcpy(user->office_number, field);
					break;
				case 2:
					strcpy(user->office_phone, field);
					break;
				case 3:
					strcpy(user->home_phone, field);
					break;
		}
		field=strtok(NULL, ",");
		gecos_part++;
	}
}

/**
 * This function populates a 'User' struct with user information retrieved
 * from the utmp file.
 *
 * @param user The 'User' struct to populate with user information.
 * @param utmp_entry The user entry from the utmp file.
 */
void set_user_utmp_information(struct User *user, struct utmp *utmp_entry){
	set_user_last_login(user, utmp_entry);
	set_user_device_name(user, utmp_entry);
	set_user_write_permission_device(user, utmp_entry);
	set_user_host(user, utmp_entry);
	set_user_idle_time(user, utmp_entry);
}

/**
 * This functions sets the user last login to a 'User' struct.
 * If the last login is less than six months from now, the last
 * login of the 'User' struct is set to 0.
 *
 * @param user The 'User' struct to set.
 * @param utmp_entry The user entry from the utmp file. If it
 * is NULL, the last login of the 'User' struct is set to 0.
 */
void set_user_last_login(struct User *user, struct utmp *utmp_entry){
	if(utmp_entry==NULL){ //If the entry from utmp file is NULL, set the last login of the 'User' struct to 0.
		user->last_login=0;
		return;
	}
	time_t last_login=utmp_entry->ut_tv.tv_sec; //Get the last login from user entry from the utmp file.
	time_t current_time=time(NULL);
	if(difftime(current_time, last_login)<15552000) //If the user last login is less than 6 months (=6*30*24*60*60 seconds) from now, copy it into the last login of the 'User' struct.
		user->last_login=last_login;
	else
		user->last_login=0; //Else set the last login of the 'User' struct to 0.
}

/**
 * This functions sets the user device name to a 'User' struct.
 *
 * @param user The 'User' struct to set.
 * @param utmp_entry The user entry from the utmp file. If it
 * is NULL, the first character of the device name of the 'User' struct
 * is set to '\0'.
 */
void set_user_device_name(struct User *user, struct utmp *utmp_entry){
	if(utmp_entry==NULL) //If the user entry from utmp file is NULL, set the first character of the device name of the 'User' struct to '\0'.
		user->device_name[0]='\0';
	else
		strcpy(user->device_name, utmp_entry->ut_line); //Else copy the device name into the 'User' struct.
}

/**
 * This functions sets the user write permission on the device file to a 'User'
 * struct.
 *
 * @param user The 'User' struct to set.
 * @param utmp_entry The user entry from the utmp file. If it is NULL, the
 * write permission device of the 'User' struct is set to false.
 */
void set_user_write_permission_device(struct User *user, struct utmp *utmp_entry){
	if(utmp_entry==NULL){ //If the user entry from utmp file is NULL, the write permission device of the 'User' struct is set to false.
		user->write_permission_device=false;
		return;
	}
	char tty_path[256]="/dev/"; //Build the device file path.
	strcat(tty_path, utmp_entry->ut_line);
	if(access(tty_path, W_OK)!=1) //Check the write permissions on the device file and copy it into the 'User' struct.
		user->write_permission_device=true;
	else
		user->write_permission_device=false;
}

/**
 * This functions sets the user host to a 'User' struct.
 *
 * @param user The 'User' struct to set.
 * @param utmp_entry The user entry from the utmp file. If it
 * is NULL, the first character of the host of the 'User' struct
 * is set to '\0'.
 */
void set_user_host(struct User *user, struct utmp *utmp_entry){
	if(utmp_entry==NULL) //If the user entry from utmp file is NULL, set the first character of the host of the 'User' struct to '\0'.
		user->host[0]='\0';
	else
		strcpy(user->host, utmp_entry->ut_host); //Else copy the host into the 'User' struct.
}

/**
 * This functions sets the user idle time to a 'User' struct.
 *
 * @param user The 'User' struct to set.
 * @param utmp_entry The user entry from the utmp file. If it
 * is NULL, the idle time of the 'User' struct is set to -1.
 */
void set_user_idle_time(struct User *user, struct utmp *utmp_entry){
	if(utmp_entry==NULL){ //If the user entry from utmp file is NULL, set the idle time of the 'User' struct to -1.
		user->idle_time=-1;
		return;
	}
	struct stat stat_buffer;
	char tty_path[256]="/dev/"; //Build the device file path.
	strcat(tty_path, utmp_entry->ut_line);
	if(stat(tty_path, &stat_buffer)==-1){ //Get the status of the device file.
		perror("stat_buffer error");
		exit(EXIT_FAILURE);
	}
	time_t current_time=time(NULL);
	user->idle_time=difftime(current_time, stat_buffer.st_atime); //Set the idle time of the 'User' struct to the difference between the current time and the last access time of the device file.
}

/**
 * This functions sets the timestamp of the user last access and
 * last modification to the .mail file.
 *
 * @param user The 'User' struct to set.
 * @param email_path The path of the user's .mail file. If it
 * is NULL, the timestamp of the last access and last modification
 * to the .mail file of 'User' struct are set to 0.
 */
void set_user_email(struct User *user, char *email_path){
	if(email_path==NULL){ //If the .mail file path is NULL, set the timestamp of the last access and last modification to the .mail file of 'User' struct to 0.
		user->email_last_access=0;
		user->email_last_modified=0;
		return;
	}
	struct stat stat_buffer;
	if(stat(email_path, &stat_buffer)==0){ //If it is possible, get the .mail file status and copies the timestamp of the last access and last modification to the .mail file into the 'User' struct.
		user->email_last_access=stat_buffer.st_atime;
		user->email_last_modified=stat_buffer.st_mtime;
	}
	else{ //Else set the timestamp of the last access and last modification to the .mail file of 'User' struct to 0.
		user->email_last_access=0;
		user->email_last_modified=0;
	}
}

/**
 * This functions sets the path of the user's .pgpkey file to
 * a 'User' struct.
 *
 * @param user The 'User' struct to set.
 * @param pgpkey_path The path of the user's .pgpkey file. If it
 * is NULL, the first character of the .pgpkey file path of the
 * 'User' struct is set to '\0'.
 */
void set_user_pgpkey(struct User *user, char *pgpkey_path){
	if(pgpkey_path==NULL) //If the .pgpkey file path is NULL, set the first character of the .pgpkey file path of the 'User' struct to '\0'.
		user->pgpkey[0]='\0';
	else
		strcpy(user->pgpkey, pgpkey_path); //Else copy the .pgpkey file path into the 'User' struct.
}

/**
 * This functions sets the path of the user's .project file to
 * a 'User' struct.
 *
 * @param user The 'User' struct to set.
 * @param project_path The path of the user's .project file. If it
 * is NULL, the first character of the .project file path of the
 * 'User' struct is set to '\0'.
 */
void set_user_project(struct User *user, char *project_path){
	if(project_path==NULL) //If the .project file path is NULL, set the first character of the .project file path of the 'User' struct to '\0'.
		user->project[0]='\0';
	else
		strcpy(user->project, project_path); //Else copy the .project file path into the 'User' struct.
}

/**
 * This functions sets the path of the user's .plan file to
 * a 'User' struct.
 *
 * @param user The 'User' struct to set.
 * @param plan_path The path of the user's .plan file. If it
 * is NULL, the first character of the .plan file path of the
 * 'User' struct is set to '\0'.
 */
void set_user_plan(struct User *user, char *plan_path){
	if(plan_path==NULL) //If the .plan file path is NULL, set the first character of the .plan file path of the 'User' struct to '\0'.
		user->plan[0]='\0';
	else
		strcpy(user->plan, plan_path); //Else copy the .plan file path into the 'User' struct.
}
