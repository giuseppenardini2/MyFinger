/**
 * This source file contains implementations of the "command_configurations.h"
 * functions and global variables.
 *
 * @author peppo02
 */

#include "command_configurations.h"


/**
 * This functions configures the arguments for the 'finger' command.
 *
 * @param formatting_type The formatting type. If it is specified other than 'l'
 * or 's', an error is thrown.
 * @param m If applying 'm' argument.
 * @param p If applying 'p' argument.
 * @param users_string The string containing the users to search for. Users must be
 * separated by blank space.
 * @return A pointer to the 'Arguments' struct.
 */
struct Arguments *initialize_command_arguments(char formatting, bool m_argument, bool p_argument, char *users_string){
	if(formatting!='\0' && formatting!='l' && formatting!='s') //If the formatting type has not been specified and it is not 's' or 'l', an error is thrown.
			wrong_argument_error(formatting);

	struct Arguments *args=(struct Arguments*)malloc(sizeof(struct Arguments)); //Initialize a 'Argument' struct for finger arguments.
	if(args==NULL){
		perror("malloc() error for args");
		exit(EXIT_FAILURE);
	}

	args->m_argument=m_argument; //Set the argument 'm'.
	args->p_argument=p_argument; //Set the argument 'p'.

	if(users_string==NULL) //Set the 'Username' struct for the users to find.
		args->users_to_find=NULL;
	else { //If 'users_string' has been provided.
		args->users_to_find=initialize_usernames(); //Initialize a 'Usernames' struct to memorize usernames/names of the users to find.
		char *field=strtok(users_string, " "); //Truncate the 'user_string' into multiple substrings based on the blank spaces.
		while(field!=NULL){
			add_username(args->users_to_find, field); //Add the substrings (username/name) to the usernames array of the 'Usernames' struct for the users to find.
			field=strtok(NULL, " ");
		}
	}

	if(formatting=='l') //Set the formatting type.
		args->formatting=LONG_F;
	else if(formatting=='s')
		args->formatting=SHORT_F;
	else if(formatting=='\0' && ((args->m_argument==true || args->p_argument==true) || args->users_to_find!=NULL)) //If the formatting type has not been specified and 'm' argument or 'p' argument or users to search has not provided, set the formatting type to 'l'.
		args->formatting=LONG_F;
	else if(formatting=='\0') //Else if the formatting type has not been specified, set the formatting type to 's'.
		args->formatting=SHORT_F;

	return args;
}

/**
 * This function throws an error to notify that a command argument is wrong.
 *
 * @param argument The wrong command argument.
 */
void wrong_argument_error(char argument){
	fprintf(stderr, "finger: invalid option -- %c"
			"\nusage: finger [-lmsp] [login ...]\n", argument);
	exit(EXIT_FAILURE);
}

/**
 * This function deallocates the memory reserved for a 'Arguments' struct.
 *
 * @param args The 'Arguments' struct to deallocate memory for.
 */
void free_command_arguments(struct Arguments *args){
	if(args==NULL)
		return;
	free_usernames(args->users_to_find); //Deallocate the memory reserved for the 'Usernames' struct for the users to find.
}
