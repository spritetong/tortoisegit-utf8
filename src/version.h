#define FILEVER        1,7,5,1
#define PRODUCTVER     1,7,5,1
#define STRFILEVER     "1, 7, 5, 1\0"
#define STRPRODUCTVER  "1, 7, 5, 1\0"

#define TGIT_VERMAJOR             1
#define TGIT_VERMINOR             7
#define TGIT_VERMICRO             5
#define TGIT_VERBUILD			  1
#define TGIT_VERDATE			  __DATE__

#ifdef _WIN64
#define TGIT_PLATFORM		"64 Bit"
#else
#define TGIT_PLATFORM		"32 Bit"
#endif


