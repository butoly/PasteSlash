#ifndef PROJECT_ABSTRACTUSECASE_H
#define PROJECT_ABSTRACTUSECASE_H

#include "Models.h"
#include "PasteDBManager.h"

class AbstractUsecase {
public:
    virtual int execute() = 0;
    virtual ~AbstractUsecase(){};
};


#endif //PROJECT_ABSTRACTUSECASE_H
