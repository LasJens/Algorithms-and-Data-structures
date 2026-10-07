#include <vector>
#include <iostream>

const int K = 26;
class Trie {
 private:
    struct Node {
        Node() : term(0), link(nullptr), to(K), link_cnt(false) {
        }
        int term = 0;
        char c = 0;
        bool link_cnt = false;
        std::shared_ptr<Node> link, parent;
        std::vector <std::shared_ptr<Node> > to;
    };
    std::shared_ptr<Node> root;

public:
    Trie() : root(new Node()) {
    }

    void add_string(const std::string& s) {
        Node* temp = root.get();
        for (int i = 0; i < s.length(); ++i) {
            if (temp->to[s[i] - 'a'] == nullptr) {
                temp->to[s[i] - 'a'] = std::make_shared<Node>();
            }
            temp = temp->to[s[i] - 'a'].get();
        }
        temp->term += 1;
    }

    int count(const std::string& s) {
        Node* temp = root.get();
        for (int i = 0; i < s.length(); ++i) {
            if (temp->to[s[i] - 'a'] == nullptr) {
                return 0;
            }
            temp = temp->to[s[i] - 'a'].get();
        }
        return temp->term;
    }

    void BuildExitSuffixReferences() {
        root.link = nullptr;
        std::queue<int64_t> queue;
        for (auto& pair: st[0].next) {
            queue.push(pair.second);
        }
        int64_t tmp = 0;
        while (!queue.empty()) {
            tmp = queue.front();
            queue.pop();
            int64_t suff_link = st[tmp].link;
            if (suff_link != 0) {
                if (st[suff_link].is_terminal) {
                    st[tmp].exit_link = suff_link;
                } else {
                    st[tmp].exit_link = st[suff_link].exit_link;
                }
            }
            for (auto& pair: st[tmp].next) {
                queue.push(pair.second);
            }
        }
    }




};