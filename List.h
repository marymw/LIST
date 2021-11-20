#ifndef LIST
#define LIST

enum ErrorsForList{
	NO_ERRORS,			//0
	CTOR_ERROR,			//1
	DTOR_ERROR,			//2
	LIST_UNDEFINED,		//3
	LACK_OF_MEMORY,		//4
	ERROR_IN_OPEN_LOG,  //5
	ERROR_IN_OPEN_DUMP	//6

};

struct List{

	int *listData;
	int *listPrev;
	int *listNext;
	int head;
	int tail;
	int free;

};
	
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