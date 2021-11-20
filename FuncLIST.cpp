#include <stdio.h>
#include "List.h"
#include <stdlib.h>
#include <string.h>

// struct List{

// 	int *listData;
// 	int *listPrev;
// 	int *listNext;
// 	int head;
// 	int tail;
//  int free;
	
// };

static FILE *FileDump = NULL;
static FILE *logFile  = NULL;


int ListCtor(List *someListPtr, size_t someListSize) {

	CheckNullPtr(stdout, someListPtr, "Передан нулевой указатель в Ctor\n", LIST_UNDEFINED);

	logFile  = fopen("Listlog.txt", "w");
	CheckNullPtr(stdout, logFile, "Ошибка открытия файла Log\n", ERROR_IN_OPEN_LOG);
	
	FileDump = fopen("ListDump.html", "w");
	CheckNullPtr(stdout, FileDump, "Ошибка открытия файла Dump\n", ERROR_IN_OPEN_DUMP);

	someListPtr->listData = (int *)calloc(someListSize, sizeof(int));
	CheckNullPtr(logFile, someListPtr->listData, "Ошибка выделения памяти для listData\n", LACK_OF_MEMORY);

	someListPtr->listPrev = (int *)calloc(someListSize, sizeof(int));
	CheckNullPtr(logFile, someListPtr->listPrev, "Ошибка выделения памяти для listPrev\n", LACK_OF_MEMORY);

	memset(someListPtr->listPrev, -1, someListSize);
	(someListPtr->listPrev)[0] = 0;

	someListPtr->listNext = (int *)calloc(someListSize, sizeof(int));
	CheckNullPtr(logFile, someListPtr->listNext, "Ошибка выделения памяти для listData\n", LACK_OF_MEMORY);

	memset(someListPtr->listNext, -1, someListSize);
	(someListPtr->listNext)[0] = 0;

	someListPtr->head = 1;
	someListPtr->tail = 1;
	someListPtr->free = 2;

	return NO_ERRORS;
}


int ListDtor(List *someListPtr){

	free(someListPtr->listData);
	free(someListPtr->listPrev);
	free(someListPtr->listNext);

	someListPtr->head = 0;
	someListPtr->tail = 0;

	fclose(logFile);
	fclose(FileDump);

	return NO_ERRORS;
}
