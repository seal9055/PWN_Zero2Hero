#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h> 
#include <stdint.h>
#include <unistd.h>

//gcc vuln.c -o vuln -fno-stack-protector -no-pie

__attribute__((constructor)) void ignore_me(){
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
}

struct head {
	uint16_t num_files;
	uint32_t centdir_size;
	uint32_t centdir_offset;
};

struct centdir {
	uint32_t comp_size;
	uint32_t filerecord_offset;
	uint16_t filename_len;
	uint16_t extrafield_len;
};

struct dataentry {
	char *comp_data;
	uint32_t comp_size;
	uint16_t extrafield_len;
};

struct head *header = NULL;
struct centdir *entrylist = NULL;
struct dataentry *data = NULL;

void useful_gadgets()
{
__asm__("pop %rdx\n\t"
        "ret\n\t");
}

void parse_data(char *buffer, int i)
{
	char buf[128];
	int offset, len;

	for (i = 0; i < header->num_files; i++) {
		memcpy(&data[i].extrafield_len, &buffer[entrylist[i].filerecord_offset + 28], sizeof(short));
		memcpy(&data[i].comp_size, &buffer[entrylist[i].filerecord_offset + 18], sizeof(int));
		offset = 30 + entrylist[i].filerecord_offset + entrylist[i].filename_len + data[i].extrafield_len;
		len = data[i].comp_size;
		data[i].comp_data = malloc(len);

		memcpy(buf, &buffer[offset], len);
		buf[128] = '\0';
		strcpy(data[i].comp_data, buf);
	}
}

void parse_centdir(char *buffer)
{
	int offset = 0;

	for (int i = 0; i < header->num_files; i++) {
		memcpy(&entrylist[i].comp_size, &buffer[offset + header->centdir_offset + 20], sizeof(int));
		memcpy(&entrylist[i].filerecord_offset, &buffer[offset + header->centdir_offset + 42], sizeof(int));

		memcpy(&entrylist[i].filename_len, &buffer[offset + header->centdir_offset + 28], sizeof(short));
		memcpy(&entrylist[i].extrafield_len, &buffer[offset + header->centdir_offset + 30], sizeof(short));

		if (entrylist[i].comp_size > 128)
			exit(1);
		offset += 46 + entrylist[i].extrafield_len + entrylist[i].filename_len;
	}
}

int parse_head(char *buffer, int len)
{
	char magic[] = {0x50, 0x4B, 0x05, 0x06};
	int header_offset;

	for (int i = 0; i < len-4; i++) {
		if (memcmp(&buffer[i], magic, 4) == 0) {
			header_offset = i;
			memcpy(&header->num_files, &buffer[header_offset+10], sizeof(short));
			memcpy(&header->centdir_size, &buffer[header_offset+12], sizeof(int));
			memcpy(&header->centdir_offset, &buffer[header_offset+16], sizeof(int));
			return 0;
		}
	}
	return 1;
}

int main(int argc, char **argv)
{
	char *buffer;
	char buf[8];
	int len;

	read(0, buf,sizeof(buf));
	len = atoi(buf);
	buffer = (char *) malloc(len);
	fgets(buffer,len, stdin);

	header = malloc(sizeof(struct head));

	if (parse_head(buffer,len))
		exit(1);
	
	entrylist = malloc(sizeof(struct centdir) * header->num_files);
	parse_centdir(buffer);

	data = malloc(sizeof(struct dataentry) * header->num_files);
	parse_data(buffer, 0);
}
