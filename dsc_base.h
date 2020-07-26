#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <math.h>

typedef unsigned char   BYTE;
typedef unsigned short  WORD;
typedef unsigned int    WORD32;
typedef unsigned long   WORD64;
typedef short           SWORD;
typedef int             SWORD32;
typedef long            SWORD64;

typedef WORD            STATUS;
typedef BYTE            BOOLEAN;

#define FALSE           (BYTE)0
#define TRUE            (BYTE)1

#define SUCCESS         (WORD)0
#define ERR_UNKNOWN     (WORD)1
#define ERR_INVALD_PARAM    (WORD)2
#define ERR_MALLOC      (WORD)3

#define DSC_DEBUG_PRINT(format, args...) do { \
    printf("[%s:%s:%d] "format".\n", __FILE__, __FUNCTION__, __LINE__, \
    ##args); \
} while (FALSE) \



