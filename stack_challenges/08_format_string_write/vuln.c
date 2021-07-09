#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// gcc vuln.c -no-pie -Wl,-z,norelro -o vuln 

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

void main() {

	char buf[0x40];

	while (1) {
		fgets(buf, sizeof(buf), stdin);
		printf(buf);

		puts("Are you finished? [y/n] ");

		if (!strncmp(buf, "y", 1)) {
			return;
		}
		memset(buf, 0, 0x40);
	}
}
