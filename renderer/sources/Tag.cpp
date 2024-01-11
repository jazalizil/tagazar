#include "Tag.h"

Tag::Tag(std::string v) : value(v), width(0) {
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

Tag::Tag() : value(""), width(0), color(0) {}

bool Tag::fit_width(int to_fit) {
    return this->width <= to_fit;
}

std::ostream& operator<<(std::ostream& out,  const Tag& t) {
    return out << "\033[" << int(t.color / 7) << ";" << 30 + t.color % 7 << "m" << t.value << "\033[0m";
}
