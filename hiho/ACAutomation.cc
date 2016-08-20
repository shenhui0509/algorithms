#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>

constexpr int char_nums = 26;

struct node
{
    node *fail;
    node *next[char_nums];
    int cnt;
    node():
        fail(nullptr), cnt(0)
        {
            std::initialize_fill_n(next, char_nums, nullptr);
        }
};

class ACAutomation
{
public:
    ACAutomation():
        node(new node)
        {}
    ~ACAutomation():
        {
            destroy(root);
        }
private:
    void destroy(node *root);
    node *root;
};
