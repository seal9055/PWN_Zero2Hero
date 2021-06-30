#include <stdio.h>

// gcc vuln.c -fno-stack-protector -no-pie -o vuln

int main(int argc, char** argv, char** envp){
    char buf[0x20];

    read(0, buf, 0x1000);
}
