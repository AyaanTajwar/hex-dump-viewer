#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



#define BYTES_PER_ROW 16

static char* parseArgs(int argc, char* argv[]);

static void readFile(FILE* file);

static void printRow(const unsigned char bytesBuffer[], size_t bytesRead, int rowNumber);

static void printByteOffset(int rowNumber);
static void printRawBytes(const unsigned char bytesBuffer[], size_t bytesRead);
static void printASCII(const unsigned char bytesBuffer[], size_t bytesRead);

static void printPadding(size_t bytesRead);



int main(int argc, char* argv[])
{
	char* fileName = parseArgs(argc, argv);

	if (fileName == NULL)
	{
		return EXIT_FAILURE;
	}


	FILE* file = fopen(fileName, "rb");

	if (file == NULL)
	{
		perror(fileName);
		return EXIT_FAILURE;
	}


	readFile(file);

	fclose(file);

	return EXIT_SUCCESS;
}

static char* parseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Wrong number of arguments\nUsage: hd -i <file>\n");
		return NULL;
	}

	if (strcmp(argv[1], "-i") != 0)
	{
		fprintf(stderr, "Invalid flag used\nUsage: hd -i <file>\n");
		return NULL;
	}

	return argv[2];
}


static void readFile(FILE* file)
{
	unsigned char bytesBuffer[BYTES_PER_ROW] = {0};

	int character = fgetc(file);

	int rowNumber = 0;

	size_t bytesRead = 0;


	while (character != EOF)
	{
		if (bytesRead >= BYTES_PER_ROW)
		{
			printRow(bytesBuffer, bytesRead, rowNumber);

			bytesRead = 0;
			memset(bytesBuffer, 0, sizeof(bytesBuffer));

			rowNumber++;
		}
		
		bytesBuffer[bytesRead] = character;

		character = fgetc(file);
		bytesRead++;
	}

	if (bytesRead > 0)
	{
		printRow(bytesBuffer, bytesRead, rowNumber);
		printf("\n");
	}
}



static void printRow(const unsigned char bytesBuffer[], size_t bytesRead, int rowNumber)
{
	printByteOffset(rowNumber);
	printRawBytes(bytesBuffer, bytesRead);
	printPadding(bytesRead);
	printASCII(bytesBuffer, bytesRead);
}



static void printByteOffset(int rowNumber)
{
	if (rowNumber == 0)
	{
		printf("%08X ", rowNumber);
	}
	else
	{
		printf("\n%08X ", rowNumber * BYTES_PER_ROW);
	}
}

static void printRawBytes(const unsigned char bytesBuffer[], size_t bytesRead)
{
	for (size_t i = 0; i < bytesRead; i++)
	{
		printf("%02X ", bytesBuffer[i]);
	}
}

static void printASCII(const unsigned char bytesBuffer[], size_t bytesRead)
{
	char charBuffer[BYTES_PER_ROW + 1] = {0};

	for (size_t i = 0; i < bytesRead; i++)
	{
		if (isprint(bytesBuffer[i]))
		{
			charBuffer[i] = bytesBuffer[i];
		}
		else
		{
			charBuffer[i] = '.';
		}
	}

	printf("%s", charBuffer);
}



static void printPadding(size_t bytesRead)
{
	for (size_t i = bytesRead; i < BYTES_PER_ROW; i++)
	{
		printf("   ");
	}
}
