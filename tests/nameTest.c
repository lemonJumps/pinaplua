#include <stdio.h>

#include "nameDB.h"

#include "string.h"

#include "nameTest.h"
#include "tests.h"

void nameTest()
{
    printf("nameDB tests\n");

    {
        struct nameDB * DB = nameDBinit();

        char * target = "World";

        nameDBsetName(DB, "Hello", target);

        char * value;
        int result = nameDBgetPtr(DB, "Hello", ((void **)&value));
    
        printf(value);

        TEST(result == 0, "value was found in database", "value wasn't found in database")
        TEST(strcmp(value, "World") == 0, "database contains World in Hello", "database doesn't contain World in Hello");
        
    }

    {
        struct nameDB * DB = nameDBinit();

        char * target = "World";

        nameDBsetName(DB, "Hello", target);

        nameDBchangeName(DB, "Hello", "Save The");
        nameDBchangeName(DB, "Save The", "Hello");
        nameDBchangeName(DB, "Hello", "Save The");
        nameDBchangeName(DB, "Save The", "Hello");
        nameDBchangeName(DB, "Hello", "Save The");
        nameDBchangeName(DB, "Save The", "Hello");
        nameDBchangeName(DB, "Hello", "Save The");
        nameDBchangeName(DB, "Save The", "Hello");
        nameDBchangeName(DB, "Hello", "Save The");
        nameDBchangeName(DB, "Save The", "Hello");
        nameDBchangeName(DB, "Hello", "Save The");
        nameDBchangeName(DB, "Save The", "Hello");
        nameDBchangeName(DB, "Hello", "Save The");
        nameDBchangeName(DB, "Save The", "Hello");
        nameDBchangeName(DB, "Hello", "Save The");
        nameDBchangeName(DB, "Save The", "Hello");
        nameDBchangeName(DB, "Hello", "Save The");
        nameDBchangeName(DB, "Save The", "Hello");
        nameDBchangeName(DB, "Hello", "Save The");

        char * value;
        int result = nameDBgetPtr(DB, "Save The", ((void **)&value));
    
        printf(value);

        TEST(result == 0, "Save The was found in database", "Save The wasn't found in database")
        TEST(strcmp(value, "World") == 0, "database contains World in Save The", "database doesn't contain World in Save The");
        
    }
}
