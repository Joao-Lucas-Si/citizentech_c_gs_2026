#ifndef StringH
#define StringH
int startWith(char* original, char* content);
char* stringf(int length, char * format, ...);

char** splitFirst(char* original, char character);

char** splitFirstNested(char* original, char character);
#endif