# MyFinger

## Table of contents
- [About](#about)
- [Configuration of command arguments](#configuration-of-command-arguments)
- [Command execution](#command-execution)
- [License](#license)

## About
MyFinger is a program that emulates the behavior of the `finger` command in GNU/Linux.

> [!WARNING]  
> MyFinger is a university project focused on emulating the `finger` command.
> The security features are overlooked in order to focus on the rest.

## Configuration of command arguments

The configuration of the `finger` command's arguments is handled by a module
(`command_configurations.h`) that sets the `finger` command's arguments depending on
whether or not they are specified. These arguments include the formatting type, the `m`
and `p` arguments, and the names or usernames of the users to search for.

## Command execution

The execution of the `finger` command is divided into four sequential phases, each defined in specific
modules:
* Definition of user data structures (users.h): A module responsible for defining
functions and data structures to represent user information relevant to the
`finger` command (`User`), a dynamic array of users (`Users`), and a dynamic array of
usernames for users to be found and those not found (`Usernames`).
* Searching for user information (users_finder.h): A module that provides functions to
search for user information relevant to the `finger` command in the .passwd3
(username, directory, shell, and GECOS), .utmp4 (last login and idle time5), .mail6, .pgpkey,
.project, and .plan7 files.
* Configuration of found information (users_builder.h): Module that provides
functions to populate user data structures with the information found by the
users_finder.h module.
* Printing user information (users_printer.h): Module that provides functions
to print the information set by the users_builder.h module based on the type of
formatting and the p argument.

## License

*Copyright© 2026 Giuseppe Nardini*\
This program is licensed under the [AGPL-3.0](LICENSE) license.
