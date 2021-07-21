#include <stdio.h>

// gcc vuln.c -o vuln

__attribute__((constructor)) void ignore_me(){
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
}

void main() {
    char buffer[0x10];

    puts("Since the past few challenges were so long, here's a short one for once.");
    puts("You do have to deal with more protections this time though, so pay attention!");
    fgets(buffer, sizeof(buffer), stdin);
    printf(buffer);

    puts("I hope you got everything u needed cause ur out of time.");
    puts("Good luck!");
    gets(buffer);
}
