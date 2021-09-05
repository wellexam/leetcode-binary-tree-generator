#include <deque>
#include <sstream>
#include <string>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() :
        val(0), left(nullptr), right(nullptr) {
    }
    TreeNode(int x) :
        val(x), left(nullptr), right(nullptr) {
    }
    TreeNode(int x, TreeNode *left, TreeNode *right) :
        val(x), left(left), right(right) {
    }
};

//Code of this function is from https://stackoverflow.com/a/29752943/14414453
void replaceAll(std::string &source, const std::string &from, const std::string &to) {
    std::string newString;
    newString.reserve(source.length()); // avoids a few memory allocations

    std::string::size_type lastPos = 0;
    std::string::size_type findPos;

    while (std::string::npos != (findPos = source.find(from, lastPos))) {
        newString.append(source, lastPos, findPos - lastPos);
        newString += to;
        lastPos = findPos + from.length();
    }

    // Care for the rest after last occurrence
    newString += source.substr(lastPos);

    source.swap(newString);
}

//Binary tree generator for leetcode.
TreeNode *BTGenerator(string str) {
    replaceAll(str, ",", " ");
    replaceAll(str, "null", "-2147483648");
    stringstream stream;
    stream << str;
    deque<TreeNode *> que, parents;
    deque<int> node_vals;
    auto count = 0, product = 2;
    auto node_val = 0;
    while (stream >> node_val) {
        node_vals.push_back(node_val);
    }
    auto root = new TreeNode(node_vals[0]);
    parents.push_back(root);
    node_vals.pop_front();
    while (!node_vals.empty()) {
        for (; count < product; ++count) {
            if (node_vals[0] != 1 << 31) {
                auto temp = new TreeNode(node_vals[0]);
                if (count % 2) {
                    parents[count / 2]->right = temp;
                } else {
                    parents[count / 2]->left = temp;
                }
                que.push_back(temp);
            }
            node_vals.pop_front();
        }
        parents.clear();
        swap(parents, que);
        product = parents.size() * 2;
        count = 0;
    }
    return root;
}