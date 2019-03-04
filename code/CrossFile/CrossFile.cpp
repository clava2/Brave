#include "CrossFile.h"

const string resourcePathPrefix = "../resources/";
const string configurePathPrefix = "../resources/configures/";


CNodeBase* getNodePointer(string nodeType)
{
    CNodeBase* result = NULL;
    if(nodeType == "button")
    {
        result = new CButton();
        return result;
    }
}