/**
 * This header file declares functions for managing user for 'finger' command.
 *
 * @author peppo02
 */

#ifndef USERS_MANAGER_H_
#define USERS_MANAGER_H_

#include <stdio.h>
#include "command_configurations.h"
#include "users.h"
#include <users_builder.h>
#include "users_finder.h"
#include "users_printer.h"


void execute_finger(struct Arguments *args);


#endif /* USERS_MANAGER_H_ */
