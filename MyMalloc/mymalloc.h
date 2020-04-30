#ifndef mymalloc_h_
#define mymalloc_h_

#define malloc(x) mymalloc(x,__FILE__,__LINE__)
#define free(x) myfree(x,__FILE__,__LINE__)



#endif