#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//gcc vuln.c -fno-stack-protector -no-pie -z execstack -o vuln

__attribute__((constructor)) void ignore_me(){
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
}

#define MAX_USERS 5
struct user {
	char username[16];
	char password[16];
};

void server() {

	int choice;
	char buf[0x10];

	struct user User[MAX_USERS];
	int num_users = 0;
	int is_admin = 0;
	char server_name[0x20] = "my_cool_server!";
	
	while(1) {

		puts("+=========:[ Menu ]:========+");
	    puts("| [1] Create Account	    |");
	    puts("| [2] View User List 	    |");
	    puts("| [3] Change Server Name    |");
	    puts("| [4] Log out		    |");
	    puts("+===========================+");
	    printf("\n > ");

		if (fgets(buf, sizeof(buf), stdin) == NULL) {
		    exit(-1);
		}  

		choice = atoi(buf);

		switch(choice) {
		   	case 1:
				if (num_users > 5)
				   	puts("The server is at its user limit.");
				else {
				   	printf("Enter the username:\n > ");
				   	fgets(User[num_users].username,15,stdin);

				   	printf("Enter the password:\n > ");
				   	fgets(User[num_users].password,15,stdin);

				   	puts("User successfully created!\n");
				   	num_users++;
				}
				break;

			case 2:
				if (num_users == 0)
					puts("There are no users on this server yet.\n");

				else {
					for (int i = 0; i < num_users; i++) {
						printf("%d: %s",i+1, User[i].username);
					}
				}
				break;
			case 3:
				if (!is_admin) {
					puts("You do not have administrative rights. Please refrain from such actions.\n");
					break;
				}
				else {
					printf("The server name is stored at %p\n",server_name);
					printf("Enter new server name.\n > ");
					gets(server_name);					
					break;
				}

			case 4:
				puts("Goodbye!");
				return;
		}
   	}
}

void main() {

	puts("Welcome to this awesome server!");
	puts("I hired a professional to make sure its security is top notch.");
	puts("Have fun!\n");

	server();
}
