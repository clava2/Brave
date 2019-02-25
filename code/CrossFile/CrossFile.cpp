#include "CrossFile.h"

CNodeBase* getNodePointer(string nodeType)
{
    CNodeBase* result = NULL;
    if(nodeType == "button")
    {
        result = new CButton();
        return result;
    }
}