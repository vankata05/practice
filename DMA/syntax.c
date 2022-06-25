/*
calloc: //can allocate multiple blocks of memory and sets all the values to 0
    ptr = (cast-type*)calloc(n, element-size);//n is the number of elements
    example:
    ptr = (float*) calloc(25, sizeof(float));

malloc: //allocates a single block of memory with garbage value
    ptr = (cast-type*) malloc(byte-size)
    example:
    ptr = (int*) malloc(100 * sizeof(int));//masiv ot 100 integera

realloc:
    ptr = realloc(ptr, newSize);//ptw i reallocated to the new size
    example:
    ptr = realloc(ptr, n * sizeof(int));//n is the number of elements

memset: //not great if you want to fill with integers
    memset(ptr, x, element-size);//x is the value to be filled with
    example:
    memset(str + 13, '.', 8*sizeof(char));// Fill 8 characters starting from str[13] with '.'

free:
    free(ptr);