/**
 * This source file contains implementations of the "users_printer.h" functions.
 *
 * @author peppo02
 */

#include "users_printer.h"


/**
 * This function prints the usernames of a 'Usernames' struct
 * for the users not found.
 *
 * @param users_not_found The 'Usernames' struct for the users not found.
 */
void print_users_not_found(struct Usernames *users_not_found){
	for(size_t i=0; i<users_not_found->size; i++){
		fprintf(stderr, "finger: %s: no such user.\n", users_not_found->usernames[i]);
	}
}

/**
 * This function prints the 'User' structs information of the 'Users'
 * struct based on the formatting type.
 *
 * @param arg The 'Arguments' struct for the 'finger' command arguments.
 * @param users The 'Users' struct for the users to print.
 */
void print_users(struct Arguments *args, struct Users *users){
	if(args->formatting==SHORT_F)
		printf("Login\t  Name\t  Tty\t  Idle\t  Login time\t  Office\t  Office Phone\n");
	for(size_t i=0; i<users->size; i++){
		print_user(args, &users->users[i]);
		printf("\n");
	}
}

/**
 * This function prints the 'User' struct information based on a
 * formatting type.
 *
 * @param arg The 'Arguments' struct for the 'finger' command arguments.
 * @param users The 'User' struct for the user to print.
 */
void print_user(struct Arguments *args, struct User *user){
	if(args->formatting==SHORT_F)
		print_short_format_user(user);
	else if(args->formatting==LONG_F)
		print_long_format_user(user, args->p_argument);
}

/**
 * This function prints the 'User' struct information based on the
 * short formatting type.
 *
 * @param users The 'User' struct for the user to print.
 */
void print_short_format_user(struct User *user){
	print_user_username(user, SHORT_F);
	print_user_real_name(user, SHORT_F);
	print_user_write_permission_device(user, SHORT_F);
	print_user_device_name(user, SHORT_F);
	print_user_idle_time(user, SHORT_F);
	print_user_last_login(user, SHORT_F);
	print_user_office_number(user, SHORT_F);
	print_user_office_phone(user, SHORT_F);
}

/**
 * This function prints the 'User' struct information based on the
 * long formatting type.
 *
 * @param users The 'User' struct for the user to print.
 * @param p_argument If printing user's .pgpkey file, .project file
 * and .plan file.
 */
void print_long_format_user(struct User *user, bool p_argument){
	print_user_username(user, LONG_F);
	print_user_real_name(user, LONG_F);
	print_user_directory(user);
	print_user_shell(user);
	print_user_office_number(user, LONG_F);
	print_user_office_phone(user, LONG_F);
	print_user_home_phone(user);
	print_user_last_login(user, LONG_F);
	print_user_device_name(user, LONG_F);
	print_user_host(user);
	print_user_write_permission_device(user, LONG_F);
	print_user_idle_time(user, LONG_F);
	print_user_email(user);
	if(p_argument==false){
		print_user_pgpkey(user);
		print_user_project(user);
		print_user_plan(user);
	}
}

/**
 * This function prints the usernames of a 'User' struct based on a
 * formatting type.
 *
 * @param users The 'User' struct for the user to print.
 * @param formatting The formatting type.
 */
void print_user_username(struct User *user, enum FormattingType formatting){
	if(formatting==SHORT_F)
		printf("%s\t", user->username);
	else if(formatting==LONG_F)
		printf("Login: %s\t", user->username);
}

/**
 * This function prints the real name of a 'User' struct based on a
 * formatting type.
 *
 * @param users The 'User' struct for the user to print.
 * @param formatting The formatting type.
 */
void print_user_real_name(struct User *user, enum FormattingType formatting){
	if(formatting==SHORT_F)
		printf("%s\t", user->real_name);
	else if(formatting==LONG_F)
		printf("Name: %s\n", user->real_name);
}

/**
 * This function prints the directory of a 'User' struct.
 *
 * @param users The 'User' struct for the user to print.
 */
void print_user_directory(struct User *user){
	printf("Directory: %s\t", user->directory);
}

/**
 * This function prints the shell of a 'User' struct.
 *
 * @param users The 'User' struct for the user to print.
 */
void print_user_shell(struct User *user){
	printf("Shell: %s\n", user->shell);
}

/**
 * This function prints the device name of a 'User' struct based on a
 * formatting type.
 *
 * @param users The 'User' struct for the user to print.
 * @param formatting The formatting type.
 */
void print_user_device_name(struct User *user, enum FormattingType formatting){
	if(formatting==SHORT_F){
		if(user->device_name[0]!='\0')
			printf("%s\t", user->device_name);
		else
			printf("*\t");
	}
	if(formatting==LONG_F){
		if(user->last_login!=0 && user->device_name[0]!='\0'){
			printf("on %s", user->device_name);
		}
	}
}

/**
 * This function prints the last login of a 'User' struct based on a
 * formatting type.
 *
 * @param users The 'User' struct for the user to print.
 * @param formatting The formatting type.
 */
void print_user_last_login(struct User *user, enum FormattingType formatting){
	if(formatting==SHORT_F){
		if(user->last_login!=0){ //If last login time of the 'User' struct is not null, format the time into a string and print it.
			char *time_string=format_time(user->last_login, false);
			printf("%s\t", time_string);
			free(time_string);
		}
		else
			printf("No logins\t");
	}
	else if(formatting==LONG_F){
		if(user->last_login!=0){ //If last login time of the 'User' struct is not null, format the time into a string and print it.
			char *time_string=format_time(user->last_login, true);
			printf("On since %s ", time_string);
			free(time_string);
		}
		else
			printf("\nNever logged in.");
	}
}

/**
 * This function prints the idle time of a 'User' struct based on a
 * formatting type.
 *
 * @param users The 'User' struct for the user to print.
 * @param formatting The formatting type.
 */
void print_user_idle_time(struct User *user, enum FormattingType formatting){
	if(formatting==SHORT_F){
		if(user->idle_time==-1){ //If the idle time of the 'User' struct is null, notify it.
			printf("*\t");
		}
		else if(user->idle_time<60){ //Else if it is less than 1 minute, print 0.
			printf("0\t");
		}
		else if(user->idle_time<3600){ //Else if it is less than 1 hour, print it in minutes.
			int minutes=(int)(user->idle_time/60);
			printf("%i\t", minutes);
		}
		else{ //Else print it in hours and minutes.
			int hours=(int)(user->idle_time/3600);
			int minutes=(int)((user->idle_time-(hours*3600))/60);
			printf("%i:%i\t", hours, minutes);
		}
	}
	else if(formatting==LONG_F){
		if(user->idle_time==-1){ //If the idle time of the 'User' struct is null, notify it.
			return;
		}
		else if(user->idle_time<60){ //Else if it is less than 1 minute, print it in seconds.
			printf("\n\t%i seconds idle", (int) user->idle_time);
		}
		else if(user->idle_time<3600){ //Else if it is less than 1 hour, print it in minutes and seconds.
			int minutes=(int)(user->idle_time/60);
			int seconds=(int)user->idle_time%60;
			printf("\n\t%i minutes %i seconds idle", minutes, seconds);
		}
		else{ //Else print it in hours and minutes.
			int hours=(int)(user->idle_time/3600);
			int minutes=(int)((user->idle_time-(hours*3600))/60);
			printf("\n\t%i hours %i minutes idle", hours, minutes);
		}
	}
}

/**
 * This function prints the host of a 'User' struct.
 *
 * @param users The 'User' struct for the user to print.
 */
void print_user_host(struct User *user){
	if(user->host[0]!='\0')
		printf(" from %s", user->host);
}

/**
 * This function prints the write permission on the user device file
 * of a 'User' struct based on a formatting type.
 *
 * @param users The 'User' struct for the user to print.
 * @param formatting The formatting type.
 */
void print_user_write_permission_device(struct User *user, enum FormattingType formatting){
	if(formatting==SHORT_F){
		if(user->last_login!=0 && user->write_permission_device==false)
			printf("*");
	}
	else if(formatting==LONG_F){
		if(user->last_login!=0 && user->write_permission_device==false)
			printf("(messages off)");
	}
}

/**
 * This function prints the office number of a 'User' struct based on a
 * formatting type.
 *
 * @param users The 'User' struct for the user to print.
 * @param formatting The formatting type.
 */
void print_user_office_number(struct User *user, enum FormattingType formatting){
	if(formatting==SHORT_F){
		if(user->office_number[0]!='\0')
			printf("%s\t", user->office_number);
		else
			printf("\t");
	}
	else if(formatting==LONG_F){
		if(user->office_number[0]!='\0')
			printf("Office: %s", user->office_number);
	}
}

/**
 * This function prints the office phone number of a 'User' struct based on a
 * formatting type.
 *
 * @param users The 'User' struct for the user to print.
 * @param formatting The formatting type.
 */
void print_user_office_phone(struct User *user, enum FormattingType formatting){
	if(formatting==SHORT_F){
		if(user->office_phone[0]!='\0'){ //If the office phone number of the 'User' struct is not null, format it into a string and print it.
			char *phone_number=format_phone_number(user->office_phone);
			printf("%s", phone_number);
			free(phone_number);
		}
	}
	else if(formatting==LONG_F){
		if(user->office_phone[0]!='\0'){ //If the office phone number of the 'User' struct is not null, format it into a string and print it.
			char *phone_number=format_phone_number(user->office_phone);
			if(user->office_number[0]!='\0')
				printf(", %s\t", phone_number);
			else
				printf("Office: %s\t", phone_number);
			free(phone_number);
		}
	}
}

/**
 * This function prints the home phone number of a 'User' struct.
 *
 * @param users The 'User' struct for the user to print.
 */
void print_user_home_phone(struct User *user){
	if(user->home_phone[0]!='\0'){ //If the home phone number of the 'User' struct is not null, format it into a string and print it.
		char *phone_number=format_phone_number(user->home_phone);
		printf("Home: %s", phone_number);
		free(phone_number);
	}
}

/**
 * This function prints the .mail file of a 'User' struct.
 *
 * @param users The 'User' struct for the user to print.
 */
void print_user_email(struct User *user){
	if(user->email_last_modified==0){
		printf("\nNo mail.\n");
	}
	else if(difftime(user->email_last_modified, user->email_last_access)>0){ //Se l'ultima modifica è stata fatta dopo l'ultimo accesso, allora l'user ha email da leggere
		char *time_string=format_time(user->email_last_modified, true);
		printf("\nNew mail received %s", time_string); //TODO: Printare ultima modifica
		time_string=format_time(user->email_last_access, true);
		printf("\n\tUnread since %s\n", time_string);
		free(time_string);
	}
	else{
		char *time_string=format_time(user->email_last_access, true);
		printf("\nMail last read %s\n", ctime(&user->email_last_access));
		free(time_string);
	}
}

/**
 * This function prints the .pgpkey file of a 'User' struct.
 *
 * @param users The 'User' struct for the user to print.
 */
void print_user_pgpkey(struct User *user){
	if(user->pgpkey[0]=='\0') //If the file does not exist, return.
		return;
	FILE *pgpkey_file=fopen(user->pgpkey, "r"); //Else open the file.
	if(pgpkey_file==NULL){
		perror("Error opening pgpkey file");
		exit(EXIT_FAILURE);
	}
	printf("PGP Key:\n");
	char line[256]; //Print the file line for line.
	while(fgets(line, sizeof(line), pgpkey_file)!=NULL){
		printf("%s", line);
	}
	fclose(pgpkey_file); //Close the file.
}

/**
 * This function prints the .project file of a 'User' struct.
 *
 * @param users The 'User' struct for the user to print.
 */
void print_user_project(struct User *user){
	if(user->project[0]=='\0'){ //If the file does not exist, return.
		return;
	}
	FILE *project_file=fopen(user->project, "r"); //Else open the file.
	if(project_file==NULL){
		perror("Error opening project file");
		exit(EXIT_FAILURE);
	}
	printf("Project:\n");
	char line[256]; //Print the file line for line.
	while(fgets(line, sizeof(line), project_file)!=NULL){
		printf("%s", line);
	}
	fclose(project_file); //Close the file.
}

/**
 * This function prints the .plan file of a 'User' struct.
 *
 * @param users The 'User' struct for the user to print.
 */
void print_user_plan(struct User *user){
	if(user->plan[0]=='\0'){ //If the file does not exist, notify it.
		printf("No plan.\n");
		return;
	}
	FILE *plan_file=fopen(user->plan, "r"); //Else open the file.
	if(plan_file==NULL){
		perror("Error opening plan file");
		exit(EXIT_FAILURE);
	}
	printf("Plan:\n");
	char line[256]; //Print the file line for line.
	while(fgets(line, sizeof(line), plan_file)!=NULL){
		printf("%s", line);
	}
	fclose(plan_file); //Close the file.
}
