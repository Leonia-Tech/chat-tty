#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lib.h"

int main(int argc, char* argv[])
{
	char Name[USR_LEN];
	char* tty_name = ttyname(STDIN_FILENO);

	FILE* Chat;
	char Buffer[MSG_LEN] = {0}; // Message buffer
	int counter = 0;
	char ChatName[PTH_LEN];

	getlogin_r(Name, 20);
	sprintf(ChatName, "/home/%s/.chat-app/chat.txt", Name);
	refresh(ChatName);

	while(1)
	{
		Chat = fopen(ChatName, "a");

		printf("%s@%s: ==> ", Name, tty_name);

		while(Buffer[counter-1] != '\\' && counter < MSG_LEN)
		{
			Buffer[counter] = getchar(); 
			if(Buffer[counter] == '@')
			{
				Buffer[counter] = '\0';
				break;
			}
			else if(Buffer[0] == '#')
				break;
			else if((Buffer[counter] == '\n' && Buffer[counter-1] == '\n') || Buffer[0] == '\n' )
				continue;
			counter++;
		}

		if(Buffer[counter-1] == '\\')
			break;

		if(Buffer[0] != '#' && Buffer != "\n")
			fprintf(Chat, "%s@%s: ==> %s\n", Name, tty_name, &Buffer[0]);

		empty(Buffer, counter);
		counter = 0;

		fclose(Chat);
		refresh(ChatName);
	}

	fclose(Chat);
	if(argc > 1 && streq(argv[1], "--hidden", 8))
		remove(ChatName);

	return 0;
}
