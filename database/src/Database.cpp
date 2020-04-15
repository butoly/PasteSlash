#include "Database.h"
#define TESTING 1

Database& Database::getInstance(){
    if (TESTING)
    {
        static MockDatabase mo;
        return mo;
    }
    // prod code
}