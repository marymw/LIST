#include <stdio.h>
#include "List.h"

int main (){

	List firstList = {};

	int statusOfListCtor = ListCtor(&firstList, 10);//любое число можно передавать
	CheckNull(stdout, statusOfListCtor, "Ошибка создания list", CTOR_ERROR);

	int statusOfListDtor = ListDtor(&firstList);
	CheckNull(stdout, statusOfListDtor, "Ошибка удаления list", DTOR_ERROR);

	return 0;

}