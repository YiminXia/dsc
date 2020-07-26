/*
    线性表动态分配顺序存储结构
*/
#define LIST_INIT_SIZE 10
#define LIST_INC_SIZE 2

typedef SWORD32 ElemType;

typedef struct tag_SqList{
    ElemType    *ptBaseAddrOfSqList;
    WORD32      dw_LengthOfSqList;
    WORD32      dw_SizeOfSqList;
}T_SqList;

