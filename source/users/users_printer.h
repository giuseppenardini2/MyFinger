/**
 * This header file declares functions for printing 'User' struct information.
 *
 * @author peppo02
 */

#ifndef USERS_PRINTER_H_
#define USERS_PRINTER_H_


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


void print_users_not_found(struct Usernames *users_not_found);

void print_users(struct Arguments *args, struct Users *users);

void print_user(struct Arguments *args, struct User *user);

void print_short_format_user(struct User *user);

void print_long_format_user(struct User *user, bool p_argument);


void print_user_username(struct User *user, enum FormattingType formatting);

void print_user_real_name(struct User *user, enum FormattingType formatting);

void print_user_directory(struct User *user);

void print_user_shell(struct User *user);

void print_user_device_name(struct User *user, enum FormattingType formatting);

void print_user_last_login(struct User *user, enum FormattingType formatting);

void print_user_idle_time(struct User *user, enum FormattingType formatting);

void print_user_host(struct User *user);

void print_user_write_permission_device(struct User *user, enum FormattingType formatting);

void print_user_office_number(struct User *user, enum FormattingType formatting);

void print_user_office_phone(struct User *user, enum FormattingType formatting);

void print_user_home_phone(struct User *user);

void print_user_email(struct User *user);

void print_user_pgpkey(struct User *user);

void print_user_project(struct User *user);

void print_user_plan(struct User *user);


#endif /* USERS_PRINTER_H_ */
