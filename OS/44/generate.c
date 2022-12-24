#include<stdio.h>
#include<stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdlib.h>

int main(){
	uint32_t arr1[5] = {0x48AB0000, 0xFC30, 0x2426, 0x83A6, 0x53AB};
	uint32_t arr2[5] = {0x0867, 0xCAB3, 0xD8AF, 0xE964, 0x8134};
	
	int fd = open("file.dat", O_WRONLY);

	if(fd == -1)
		exit(1);
	
	for(int i = 0; i < 5; i++){
		uint32_t temp = arr1[i];
		if(write(fd, &temp, 4) == -1)
			exit(1);
	}
	close(fd);
}
