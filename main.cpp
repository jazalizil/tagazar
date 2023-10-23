#include <iostream>
#include <sstream>
#include <string>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include "JazaTag.h"
#include "jaza_ascii.h"

JazaTag rand_tag(std::vector<JazaTag>& tags) {
    int rand_idx = std::rand() % tags.size();

    return tags[rand_idx];
}

std::string get_jaza_ascii_str()
{
    std::string s;
    s.reserve(jaza_ascii_len);
    int i;
    for (i = 0; i < jaza_ascii_len; i++) {
        s += jaza_ascii_chars[i];
    }
    return s;
}

std::vector<JazaTag> get_tags(struct winsize& w) {
    std::string line;
    std::string tag;
    JazaTag jt;
    std::vector<JazaTag> tags;
    std::stringstream jaza_ascii(get_jaza_ascii_str());

    while (jaza_ascii) {
        std::getline(jaza_ascii, line);
        if (line.compare("= FontSelect & Copy") == 0)  {
            jt = JazaTag(tag);
            if (jt.fit_width(w.ws_col)) {
                tags.push_back(jt);
            }
            tag = "";
        } else {
            tag += "\n" + line;
        }
    }
    return tags;
}

int main() {
    struct winsize w;
    std::vector<JazaTag> tags;

    srand (time(0));
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    tags = get_tags(w);
    std::cout << rand_tag(tags) << std::endl;
    return 0;
}
