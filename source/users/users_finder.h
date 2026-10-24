/**
 * This header file declares functions for finding users information.
 *
 * @author peppo02
 */

#ifndef USERS_FINDER_H_
#define USERS_FINDER_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pwd.h>
#include <utmp.h>
#include "utils.h"
#include "users.h"
#include "users_builder.h"
#include "command_configurations.h"


void find_logged_users(struct Arguments *args, struct Users *users);

void find_users(struct Arguments *args, struct Users *users, struct Usernames *users_not_found);

struct passwd *find_user_passwd(char *username, bool name);

struct utmp *find_user_utmp(char *username);

char *find_user_email(char *username);

char *find_user_pgpkey(char *username);

char *find_user_project(char *username);

char *find_user_plan(char *username);

#endif /* USERS_FINDER_H_ */
