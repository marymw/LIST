#ifndef LIST
#define LIST

enum ErrorsForList{
	
	NO_ERRORS,				//0
	CTOR_ERROR,				//1
	DTOR_ERROR,				//2
	LIST_UNDEFINED,			//3
	LACK_OF_MEMORY,			//4
	ERROR_IN_OPEN_LOG,  	//5
	ERROR_IN_OPEN_DUMP,		//6
	SECOND_CTOR_CALL,		//7
	LIST_NULL_PTR,			//8
	LIST_ELEM_NULL_PTR, 	//9
	LIST_MEM_OVERFL,    	//10
	ERROR_IN_INSERT_ELEM,	//11
	ERROR_IN_DELETE_ELEMENT,//12
	RESIZE_ERROR,			//13

};
//а есть разница между тем напишу я typedef или нет?

struct ListElem {

	int elemData;
	int elemNext;
	int elemPrev;
};

struct List{

	ListElem* element;
	int head;
	int tail;
	int free;
	int capacity;

};


const int START_CAPACITY_OF_LIST = 10;
const int POISON				 = (int)0xded32bad;
const int COEF_OF_RESIZE 		 = 2;
#ifdef DUMP
#define ListDump(listPtr) ListDump_(listPtr, __FUNCTION__)
#else
#define ListDump(listPtr) printf(" ");
#endif

#define LIST_OK(someListPtr) do{																							\
								if((int statusOfListCheckErrors = ListCheckErrors(someListPtr, __FUNCTION__)) != NO_ERRORS) \
									return statusOfListCheckErrors;															\
							 }while(0)																						\
	
#define CheckNull(stream, param, string, nameOfError) do {				       	\
												if (param != 0) {	   			\
													fprintf(stream, string);    \
													return nameOfError;			\
												}				       			\
								 			  } while(0)


#define CheckNullPtr(stream, param, string, nameOfError) do {			\
										if (param == nullptr) { 		\
											fprintf(stream, string);	\
											return nameOfError;			\
										}								\
									} while(0)


int ListCtor(List *someListPtr, size_t someListSize);
int ListDtor(List *someListPtr);

#endif