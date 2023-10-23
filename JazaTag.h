#ifndef JAZA_TAG_CLASS_H
#define JAZA_TAG_CLASS_H

#include <string>
#include <iostream>

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
