#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Database.h"
#include "DatabaseManager.h"
#include "PasteManager.h"
#include "UserManager.h"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

/*
TEST(DatabaseTest, expect_addPaste)
{
    MockDatabase database;
    EXPECT_CALL(database, execQuery("")).Times(AtLeast(1));

    PasteManager pasteManager;
    pasteFormat someData;
    pasteManager.addPaste(someData);
}

TEST(DatabaseTest, expect_getPaste)
{
    MockDatabase& database = Database::getInstance();
    EXPECT_CALL(database, execQuery("")).Times(AtLeast(1));

    PasteManager pasteManager;
    std::string some_hash = "k41kjz2";
    pasteManager.getPaste(some_hash);
}

TEST(DatabaseTest, expect_deletePaste)
{
    MockDatabase& database = Database::getInstance();
    EXPECT_CALL(database, execQuery("")).Times(AtLeast(1));

    PasteManager pasteManager;
    std::string some_hash = "k41kjz2";
    pasteManager.deletePaste(some_hash);
}


TEST(DatabaseTest, expect_addUser)
{
    MockDatabase database;
    EXPECT_CALL(database, execQuery("")).Times(AtLeast(1));

    UserManager userManager;
    userFormat someNewUser;
    userManager.addUser(someNewUser);
}

TEST(DatabaseTest, expect_getUser)
{
    MockDatabase database;
    EXPECT_CALL(database, execQuery("")).Times(AtLeast(1));

    UserManager userManager;
    std::string some_username = "Dr_Pepper";
    userManager.getUser(some_username);
}

TEST(DatabaseTest, expect_deleteUser)
{
    MockDatabase database;
    EXPECT_CALL(database, execQuery("")).Times(AtLeast(1));

    UserManager userManager;
    std::string some_username = "Dr_Pepper";
    userManager.deleteUser(some_username);
}
*/

TEST(PasteManagerTest, expect_addPaste)
{
    MockPasteManager pasteManager;
    pasteFormat some_paste;
    EXPECT_CALL(pasteManager, addPaste(some_paste)).Times(AtLeast(1));

    DatabaseManager databaseManager;
    databaseManager.addPaste(some_paste);
}

TEST(PasteManagerTest, expect_getPaste)
{
    MockPasteManager pasteManager;
    std::string some_hash = "hash";
    EXPECT_CALL(pasteManager, getPaste(some_hash)).Times(AtLeast(1));

    DatabaseManager databaseManager;
    databaseManager.getPaste(some_hash);
}

TEST(PasteManagerTest, expect_deletePaste)
{
    MockPasteManager pasteManager;
    std::string some_hash = "hash";
    EXPECT_CALL(pasteManager, deletePaste(some_hash)).Times(AtLeast(1));

    DatabaseManager databaseManager;
    databaseManager.deletePaste(some_hash);
}

TEST(UserManagerTest, expect_addUser)
{
    MockUserManager userManager;
    userFormat userData;
    EXPECT_CALL(userManager, addUser(userData)).Times(AtLeast(1));

    DatabaseManager databaseManager;
    databaseManager.addUser(userData);
}

TEST(UserManagerTest, expect_getUser)
{
    MockUserManager userManager;
    std::string username = "username";
    EXPECT_CALL(userManager, getUser(username)).Times(AtLeast(1));

    DatabaseManager databaseManager;
    databaseManager.getUser(username);
}

TEST(UserManagerTest, expect_deleteUser)
{
    MockUserManager userManager;
    std::string username = "username";
    EXPECT_CALL(userManager, deleteUser(username)).Times(AtLeast(1));

    DatabaseManager databaseManager;
    databaseManager.deleteUser(username);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}