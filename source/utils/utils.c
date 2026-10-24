/**
 * This source file contains implementations of the "utils.h" functions.
 *
 * @author peppo02
 */

#include "utils.h"


/**
 * This function checks if two strings are case-insensitive equal.
 *
 * @param string1 First string to compare.
 * @param string2 Second string to compare.
 * @return If two strings are equal.
 */
bool compare_case_insensitive_strings(char *string1, char *string2){
	if(string1==NULL || string2==NULL) //If a string is null, return false.
		return false;
	size_t length1=strlen(string1);
	size_t length2=strlen(string2);
	if(length1!=length2) //If the length of the strings is different, return false.
		return false;
	for(int i=0; i<length1; i++){
		if(tolower(string1[i])!=tolower(string2[i])) //If two characters of the strings are different, return false.
			return false;
	}
	return true; //Else return true.
}

/**
 * This function extracts a substring from a given string.
 *
 * @param string The string from which the substring will be extracted.
 * @param start The starting index of the substring.
 * @param end The ending index of the substring.
 * @return A pointer to the substring. If the is string is NULL or the
 * starting or ending indexes are not valid, the return value is NULL.
 */
char *substring(char *string, size_t start, size_t end){
	if(string==NULL || start>end || start<0 || end>=strlen(string)){ //If the string or indexes are not valide, return NULL.
		perror("Invalid start or end index for substring");
		return NULL;
	}
	size_t substring_length=end-start+1; //Calculates the substring length.
	char *substring=(char*)malloc((substring_length+1)*sizeof(char));
	if(substring==NULL){
		perror("malloc() error for substring");
		exit(EXIT_FAILURE);
	}
	for(size_t i=0; i<substring_length; i++){ //Copies each character of the string into the substring starting from the starting index.
		substring[i]=string[start+i];
	}
	substring[substring_length]='\0';
	return substring;
}

/**
 * This function formats a time as a string "Day Month DayNumber Hour:Minute (TimeZone)"
 * with or without a time zone.
 *
 * @param time The time to format as a string.
 * @param time_zone If include the time zone in the formatted string.
 * @return A pointer to the formatted string.
 */
char *format_time(time_t time, bool time_zone){
	struct tm *time_buffer;
	size_t string_length=100;
	char *time_string=(char*)malloc(string_length*sizeof(char));
	if(time_string==NULL){
		perror("malloc() error for time_string");
		exit(EXIT_FAILURE);
	}
	time_buffer=localtime(&time); //Converts the time from "time_t" to a struct tm in order to separate the different compenents of the time
	if(strftime(time_string, string_length, (time_zone==true)? "%a %b %-d %H:%M (%Z)":"%a %b %-d %H:%M", time_buffer)==0){ //Formats the time (struct tm) as a string with or without the time zone.
		perror("sfrtime() error for time_buffer");
		free(time_string);
		exit(EXIT_FAILURE);
	}
	return time_string;
}

/**
 * This function formats a phone number as a string based on the phone number length.
 * If the phone number length is 11, it will be formatted as "+N-NNN-NNN-NNNN".
 * If the phone number length is 10, it will be formatted as "NNN-NNN-NNNN".
 * If the phone number length is 7, it will be formatted as "NNN-NNNN".
 * If the phone number length is 5, it will be formatted as "xN-NNNN".
 * If the phone number length is 4, it will be formatted as "xNNNN".
 *
 * @param phone_number Numero di telefono.
 * @return A pointer to the formatted string. If the phone number length does
 * not fall within the specified lengths, the return value is NULL.
 */
char *format_phone_number(char *phone_number){
	char *formatted_string=(char*)malloc(16*sizeof(char));
	if(formatted_string==NULL){
		perror("malloc() error for formatted_string");
		exit(EXIT_FAILURE);
	}
	formatted_string[0]='\0';
	size_t phone_number_length=strlen(phone_number);
	switch(phone_number_length){
		case 11:
			formatted_string[0]='+';
			formatted_string[1]=phone_number[0];
			formatted_string[2]='-';
			formatted_string[3]=phone_number[1];
			formatted_string[4]=phone_number[2];
			formatted_string[5]=phone_number[3];
			formatted_string[6]='-';
			formatted_string[7]=phone_number[4];
			formatted_string[8]=phone_number[5];
			formatted_string[9]=phone_number[6];
			formatted_string[10]='-';
			formatted_string[11]=phone_number[7];
			formatted_string[12]=phone_number[8];
			formatted_string[13]=phone_number[9];
			formatted_string[14]=phone_number[10];
			formatted_string[15]='\0';
			break;
		case 10:
			formatted_string[0]=phone_number[0];
			formatted_string[1]=phone_number[1];
			formatted_string[2]=phone_number[2];
			formatted_string[3]='-';
			formatted_string[4]=phone_number[3];
			formatted_string[5]=phone_number[4];
			formatted_string[6]=phone_number[5];
			formatted_string[7]='-';
			formatted_string[8]=phone_number[6];
			formatted_string[9]=phone_number[7];
			formatted_string[10]=phone_number[8];
			formatted_string[11]=phone_number[9];
			formatted_string[12]='\0';
			break;
		case 7:
			formatted_string[0]=phone_number[0];
			formatted_string[1]=phone_number[1];
			formatted_string[2]=phone_number[2];
			formatted_string[3]='-';
			formatted_string[4]=phone_number[3];
			formatted_string[5]=phone_number[4];
			formatted_string[6]=phone_number[5];
			formatted_string[7]=phone_number[6];
			formatted_string[8]='\0';
			break;
		case 5:
			formatted_string[0]='x';
			formatted_string[1]=phone_number[0];
			formatted_string[2]='-';
			formatted_string[3]=phone_number[1];
			formatted_string[4]=phone_number[2];
			formatted_string[5]=phone_number[3];
			formatted_string[6]=phone_number[4];
			formatted_string[7]='\0';
			break;
		case 4:
			strcat(formatted_string, "x");
			strcat(formatted_string, phone_number);
			break;
		default:
			fprintf(stderr, "Invalide phone number to format '%s'\n", phone_number);
			formatted_string=NULL;
			break;
	}
	return formatted_string;
}
