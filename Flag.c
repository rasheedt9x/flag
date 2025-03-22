#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FLAGS 100

typedef enum FlagType {
    STRING,
    INT,
    BOOL
} FlagType;


typedef struct Flag {
    char* argName;
    char* desc;
    FlagType type;
    void* value;  
} Flag;

Flag flags[MAX_FLAGS];
int flagCount = 0;

void flag_Add(char *name, void* defaultVal, char *desc, FlagType type) {
    flags[flagCount].argName = name;
    flags[flagCount].desc = desc;
    flags[flagCount].type = type;

    if (type == STRING) {
        flags[flagCount].value = strdup((char*) defaultVal);
    } else {
        flags[flagCount].value = malloc(sizeof(int));
        // deref then assign value
        *(int*)flags[flagCount].value = *(int*)defaultVal;
    }
    flagCount++;
}


void flag_StringVar(char* argName, char* defaultVal, char* description) {
    flag_Add(argName,defaultVal,description, STRING);
}

void flag_IntVar(char* argName, int defaultVal, char* description) {
    flag_Add(argName,&defaultVal,description, INT);
}


void flag_BoolVar(char* argName, int defaultVal, char* description) {
    flag_Add(argName,&defaultVal,description, INT);
}


int flag_GetInt(char *name) {
    int found = 0;
    for (int i=0; i<flagCount; i++) {
        if ( strcmp(name, flags[i].argName) == 0) {
            found = 1;
            return *(int*) flags[i].value;
        }
    }
    if (!found) {    
        fprintf(stderr, "No arg with name %s found", name);
    }
    return -999999;
}


int flag_GetBool(char *name) {
    int found = 0;
    for (int i=0; i<flagCount; i++) {
        if ( strcmp(name, flags[i].argName) == 0) {
            found = 1;
            return *(int*) flags[i].value;
        }
    }
    if (!found) {    
        fprintf(stderr, "No arg with name %s found", name);
    }
    return -999999;
}


char* flag_GetString(char *name) {
    int found = 0;
    for (int i=0; i<flagCount; i++) {
        if ( strcmp(name, flags[i].argName) == 0) {
            return strdup(flags[i].value);
        } else {
            fprintf(stderr, "No arg with name %s found", name);
        }
    }
    
    if (!found) {    
        fprintf(stderr, "No arg with name %s found", name);
    }
    return NULL;
}


void flag_Parse(int argc, char* argv[]) {
    for (int i=1; i<argc; i++) {
        // flag detected
        if (argv[i][0] == '-') {
//            printf("flag encountered %s\n", argv[i]+1);
            int found = 0;
            //loop thru flags
            for (int j=0; j<flagCount; j++) {
                if (strcmp(argv[i]+1, flags[j].argName) == 0) {
                    found = 1;
                    if (flags[j].type ==  BOOL) {
                        // deref --> assign value
                        *(int*)flags[j].value = 1;
                    } else if(i+1 < argc) {
                        if (  argv[i+1][0] == '-'  ) {
                            fprintf(stderr,"expected arg \''%s\' value", argv[i]+1);
                        }
                        if (flags[j].type ==STRING) {
                            flags[j].value = strdup(argv[i+1]);
                        } else if (flags[j].type == INT) {
                            *(int*)flags[j].value = atoi(argv[i+1]);                        
                        }
                        i++;
                    }
                    break;
                }
           }

            if(!found) {
                fprintf(stderr,"Unknown flag %s\n", argv[i]+1);                
            }
        }
    }
}


