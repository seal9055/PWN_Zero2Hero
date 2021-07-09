#include <stdio.h>
#include <unistd.h>

// clang vuln.c -o vuln		Gcc kept optimising out defuse_bomb even with -O0 so I used clang for this

void bomb() {
	puts("We all died");
}

int defuse_bomb(long wire_one, long wire_two, long wire_three) {
	puts("Good luck!");//

	if(wire_one == 0xdeadbeefdeadbeef && wire_two == 0xf00dd00dcafebabe) {
        char* cmd = "/bin/sh";
        puts("You are making some nice progress!");

        if(wire_three == 0x1337c0ded457c0de) {
            puts("You saved the world!");
            execve(cmd, NULL, NULL);
        } 
    }
    bomb();
}

void main() {

	char buf[0x20];
	alarm(6);

	printf("A bomb is about to go off, please defuse it quick!\n");
	printf("You can find your defuse kit at %p!\n", defuse_bomb);

	fgets(buf,0x200,stdin);
}
