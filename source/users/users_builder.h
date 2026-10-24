/**
 * This header file declares functions for populating 'User' struct with
 * user information.
 *
 * @author peppo02
 */

#ifndef USERS_BUILDER_H_
#define USERS_BUILDER_H_


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
#include "command_configurations.h"


void set_user_information(struct Arguments *args, struct User *user, struct passwd *passwd_entry,
		struct utmp *utmp_entry, char *email_path, char *pgpkey_path, char *project_path, char *plan_path);

void set_user_passwd_information(enum FormattingType formatting, struct User *user, struct passwd *passwd_entry);

void set_user_gecos(enum FormattingType formatting, struct User *user, char *gecos);

void set_user_utmp_information(struct User *user, struct utmp *utmp_entry);

void set_user_last_login(struct User *user, struct utmp *utmp_entry);

void set_user_device_name(struct User *user, struct utmp *utmp_entry);

void set_user_write_permission_device(struct User *user, struct utmp *utmp_entry);

void set_user_host(struct User *user, struct utmp *utmp_entry);

void set_user_idle_time(struct User *user, struct utmp *utmp_entry);

void set_user_email(struct User *user, char *email_path);

void set_user_pgpkey(struct User *user, char *pgpkey_path);

void set_user_project(struct User *user, char *project_path);

void set_user_plan(struct User *user, char *plan_path);


#endif /* USERS_BUILDER_H_ */
