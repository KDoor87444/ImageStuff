#include "oriPaths.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdint.h>
#include <string.h>

//Bitmap header is always 14 bytes in length. Keeping the struct packed is important due to this.
//Header is required
typedef struct {
	uint16_t type;
	uint32_t fileSize;
	uint16_t reserved1;
	uint16_t reserved2;
	uint32_t offset;
} __attribute__((packed)) BMPHeader;
//Comes right after bmp file's header.
typedef struct {
	uint32_t size;
	uint32_t width;
	uint32_t height;
	uint16_t planes;
	uint16_t bitsPerPixel;
	uint32_t compression;
	uint32_t imageSize;
	int32_t xResolution;
	int32_t yResolution;
	uint32_t numColors;
	uint32_t importantColors;
} __attribute__((packed)) BMPInfoHeader;

//The extra bit masks are optional.
//They can be 3 or 4 dwords in size (12 or 16 bytes)
typedef struct {
	uint32_t dword1;
	uint32_t dword2;
	uint32_t dword3;
} __attribute__((packed)) BMPExtraBitMasks3;
typedef struct {
	uint32_t dword1;
	uint32_t dword2;
	uint32_t dword3;
	uint32_t dword4;
} __attribute__((packed)) BMPExtraBitMasks4;

typedef struct {
	char *filePath;
	void *imgBuffer;
	BMPHeader *header;
	BMPInfoHeader *infoHeader;
	uint8_t *imageBytes;
} BMPImage;

BMPImage loadBMP(char *path) {
	FILE *file = fopen(path, "rb");
	if(file==NULL) {
		printf("Couldn't open file :(");
		return (BMPImage) {NULL};
	}
	fseek(file, 0L, SEEK_END);
	long int size=ftell(file);
	fseek(file, 0L, SEEK_SET);
	void* imgBuffer=malloc(size);
	fread(imgBuffer, size, 1, file);
	BMPHeader *header=(BMPHeader*)imgBuffer;
	BMPInfoHeader *infoHeader=(BMPInfoHeader*)(imgBuffer+sizeof(BMPHeader));
	uint8_t *imageBytes=(uint8_t*)(imgBuffer+sizeof(BMPHeader)+sizeof(BMPInfoHeader));
	return (BMPImage){path, imgBuffer, header, infoHeader, imageBytes};
}

int main() {
	char exePath[50];	
	getCurrentExePath(exePath, 50);
	char* imgPath=alloca(strlen(exePath)+strlen(PS".."PS"test.bmp"));
	strcpy(imgPath, exePath);
	strcat(imgPath, PS".."PS"test.bmp");	
	
	printf("path: %s\n", imgPath);
	FILE* file=fopen(imgPath, "rb");
	if(file==NULL) {
		printf("Did not open file");
		return 1; 
	}	
	
	BMPImage imageTest=loadBMP(imgPath);

	printf("[");
	for(int i = 0; i<(imageTest.infoHeader->height*imageTest.infoHeader->width); i++) {
		printf("%d, ", imageTest.imageBytes[i]);
	}
	printf("]\n");
	return 0;
}
