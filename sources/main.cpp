#include "Tag.h"
#include "tags.h"

Tag rand_tag(std::vector<Tag>& tags) {
    int rand_idx = std::rand() % tags.size();

    return tags[rand_idx];
}

std::vector<Tag> get_tags(struct winsize& w) {
    Tag t;
    std::vector<Tag> tags;
    unsigned int i = 0;

    while (i < TAGS_SIZE) {
        t = Tag(TAGS[i]);
        if (t.fit_width(w.ws_col)) {
            tags.push_back(t);
        }
        i++;
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
