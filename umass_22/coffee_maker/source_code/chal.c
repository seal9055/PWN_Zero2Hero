#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

// gcc chal.c -o chal -no-pie -fno-stack-protector

#define MAGIC 0x1337

__attribute__((constructor)) void ignore_me() {
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
}

struct P1Header {
    unsigned int magic;
    unsigned int action;
    unsigned int length;
    char         key[32];
};

struct P2Header {
    unsigned int magic;
    unsigned int temperature;
    unsigned int type;
    unsigned int cup_size;
    unsigned int length;
    char         data[512];
    unsigned int checksum; 
};

char *base46_map = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
char *Pass = "password";
int Action = -1;
struct P2Header *p2;
char plain[64];

char* base64_decode(char* cipher) {
    char counts = 0;
    char buffer[4];
    int i = 0, p = 0;

    for(i = 0; cipher[i] != '\0'; i++) {
        char k;
        for(k = 0 ; k < 64 && base46_map[(int)k] != cipher[i]; k++);
        buffer[(int)counts++] = k;
        if(counts == 4) {
            plain[p++] = (buffer[0] << 2) + (buffer[1] >> 4);
            if(buffer[2] != 64)
                plain[p++] = (buffer[1] << 4) + (buffer[2] >> 2);
            if(buffer[3] != 64)
                plain[p++] = (buffer[2] << 6) + buffer[3];
            counts = 0;
        }
    }
    plain[p] = '\0';
    return plain;
}

// Verify that the user is sending proper packets
int verify_initial_packet(char *buffer) {
    struct P1Header *p1_header;

    p1_header = (struct P1Header*) buffer;

    if (p1_header->magic != MAGIC) { return -1; }

    Action = p1_header->action;
    char *key = base64_decode(p1_header->key);

    return strcmp(key, Pass);
}

// Verify that the second packets checksum is correct
int verify_checksum(char *buffer) {
    p2 = (struct P2Header*) buffer;
    int sum = 0;

    for (int i = 0; i < p2->length; i++) {
        sum += (char) p2->data[i];
    }
    return sum - p2->checksum;
}

// Start making the coffee
int make_coffee() {
    char size[16];
    char coffee[64];
    char name[256];

    if (p2->temperature > 150) {
        return 1;
    }

    switch (p2->cup_size) {
        case 0:
            strcpy(size, "Small");
            break;
        case 1:
            strcpy(size, "Medium");
            break;
        case 2:
            strcpy(size, "Large");
            break;
        default:
            strcpy(size, "None");
            break;
    }

    sprintf(coffee, "Good Morning!\n Your %s", size);
    memcpy(name, p2->data, p2->length);

    switch (p2->type) {
        case 0:
            strcat(coffee, " Espresso will be ready in 2 minutes.\n");
            write(1, coffee, strlen(coffee));
            break;
        case 1:
            strcat(coffee, " Decaf will be ready in 10 seconds.\n");
            write(1, coffee, strlen(coffee));
            break;
        case 2:
            strcat(coffee, " Honey Spiced Latte will be ready in 20 minutes.\n");
            write(1, coffee, strlen(coffee));
            break;
        default:
            write(1, "An error has occured, please try again\n", 39);
            return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    char packet_1[128];
    char tmp_p2[sizeof(struct P2Header)];

    // Verify first payload meant for verification purposes
    puts("VERIFY");
    fgets(packet_1, sizeof(packet_1), stdin);

    // Verify the initial payload and print SUCCESS | FAILURE
    if (verify_initial_packet(packet_1) != 0) {
        puts("FAILURE");
        return 1;
    }
    puts("SUCCESS");

    // Receive data packet
    fgets(tmp_p2, sizeof(tmp_p2), stdin);

    // Verify the second packets checksum
    if (verify_checksum(tmp_p2) != 0) {
        puts("Check FAILURE");
        return 1;
    }
    puts("CHECK SUCCESS");

    switch (Action) {
        case 1: // Reboot
            puts("Rebooting your CoffeeMaker9000");
            return 1;
        case 2: // Make Coffee
            puts("Making Coffee");
            make_coffee();
            break;
        case 3: // Turn off
            puts("Shutting Down...");
            return 1;
        default:
            puts("An error has occured, please try again");
            return 1;
    }
    return 0;
}
