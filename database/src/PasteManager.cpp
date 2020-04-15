#include "PasteManager.h"
#include "Database.h"
#include "SqlGenerator.h"

void PasteManager::addPaste(pasteFormat data) {
    Meta meta = {}; // generate meta about paste (probably read from file)
    SqlGenerator sqlGenerator;
    std::string generated_query = sqlGenerator.generateAddQuery(data, meta);
    Database::getInstance().execQuery(generated_query);
}
