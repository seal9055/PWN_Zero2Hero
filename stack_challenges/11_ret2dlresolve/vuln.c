#include <stdio.h>

// gcc vuln.c -fno-stack-protector -no-pie -o vuln

__attribute__((constructor)) void ignore_me(){
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
}

int main(int argc, char** argv, char** envp){
    char buf[0x20];

    read(0, buf, 0x1000);
}
