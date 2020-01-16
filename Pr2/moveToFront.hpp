#ifndef MOVETOFRONT_HH
#define MOVETOFRONT_HH

#include <string>

class MoveToFront {
protected:
    static int indexOf(const char list[256], char c);
    static void moveToFront(char list[256], int idx);
public:
    static std::string compress(const char * c);
    static std::string decompress(const char * c);
};

#endif