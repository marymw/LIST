#include <stdio.h>
#include "List.h"

//TODO! listInsertBack; listInsertFront; listInsertBefore; listInsertAfter;listDeleteBack;listDeleteFront;listDelete; listInsertInstead;
//printfListElems;listSort;

int main (){

	List firstList = {};

	int statusOfListCtor = ListCtor(&firstList, START_CAPACITY_OF_LIST);//любое число можно передавать
	CheckNull(stdout, statusOfListCtor, "Ошибка создания list", CTOR_ERROR);

	int statusOfListDtor = ListDtor(&firstList);
	CheckNull(stdout, statusOfListDtor, "Ошибка удаления list", DTOR_ERROR);

	return 0;

}