#ifndef ANALYZER_H
#define ANALYZER_H

#include "global.h"

class Analyzer
{
public:
    Analyzer();

    /**
     * @brief judegeLightOperation 判断需要进行哪一种光照操作
     */
    virtual LightOpertion judegeLightOperation();
};

#endif // ANALYZER_H
