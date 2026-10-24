/**
 * This source file contains the main function.
 *
 * @author peppo02
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "command_configurations.h"
#include "users_manager.h"


int main(){
	char display_formatting='l'; //Declare the arguments for the 'finger' command.
	bool m=false;
	bool p=false;
	char users_string[]="pEpPo02 NeSsuno ciruzzo jacob";

	struct Arguments *args=initialize_command_arguments(display_formatting, m, p, users_string); //Set the arguments for the 'finger' command to an 'Arguments' struct.

	execute_finger(args); //Execute 'finger' command.

	free_command_arguments(args); //Deallocate the memory reserved for the 'Arguments' struct.

	return 0;
}
