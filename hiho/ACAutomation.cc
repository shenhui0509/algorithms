#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <queue>

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
    void feed(const std::string &word)
    {
        auto it = word.begin();
        auto p = root;
        for(; it != word.end(); ++it){
            if(p->next[*it - 'a'] == nullptr)
                p->next[*it - 'a'] = new node;
            p = p->next[*it - 'a'];
        }
        ++p->cnt;
    }

    void build_ac()
    {
        root->fail = nullptr;
        std::queue<decltype(root)> q;
        q.push(root);

        while(!q.empty()){
            auto tmp = q.front();
            q.pop();
            node *p;
            for(int i = 0; i < char_nums; ++i){
                if(tmp->next[i] != nullptr){
                    if(tmp == root)
                        tmp->next[i]->faile = root;
                    else{
                        p = tmp->fail;
                        while(p){
                            if(p->next[i] != nullptr){
                                tmp->next[i]->fail = p->next[i];
                                break;
                            }
                            p = p->fail;
                        }
                        if(!p) tmp->next[i]->fail = root;
                    }
                }
            }
        }
    }

    int search(const std::string &word)
    {
        int cnt = 0, t;
        auto p = root;
        auto it = word.begin();
        while(it != word.end()){
            t = *it - 'a';
            while(p->next[t] == nullptr && p != root)
                p = p->fail;
            p = p->next[t];
            if(p == root) p = root;
            auto tmp = p;
            while(tmp != root && tmp->cnt != -1){
                cnt += tmp->cnt;
                tmp->cnt = -1;
                tmp = tmp->fail;
            }
            ++it;
        }
        return cnt;
    }
private:
    void destroy(node *root)
    {
        for(int i = 0; i < char_nums; ++i){
            if(root->next[i] != nullptr)
                destroy(root->next[i]);
        }
        delete root;
        return;
    }
    node *root;
};
