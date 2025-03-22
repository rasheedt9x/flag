#ifndef FLAG_H

#define FLAG_H

#define INVALID_INT -999999


int flag_GetBool(char *name);
int flag_GetInt(char *name);
char* flag_GetString(char *name);

void flag_StringVar(char *name, char *defaultVal, char *desc);
void flag_IntVar(char *name, int defaultVal, char *desc);
void flag_BoolVar(char *name, int defaultVal, char *desc);


void flag_Parse(int argc, char *argv[]);
#endif

