#ifndef DATABASE_PASTEMANAGER_H
#define DATABASE_PASTEMANAGER_H

#include "dataFormat.h"
#include "gmock/gmock.h"

class BasePasteManager {
public:
    virtual ~BasePasteManager() = 0;
    virtual void addPaste(pasteFormat) = 0;
    virtual void deletePaste(std::string) = 0;
    virtual pasteFormat getPaste(std::string) = 0;
};

class PasteManager: BasePasteManager {
public:
    ~PasteManager() override = default;
    void addPaste(pasteFormat) override;
    void deletePaste(std::string) override;
    pasteFormat getPaste(std::string hash) override;
};

class MockPasteManager : BasePasteManager {
public:
    MOCK_METHOD1(addPaste, void (pasteFormat));
    MOCK_METHOD1(deletePaste, void (std::string));
    MOCK_METHOD1(getPaste, pasteFormat (std::string));
};

#endif // DATABASE_PASTEMANAGER_H
