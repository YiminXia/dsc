#include "../dsc_base.h"
#include "include/sq_list.h"
#include "source/sq_list_imp.c"

void main()
{
    T_SqList tSqList;
    STATUS retStatus = InitSqList(&tSqList);
    if (retStatus != SUCCESS)
    {
        DSC_DEBUG_PRINT("InitSqList return [%d]", retStatus);
        return;
    }
    int i;
    for(i = 0; i < 6; i++)
    {
        retStatus = ListInsert(&tSqList, 1, &i);
        if(retStatus != SUCCESS)
        {
            DSC_DEBUG_PRINT("ListInsert return [%d], Elem is [%d]", retStatus, i);
        }
    }
    retStatus = ListTraverse(&tSqList, Visit);
}