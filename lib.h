#ifndef LIB_H
#define LIB_H
#include <sys/types.h>

#define CLEAR		"\e[1;1H\e[2J"
#define PROC_NAME   "chat"

#define	USR_LEN		20
#define MSG_LEN		80
#define PTH_LEN		100

pid_t proc_find(const char* name);
void empty(char* buff, int size);
void refresh(const char* filename);
int streq(char* str1, char* str2, int size);

#endif