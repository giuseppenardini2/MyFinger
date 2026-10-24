/*
 * This source file contains implementations of the "utils.h" functions.
 *
 * @author peppo02
 */

#include "users.h"


/**
 * This function initializes a 'User' struct.
 *
 * @return A pointer to the 'User' struct.
 */
struct User *initialize_user(){
	struct User *user=(struct User*)malloc(sizeof(struct User));
	if(user==NULL){
		perror("malloc() error for user");
		exit(EXIT_FAILURE);
	}
	return user;
}

/**
 * This function initializes a 'Users' struct.
 *
 * @return A pointer to the 'Users' struct.
 */
struct Users *initialize_users(){
	struct Users *users=(struct Users*)malloc(sizeof(struct Users)); //Initialize a 'Users' struct.
	if(users==NULL){
		perror("malloc() error for users");
		exit(EXIT_FAILURE);
	}
	users->size=0; //Initialize the array size.
	users->capacity=5; //Initialze the array capacity.
	users->users=(struct User*)malloc(users->capacity*sizeof(struct User)); //Initialize the array of 'User' struct.
	if(users->users==NULL){
		perror("malloc() error for users->users");
		exit(EXIT_FAILURE);
	}
	return users;
}

/**
 * This function initializes a 'Usernames' struct.
 *
 * @return A pointer to the 'Usernames' struct.
 */
struct Usernames *initialize_usernames(){
	struct Usernames *usernames=(struct Usernames*)malloc(sizeof(struct Usernames)); //Initialize a struct 'Usernames'.
	if(usernames==NULL){
		perror("malloc() error for usernames");
		exit(EXIT_FAILURE);
	}
	usernames->size=0; //Initialize the array size.
	usernames->capacity=5; //Initialize the array capacity.
	usernames->usernames=malloc(usernames->capacity*sizeof(char*)); //Initialize the array of usernames.
	if(usernames->usernames==NULL){
		perror("malloc() error for usernames->usernames");
		exit(EXIT_FAILURE);
	}
	return usernames;
}

/**
 * This function adds a 'User' struct in a 'Users' struct.
 *
 * @param users The 'Users' struct in which to add the 'User' struct.
 * @param user The 'User' struct to add.
 */
void add_user(struct Users *users, struct User *user){
	if(users->size>=users->capacity){ //If the 'Users' struct size is greater than or equals to its capacity, Allocate additional memory to increase its capacity.
		users->capacity+=5;
		users->users=realloc(users->users, users->capacity*sizeof(struct Users));
		if(users->users==NULL){
			perror("realloc() error for users->users");
			exit(EXIT_FAILURE);
		}
	}
	users->users[users->size]=*(user); //Add the 'User' struct to the array of 'User' struct.
	users->size++; //Increase the array size.
}

/**
 * This function checks if a 'User' struct is present in a 'Users' struct by the username.
 *
 * @param users The 'Users' struct.
 * @param username The username to check.
 * @return If the 'User' struct is present in the 'Users' struct.
 */
bool is_user_in_users(struct Users *users, char *username){
	for(size_t i=0; i<users->size; i++){
		if(strcmp(users->users[i].username, username)==0) //If the provided username is equals to a 'User' struct username in the 'Users' struct, return true.
			return true;
	}
	return false; //Else return false.
}

/**
 * This function adds a username in a 'Usernames' struct.
 *
 * @param users The 'Usernames' struct in which to add the 'User' struct.
 * @param username The username to add.
 */
void add_username(struct Usernames *usernames, char *username){
	if(usernames->size>=usernames->capacity){ //If the 'Usernames' struct size is greater than or equals to its capacity, Allocate additional memory to increase its capacity.
		usernames->capacity+=5;
		usernames->usernames=realloc(usernames->usernames, usernames->capacity*sizeof(char*));
		if(usernames->usernames==NULL){
			perror("realloc() error for usernames");
			exit(EXIT_FAILURE);
		}
	}
	usernames->usernames[usernames->size]=(char*)malloc(strlen(username)+1); //Allocates memory for the username to add in the array of usernames.
	if(usernames->usernames[usernames->size]==NULL){
		perror("malloc() error for usernames->usernames[usernames->size]");
		exit(EXIT_FAILURE);
	}
	strcpy(usernames->usernames[usernames->size], username); //Add the username in the array of usernames.
	usernames->size++; //Increase the array size.
}

/**
 * This function deallocates the memory reserved for a 'Users' struct.
 *
 * @param users The 'Users' struct to deallocate memory for.
 */
void free_users(struct Users *users){
	if(users==NULL)
		return;
	free(users->users); //Deallocate the memory for array of 'User' struct.
	free(users); //Deallocate the memory for 'Users' struct.
}

/**
 * This function deallocates the memory reserved for a 'Usernames' struct.
 *
 * @param users The 'Usernames' struct to deallocate memory for.
 */
void free_usernames(struct Usernames *usernames){
	if(usernames==NULL)
		return;
	for(size_t i=0; i<usernames->size; i++){
		free(usernames->usernames[i]); //Deallocate the memory for the usernames in the array.
	}
	free(usernames->usernames); //Deallocate the memory for usernames array.
	free(usernames); //Deallocate the memory for 'Usernames' struct.
}
