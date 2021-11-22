#include <stdio.h>
#include "List.h"
#include <stdlib.h>
#include <string.h>


static FILE *FileDump = NULL;
static FILE *logFile  = NULL;

static int IsInsertFunc (const char funcName);
static int IsDeleteFunc(const int funcName);
static int ListElemCtor(List* someListPtr);
static int SetPoisonToList(List *someListPtr);


// struct ListElem {

// 	int elemData;
// 	int elemNext;
// 	int elemPrev;
// };

// struct List{

// 	ListElem* element;
// 	int head;
// 	int tail;
// 	int free;
// 	int capacity;

// };


int ListCtor(List *someListPtr, int someListSize) {

	CheckNullPtr(stdout, someListPtr, "Передан нулевой указатель в Ctor\n", LIST_UNDEFINED);

	logFile  = fopen("Listlog.txt", "w");
	CheckNullPtr(stdout, logFile, "Ошибка открытия файла Log\n", ERROR_IN_OPEN_LOG);
	
	FileDump = fopen("ListDump.html", "w");
	CheckNullPtr(stdout, FileDump, "Ошибка открытия файла Dump\n", ERROR_IN_OPEN_DUMP);

	someListPtr->capacity = someListSize;

	someListPtr->element = (ListElem*)calloc(someListPtr->capacity + 1, sizeof(ListElem)); //+1??
	CheckNullPtr(logFile, someListPtr->element, "Ошибка выделения памяти для элемента\n", LACK_OF_MEMORY);

	int statusOfListElemCtor = ListElemCtor(someListPtr);
	CheckNullPtr(logFile, statusOfListElemCtor, "Ошибка заполнения элементов\n", CTOR_ERROR);	

	someListPtr->head = 1;
	someListPtr->tail = 1;
	someListPtr->free = 1;

	ListDump(someListPtr);

	return NO_ERRORS;
}


int ListDtor(List *someListPtr){

	int statusOfListCheckErrors = ListCheckErrors(someListPtr, __FUNCTION__);
	CheckNull(logFile, statusOfListCheckErrors, "Failed Dtor", DTOR_ERROR);

	int statusOfSetPoisonToList = SetPoisonToList(someListPtr);
	CheckNull(logFile, statusOfSetPoisonToList, "Failed Dtor", DTOR_ERROR);

	someListPtr->head = -1;
	someListPtr->tail = -1;
	someListPtr->free = -1;

	fclose(logFile);
	fclose(FileDump);

	free(someListPtr->element);

	return NO_ERRORS;
}


static int ListElemCtor(List* someListPtr){

	int statusOfListCheckErrors = ListCheckErrors(someListPtr, __FUNCTION__);
	CheckNull(logFile, statusOfListCheckErrors, "Failed to arrange parameters in a sheet element", CTOR_ERROR);

	for (int i = 1; i <= someListPtr->capacity; i++) {

		someListPtr->element[i].elemData = 0;
		someListPtr->element[i].elemNext = i + 1;
		someListPtr->element[i].elemPrev = -1;
	}

	someListPtr->element[list->capacity].next = 0;

	someListPtr->element[0].elemData = 0;
	someListPtr->element[0].elemNext = 0;
	someListPtr->element[0].elemPrev = -1;

	return NO_ERRORS;
}


int ListCheckErrors(List *someListPtr, const char funcName){

	if (strncmp(funcName, "ListCtor", 8) == 0){//8!!!!!!!!!!!

		// if(someListPtr->element != nullptr){
		// 	ListDump(someListPtr);
		// 	return SECOND_CTOR_CALL;
		// } //а нужно как-то в структуре прописать что там нулптр
		//туда в любом случае нулевой указатель не передадут
	}
	else{

		if (!someListPtr){
			return LIST_NULL_PTR;//+дамп или нет?
		}

		if (!(someListPtr->element)){
			return LIST_ELEM_NULL_PTR;//+дамп или нет?
		}

		if(IsInsertFunc(funcName)){

			if(someListPtr->free > someListPtr->capacity){
				ListDump(someListPtr);
				return LIST_MEM_OVERFL;
			}
			if(someListPtr->element[someListPtr->free].prev != -1){
				ListDump(someListPtr);
				return ERROR_IN_INSERT_ELEM;
			}
		}

		if (IsDeleteFunc(funcName)){
			if(someListPtr->head == someListPtr->free){
				ListDump(someListPtr);
				return ERROR_IN_DELETE_ELEMENT;
			}
		}
	}

	return NO_ERRORS;
}


static int IsInsertFunc(const char funcName){

	if(strncmp(funcName, "ListInsertBack", 14)   == 0 || strncmp(funcName, "ListInsertFront", 15) == 0 || 
	   strncmp(funcName, "ListInsertBefore", 16) == 0 || strncmp(funcName, "ListInsertAfter", 15) == 0)//или поставить на 1 больше длину ммм?

		return 1;

	return 0;
}


static int IsDeleteFunc(const int funcName){

	if(strncmp(funcName, "ListDeleteBack", 14) == 0 || strncmp(funcName, "ListDeleteFront", 15) == 0 ||
	   strncmp(funcName, "ListGetBack", 11)    == 0 || strncmp(funcName, "ListGetFront", 12)    == 0 ||
	   strncmp(funcName, "ListDelete", 10)     == 0 || strncmp(funcName, "ListGet", 7) == 0)//или поставить на 1 больше длину ммм?

		return 1;

	return 0;
}


static int SetPoisonToList(List *someListPtr){

	int statusOfListCheckErrors = ListCheckErrors(someListPtr, __FUNCTION__);
	CheckNull(logFile, statusOfListCheckErrors, "Failed to arrange parameters in a sheet element", DTOR_ERROR);

	for (int i = 0; i <= someListPtr->capacity; i++){
		someListPtr->element[i].elemData = POISON;
		someListPtr->element[i].elemNext = POISON;
		someListPtr->element[i].elemPrev = POISON;

	}

	return NO_ERRORS;
}


int ListResize(List *someListPtr){

	int statusOfListCheckErrors = ListCheckErrors(someListPtr, __FUNCTION__);
	CheckNull(logFile, statusOfListCheckErrors, "Failed in resize", RESIZE_ERROR);

	int lastCapacity = someListPtr->capacity;
	someListPtr->capacity *= COEF_OF_RESIZE;

	ListElem *newListElem = (ListElem *)realloc(someListPtr->element, (someListPtr->capacity + 1) * sizeof(ListElem));
	CheckNullPtr(logFile, someListPtr->element, "Ошибка выделения памяти для элемента\n", LACK_OF_MEMORY);

	someListPtr->element = newListElem;

	someListPtr->free = lastCapacity + 1;

	SetPoisonValuesAfterResize();

	ListDump(someListPtr);
	return NO_ERRORS;
}


int SetPoisonValuesAfterResize(List *someListPtr, int lastCapacity){

	int statusOfListCheckErrors = ListCheckErrors(someListPtr, __FUNCTION__);
	CheckNull(logFile, statusOfListCheckErrors, "Failed in resize", RESIZE_ERROR);

	for (int i = lastCapacity + 1; i <= someListPtr->capacity; i++){
		someListPtr->element[i].elemData = 0;
		someListPtr->element[i].elemNext = i + 1;
		someListPtr->element[i].elemPrev = -1;
	}

	someListPtr->element[list->capacity].next = 0;

	return NO_ERRORS;

}
