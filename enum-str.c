#include "stdio.h"

#define str(x) #x
#define xstr(x) str(x)
#define foo apple

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


/* without second replace method */
enum my_enum {
	#define MY_ENUM_ITEM(_n, _v) _n = _v,
	#include "enum-str.h"
	#undef MY_ENUM_ITEM
};

const char *my_enum_to_string(enum my_enum e) {
switch (e) {
	#define MY_ENUM_ITEM(_n, _v) case _v: return #_n;
	#include "enum-str.h"
	#undef MY_ENUM_ITEM
	default: return " not in the list\n\r";
	}
}

int main() {
    int i;
    for( i = 0; i < 4; i++ ) {
        printf("enum %d as a string: %s\n", i, FRUIT_STRING[i]);
    }

    printf("%s\n", str(foo));    // convert to "foo"
    printf("%s\n", xstr(foo));   // convert to str(apple), second pass, convert to "apple"

    printf("%s = %d\n\r", my_enum_to_string(ABC), ABC );
	printf("%s = %d\n\r", my_enum_to_string(FOO), FOO );

}
