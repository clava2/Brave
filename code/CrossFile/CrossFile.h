#define __DEBUG__

#ifdef __DEBUG__
#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>
#include <iostream>
#endif

// Debug
#ifdef __DEBUG__
extern log4cpp::Category& mainLog;
#endif