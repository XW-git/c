#include "stdio.h"

// prepare 
#define FOREACH_FRUIT(FRUIT) \
        FRUIT(apple)   \
        FRUIT(orange)  \
        FRUIT(grape)   \
        FRUIT(banana)  \

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,


// enterty 
enum FRUIT_ENUM {
    FOREACH_FRUIT(GENERATE_ENUM)    // step1, replace with              step2, replace with
};                                  //  GENERATE_ENUM(apple)   \        apple, \
                                    //  GENERATE_ENUM(orange)  \        orange, \
                                    //  GENERATE_ENUM(grape)   \        grape, \
                                    //  GENERATE_ENUM(banana)  \        banana, \ 


static const char *FRUIT_STRING[] = {
    FOREACH_FRUIT(GENERATE_STRING)
};

int main() {
    int i;
    for( i = 0; i < 4; i++ ) {
        printf("enum %d as a string: %s\n", i, FRUIT_STRING[i]);
    }
        
}
