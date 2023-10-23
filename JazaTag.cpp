#include <sstream>
#include "JazaTag.h"

JazaTag::JazaTag(std::string v) : value(v), width(0) {
    std::string line;
    std::stringstream s(value);
    int width;
    
    while (std::getline(s, line)) {
        width = strlen(line.c_str());
        if (width > this->width) {
            this->width = width;
        }
    }
    this->color = std::rand() % 13 + 1;
}

JazaTag::JazaTag() : value(""), width(0), color(0) {}

bool JazaTag::fit_width(int to_fit) {
    return this->width <= to_fit;
}

std::ostream& operator<<(std::ostream& out,  const JazaTag& jt) {
    return std::cout << "\033[" << int(jt.color / 7) << ";" << 30 + jt.color % 7 << "m" << jt.value << "\033[0m";
}
