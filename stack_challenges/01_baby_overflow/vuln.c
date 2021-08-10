#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//gcc vuln.c -fno-stack-protector -o vuln

__attribute__((constructor)) void ignore_me(){
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
}

int read_flag() {
	char flag[32] = {0};
	FILE *fd = NULL;
	fd = fopen("flag.txt","r");

	if(fd == NULL) {
		puts("Something went wrong while opening the flag file.");
		exit(-1);
	}

	fgets(flag, 0x30, fd);
	printf("The flag is: %s\n", flag);
	exit(1);
}

int main() {
 
	int password;
	char buf[10];
	
	char *var;
	
	puts("Hey, how are you doing today?");
	fgets(buf,0x10,stdin);
	
	var = strtok(buf,"-");
	
	if (!strcmp(var,"good") && password == 0xdeadbeef) {
	  read_flag();
	}
	
	puts("I guess u just aren't good enough yet. ¯\\_(ツ)_/¯ ");
}
