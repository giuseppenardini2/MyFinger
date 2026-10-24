/**
 * This header file declares functions and structs for configuring the 'finger' command arguments.
 *
 * @author peppo02
 */

#ifndef COMMAND_CONFIGURATIONS_H_
#define COMMAND_CONFIGURATIONS_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <users.h>


/**
 * An enum that defines the formatting type.
 */
typedef enum FormattingType{
	SHORT_F, /** The short formatting. */
	LONG_F /** The long formatting. */
};

/**
 * A data structure that stores finger arguments.
 */
typedef struct Arguments{
	enum FormattingType formatting; /** The formatting type */
	bool m_argument; /** The 'm' argument */
	bool p_argument; /** The  'p' argument */
	struct Usernames *users_to_find; /** The 'Usernames' struct for the users to find */
};


struct Arguments *initialize_command_arguments(char formatting, bool m_argument, bool p_argument, char *users_string);

void wrong_argument_error(char argument);

void free_command_arguments(struct Arguments *args);


#endif /* COMMAND_CONFIGURATIONS_H_ */
