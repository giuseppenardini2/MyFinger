/**
 * This source file contains implementations of the "users_manager.h" functions.
 *
 * @author peppo02
 */

#include "users_manager.h"


/**
 * This function execute the 'finger' command in accordance with
 * the provided arguments.
 *
 * @param args The 'Arguments' struct for the 'finger' command arguments.
 */
void execute_finger(struct Arguments *args){
	struct Users *users=initialize_users();
	struct Usernames *users_not_found=initialize_usernames();
	if(args->users_to_find!=NULL) //If there are some users to find.
		find_users(args, users, users_not_found); //Find the users information and set it.
	else
		find_logged_users(args, users); //Else find the logged-in users.
	print_users_not_found(users_not_found); //Print the usernames of the users not not found.
	free_usernames(users_not_found); //Deallocate the memory reserved for the 'Usernames' struct for the users not found.
	print_users(args, users); //Print the information of the users found.
	free_users(users); //Deallocate the memory reserved for the 'Users' struct for the users found.
}
