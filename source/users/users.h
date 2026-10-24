/**
 * This header file declares functions for managing the data structures of the users.
 * The data structures must be initialized through the functions provided by the header
 * file 'users_builder' before using them.
 *
 * @author peppo02
 */

#ifndef USERS_H_
#define USERS_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "utils.h"


/**
 * A struct that stores users information.
 */
typedef struct User{
	char username[256]; /** The username. */
	char real_name[256]; /** The real name. */
	char directory[256]; /** The directory. */
	char shell[256]; /** The shell. */
	time_t last_login; /** The last login time. */
	char device_name[32]; /** The device name. */
	char host[256]; /** The host name. */
	bool write_permission_device; /** The write permission on the device file. */
	double idle_time; /** The idle time in seconds. */
	char office_number[10]; /** The office number. */
	char office_phone[20]; /** The office phone number. */
	char home_phone[20]; /** The home phone number. */
	time_t email_last_access; /** The timestamp of the last access to the '.mail' file. */
	time_t email_last_modified; /** The timestamp of the last modification to the '.mail' file. */
	char pgpkey[256]; /** The '.pgpkey' file path. */
	char project[256]; /** The '.project' file path. */
	char plan[256]; /** The '.plan' file path. */
};

/**
 * A struct that represents a dynamic array of 'Users' structs.
 */
typedef struct Users{
	struct User *users; /** The dynamic array of 'User' struct */
	size_t size; /** The array size. */
	size_t capacity; /** The array capacity. */
};

/**
 * A struct that represents a dynamic array of usernames.
 */
typedef struct Usernames{
	char **usernames; /** The array of usernames. */
	size_t size; /** The array size. */
	size_t capacity; /** The array capacity. */
};


struct User *initialize_user();

struct Users *initialize_users();

struct Usernames *initialize_usernames();

void add_user(struct Users *users, struct User *user);

bool is_user_in_users(struct Users *users, char *username);

void add_username(struct Usernames *usernames, char *username);

void free_users(struct Users *users);

void free_usernames(struct Usernames *usernames);


#endif /* USERS_H_ */
