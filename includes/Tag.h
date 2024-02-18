#ifndef TAG_CLASS_H
#define TAG_CLASS_H

#include <cstdlib>
#include <sstream>
#include <cstring>
#include <iostream>
#include <sys/ioctl.h>
#include <stdio.h>
#include <vector>
#include <unistd.h>

class Tag
{
    private:
        std::string value;
        int width;
        int color;
    public:
        Tag();
        Tag(std::string v);
        friend std::ostream& operator<<(std::ostream& os, const Tag& t);
        bool fit_width(int width);
};

#endif // TAG_H
