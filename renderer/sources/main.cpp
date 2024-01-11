#include "Tag.h"
#include "Tags.h"

Tag rand_tag(std::vector<Tag>& tags) {
    int rand_idx = std::rand() % tags.size();

    return tags[rand_idx];
}

std::string get_tag_str()
{
    std::string s;
    s.reserve(tags_len);
    unsigned int i;
    for (i = 0; i < tags_len; i++) {
        s += tags_chars[i];
    }
    return s;
}

std::vector<Tag> get_tags(struct winsize& w) {
    std::string line;
    std::string tag;
    Tag jt;
    std::vector<Tag> tags;
    std::stringstream tags_stream(get_tag_str());

    while (tags_stream) {
        std::getline(tags_stream, line);
        if (line.compare("= FontSelect & Copy") == 0)  {
            jt = Tag(tag);
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
    std::vector<Tag> tags;

    srand (time(0));
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    tags = get_tags(w);
    std::cout << rand_tag(tags) << std::endl;
    return 0;
}
