#ifndef MOVETOFRONT_HH
#define MOVETOFRONT_HH

#include <string>

class MoveToFront {
protected:
    static unsigned int indexOf(const char list[256], char c);
    static void moveToFront(char list[256], int idx);
public:
    static char * compress(const char * c, const int l);
    static char * decompress(const char * c, const int l);
};

#endif