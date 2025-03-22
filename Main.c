#include "./Flag.h"
#include<stdio.h>

int main(int argc, char *argv[]) {
    flag_StringVar("name","default", "Some name");
    flag_IntVar("age", 20, "Age sum");
    flag_BoolVar("bull", 0, "demo bool");
    flag_Parse(argc, argv);

    printf("name: %s\n", flag_GetString("name"));  
    printf("age: %d\n", flag_GetInt("age"));
    printf("bull: %d\n", flag_GetBool("bull"));
    printf("age1: %d\n", flag_GetInt("age1"));
}
