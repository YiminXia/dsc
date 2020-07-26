STATUS InitSqList(T_SqList * ptSqList)
{
    STATUS      wRetStatus = ERR_UNKNOWN;
    ElemType   *ptlElem = NULL;

    if(NULL == ptSqList)
    {
        DSC_DEBUG_PRINT("input param is invalid");
        wRetStatus = ERR_INVALD_PARAM;
        return wRetStatus;
    }

    ptlElem = (ElemType *)malloc(sizeof(ElemType) * LIST_INIT_SIZE);
    if(NULL == ptlElem)
    {
        DSC_DEBUG_PRINT("malloc return NULL");
        wRetStatus = ERR_MALLOC;
        return wRetStatus;
    }
    ptSqList->ptBaseAddrOfSqList = ptlElem;
    ptSqList->dw_LengthOfSqList = 0;
    ptSqList->dw_SizeOfSqList = LIST_INIT_SIZE;
    wRetStatus = SUCCESS;
    return wRetStatus;
}

STATUS DestroySqList(T_SqList * ptSqList)
{
    STATUS      wRetStatus = ERR_UNKNOWN;
    ElemType    *ptlElem = NULL;

    if(NULL == ptSqList)
    {
        DSC_DEBUG_PRINT("input param is invalid");
        wRetStatus = ERR_INVALD_PARAM;
        return wRetStatus;
    }

    ptlElem = ptSqList->ptBaseAddrOfSqList;
    memset(ptlElem, 0, ptSqList->dw_SizeOfSqList * sizeof(ElemType));
    free(ptlElem);

    memset(ptSqList, 0, sizeof(T_SqList));
    free(ptSqList);

    wRetStatus = SUCCESS;
    return wRetStatus;
}

STATUS ClearSqList(T_SqList * ptSqList)
{
    STATUS      wRetStatus = ERR_UNKNOWN;

    if(NULL == ptSqList)
    {
        DSC_DEBUG_PRINT("input param is invalid");
        wRetStatus = ERR_INVALD_PARAM;
        return wRetStatus;
    }

    ptSqList->ptBaseAddrOfSqList = NULL;
    ptSqList->dw_LengthOfSqList = 0;
    wRetStatus = SUCCESS;
    return wRetStatus;
}

STATUS ListEmpty(T_SqList * ptSqList, BOOLEAN * pbRet)
{
    STATUS  wRetStatus = ERR_UNKNOWN;

    if(NULL == ptSqList || NULL == pbRet)
    {
        DSC_DEBUG_PRINT("input param is invalid");
        wRetStatus = ERR_INVALD_PARAM;
        return wRetStatus;
    }

    if(ptSqList->dw_LengthOfSqList > 0)
        *pbRet = TRUE;
    else
        *pbRet = FALSE;
    wRetStatus = SUCCESS;
    return wRetStatus;
}

STATUS ListLength(T_SqList *ptSqList, WORD32 * pwLength)
{
    STATUS wRetStatus = ERR_UNKNOWN;
    if(NULL == ptSqList || NULL == pwLength)
    {
        DSC_DEBUG_PRINT("input param is invalid");
        wRetStatus = ERR_INVALD_PARAM;
        return wRetStatus;
    }

    *pwLength = ptSqList->dw_LengthOfSqList;
    wRetStatus = SUCCESS;
    return wRetStatus;
}

STATUS GetElem(T_SqList *ptSqList, WORD32 dwIndex, ElemType *ptElem)
{
    STATUS wRetStatus = ERR_UNKNOWN;
    if(NULL == ptSqList || NULL == ptElem)
    {
        DSC_DEBUG_PRINT("input param is invalid");
        wRetStatus = ERR_INVALD_PARAM;
        return wRetStatus;
    }

    if(dwIndex == 0 || dwIndex > ptSqList->dw_LengthOfSqList)
    {
        DSC_DEBUG_PRINT("the input param dwIndex is %d, and dw_LengthOfSqList is %d", 
            dwIndex, ptSqList->dw_LengthOfSqList);
        return wRetStatus;
    }
    *ptElem = *(ptSqList->ptBaseAddrOfSqList + (dwIndex - 1));
    wRetStatus = SUCCESS;
    return wRetStatus;
}

BOOLEAN compare(ElemType *ptElem1, ElemType *ptElem2)
{
    if(NULL == ptElem1 || NULL == ptElem2)
    {
        DSC_DEBUG_PRINT("input param is invalid");
        return FALSE;
    }

    if(*ptElem1 == *ptElem2)
        return TRUE;
    return FALSE;
}

STATUS LocateElem(T_SqList *ptSqList, ElemType *ptElem, BOOLEAN (*p_compare)(ElemType *, ElemType *), WORD32 *
pwRetIndex)
{
    STATUS wRetStatus = ERR_UNKNOWN;
    WORD32 dwIndex = 0;
    BOOLEAN bTmp = FALSE;

    if(NULL == ptSqList || NULL == ptElem || NULL == p_compare || NULL == pwRetIndex)
    {
        DSC_DEBUG_PRINT("input param is invalid");
        wRetStatus = ERR_INVALD_PARAM;
        return wRetStatus;
    }

    for(; dwIndex < ptSqList->dw_LengthOfSqList; dwIndex++)
    {
        bTmp = (*p_compare)(ptElem, (ptSqList->ptBaseAddrOfSqList + (dwIndex - 1)));
        if(bTmp)
        {
            *pwRetIndex = dwIndex;
            wRetStatus = SUCCESS;
            return wRetStatus;
        }
    }
    *pwRetIndex = 0;
    wRetStatus = SUCCESS;
    return wRetStatus;
}

STATUS PriorElem(T_SqList *ptSqList, ElemType *ptElem, ElemType *ptPreElem)
{
    STATUS wRetStatus = ERR_UNKNOWN;
    WORD32  dwIndex = 0;
    STATUS wTmp = ERR_UNKNOWN;

    if(NULL == ptSqList || NULL == ptElem || NULL == ptPreElem)
    {
        DSC_DEBUG_PRINT("input param is invalid");
        wRetStatus = ERR_INVALD_PARAM;
        return wRetStatus;
    }

    wTmp = LocateElem(ptSqList, ptElem, compare, &dwIndex);
    if(SUCCESS != wTmp)
    {
        DSC_DEBUG_PRINT("LocateElem return FALSE");
        return wRetStatus;
    }
    else
    {
        if(dwIndex == 1)
        {
            DSC_DEBUG_PRINT("we find the postion of *ptElem(%d) in SqList is the first one", *ptElem);
            return wRetStatus;
        }
        else if(dwIndex == 0)
        {
            DSC_DEBUG_PRINT("can not find postion of *ptElem(%d) in SqList", *ptElem);
            return wRetStatus;
        }
        else
        {
            *ptPreElem = *(ptSqList->ptBaseAddrOfSqList + (dwIndex - 2));
            wRetStatus = SUCCESS;
            return wRetStatus;
        }
    }
}

STATUS NextElem(T_SqList *ptSqList, ElemType *ptElem, ElemType *ptNextElem)
{
    STATUS wRetStatus = ERR_UNKNOWN;
    WORD32 dwIndex = 0;
    STATUS wTmp = ERR_UNKNOWN;

    if(NULL == ptSqList || NULL == ptElem || NULL == ptNextElem)
    {
        DSC_DEBUG_PRINT("input param is invalid");
        wRetStatus = ERR_INVALD_PARAM;
        return wRetStatus;
    }

    wTmp = LocateElem(ptSqList, ptElem, compare, &dwIndex);
    if(SUCCESS != wTmp)
    {
        DSC_DEBUG_PRINT("LocateElem return FALSE");
        return wRetStatus;
    }
    else
    {
        if(dwIndex == ptSqList->dw_LengthOfSqList)
        {
            DSC_DEBUG_PRINT("we find the postion of *ptElem(%d) in SqList is the last one", *ptElem);
            return wRetStatus;
        }
        else if(dwIndex == 0)
        {
            DSC_DEBUG_PRINT("can not find postion of *ptElem(%d) in SqList", *ptElem);
            return wRetStatus;
        }
        else
        {
            *ptElem = *(ptSqList->ptBaseAddrOfSqList + dwIndex);
            wRetStatus = SUCCESS;
            return wRetStatus;
        }
    }
}

STATUS ListInsert(T_SqList *ptSqList, WORD32 dwIndexForInsertPos, ElemType *ptElemForInsert)
{
    STATUS wRetStatus = ERR_UNKNOWN;
    WORD32 dwIndex = 0;

    if(NULL == ptSqList || NULL == ptElemForInsert)
    {
        DSC_DEBUG_PRINT("input param is invalid");
        wRetStatus = ERR_INVALD_PARAM;
        return wRetStatus;
    }

    if(dwIndexForInsertPos < 1 || dwIndexForInsertPos > (ptSqList->dw_LengthOfSqList) + 1)
    {
        DSC_DEBUG_PRINT("dwIndexForInserPos is %d and the Length of SqList is %d", 
            dwIndexForInsertPos, ptSqList->dw_LengthOfSqList);
        return wRetStatus;
    }

    if(ptSqList->dw_LengthOfSqList == ptSqList->dw_SizeOfSqList)
    {
        ptSqList->ptBaseAddrOfSqList = (ElemType *)realloc(ptSqList->ptBaseAddrOfSqList, 
            (ptSqList->dw_SizeOfSqList + LIST_INC_SIZE)*sizeof(ElemType));
        if(NULL == ptSqList->ptBaseAddrOfSqList)
        {
            DSC_DEBUG_PRINT("call realloc filed");
            return wRetStatus;
        }
        ptSqList->dw_SizeOfSqList = ptSqList->dw_SizeOfSqList + LIST_INC_SIZE;
    }
    // *1*2*3*4*5*six
    if(dwIndexForInsertPos == ptSqList->dw_LengthOfSqList + 1)
    {
        *(ptSqList->ptBaseAddrOfSqList + (dwIndexForInsertPos - 1)) = *ptElemForInsert;
    }
    else
    {
        for(dwIndex = ptSqList->dw_LengthOfSqList; dwIndex >= dwIndexForInsertPos; dwIndex--)
        {
            *(ptSqList->ptBaseAddrOfSqList + dwIndex) = *(ptSqList->ptBaseAddrOfSqList + (dwIndex - 1));
        }
        *(ptSqList->ptBaseAddrOfSqList + dwIndex) = *(ptElemForInsert);
    }
    ptSqList->dw_LengthOfSqList = ptSqList->dw_LengthOfSqList + 1;
    wRetStatus = SUCCESS;
    return wRetStatus;
}

STATUS ListDelete(T_SqList *ptSqList, WORD32 dwIndexForDel, ElemType * ptElemForDel)
{
    STATUS wRetStatus = ERR_UNKNOWN;
    WORD32 dwIndex = 0;

    if(NULL == ptSqList || NULL == ptElemForDel)
    {
        DSC_DEBUG_PRINT("input param is invalid");
        wRetStatus = ERR_INVALD_PARAM;
        return wRetStatus;
    }

    if(dwIndexForDel < 1 || dwIndexForDel > ptSqList->dw_LengthOfSqList)
    {
        DSC_DEBUG_PRINT("dwIndexForDel is %d and the length of the SqList is %d",
            dwIndexForDel, ptSqList->dw_LengthOfSqList);
        return wRetStatus;
    }
    //*1*2*3*4*5
    for(dwIndex = dwIndexForDel; dwIndex < (ptSqList->dw_LengthOfSqList); dwIndex++)
    {
        *(ptSqList->ptBaseAddrOfSqList + (dwIndex - 1)) = *(ptSqList->ptBaseAddrOfSqList + dwIndex);
    }
    ptSqList->dw_LengthOfSqList = ptSqList->dw_LengthOfSqList - 1;
    wRetStatus = SUCCESS;
    return wRetStatus;
}

STATUS ListTraverse(T_SqList *ptSqList, STATUS (*pfVisit)(ElemType *))
{
    STATUS wRetStatus = ERR_UNKNOWN;
    WORD32 dwIndex = 0;

    if(NULL == ptSqList || NULL == pfVisit)
    {
        DSC_DEBUG_PRINT("input param is invalid");
        wRetStatus = ERR_INVALD_PARAM;
        return wRetStatus;
    }

    for(dwIndex = 1; dwIndex <= ptSqList->dw_LengthOfSqList; dwIndex++)
    {
        wRetStatus = pfVisit(ptSqList->ptBaseAddrOfSqList + (dwIndex -  1));
        if(SUCCESS != wRetStatus)
        {
            DSC_DEBUG_PRINT("pfVisit return FALSE");
            return wRetStatus;
        }
    }
    wRetStatus = SUCCESS;
    return wRetStatus;
}

STATUS Visit(ElemType *ptElem)
{
    STATUS wRetStatus = ERR_UNKNOWN;

    if(NULL == ptElem)
    {
        DSC_DEBUG_PRINT("input param is invalid");
        wRetStatus = ERR_INVALD_PARAM;
        return wRetStatus;
    }

    DSC_DEBUG_PRINT("*ptElem is %d", *ptElem);
    wRetStatus = SUCCESS;
    return wRetStatus;
}
