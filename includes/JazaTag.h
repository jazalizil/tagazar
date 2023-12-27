#ifndef JAZA_TAG_CLASS_H
#define JAZA_TAG_CLASS_H

#include <string>
#include <cstdlib>
#include <sstream>
#include <cstring>
#include <iostream>
#include <sys/ioctl.h>
#include <stdio.h>
#include <vector>
#include <unistd.h>

class JazaTag
{
    private:
        std::string value;
        int width;
        int color;
    public:
        JazaTag();
        JazaTag(std::string v);
        friend std::ostream& operator<<(std::ostream& os, const JazaTag& jt);
        bool fit_width(int width);
};

#endif // JAZA_TAG_H
