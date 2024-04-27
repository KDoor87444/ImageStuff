#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdint.h>

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
	BMPHeader header;
	BMPInfoHeader infoHeader;
	uint8_t *colorBytes;
} BMPImage24bitUC;

int main() {
	FILE* file=fopen("C:\\Users\\Oridubi\\Documents\\Programming\\ImageStuff\\test.bmp", "rb");
	if(file==NULL) {
		printf("Did not open file");
		return 1; 
	}	
	
	unsigned long originalPos=ftell(file);
	BMPHeader header;
	BMPInfoHeader infoHeader;
	fread(&header, sizeof(header), 1, file);
	fread(&infoHeader, sizeof(infoHeader), 1, file);
	fseek(file, 0, header.offset);
	unsigned int sizeOfImage=header.fileSize-header.offset+1;
	uint8_t *colorBytes=malloc(sizeOfImage);
	fread(colorBytes, sizeOfImage, 1, file);
	printf("[");
	for(int i = 0; i<sizeOfImage/sizeof(uint8_t); i++) {
		printf("%d, ", colorBytes[i]);
	}
	printf("]\n");
	printf("header offset: %d\n", header.offset);
	printf("file size: %d\n", header.fileSize);
	printf("info header width: %d\n", infoHeader.width);
	printf("bytes per pixel: %d\n", infoHeader.bitsPerPixel/8);
	printf("bytes total: %d\n", sizeOfImage);
	return 0;
}
