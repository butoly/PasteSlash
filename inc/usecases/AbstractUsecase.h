#ifndef PROJECT_ABSTRACTUSECASE_H
#define PROJECT_ABSTRACTUSECASE_H

#include "Models.h"

class AbstractUsecase {
public:
    virtual void execute() = 0;
    virtual ~AbstractUsecase(){};
};


#endif //PROJECT_ABSTRACTUSECASE_H
