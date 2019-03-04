#ifndef __CROSS_FILE_H__
#define __CROSS_FILE_H__

#include <yaml-cpp/yaml.h>
#include <string>
#include "../BaseClass/NodeBase.h"
#include "../GUI/CButton.h"

using std::string;


CNodeBase* getNodePointer(string nodeType);

extern const string resourcePathPrefix;
extern const string configurePathPrefix;


#endif