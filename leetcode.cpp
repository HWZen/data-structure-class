#include <stdexcept>
#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <array>
#include <climits>
#include <cmath>
#include <string_view>
#include <type_traits>

#ifdef _MSC_VER
#include <corecrt_math_defines.h>
#include <intrin0.inl.h>
#include <vcruntime.h>

#endif
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <stdint.h>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <concepts>
#include <regex>
#include <span>
#include <cassert>
#include <any>

#ifdef _MSC_VER
#include <intrin.h>
#define __builtin_popcount __popcnt
#define __builtin_clz __lzcnt
#endif

using namespace std;
namespace daily{
class Solution
{
public:
    Solution() = default;

    class Node
    {
    public:
        int val;
        vector<Node *> children;

        Node *next;

        Node() = default;

        Node(int _val)
        {
            val = _val;
        }

        Node(int _val, vector<Node *> _children)
        {
            val = _val;
            children = std::move(_children);
        }
    };

    struct TreeNode
    {
        int val{};
        TreeNode *left{};
        TreeNode *right{};
        TreeNode() = default;
        TreeNode(int x) : val(x) {}
        TreeNode(int x, TreeNode *_left, TreeNode *_right) : val(x), left(_left), right(_right) {}
    };
    class treeNodeInit
    {
    public:
        void trimLeftTrailingSpaces(string &input)
        {
            input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch)
                                               { return !isspace(ch); }));
        }

        void trimRightTrailingSpaces(string &input)
        {
            input.erase(find_if(input.rbegin(), input.rend(), [](int ch)
                                { return !isspace(ch); })
                            .base(),
                        input.end());
        }
        auto stringToTreeNode(string input) -> TreeNode *
        {
            trimLeftTrailingSpaces(input);
            trimRightTrailingSpaces(input);
            input = input.substr(1, input.length() - 2);
            if (!input.size())
            {
                return nullptr;
            }

            string item;
            stringstream ss;
            ss.str(input);

            getline(ss, item, ',');
            auto *root = new TreeNode(stoi(item));
            queue<TreeNode *> nodeQueue;
            nodeQueue.push(root);

            while (true)
            {
                TreeNode *node = nodeQueue.front();
                nodeQueue.pop();

                if (!getline(ss, item, ','))
                {
                    break;
                }

                trimLeftTrailingSpaces(item);
                if (item != "null")
                {
                    int leftNumber = stoi(item);
                    node->left = new TreeNode(leftNumber);
                    nodeQueue.push(node->left);
                }

                if (!getline(ss, item, ','))
                {
                    break;
                }

                trimLeftTrailingSpaces(item);
                if (item != "null")
                {
                    int rightNumber = stoi(item);
                    node->right = new TreeNode(rightNumber);
                    nodeQueue.push(node->right);
                }
            }
            return root;
        }
    };

    string convert(string s, int numRows)
    {
        if (numRows == 1)
            return s;
        string *rows;
        rows = new string[numRows];
        int ptr = 0;
        int sign = 1;
        for (char ch : s)
        {
            rows[ptr].insert(rows[ptr].end(), ch);
            ptr += sign;
            if (ptr == numRows || ptr == -1)
            {
                sign *= -1;
                ptr += 2 * sign;
            }
        }

        string res;
        for (int i = 0; i < numRows; i++)
            res += rows[i];

        delete[] rows;
        return res;
    }

    int reverse(int x)
    {
        int res = 0;
        for (int count = 0; count < 10; count++)
        {
            res *= 10;
            res += x % 10;
            x /= 10;
            if (count == 8)
            {
                if ((res > 214748364 || res < -214748364) && x != 0 || (res == 214748364 && x > 7) || (res == -214748364 && x < -8))
                    return 0;
            }

            if (x == 0)
                return res;
        }
        return 0;
    }

    int myAtoi(const string &s)
    {
        bool start = false;
        long long res = 0;
        bool sign = true;
        for (char ch : s)
        {
            if (start == false)
            {
                if ((ch > '9' || ch < '0') && ch != '+' && ch != '-')
                {
                    if (ch != ' ')
                        return 0;
                    continue;
                }
                else
                {
                    start = true;
                    if (ch == '-')
                        sign = false;
                    else if (ch >= '0' && ch <= '9')
                        res += static_cast<long long>(sign * (ch - '0'));
                }
            }
            else
            {
                if (ch > '9' || ch < '0')
                {
                    if (res > 2147483647)
                        return 2147483647;
                    else if (res < -2147483648)
                        return -2147483648;
                    else
                        return static_cast<int>(res);
                }
                else
                {
                    res *= 10;
                    res += static_cast<long long>((sign ? 1 : -1) * (ch - '0'));
                }
                if (res > 2147483647)
                    return 2147483647;
                else if (res < -2147483648)
                    return -2147483648;
            }
        }
        if (res > 2147483647)
            return 2147483647;
        else if (res < -2147483648)
            return -2147483648;
        else
            return static_cast<int>(res);
    }

    bool isPalindrome(int x)
    {
        if (x < 0)
            return false;

        string str = to_string(x);
        for (int i = 0; i < (str.size() / 2); i++)
        {
            if (str[i] != str[str.size() - i - 1])
                return false;
        }
        return true;
    }

    // TODO:
    bool isMatch(string s, string p)
    {
        string::iterator s_it = s.begin();
        string::iterator p_it = p.begin();
        for (; p_it != p.end(); p_it++)
        {
        }
        return false;
    }

    int maxArea(vector<int> &height)
    {
        int hand_ptr = 0;
        auto last_ptr = height.size() - 1;
        int max = 0;
        while (hand_ptr != last_ptr)
        {
            if (((height[hand_ptr] < height[last_ptr]) ? height[hand_ptr] : height[last_ptr]) * (last_ptr - hand_ptr) > max)
                max = ((height[hand_ptr] < height[last_ptr]) ? height[hand_ptr] : height[last_ptr]) * (last_ptr - hand_ptr);
            if (height[hand_ptr] > height[last_ptr])
                last_ptr--;
            else
                hand_ptr++;
        }
        return max;
    }

    string intToRoman(int num)
    {
        string res;
        int M_num = num / 1000;
        num -= 1000 * M_num;
        for (int i = 0; i < M_num; i++)
            res += 'M';

        int C_num = num / 100;
        num -= 100 * C_num;
        if (C_num == 4)
            res += "CD";
        else if (C_num == 9)
            res += "CM";
        else
        {
            if (C_num >= 5)
            {
                res += 'D';
                C_num -= 5;
            }
            while (C_num--)
                res += 'C';
        }

        int X_num = num / 10;
        num -= 10 * X_num;
        if (X_num == 4)
            res += "XL";
        else if (X_num == 9)
            res += "XC";
        else
        {
            if (X_num >= 5)
            {
                res += 'L';
                X_num -= 5;
            }
            while (X_num--)
                res += 'X';
        }

        int I_num = num / 1;
        num -= 1 * I_num;
        if (I_num == 4)
            res += "IV";
        else if (I_num == 9)
            res += "IX";
        else
        {
            if (I_num >= 5)
            {
                res += 'V';
                I_num -= 5;
            }
            while (I_num--)
                res += 'I';
        }

        return res;
    };

    string longestCommonPrefix(vector<string> &strs)
    {
        string res;
        if (strs.size() == 0)
            return res;

        int num = 0;
        while (true)
        {
            if (strs[0].length() <= num)
                return res;
            char temp = strs[0][num];
            for (int i = 1; i < strs.size(); i++)
            {
                if (strs[i].length() <= num)
                    return res;
                if (strs[i][num] != temp)
                    return res;
            }
            num++;
            res += temp;
        }
        return res;
    }

    vector<vector<int>> threeSum(vector<int> &nums)
    {
        if (nums.size() < 3)
            return {};

        sort(nums.begin(), nums.end());

        std::array<char, 200000> index = {};
        vector<vector<int>> res;
        for (int i : nums)
            index[i + 100000] += 1;

        for (int i = 0; i < nums.size() && nums.at(i) <= 0; i++)
        {
            index[nums.at(i) + 100000] -= 1;

            if (i > 0 && nums.at(i) == nums.at(i - 1))
                continue;

            for (int k = nums.size() - 1; k > i && nums.at(k) >= 0 && -nums.at(i) - nums.at(k) <= nums.at(k); k--)
            {
                index[nums.at(k) + 100000] -= 1;

                if (k < nums.size() - 1 && nums.at(k) == nums.at(k + 1))
                    continue;

                if (index[-nums.at(i) - nums.at(k) + 100000] != 0)
                    res.push_back({nums.at(i), -nums.at(i) - nums.at(k), nums.at(k)});
            }
        }

        return res;
    }

    int threeSumClosest(vector<int> &nums, int target)
    {
        sort(nums.begin(), nums.end());

        int min_sum = nums.at(0) + nums.at(1) + nums.at(2);
        for (int i = 0; i < nums.size() - 2; i++)
        {
            int l = i + 1, r = nums.size() - 1;
            while (l != r)
            {
                if (abs(min_sum - target) > abs(target - nums.at(i) - nums.at(l) - nums.at(r)))
                    min_sum = nums.at(i) + nums.at(l) + nums.at(r);

                if (abs(min_sum - target) == 0)
                    return min_sum;

                if (nums.at(i) + nums.at(l) + nums.at(r) > target)
                    r--;
                else
                    l++;
            }
        }
        return min_sum;
    }

    vector<string> letterCombinations(string &digits)
    {
        const array<string, 10> n2s = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

        function<void(string, vector<string> &, string)> backtracking = [&](string source, vector<string> &date, string temp)
        {
            if (source.length() == 0)
            {
                if (!temp.empty())
                    date.push_back(temp);
                return;
            }
            for (char ch : n2s[source[0] - '0'])
                backtracking(string(++source.begin(), source.end()), date, temp + ch);
        };
        vector<string> res;
        backtracking(std::move(digits), res, {});
        return res;
    }
    struct ListNode
    {
        int val{};
        ListNode *next = nullptr;
        ListNode() = default;
        ListNode(int x) : val(x) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };
    ListNode *deleteDuplicates(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *p = head;
        ListNode *s = head;
        ListNode *e = head;

        while (head != nullptr && head->next != nullptr && head->val == head->next->val)
        {
            e = s->next;
            while (e != nullptr && e->val == s->val)
            {
                e = e->next;
            }
            head = s = p = e;
        }
        while (p != nullptr && p->next != nullptr)
        {
            s = p->next;
            if (s->next != nullptr && s->val == s->next->val)
            {
                e = s->next;
                while (e != nullptr && e->val == s->val)
                {
                    e = e->next;
                }
                p->next = e;
            }
            else
                p = p->next;
        }
        return head;
    };
    ListNode *rotateRight(ListNode *head, int k)
    {
        if (head == nullptr || head->next == nullptr)
            return head;
        ListNode *p = head;
        int tol = 1;
        while (p->next != nullptr)
        {
            p = p->next;
            tol++;
        }
        p->next = head;
        int targ = tol - (k % tol);
        while (targ--)
            p = p->next;
        ListNode *res = p->next;
        p->next = nullptr;
        return res;
    };

    class BSTIterator
    {
    public:
        queue<int> date;
        void bsp(TreeNode *node)
        {
            if (node->left != nullptr)
                bsp(node->left);
            date.push(node->val);
            if (node->right != nullptr)
                bsp(node->right);
        }
        BSTIterator(TreeNode *root)
        {
            bsp(root);
        }

        int next()
        {
            int res = date.front();
            date.pop();
            return res;
        }

        bool hasNext()
        {
            return !date.empty();
        }
    };

    uint32_t reverseBits(uint32_t n)
    {
        uint32_t res = 0;
        for (int i = 0; i < 32; i++)
        {
            res = res << 1;
            res += n % 2;
            n = n >> 1;
        }
        return res;
    };

    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        if (matrix.at(0).at(0) >= target)
            return binary_search(matrix[0].begin(), matrix[0].end(), target);
        auto col = lower_bound(matrix.begin(), matrix.end(), target, [](const vector<int> &v, const int &tar)
                               { return v.at(0) < tar; });
        col--;
        return binary_search((*col).begin(), (*col).end(), target);
    };

    class NestedInteger
    {
    public:
        NestedInteger() = default;
        NestedInteger(int val);
        // Return true if this NestedInteger holds a single integer, rather than a nested list.
        bool isInteger() const;

        // Return the single integer that this NestedInteger holds, if it holds a single integer
        // The result is undefined if this NestedInteger holds a nested list
        int getInteger() const;
        // Return the nested list that this NestedInteger holds, if it holds a nested list
        // The result is undefined if this NestedInteger holds a single integer
        [[nodiscard]] const vector<NestedInteger> &getList() const;

        void setInteger(int value);

        void add(const NestedInteger &ni);
    };

    class NestedIterator
    {
    public:
        vector<int> res;
        void tra(const vector<NestedInteger> &nestedList)
        {
            for (NestedInteger Ne : nestedList)
            {
                if (Ne.isInteger())
                    res.push_back(Ne.getInteger());
                else
                    tra(Ne.getList());
            }
        }
        NestedIterator(vector<NestedInteger> &nestedList)
        {
            tra(nestedList);
        }

        int next()
        {
            int tmp = res.at(0);
            res.erase(res.begin());
            return tmp;
        }

        bool hasNext()
        {
            return !res.empty();
        }
    };

    vector<vector<int>> subsetsWithDup(vector<int> &nums)
    {
        auto set2vector = [](const set<vector<int>> &s)
        {
            vector<vector<int>> res;
            res.reserve(s.size());
            for (const vector<int> &tmp : s)
                res.push_back(tmp);
            return res;
        };

        function<void(set<vector<int>> &, vector<int>, vector<int>::iterator)> dfs = [&](set<vector<int>> &res, vector<int> tmp, vector<int>::iterator it)
        {
            if (it == nums.end())
                res.insert(tmp);
            else
            {
                dfs(res, tmp, it + 1);
                tmp.push_back(*it);
                dfs(res, tmp, it + 1);
            };
        };

        sort(nums.begin(), nums.end());
        set<vector<int>> res;
        dfs(res, vector<int>(), nums.begin());
        return set2vector(res);
    };

    int clumsy(int N)
    {
        const array<int, 4> top_three = {0, 1, 2, 7};
        if (N <= 3)
            return top_three[N];

        enum Operator
        {
            A,
            S
        } oper = A;
        int res = (N - 1) * (N - 2) / (N - 3);
        N -= 3;
        while (N >= 1)
        {
            switch (oper)
            {
            case A:
                res += N--;
                oper = S;
                break;
            case S:
            {
                int tmp = N--;
                if (N >= 1)
                    tmp *= N--;
                if (N >= 1)
                    tmp /= N--;
                res -= tmp;
                oper = A;
            }
            break;
            default:
                break;
            }
        }
        return res;
    };

    int trap(vector<int> &height)
    {
        vector<int> *H;
        if (height.size() < 3)
            return 0;

        vector<int> index;
        index.resize(height.size());
        for (int i = 0; i < height.size(); i++)
            index[i] = i;

        sort(index.begin(), index.end(), [&](int l, int r)
             { return height.at(l) >= height.at(r); });

        int res = 0;
        int j = index[0];
        int k = j;
        for (int i = 1; i < index.size() || (j > 0 && k < index.size() - 1); i++)
        {
            if (index[i] > j && index[i] < k)
                continue;

            if (index[i] < j)
            {
                res += height[index[i]] * (j - index[i] - 1);
                for (int t = index[i] + 1; t < j; t++)
                    res -= height[t];
                j = index[i];
            }
            else
            {
                res += height[index[i]] * (index[i] - k - 1);
                for (int t = k + 1; t < index[i]; t++)
                    res -= height[t];
                k = index[i];
            }
        }
        return res;
    };

    int longestCommonSubsequence(string text1, string text2)
    {
        vector<vector<int>> DP;
        function<void(int, int)> upDP = [&](int i, int j)
        {
            if (text1[i] == text2[j])
                DP[i][j] = max(DP[i - 1][j - 1] + 1, max(DP[i - 1][j], DP[i][j - 1]));
            else
                DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);
        };

        if (text1.size() <= 1 && text2.size() <= 1)
            return text1[0] == text2[0];
        text1 = " " + text1;
        text2 = " " + text2;
        DP.resize(text1.size());
        for (auto &i : DP)
            i.resize(text2.size());

        for (int i = 0; i < text1.size(); i++)
            DP[i][0] = 1;
        for (int i = 0; i < text2.size(); i++)
            DP[0][i] = 1;

        for (int i = 1; i < text1.size(); i++)
            for (int j = 1; j < text2.size(); j++)
                upDP(i, j);

        return DP[text1.size() - 1][text2.size() - 1] - 1;
    };

    int removeDuplicates(vector<int> &nums)
    {
        if (nums.size() <= 2)
            return 2;
        int res = 2;
        for (int i = 2; i < nums.size(); i++)
        {
            if (nums[i] != nums[res - 2])
                nums[res++] = nums[i];
        }
        return res;
    }

    int findMin(vector<int> &nums)
    {
        vector<int> NUMS;
        function<int(int, int)> dich = [&](int l, int r)
        {
            if (NUMS[(l + r) / 2] > NUMS[(l + r) / 2 + 1])
                return NUMS[(l + r) / 2 + 1];
            if (NUMS[(l + r) / 2] > NUMS[r])
                return dich((l + r) / 2, r);
            else
                return dich(l, (l + r) / 2);
        };

        if (nums.size() <= 1)
            return *nums.begin();
        if (*(nums.end() - 1) > *nums.begin())
            return *nums.begin();
        NUMS = nums;
        return dich(0, nums.size() - 1);
    }

    bool isUgly(int n)
    {
        if (n <= 0)
            return false;
        while (n % 5 == 0)
            n /= 5;
        while (n % 3 == 0)
            n /= 3;
        while (n % 2 == 0)
            n /= 2;
        return n == 1;
    }

    int nthUglyNumber(int n)
    {
        vector<int> ugly({1});
        int p2, p3, p5 = 0;
        p2 = p3 = p5;
        for (int i = 1; i < n; i++)
        {
            int np2 = ugly[p2] * 2, np3 = ugly[p3] * 3, np5 = ugly[p5] * 5;
            ugly.push_back(min({np2, np3, np5}));
            if (ugly[i] == np2)
                p2++;
            if (ugly[i] == np3)
                p3++;
            if (ugly[i] == np5)
                p5++;
        }
        return ugly[n - 1];
    }

    uint64_t static combine2int(int x1, int x2)
    {
        return x1 * pow(10, uint64_t(log10(x2)) + 1) + x2;
    }
    bool static largestNumberCMP(int l, int r)
    {
        return combine2int(l, r) > combine2int(r, l);
    }
    string largestNumber(vector<int> &nums)
    {
        int tmp;
        for (tmp = 0; tmp < nums.size(); tmp++)
            if (nums[tmp] != 0)
                break;
        if (tmp == nums.size())
            return "0";

        sort(nums.begin(), nums.end(), Solution::largestNumberCMP);
        string res;
        for (int i : nums)
            res += to_string(i);
        return res;
    }

    void left_mid_right_tra_for_minDiffInBST(TreeNode *node, int &minimum, int &compara)
    {
        if (node->left != nullptr)
            left_mid_right_tra_for_minDiffInBST(node->left, minimum, compara);
        if (minimum > abs(node->val - compara))
            minimum = abs(node->val - compara);
        compara = node->val;
        if (node->right != nullptr)
            left_mid_right_tra_for_minDiffInBST(node->right, minimum, compara);
    }
    int minDiffInBST(TreeNode *root)
    {
        int res = 0xfffff;
        int comp = 0xffff;
        left_mid_right_tra_for_minDiffInBST(root, res, comp);
        return res;
    }

    class Trie
    {
    private:
        bool is_a_word;
        array<Trie *, 26> index;

    public:
        /** Initialize your data structure here. */
        Trie()
        {
            index.fill(nullptr);
            is_a_word = false;
        }

        /** Inserts a word into the trie. */
        void insert(const string &word)
        {
            Trie *p = this;
            for (char ch : word)
            {
                if (p->index[ch - 'a'] == nullptr)
                    p->index[ch - 'a'] = new Trie();
                p = p->index[ch - 'a'];
            }
            p->is_a_word = true;
        }

        /** Returns if the word is in the trie. */
        bool search(const string &word)
        {
            Trie *p = this;
            for (char ch : word)
            {
                if (p->index[ch - 'a'] == nullptr)
                    return false;
                p = p->index[ch - 'a'];
            }
            return p->is_a_word;
        }

        /** Returns if there is any word in the trie that starts with the given prefix. */
        bool startsWith(const string &prefix)
        {
            Trie *p = this;
            for (char ch : prefix)
            {
                if (p->index[ch - 'a'] == nullptr)
                    return false;
                p = p->index[ch - 'a'];
            }
            return true;
        }
    };

    int rob(vector<int> &nums)
    {
        if (nums.size() == 1)
            return nums[0];
        int start = 0;
        int res = 0;
        vector<int> DP;
        DP.push_back(nums[start]);
        DP.push_back(max(nums[start], nums[start + 1]));
        for (int i = 2; i < nums.size() - 1; i++)
            DP.push_back(max(nums[i] + DP[i - 2], DP[i - 1]));
        if (nums.size() == 2)
            return DP[1];
        int res1 = DP[nums.size() - 2];
        DP.resize(0);
        start = 1;
        DP.push_back(nums[start]);
        DP.push_back(max(nums[start], nums[start + 1]));
        for (int i = 3; i < nums.size(); i++)
            DP.push_back(max(nums[i] + DP[i - 3], DP[i - 2]));
        return max(res1, DP[nums.size() - 2]);
    }

    // TODO
    bool isScramble(const string &s1, const string &s2)
    {
        return false;
    }

    int removeElement(vector<int> &nums, int val)
    {
        if (nums.size() < 1)
            return 0;
        int p = 0;
        for (int i = 0; i < nums.size(); i++)
            if (nums[i] != val)
                nums[p++] = nums[i];
        return p;
    }

    int strStr(string haystack, string needle)
    {
        if (needle.size() == 0)
            return 0;
        if (needle.size() > haystack.size())
            return -1;

        for (int p = 0; p < haystack.size() - needle.size() + 1; p++)
        {
            if (haystack[p] == needle[0])
            {
                int i = p + 1;
                for (; i < p + needle.size(); i++)
                    if (haystack[i] != needle[i - p])
                        break;
                if (i == p + needle.size())
                    return p;
            }
        }
        return -1;
    }

    int combinationSum4(vector<int> &nums, int target)
    {
        vector<uint64_t> dp(target + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= target; i++)
            for (int j : nums)
                if (j <= i)
                    dp[i] += dp[i - j];
        return dp[target];
    }

    int singleNumber(vector<int> &nums)
    {
        array<int, 2> dual_bit = {0, 0};
        for (int i : nums)
        {
            dual_bit[1] = ~dual_bit[0] & (dual_bit[1] ^ i);
            dual_bit[0] = ~dual_bit[1] & (dual_bit[0] ^ i);
        }
        return dual_bit[1];
    }

    int leastBricks(vector<vector<int>> &wall)
    {

        int width = 0;
        for (int i : wall[0])
            width += i;

        if (width == 1)
            return wall.size();

        unordered_map<int, int> index;
        for (auto &col : wall)
        {
            int length = 0;
            for (auto i : col)
            {
                length += i;
                if (length < width)
                    index[length]++;
            }
        }

        int minest = 0;
        for (auto i : index)
            if (minest < i.second)
                minest = i.second;

        return wall.size() - minest;
    }

    int strangePrinter(string s)
    {
        int Size = s.size();
        if (Size == 0)
            return 0;

        array<array<int, 102>, 102> dp = {};
        for (int i = 0; i < Size; ++i)
            dp[i][i] = 1;
        for (int j = 1; j < Size; ++j)
        {
            for (int i = j - 1; i >= 0; --i)
            {
                int Min = 1 + dp[i][j - 1];
                for (int k = i + 1; k < j; ++k)
                    if (s[k] == s[j])
                        Min = min(Min, dp[i][k - 1] + dp[k][j - 1]);
                if (s[i] == s[j])
                    Min = min(Min, dp[i][j - 1]);
                dp[i][j] = Min;
            }
        }
        return dp[0][Size - 1];
    }

    ListNode *removeElements(ListNode *head, int val)
    {
        ListNode *Head = head;
        ListNode *p = head;
        while (p != nullptr)
        {
            if (p == Head && p->val == val)
            {
                p = Head = p->next;
                continue;
            }
            if (p->next != nullptr && p->next->val == val)
                p->next = p->next->next;
            else
                p = p->next;
        }
        return Head;
    }

    int findTargetSumWays(vector<int> &nums, int target)
    {
        // if(nums.size()<14)
        // {

        // }

        int **dp;
        int SUM = 0;
        for (auto i : nums)
            SUM += abs(i);
        if (target > SUM || (SUM - target) % 2 != 0)
            return 0;
        int lim = (SUM - target) / 2;
        dp = new int *[nums.size() + 1];
        for (int i = 0; i <= nums.size(); ++i)
        {
            dp[i] = new int[2 * SUM + 1];
            memset(dp[i], 0, (2 * SUM + 1) * sizeof(int));
        }

        dp[0][0] = 1;

        for (int i = 1; i < nums.size(); ++i)
        {
            int x = nums[i - 1];
            for (int j = 0; j <= lim; ++j)
            {
                dp[i][j] += dp[i - 1][j];
                if (j >= x)
                    dp[i][j] += dp[i - 1][j - x];
            }
        }
        return dp[nums.size()][lim];
    }

    int getMaximumGenerated(int n)
    {
        if (n <= 1)
            return n;
        array<uint16_t, 101> nums = {};
        nums[0] = 0;
        nums[1] = 1;
        unsigned short max = 1;
        for (int i = 2; i <= n; ++i)
        {
            auto half = i >> 1;
            if (i & 1)
                nums[i] = nums[half] + nums[half + 1];
            else
                nums[i] = nums[half];
            if (max < nums[i])
                max = nums[i];
        }
        return max;
    }

    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k)
    {
        const int MAX = 0xffffff;
        queue<vector<int>> que;
        vector<vector<vector<int>>> edge(n);
        vector<int> price(n);
        for (int i = 0; i < n; ++i)
            price[i] = MAX;
        for (auto flight : flights)
            edge[flight[0]].push_back(vector<int>({flight[1], flight[2]}));
        price[src] = 0;
        que.push(vector<int>({src, 0, price[src]}));
        while (!que.empty())
        {
            auto node = que.front();
            que.pop();
            if (node[1] > k)
                continue;
            for (auto next : edge[node[0]])
            {
                if (price[next[0]] > node[2] + next[1])
                {
                    price[next[0]] = node[2] + next[1];
                    que.push(vector<int>({next[0], node[1] + 1, node[2] + next[1]}));
                }
            }
        }
        return price[dst] == MAX ? -1 : price[dst];
    }

    class MedianFinder
    {
    public:
        /** initialize your data structure here. */
        multiset<int> buf;
        MedianFinder() = default;

        void addNum(int num)
        {
            buf.insert(num);
        }

        double findMedian()
        {
            auto mid = buf.size();
            auto it = buf.begin();
            auto all = buf.get_allocator();
            if (mid & 1)
            {
                // for (int i = 1; i < buf.size() / 2 + 1;++i)
                //     ++it;
                return *next(it, buf.size() / 2);
            }
            else
            {
                // for (int i = 1; i < buf.size() / 2;++i)
                //     ++it;
                it = next(it, buf.size() / 2 - 1);
                return double(*it + *(++it)) / 2;
            }
        }
    };

    int numRescueBoats(vector<int> &people, int limit)
    {
        sort(people.begin(), people.end());
        int f = 0, b = people.size() - 1;
        int nums = 0;
        while (f < b)
        {
            ++nums;
            if (people[f] + people[b] <= limit)
                ++f;
            --b;
        }
        if (f == b)
            ++nums;
        return nums;
    }

    vector<int> runningSum(vector<int> &nums)
    {
        for (int i = 1; i < nums.size(); ++i)
            nums[i] += nums[i - 1];
        return nums;
    }

    vector<int> _w;
    Solution(vector<int> &w) : _w(w)
    {
        partial_sum(_w.begin(), _w.end(), _w.begin());
    }

    int pickIndex()
    {
        // srand((unsigned)time( NULL ));
        int r = rand() % _w.back();
        return lower_bound(_w.begin(), _w.end(), r + 1) - _w.begin();
    }

    int sumOddLengthSubarrays(vector<int> &arr)
    {
        int sum = 0;
        for (int i = 0; i < arr.size(); ++i)
        {
            int a = 0;
            for (int x = 1; x <= arr.size(); x += 2)
            {
                // a += x;
                // if (x > i + 1)
                //     a -= x - i - 1;
                // if (x > arr.size() - i)
                //     a -= x - arr.size() + i;

                a += x - ((x > i + 1) ? x - i - 1 : 0) - ((x > arr.size() - i) ? x - arr.size() + i : 0);
            }
            sum += arr[i] * a;
        }
        return sum;
    }

    vector<int> corpFlightBookings(vector<vector<int>> &bookings, int n)
    {
        vector<int> delta(n, 0);
        for (auto &item : bookings)
        {
            delta[item[0] - 1] += item[2];
            if (item[1] < n)
                delta[item[1]] -= item[2];
        }
        partial_sum(delta.begin(), delta.end(), delta.begin());
        return delta;
    }

    int compareVersion(char *version1, char *version2)
    {
        int len1 = strlen(version1);
        int len2 = strlen(version2);
        char *l1 = version1, *l2 = version2;
        char *r1 = l1, *r2 = l2;
        while (l1 < version1 + len1 || l2 < version2 + len2)
        {
            uint32_t v1 = 0, v2 = 0;
            if (l1 < version1 + len1)
            {
                while (*r1 != '.' && *r1 != '\0')
                {
                    ++r1;
                }
                r1[0] = '\0';
                v1 = atoi(l1);
                l1 = ++r1;
            }
            if (l2 < version2 + len2)
            {
                while (*r2 != '.' && *r2 != '\0')
                {
                    ++r2;
                }
                r2[0] = '\0';
                v2 = atoi(l2);
                l2 = ++r2;
            }
            if (v1 != v2)
                return (v1 > v2) ? 1 : -1;
        }
        return 0;
    }

    ListNode *getKthFromEnd(ListNode *head, int k)
    {
        auto res = head;
        for (int i = 1; i < k; ++i)
            head = head->next;
        while ((head = head->next) != nullptr)
            res = res->next;
        return res;
    }

    static void Qsort(int *arrey, int hand, int last)
    {
        if (hand >= last)
            return;

        int T = arrey[hand];
        int F = hand;
        int L = last;

        while (F < L)
        {
            while (F < L && arrey[L] >= T)
                --L;
            arrey[F] = arrey[L];
            while (F < L && arrey[F] < T)
                ++F;
            arrey[L] = arrey[F];
        }
        arrey[F] = T;

        if ((last - hand) > 3000000)
        {
            thread thL(Qsort, arrey, hand, F - 1);
            thread thR(Qsort, arrey, L + 1, last);
            thL.join();
            thR.join();
        }
        else
        {
            Qsort(arrey, hand, F - 1);
            Qsort(arrey, L + 1, last);
        }
    }
    int *smallestK(int *arr, int arrSize, int k, int *returnSize)
    {
        Qsort(arr, 0, arrSize - 1);
        return arr;
    }

    vector<int> smallestK(vector<int> &arr, int k)
    {
        sort(arr.begin(), arr.end());
        return {arr.begin(), arr.begin() + k};
    }

    int fib(int n)
    {
        if (n <= 1)
            return n;
        array<int64_t, 101> dp = {};
        dp[1] = 1;
        for (int i = 2; i <= n; ++i)
            dp[i] = (dp[i - 1] + dp[i - 2]) % int(1e9 + 7);
        return dp[n] % int(1e9 + 7);
    }

    int rand7()
    {
        return (rand() % 7) + 1;
    }
    int rand10()
    {
        int num;
        while ((num = ((rand7() - 1) * 7 + rand7())) > 40)
        {
        }
        return (num % 10) + 1;
    }

    int search(vector<int> &nums, int target)
    {
        int p = lower_bound(nums.begin(), nums.end(), target) - nums.begin();
        return nums[p] == target ? p : -1;
    }
    int balancedStringSplit(const string &s)
    {
        int Stack = 0;
        int sum = 0;
        for (char i : s)
        {
            Stack += (i == 'L') ? 1 : -1;
            if (Stack == 0)
                sum++;
        }
        return sum;
    }

    int findMaximizedCapital(int k, int w, vector<int> &profits, vector<int> &capital)
    {
        vector<int> index(profits.size(), 0);
        for (int i = 0; i < index.size(); ++i)
            index[i] = i;
        sort(index.begin(), index.end(), [&](int left, int right)
             { return capital[left] < capital[right]; });
        priority_queue<int> q;
        auto it = index.begin();
        do
        {
            while (it != index.end() && capital[*it] <= w)
                q.push(profits[*(it++)]);
            if (q.empty())
                return w;
            w += q.top();
            q.pop();
        } while (--k);
        return w;
    }

    vector<string> fullJustify(vector<string> &words, int maxWidth)
    {
        vector<string> res;
        auto begin = words.begin();
        int sum = 0;
        for (auto it = begin; it != words.end(); ++it)
        {
            if (sum + (*it).size() > maxWidth)
            {
                string tmp;
                int spcae_num = ((it - begin) - 1) == 0 ? 0 : (maxWidth - sum + 1) / ((it - begin) - 1);
                int remainder = ((it - begin) - 1) == 0 ? 0 : (maxWidth - sum + 1) % ((it - begin) - 1);
                while (begin < it - 1)
                {
                    tmp += *begin;
                    for (int i = 0; i < spcae_num + 1 + (remainder > 0 ? 1 : 0); ++i)
                        tmp.push_back(' ');
                    remainder--;
                    ++begin;
                }
                tmp += *begin++;
                if (tmp.size() != maxWidth)
                    tmp.resize(maxWidth, ' ');
                res.push_back(tmp);
                sum = 0;
            }
            sum += (*it).size() + 1;
        }
        string tmp;
        do
        {
            tmp += *begin + ' ';
        } while (++begin != words.end());
        tmp.resize(maxWidth, ' ');
        res.push_back(tmp);
        return res;
    }

    int chalkReplacer(vector<int> &chalk, int k)
    {
        vector<long long> _chalk(chalk.begin(), chalk.end());
        partial_sum(_chalk.begin(), _chalk.end(), _chalk.begin());
        long long remainder = k % _chalk.back();
        return upper_bound(_chalk.begin(), _chalk.end(), remainder) - _chalk.begin();
    }

    int findPeakElement(vector<int> &nums)
    {
        int left = 0;
        int right = nums.size() - 1;
        while (left < right)
        {
            int mid = (left + right) >> 1;
            if (nums[mid] > nums[mid + 1])
                right = mid;
            else
                left = mid + 1;
        }
        return left;
    }

    bool isValidSudoku(vector<vector<char>> &board)
    {
        array<set<char>, 9> col = {}, row = {}, block = {};
        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                if (board[i][j] == '.')
                    continue;

                if (col[i].find(board[i][j]) != col[i].end() ||
                    row[j].find(board[i][j]) != row[j].end() ||
                    block[(i / 3) * 3 + j / 3].find(board[i][j]) != block[(i / 3) * 3 + j / 3].end())
                    return false;

                col[i].insert(board[i][j]);
                row[j].insert(board[i][j]);
                block[(i / 3) * 3 + j / 3].insert(board[i][j]);
            }
        }
        return true;
    }

    bool canWinNim(int n)
    {
        return n % 4 != 0;
    }

    int minSteps(int n)
    {
        vector<int> dp(n + 1, 0);
        dp[1] = 0;
        for (int i = 2; i <= n; ++i)
        {
            dp[i] = 0xffff;
            for (int j = 1; j * j <= i; ++j)
            {
                if (i % j != 0)
                    continue;
                dp[i] = min({dp[i], dp[j] + i / j, dp[i / j] + j});
            }
        }
        return dp[n];
    }

    int lengthOfLIS(vector<int> &nums)
    {
        vector<int> dp(nums);
        dp[0] = 1;
        int max_len = 1;
        // int max_size = 1;
        for (int i = 1; i < nums.size(); ++i)
        {
            dp[i] = 1;
            for (int j = 0; j < i; ++j)
                dp[i] = max(dp[i], nums[i] > nums[j] ? dp[j] + 1 : 0);
            if (dp[i] > max_len)
                max_len = dp[i];
        }
        return max_len;
    }

    int findNumberOfLIS(vector<int> &nums)
    {
        vector<int> dp(nums);
        dp[0] = 1;
        int max_len = 1;
        int max_size = 1;
        vector<int> size(nums);
        size[0] = 1;
        for (int i = 1; i < nums.size(); ++i)
        {
            dp[i] = 1;
            size[i] = 1;
            for (int j = 0; j < i; ++j)
            {
                if (nums[i] > nums[j])
                {
                    if (dp[j] + 1 > dp[i])
                    {
                        dp[i] = dp[j] + 1;
                        size[i] = size[j];
                    }
                    else if (dp[j] + 1 == dp[i])
                        size[i] += size[j];
                }
            }
            if (dp[i] > max_len)
            {
                max_len = dp[i];
                max_size = size[i];
            }
            else if (dp[i] == max_len)
                max_size += size[i];
        }
        return max_size;
    }

    int lengthOfLastWord(string s)
    {
        auto rit = s.rbegin();
        while (rit != s.rend() && *rit == ' ')
            ++rit;
        int sum = 1;
        while (++rit != s.rend() && *rit != ' ')
            ++sum;
        return sum;
    }

    vector<ListNode *> splitListToParts(ListNode *head, int k)
    {
        vector<ListNode *> res(k, nullptr);
        int size = 0;
        auto it = head;
        while (it != nullptr)
        {
            it = it->next;
            ++size;
        }
        int div = size / k;
        int rem = size % k;
        it = head;
        for (auto &lp : res)
        {
            for (int i = 1; i < div + (rem > 0); ++i)
                it = it->next;
            lp = head;
            if (it == nullptr)
                break;
            head = it->next;
            it->next = nullptr;
            it = head;
            --rem;
        }
        return res;
    }

    bool isPowerOfThree(int n)
    {
        if (n == 0)
            return false;
        if (n <= 9)
        {
            while (n % 3 == 0)
                n /= 3;
            return n == 1;
        }
        else
        {
            return 1162261467 % n == 0;
        }
    }

    class flattenClass
    {
        class Node
        {
        public:
            int val;
            Node *prev;
            Node *next;
            Node *child;
        };
        Node *flatten(Node *head)
        {
            stack<Node *> pre_next;
            auto it = head;
            for (auto it = head; it; it = it->next)
            {
                if (it->child)
                {
                    if (it->next)
                        pre_next.push(it->next);
                    it->next = it->child;
                    it->next->prev = it;
                    it->child = nullptr;
                }
                if (!it->next && !pre_next.empty())
                {
                    it->next = pre_next.top();
                    it->next->prev = it;
                    pre_next.pop();
                }
            }
            return head;
        }
    };

    int minDistance(string text1, string text2)
    {
        vector<vector<int>> DP;
        function<void(int, int)> upDP = [&](int i, int j)
        {
            if (text1[i] == text2[j])
                DP[i][j] = max(DP[i - 1][j - 1] + 1, max(DP[i - 1][j], DP[i][j - 1]));
            else
                DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);
        };
        if (text1.size() <= 1 && text2.size() <= 1)
            return text1[0] == text2[0];
        text1 = " " + text1;
        text2 = " " + text2;

        DP.resize(text1.size());
        for (auto &i : DP)
            i.resize(text2.size());

        for (int i = 0; i < text1.size(); i++)
            DP[i][0] = 1;
        for (int i = 0; i < text2.size(); i++)
            DP[0][i] = 1;

        for (int i = 1; i < text1.size(); i++)
            for (int j = 1; j < text2.size(); j++)
                upDP(i, j);

        auto max = DP[text1.size() - 1][text2.size() - 1] - 1;
        return text1.size() + text2.size() - 2 * max - 2;
    }

    int pathSum(TreeNode *root, int targetSum)
    {
        int res = 0;
        unordered_map<int, int> map;
        map[0] = 1;

        function<void(TreeNode * &root, int val)> dfs = [&](TreeNode *&root, int val)
        {
            if (map.count(val - targetSum))
                res += map[val - targetSum];
            ++map[val];
            if (root->left)
                dfs(root->left, val + root->left->val);
            if (root->right)
                dfs(root->right, val + root->right->val);
            --map[val];
        };

        dfs(root, root->val);
        return res;
    }

    int getSum(int a, int b)
    {
        return b == 0 ? a : getSum(a ^ b, (a & b) << 1);
    }

    int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2)
    {
        int delta_x = ax2 - ax1 + bx2 - bx1 - (ax2 > bx2 ? ax2 : bx2) + (ax1 < bx1 ? ax1 : bx1);
        if (delta_x < 0)
            delta_x = 0;
        int delta_y = ay2 - ay1 + by2 - by1 - (ay2 > by2 ? ay2 : by2) + (ay1 < by1 ? ay1 : by1);
        if (delta_y < 0)
            delta_y = 0;

        return (ax2 - ax1) * (ay2 - ay1) + (bx2 - bx1) * (by2 - by1) - delta_x * delta_y;
    }

    string destCity(vector<vector<string>> &paths)
    {
        unordered_set<string> res, enres;
        for (auto path : paths)
        {
            enres.insert(path[0]);
            if (res.count(path[0]))
                res.erase(path[0]);
            if (!enres.count(path[1]))
                res.insert(path[1]);
        }
        return *res.begin();
    }

    string toHex(unsigned int num)
    {
        const string hex = "0123456789abcdef";
        string res;
        while (num)
        {
            res.insert(res.begin(), hex[num % 16]);
            num = num >> 4;
        }
        return res.empty() ? "0" : res;
    }

    string fractionToDecimal(long long numerator, int denominator)
    {
        if (!(numerator % denominator))
            return to_string(numerator / denominator);
        string integer;
        if (numerator * denominator < 0)
            integer = "-";
        numerator = abs(numerator);
        denominator = abs(denominator);
        integer += to_string(numerator / denominator);

        string decimal;
        map<long long, size_t> Map;
        numerator %= denominator;
        auto it = 0;
        while (numerator)
        {

            Map[numerator] = decimal.size();
            numerator *= 10;
            decimal += to_string(numerator / denominator);
            numerator %= denominator;
            if (Map.count(numerator))
            {
                decimal.insert(decimal.begin() + Map.find(numerator)->second, '(');
                return std::move(integer + "." + decimal + ")");
            }
        }
        return std::move(integer + "." + decimal);
    }

    string licenseKeyFormatting(string s, int k)
    {
        while (s.find('-') != s.npos)
            s.erase(s.find('-'), 1);
        if (s.empty())
            return s;
        for (auto &ch : s)
        {
            if (ch >= 97)
                ch -= 32;
        }
        auto rem = (s.size() % k);
        size_t it = 0;
        if (rem)
            it += rem;
        else
            it += k;
        if (it != s.size())
        {
            s.insert(s.begin() + it, '-');
            it += k + 1;
        }

        while (it < s.size())
        {
            s.insert(s.begin() + it, '-');
            ++it;
            it += k;
        }
        return s;
    }

    /*
     * Below is the interface for Iterator, which is already defined for you.
     * **DO NOT** modify the interface for Iterator.
     */
    class Iterator
    {
        typename vector<int>::const_iterator end;
        typename vector<int>::const_iterator it;

    public:
        Iterator(const vector<int> &nums) : it(nums.begin()), end(nums.end()) {}
        Iterator(const Iterator &iter) : end(iter.end), it(iter.it) {}

        // Returns the next element in the iteration.
        int next()
        {
            return *++it;
        };

        // Returns true if the iteration has more elements.
        bool hasNext() const
        {
            return it != end;
        };
    };

    class PeekingIterator : public Iterator
    {
    public:
        vector<int>::const_iterator it;
        PeekingIterator(const vector<int> &nums) : Iterator(nums)
        {
            it = nums.begin();
            void *n = (void *)&nums;
            ((vector<int> *)n)->at(1) = 2;
        }
        int peek()
        {
            return Iterator(*this).next();
        }
    };

    int thirdMax(vector<int> &nums)
    {
        set<int> buf({INT_MIN, INT_MIN + 1, INT_MIN + 2});
        for (int i : nums)
        {
            if (*buf.begin() < i)
                buf.insert(i);

            if (buf.size() > 3)
                buf.erase(buf.begin());
        }
        return (buf.size() == 3 ? *buf.begin() : *(--buf.end()));
    }

    int countSegments(string s)
    {
        s = " " + s + " ";
        int sum = 0;
        bool last_char_is_space = true;
        for (char ch : s)
        {
            if (last_char_is_space && ch != ' ')
            {
                ++sum;
                last_char_is_space = false;
            }

            if (!last_char_is_space && ch == ' ')
                last_char_is_space = true;
        }
        return sum;
    }

    vector<string> findRepeatedDnaSequences(string s)
    {
        if (s.length() <= 10)
            return {};

        int x;
        unordered_map<char, int> bin({{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}});
        for (int i = 0; i < 9; ++i)
            x = (x << 2) | bin[s[i]];

        vector<string> res;
        unordered_map<int, int> hash_map;
        for (int i = 9; i < s.length(); ++i)
        {
            x = ((x << 2) | bin[s[i]]) & ((1 << (10 * 2)) - 1);
            if (++hash_map[x] == 2)
            {
                res.push_back(s.substr(i - 9, i));
            }
        }
        return res;
    }

    class SummaryRanges
    {
    public:
        map<int, int> start, end;
        SummaryRanges() = default;

        void addNum(int val)
        {
            auto it = end.lower_bound(val);
            if (it != end.end() && it->second <= val)
                return;

            if (start.count(val + 1))
            {
                start[val] = start[val + 1];
                end[start[val]] = val;
                start.erase(val + 1);
            }
            else
                end[val] = val;

            if (end.count(val - 1))
            {
                auto it = start.count(val) ? start[val] : val;
                end[it] = end[val - 1];
                start[end[val - 1]] = it;
                end.erase(val - 1);

                if (start.count(val))
                    start.erase(val);
            }
            else if (!start.count(val))
                start[val] = val;
        }

        vector<vector<int>> getIntervals()
        {
            vector<vector<int>> res;
            for (auto it : start)
                res.push_back({it.first, it.second});
            return res;
        }
    };

    int arrangeCoins(int n)
    {
        return (sqrt(8 * (long long)n + 1) - 1) / 2;
    }

    class NumberToWords
    {
    public:
        unordered_map<int, string> i_to_s = {
            {1, "One"}, {2, "Two"}, {3, "Three"}, {4, "Four"}, {5, "Five"}, {6, "Six"}, {7, "Seven"}, {8, "Eight"}, {9, "Nine"}, {10, "Ten"}, {11, "Eleven"}, {12, "Twelve"}, {13, "Thirteen"}, {14, "Fourteen"}, {15, "Fifteen"}, {16, "Sixteen"}, {17, "Seventeen"}, {18, "Eighteen"}, {19, "Nineteen"}, {20, "Twenty"}, {30, "Thirty"}, {40, "Forty"}, {50, "Fifty"}, {60, "Sixty"}, {70, "Seventy"}, {80, "Eighty"}, {90, "Ninety"}};

        const vector<string> i3_to_s = {"Thousand", "Million", "Billion"};

        string numberToWords(int num, int is_root = -1)
        {
            if (!num && is_root == -1)
                return "Zero";

            int tmp = num % 1000;
            string res;

            if (tmp > 99)
            {
                res = i_to_s[tmp / 100] + " Hundred";
                tmp %= 100;
                if (tmp != 0)
                    res += " ";
            }

            if (tmp != 0)
                res += (tmp < 20 || !(tmp % 10) ? i_to_s[tmp] : (i_to_s[(tmp / 10) * 10] + " " + i_to_s[tmp % 10]));

            if (num && is_root != -1)
                res += " " + i3_to_s[is_root] + " ";

            if (num < 1000)
                return res;

            for (int cnt = 0; num /= 1000; ++cnt)
            {
                if (res == string())
                {
                    res = std::move(numberToWords(num % 1000, cnt) + res);
                    if (res != string())
                        res.erase(res.end() - 1);
                }
            }

            return res;
        }
    };

    int devide(long long devidend, long long devisor)
    {
        if (devidend == INT_MIN && devisor == -1)
            return INT_MAX;
        return devidend / devisor;
    }

    vector<string> fizzBuzz(int n)
    {
        vector<string> res;
        for (int i = 1; i <= n; ++i)
        {
            string tmp;
            if (!(i % 3))
                tmp = "Fizz";
            if (!(i % 5))
                tmp += "Buzz";
            if (tmp.empty())
                tmp = to_string(i);
            res.push_back(tmp);
        }
        return res;
    }

    int peakIndexInMountainArray(vector<int> &arr)
    {
        int l = 0, r = arr.size() - 1;
        while (l < r - 1)
        {
            if (arr[(l + r) / 2] > arr[(l + r) / 2 + 1] && arr[(l + r) / 2] > arr[(l + r) / 2 - 1])
                return (l + r) / 2;

            if (arr[(l + r) / 2] > arr[(l + r) / 2 + 1])
                r = (l + r) / 2;
            else
                l = (l + r) / 2;
        }
        return arr[l] > arr[r] ? l : r;
    }

    string countAndSay(int n)
    {
        string res = "1";
        while (n--)
        {
            int cnt = 0;
            char buf = res[0];
            string tmp;
            for (char ch : res)
            {
                if (ch == buf)
                    ++cnt;
                else
                {
                    tmp += to_string(cnt) + buf;
                    cnt = 1;
                    buf = ch;
                }
            }
            tmp += to_string(cnt) + buf;
            res = tmp;
        }
        return res;
    }

    class AddOperators
    {
    public:
        vector<string> res;
        string num;
        int target;
        void foo(string &str, int off, long sum, long mul)
        {
            if (off == num.size() && sum == target)
            {
                res.push_back(str);
                return;
            }
            int sign = str.size();
            if (off > 0)
                str.push_back(0);
            long val = 0;
            for (int i = off; i < num.size() && (i != off || num[off] != '0'); ++i)
            {
                val = 10 * val + num[i] - '0';
                str.push_back(num[i]);
                if (off == 0)
                    foo(str, i + 1, val, val);
                else
                {
                    str[sign] = '*';
                    foo(str, i + 1, sum - mul + mul * val, mul * val);

                    str[sign] = '+';
                    foo(str, i + 1, val + sum, val);

                    str[sign] = '-';
                    foo(str, i + 1, sum - val, -val);
                }
            }
            str.resize(sign);
        }
        vector<string> addOperators(string _num, int _target)
        {
            num = std::move(_num);
            target = _target;
            string exp;
            foo(exp, 0, 0, 0);
            return res;
        }
    };

    int kthSmallest(TreeNode *root, int k)
    {
        stack<TreeNode *> tree_stack;
        // function<void(TreeNode *)> foo = [foo](TreeNode *node)
        // {
        //     if(node->left)
        //         foo(node->left);

        // };
        auto it = root;
        while (k)
        {
            if (it->left && it->left->val != -1)
            {
                tree_stack.push(it);
                it = it->left;
            }
            else
            {
                if (it->val != -1)
                {
                    --k;
                    if (!k)
                        break;
                    it->val = -1;
                }
                if (it->right && it->right->val != -1)
                {
                    tree_stack.push(it);
                    it = it->right;
                }
                else
                {
                    it = tree_stack.top();
                    tree_stack.pop();
                }
            }
        }
        return it->val;
    }

    int findComplement(int num)
    {
        int off = 32 - int(log(num) / log(2)) - 1;
        return (~(num << off)) >> off;
    }

    class WordDictionary
    {
    private:
        struct nodetree;
        using pnode = nodetree *;
        struct nodetree
        {
            bool is_end = false;
            array<pnode, 26> node = {nullptr};
        };

    public:
        nodetree root;
        WordDictionary() = default;

        void addWord(const string &word)
        {
            auto it = &root;
            for (char ch : word)
            {
                // if(!it->node)
                //     it->node = new pnode;
                if (!it->node[ch - 'a'])
                    it->node[ch - 'a'] = new nodetree();
                it = it->node[ch - 'a'];
            }
            it->is_end = true;
        }

        bool search(string word, pnode _root = nullptr)
        {

            if (!_root)
                _root = &root;
            for (int i = 0; i < word.size(); ++i)
            {
                // if (!_root->node)
                //     return false;

                if (word[i] != '.')
                {
                    if (!_root->node[word[i] - 'a'])
                        return false;
                    _root = _root->node[word[i] - 'a'];
                }
                else
                {
                    for (int j = 0; j < 26; ++j)
                    {
                        if (_root->node[j] && search(word.substr(i + 1), _root->node[j]))
                            return true;
                    }
                    return false;
                }
            }
            return _root->is_end;
        }
    };

    int minMoves(vector<int> &nums)
    {
        int sum = 0, min = INT_MAX;
        for (int i : nums)
        {
            if (i < min)
                min = i;
            sum += i;
        }
        return sum - nums.size() * min;
    }

    vector<int> plusOne(vector<int> &digits)
    {
        ++digits.back();
        for (int it = digits.size() - 1; it >= 0 && digits[it] > 9; --it)
        {
            digits[it] = 0;
            if (it == 0)
                digits.insert(digits.begin(), {1});
            else
                ++digits[it - 1];
        }
        return digits;
    }

    vector<int> majorityElement(vector<int> &nums)
    {
        int threshold = nums.size() / 3;
        // map<int, int> cnt;
        // for(int i:nums)
        //     ++cnt[i];
        // vector<int> res;
        // for(auto p:cnt)
        //     if (p.second > threshold)
        //         res.push_back(p.first);
        // return res;

        array<int, 2> cnt = {0, 0};
        array<int, 2> candidate = {-1, -1};
        for (int i : nums)
        {
            if (i == candidate[0])
                ++cnt[0];
            else if (i == candidate[1])
                ++cnt[1];
            else if (cnt[0] == 0)
            {
                candidate[0] = i;
                cnt[0] = 1;
            }
            else if (cnt[1] == 0)
            {
                candidate[1] = i;
                cnt[1] = 1;
            }
            else
            {
                --cnt[0];
                --cnt[1];
            }
        }

        vector<int> res;
        if (cnt[0] > 0 && count(nums.begin(), nums.end(), candidate[0]) > threshold)
            res.push_back(candidate[0]);
        if (cnt[1] > 0 && count(nums.begin(), nums.end(), candidate[1]) > threshold)
            res.push_back(candidate[1]);
        return res;
    }

    vector<int> constructRectangle(int area)
    {

        for (int sq = sqrt(area); sq > 0; --sq)
            if (area % sq == 0)
                return {sq, area / sq};
        return {};
    }

    class ShoppingOffers
    {
    public:
        int shoppingOffers(vector<int> &price, vector<vector<int>> &special, vector<int> &needs)
        {
            return dfs(price, special, needs);
        }
        map<vector<int>, int> hash;

        int dfs(vector<int> &price, vector<vector<int>> &special, vector<int> &needs)
        {
            if (hash.count(needs))
                return hash[needs];
            int res = 0, n = (int)price.size();
            for (int i = 0; i < n; i++)
                res += (needs[i] * price[i]);
            for (int i = 0; i < special.size(); i++)
            {
                bool valid = true;
                for (int j = 0; j < n; j++)
                {
                    if (special[i][j] > needs[j])
                    {
                        valid = false;
                        break;
                    }
                }
                if (!valid)
                    continue;
                vector<int> tmp(n);
                for (int j = 0; j < n; j++)
                    tmp[j] = needs[j] - special[i][j];
                res = min(res, special[i].back() + dfs(price, special, tmp));
            }
            hash[needs] = res;
            return res;
        }
    };
    int shoppingOffers(vector<int> &price, vector<vector<int>> &special, vector<int> &needs)
    {
        vector<int> accum(price.size() + 1);
        accum[0] = 1;
        for (int i = 1; i <= price.size(); ++i)
            accum[i] = accum[i - 1] * (needs[i - 1] + 1);
        int mask = accum[price.size()];
        vector<int> f(mask);
        int *cnt = new int[price.size()];
        for (int state = 1; state < mask; ++state)
        {
            f[state] = INT_MAX;
            memset(cnt, 0, price.size() * sizeof(int));
            for (int i = 0; i < price.size(); ++i)
                cnt[i] = state % accum[i + 1] / accum[i];
            for (int i = 0; i < price.size(); ++i)
                if (cnt[i] > 0)
                    f[state] = min(f[state], f[state - accum[i]] + price[i]);

            for (auto &x : special)
            {
                int cur = state;
                int i = 0;
                for (i = 0; i < price.size(); ++i)
                {
                    if (cnt[i] < x[i])
                        break;
                    cur -= x[i] * accum[i];
                }
                if (i == price.size())
                    f[state] = min(f[state], f[cur] + x[price.size()]);
            }
        }
        return f[mask - 1];
    }
    bool searchMatrix(vector<vector<int>> &matrix, int target, int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0, bool revix = true)
    {
        // if(revix)
        // {
        //     x2 = matrix.size() - x2 - 1;
        //     y2 = matrix[0].size() - y2 - 1;
        // }
        // if (x1 > x2 || y1 > y2 || x1 < 0 || x2 >= matrix.size() || y1 < 0 || y2 >= matrix[0].size())
        //     return false;
        // if(target < matrix[x1][y1] || target > matrix[x2][y2])
        //     return false;
        // if (matrix[(x1 + x2) / 2][(y1 + y2) / 2] == target)
        //     return true;
        // else if (x1 == x2 && y1 == y2)
        //     return false;
        // if (searchMatrix(matrix, target, x1, (y1 + y2) / 2 + 1, (x1 + x2) / 2 - 1, y2, false) ||
        //     searchMatrix(matrix, target, (x1 + x2) / 2 + 1, y1, x2, (y1 + y2) / 2 - 1, false))
        //     return true;

        // if (x2 - x1 <= 1 && y2 - y1 <= 1)
        //     return matrix[x2][y1] == target || matrix[x1][y2] == target || matrix[x2][y2] == target;
        // if (matrix[(x1 + x2) / 2][(y1 + y2) / 2] > target)
        //     return searchMatrix(matrix, target, x1, y1, (x1 + x2) / 2, (y1 + y2) / 2, false);
        // else
        //     return searchMatrix(matrix, target, (x1 + x2) / 2, (y1 + y2) / 2, x2, y2, false);

        int x = 0;
        int y = matrix[0].size();
        while (matrix[x][y] != target && x < matrix.size() && y >= 0)
        {
            if (matrix[x][y] > target)
                ++x;
            else
                --y;
        }
        if (x < matrix.size() && y >= 0 && matrix[x][y] == target)
            return true;
        else
            return false;
    }

    vector<int> nextGreaterElement(vector<int> &nums1, vector<int> &nums2)
    {
        unordered_map<int, int> Map;
        stack<int> st;
        for (auto it = nums2.rbegin(); it != nums2.rend(); ++it)
        {
            if (!st.empty() && *it > st.top())
                st.pop();
            Map[*it] = st.empty() ? -1 : st.top();
            st.push(*it);
        }

        vector<int> res;
        res.reserve(nums1.size());
        for (int i : nums1)
            res.push_back(Map[i]);
        return res;
    }

    bool isPerfectSquare(int num)
    {
        int cnt = 1;
        while (num > 0)
        {
            num -= cnt;
            cnt += 2;
        }
        return num == 0;
    }

    class findTiltlass
    {
        int tileSum = 0;
        int dfs(TreeNode *node)
        {
            if (node)
            {
                auto l = dfs(node->left);
                auto r = dfs(node->right);
                tileSum += abs(l - r);
                return l + r + node->val;
            }
            else
                return 0;
        }
        int findTilt(TreeNode *root)
        {
            dfs(root);
            return tileSum;
        }
    };

    int integerReplacement(int n)
    {
        int cnt = 0;
        while (n != 1)
        {
            if (n & 1)
            {
                if (n == 3)
                    return cnt + 2;
                if ((n >> 1) & 1)
                    ++n;
                else
                    --n;
            }
            else
                n = n >> 1;
            ++cnt;
        }
        return cnt;
    }

    int findLHS(vector<int> &nums)
    {
        map<int, int> counter;
        for (auto i : nums)
            ++counter[i];
        auto tmp = vector<int>({0, -1});
        int lengest = 0;
        for (auto p : counter)
        {
            if (tmp[0] != 0 && abs(p.first - tmp[0]) <= 1 && (p.second + tmp[1]) > lengest)
                lengest = p.second + tmp[1];
            tmp[0] = p.first;
            tmp[1] = p.second;
        }
        return lengest;
    }

    class maxDepthClass
    {
        class Node
        {
        public:
            int val;
            vector<Node *> children;

            Node() = default;

            Node(int _val)
            {
                val = _val;
            }

            Node(int _val, vector<Node *> _children)
            {
                val = _val;
                children = std::move(_children);
            }
        };
        int maxDepth(Node *root, int deep = 0)
        {
            if (!root)
                return deep;
            if (root->children.empty())
                ++deep;
            int deepest = deep;
            for (auto i : root->children)
            {
                deepest = max(maxDepth(i, deep + 1), deepest);
            }

            return deepest;
        }
    };

    class shuffle
    {
        class Solution
        {
        private:
            vector<int> original;
            vector<int> nums;

        public:
            Solution(std::vector<int> &_nums) : original(std::move(_nums)) { nums = original; }
            vector<int> reset()
            {
                nums = original;
                return nums;
            }

            vector<int> shuffle()
            {
                for (int i = 0; i < nums.size(); ++i)
                {
                    int j = (rand() % (nums.size() - i)) + i;
                    swap(nums[i], nums[j]);
                }
                return nums;
            }
        };
    };

    bool buddyStrings(string s, string goal)
    {
        if (s.length() != goal.length())
            return false;
        int state = 0;
        array<char, 2> ch;
        array<bool, 26> map = {false};
        bool has_double = false;
        for (int i = 0; i < s.size(); ++i)
        {
            if (!has_double)
            {
                if (map[s[i] - 'a'])
                    has_double = true;
                else
                    map[s[i] - 'a'] = true;
            }
            if (s[i] != goal[i])
            {
                switch (++state)
                {
                case 1:
                    ch[0] = s[i];
                    ch[1] = goal[i];
                    break;
                case 2:
                    if (ch[0] != goal[i] || ch[1] != s[i])
                        return false;
                    break;
                default:
                    return false;
                }
            }
        }
        return state == 2 || (state == 0 && has_double);
    }

    string originalDigits(const string &s)
    {
        unordered_map<char, int> alphabet;
        for (char ch : s)
            ++alphabet[ch];
        vector<int> nums(10, 0);
        nums[0] = alphabet['z'];
        nums[2] = alphabet['w'];
        nums[4] = alphabet['u'];
        nums[5] = alphabet['f'] - nums[4];
        nums[1] = alphabet['o'] - nums[0] - nums[2] - nums[4];
        nums[3] = alphabet['r'] - nums[0] - nums[4];
        nums[6] = alphabet['x'];
        nums[7] = alphabet['v'] - nums[5];
        nums[8] = alphabet['g'];
        nums[9] = alphabet['i'] - nums[5] - nums[6] - nums[8];
        string res;
        for (int i = 0; i < 10; ++i)
            res += string(nums[i], i + '0');
        return res;
    }

    int poorPigs(int buckets, int minutesToDie, int minutesToTest)
    {
        int times = minutesToTest / minutesToDie;
        int tmp = log(buckets) / log(times + 1);
        return pow(times + 1, tmp) > buckets ? tmp : tmp + 1;
    }

    TreeNode *searchBST(TreeNode *root, int val)
    {
        TreeNode *it = root;
        while (it && it->val != val)
            it = it->val > val ? it->left : it->right;
        return it;
    }

    class RandomFlipMatrix
    {
        class Solution
        {
        private:
            /* Seed */
            shared_ptr<std::random_device> rd;

            /* Random number generator */
            shared_ptr<std::default_random_engine> generateor;
            /* Distribution on which to apply the generator */
            shared_ptr<std::uniform_int_distribution<int32_t>> distribution;

        public:
            int mn;
            std::set<int> Map;
            int _n;
            int _m;
            Solution(int m, int n) : _n(n), _m(m), mn(m * n), rd(new std::random_device()),
                                     generateor(new std::default_random_engine((*rd)())),
                                     distribution(new std::uniform_int_distribution<int32_t>(0, (int32_t)(1e+8)))
            {
                for (int i = 0; i < mn; ++i)
                    Map.insert(i);
            }

            vector<int> flip()
            {
                auto gen = (*distribution)(*generateor) % mn--;
                auto it = Map.begin();
                for (int i = 0; i < gen; ++i)
                {
                    ++it;
                }

                vector<int> res({*it % _m, *it / _m});
                Map.erase(it);
                return res;
            }

            void reset()
            {
                mn = _n * _m;
                for (int i = 0; i < mn; ++i)
                    Map.insert(i);
            }
        };
    };

    vector<int> findAnagrams(string s, const string &p)
    {
        if (s.length() < p.length())
            return {};
        vector<int> counter(26, 0);
        int diff = 0;
        for (char ch : p)
        {
            if (counter[ch - 'a']++ == 0)
                ++diff;
        }
        for (int i = 0; i < p.length(); ++i)
        {
            if (--counter[s[i] - 'a'] == 0)
                --diff;
            else if (counter[s[i] - 'a'] == -1)
                ++diff;
        }
        vector<int> res;
        if (!diff)
            res.push_back(0);
        for (int i = 0, j = p.length(); j < s.length(); ++i, ++j)
        {

            ++counter[s[i] - 'a'];
            if (counter[s[i] - 'a'] == 0)
                --diff;
            else if (counter[s[i] - 'a'] == 1)
                ++diff;

            --counter[s[j] - 'a'];
            if (counter[s[j] - 'a'] == 0)
                --diff;
            else if (counter[s[j] - 'a'] == -1)
                ++diff;
            if (!diff)
                res.push_back(i + 1);
        }
        return res;
    }

    int findNthDigit(int n)
    {
        uint32_t index = 1;
        uint64_t base = 9;
        while (n > base * index)
        {
            n -= base * index;
            base *= 10;
            ++index;
        }
        auto num = (n - 1) / index + (uint32_t)pow(10, index - 1);
        auto dig = (n - 1) % index;
        return num / (uint32_t)pow(10, index - dig - 1) % 10;
    }

    int maxPower(string s)
    {
        if (s.size() == 1)
            return 1;
        int count = 0;
        auto f = s.begin();
        for (auto it = f; it < s.end(); ++it)
        {
            if (*it != *f)
            {

                if (it - f > count)
                    count = it - f;
                f = it;
            }
        }
        if (*(s.end() - 1) == *f)
            if (s.end() - f > count)
                count = s.end() - f;
        return count;
    }

    vector<string> findRelativeRanks(vector<int> &score)
    {
        vector<int> index(score.size());
        for (int i = 0; i < index.size(); ++i)
            index[i] = i;
        sort(index.begin(), index.end(), [&score](int l, int r) -> bool
             { return score[l] > score[r]; });
        vector<string> res(index.size());
        for (int i = 0; i < index.size(); ++i)
        {
            switch (i)
            {
            case 0:
                res[index[i]] = "Gold Medal";
                break;
            case 1:
                res[index[i]] = "Silver Meda";
                break;
            case 2:
                res[index[i]] = "Bronze Meda";
                break;
            default:
                res[index[i]] = to_string(i + 1);
                break;
            }
        }
        return res;
    }

    int largestSumAfterKNegations(vector<int> &nums, int k)
    {
        auto end = nums.end();
        auto begin = nums.begin();
        sort(begin, end);
        auto it = begin;
        for (; it < end && *it < 0 && k; ++it, --k)
            *it = -*it;
        if (k & 1)
        {
            if (it != begin && it != end)
                *it -= 2 * min(*it, *(it - 1));
            else if (it == begin)
                *it = -*it;
            else
                *(it - 1) = -*(it - 1);
        }
        int sum = 0;
        for (int i : nums)
            sum += i;
        return sum;
    }

    bool canConstruct(const string &ransomNote, string magazine)
    {
        if (ransomNote.length() > magazine.length())
            return false;

        for (char ch : ransomNote)
        {
            auto f = magazine.find(ch);
            if (f != magazine.npos)
                magazine[f] = ' ';
            else
                return false;
        }
        return true;
    }

    class superPowClass
    {
    public:
        const int MOD = 1337;

        int superPow(int a, vector<int> &b)
        {
            int res = qmod(a, b[0]) % MOD;
            for (int i = 1; i < b.size(); ++i)
                res = qmod(res, 10) * qmod(a, b[i]) % MOD;
            return res;
        }

        int qmod(int a, int b)
        {
            int ans = 1;
            a %= MOD;
            while (b)
            {
                if (b & 1)
                    ans = ans * a % MOD;
                a = a * a % MOD;
                b >>= 1;
            }
            return ans;
        }
    };

    string truncateSentence(string s, int k)
    {
        auto it = s.begin();
        for (; k && it < s.end(); --k)
        {
            while (*it != ' ' && it != s.end())
                ++it;
            while (*it == ' ' && it != s.end())
                ++it;
        }
        return std::move(string(s.begin(), it));
    }

    vector<vector<int>> colorBorder(vector<vector<int>> &grid, int row, int col, int color)
    {
        struct pairHash
        {
            size_t operator()(const pair<int, int> &p) const
            {
                return hash<int>{}(p.first) ^ hash<int>{}(p.second);
            }
        };
        unordered_set<pair<int, int>, pairHash> edge;

        int m = grid.size(), n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        int originalColor = grid[row][col];

        function<void(int, int)>
            dfs = [&grid, &edge, &dfs, &visited, &m, &n, &originalColor](int x, int y)
        {
            visited[x][y] = true;
            bool is_edge = false;
            if (x > 0 && grid[x - 1][y] == originalColor)
            {
                if (!visited[x - 1][y])
                    dfs(x - 1, y);
            }
            else
                is_edge = true;
            if (y < n - 1 && grid[x][y + 1] == originalColor)
            {
                if (!visited[x][y + 1])
                    dfs(x, y + 1);
            }
            else
                is_edge = true;
            if (x < m - 1 && grid[x + 1][y] == originalColor)
            {
                if (!visited[x + 1][y])
                    dfs(x + 1, y);
            }
            else
                is_edge = true;
            if (y > 0 && grid[x][y - 1] == originalColor)
            {
                if (!visited[x][y - 1])
                    dfs(x, y - 1);
            }
            else
                is_edge = true;

            if (is_edge)
                edge.insert(pair<int, int>(x, y));
        };
        dfs(row, col);
        for (auto p : edge)
            grid[p.first][p.second] = color;
        return grid;
    }

    class TopVotedCandidate
    {
    private:
        vector<int> presons;
        vector<int> times;

    public:
        TopVotedCandidate(vector<int> &_persons, vector<int> &_times)
            : presons(std::move(_persons)), times(std::move(_times))
        {
            unordered_map<int, int> votes;
            int cnt = 0;
            votes[-1] = -1;
            int max_it = -1;
            for (auto &i : presons)
            {
                ++votes[i];
                if (votes[i] >= votes[max_it])
                    max_it = i;
                i = max_it;
            }
        }

        int q(int t)
        {
            auto i = upper_bound(times.begin(), times.end(), t) - times.begin();
            return presons[i == 0 ? 0 : i - 1];
        }
    };

    string toLowerCase(string &s)
    {
        for (char &ch : s)
            if (isupper(ch))
                ch += 32;
        return std::move(s);
    }

    int maxIncreaseKeepingSkyline(vector<vector<int>> &grid)
    {
        vector<int> col(grid.size(), -1);
        vector<int> row(grid.size(), -1);

        for (int i = 0; i < grid.size(); ++i)
        {
            for (int j = 0; j < grid.size(); ++j)
            {
                row[i] = max(grid[i][j], row[i]);
                col[j] = max(grid[i][j], col[j]);
            }
        }
        int res = 0;
        for (int i = 0; i < grid.size(); ++i)
        {
            for (int j = 0; j < grid.size(); ++j)
                res += min(row[i], col[j]) - grid[i][j];
        }
        return res;
    }

    int scheduleCourse(vector<vector<int>> &courses)
    {
        sort(courses.begin(), courses.end(), [](const vector<int> &l, const vector<int> &r)
             { return l[1] < r[1]; });
        priority_queue<int> q;

        int sum = 0;
        for (auto &c : courses)
        {
            if (c[0] + sum <= c[1])
            {
                sum += c[0];
                q.push(c[0]);
            }
            else if (!q.empty() && q.top() > c[0])
            {
                sum -= q.top() - c[0];
                q.pop();
                q.push(c[0]);
            }
        }
        return q.size();
    }

    vector<int> loudAndRich(vector<vector<int>> &richer, vector<int> &quiet)
    {
        auto len = quiet.size();
        vector<vector<int>> graph(len);
        for (auto &v : richer)
            graph[v[1]].emplace_back(v[0]);

        vector<int> ans(len, -1);
        function<void(int)> dfs = [&graph, &quiet, &dfs, &ans](int index)
        {
            if (ans[index] != -1)
                return;
            ans[index] = index;
            for (int i : graph[index])
            {
                dfs(i);
                if (quiet[ans[i]] < quiet[ans[index]])
                    ans[index] = ans[i];
            }
        };
        for (int i = 0; i < len; ++i)
            dfs(i);
        return ans;
    }

    int visiblePoints(vector<vector<int>> &points, int angle, vector<int> &location)
    {
        auto pos_num = points.size();
        vector<double> angles;
        int same_location = 0;
        for (int i = 0; i < pos_num; ++i)
        {
            if (points[i][0] == location[0] && points[i][1] == location[1])
            {
                ++same_location;
                continue;
            }
            double x = points[i][0] - location[0];
            double y = points[i][1] - location[1];
            angles.emplace_back(atan2(y, x) / M_PI * 180);
            angles.emplace_back(angles.back() + 360);
        }
        if (angles.empty())
            return same_location;
        sort(angles.begin(), angles.end());
        auto end = angles.end();
        auto begin = *angles.begin();
        auto top = upper_bound(angles.begin(), angles.end(), angles[0] + angle);
        auto botton = angles.begin();
        int max = top - botton;
        for (; top < end; ++top)
        {
            botton = lower_bound(botton, top, *top - angle);
            if (top - botton + 1 > max)
                max = top - botton + 1;
        }
        return max + same_location;
    }

    int numWaterBottles(int bottles, int exchange)
    {
        if (bottles < exchange)
            return bottles;
        else
            return (bottles - exchange) / (exchange - 1) + 1 + bottles;
    }

    int countBattleships(vector<vector<char>> &board)
    {
        auto col = board.size();
        auto row = board[0].size();

        int sum = 0;
        for (int y = 0; y < col; ++y)
            for (int x = 0; x < row; ++x)
                if (board[y][x] == 'X' &&
                    (x == 0 || board[y][x - 1] == '.') &&
                    (y == 0 || board[y - 1][x] == '.'))
                    ++sum;

        return sum;
    }
    int findJudge(int n, vector<vector<int>> &trust)
    {
        vector<pair<int, int>> trust_ed(n, pair<int, int>(0, 0));
        for (auto &Pair : trust)
        {
            ++trust_ed[Pair[0] - 1].first;
            ++trust_ed[Pair[1] - 1].second;
        }

        for (int i = 0; i < n; ++i)
            if (trust_ed[i].second == n - 1 && trust_ed[i].first == 0)
                return i + 1;
        return -1;
    }

    int findRadius(vector<int> &houses, vector<int> &heaters)
    {
        sort(heaters.begin(), heaters.end());
        int ans = 0;
        for (int i : houses)
        {
            auto it = upper_bound(heaters.begin(), heaters.end(), i);
            if (it == heaters.end())
                --it;
            auto delta = min(abs(*it - i), abs(i - *(it == heaters.begin() ? it : it - 1)));
            if (delta > ans)
                ans = delta;
        }
        return ans;
    }

    int dayOfYear(string &date)
    {
        date[4] = '\0';
        date[6] = '\0';
        auto strp = date.c_str();
        int year = atoi(strp);
        int month = atoi(strp + 5);
        int day = atoi(strp + 8);
        if ((!(year % 4) && year % 100) || !(year % 400))
        {
            array<int, 12> month_day_sum = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
            return month_day_sum[month - 1] + day;
        }
        else
        {
            array<int, 12> month_day_sum = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
            return month_day_sum[month - 1] + day;
        }
    }

    int repeatedStringMatch(string &a, string &b)
    {
        auto asource = a;
        auto asize = a.size();
        auto bsize = b.size();

        while (a.size() < bsize)
            a += asource;
        if (a.find(b) != string::npos)
            return a.size() / asize;
        a += asource;
        return a.find(b) == string::npos ? -1 : a.size() / asize;
    }

    string longestDupSubstring(string &s)
    {
        auto size = s.size();
        int mid = size / 2;
        int left = 1;
        int right = size;
        hash<string> hs;
        unordered_set<size_t> tab;
        string res;
        while (left <= right)
        {
            mid = (left + right) / 2;
            tab.clear();
            int i;
            string substr;
            for (i = 0; i <= size - mid; ++i)
            {
                substr = s.substr(i, mid);
                size_t Hash = hs(substr);
                if (tab.find(Hash) != tab.end())
                {
                    if (mid > res.size())
                        res = substr;
                    break;
                }
                tab.insert(Hash);
            }
            if (i <= size - mid)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return std::move(res);
    }

    int countQuadruplets(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        auto size = nums.size();
        int res = 0;
        for (int i1 = 0; i1 < size; ++i1)
        {
            for (int i2 = i1 + 1; i2 < size; ++i2)
            {
                for (int i3 = i2 + 1; i3 < size; ++i3)
                {
                    for (int i4 = i3 + 1; i4 < size; ++i4)
                    {
                        if (nums[i1] + nums[i2] + nums[i3] == nums[i4])
                            ++res;
                        else if (nums[i1] + nums[i2] + nums[i3] < nums[i4])
                            break;
                    }
                }
            }
        }
        return res;
    }

    bool isNStraightHand(vector<int> &hand, int groupSize)
    {
        auto size = hand.size();
        if (size % groupSize)
            return false;

        sort(hand.begin(), hand.end());

        int cnt = 0;
        auto it = hand.begin();
        while (it < hand.end())
        {
            if (cnt < groupSize)
            {
                auto next_it = upper_bound(hand.begin(), hand.end(), *it);
                if (next_it == hand.end())
                    return false;
                *it = -1;
                it = next_it;
            }
            else
            {
                cnt = 0;
                *it = -1;
                ++it;
            }
        }
        return true;
    }

    bool checkPerfectNumber(int num)
    {
        int sum = -num;
        int sq = sqrt(num);
        for (int i = 1; i <= sq; ++i)
        {
            if (num % i)
                continue;

            sum += i + num / i;
        }
        return sum == num;
    }

    vector<vector<int>> construct2DArray(vector<int> &original, int m, int n)
    {
        int size = original.size();

        if (size != m * n)
            return {};
        vector<vector<int>> res(m, vector<int>(n));
        auto row_it = res.begin();
        auto it = row_it->begin();

        for (int i : original)
        {
            *it = i;
            if (++it == row_it->end())
            {
                ++row_it;
                if (row_it != res.end())
                    it = row_it->begin();
            }
        }

        return std::move(res);
    }

    int lastRemaining(int n)
    {
        int l = 1;
        int nums = n;
        int delta = 1;
        bool revel = true;
        while (nums > 1)
        {
            if (revel || nums & 1)
                l += delta;
            delta *= 2;
            nums /= 2;
            revel = !revel;
        }
        return l;
    }

    string dayOfTheWeek(int day, int month, int year)
    {
        int delta_year = year - 1971;
        int delta_day = 365 * delta_year + (delta_year + 2) / 4;

        if ((!(year % 4) && year % 100) || !(year % 400))
        {
            array<int, 12> month_day_sum = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
            delta_day += month_day_sum[month - 1] + day;
        }
        else
        {
            array<int, 12> month_day_sum = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
            delta_day += month_day_sum[month - 1] + day;
        }

        int week = delta_day % 7;

        switch (week)
        {
        case 1:
            return "Friday";
            break;
        case 2:
            return "Saturday";
            break;
        case 3:
            return "Sunday";
            break;
        case 4:
            return "Monday";
            break;
        case 5:
            return "Tuesday";
            break;
        case 6:
            return "Wednesday";
            break;
        case 0:
            return "Thursday";
            break;
        default:
            return "";
            break;
        }
    }

    string modifyString(string &s)
    {
        auto begin = s.begin();
        auto end = s.end();

        if (s.size() == 1)
            return *begin == '?' ? "a" : s;

        for (auto it = begin; it < s.end(); ++it)
        {
            if (*it != '?')
                continue;
            *it = 'a';
            while ((it != begin && *it == *(it + 1)) || (it != end - 1 && *it == *(it - 1)))
                ++(*it);
        }
        return std::move(s);
    }

    string simplifyPath(string &path)
    {
        stack<string> folders;
        auto begin = path.begin();
        auto end = path.end();
        auto it = begin;
        while (++it < end)
        {
            if (*it == '/')
                continue;
            auto r = it;
            while (++r < end && *r != '/')
            {
            }
            auto tmp = string(it, r);
            if (tmp == "..")
            {
                if (!folders.empty())
                    folders.pop();
            }
            else if (tmp != ".")
                folders.push(std::move(tmp));

            it = r;
        }

        string res;
        while (!folders.empty())
        {
            res = "/" + std::move(folders.top()) + res;
            folders.pop();
        }

        return std::move(res == "" ? "/" : res);
    }

    int maxDepth(string &s)
    {
        uint16_t depth = 0;
        uint16_t max_depth = 0;

        for (char ch : s)
        {
            if (ch == '(')
            {
                ++depth;
                if (depth > max_depth)
                    ++max_depth;
            }
            else if (ch == ')')
                --depth;
        }
        return max_depth;
    }

    vector<int> grayCode(int n)
    {

        vector<int> res(1 << n);
        auto _size = 1 << n;
        for (int i = 0; i < _size; ++i)
            res[i] = (i >> 1) ^ i;
        return res;
    }

    char slowestKey(vector<int> &releaseTimes, string &keysPressed)
    {
        auto size = releaseTimes.size();
        char res = keysPressed[0];
        int res_time = releaseTimes[0];
        for (int i = 1; i < size; ++i)
        {
            if (releaseTimes[i] - releaseTimes[i - 1] > res_time || (releaseTimes[i] - releaseTimes[i - 1] == res_time && keysPressed[i] > res))
            {
                res = keysPressed[i];
                res_time = releaseTimes[i] - releaseTimes[i - 1];
            }
        }
        return res;
    }

    bool isAdditiveNumber(const string &num)
    {
        auto size = num.size();
        if (size < 3)
            return false;

        uint64_t num1, num2, num3;
        uint16_t it1, it2, it3;
        it1 = 0;
        while (++it1 <= size / 2 + 1)
        {
            num1 = stoull(num.substr(0, it1));
            it2 = it1;
            while (++it2 <= size - it1)
            {
                if (num[it1] == '0' && it2 - it1 > 1)
                    break;
                num2 = stoull(num.substr(it1, it2 - it1));
                // TODO: can prune
                it3 = it2;
                while (++it3 <= size)
                {
                    if (num[it2] == '0' && it3 - it2 > 1)
                        break;
                    num3 = stoll(num.substr(it2, it3 - it2));
                    if (num3 == num1 + num2)
                    {
                        uint64_t next = num2 + num3;
                        while (it3 < size)
                        {
                            auto next_str = to_string(next);
                            if (next_str.size() + it3 > size)
                                break;
                            if (next_str != num.substr(it3, next_str.size()))
                                break;
                            it3 += next_str.size();
                            num2 = num3;
                            num3 = next;
                            next += num2;
                        }
                        if (it3 == size)
                            return true;
                    }
                    if (num3 > num1 + num2)
                        break;
                }
            }
            if (num[0] == '0')
                break;
        }
        return false;
    }

    bool isEscapePossible(vector<vector<int>> &blocked, vector<int> &source, vector<int> &target)
    {
        auto blocked_size = blocked.size();
        if (blocked_size < 2)
            return true;
        int width, length;
        for (auto &v : blocked)
        {
            length = max(v[0], length);
            width = max(v[1], width);
        }
        length = max(source[0], length);
        width = max(source[1], width);

        length = max(target[0], length);
        width = max(target[1], width);

        ++length;
        ++width;

        vector<vector<bool>> tab(length, vector<bool>(width, false));

        return true;
    }

    bool increasingTriplet(vector<int> &nums)
    {
        if (nums.size() < 3)
            return false;
        int small_num = INT_MAX;
        int mid = INT_MAX;
        for (int i : nums)
        {
            if (i > mid)
                return true;
            if (i < small_num)
                small_num = i;
            else
                mid = i;
        }
        return false;
    }

    int dominantIndex(vector<int> &nums)
    {
        int Max = 0;
        for (int i = 0; i < nums.size(); ++i)
        {
            if (nums[i] > nums[Max])
            {
                if (nums[i] < 2 * nums[Max])
                    return -1;
                Max = i;
            }
        }
        return Max;
    }

    int countVowelPermutation(int n)
    {
        array<array<uint32_t, 5>, 2> dp;
        dp[0].fill(1);
        auto begin = &dp[0];
        auto end = &dp[1];
        int mod = 1000000007;
        for (int i = 1; i < n; ++i)
        {
            end->at(0) = (begin->at(1) + begin->at(2) + begin->at(4)) % mod;
            end->at(1) = (begin->at(0) + begin->at(2)) % mod;
            end->at(2) = (begin->at(1) + begin->at(3)) % mod;
            end->at(3) = begin->at(2) % mod;
            end->at(4) = (begin->at(2) + begin->at(3)) % mod;
            swap(begin, end);
        }

        return accumulate(begin->begin(), begin->end(), 0LL) % mod;
    }

    bool containsNearbyDuplicate(vector<int> &nums, int k)
    {
        unordered_set<int> tab;
        auto size = nums.size();
        tab.reserve(k + 1);
        for (int i = 0; i < size; ++i)
        {
            if (i > k)
                tab.erase(nums[i - k - 1]);
            if (tab.count(nums[i]))
                return true;
            tab.emplace(nums[i]);
        }
        return false;
    }

    bool stoneGameIX(vector<int> &stones)
    {
        array<int, 3> cnt{{0}};
        for (int i : stones)
            ++cnt[i % 3];
        if (cnt[0] & 1)
            return cnt[1] - cnt[2] > 2 || cnt[2] - cnt[1] > 2;
        else
            return cnt[1] >= 1 && cnt[2] >= 1;
    }

    int minJumps(const vector<int> &arr)
    {
        if (arr.size() == 1)
            return 0;

        unordered_map<int, vector<int>> same_val_index;
        auto size = arr.size();
        for (int i = 0; i < size; ++i)
            same_val_index[arr[i]].push_back(i);
        queue<pair<int, int>> que;
        que.emplace(0, 0);
        while (!que.empty())
        {
            auto it = que.front();
            que.pop();
            if (it.first == size - 2 || arr[it.first] == arr.back())
                return it.second + 1;
            if (same_val_index.count(arr[it.first]))
            {
                for (int i : same_val_index[arr[it.first]])
                    if (i != it.first)
                        que.emplace(i, it.second + 1);

                same_val_index.erase(arr[it.first]);
            }
            if (it.first != 0 && same_val_index.count(arr[it.first - 1]))
                que.emplace(it.first - 1, it.second + 1);
            if (it.first < size - 1)
                que.emplace(it.first + 1, it.second + 1);
        }
        return -1;
    }

    int secondMinimum(int n, vector<vector<int>> &edges, int time, int change)
    {
        vector<vector<int>> _edges(n);
        for (auto &edge : edges)
        {
            _edges[edge[0] - 1].emplace_back(edge[1] - 1);
            _edges[edge[1] - 1].emplace_back(edge[0] - 1);
        }

        vector<array<int, 2>> hit_times(n);

        queue<array<int, 2>> que;
        que.push({0, 0});
        while (!que.empty() && hit_times[n - 1][1] == 0)
        {
            auto [it, cnt] = que.front();
            que.pop();

            for (auto i : _edges[it])
                if (!hit_times[i][0])
                {
                    hit_times[i][0] = cnt + 1;
                    que.push({i, cnt + 1});
                }
                else if (cnt + 1 > hit_times[i][0] && !hit_times[i][1])
                {
                    hit_times[i][1] = cnt + 1;
                    que.push({i, cnt + 1});
                }
        }
        int res = 0;
        for (int i = 0; i < hit_times[n - 1][1]; ++i)
            res += (res % (2 * change) < change ? 0 : (2 * change - res % (2 * change))) + time;
        return res;
    }

    int numberOfMatches(int n)
    {
        int res = 0;
        while (n != 1)
        {
            res += n / 2;
            n = n / 2 + n & 1;
        }
        return res;
    }

    vector<string> uncommonFromSentences(const string &s1, const string &s2)
    {
        unordered_map<string, int> Map;
        auto it_front = s1.begin();
        auto it_back = it_front;
        while (it_back != s1.end())
        {
            if (*(++it_back) == ' ')
            {
                ++Map[move(string(it_front, it_back))];
                it_front = ++it_back;
            }
        }
        ++Map[move(string(it_front, it_back))];

        it_front = s2.begin();
        it_back = it_front;
        while (it_back != s2.end())
        {
            if (*(++it_back) == ' ')
            {
                ++Map[move(string(it_front, it_back))];
                it_front = ++it_back;
            }
        }
        ++Map[move(string(it_front, it_back))];

        vector<string> res;
        for (auto &p : Map)
            if (p.second == 1)
                res.emplace_back(p.first);

        return move(res);
    }

    int numberOfSteps(int num)
    {
        return num ? (31 - __builtin_clz(num) + __builtin_popcount(num)) : 0;
    }

    string longestNiceSubstring(string s)
    {
        int maxPos = 0, maxLen = 0;
        auto check = [&](int typeNum)
        {
            vector<int> lowerCnt(26);
            vector<int> upperCnt(26);
            int cnt = 0;
            for (int l = 0, r = 0, total = 0; r < s.size(); ++r)
            {
                int idx = tolower(s[r]) - 'a';
                if (islower(s[r]))
                {
                    ++lowerCnt[idx];
                    if (lowerCnt[idx] == 1 && upperCnt[idx] > 0)
                    {
                        ++cnt;
                    }
                }
                else
                {
                    ++upperCnt[idx];
                    if (upperCnt[idx] == 1 && lowerCnt[idx] > 0)
                    {
                        ++cnt;
                    }
                }
                total += (lowerCnt[idx] + upperCnt[idx]) == 1 ? 1 : 0;

                while (total > typeNum)
                {
                    idx = tolower(s[l]) - 'a';
                    total -= (lowerCnt[idx] + upperCnt[idx]) == 1 ? 1 : 0;
                    if (islower(s[l]))
                    {
                        --lowerCnt[idx];
                        if (lowerCnt[idx] == 0 && upperCnt[idx] > 0)
                        {
                            --cnt;
                        }
                    }
                    else
                    {
                        --upperCnt[idx];
                        if (upperCnt[idx] == 0 && lowerCnt[idx] > 0)
                        {
                            --cnt;
                        }
                    }
                    ++l;
                }
                if (cnt == typeNum && r - l + 1 > maxLen)
                {
                    maxPos = l;
                    maxLen = r - l + 1;
                }
            }
        };

        int mask = 0;
        for (char &ch : s)
        {
            mask |= 1 << (tolower(ch) - 'a');
        }
        int types = __builtin_popcount(mask);
        for (int i = 1; i <= types; ++i)
        {
            check(i);
        }
        return s.substr(maxPos, maxLen);
    }

    string reversePrefix(string word, char ch)
    {
        if (auto it = word.find(ch); it != string::npos)
        {
            std::reverse(word.begin(), word.begin() + it + 1);
            return std::move(word);
        }
        else
            return std::move(word);
    }

    int findMinFibonacciNumbers(int k)
    {

        vector<int> fb({1, 1});
        while (fb.back() <= k)
            fb.emplace_back(fb.back() + *(fb.end() - 2));
        int cnt = 0;
        auto it = fb.end();
        while (k)
        {
            it = upper_bound(fb.begin(), it, k);
            if (it > fb.begin())
                k -= *(it - 1);
            else
                cout << "can't found.\n";
            ++cnt;
        }
        return cnt;
    }

    int numEnclaves(vector<vector<int>> &grid)
    {
        auto weighLen = grid[0].size();
        auto heighLen = grid.size();
        int cnt = 0;
        std::function<void(int, int)> dfs = [&](int height, int weight)
        {
            if (height < 0 || height >= heighLen || weight < 0 || weight >= weighLen || grid[height][weight] == 0)
                return;

            grid[height][weight] = 0;
            if (cnt != -1)
            {
                if (height > 0 && height < heighLen - 1 && weight > 0 && weight < weighLen - 1)
                    ++cnt;
                else
                    cnt = -1;
            }

            dfs(height - 1, weight);
            dfs(height + 1, weight);
            dfs(height, weight + 1);
            dfs(height, weight - 1);
        };

        int res = 0;
        for (int i = 0; i < heighLen; ++i)
            for (int j = 0; j < weighLen; ++j)
                if (grid[i][j] == 1)
                {
                    dfs(i, j);
                    res += cnt == -1 ? 0 : cnt;
                    cnt = 0;
                }

        return res;
    }

    int singleNonDuplicate(vector<int> &nums)
    {
        auto size = nums.size();
        auto begin = 0;
        auto end = size;
        auto left = begin;
        auto right = end;
        auto it = (left + right) / 2;
        while (it != end)
        {
            if ((it == 0 || nums[it] != nums[it - 1]) && (it == end - 1 || nums[it] != nums[it + 1]))
                return nums[it];

            if (it != 0 && nums[it] == nums[it - 1])
            {
                if ((it - begin) & 1)
                    left = it;
                else
                    right = it;
            }
            else
            {
                if ((it - begin) & 1)
                    right = it;
                else
                    left = it;
            }
            it = (left + right) / 2;
        }
        // error
        return -1;
    }

    vector<int> luckyNumbers(vector<vector<int>> &matrix)
    {
        auto cols = matrix[0].size();
        auto rows = matrix.size();
        vector<int> minInRow;
        minInRow.reserve(rows);

        for (auto &row : matrix)
            minInRow.push_back(*min_element(row.begin(), row.end()));

        vector<int> res;
        for (int col = 0; col < cols; ++col)
        {
            int it = 0;
            int _max = -1;
            for (int row = 0; row < rows; ++row)
            {
                if (matrix[row][col] > _max)
                {
                    it = row;
                    _max = matrix[row][col];
                }
            }
            if (_max == minInRow[it])
                res.push_back(_max);
        }
        return res;
    }

    string pushDominoes(string &dominoes)
    {
        auto end = dominoes.end();
        auto left_it = dominoes.begin();
        char left = 'L';
        while (left_it < end)
        {
            auto right_it = left_it;
            while (right_it < end && *right_it == '.')
                ++right_it;
            char right = right_it < end ? *right_it : 'R';
            if (left == right)
            {
                for (auto it = left_it; it < right_it; ++it)
                    if (*it == '.')
                        *it = left;
            }
            else if (left == 'R' && right == 'L')
            {
                for (auto _begin = left_it, _end = right_it - 1; _begin < _end; ++_begin, --_end)
                {
                    *_begin = 'R';
                    *_end = 'L';
                }
            }
            left_it = right_it + 1;
            left = right;
        }
        return dominoes;
    }

    string reverseOnlyLetters(string &s)
    {
        stack<char> index;
        for (auto ch : s)
            if (isalpha(ch))
                index.push(ch);
        for (auto &ch : s)
            if (isalpha(ch))
            {
                ch = index.top();
                index.pop();
            }
        return s;
    }

    vector<int> findBall(vector<vector<int>> &grid)
    {
        int n = grid[0].size();
        vector<int> ans(n);
        for (int j = 0; j < n; ++j)
        {
            int col = j;
            for (auto &row : grid)
            {
                int dir = row[col];
                col += dir;
                if (col < 0 || col == n || row[col] != dir)
                {
                    col = -1;
                    break;
                }
            }
            ans[j] = col;
        }
        return ans;
    }

    string complexNumberMultiply(string &num1, string &num2)
    {
        auto getNum = [](string &str)
        {
            auto it = str.begin();
            while (*it != '+')
                ++it;
            return array<int, 2>{{stoi(string{str.begin(), it}), stoi(string{it + 1, str.end() - 1})}};
        };
        auto _num1 = getNum(num1);
        auto _num2 = getNum(num2);
        return to_string(_num1[0] * _num2[0] - _num1[1] * _num2[1]) + "+" + to_string(_num1[0] * _num2[1] + _num1[1] * _num2[0]) + "i";
    }

    int maximumDifference(vector<int> &nums)
    {
        int min = nums.front();
        int res = 0;
        auto size = nums.size();
        for (int i = 1; i < size; ++i)
        {
            if (nums[i] < min)
                min = nums[i];
            else if (nums[i] - min > res)
                res = nums[i] - min;
        }
        return res == 0 ? -1 : res;
    }

    string optimalDivision(vector<int> &nums)
    {
        if (nums.size() > 2)
        {
            auto end = nums.end();
            auto it = nums.begin();
            string res = to_string(*it++) + "/(";
            while (it < end)
                res += to_string(*it++) + "/";
            res.back() = ')';
            return res;
        }
        else
        {
            string res;
            for (auto i : nums)
                res += to_string(i) + "/";
            res.pop_back();
            return res;
        }
    }

    int maximumRequests(int n, vector<vector<int>> &requests)
    {
        vector<vector<int>> _to(n + 2);
        vector<int> diff(n, 0);
        for (auto &edge : requests)
        {
            ++diff[edge[0]];
            --diff[edge[1]];
            _to[edge[0]].push_back(edge[1]);
        }

        for (int i = 0; i < n; ++i)
        {
            if (diff[i] > 0)
                for (int j = 0; j < diff[i]; ++j)
                    _to[n].push_back(i);
            else if (diff[i] < 0)
                for (int j = 0; j < -diff[i]; ++j)
                    _to[i].push_back(n + 1);
        }

        if (_to[n].size() != _to[n + 1].size())
            throw "error size.";

        function<int(list<int>, int &)> bfs = [&](list<int> froms, int &length)
        {
            list<int> next_froms;
            for (int from : froms)
            {
                for (int &to : _to[from])
                {
                    if (to == n + 1)
                    {
                        to = -1;
                        return from;
                    }
                    else if (to != -1)
                        next_froms.push_back(to);
                }
            }

            auto p = bfs(next_froms, ++length);
        };
    }

    string convert(string &s, uint32_t numRows)
    {
        string res;
        auto size = s.size();
        auto begin = s.begin();
        auto end = s.end();
        res.reserve(size);
        for (int line = 0; line < numRows; ++line)
        {
            for (auto it = begin; it < end; it += 2 * numRows - 2)
            {
                if (line == 0)
                    res.push_back(*it);
                else if (line == numRows - 1)
                {
                    if (it + line < end)
                        res.push_back(*(it + line));
                }
                else
                {
                    if (it + line < end)
                        res.push_back(*(it + line));
                    if (it + 2 * numRows - 2 - line < end)
                        res.push_back(*(it + 2 * numRows - 2 - line));
                }
            }
        }
        return res;
    }

    int addDigits(int num)
    {
        int res = 0;
        while (num)
        {
            res += num % 10;
            num /= 10;
        }
        if (res < 10)
            return res;
        else
            return addDigits(res);
    }

    int addDigits(uint32_t num)
    {
        return (num - 1) % 9 + 1;
    }

    long long subArrayRanges(vector<int> &&nums)
    {
        using _stack = stack<int>;
        auto size = nums.size();
        vector<int> lMin(size), rMin(size), rMax(size), lMax(size);

        _stack s;
        for (int i = 0; i < size; ++i)
        {
            while (!s.empty() && nums[s.top()] >= nums[i])
                s.pop();
            lMin[i] = s.empty() ? -1 : s.top();
            s.push(i);
        }

        _stack().swap(s);
        for (int i = size - 1; i >= 0; --i)
        {
            while (!s.empty() && nums[s.top()] > nums[i])
                s.pop();
            rMin[i] = s.empty() ? size : s.top();
            s.push(i);
        }

        _stack().swap(s);
        for (int i = 0; i < size; ++i)
        {
            while (!s.empty() && nums[s.top()] <= nums[i])
                s.pop();
            lMax[i] = s.empty() ? -1 : s.top();
            s.push(i);
        }

        _stack().swap(s);
        for (int i = size - 1; i >= 0; --i)
        {
            while (!s.empty() && nums[s.top()] < nums[i])
                s.pop();
            rMax[i] = s.empty() ? size : s.top();
            s.push(i);
        }

        int64_t res;
        for (int i = 0; i < size; ++i)
        {
            res += static_cast<uint64_t>(nums[i]) * (i - lMax[i]) * (rMax[i] - i);
            res -= static_cast<uint64_t>(nums[i]) * (i - lMin[i]) * (rMin[i] - i);
        }
        return res;
    }

    int findLUSlength(string &a, string &b)
    {
        return a != b ? max(a.length(), b.length()) : -1;
    }

    vector<int> goodDaysToRobBank(vector<int> &security, int time)
    {
        auto size = security.size();
        if (2 * time + 1 > size)
            return {};
        vector<array<int, 2>> cnt(size);
        cnt[0] = {0, 0};
        for (int i = 1; i < size; ++i)
        {
            cnt[i] = cnt[i - 1];
            if (security[i] > security[i - 1])
                ++cnt[i][0];
            else if (security[i] < security[i - 1])
                ++cnt[i][1];
        }

        vector<int> res;
        for (int i = time; i < size - time; ++i)
        {
            if (cnt[i][0] == cnt[i - time][0] && cnt[i][1] == cnt[i + time][1])
                res.push_back(i);
        }
        return res;
    }

    string convertToBase7(int num)
    {
        string res;
        if (num < 0)
        {
            num += 2 * num;
            res.push_back('-');
        }
        while (num)
        {
            res.push_back(num % 7 + '0');
            num /= 7;
        }
        std::reverse(res.begin(), res.end());
        return res;
    }

    vector<int> platesBetweenCandles(string &s, vector<vector<int>> &queries)
    {
        auto size = s.size();
        vector<int> prefixSum(size, 0);
        vector<int> candleIndex;

        for (int i = 0; i < size; ++i)
        {
            prefixSum[i] = prefixSum[i - 1 < 0 ? 0 : i - 1];
            if (s[i] == '*')
                ++prefixSum[i];
            else if (s[i] == '|')
                candleIndex.push_back(i);
            else
                throw std::exception();
        }
        if (candleIndex.size() < 2)
            return vector(queries.size(), 0);
        vector<int> res;
        res.reserve(queries.size());
        auto begin = candleIndex.begin();
        auto end = candleIndex.end();
        for (auto &querie : queries)
        {
            auto leftCandle = lower_bound(begin, end, querie[0]);
            auto rightCandle = upper_bound(begin, end, querie[1]) - 1;
            if (leftCandle >= end - 1 || rightCandle <= begin || leftCandle > rightCandle)
                res.push_back(0);
            else
                res.push_back(prefixSum[*rightCandle] - prefixSum[*leftCandle]);
        }
        return res;
    }

    class PreorderClass
    {
    public:
        class Node
        {
        public:
            int val;
            vector<Node *> children;

            Node() = default;

            Node(int _val)
            {
                val = _val;
            }

            Node(int _val, vector<Node *> _children)
            {
                val = _val;
                children = std::move(_children);
            }
        };

        vector<int> preorder(Node *root)
        {
            vector<int> res;
            function<void(Node *)> dfs = [&](Node *node)
            {
                if (!node)
                    return;
                res.push_back(node->val);
                for (auto next : node->children)
                    dfs(next);
            };

            dfs(root);
            return res;
        }
    };

    int countHighestScoreNodes(vector<int> &parents)
    {
        auto size = parents.size();
        vector<vector<int>> children(size);
        for (int node = 0; node < size; ++node)
        {
            if (parents[node] != -1)
                children[parents[node]].push_back(node);
        }

        uint64_t maxScore = 0, cnt = 0;

        function<int(int)> dfs = [&](int node)
        {
            uint64_t score = 1;
            int parentScore = size - 1;
            for (int child : children[node])
            {
                int num = dfs(child);
                score *= num;
                parentScore -= num;
            }

            if (node != 0)
                score *= parentScore;

            if (score > maxScore)
            {
                maxScore = score;
                cnt = 1;
            }
            else if (score == maxScore)
                ++cnt;
            return size - parentScore;
        };

        dfs(0);

        return cnt;
    }

    class PostorderClass
    {
    public:
        class Node
        {
        public:
            int val;
            vector<Node *> children;

            Node() = default;

            Node(int _val)
            {
                val = _val;
            }

            Node(int _val, vector<Node *> _children)
            {
                val = _val;
                children = std::move(_children);
            }
        };

        vector<int> postorder(Node *root)
        {
            vector<int> res;
            function<void(Node *)> dfs = [&](Node *pnode)
            {
                if (!pnode)
                    return;
                for (auto child : pnode->children)
                    dfs(child);
                res.push_back(pnode->val);
            };
            dfs(root);
            return res;
        }
    };

    bool validUtf8(vector<int> &data)
    {
        array<const int, 4> startCode = {0b11000000, 0b11100000, 0b11110000, 0b11111000};
        const int alternateCode = 0b10000000;

        auto end = data.end();
        for (auto it = data.begin(); it < end; ++it)
        {
            if (*it >= startCode[3])
                return false;
            else if (*it >= startCode[2])
            {
                for (int i = 0; i < 3; ++i)
                {
                    ++it;
                    if (it >= end || *it < alternateCode || *it >= startCode[0])
                        return false;
                }
            }
            else if (*it >= startCode[1])
            {
                for (int i = 0; i < 2; ++i)
                {
                    ++it;
                    if (it >= end || *it < alternateCode || *it >= startCode[0])
                        return false;
                }
            }
            else if (*it >= startCode[0])
            {
                for (int i = 0; i < 1; ++i)
                {
                    ++it;
                    if (it >= end || *it < alternateCode || *it >= startCode[0])
                        return false;
                }
            }
            else if (*it >= alternateCode)
                return false;
        }
        return true;
    }

    vector<string> findRestaurant(vector<string> &list1, vector<string> &list2)
    {
        unordered_map<string, int> map1;
        unordered_map<string, int> map2;
        auto list1size = list1.size();
        for (int i = 0; i < list1size; ++i)
            map1.insert({std::move(list1[i]), i});

        auto list2size = list2.size();

        for (int i = 0; i < list2size; ++i)
            if (map1.count(list2[i]))
                map2.insert({std::move(list2[i]), map1[list2[i]] + i});

        vector<string> res;
        auto minimun = INT_MAX;
        for (auto &p : map2)
            minimun = min(p.second, minimun);
        for (auto &p : map2)
        {
            if (p.second == minimun)
                res.emplace_back(p.first);
        }

        return res;
    }

    int countMaxOrSubsets(vector<int> &nums)
    {
        int Max = 0;
        int cnt = 0;
        auto size = nums.size();
        function<void(int, int)> dfs = [&](int it, int orVal)
        {
            if (it == size)
            {
                if (Max < orVal)
                {
                    Max = orVal;
                    cnt = 1;
                }
                else if (Max == orVal)
                    ++cnt;
            }

            dfs(it + 1, orVal | nums[it]);
            dfs(it + 1, orVal);
        };
        dfs(0, 0);
        return cnt;
    }

#if 1
    class AllOne
    {
    public:
        AllOne() = default;

        void inc(const string &key)
        {
            if (index.count(key))
            {
                index[key]->inc();
            }
            else
            {
                if (!index.empty())
                    index.insert({key, new MyList(key, min)});
                else
                {
                    index[key] = new MyList(key);
                    min = index[key];
                    max = min;
                }
            }
            updateMinMax();
        }

        void dec(const string &key)
        {
            auto node = index[key];
            if (--node->cnt() <= 0)
            {
                if (index.size() == 1)
                {
                    min = nullptr;
                    max = nullptr;
                }
                else
                {
                    if (min == node)
                        min = node->next() ? node->next() : (node->prev() ? node->prev() : nullptr);
                    if (max == node)
                        max = node->prev() ? node->prev() : (node->next() ? node->next() : nullptr);
                }

                delete node;
                index.erase(key);
            }
            else
                while (node->prev() && node->prev()->cnt() > node->cnt())
                    node->moveFront();

            updateMinMax();
        }

        string getMaxKey()
        {
            if (max)
                return max->str();
            else
                return {};
        }

        string getMinKey()
        {
            if (min)
                return min->str();
            else
                return {};
        }

        class MyList
        {

        public:
            MyList() = default;
            using PListNode = MyList *;
            MyList(string &&str, PListNode root = nullptr) : _str(str)
            {
                if (root)
                    root->PrevAdd(this);
            }
            MyList(string str, PListNode root = nullptr) : _str(std::move(str))
            {
                if (root)
                    root->PrevAdd(this);
            }

            void PrevAdd(PListNode node)
            {
                if (!node)
                    throw "node is nullptr";
                node->_next = this;
                if (!_prev)
                {
                    _prev = node;
                }
                else
                {
                    node->_prev = _prev;
                    _prev->_next = node;
                    _prev = node;
                }
            }

            void NextAdd(PListNode node)
            {
                if (_next)
                {
                    _next->PrevAdd(node);
                    return;
                }
                if (!node)
                    throw "node is nullptr";
                node->_prev = this;
                _next = node;
            }

            void moveFront()
            {
                if (!_prev)
                    return;
                bool has_prev_prev = _prev->_prev;
                if (has_prev_prev)
                    _prev->_prev->_next = this;
                if (_next)
                    _next->_prev = _prev;
                auto tmp = _prev->_prev;
                _prev->_prev = this;
                _prev->_next = _next;
                _next = _prev;
                _prev = tmp;
            }

            void moveBack()
            {
                if (!_next)
                    return;
                _next->moveFront();
            }

            ~MyList()
            {
                if (_prev)
                    _prev->_next = _next;
                if (_next)
                    _next->_prev = _prev;
            }

            void inc()
            {
                ++_cnt;
                while (_next && _next->_cnt < _cnt)
                    moveBack();
            }

            string &str() { return _str; }
            int &cnt() { return _cnt; }
            const PListNode &prev() { return _prev; }
            const PListNode &next() { return _next; }

        private:
            string _str{};
            int _cnt{1};
            PListNode _prev{};
            PListNode _next{};
        };

        void updateMinMax()
        {
            while (min->prev())
                min = min->prev();
            while (max->next())
                max = max->next();
        }

    private:
        using PListNode = MyList *;
        unordered_map<string, PListNode> index;
        PListNode min;
        PListNode max;
    };

    /**
     * Your AllOne object will be instantiated and called as such:
     * AllOne* obj = new AllOne();
     * obj->inc(key);
     * obj->dec(key);
     * string param_3 = obj->getMaxKey();
     * string param_4 = obj->getMinKey();
     */
#else

    class AllOne
    {
        list<pair<unordered_set<string>, int>> lst;
        unordered_map<string, list<pair<unordered_set<string>, int>>::iterator> nodes;

    public:
        AllOne() {}

        void inc(string key)
        {
            if (nodes.count(key))
            {
                auto cur = nodes[key], nxt = next(cur);
                if (nxt == lst.end() || nxt->second > cur->second + 1)
                {
                    unordered_set<string> s({key});
                    nodes[key] = lst.emplace(nxt, s, cur->second + 1);
                }
                else
                {
                    nxt->first.emplace(key);
                    nodes[key] = nxt;
                }
                cur->first.erase(key);
                if (cur->first.empty())
                {
                    lst.erase(cur);
                }
            }
            else
            { 
                if (lst.empty() || lst.begin()->second > 1)
                {
                    unordered_set<string> s({key});
                    lst.emplace_front(s, 1);
                }
                else
                {
                    lst.begin()->first.emplace(key);
                }
                nodes[key] = lst.begin();
            }
        }

        void dec(string key)
        {
            auto cur = nodes[key];
            if (cur->second == 1)
            {
                nodes.erase(key);
            }
            else
            {
                auto pre = prev(cur);
                if (cur == lst.begin() || pre->second < cur->second - 1)
                {
                    unordered_set<string> s({key});
                    nodes[key] = lst.emplace(cur, s, cur->second - 1);
                }
                else
                {
                    pre->first.emplace(key);
                    nodes[key] = pre;
                }
            }
            cur->first.erase(key);
            if (cur->first.empty())
            {
                lst.erase(cur);
            }
        }

        string getMaxKey()
        {
            return lst.empty() ? "" : *lst.rbegin()->first.begin();
        }

        string getMinKey()
        {
            return lst.empty() ? "" : *lst.begin()->first.begin();
        }
    };
#endif

    string longestWord(vector<string> &words)
    {
        sort(words.begin(), words.end(), [](const string &l, const string &r)
             { return l.size() != r.size() ? l.size() > r.size() : l < r; });
        unordered_set<string> index(words.begin(), words.end());
        for (auto &ref_str : words)
        {
            auto str = ref_str;
            str.pop_back();
            while (!str.empty())
            {
                if (!index.count(str))
                    break;
                else
                    str.pop_back();
            }
            if (str.empty())
                return ref_str;
        }
        return {};
    }

    class Bank
    {
    public:
        Bank(vector<long long> &balance) : size(data.size()), data(std::move(balance)) {}

        bool transfer(int account1, int account2, long long money)
        {
            --account1;
            --account2;
            if (!assertIndex(account1) || !assertIndex(account2))
                return false;
            if (data[account1] < money)
                return false;
            data[account1] -= money;
            data[account2] += money;
            return true;
        }

        bool deposit(int account, long long money)
        {
            --account;
            if (!assertIndex(account))
                return false;
            data[account] += money;
            return true;
        }

        bool withdraw(int account, long long money)
        {
            --account;
            if (assertIndex(account) && data[account] >= money)
            {
                data[account] -= money;
                return true;
            }
            return false;
        }

    private:
        bool assertIndex(int i)
        {
            return i >= 0 && i < size;
        }
        vector<long long> data;
        size_t size;
    };

    /**
     * Your Bank object will be instantiated and called as such:
     * Bank* obj = new Bank(balance);
     * bool param_1 = obj->transfer(account1,account2,money);
     * bool param_2 = obj->deposit(account,money);
     * bool param_3 = obj->withdraw(account,money);
     */

    string tree2str(TreeNode *root)
    {
        string res;
        function<void(TreeNode *)> dfs = [&](TreeNode *node)
        {
            res += to_string(node->val);
            if (!node->left && !node->right)
                return;
            res += "(";
            if (node->left)
                dfs(node->left);
            res += ")";

            if (node->right)
            {
                res += "(";
                dfs(node->right);
                res += ")";
            }
        };

        dfs(root);
        return res;
    }

    bool findTarget(TreeNode *root, int k)
    {
        unordered_set<int> hashTab;
        function<void(TreeNode *)> bfs = [&](TreeNode *node)
        {
            if (!node)
                return;
            bfs(node->left);
            bfs(node->right);
            hashTab.insert(node->val);
        };

        bfs(root);
        for (auto i : hashTab)
        {
            if (hashTab.count(k - i) && k - i != i)
                return true;
        }
        return false;
    }

    bool winnerOfGame(string colors)
    {
        array<int, 2> ABtimes{0};
        char cur = 0;
        int cnt = 1;
        for (char ch : colors)
        {
            if (ch != cur)
            {
                if (cur == 0)
                {
                    cur = ch;
                    continue;
                }

                ABtimes[cur - 'A'] += max(0, cnt - 2);

                cur = ch;
                cnt = 1;
            }
            else
                ++cnt;
        }
        ABtimes[cur - 'A'] += max(0, cnt - 2);
        return ABtimes[0] > ABtimes[1];
    }

    int findKthNumber(int n, int k)
    {

        function<int(int, int)> getSteps = [](int curr, int n)
        {
            int steps = 0;
            long first = curr;
            long last = curr;
            while (first <= n)
            {
                steps += std::min(last, (long)n) - first + 1;
                first = first * 10;
                last = last * 10 + 9;
            }
            return steps;
        };
        int curr = 1;
        k--;
        while (k > 0)
        {
            int steps = getSteps(curr, n);
            if (steps <= k)
            {
                k -= steps;
                curr++;
            }
            else
            {
                curr = curr * 10;
                k--;
            }
        }
        return curr;
    }

    vector<vector<int>> imageSmoother(vector<vector<int>> &img)
    {
        int m = img.size();
        int n = img[0].size();

        auto indexCheck = [&](int y, int x)
        {
            return y >= 0 && y < m && x >= 0 && x < n;
        };

        vector<vector<int>> res(m, vector<int>(n));
        for (int y{}; y < m; ++y)
        {
            for (int x{}; x < n; ++x)
            {
                int sum{}, cnt{};
                for (int _y = -1; _y <= 1; ++_y)
                {
                    for (int _x = -1; _x <= 1; ++_x)
                    {
                        if (indexCheck(y + _y, x + _x))
                        {
                            sum += img[y + _y][x + _x];
                            ++cnt;
                        }
                    }
                }
                res[y][x] = sum / cnt;
            }
        }
        return res;
    }

    int trailingZeroes(int n)
    {
        int res{};
        while (n)
        {
            n /= 5;
            res += n;
        }
        return res;
    }

    int calPoints(vector<string> &ops)
    {
        vector<int> res;
        res.reserve(ops.size());

        for (auto &str : ops)
        {
            if (str == "C")
                res.pop_back();
            else if (str == "D")
                res.push_back(res.back() * 2);
            else if (str == "+")
                res.push_back(*(res.end() - 2) + *(res.end() - 1));
            else
                res.push_back(std::stoi(str));
        }

        return std::accumulate(res.begin(), res.end(), 0);
    }

    vector<int> missingRolls(vector<int> &rolls, int mean, int n)
    {
        auto mn = rolls.size() + n;
        auto sum = mn * mean;
        auto diff = sum - std::accumulate(rolls.begin(), rolls.end(), 0);
        double diffAvg = (double)(diff) / n;
        if (diffAvg > 6 || diffAvg < 1)
            return {};
        vector<int> res;
        res.reserve(n);
        int adj = diff - static_cast<long long>(n) * (int)diffAvg;
        for (int i{}; i < adj; ++i)
            res.emplace_back((int)diffAvg + 1);
        for (int i{adj}; i < n; ++i)
            res.emplace_back((int)diffAvg);
        return res;
    }

    bool hasAlternatingBits(int n)
    {
        long nn = n ^ (n >> 1);
        return !(nn & (nn + 1));
    }

    int maxConsecutiveAnswers(string key, int k)
    {
        auto size = key.size();
        int res{};

        for (int l{}, r{}, cnt{}; r < size; ++r)
        {
            if (key[r] != 'T')
                ++cnt;
            while (cnt > k)
                if (key[l++] != 'T')
                    --cnt;
            res = max(res, r - l + 1);
        }

        for (int l{}, r{}, cnt{}; r < size; ++r)
        {
            if (key[r] != 'F')
                ++cnt;
            while (cnt > k)
                if (key[l++] != 'F')
                    --cnt;
            res = max(res, r - l + 1);
        }

        return res;
    }

    vector<int> busiestServers(int k, const vector<int> &arrival, const vector<int> &load)
    {
        priority_queue<int, vector<int>, greater<>> freeServer;
        for (int i{}; i < k; ++i)
            freeServer.push(i);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> busyServer;
        vector<int> serverCnt(k, 0);
        auto requestNUms = arrival.size();
        for (int i{}; i < requestNUms; ++i)
        {
            while (!busyServer.empty() && busyServer.top().first <= arrival[i])
            {
                auto id = busyServer.top().second;
                busyServer.pop();
                freeServer.push(i + ((id - i) % k + k) % k);
            }
            if (freeServer.empty())
                continue;
            auto it = freeServer.top() % k;
            freeServer.pop();
            ++serverCnt[it];
            busyServer.push({arrival[i] + load[i], it});
        }
        auto maxCnt = *max_element(serverCnt.begin(), serverCnt.end());
        vector<int> res;

        for (int i{}; i < k; ++i)
            if (serverCnt[i] == maxCnt)
                res.push_back(i);
        return res;
    }

    vector<int> selfDividingNumbers(int left, int right)
    {

        auto [tab, cnt] = []() constexpr
        {
            int cnt{};
            array<int, 500> tab;
            for (int i{1}; i <= 10000; ++i)
            {
                int j = i;
                while (j)
                {
                    if (j % 10 == 0)
                        break;
                    if (i % (j % 10))
                        break;
                    j /= 10;
                }
                if (!j)
                {
                    tab[cnt++] = i;
                }
            }
            return pair(tab, cnt);
        }
        ();

        return {lower_bound(tab.begin(), tab.begin() + cnt - 1, left), lower_bound(tab.begin(), tab.begin() + cnt - 1, right)};
    }

    bool canReorderDoubled(auto &&arr)
    {
        struct comp
        {
            bool operator()(int l, int r) const
            {
                if (l < 0 && r < 0)
                    return l > r;
                else
                    return l < r;
            }
        };
        multiset<int, comp> tab(arr.begin(), arr.end());

        if (tab.count(0) & 1)
            return false;
        if (tab.count(0))
            tab.erase(0);
        while (!tab.empty())
        {

            if (auto it = tab.find(*tab.begin() * 2); it == tab.end())
                return false;
            else
            {
                tab.erase(it);
                tab.erase(tab.begin());
            }
        }
        return true;
    }

    int strongPasswordChecker(string password)
    {
        int n = password.size();
        bool has_lower = false, has_upper = false, has_digit = false;
        for (char ch : password)
        {
            if (islower(ch))
            {
                has_lower = true;
            }
            else if (isupper(ch))
            {
                has_upper = true;
            }
            else if (isdigit(ch))
            {
                has_digit = true;
            }
        }
        int categories = has_lower + has_upper + has_digit;

        if (n < 6)
        {
            return max(6 - n, 3 - categories);
        }
        else if (n <= 20)
        {
            int replace = 0;
            int cnt = 0;
            char cur = '#';

            for (char ch : password)
            {
                if (ch == cur)
                {
                    ++cnt;
                }
                else
                {
                    replace += cnt / 3;
                    cnt = 1;
                    cur = ch;
                }
            }
            replace += cnt / 3;
            return max(replace, 3 - categories);
        }
        else
        {
            
            int replace = 0, remove = n - 20;
            
            int rm2 = 0;
            int cnt = 0;
            char cur = '#';

            for (char ch : password)
            {
                if (ch == cur)
                {
                    ++cnt;
                }
                else
                {
                    if (remove > 0 && cnt >= 3)
                    {
                        if (cnt % 3 == 0)
                        {
                            --remove;
                            --replace;
                        }
                        else if (cnt % 3 == 1)
                        {
                            ++rm2;
                        }
                    }
                    replace += cnt / 3;
                    cnt = 1;
                    cur = ch;
                }
            }
            if (remove > 0 && cnt >= 3)
            {
                if (cnt % 3 == 0)
                {
                    --remove;
                    --replace;
                }
                else if (cnt % 3 == 1)
                {
                    ++rm2;
                }
            }
            replace += cnt / 3;

            int use2 = min({replace, rm2, remove / 2});
            replace -= use2;
            remove -= use2 * 2;
            int use3 = min({replace, remove / 3});
            replace -= use3;
            remove -= use3 * 3;
            return (n - 20) + max(replace, 3 - categories);
        }
    }

    char nextGreatestLetter(vector<char> &letters, char target)
    {
        auto resIt = upper_bound(letters.begin(), letters.end(), target);
        return resIt == letters.end() ? letters.front() : *resIt;
    }

    class NumArray
    {
    public:
        NumArray(vector<int> &nums)
        {
            size = nums.size();
            tree.resize(size + 1);
            rawData = move(nums);
            for (int i{}; i < size; ++i)
                update(i, rawData[i], true);
        }

        void update(int index, int val, bool init = false)
        {
            int delta = val - (init ? 0 : rawData[index]);
            auto it = index + 1;
            while (it < tree.size())
            {
                tree[it] += delta;
                it += lowBit(it);
            }
            rawData[index] = val;
        }

        int sumRange(int left, int right)
        {
            return getSum(right) - getSum(left - 1);
        }

    private:
        int lowBit(int x)
        {
            return x & -x;
        }
        int getSum(int it)
        {
            ++it;
            int res{};
            while (it)
            {
                res += tree[it];
                it -= lowBit(it);
            }
            return res;
        }
        size_t size;
        vector<int> tree;
        vector<int> rawData;
    };

    int countPrimeSetBits(int left, int right)
    {
        auto isPrime = [](int x)
        {
            return 1 << __builtin_popcount(x) & 0b10100010100010101100;
        };

        int res{};
        for (int x{left}; x <= right; ++x)
            if (isPrime(x))
                ++res;
        return res;
    }

    vector<int> findMinHeightTrees(int n, vector<vector<int>> &edges)
    {
        if (n == 1)
            return {0};
        vector<vector<int>> graph(n);
        vector<int> degree(n, 0);
        for (auto &edge : edges)
        {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
            ++degree[edge[0]];
            ++degree[edge[1]];
        }

        queue<int> que;
        for (int i{}; i < n; ++i)
        {
            if (degree[i] == 1)
                que.push(i);
        }

        int cnt{n};
        while (cnt > 2)
        {
            auto size = que.size();
            cnt -= size;

            for (int i{}; i < size; ++i)
            {
                int node = que.front();
                que.pop();
                for (auto child : graph[node])
                    if (--degree[child] == 1)
                        que.push(child);
            }
        }

        vector<int> res;
        while (!que.empty())
        {
            res.push_back(que.front());
            que.pop();
        }
        return res;
    }

    bool rotateString(string &s, const string &goal)
    {
        return s.size() == goal.size() && (s + s).find(goal) != string::npos;

        if (s.size() != goal.size())
            return false;
        hash<string> hashPrese{};
        auto strHas = hashPrese(goal);

        auto size = s.size();
        for (int i{}; i < size; ++i)
        {
            if (hashPrese(s) == strHas)
                return true;
            s.push_back(s.front());
            s.erase(0, 1);
        }
        return false;
    }

    vector<vector<int>> levelOrder(Node *root)
    {
        queue<Node *> que;
        que.push(root);
        vector<vector<int>> res;
        while (!que.empty())
        {
            auto size = que.size();
            vector<int> tmp(size);
            for (int i{}; i < size; ++i)
            {
                tmp[i] = que.front()->val;
                for (auto node : que.front()->children)
                    que.push(node);
                que.pop();
            }
            res.push_back(std::move(tmp));
        }
        return res;
    }

    bool reachingPoints(int sx, int sy, int tx, int ty)
    {
        while (tx > sx && ty > sy)
        {
            if (tx == ty)
                break;
            if (tx > ty)
                tx %= ty;
            else
                ty %= tx;
        }
        if (tx == sx && ty == sy)
            return true;
        if (tx == sx)
            return ty > sy && (ty - sy) % sx == 0;
        else if (ty == sy)
            return tx > sx && (tx - sx) % sy == 0;
        else
            return false;
    }

    int uniqueMorseRepresentations(vector<string> &words)
    {
        static array<string, 26> alphaTab{".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
        unordered_set<string> tab;
        for (auto &word : words)
        {
            string tmp;
            for (char ch : word)
                tmp += alphaTab[ch - 'a'];
            tab.insert(tmp);
        }
        return tab.size();
    }

    int countNumbersWithUniqueDigits(int n)
    {
        array<int, 9> tab{{1, 10, 91, 739, 5275, 32491, 168571, 712891, 2345851}};
        return tab[n];
    }

    vector<int> numberOfLines(vector<int> &widths, string s)
    {
        int res{};
        int cur{};
        for (char ch : s)
        {
            cur += widths[ch - 'a'];
            if (cur > 100)
            {
                ++res;
                cur = widths[ch - 'a'];
            }
        }
        ++res;
        return {res, cur};
    }

    class RandomizedSet
    {
    public:
        /** Initialize your data structure here. */
        RandomizedSet()
        {
        }

        /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
        bool insert(int val)
        {
            if (set.find(val) != set.end())
                return false;
            set.insert(val);
            return true;
        }

        /** Removes a value from the set. Returns true if the set contained the specified element. */
        bool remove(int val)
        {
            if (set.find(val) == set.end())
                return false;
            set.erase(val);
            return true;
        }

        /** Get a random element from the set. */
        int getRandom()
        {
            auto it = set.begin();
            advance(it, rand() % set.size());
            return *it;
        }

    private:
        unordered_set<int> set;
    };

    int maximumWealth(vector<vector<int>> &accounts)
    {
        int res{};
        for (auto &account : accounts)
            res = max(res, accumulate(account.begin(), account.end(), 0));
        return res;
    }

    NestedInteger deserialize(const string &s)
    {
        function<NestedInteger(int &)> bfs = [&](int &i) -> NestedInteger
        {
            if (s[i] == '[')
            {
                ++i;
                NestedInteger res;
                while (s[i] != ']')
                {
                    res.add(bfs(i));
                    if (s[i] == ',')
                        ++i;
                }
                ++i;
                return res;
            }
            else
            {
                int start{i};
                while (i < s.size() && s[i] != ',' && s[i] != ']')
                    ++i;
                return {stoi(s.substr(start, i - start))};
            }
        };

        int i{0};
        return bfs(i);
    }

    int largestPalindrome(int n)
    {
        if (n == 1)
            return 9;
        uint64_t halfPalindrome = pow(10, n) - 1;
        for (auto left = halfPalindrome; left > 0; --left)
        {
            string str = to_string(left);
            uint64_t palindrome = stoull(str + string(str.rbegin(), str.rend()));
            for (auto l = halfPalindrome; l * l >= palindrome; --l)
            {
                if (palindrome % l == 0)
                    return palindrome % 1337;
            }
        }
        return 0;
    }

    string mostCommonWord(string &paragraph, vector<string> &banned)
    {
        string dots = "!?',;.";
        for (auto &ch : paragraph)
        {
            if (dots.find(ch) != string::npos)
                ch = ' ';
            if (ch >= 'A' && ch <= 'Z')
                ch += 'a' - 'A';
        }
        stringstream ss(paragraph);
        unordered_set<string> ban(banned.begin(), banned.end());
        unordered_map<string, int> ans;
        for (string word; ss >> word;)
        {
            if (ban.find(word) == ban.end())
                ++ans[word];
        }
        int max{};
        string res;
        for (auto &p : ans)
        {
            if (p.second > max)
            {
                max = p.second;
                res = p.first;
            }
        }
        return res;
    }

    vector<int> lexicalOrder(int n)
    {
        vector<int> res;
        function<void(int)> dfs = [&](int num)
        {
            if (num > n)
                return;
            res.push_back(num);
            for (int i = 0; i < 10; ++i)
                dfs(num * 10 + i);
        };
        for (int i = 1; i < 10; ++i)
            dfs(i);
        return res;
    }

    vector<int> shortestToChar(string &s, char c)
    {
        vector<int> cIndex;
        for (int i{}; i < s.size(); ++i)
            if (s[i] == c)
                cIndex.push_back(i);
        vector<int> res(s.size(), INT_MAX);
        for (int i{}; i < s.size(); ++i)
        {
            for (auto &index : cIndex)
            {
                if (abs(index - i) < res[i])
                    res[i] = abs(index - i);
            }
        }
        return res;
    }

    int lengthLongestPath(string &input)
    {
        int res{};
        int cur{};
        stack<int> stk;
        auto size = input.size();
        ;

        for (int it{}; it < size;)
        {
            if (input[it] == '.')
            {
                ++cur;
                while (it < size && input[it] != '\n')
                {
                    ++it;
                    ++cur;
                }
                if (stk.empty())
                    res = max(res, cur);
                else
                    res = max(res, cur + stk.top());
            }
            else if (input[it] == '\n')
            {
                int level{};
                ++it;
                while (it < size && input[it] == '\t')
                {
                    ++it;
                    ++level;
                }

                if (stk.size() < level)
                    stk.push(cur + 1 + (stk.empty() ? 0 : stk.top()));
                else if (stk.size() > level)
                {
                    while (stk.size() > level)
                        stk.pop();
                }

                cur = 0;
            }
            else
            {
                ++cur;
                ++it;
            }
        }
        return res;
    }

    string toGoatLatin(string &sentence)
    {
        stringstream ss(sentence);
        string str;
        string res;
        int cnt{1};
        while (ss >> str)
        {
            switch (str[0])
            {
            case 'a':
            case 'A':
            case 'e':
            case 'E':
            case 'i':
            case 'I':
            case 'o':
            case 'O':
            case 'u':
            case 'U':
                break;
            default:
                str.push_back(str[0]);
                str.erase(str.begin());
            }
            str += "ma";
            for (int i{}; i < cnt; ++i)
                str += "a";
            res += str + " ";
            ++cnt;
        }
        return res.substr(0, res.size() - 1);
    }

    int maxRotateFunction(vector<int> &nums)
    {
        auto size = nums.size();
        int res{};
        int sum{};
        for (int i = 0; i < size; ++i)
        {
            res += i * nums[i];
            sum += nums[i];
        }

        int last{res};
        for (int i{1}; i < size; ++i)
        {
            last = last + sum - size * nums[size - i];
            res = max(res, last);
        }
        return res;
    }

    vector<vector<int>> outerTrees(vector<vector<int>> &trees)
    {
        if (trees.size() == 1)
            return trees;
        vector<vector<int>> res;
        using point = vector<int>;
        point p0 = trees[0];
        for (auto &tree : trees)
            if (tree[1] < p0[1])
                p0 = tree;

        for (auto &tree : trees)
        {
            tree[0] -= p0[0];
            tree[1] -= p0[1];
        }

        function cmp = [](point &p1, point &p2)
        {
            if (p1[0] == 0 && p1[1] == 0)
                return false;
            if (p2[0] == 0 && p2[1] == 0)
                return true;
            auto alpha1 = atan2(p1[1], p1[0]);
            auto alpha2 = atan2(p2[1], p2[0]);
            if (alpha1 > alpha2)
                return true;
            else if (fabs(alpha1 - alpha2) < 1e-6)
            {
                if (p1[0] * p1[0] + p1[1] * p1[1] > p2[0] * p2[0] + p2[1] * p2[1])
                    return true;
            }
            return false;
        };

        sort(trees.begin(), trees.end(), cmp);
        vector<point>::reverse_iterator rit;
        for (rit = trees.rend() - 1; rit >= trees.rbegin(); --rit)
        {
            auto vectorAngle0 = atan2(trees[0][1], trees[0][0]);
            auto &tree = *rit;
            auto vectorAngle1 = atan2(tree[1], tree[0]);
            if (fabs(vectorAngle0 - vectorAngle1) > 1e-6)
                break;
        }
        auto temp = vector<point>(rit + 1, trees.rend());
        for (int i{}; i < temp.size(); ++i)
            trees[i] = temp[i];

        res.push_back(trees.back());
        trees.pop_back();
        res.push_back(trees.back());
        trees.pop_back();

        while (!trees.empty())
        {
            double vectorAngle0, vectorAngle1;
            do
            {
                vectorAngle0 = atan2(res.back()[1] - (res.end() - 2)->at(1), res.back()[0] - (res.end() - 2)->at(0));
                vectorAngle1 = atan2(trees.back()[1] - res.back()[1], trees.back()[0] - res.back()[0]);
                vectorAngle0 = vectorAngle0 < 0 ? 2 * M_PI + vectorAngle0 : vectorAngle0;
                vectorAngle1 = vectorAngle1 < 0 ? 2 * M_PI + vectorAngle1 : vectorAngle1;
                if (vectorAngle0 > vectorAngle1)
                    res.pop_back();
            } while (vectorAngle0 > vectorAngle1);
            res.push_back(trees.back());
            trees.pop_back();
        }
        for (auto &tree : res)
        {
            tree[0] += p0[0];
            tree[1] += p0[1];
        }
        return res;
    }

    int binaryGap(int n)
    {
        int res{};
        int cur{};
        bool flag{};
        while (n)
        {
            if (n & 1)
            {
                if (flag)
                {
                    res = max(res, cur + 1);
                    cur = 0;
                }
                flag = true;
            }
            else
            {
                if (flag)
                    ++cur;
            }
            n >>= 1;
        }
        return res;
    }

    class RandomPickIndex
    {
    public:
        vector<int> &nums;
        RandomPickIndex(vector<int> &nums) : nums(nums)
        {
        }

        int pick(int target)
        {
            int res{};
            int cnt{};
            for (int i{}; i < nums.size(); ++i)
            {
                if (nums[i] == target)
                {
                    if (rand() % (++cnt) == 0)
                        res = i;
                }
            }
            return res;
        }
    };

    int projectionArea(vector<vector<int>> &grid)
    {
        int x{}, y{}, z{};
        for (int x = 0; x < grid.size(); ++x)
        {
            int y_max{};
            for (int y{}; y < grid[0].size(); ++y)
            {
                if (grid[x][y])
                    ++z;
                if (grid[x][y] > y_max)
                    y_max = grid[x][y];
            }
            y += y_max;
        }

        for (int y = 0; y < grid[0].size(); ++y)
        {
            int x_max{};
            for (int x{}; x < grid.size(); ++x)
            {
                if (grid[x][y] > x_max)
                    x_max = grid[x][y];
            }
            x += x_max;
        }
        return x + y + z;
    }

    vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights)
    {

        struct ArrayHash
        {
            size_t operator()(const array<int, 2> &a) const
            {
                size_t seed = (uint32_t)a[0];
                seed <<= 32;
                seed += (uint32_t)a[1];
                return seed;
            }
        };

        using point = array<int, 2>;
        unordered_set<point, ArrayHash> atlantic;
        unordered_set<point, ArrayHash> pacific;
        unordered_set<point, ArrayHash> *ocean;

        array<array<int, 2>, 4> directions{{{0, 1}, {0, -1}, {1, 0}, {-1, 0}}};

        function<void(int x, int y)> dfs = [&](int x, int y)
        {
            ocean->insert({x, y});

            for (auto [nx, ny] : directions)
            {
                nx += x;
                ny += y;
                if (nx < 0 || nx >= heights.size() || ny < 0 || ny >= heights[0].size() || ocean->count({nx, ny}) || heights[nx][ny] < heights[x][y])
                    continue;
                dfs(nx, ny);
            }
        };

        ocean = &atlantic;
        for (int y{}; y < heights[0].size(); ++y)
            dfs(0, y);
        for (int x{}; x < heights.size(); ++x)
            dfs(x, 0);
        ocean = &pacific;
        for (int y{}; y < heights[0].size(); ++y)
            dfs(heights.size() - 1, y);
        for (int x{}; x < heights.size(); ++x)
            dfs(x, heights[0].size() - 1);

        vector<vector<int>> res;
        for (int x{}; x < heights.size(); ++x)
            for (int y{}; y < heights[0].size(); ++y)
                if (atlantic.count({x, y}) && pacific.count({x, y}))
                    res.push_back({x, y});
        return res;
    }

    vector<int> sortArrayByParity(vector<int> &nums)
    {
        sort(nums.begin(), nums.end(), [](int l, int r)
             {
                if(!(l & 1) && r & 1)
                    return true;
                if (l & 1 && !(r & 1))
                    return false;
                return l < r; });
        return nums;
    }

    class Construct
    {
    public:
        class Node
        {
        public:
            bool val;
            bool isLeaf;
            Node *topLeft;
            Node *topRight;
            Node *bottomLeft;
            Node *bottomRight;

            Node()
            {
                val = false;
                isLeaf = false;
                topLeft = NULL;
                topRight = NULL;
                bottomLeft = NULL;
                bottomRight = NULL;
            }

            Node(bool _val, bool _isLeaf)
            {
                val = _val;
                isLeaf = _isLeaf;
                topLeft = NULL;
                topRight = NULL;
                bottomLeft = NULL;
                bottomRight = NULL;
            }

            Node(bool _val, bool _isLeaf, Node *_topLeft, Node *_topRight, Node *_bottomLeft, Node *_bottomRight)
            {
                val = _val;
                isLeaf = _isLeaf;
                topLeft = _topLeft;
                topRight = _topRight;
                bottomLeft = _bottomLeft;
                bottomRight = _bottomRight;
            }
        };

        Node *construct(vector<vector<int>> &grid)
        {
            if (grid.empty())
                return nullptr;
            int size = grid.size();
            vector<vector<int>> pre(size + 1, vector<int>(size + 1));
            for (int i{1}; i <= size; ++i)
                for (int j{1}; j <= size; ++j)
                    pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + grid[i - 1][j - 1];

            auto getSum = [&](int r0, int c0, int r1, int c1)
            {
                return pre[r1][c1] - pre[r1][c0] - pre[r0][c1] + pre[r0][c0];
            };

            function<Node *(int, int, int, int)> dfs = [&](int r0, int c0, int r1, int c1)
            {
                int total = getSum(r0, c0, r1, c1);
                if (total == 0)
                    return new Node(false, true);

                if (total == (r1 - r0) * (c1 - c0))
                    return new Node(true, true);

                return new Node(
                    true,
                    false,
                    dfs(r0, c0, (r0 + r1) / 2, (c0 + c1) / 2),
                    dfs(r0, (c0 + c1) / 2, (r0 + r1) / 2, c1),
                    dfs((r0 + r1) / 2, c0, r1, (c0 + c1) / 2),
                    dfs((r0 + r1) / 2, (c0 + c1) / 2, r1, c1));
            };
            return dfs(0, 0, size, size);
        }
    };

    int smallestRangeI(vector<int> &nums, int k)
    {
        int _min{nums[0]}, _max{nums[0]};
        for (int i{1}; i < nums.size(); ++i)
        {
            _min = min(_min, nums[i]);
            _max = max(_max, nums[i]);
        }
        if (_max - _min <= k * 2)
            return 0;
        return _max - _min - k * 2;
    }

    vector<int> getAllElements(TreeNode *root1, TreeNode *root2)
    {

        vector<int> v1, v2;
        vector<int> *p;
        function<void(TreeNode *)> dfs = [&](TreeNode *root)
        {
            if (!root)
                return;
            dfs(root->left);
            p->push_back(root->val);
            dfs(root->right);
        };
        p = &v1;
        dfs(root1);
        p = &v2;
        dfs(root2);

        vector<int> res;
        auto it1 = v1.begin();
        auto it2 = v2.begin();
        while (it1 != v1.end() && it2 != v2.end())
        {
            if (*it1 < *it2)
            {
                res.push_back(*it1);
                ++it1;
            }
            else
            {
                res.push_back(*it2);
                ++it2;
            }
        }
        while (it1 != v1.end())
        {
            res.push_back(*it1);
            ++it1;
        }
        while (it2 != v2.end())
        {
            res.push_back(*it2);
            ++it2;
        }
        return res;
    }

    vector<string> reorderLogFiles(vector<string> &logs)
    {
        stable_sort(logs.begin(), logs.end(), [&](const string &log1, const string &log2)
                    {
            int pos1 = log1.find_first_of(' ');
            int pos2 = log2.find_first_of(' ');
            bool isDigit1 = isdigit(log1[pos1 + 1]);
            bool isDigit2 = isdigit(log2[pos2 + 1]);
            if (isDigit1 && isDigit2)
            {
                return false;
            }
            if (!isDigit1 && !isDigit2)
            {
                string s1 = log1.substr(pos1);
                string s2 = log2.substr(pos2);
                if (s1 != s2)
                {
                    return s1 < s2;
                }
                return log1 < log2;
            }
            return isDigit1 ? false : true; });
        return logs;
    }

    int findTheWinner(int n, int k)
    {
        if (n == 1)
            return 1;
        return (k + findTheWinner(n - 1, k) - 1) % n + 1;
    }

    int numSubarrayProductLessThanK(vector<int> &nums, int k)
    {
        int res{0};
        int slipWindowsBegin{0};
        int slipWindowsEnd{0};
        int product{1};
        auto size = nums.size();
        while (slipWindowsEnd < size)
        {
            product *= nums[slipWindowsEnd];
            while (product >= k && slipWindowsBegin <= slipWindowsEnd)
            {
                product /= nums[slipWindowsBegin];
                ++slipWindowsBegin;
            }
            res += slipWindowsEnd - slipWindowsBegin + 1;
            ++slipWindowsEnd;
        }
        return res;
    }

    class MyQueue
    {
    public:
        MyQueue() = default;
        MyQueue(size_t size) : data_(size) {}

        void push(int x)
        {
            if (size_ == 0)
            {
                front_ = 0;
                tail_ = 0;
                size_ = 1;
                data_[0] = x;
                return;
            }
            if (size_ == data_.size())
            {
                data_.resize(size_ * 2);
                if (tail_ < front_)
                {
                    for (size_t i = tail_; i < size_; i++)
                    {
                        data_[i + size_] = data_[i];
                    }
                }
            }
            tail_ = (tail_ + 1) % data_.size();
            data_[tail_] = x;
            ++size_;
        }

        int pop()
        {
            if (size_ == 0)
            {
                throw runtime_error("empty queue");
            }
            int x = data_[front_];
            front_ = (front_ + 1) % data_.size();
            --size_;
            return x;
        }

        int front()
        {
            if (size_ == 0)
            {
                throw runtime_error("empty queue");
            }
            return data_[front_];
        }

        bool empty()
        {
            return size_ == 0;
        }

        int back()
        {
            if (size_ == 0)
            {
                throw runtime_error("empty queue");
            }
            return data_[tail_];
        }

        size_t size()
        {
            return size_;
        }

    private:
        vector<int> data_{vector<int>(3001)};
        int front_ = 0;
        int tail_ = 0;
        int size_ = 0;
    };

    class RecentCounter
    {
    public:
        MyQueue date;
        RecentCounter() = default;
        int ping(int t)
        {
            date.push(t);
            while (date.front() < t - 3000)
                date.pop();
            return date.size();
        }
    };

    vector<int> findDuplicates(vector<int> &nums)
    {
        unordered_set<int> res;
        unordered_set<int> s;
        for (int i : nums)
        {
            if (s.count(i))
                res.insert(i);
            else
                s.insert(i);
        }
        return {res.begin(), res.end()};
    }

    vector<int> diStringMatch(string &s)
    {
        vector<int> res(s.size() + 1);
        int min{0};
        int max = s.size();
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == 'I')
                res[i] = min++;
            else
                res[i] = max--;
        }
        if (s.back() == 'I')
            res.back() = min;
        else
            res.back() = max;
        return res;
    }

    class Codec
    {
    public:
        // Encodes a tree to a single string.
        string serialize(TreeNode *root)
        {
            if (root == nullptr)
                return "";
            string res = to_string(root->val);
            res += '[';
            res += serialize(root->left);
            res += ']';
            res += '[';
            res += serialize(root->right);
            res += ']';
            return res;
        }

        // Decodes your encoded data to tree.
        TreeNode *deserialize(string &data, int *pit = nullptr)
        {
            if (data.empty())
                return nullptr;
            if (!pit)
                pit = new int(0);
            auto &it = *pit;
            if (data[it] == ']')
                return nullptr;
            int pos = data.find('[', it);
            int val = stoi(data.substr(it, pos - it));
            auto node = new TreeNode(val);
            it = pos + 1;
            node->left = deserialize(data, pit);
            it += 2;
            node->right = deserialize(data, pit);
            ++it;
            return node;
        }
    };

    int minDeletionSize(vector<string> &strs)
    {
        auto cols = strs[0].size();
        auto rows = strs.size();
        int res{};
        for (int i{}; i < cols; ++i)
        {
            for (int j{1}; j < rows; ++j)
            {
                if (strs[j][i] < strs[j - 1][i])
                {
                    ++res;
                    break;
                }
            }
        }
        return res;
    }

    bool oneEditAway(string &first, string &second)
    {
        int delta = first.size() - second.size();
        if (abs(delta) > 1)
            return false;
        bool changed{false};
        for (size_t it1{}, it2{}; it1 < first.size() && it2 < second.size(); ++it1, ++it2)
        {
            if (first[it1] != second[it2])
            {
                if (changed)
                    return false;
                changed = true;
                if (delta > 0)
                {
                    ++it1;
                    if (first[it1] != second[it2])
                        return false;
                }
                else if (delta < 0)
                {
                    ++it2;
                    if (first[it1] != second[it2])
                        return false;
                }
            }
        }
        return true;
    }

    double largestTriangleArea(vector<vector<int>> &points)
    {
        double res{};
        for (size_t i{}; i < points.size(); ++i)
        {
            for (size_t j{i + 1}; j < points.size(); ++j)
            {
                for (size_t k{j + 1}; k < points.size(); ++k)
                {
                    res = max(res, 0.5 * abs(points[i][0] * points[j][1] + points[j][0] * points[k][1] + points[k][0] * points[i][1] - points[i][0] * points[k][1] - points[j][0] * points[i][1] - points[k][0] * points[j][1]));
                }
            }
        }
        return res;
    }

    TreeNode *inorderSuccessor(TreeNode *root, TreeNode *p)
    {
        if (!root)
            return nullptr;
        if (root->val <= p->val)
            return inorderSuccessor(root->right, p);
        else
        {
            auto left = inorderSuccessor(root->left, p);
            return left ? left : root;
        }
    }

    int minStickers(vector<string> &stickers, string target)
    {
        int m = target.size();
        vector<int> dp(1 << m, -1);
        dp[0] = 0;
        function<int(int)> helper = [&](int mask)
        {
            if (dp[mask] != -1)
            {
                return dp[mask];
            }
            dp[mask] = m + 1;
            for (auto &sticker : stickers)
            {
                int left = mask;
                vector<int> cnt(26);
                for (char &c : sticker)
                {
                    cnt[c - 'a']++;
                }
                for (int i = 0; i < m; i++)
                {
                    if ((mask >> i & 1) && cnt[target[i] - 'a'] > 0)
                    {
                        cnt[target[i] - 'a']--;
                        left ^= 1 << i;
                    }
                }
                if (left < mask)
                {
                    dp[mask] = min(dp[mask], helper(left) + 1);
                }
            }
            return dp[mask];
        };
        int res = helper((1 << m) - 1);
        return res > m ? -1 : res;
    }

    bool isAlienSorted(vector<string> &words, string order)
    {
        array<int, 26> pos;
        for (int i = 0; i < 26; ++i)
            pos[order[i] - 'a'] = i;
        for (int i = 0; i < words.size() - 1; ++i)
        {
            if (words[i] == words[i + 1])
                continue;
            int j;
            for (j = 0; j < min(words[i].size(), words[i + 1].size()); ++j)
            {
                if (words[i][j] != words[i + 1][j])
                {
                    if (pos[words[i][j] - 'a'] > pos[words[i + 1][j] - 'a'])
                        return false;
                    break;
                }
            }
            if (j == min(words[i].size(), words[i + 1].size()) && words[i].size() > words[i + 1].size())
                return false;
        }
        return true;
    }

    int minMoves2(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        int res{};
        int x = nums[nums.size() / 2];
        for (int i{}; i < nums.size(); ++i)
        {
            res += abs(nums[i] - x);
        }
        return res;
    }

    int repeatedNTimes(vector<int> &nums)
    {
        unordered_map<int, int> hashTab;
        auto n = nums.size() / 2;
        for (auto &num : nums)
            if (++hashTab[num] == n)
                return num;
        return -1;
    }

    vector<int> findRightInterval(vector<vector<int>> &intervals)
    {
        unordered_map<int, int> indexTab;
        for (int i = 0; i < intervals.size(); ++i)
            indexTab[intervals[i][0]] = i;
        sort(intervals.begin(), intervals.end(),[](const vector<int> &left, const vector<int> &right)
        {
            return left[0] < right[0];
        });
        vector<int> res(intervals.size());
        for (int i = 0; i < intervals.size(); ++i)
        {
            auto index = indexTab[intervals[i][0]];
            auto it = lower_bound(intervals.begin(), intervals.end(), intervals[i][1], [](const vector<int> &left, int right)
                                   { return left[0] < right; });
            if(it != intervals.end())
                res[index] = indexTab[it->front()];
            else
                res[index] = -1;
        }
        return res;
    }

    int findClosest(vector<string> &words, string &word1, string &word2)
    {
        int word1index{-1};
        int word2index{-1};
        int res{INT_MAX};
        for (int i = 0; i < words.size(); ++i)
        {
            if (words[i] == word1)
            {
                word1index = i;
                if (word2index != -1)
                {
                    res = min(res, abs(word1index - word2index));
                    if(res == 1)
                        return res;
                }
            }
            if (words[i] == word2)
            {
                word2index = i;
                if (word1index != -1)
                {
                    res = min(res, abs(word1index - word2index));
                    if(res == 1)
                        return res;
                }
            }
        }
        return res;
    }

    string removeOuterParentheses(string &s)
    {
        int st{};
        int firstLevalBacketIndex{};
        string res;
        for(int i = 0; i < s.size(); ++i)
        {
            if(s[i] == '(')
            {
                st++;
                if(st == 1)
                    firstLevalBacketIndex = i;
            }
            else
            {
                st--;
                if(st == 0)
                    res += s.substr(firstLevalBacketIndex + 1, i - firstLevalBacketIndex - 1);
            }
        }
        return res;
    }

    string validIPAddress(string & queryIP)
    {

        auto isIpv4 = std::regex("^((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][1-9]?|0)(\\.|$))(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][1-9]?|0)$");
        auto isIpv6 = std::regex("^(([0-9a-fA-F]{4,4})(:|$)){8}$");
        if(regex_match(queryIP, isIpv4))
            return "IPv4";
        if (regex_match(queryIP, isIpv6))
            return "IPv6";
        return "Neither";
    }

    int sumRootToLeaf(TreeNode *root)
    {
        int res{};
        function<void(TreeNode *, uint16_t)> dfs = [&](TreeNode *node, uint32_t sum)
        {
            if (!node)
                return;
            sum = sum * 2 + node->val;
            if (!node->left && !node->right)
                res += sum;
            dfs(node->left, sum);
            dfs(node->right, sum);
        };
        dfs(root, 0);
        return res;
    }

    bool makesquare(vector<int> &matchsticks)
    {
        int sum = accumulate(matchsticks.begin(), matchsticks.end(), 0);
        if (sum % 4)
            return false;
        int sideLen = sum / 4;
        int nums = matchsticks.size();
        vector<int> dp(1 << nums, -1);
        dp[0] = 0;
        for (int i{1}; i < (1 << nums); ++i)
        {
            for(int j{0}; j < nums; ++j)
            {
                int s1 = 1 << j;
                if (!(s1 & i))
                    continue;
                if (dp[i & ~s1] >= 0 && matchsticks[j] + dp[i & ~s1] <= sideLen)
                {
                    dp[i] = (matchsticks[j] + dp[i & ~s1]) % sideLen;
                    break;
                }            
            }
        }
        return dp[(1 << nums) - 1] == 0;
    }

    TreeNode *deleteNode(TreeNode *root, int key)
    {
        if (!root)
            return nullptr;
        if (root->val > key && root->left)
            root->left = deleteNode(root->left, key);
        else if (root->val < key && root->right)
            root->right = deleteNode(root->right, key);
        else if (root->val == key)
        {
            if (!root->left)
                return root->right;
            if (!root->right)
                return root->left;
            TreeNode *minNode = root->right;
            while (minNode->left)
                minNode = minNode->left;
            root->val = minNode->val;
            root->right = deleteNode(root->right, minNode->val);
        }
        return root;
    }

    class RandomPoinInCircle
    {
    public:
        class Solution
        {
        private:
            mt19937 gen{random_device{}()};
            uniform_real_distribution<double> dis;
            double xc, yc, r;

        public:
            Solution(double radius, double x_center, double y_center) : dis(-radius, radius), xc(x_center), yc(y_center), r(radius) {}

            vector<double> randPoint()
            {
                double x, y;
                do {
                    x = dis(gen);
                    y = dis(gen);
                } while (x * x + y * y > r * r);
                return {xc + x, yc + y};
            }
        };
    };

    int minEatingSpeed(vector<int> &piles, int h)
    {
        int l{1};
        int r{*max_element(piles.begin(), piles.end())};
        while (l < r)
        {
            int m = (l + r) / 2;
            int cnt{0};
            for (int pile : piles)
            {
                cnt += pile / m;
                if (pile % m)
                    cnt++;
            }
            if (cnt > h)
                l = m + 1;
            else
                r = m;
        }
        return l;
    }

    bool isBoomerang(vector<vector<int>> &points)
    {
        auto &point1 = points[0];
        auto &point2 = points[1];
        auto &point3 = points[2];
        point2[0] -= point1[0];
        point2[1] -= point1[1];
        point3[0] -= point1[0];
        point3[1] -= point1[1];
        point1[0] = point1[1] = 0;
        return point2[0] * point3[1] - point2[1] * point3[0] != 0;
    }

    class RandomPointInRectangles
    {
    public:
        class Solution {
        public:
            Solution(vector<vector<int>> &rects): rects(rects)
            {
                rectAreas.reserve(rects.size() + 1);
                rectAreas.push_back(0);
                for (auto &rect : rects)
                    rectAreas.push_back((rect[2] - rect[0]) * (rect[3] - rect[1]) + rectAreas.back());
                
                dis = new uniform_int_distribution<int>(0, rectAreas.back());
            }

            vector<int> pick()
            {
                auto area = dis->operator()(gen);
                int index = lower_bound(rectAreas.begin(), rectAreas.end(), area) - rectAreas.begin();
                if (index == 0)
                    index = 1;
                area = rectAreas[index] - area;
                if(area == 0)
                    return {rects[index - 1][0], rects[index - 1][1]};
                auto &rect = rects[index - 1];
                auto x = rect[0] + area / (rect[3] - rect[1]);
                auto y = rect[1] + area % (rect[3] - rect[1]);
                return {x, y};
            }

        private:
            vector<vector<int>> &rects;
            vector<int> rectAreas;
            mt19937 gen{random_device{}()};
            uniform_int_distribution<int> *dis;
        };
    };

    int minFlipsMonoIncr(string &s)
    {
        int res{};
        int zeroCnt{};
        int oneCnt{};
        for (char c : s)
        {
            if (c == '0' && oneCnt > 0)
                ++zeroCnt;
            else if(c == '1')
                ++oneCnt;
                

            if(oneCnt > 0 && zeroCnt > oneCnt)
            {
                res += oneCnt;
                zeroCnt = 0;
                oneCnt = 0;
            }
        }
        return res + zeroCnt;
    }

    vector<string> findAndReplacePattern(vector<string> &words, string &pattern)
    {
        vector<string> res;
        auto size = pattern.size();
        for(auto &word : words)
        {
            if(word.size() != size)
                continue;
            if (size == 1)
            {
                res.push_back(word);
                continue;
            }
            int wIter{0};
            int pIter{0};
            unordered_map<char, char> map;
            unordered_map<char, char> map2;
            while (wIter < size)
            {
                if (map.find(word[wIter]) == map.end())
                {
                    if(map2.find(pattern[pIter]) != map2.end())
                        break;
                    map[word[wIter]] = pattern[pIter];
                    map2[pattern[pIter]] = word[wIter];
                }
                else if (map[word[wIter]] != pattern[pIter])
                    break;
                ++pIter;
                ++wIter;
            }
            if (wIter == size)
                res.push_back(word);
        }
        return res;
    }

    vector<int> findDiagonalOrder(vector<vector<int>> &mat)
    {
        vector<int> res;
        res.reserve(mat.size() * mat[0].size());
        int width = mat[0].size();
        int height = mat.size();
        for (int i{}; i < width + height - 1; ++i)
        {
            if (i & 1)
            {
                int x = i < width ? 0 : i - width + 1;
                int y = i < width ? 1 : width - 1;
                while (x < height && y >= 0)
                    res.emplace_back(mat[x++][y--]);
            }
            else
            {
                int x = i < height ? i : height - 1;
                int y = i < height ? 0 : i - height + 1;
                while (x >= 0 && y < width)
                    res.emplace_back(mat[x--][y++]);
            }
        }
        return res;
    }

    int findPairs(vector<int> &nums, int k)
    {
        unordered_set<int> traversed;
        unordered_set<int> res;
        for (auto num : nums)
        {
            if (traversed.count(num - k))
                res.insert(num - k);
            if (traversed.count(num + k))
                res.insert(num);
            traversed.insert(num);
        }
        return res.size();
    }

    void duplicateZeros(vector<int> &arr)
    {
        auto size = arr.size();
        auto topIt = arr.begin();
        size_t top{0};
        while (topIt <= arr.end() && top < size)
        {
            top += *topIt == 0 ? 2 : 1;
            ++topIt;
        }
        if(topIt == arr.end())
            return;
        --topIt;

        auto end = arr.end() - 1;
        if (top > size && *topIt == 0)
        {
            *end-- = 0;
            --topIt;
        }
        while (topIt >= arr.begin())
        {
            if (*topIt == 0)
            {
                *end-- = 0;
                *end-- = 0;
            }
            else
                *end-- = *topIt;
            --topIt;
        }
    }

    Node *insert(Node *head, int insertVal)
    {
        if (head == nullptr)
        {
            auto tmp = new Node(insertVal);
            tmp->next = tmp;
            return tmp;
        }

        auto it = head->next;
        while (it != head)
        {
            if ((it->val <= insertVal && (it->next->val >= insertVal || it->val > it->next->val)) || (it->val > it->next->val && it->next->val > insertVal))
            {
                auto tmp = new Node(insertVal);
                tmp->next = it->next;
                it->next = tmp;
                return head;
            }
            it = it->next;
        }
        auto tmp = new Node(insertVal);
        tmp->next = head->next;
        head->next = tmp;
        return head;
    }
    vector<int> findFrequentTreeSum(TreeNode *root)
    {
        unordered_map<int, int> m;
        function<int(TreeNode *)> dfs = [&](TreeNode *root)
        {
            if (root == nullptr)
                return 0;
            int sum = root->val + dfs(root->left) + dfs(root->right);
            ++m[sum];
            return sum;
        };
        dfs(root);
        vector<int> res;
        int max{};
        for (auto &[key, value] : m)
        {
            if (value > max)
            {
                max = value;
                res.clear();
                res.emplace_back(key);
            }
            else if (value == max)
                res.emplace_back(key);
        }
        return res;
    }

    int minCost(vector<vector<int>> &costs)
    {
        array<vector<int>, 3> dp{vector<int>(costs.size()), vector<int>(costs.size()), vector<int>(costs.size())};
        dp[0][0] = costs[0][0];
        dp[1][0] = costs[0][1];
        dp[2][0] = costs[0][2];

        for (size_t i{1}; i < costs.size(); ++i)
        {
            dp[0][i] = min(dp[1][i - 1], dp[2][i - 1]) + costs[i][0];
            dp[1][i] = min(dp[0][i - 1], dp[2][i - 1]) + costs[i][1];
            dp[2][i] = min(dp[0][i - 1], dp[1][i - 1]) + costs[i][2];
        }

        return min({dp[0].back(), dp[1].back(), dp[2].back()});
    }

    class RandInBlacklist
    {
    public:
        class Solution
        {
            int m_nums;
            unordered_map<int, int> m_blacklistMap;

        public:
            Solution(int n, vector<int> &blacklist) : m_nums(n - blacklist.size())
            {
                unordered_set<int> black;
                for (auto i : blacklist)
                    if (i >= m_nums)
                        black.insert(i);

                auto it = m_nums - 1;
                for (auto i : blacklist)
                {
                    if (i < m_nums)
                    {
                        while (black.count(++it)){}
                        m_blacklistMap[i] = it;
                    }
                }
            }
            int pick()
            {
                int res = rand() % m_nums;
                return (m_blacklistMap.count(res) ? m_blacklistMap[res] : res);
            }
        };
    };

    int minRefuelStops(int target, int startFuel, vector<vector<int>> &stations)
    {
        int carPos{0};
        int cnt{0};
        std::priority_queue<int, vector<int>, std::less<int>> q;
        auto stationIt = stations.begin();
        while (carPos < target) {
            if (target - carPos <= startFuel)
                return cnt;
            if (stationIt == stations.end())
            {
                while (!q.empty() && target - carPos > startFuel)
                {
                    startFuel += q.top();
                    ++cnt;
                    q.pop();
                }
                if (target - carPos > startFuel)
                    return -1;
                else
                    return cnt;
            }

            if ((*stationIt)[0] - carPos > startFuel)
            {
                while (!q.empty() && (*stationIt)[0] - carPos > startFuel)
                {
                    startFuel += q.top();
                    ++cnt;
                    q.pop();
                }
                if ((*stationIt)[0] - carPos > startFuel)
                    return -1;
            }
            startFuel -= (*stationIt)[0] - carPos;
            carPos = (*stationIt)[0];
            q.push((*stationIt)[1]);
            ++stationIt;
        }
        return -1;

    }

    int nextGreaterElement(int n)
    {
        // auto s = to_string(n);
        // return !next_permutation(s.begin(), s.end()) || stol(s) > INT_MAX ? -1 : stoi(s);
    }

    class MyCalendar
    {
        set<pair<int,int>> books;
    public:
        MyCalendar() = default;

        bool book(int start, int end)
        {
            auto it = books.lower_bound({end, 0});
            if (it == books.begin() || (--it)->second <= start)
            {
                books.emplace(start, end);
                return true;
            }
            return false;
        }
    };

    int minCostToMoveChips(vector<int> &position)
    {
        int odd{};
        int even{};
        for (int i : position)
            if (i & 1)
                ++odd;
            else
                ++even;

        return min(odd,even);
    }

    class MagicDictionary
    {
        class DictTree
        {
        public:
            char ch{};
            bool isEnd{};
            unordered_map<char, DictTree*> next;
        };
        DictTree root;

    public:
        MagicDictionary() = default;

        void buildDict(vector<string> &dictionary)
        {
            for (auto &word : dictionary)
            {
                auto pnode = &root;
                for (char ch : word)
                {
                    if (pnode->next.count(ch) == 0)
                        pnode->next[ch] = new DictTree;
                    pnode = pnode->next[ch];
                }
                pnode->isEnd = true;
            }

        }

        bool search(string &searchWord)
        {
            function<bool(DictTree *, int, bool)> dfs = [&](DictTree *node, int index, bool modified)
            {
                if (index == searchWord.size())
                    return modified && node->isEnd;
                if (node->next.count(searchWord[index]))
                    if (dfs(node->next[searchWord[index]], index + 1, modified))
                        return true;
                if (modified)
                    return false;
                for (auto &[ch, nextNode] : node->next)
                    if (searchWord[index] != ch && dfs(nextNode, index + 1, true))
                        return true;
                return false;
            };

            return dfs(&root, 0, false);
        }
    };

    int oddCells(int m, int n, vector<vector<int>> &indices)
    {
        unordered_map<int, int> cols;
        unordered_map<int, int> rows;

        for (auto &p : indices)
        {
            ++rows[p[0]];
            ++cols[p[1]];
        }

        int oddCols{}, oddRows{};
        for (auto &[col, cnt] : cols)
            if (cnt & 1)
                ++oddCols;

        for (auto &[col, cnt] : rows)
            if (cnt & 1)
                ++oddRows;

        return oddRows * (n - oddCols) + oddCols * (m - oddRows);
    }

    vector<int> asteroidCollision(vector<int> &asteroids)
    {
        vector<int> st;
        vector<int> res;
        for (int aster : asteroids)
        {
            if (aster > 0)
            {
                st.emplace_back(aster);
                continue;
            }

            if (st.empty())
            {
                res.emplace_back(aster);
                continue;
            }

            while (!st.empty() && st.back() < aster)
                st.pop_back();

            if (st.empty())
            {
                res.emplace_back(aster);
                continue;
            }

            if (st.back() == -aster)
            {
                st.pop_back();
                continue;
            }
        }

        res.insert(res.end(), st.begin(), st.end());
        return res;
    }

    class WordFilter
    {
        vector<string> &m_words;
    public:
        WordFilter(vector<string> &words):m_words(words)
        {
        }

        int f(const string &pref, const string &&suff)
        {
            std::regex reg{pref + ".*+" + suff};
            for (int i = m_words.size() - 1; i > 0; --i)
                if (regex_match(m_words[i], reg))
                    return i;
            return -1;
        }
    };

    class logicalORofQuardTree
    {
        // Definition for a QuadTree node.
        class Node
        {
        public:
            bool val;
            bool isLeaf;
            Node *topLeft;
            Node *topRight;
            Node *bottomLeft;
            Node *bottomRight;

            Node()
            {
                val = false;
                isLeaf = false;
                topLeft = NULL;
                topRight = NULL;
                bottomLeft = NULL;
                bottomRight = NULL;
            }

            Node(bool _val, bool _isLeaf)
            {
                val = _val;
                isLeaf = _isLeaf;
                topLeft = NULL;
                topRight = NULL;
                bottomLeft = NULL;
                bottomRight = NULL;
            }

            Node(bool _val, bool _isLeaf, Node *_topLeft, Node *_topRight, Node *_bottomLeft, Node *_bottomRight)
            {
                val = _val;
                isLeaf = _isLeaf;
                topLeft = _topLeft;
                topRight = _topRight;
                bottomLeft = _bottomLeft;
                bottomRight = _bottomRight;
            }
        };

        Node *intersect(Node *quadTree1, Node *quadTree2)
        {
            if (quadTree1->isLeaf)
            {
                if (quadTree1->val)
                    return quadTree1;
                else
                    return quadTree2;
            }

            if (quadTree2->isLeaf)
            {
                if (quadTree2->val)
                    return quadTree2;
                else
                    return quadTree1;
            }

            auto res{new Node};
            res->topLeft = intersect(quadTree1->topLeft, quadTree2->topLeft);
            res->topRight = intersect(quadTree1->topRight, quadTree2->topRight);
            res->bottomLeft = intersect(quadTree1->bottomLeft, quadTree2->bottomLeft);
            res->bottomRight = intersect(quadTree1->bottomRight, quadTree2->bottomRight);

            if (res->topLeft->isLeaf && res->topRight->isLeaf && res->bottomLeft->isLeaf && res->bottomRight->isLeaf && (res->bottomLeft->val == res->topLeft->val && res->topRight->val == res->topLeft->val && res->topRight->val == res->bottomRight->val))
            {
                res = new Node(res->topLeft->val, true);
            }

            return res;
        }
    };

    int arrayNesting(vector<int> &nums)
    {
        vector<unordered_set<int>> circles;

        int res{0};
        for (auto it{nums.begin()}; it < nums.end(); ++it)
        {
            if (*it == -1)
                continue;
            auto it2 = nums[*it];
            auto iit = *it;
            nums[*it] = -1;
            int circleCnt{1};
            while (it2 != iit)
            {
                ++circleCnt;
                int tmp = it2;
                it2 = nums[it2];
                nums[tmp] = -1;
            }
            res = max(res, circleCnt);
        }
        return res;
    }

    vector<vector<int>> shiftGrid(vector<vector<int>> &grid, int k)
    {
        if (k == 0)
            return grid;
        int tmp = grid.back().back();
        auto m{grid.size()};
        auto n{grid.back().size()};
        std::pair<size_t, size_t> point;

        for (int x = m - 1; x >= 0; --x)
        {
            for (int y = n - 1; y >= 0; --y)
            {
                if (y == n - 1)
                {
                    if (x == m - 1)
                        continue;
                    grid[x + 1][0] = grid[x][y];
                }
                else
                    grid[x][y + 1] = grid[x][y];
            }
        }

        grid[0][0] = tmp;

        return shiftGrid(grid, k - 1);
    }

    TreeNode *pruneTree(TreeNode *root)
    {
        function<bool(TreeNode *)> dfs = [&](TreeNode *node)
        {
            if (node == nullptr)
                return false;
            auto leftRes = dfs(node->left);
            auto rightRes = dfs(node->right);

            if (!leftRes)
                node->left = nullptr;
            if (!rightRes)
                node->right = nullptr;

            if (!leftRes && !rightRes && !node->val)
                return false;
            else
                return true;
        };

        if (!dfs(root))
            root = nullptr;
        return root;
    }

    int distanceBetweenBusStops(vector<int> &distance, int start, int destination)
    {
        int res{0};
        for (int i{start}; i != destination; i = (i + 1 == distance.size() ? 0 : i + 1))
        {
            res += distance[i];
        }

        int tmp{0};
        for (int i{destination}; i != start; i = (i + 1 == distance.size() ? 0 : i + 1))
        {
            tmp += distance[i];
            if (tmp > res)
                break;
        }
        return min(res, tmp);
    }

    class CBTInserter
    {
        vector<TreeNode *> binaryHeap;

    public:
        CBTInserter(TreeNode *root)
        {
            queue<TreeNode *> q;
            q.push(root);
            while (!q.empty())
            {
                auto node = q.front();
                q.pop();
                binaryHeap.emplace_back(node);
                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }
        }

        int insert(int val)
        {
            auto node = new TreeNode(val);
            binaryHeap.emplace_back(node);
            auto fatherIndex = (binaryHeap.size() / 2) - 1;
            bool isRight = binaryHeap.size() & 1;
            if (isRight)
                binaryHeap[fatherIndex]->right = node;
            else
                binaryHeap[fatherIndex]->left = node;
            return binaryHeap[fatherIndex]->val;
        }

        TreeNode *get_root()
        {
            return binaryHeap.front();
        }
    };

    class Skiplist
    {
    public:
        static inline const int MAX_LEVEL = 16;
        struct Node
        {
            int val;
            vector<Node *> forward;
            Node(int _val, int _maxLevel = MAX_LEVEL) : val(_val), forward(_maxLevel, nullptr) {}
        };

    private:
        Node *head;
        int level;
        mt19937 gen{random_device{}()};
        uniform_real_distribution<double> dis;

    public:
        Skiplist() : head(new Node(-1)), level(0), dis(0, 1) {}

        int randomLevel()
        {
            int lv = 1;
            while (dis(gen) < 0.25 && lv < MAX_LEVEL)
                lv++;
            return lv;
        }

        Node *lower_bound(int target, vector<Node *> *update = nullptr)
        {
            auto it = head;
            for (int i{level - 1}; i >= 0; --i)
            {
                while (it->forward[i] && it->forward[i]->val < target)
                    it = it->forward[i];
                if (update)
                    update->at(i) = it;
            }
            return it;
        }
        bool search(int target)
        {
            auto it = lower_bound(target);

            it = it->forward[0];
            if (it && it->val == target)
                return true;
            return false;
        }

        void add(int num)
        {
            vector<Node *> update(MAX_LEVEL, head);

            auto it = lower_bound(num, &update);

            int lv = randomLevel();
            level = max(level, lv);
            auto newNode = new Node(num, lv);
            for (int i{}; i < lv; ++i)
            {
                newNode->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = newNode;
            }
        }

        bool erase(int num)
        {
            vector<Node *> update(MAX_LEVEL, nullptr);

            auto it = lower_bound(num, &update);

            it = it->forward[0];
            if (!it || it->val != num)
                return false;
            for (int i{}; i < level; ++i)
            {
                if (update[i]->forward[i] != it)
                    break;
                update[i]->forward[i] = it->forward[i];
            }
            delete it;

            while (level > 1 && head->forward[level - 1] == nullptr)
                --level;

            return true;
        }
    };

    string fractionAddition(string expression)
    {
        auto it = expression.begin();
        int64_t numeratorSum{1}, denominatorSum{0};
        while (it < expression.end())
        {
            int denominator{0}, sign{1};
            switch (*it)
            {
            case '-':
                sign = -1;
            case '+':
                ++it;
                break;
            default:
                break;
            }
            while (it < expression.end() && isdigit(*it))
            {
                denominator *= 10;
                denominator += *it - '0';
                ++it;
            }

            denominator *= sign;

            ++it;
            int numerator{0};
            while (it < expression.end() && isdigit(*it))
            {
                numerator *= 10;
                numerator += *it - '0';
                ++it;
            }

            denominatorSum = denominatorSum * (int64_t)numerator + (int64_t)denominator * numeratorSum;
            numeratorSum = numeratorSum * numerator;
        }
        if (denominatorSum == 0)
            return "0/1";
        auto g = gcd(abs(numeratorSum), denominatorSum);
        return to_string(denominatorSum / g) + "/" + to_string(numeratorSum / g);
    }

    vector<int> arrayRankTransform(vector<int> &arr)
    {
        map<int, vector<int>> m;
        for (int i{}; i < arr.size(); ++i)
            m[arr[i]].emplace_back(i);
        int rank{1};
        for (auto &[val, indexs] : m)
        {
            for (auto &index : indexs)
                arr[index] = rank;
            ++rank;
        }
        return arr;
    }

    bool validSquare(vector<int> &p1, vector<int> &p2, vector<int> &p3, vector<int> &p4)
    {
        using point = std::pair<int,int>;
        auto isRightAng = [](point first, point mid, point last)
        {
            auto vec1 = point{first.first - mid.first, first.second - mid.second};
            auto vec2 = point{last.first - mid.first, last.second - mid.second};
            return vec1.first * vec2.first + vec1.second * vec2.second == 0 &&
                   vec1.first * vec1.first + vec1.second * vec1.second == vec2.first * vec2.first + vec2.second * vec2.second;
        };

        auto v2p = [](vector<int> v)
        {
            return point{v[0], v[1]};
        };

        if (isRightAng(v2p(p1),v2p(p2),v2p(p3)))
            return isRightAng(v2p(p1), v2p(p4), v2p(p3));
        if (isRightAng(v2p(p2), v2p(p1), v2p(p3)))
            return isRightAng(v2p(p2), v2p(p4), v2p(p3));
        if (isRightAng(v2p(p1), v2p(p3), v2p(p2)))
            return isRightAng(v2p(p1), v2p(p4), v2p(p2));
        return false;
    }

    int maxLevelSum(TreeNode *root)
    {
        int res{INT_MIN};
        int resIndex{0};
        queue<TreeNode *> q;
        q.push(root);
        for(int index{1}; !q.empty(); ++index)
        {
            int sum{};
            queue<TreeNode*> next_q;
            while (!q.empty())
            {
                auto node = q.front();
                q.pop();
                sum += node->val;
                if (node->left)
                    next_q.push(node->left);
                if (node->right)
                    next_q.push(node->right);
            }
            q.swap(next_q);
            if (sum > res)
            {
                res = sum;
                resIndex = index;
            }
        }
        return resIndex;
    }

    vector<string> stringMatching(vector<string> &words)
    {
        vector<string> res;
        for (int i{}; i < words.size(); ++i)
        {
            
            for (int j = 0; j < words.size(); ++j)
            {
                if (j == i)
                    continue;
                if (words[j].find(words[i]) != string::npos)
                {
                    res.emplace_back(std::move(words[i]));
                    break;
                }
            }
        }
        return res;
    }

    vector<int> exclusiveTime(int n, vector<string> &strLogs)
    {
        struct Log
        {
            int func;
            bool isStart;
            int timestamp;
            Log(const string &str)
            {
                char buf[8];
                sscanf(str.c_str(), "%d:%[^:]:%d", &func, buf, &timestamp);
                isStart = (strcmp("start", buf) ? false : true);
            }
        };
        vector<int> res(n, 0);
        vector<Log> logs(strLogs.begin(), strLogs.end());
        stack<int> st;
        for (auto it{logs.begin()}; it < logs.end(); ++it)
        {
            if (it->isStart)
            {
                if (st.empty())
                {
                    st.emplace(it->func);
                    continue;
                }
                res[st.top()] += it->timestamp - (it - 1)->timestamp - ((it - 1)->isStart ? 0 : 1);
                st.emplace(it->func);
            }
            else
            {
                res[st.top()] += it->timestamp - (it - 1)->timestamp + ((it - 1)->isStart ? 1 : 0);
                st.pop();
            }
        }
        return res;
    }

    string generateTheString(int n)
    {
        string res(n, 'a');
        if (!(n & 1))
            res.back() = 'b';
        return res;
    }

    class MyCircularQueue
    {
        vector<int> m_data;
        size_t m_size{0};
        size_t m_head{0};
        size_t m_tail{0};
    public:
        MyCircularQueue(int k):m_data(k){}

        bool enQueue(int value)
        {
            if (isFull())
                return false;
            m_data[m_tail++] = value;
            if (m_tail == m_data.size())
                m_tail = 0;
            ++m_size;
            return true;
        }

        bool deQueue()
        {
            if (isEmpty())
                return false;
            ++m_head;
            if (m_head == m_data.size())
                m_head = 0;
            --m_size;
            return true;
        }

        int Front()
        {
            return isEmpty() ? -1 : m_data[m_head];
        }

        int Rear()
        {
            return isEmpty() ? -1 : (m_tail == 0 ? m_data.back() : m_data[m_tail - 1]);
        }

        bool isEmpty()
        {
            return m_size == 0;
        }

        bool isFull()
        {
            return m_size == m_data.size();
        }
    };

    string orderlyQueue(string s, int k)
    {
        if (k == 1)
        {
            s += s;
            string_view sv{s}, ans{sv};
            for (size_t i{}, n{s.size()/2}; i < n; ++i)
                ans = min(ans, sv.substr(i, n));
            return {ans.cbegin(), ans.cend()};
        }
        else
        {
            sort(s.begin(), s.end());
            return s;
        }
    }

    vector<int> minSubsequence(vector<int> &nums)
    {
        auto sum = accumulate(nums.begin(), nums.end(), 0);
        sort(nums.begin(), nums.end(),std::greater<>());
        int resSum{};
        int it;
        for (it = 0 ; it < nums.size() && resSum <= sum / 2; ++it)
        {
            resSum += nums[it];
        }

        return {nums.begin(), nums.begin() + it};
    }

    TreeNode *addOneRow(TreeNode *root, int val, int depth)
    {
        if (depth == 1)
            return new TreeNode(val, root, nullptr);

        vector<TreeNode *> layer[2];
        layer[0].emplace_back(root);
        for (int i{}; i < depth - 1; ++i)
        {
            for (auto &it : layer[0])
            {
                if (it->left)
                    layer[1].emplace_back(it->left);
                if (it->right)
                    layer[1].emplace_back(it->right);
            }
            layer[0].swap(layer[1]);
            layer[1].clear();
        }
        for (auto &it : layer[1])
        {
            it->left = new TreeNode(val, it->left, nullptr);
            it->right = new TreeNode(val, nullptr, it->right);
        }
        return root;
    }


    template<class Ty>
    string makeLargestSpecial(Ty &&s)
    {
        if (s.size() <= 2)
            return s;
        vector<string> subString;
        int cnt{};
        auto left{s.begin()};
        for (auto it{s.begin()}; it < s.end(); ++it)
        {
            if (*it == '1')
                ++cnt;
            else
            {
                --cnt;
                if (cnt == 0)
                {
                    subString.emplace_back("1" + makeLargestSpecial(string(left + 1, it - 1)) + "0");
                    left = it + 1;
                }
            }
        }
        sort(subString.begin(), subString.end(), greater<string>{});
        string res = accumulate(subString.begin(), subString.end(), ""s);
        return res;
    }

    int minStartValue(vector<int> &nums)
    {
        int minimum{INT_MAX};
        int64_t sum{};
        for (auto &it : nums)
        {
            sum += it;
            if (sum < minimum)
                minimum = sum;
        }
        return minimum > -1 ? 1 : -minimum + 1;
    }

    string solveEquation(string equation)
    {
        auto getNum = [&equation](string::iterator &it)
        {
            int res{0};
            while (it < equation.end() && *it >= '0' && *it <= '9')
            {
                res *= 10;
                res += *it++ - '0';
            }
            return res;
        };
        
        int x{0}, c{0};
        int sign1{1}, sign2{1};
        for (auto it{equation.begin()}; it < equation.end();)
        {
            if (*it >= '0' && *it <= '9')
            {
                auto num = getNum(it) * sign1 * sign2;
                if (it == equation.end() || *it != 'x')
                    c += num;
                else if (*it == 'x')
                {
                    x += num;
                    ++it;
                }
            }
            else
            {
                switch (*it)
                {
                case '+':
                    sign1 = 1;
                    break;
                case '-':
                    sign1 = -1;
                    break;
                case '=':
                    sign1 = 1;
                    sign2 = -1;
                    break;
                case 'x':
                    x += sign1 * sign2;
                    break;
                default:
                    throw std::runtime_error((string("unexpect char: ") + *it).c_str());
                }
                ++it;
            }
        }
        if (x == 0 && c == 0)
            return "Infinite solutions";
        if (x != 0 && c == 0)
            return "x=0";
        if (x == 0 && c != 0)
            return "No solution";
        if (x != 0 && c != 0)
            return "x=" + to_string(-c / x);
        return "";
    }

    string reformat(string s)
    {
        vector<char> nums, chars;
        for (auto &ch : s)
        {
            if (ch >= '0' && ch <= '9')
                nums.emplace_back(ch);
            else
                chars.emplace_back(ch);
        }
        if (abs((int64_t)nums.size() - (int64_t)chars.size()) > 1)
            return {};

        string res;
        res.reserve(nums.size() + chars.size());
        if (chars.size() > nums.size())
            swap(chars, nums);
        while(!nums.empty() || !chars.empty())
        {
            if (!nums.empty())
            {
                res.push_back(nums.back());
                nums.pop_back();
            }
            if (!chars.empty())
            {
                res.push_back(chars.back());
                chars.pop_back();
            }
        }
        return res;
    }

    vector<vector<int>> groupThePeople(vector<int> &groupSizes)
    {
        unordered_map<int, vector<int>> m;
        for (int i{}; i < groupSizes.size(); ++i)
            m[groupSizes[i]].emplace_back(i);
        vector<vector<int>> res;
        for (auto &pair : m)
        {
            auto v{std::move(pair.second)};
            for (auto it{v.begin()}; it < v.end(); it += pair.first)
                res.emplace_back(it, it + pair.first);
        }
        return res;
    }

    int maxScore(string &s)
    {
        int oneNums = std::count(s.begin(), s.end(), '1');
        int score{oneNums};
        int maxScore{score - 1};
        for (auto it{s.begin()}; it < s.end() - 1; ++it)
        {
            auto &ch = *it;
            if (ch == '0')
            {
                ++score;
                if (score > maxScore)
                    maxScore = score;
            }
            else
                --score;
        }
        return maxScore;
    }

    int maxProduct(vector<int> &nums)
    {
        int max{}, secondMax{};
        for (auto &it : nums)
        {
            if (it > max)
            {
                secondMax = max;
                max = it;
            }
            else if (it > secondMax)
                secondMax = it;
        }
        return (max -  1) * (secondMax - 1);
    }

    int widthOfBinaryTree(TreeNode *root)
    {
        if (!root)
            return 0;
        vector<pair<TreeNode *, uint64_t>> q;
        q.emplace_back(root, 0);
        uint64_t max{0};
        while (!q.empty())
        {
            uint64_t left{q.front().second};
            uint64_t right{left};
            auto tempQ{decltype(q)()};
            for (auto &[node, pos] : q)
            {
                if (node->left)
                    tempQ.emplace_back(node->left, pos * 2);
                if (node->right)
                    tempQ.emplace_back(node->right, pos * 2 + 1);
                if (pos > right)
                    right = pos;
            }
            q.swap(tempQ);
            if (right - left > max)
                max = right - left;
        }
        return max + 1;
    }

    int preimageSizeFZF(int k)
    {
        int64_t left{0}, right{5 * static_cast<int64_t>(k + 1)};
        while (right >= left)
        {
            auto mid{(left + right) / 2};
            auto count = trailingZeroes(mid);
            if (count < k)
                left = mid + 1;
            else
                right = mid - 1;
        }
        if (trailingZeroes(right + 1) != k)
            return 0;
        auto L = right;
        ++k;
        left = 0;
        right = 5 * static_cast<int64_t>(k + 1);
        while (right >= left)
        {
            auto mid{(left + right) / 2};
            auto count = trailingZeroes(mid);
            if (count < k)
                left = mid + 1;
            else
                right = mid - 1;
        }
        auto R = right;
        return R - L;
    }

    class MyCircularDeque
    {
        std::vector<int> m_data;
        std::vector<int>::iterator frontIt;
        std::vector<int>::iterator backIt;
        size_t m_size{0};
    public:
        MyCircularDeque(int k)
            : m_data(k), frontIt(m_data.begin()), backIt(m_data.begin() + 1)
        {
        }

        bool insertFront(int value)
        {
            if (m_size >= m_data.size())
                return false;
            frontIt = (frontIt == m_data.begin() ? m_data.end() - 1 : frontIt - 1);
            *frontIt = value;
            ++m_size;
            return true;
        }

        bool insertLast(int value)
        {
            if (m_size >= m_data.size())
                return false;
            *backIt++ = value;
            if (backIt == m_data.end())
                backIt = m_data.begin();
            ++m_size;
            return true;
        }

        bool deleteFront()
        {
            if (isEmpty())
                return false;
            frontIt = (frontIt == m_data.end() - 1 ? m_data.begin() : frontIt + 1);
            --m_size;
            return true;
        }

        bool deleteLast()
        {
            if (isEmpty())
                return false;
            backIt = (backIt == m_data.begin() ? m_data.end() - 1 : backIt - 1);
            --m_size;
            return true;
        }

        int getFront()
        {
            if (isEmpty())
                return -1;
            return *frontIt;
        }

        int getRear()
        {
            if (isEmpty())
                return -1;
            return (backIt == m_data.begin() ? m_data.back() : *(backIt - 1));
        }

        bool isEmpty()
        {
            return m_size == 0;
        }

        bool isFull()
        {
            return m_size == m_data.size();
        }
    };

    class OrderedStream
    {
        vector<string>::iterator ptr;
        vector<string> data;
    public:
        OrderedStream(int n) : data(n)
        {
            ptr = data.begin();
        }

        vector<string> insert(int idKey, string &value)
        {
            data[idKey] = std::move(value);
            vector<string> res;
            while (ptr < data.end() && !ptr->empty())
                res.emplace_back(std::move(*ptr++));
            return res;
        }
    };

    int deepestLeavesSum(TreeNode *root)
    {
        int res;
        vector<TreeNode *> bfsBuffer;
        bfsBuffer.emplace_back(root);
        while (!bfsBuffer.empty())
        {
            vector<TreeNode *> nextBuffer;
            res = 0;
            for (auto &node : bfsBuffer)
            {
                res += node->val;
                if (node->left)
                    nextBuffer.emplace_back(node->left);
                if (node->right)
                    nextBuffer.emplace_back(node->right);
            }
            bfsBuffer = std::move(nextBuffer);
        }
        return res;
    }

    int maxEqualFreq(vector<int> &nums)
    {
        unordered_map<int, int> count, freq;
        int maxFreq{0}, res{0};
        for (int i{}; i < nums.size(); ++i)
        {
            auto num = nums[i];
            if (count[num] > 0)
                --freq[count[num]];
            ++count[num];
            maxFreq = max(maxFreq, count[num]);
            ++freq[count[num]];
            bool match = maxFreq == 1 ||
                    freq[maxFreq] * maxFreq + freq[maxFreq - 1] * (maxFreq - 1) == i + 1 && freq[maxFreq] == 1 ||
                    freq[maxFreq] * maxFreq + 1 == i + 1 && freq[1] == 1;

            if (match)
                res = max(res, i + 1);
        }
        return res;
    }

    int busyStudent(vector<int> &startTime, vector<int> &endTime, int queryTime)
    {
        int res{0};
        for (int i{}; i < startTime.size(); ++i)
            if (startTime[i] <= queryTime && endTime[i] >= queryTime)
                ++res;
        return res;
    }

    vector<vector<string>> printTree(TreeNode *root)
    {
        int MaxDepth{0};
        function<void(TreeNode *, int)> dfs = [&](TreeNode *node, int depth)
        {
            if (!node)
                return;
            if (depth > MaxDepth)
                MaxDepth = depth;
            dfs(node->left, depth + 1);
            dfs(node->right, depth + 1);
        };

        dfs(root, 1);
        auto n = (1 << MaxDepth) - 1;
        vector<vector<string>> res(MaxDepth, vector<string>(n, ""));
        function<void(TreeNode *, int, int)> dfs2 = [&](TreeNode *node, int depth, int idx)
        {
            res[depth][idx] = to_string(node->val);
            if (node->left)
                dfs2(node->left, depth + 1, idx - (1 << (MaxDepth - depth - 2)));
            if (node->right)
                dfs2(node->right, depth + 1, idx + (1 << (MaxDepth - depth - 2)));
        };
        dfs2(root, 0, (n - 1) / 2);
        return res;
    }

    bool canBeEqual(vector<int> &target, vector<int> &arr)
    {
        int *pTarget = target.data();
        int *pArr = arr.data();
        sort(pTarget , pTarget + target.size());
        sort(pArr, pArr + arr.size());
        return target == arr;
    }

    vector<int> findClosestElements(vector<int> &arr, int k, int x)
    {
        auto begin = lower_bound(arr.begin(), arr.end(), x);
        if (begin == arr.end())
            return vector<int>{arr.end() - k, arr.end()};
        if(begin > arr.begin() && abs(*begin - x) > abs(*(begin - 1) - x))
            --begin;
        auto leftIt = begin;
        auto rightIt = begin + 1;
        while(--k && leftIt > arr.begin() && rightIt < arr.end())
        {
            if (abs(*(leftIt - 1) - x) <= abs(*rightIt - x))
                --leftIt;
            else
                ++rightIt;
        }
        if (!k)
            return {leftIt, rightIt};
        if(leftIt == arr.begin())
            return {leftIt, rightIt + k};
        if (rightIt == arr.end())
            return {leftIt - k, rightIt};
        throw
            std::runtime_error("findClosestElements: not enough elements");
    }

    vector<int> shuffle(vector<int> &nums, int n)
    {
        auto it1 = nums.begin();
        auto it2 = it1 + n;

        vector<int> res;
        res.reserve(nums.size());
        for (int i{}; i < n; ++i)
        {
            res.emplace_back(*it1++);
            res.emplace_back(*it2++);
        }
        return res;
    }

    TreeNode *insertIntoMaxTree(TreeNode *root, int val)
    {
        if (!root)
            return new TreeNode(val);
        if (root->val < val)
        {
            auto newRoot = new TreeNode(val);
            newRoot->left = root;
            return newRoot;
        }
        auto it = root;
        while (it->right && it->right->val > val)
            it = it->right;
        auto newRoot = new TreeNode(val);
        newRoot->left = it->right;
        it->right = newRoot;
        return root;
    }

    bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
    {
        stack<int> s;
        int i{};
        for (int val : pushed)
        {
            s.push(val);
            while (!s.empty() && s.top() == popped[i])
            {
                s.pop();
                ++i;
            }
        }
        return s.empty();
    }

    vector<int> finalPrices(vector<int> &prices)
    {
        stack<int> s;
        for(int i{int(prices.size() - 1)}; i >= 0; --i)
        {
            auto tmp = prices[i];
            while(!s.empty() && prices[i] < s.top())
                s.pop();
        
            if(!s.empty())
                prices[i] -= s.top();
            s.push(tmp);
        }
        return prices;
    }

    int longestUnivaluePath(TreeNode *root)
    {
        int res{};
        function<int(TreeNode *)> dfs = [&](TreeNode *node)
        {
            if (!node)
                return 0;
            int leftRes{0}, rightRes{0};
            if (int tmp{dfs(node->left)}; node->left && node->left->val == node->val)
                leftRes = tmp + 1;
            if (int tmp{dfs(node->right)}; node->right && node->right->val == node->val)
                rightRes = tmp + 1;
            res = max({res, leftRes + rightRes});
            return max(leftRes, rightRes);
        };
        dfs(root);
        return res;
    }

    vector<TreeNode *> findDuplicateSubtrees(TreeNode *root)
    {
        struct Tuple
        {
            int val{};
            size_t leftHash{};
            size_t rightHash{};

            size_t hash()
            {
                std::array<size_t, 3> tmp{(size_t)val, leftHash, rightHash};
                std::string buf;
                buf.resize(sizeof(size_t[3]));
                memcpy(buf.data(), tmp.data(), sizeof(size_t[3]));
                return std::hash<std::string>{}(buf);
            }
        };

        std::unordered_map<size_t, int> trees;
        vector<TreeNode *> res;

        function<size_t(TreeNode *)> dfs = [&](TreeNode *node) -> size_t
        {
            if (!node)
                return 114514;

            Tuple myTuple{node->val, dfs(node->left), dfs(node->right)};

            size_t myHash = myTuple.hash();

            if (++trees[myHash] == 2)
                res.emplace_back(node);
            return myHash;
        };
        dfs(root);
        return res;
    }

    string reorderSpaces(string text)
    {
        vector<string_view> words;
        int spaceCount{0};
        for (auto it{text.begin()}; it < text.end();)
        {
            if (*it != ' ')
            {
                auto wordBegin{it};
                while (it < text.end() && *it != ' ')
                    ++it;
                words.emplace_back(&*wordBegin, it - wordBegin);
            }
            else
            {
                ++it;
                ++spaceCount;
            }
        }
        if (words.size() == 1)
            return string(words.front()) + string(spaceCount, ' ');
        int interval = spaceCount / (words.size() - 1);
        int endSpace = spaceCount % (words.size() - 1);
        string res(endSpace, ' ');
        string strInterval(interval,' ');
        for (auto &word : words)
        {
            res += word;
            res += strInterval;
        }
        res += string(endSpace, ' ');
        res.resize(text.size());
        return res;
    }

    vector<int> constructArray(int n, int k)
    {
        int nk = n - k;
        vector<int> res;
        res.reserve(n);
        int itBegin{1};
        for (; itBegin < nk; ++itBegin)
            res.emplace_back(itBegin);
        for (int itEnd{n}; itBegin <= itEnd; ++itBegin, --itEnd)
        {
            res.emplace_back(itBegin);
            if (itBegin != itEnd)
                res.emplace_back(itEnd);
        }
        return res;
    }

    int findLongestChain(vector<vector<int>> &pairs)
    {
        sort(pairs.begin(), pairs.end(), [](const auto &a, const auto &b)
             { return a[1] < b[1]; });

        int res{0};
        int now{INT_MIN};
        for (auto &nums : pairs)
        {
            if(nums[0] > now)
            {
                now = nums[1];
                ++res;
            }
        }
        return res;
    }

    int numSpecial(vector<vector<int>> &mat)
    {
        vector<int> row(mat.size());
        vector<int> col(mat[0].size());
        for(int i{}; i < mat.size(); ++i)
        {
            for(int j{}; j < mat[i].size(); ++j)
            {
                if(mat[i][j])
                {
                    ++row[i];
                    ++col[j];
                }
            }
        }
        int res{};
        for(int i{}; i < mat.size(); ++i)
        {
            for(int j{}; j < mat[i].size(); ++j)
            {
                if(mat[i][j] && row[i] == 1 && col[j] == 1)
                    ++res;
            }
        }
        return res;
    }

    TreeNode *trimBST(TreeNode *root, int low, int high)
    {
        function<void(TreeNode *)> dfs = [&](TreeNode *node)
        {
            if (!node)
                return;
            while(node->left && node->left->val < low)
                node->left = node->left->right;
            while(node->right && node->right->val > high)
                node->right = node->right->left;
            dfs(node->left);
            dfs(node->right);
        };
        if(!root)
            return nullptr;
        if(root->val < low)
            return trimBST(root->right, low, high);
        if(root->val > high)
            return trimBST(root->left, low, high);
        dfs(root);
        return root;
    }

    double mincostToHireWorkers(vector<int> &quality, vector<int> &wage, int k)
    {
        vector<int> index(quality.size());
        iota(index.begin(), index.end(), 0);
        sort(index.begin(), index.end(), [&](int left, int right)
             { return double(wage[left]) / quality[left] < double(wage[right]) / quality[right]; });
        priority_queue<int> q;
        int sum{};
#ifndef DBL_MAX
#define DBL_MAX 1.7976931348623158e+308
#endif
        double res{DBL_MAX};
        for (int i{}; i < index.size(); ++i)
        {
            
            if (q.size() < k || q.top() > quality[index[i]])
            {
                if (q.size() > k)
                {
                    sum -= q.top();
                    q.pop();
                }
                q.push(quality[index[i]]);
                sum += quality[index[i]];
            }

            if (q.size() == k)
                res = min(res, double(sum) * wage[index[i]] / quality[index[i]]);
        }
        return res;
    }

    int minOperations(vector<string> &logs)
    {
        int res{0};
        for (auto &log : logs)
        {
            if (log == "../")
            {
                if(res > 0)
                    --res;
            }
            else if (log != "./")
                ++res;
        }
        return res;
    }

    int maximumSwap(int num)
    {
        if (num == 0)
            return 0;
        int maxNum{-1};
        size_t maxIndex{0};
        int res{num};
        size_t index{0};
        int rawNum{num};
        while (num > 0)
        {

            if (num % 10 > maxNum)
            {
                maxNum = num % 10;
                maxIndex = index;
            }
            else if (num % 10 < maxNum)
                res = (maxNum - num % 10) * pow(10, index) + (num % 10 - maxNum) * pow(10, maxIndex) + rawNum;
            num /= 10;
            ++index;
        }
        return res;
    }

    double trimMean(vector<int> &arr)
    {
        sort(arr.begin(), arr.end());
        double sum{0};
        auto itEnd{arr.end() - arr.size() * 0.05};
        for (auto itBegin{arr.begin() + arr.size() * 0.05}; itBegin < itEnd; ++itBegin)
            sum += *itBegin;
        return sum / arr.size() * 0.9;
    }
        
    int specialArray(vector<int> &nums)
    {
        sort(nums.begin(), nums.end(), std::greater<int>());
        for (int i{1}; i < nums.size(); ++i)
        {
            if(nums[i - 1] >= i && (nums[i] < i || i == nums.size()))
                return i;
        }
        return -1;
    }

    int maxLengthBetweenEqualCharacters(string s)
    {
        struct hash_char
        {
            size_t operator()(const char &c) const
            {
                return c;
            }
        };

        unordered_map<char, pair<int, int>, hash_char> map;

        if (s.size() < 2)
            return -1;

        int res{-1};
        for (int i{}; i < s.size(); ++i)
        {
            if (map.find(s[i]) == map.end())
                map[s[i]] = {i, i};
            else
            {
                map[s[i]].second = i;
                if (map[s[i]].second - map[s[i]].first - 1 > res)
                    res = map[s[i]].second - map[s[i]].first - 1;
            }
        }
        return res;
    }

    vector<int> decrypt(vector<int> &code, int k)
    {
        class MyInt : public vector<int>
        {
        public:
            using vector<int>::vector;
            MyInt(vector<int> &&vec) : vector<int>(std::move(vec)) {}
            auto &operator[](int64_t index)
            {
                if (index < 0)
                    index += size();
                index %= size();
                return vector<int>::operator[](index);
            }
        };
        auto accumulate = [](MyInt &code, int64_t begin, int64_t end)
        {
            int sum{};
            for (auto i{begin}; i < end; ++i)
                sum += code[i];
            return sum;
        };
        if (k == 0)
            return vector<int>(code.size(), 0);
        MyInt _code{std::move(code)};
        MyInt res(_code.size(), 0);
        for (int i{}; i < _code.size(); ++i)
        {
            if (k > 0)
                res[i] = accumulate(_code, i + 1, i + k + 1);
            else
                res[i] = accumulate(_code, i + k, i);
        }
        return res;
    }

    int rotatedDigits(int n)
    {
        auto isGoodNum = [](int num) constexpr noexcept
        {
            bool flag{false};
            while (num)
            {
                if (num % 10 == 3 || num % 10 == 4 || num % 10 == 7)
                    return false;
                if (num % 10 == 2 || num % 10 == 5 || num % 10 == 6 || num % 10 == 9)
                    flag = true;
                num /= 10;
            }
            return flag;
        };
        constexpr array<int, 10001> isGoodNumArray{[&]() constexpr noexcept
                                                   {
                                                       array<int, 10001> res{0};
                                                       for (int i{1}; i < res.size(); ++i)
                                                           res[i] = res[i - 1] + static_cast<int>(isGoodNum(i));
                                                       return res;
                                                   }()};
        return isGoodNumArray[n];
    }

    int minAddToMakeValid(string s)
    {
        int res{};
        int left{};
        for (auto &c : s)
        {
            if (c == '(')
                ++left;
            else if (left > 0)
                --left;
            else
                ++res;
        }
        return res + left;
    }

    int jobScheduling(vector<int> &startTime, vector<int> &endTime, vector<int> &profit)
    {
        vector<int> index(startTime.size());
        iota(index.begin(), index.end(), 0);
        sort(index.begin(), index.end(), [&](int a, int b)
             { return endTime[a] < endTime[b]; });
        vector<int> dp(startTime.size());
        dp[0] = profit[index[0]];
        for (int i{1}; i < index.size(); ++i)
        {
            int k = upper_bound(index.begin(), index.begin() + i, startTime[index[i]], [&](int left, int right)
                                { return left < endTime[index[right]]; }) - index.begin();
            dp[i] = max(dp[i - 1], profit[index[i]] + (k > 0 ? dp[k] : 0));
        }
        return dp.back();
    }

    string mergeAlternately(string word1, string word2)
    {
        string res(word1.size() + word2.size(), 0);
        auto it1{0};
        auto it2{0};
        for(;it1 < word1.size() && it2 < word2.size(); ++it1, ++it2)
        {
            res[it1 + it2] = word1[it1];
            res[it1 + it2 + 1] = word2[it2];
        }
        for (; it1 < word1.size(); ++it1)
            res[it1 + it2] = word1[it1];
        for (; it2 < word2.size(); ++it2)
            res[it1 + it2] = word2[it2];
        return res;
    }

    int countMatches(vector<vector<string>> &items, string ruleKey, string ruleValue)
    {
        unordered_map<string, int> type, color, name;
        for (auto &item : items)
        {
            ++type[item[0]];
            ++color[item[1]];
            ++name[item[2]];
        }
        if (ruleKey == "type")
            return type[ruleValue];
        else if(ruleKey == "color")
            return color[ruleValue];
        else
            return name[ruleValue];
    }

    int flipLights(int n, int presses)
    {
        if (presses > 2 && n > 2)
            return 8;
        if (n < 3)
            return 1 + (presses > 0) * n + (presses > 1 && n > 1);
        else
            return 1 + 3 * presses;
    }

    vector<int> frequencySort(vector<int> &nums)
    {
        array<int, 201> mp{0};
        for (const auto &num : nums)
            ++mp[num + 100];
        sort(nums.begin(), nums.end(), [&](int left, int right)
             {
                if (mp[left + 100] == mp[right + 100])
                    return left > right;
                else
                    return mp[left + 100] < mp[right + 100];
             });
        return std::move(nums);
    }

    bool canPartitionKSubsets(vector<int> &nums, int k)
    {
        auto sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % k != 0)
            return false;
        int per = sum / k;
        sort(nums.begin(), nums.end());
        if (nums.back() > per)
            return false;

        vector<bool> dp(1 << nums.size(), true);
        function<bool(int, int)> dfs = [&](int s, int p)
        {
            if (s == 0)
                return true;
            if (!dp[s])
                return false;
            for (int i{}; i < nums.size(); ++i)
            {
                if (nums[i] + p > per)
                    break;
                if ((s >> i) & 1)
                    if (dfs(s ^ (1 << i), (p + nums[i]) % per))
                        return true;
            }
            return false;
        };
        return dfs((1<<nums.size()) - 1, 0);
    }

    bool canFormArray(vector<int> &arr, vector<vector<int>> &pieces)
    {
        unordered_map<int, size_t> m;
        for (size_t i{}; i < arr.size(); ++i)
            m[arr[i]] = i;

        for (const auto &piece : pieces)
        {
            int index{-1};
            for (const auto &i : piece)
            {
                if (m.count(i) == 0)
                    return false;
                if (m[i] != index + 1 && index != -1)
                    return false;
                index = m[i];
            }
        }
        return true;
    }

    class MyLinkedList
    {
    private:
        struct Node
        {
            int m_val;
            Node *m_next;
        };
        using pNode = Node *;
        pNode m_begin{nullptr};
        size_t m_size{0};
    public:
        
        MyLinkedList()
        {
        }

        int get(int index)
        {
            if (index < 0 || index >= m_size)
                return -1;
            auto it = m_begin;
            while (index--)
                it = it->m_next;
            return it->m_val;
        }

        void addAtHead(int val)
        {
            addAtIndex(0, val);
        }

        void addAtTail(int val)
        {
            addAtIndex(m_size, val);
        }

        void addAtIndex(int index, int val)
        {
            if (index > m_size)
                return;
            
            if (index <= 0)
            {
                auto node{new Node{val, m_begin}};
                m_begin = node;
                ++m_size;
                return;
            }

            auto it{m_begin};
            --index;
            while (index--)
                it = it->m_next;
            auto node{new Node{val, it->m_next}};
            it->m_next = node;
            ++m_size;
        }

        void deleteAtIndex(int index)
        {
            if (index < 0 || index >= m_size)
                return;
            if (index == 0)
            {
                m_begin = m_begin->m_next;
                --m_size;
                return;
            }

            auto it{m_begin};
            --index;
            while (index--)
                it = it->m_next;
            it->m_next = it->m_next->m_next;
            --m_size;
        }
    };

    int getKthMagicNumber(int k)
    {
        vector<int> dp(k);
        dp[0] = 1;
        size_t p3{0}, p5{0}, p7{0};
        for (int i{1}; i < k; ++i)
        {
            dp[i] = min({dp[p3] * 3, dp[p5] * 5, dp[p7] * 7});
            if (dp[i] == dp[p3] * 3)
                ++p3;
            if (dp[i] == dp[p5] * 5)
                ++p5;
            if (dp[i] == dp[p7] * 7)
                ++p7;
        }
        return dp.back();
    }

    bool isFlipedString(string &s1, string &s2)
    {
        if (s1.size() != s2.size())
            return false;
        s2 += s2;
        return s2.find(s1) != string::npos;
    }

    void setZeroes(vector<vector<int>> &matrix)
    {
        bool firstColZero{false};
        bool firstRowZero{false};
        for (const auto &col : matrix)
            if (col.front() == 0)
                firstRowZero = true;
        for (const auto &i : matrix.front())
            if (i == 0)
                firstColZero = true;
        for (int i{1}; i < matrix.size(); ++i)
        {
            for (int j{1}; j < matrix.front().size(); ++j)
            {
                if (matrix[i][j] == 0)
                {
                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
                }
            }
        }

        for (size_t i{1}; i < matrix.front().size(); ++i)
            if (matrix.front()[i] == 0)
                for (size_t j{1}; j < matrix.size(); ++j)
                    matrix[j][i] = 0;

        for (size_t i{1}; i < matrix.size(); ++i)
            if (matrix[i].front() == 0)
                for (size_t j{1}; j < matrix.front().size(); ++j)
                    matrix[i][j] = 0;
        if (firstRowZero)
            for (auto &col : matrix)
                col.front() = 0;
        if (firstColZero)
            matrix.front() = vector<int>(matrix.front().size(), 0);
    }

    int scoreOfParentheses(string s)
    {
        std::function<int(string::iterator &)> fun = [&](string::iterator &iter)
        {
            int stk = 0;
            int res = 0;
            char last = *iter;
            while (stk > 0)
            {
                ++iter;
                if (*iter == '(' && last == '(')
                    ++stk;
                else if (*iter == ')')
                {
                    res = res == 0 ? 1 : res * 2;
                    --stk;
                }
                else if (*iter == '(' && last == ')')
                    res += fun(iter);
                last = *iter;
            }
            return res;
        };

        auto iter = s.begin();
        int sum = 0;
        while (iter != s.end())
        {
            sum += fun(iter);
            ++iter;
        }
        return sum;
    }

    bool areAlmostEqual(string &s1, string &s2)
    {
        if (s1.length() != s2.length())
            return false;
        char s1_index[2]{0,0};
        char s2_index[2]{0,0};
        for (size_t i{0}; i < s1.length(); ++i)
        {
            if (s1[i] != s2[i])
            {
                if (s1_index[0] == 0)
                {
                    s1_index[0] = s1[i];
                    s2_index[0] = s2[i];
                }
                else if (s1_index[1] == 0)
                {
                    s1_index[1] = s1[i];
                    s2_index[1] = s2[i];
                }
                else
                    return false;
            }
        }
        return s1_index[0] == s2_index[1] && s1_index[1] == s2_index[0];
    }

    int numComponents(ListNode *head, vector<int> &nums)
    {
        unordered_set<int> set_nums(nums.begin(), nums.end());

        int res{0};
        for (auto it = head; it; )
        {
            while (it && !set_nums.count(it->val))
                it = it->next;
            if (!it)
                return res;
            ++res;
            while (it && set_nums.count(it->val))
                it = it->next;
        }

        return res;
    }

    int maxChunksToSorted(vector<int> &arr)
    {
        int res{0};
        int tmp{0};
        for (int i{}; i < arr.size(); ++i)
        {
            tmp = max(arr[i], tmp);
            if (tmp == i)
                ++res;
        }
        return res;
    }

    int totalFruit(vector<int> &fruits)
    {
        if (fruits.size() < 2)
            return fruits.size();
        int res{0};
        int bufNum[2];
        int bufIndex[2];
        int now{1};
        bufNum[0] = fruits.back();
        bufIndex[0] = fruits.size() - 1;

        int it;
        for (it = fruits.size() - 2; it >= 0; --it)
        {
            if (fruits[it] != bufNum[0])
            {
                bufNum[1] = fruits[it];
                bufIndex[1] = it;
                bufIndex[0] = it + 1;
                ++now;
                --it;
                break;
            }
            else
            {
                ++now;
            }
        }

        for (; it >= 0; --it)
        {
            auto num = fruits[it];
            if (num == bufNum[0] || num == bufNum[1])
            {
                ++now;
                if (num != fruits[it + 1])
                    bufIndex[num == bufNum[1]] = it;
            }
            else
            {
                res = max(res, now);
                if (bufIndex[0] > bufIndex[1])
                {
                    swap(bufIndex[0], bufIndex[1]);
                    bufNum[0] = bufNum[1];
                }
                bufIndex[1] = it;
                bufNum[1] = num;
                now = bufIndex[0] - it + 1;
            }
        }
        return max(res, now);

    }

    int countStudents(vector<int> &students, vector<int> &sandwiches)
    {
        int s[2];
        s[1] = accumulate(students.begin(), students.end(), 0);
        s[0]  = students.size() - s[1];
        int res{0};
        for (const auto &i : sandwiches)
        {
            if (s[i] <= 0)
                return res;
            --s[i];
            ++res;
        }
        return students.size() - res;
    }

    class StockSpanner
    {
        struct DayPrice
        {
            int day{};
            int price{};
        };
    public:
        StockSpanner() = default;

        int next(int price)
        {
            while (!m_st.empty() && price >= m_st.top().price)
                m_st.pop();
            int last_day = m_st.empty() ? 0 : m_st.top().day;
            m_st.emplace(DayPrice{++m_day, price});
            return m_day - last_day;
        }

    private:
        stack<DayPrice> m_st{};
        int m_day{};
    };

    int partitionDisjoint(vector<int> &nums)
    {
        int pos{0}, leftMax{nums[0]};
        for (int i{1}; i < nums.size() - 1; ++i)
        {
            if (nums[i] > leftMax)
                leftMax = nums[i];
            if (nums[i] < leftMax)
                pos = i;
        }
        return pos + 1;
    }

    int shortestSubarray(vector<int> &nums, int k)
    {
        if (nums.front() >= k)
            return 1;
        vector<int> preSum(nums.size() + 1);
        preSum[0] = 0;
        for (size_t i{1}; i < preSum.size(); ++i)
            preSum[i] = preSum[i - 1] + nums[i - 1];

        deque<int> dq({0});
        int res = INT_MAX;
        for (size_t i{1}; i < preSum.size(); ++i)
        {
            while (!dq.empty() && preSum[i] - preSum[dq.front()] >= k)
            {
                res = min(int(i - dq.front()), res);
                dq.pop_front();
            }
            while (!dq.empty() && preSum[dq.back()] > preSum[i])
                dq.pop_back();
            dq.push_back(i);
        }
        return res < preSum.size() ? res : -1;
    }

    int arraySign(vector<int> &nums)
    {
        int res{1};
        for (int i : nums)
        {
            if (i == 0)
                return 0;
            if (i < 0)
                res *= -1;
        }
        return res;
    }

    int sumSubarrayMins(vector<int> &arr)
    {
        stack<int> st;
        vector<int> dp(arr.size());
        int64_t res{0};
        constexpr int64_t mod = 1e9 + 7;
        for (int i{}; i < arr.size(); ++i)
        {
            while (!st.empty() && arr[st.top()] > arr[i])
                st.pop();
            int k = st.empty() ? (i + 1) : (i - st.top());
            dp[i] = k * arr[i] + (st.empty() ? 0 : dp[i - k]);
            res = (res + dp[i]) % mod;
            st.emplace(i);
        }
        return res;
    }

    int magicalString(int n)
    {
        vector<char> vec{1, 2, 2, 1, 1, 2, 1, 2, 2, 1, 2, 2, 1, 1, 2, 1, 1, 2, 2};
        if (n <= vec.size())
            return std::count_if(vec.begin(), vec.begin() + n, [](int i){return i == 1;});
        vec.resize(n);
        int it_begin = 12;
        int it_now = 19;
        int res{9};
        while (it_now < n)
        {
            int insert_num = vec[it_now - 1] == 1 ? 2 : 1;
            int add_res = insert_num == 1;
            vec[it_now++] = insert_num;
            res += add_res;
            if (vec[it_begin++] == 2 && it_now < n)
            {
                res += add_res;
                vec[it_now++] = insert_num;
            }
        }
        return res;
    }

    bool arrayStringsAreEqual(vector<string> &word1, vector<string> &word2)
    {
        struct vec_str_it
        {
            vector<string> &vec_ref;
            size_t vec_index{0};
            size_t str_index{0};
            auto& operator*()
            {
                return vec_ref[vec_index][str_index];
            }
            void operator++()
            {
                if (++str_index < vec_ref[vec_index].size())
                    return;
                str_index = 0;
                ++vec_index;
            }
            bool end()
            {
                return vec_ref.size() == vec_index;
            }
        } it1{word1}, it2{word2};

        while(!it1.end() && !it2.end()){
            if (*it1 != *it2)
                break;
            ++it1;
            ++it2;
        }
        return it1.end() && it2.end();
    }

    vector<int> bestCoordinate(vector<vector<int>> &towers, int radius)
    {
        vector<int> res_pos(2, 0);
        int res_power{0};

        auto getDis = [](auto x1, auto y1, auto x2, auto y2)
        {
            auto dx = x2 - x1;
            auto dy = y2 - y1;
            return dx * dx + dy * dy;
        };
        
        for (int x{0}; x <= 50; ++x)
        {
            for (int y{0}; y <= 50; ++y)
            {
                int power{0};
                for (auto &tower : towers)
                {
                    auto dis = getDis(x, y, tower[0], tower[1]);
                    if (dis > radius * radius)
                        continue;
                    power += tower[2] / (1 + sqrt(dis));
                }
                if (power > res_power)
                {
                    res_power = power;
                    res_pos[0] = x;
                    res_pos[1] = y;
                }
            }
        }
        return res_pos;
    }

    int maxRepeating(string sequence, string word)
    {
        int res{0};
        int cnt{0};
        int word_index{0};
        for (size_t i{}; i < sequence.size(); ++i)
        {
            if (sequence[i] == word[word_index])
            {
                if (++word_index == word.size())
                {
                    ++cnt;
                    word_index = 0;
                }
            }
            else
            {
                res = max(res, cnt);
                cnt = 0;
                word_index = 0;
            }
        }
        return res;
    }

    int countConsistentStrings(string allowed, vector<string> &words)
    {
        int alowedMask{0};
        for (auto &ch : allowed)
            alowedMask |= 1 << (ch - 'a');
        auto isConsistentString = [&](const string &str)
        {
            for (auto &ch : str)
                if (!(alowedMask | (ch - 'a')))
                    return false;
            return true;
        };
        return count_if(words.begin(),words.end(),isConsistentString);
    }

    int numMatchingSubseq(const string &s, vector<string> &words)
    {
        array<vector<int>, 26> tab;
        for (int i{0}; i < s.size(); ++i)
            tab[s[i] - 'a'].emplace_back(i);

        auto is_substr = [&tab](const string &sub)
        {
            auto it1 = sub.begin();
            int it2{-1};
            for (; it1 < sub.end(); ++it1)
            {
                auto &poses = tab[*it1 - 'a'];
                auto res = upper_bound(poses.begin(), poses.end(), it2);
                if (res == poses.end())
                    return false;
                it2 = *res;
            }
            return true;
        };

        return count_if(words.begin(), words.end(), is_substr);
    }

    int sumSubseqWidths(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        int64_t res{0};
        constexpr int64_t mod{static_cast<int64_t>(1e9 + 7)};
        int64_t x = nums[0], y = 2;
        for (int j = 1; j < nums.size(); ++j)
        {
            res = (res + nums[j] * (y - 1) - x) % mod;
            x = (x * 2 + nums[j]) % mod;
            y = y * 2 % mod;
        }
        return (res + mod) % mod;
    }

    int countBalls(int lowLimit, int highLimit)
    {
        unordered_map<int, int> tab;
        for (int i = lowLimit; i <= highLimit; ++i)
        {
            int box{0};
            for (auto tmp{i}; tmp; tmp /= 10)
                box += tmp % 10;
            ++tab[box];
        }
        int res{0};
        for (const auto &[box, num] : tab)
        {
            if (num > res)
                res = num;
        }
        return res;
    }

    int numSubarrayBoundedMax(vector<int> &nums, int left, int right)
    {
        auto count = [&](int lower)
        {
            int res{};
            int cnt{};
            for (auto i : nums)
            {
                if (i <= lower)
                    res += ++cnt;
                else
                    cnt = 0;
            }
            return res;
        };
        return count(right) - count(left - 1);
    }

    vector<string> letterCasePermutation(const string &s)
    {
        const size_t size = s.size();
        const int letterCount = count_if(s.begin(), s.end(), [](char c)
                                         { return isalpha(c); });
        vector<string> res(1 << letterCount, string(size, 0));
        for (int mask{0}; mask < (1 << letterCount); ++mask)
        {
            int bitCount{};
            for (int i{}; i < size; ++i)
            {
                if (isalpha(s[i]))
                {
                    if (mask & (1 << bitCount))
                        res[mask][i] = toupper(s[i]);
                    else
                        res[mask][i] = tolower(s[i]);
                    ++bitCount;
                }
                else
                    res[mask][i] = s[i];
            }
        }
        return res;
    }
    
    int reachNumber(int target)
    {
        target = abs(target);
        int sum{};
        int step{};
        while (sum < target)
        {
            ++step;
            sum += step;
        }
        return target % 2 == 0 ? step : step + 1 + step % 2;
    }

    int largestAltitude(vector<int>& gain)
    {
        int res{0};
        int cur{0};
        for (auto i : gain)
        {
            cur += i;
            res = max(res, cur);
        }
        return res;
    }

    int numDifferentIntegers(const string &word)
    {
        std::unordered_set<string_view> tab;
        for (auto it = word.begin(); it < word.end(); ++it)
        {
            if (*it < '0' || *it > '9')
                continue;

            auto tmp = it;
            for (++it; it < word.end() && *it >= '0' && *it <= '9'; ++it){}
            while( tmp < it - 1 && *tmp == '0'){ ++tmp;}
            tab.emplace(tmp, it);
        }
        return tab.size();
    }

    int minOperations(vector<int> &nums1, vector<int> &nums2)
    {
        if (nums1.size() * 6 < nums2.size() || nums2.size() * 6 < nums1.size())
            return -1;
        int sum1 = accumulate(nums1.begin(), nums1.end(), 0);
        int sum2 = accumulate(nums2.begin(), nums2.end(), 0);
        int delta = abs(sum1 - sum2);
        auto &minVec = sum1 < sum2 ? nums1 : nums2;
        auto &maxVec = sum1 < sum2 ? nums2 : nums1;
        array<int, 6> count{0};
        for (auto i : minVec)
            ++count[6 - i];
        for (auto i : maxVec)
            ++count[i - 1];
        int res{};
        for (int i = 5; i >= 0; --i)
        {
            int tmp = min(count[i], (delta + i - 1) / i);
            res += tmp;
            delta -= tmp * i;
            if (delta <= 0)
                break;
        }
        return res;
    }

    bool squareIsWhite(string coordinates) {
        return (coordinates[0] - 'a' + coordinates[1] - '1') % 2 == 1;
    }

    bool checkPowersOfThree(int n)
    {
        if (n == 0)
            return true;
        if (n % 3 != 0 && n % 3 != 1)
            return false;

        auto pow = [](int x, int y) consteval
        {
            int res{1};
            for (int i{}; i < y; ++i)
                res *= x;
            return res;
        };

        constexpr int threePow[20] = {pow(3, 0), pow(3, 1), pow(3, 2), pow(3, 3), pow(3, 4), pow(3, 5), pow(3, 6), pow(3, 7), pow(3, 8), pow(3, 9), pow(3, 10), pow(3, 11), pow(3, 12), pow(3, 13), pow(3, 14), pow(3, 15), pow(3, 16), pow(3, 17), pow(3, 18), pow(3, 19)};

        auto it = 19;
        while (n > 0)
        {
            if (n >= threePow[it])
            {
                n -= threePow[it];
                if (n == 0)
                    return true;
            }
            --it;
        }
        return false;
    }

    int minOperations(vector<int> &nums)
    {
        int res{0};
        int last{nums.front() - 1};
        for (auto i : nums)
        {
            auto tmp = last - i + 1;
            res += max(0, tmp);
            last = tmp > 0 ? i + tmp : i;
        }
        return res;
    }

    int beautySum(string &s)
    {
        if (s.size() < 3)
            return 0;
        auto beauty = [](const string_view &s)
        {
            array<int, 26> count{};
            for (auto i : s)
                ++count[i - 'a'];
            int minIt{INT_MAX};
            for (auto i: count)
                if (i != 0)
                    minIt = min(minIt, i);
            auto maxIt = *max_element(count.begin(), count.end());
            return maxIt - minIt;
        };
        int res{};
        for (int i{}; i < s.size(); ++i)
        {
            for (int j{i + 2}; j < s.size(); ++j)
            {
                res += beauty(string_view{s.data()+ i, static_cast<size_t>(j - i + 1)});
            }
        }
        return res;
    }

    bool checkIfPangram(string sentence)
    {
        array<bool, 26> count{};
        for (auto i : sentence)
            count[i - 'a'] = true;
        return all_of(count.begin(), count.end(), [](bool i){return i;});
    }

    int getLucky(string &s, int k)
    {
        int res{0};
        for (auto i : s)
            res += (i - 'a' + 1) / 10 + (i - 'a' + 1) % 10;
        for (int i{}; i < k - 1; ++i)
        {
            int tmp{};
            while (res > 0)
            {
                tmp += res % 10;
                res /= 10;
            }
            res = tmp;
        }
        return res;
    }

    int minElements(vector<int> &nums, int limit, int goal)
    {
        int64_t sum = accumulate(nums.begin(), nums.end(), 0ll);
        int64_t delta = abs(sum - goal);
        return (delta + limit - 1) / limit;
    }

    bool validPath(int n, vector<vector<int>> &edges, int source, int destination)
    {
        vector<vector<int>> graph(n);
        for (auto &i : edges)
        {
            graph[i[0]].push_back(i[1]);
            graph[i[1]].push_back(i[0]);
        }
        vector<bool> visited(n);
        queue<int> q;
        q.push(source);
        visited[source] = true;
        while (!q.empty())
        {
            auto tmp = q.front();
            q.pop();
            if (tmp == destination)
                return true;
            for (auto i : graph[tmp])
            {
                if (!visited[i])
                {
                    q.push(i);
                    visited[i] = true;
                }
            }
        }
        return false;
    }

    int minimumSize(vector<int> &nums, int maxOperations)
    {
        int minNum = 1, maxNum = *max_element(nums.begin(), nums.end());
        for (auto i : nums)
        {
            maxNum = max(maxNum, i);
            minNum = min(minNum, i);
        }
        // binary search
        while (minNum < maxNum)
        {
            int mid = (minNum + maxNum) / 2;
            int count{};
            for (auto i : nums)
                count += (i - 1) / mid;
            if (count > maxOperations)
                minNum = mid + 1;
            else
                maxNum = mid;
        }
        return minNum;
    }

    int maximumScore(int a, int b, int c)
    {
        std::array<int, 3> nums{a, b, c};
        sort(nums.begin(), nums.end());
        int res{};
        if (nums[0] + nums[1] <= nums[2])
            return nums[0] + nums[1];
        else
        {
            res += nums[2];
            res += (nums[0] + nums[1] - nums[2]) / 2;
            return res;
        }
    }

    int finalValueAfterOperations(vector<string> &operations)
    {
        int res{0};
        for (auto &op : operations)
        {
            if (op[1] == '+')
                ++res;
            else
                --res;
        }
        return res;
    }

    string largestMerge(string_view word1, string_view word2)
    {
        string res;
        res.reserve(word1.size() + word2.size());
        while (!word1.empty() && !word2.empty())
        {
            if (word1 > word2)
            {
                res.push_back(word1.front());
                word1.remove_prefix(1);
            }
            else
            {
                res.push_back(word2.front());
                word2.remove_prefix(1);
            }
        }
        res.append(word1);
        res.append(word2);
        return res;
    }

    int minMovesToSeat(vector<int> &seats, vector<int> &students)
    {
        sort(seats.begin(), seats.end());
        sort(students.begin(), students.end());
        int res{};
        for (int i{}; i < seats.size(); ++i)
            res += abs(seats[i] - students[i]);
        return res;
    }

    char repeatedCharacter(std::string_view s)
    {
        int countCode{};
        for (auto ch : s)
        {
            if (countCode & (1 << (ch - 'a')))
                return ch;
            else
                countCode |= (1 << (ch - 'a'));
        }
        return 0;
    }

    int countEven(int num)
    {
        int res{};
        auto count = [](int n) constexpr noexcept {
            int res{};
            while (n > 0)
            {
                res += n % 10;
                n /= 10;
            }
            return res;
        };
        for (int i = 2; i <= num; ++i)
        {
            if (count(i) % 2 == 0)
                ++res;
        }
        return res;
    }

    int rearrangeCharacters(string_view s, string_view target)
    {
        unordered_map<char, int> targetCount;
        for (auto ch : target)
            ++targetCount[ch];

        array<int, 26> count{};
        for (auto ch : s)
            ++count[ch - 'a'];

        int res = INT_MAX;
        for (const auto &[ch, cnt] : targetCount)
            res = min(res, count[ch - 'a'] / cnt);
        if (res == INT_MAX)
            return 0;
        return res;
    }

    bool areSentencesSimilar(string_view sentence1, string_view sentence2)
    {
        if (sentence1 == sentence2)
            return true;
        if (sentence1.size() == sentence2.size())
            return false;

        auto split = [](string_view s)
        {
            vector<string_view> res;
            for (auto i = s.begin(); i != s.end();)
            {
                auto j = find(i, s.end(), ' ');
                res.emplace_back(&*i, distance(i, j));
                i = j;
                if (i != s.end())
                    ++i;
            }
            return res;
        };
        auto words1 = split(sentence1);
        auto words2 = split(sentence2);
        if (words1.size() == words2.size())
            return false;
        if (words1.size() < words2.size())
            swap(words1, words2);
        auto itLeft = words2.begin();
        auto itRight = words2.end();
        for (auto it = words1.begin(); it != words1.end() && itLeft <= words2.end();)
        {
            if (*it == *itLeft)
            {
                ++itLeft;
                ++it;
            }
            else
                break;
        }
        for (auto it = words1.rbegin(); it != words1.rend() && itRight >= words2.begin();)
        {
            if (*it == *(itRight - 1))
            {
                --itRight;
                ++it;
            }
            else
                break;
        }
        return itRight == itLeft;
    }

    int countNicePairs(vector<int> &nums)
    {
        unordered_map<int, int> count;
        auto reverse = [](int n) constexpr noexcept {
            int res{};
            while (n > 0)
            {
                res = res * 10 + n % 10;
                n /= 10;
            }
            return res;
        };
        for (auto &num : nums)
            ++count[num - reverse(num)];
        int res{};
        for (const auto &[_, cnt] : count)
            res = (res + (long long)cnt * (cnt - 1) / 2) % 1000000007;
        return res;
    }

    class MKAverage
    {
    public:
        MKAverage(int m, int k) : m(m), k(k)
        {
            divisor = m - 2 * k;
        }

        void addElement(int num)
        {
            dataStream.emplace(num);
            if (dataStream.size() <= m)
            {
                mid.emplace(num);
                MKsum += num;

                if (dataStream.size() == m)
                {
                    auto it = mid.begin();
                    advance(it, k);
                    left.insert(mid.begin(), it);

                    auto rit = mid.rbegin();
                    advance(rit, k);
                    right.insert(mid.rbegin(), rit);

                    MKsum -= accumulate(left.begin(), left.end(), 0);
                    MKsum -= accumulate(right.begin(), right.end(), 0);

                    mid.erase(mid.begin(), it);
                    mid.erase(prev(mid.end(), k), mid.end());
                }
                return;
            }

            if (num < *mid.begin())
            {
                left.emplace(num);
                MKsum += *left.rbegin();
                mid.emplace(*left.rbegin());
                left.erase(prev(left.end()));
            }
            else if (num > *mid.rbegin())
            {
                right.emplace(num);
                MKsum += *right.begin();
                mid.emplace(*right.begin());
                right.erase(right.begin());
            }
            else
            {
                mid.emplace(num);
                MKsum += num;
            }

            auto remove = dataStream.front();
            dataStream.pop();
            auto it = mid.find(remove);
            if (it != mid.end())
            {
                mid.erase(it);
                MKsum -= remove;
            }
            else if ((it = left.find(remove)) != left.end())
            {
                left.erase(it);
                left.emplace(*mid.begin());
                MKsum -= *mid.begin();
                mid.erase(mid.begin());
            }
            else
            {
                it = right.find(remove);
                right.erase(it);
                right.emplace(*mid.rbegin());
                MKsum -= *mid.rbegin();
                mid.erase(prev(mid.end()));
            }
        }

        int calculateMKAverage()
        {
            if (dataStream.size() < m)
                return -1;
            return MKsum / divisor;
        }

    private:
        int m;
        int k;
        queue<int> dataStream;
        multiset<int> left;
        multiset<int> mid;
        multiset<int> right;
        int64_t MKsum{0};
        int64_t divisor;
    };

    bool strongPasswordCheckerII(string password)
    {
        if (password.size() < 8)
            return false;
        bool hasLower = false;
        bool hasUpper = false;
        bool hasDigit = false;
        bool hasUnusual = false;
        std::string_view unusual{"!@#$%^&*()-+"};
        char lastChar{-1};
        for (auto c : password)
        {
            if (c == lastChar)
                return false;

            if (c >= 'a' && c <= 'z')
                hasLower = true;
            else if (c >= 'A' && c <= 'Z')
                hasUpper = true;
            else if (c >= '0' && c <= '9')
                hasDigit = true;
            else if (unusual.find(c) != std::string_view::npos)
                hasUnusual = true;
            lastChar = c;
        }
        return hasLower && hasUpper && hasDigit && hasUnusual;
    }

    vector<int> findingUsersActiveMinutes(vector<vector<int>> &logs, int k)
    {
        unordered_map<int, unordered_set<int>> userActiveMinutes;
        for (auto &log : logs)
            userActiveMinutes[log[0]].emplace(log[1]);
        vector<int> res(k);
        for (const auto &[_, minutes] : userActiveMinutes)
            if (minutes.size() <= k && !minutes.empty())
                ++res[minutes.size() - 1];
        return res;
    }

    int minSideJumps(vector<int> &obstacles)
    {
        array<vector<int>, 3> dp;
        dp.fill(vector<int>(obstacles.size()));
        dp[0][0] = 1;
        dp[1][0] = 0;
        dp[2][0] = 1;
        for (size_t i{1}; i < obstacles.size(); ++i)
        {
            for (auto &j : dp)
                j[i] = j[i - 1];
            if (obstacles[i] != 0)
                dp[obstacles[i] - 1][i] = INT_MAX - 1;
            auto miniCnt = min({dp[0][i], dp[1][i], dp[2][i]});
            for (auto &j : dp)
                j[i] = min(j[i], miniCnt + 1);
        }
        return min({dp[0].back(), dp[1].back(), dp[2].back()});
    }

    double calculateTax(vector<vector<int>> &brackets, int income)
    {
        if (income <= 0)
            return 0;
        double tax{0.0};
        for (size_t i{brackets.size() - 1}; i > 0; --i)
            brackets[i][0] -= brackets[i - 1][0];
        for (auto &bracket : brackets)
        {
            if (income <= bracket[0])
            {
                return (tax + income * bracket[1]) / 100.0;
            }
            else
            {
                tax += bracket[0] * bracket[1];
                income -= bracket[0];
            }
        }
        return tax;
    }

    vector<int> countPoints(vector<vector<int>> &points, vector<vector<int>> &queries)
    {
        auto GetDistence = [](int x1, int y1, int x2, int y2) constexpr noexcept -> int
        {
            return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
        };

        vector<int> res;
        res.reserve(queries.size());
        for (const auto & query : queries)
        {
            int cnt{0};
            int r2 = query[2] * query[2];
            for (const auto & point : points)
                if (GetDistence(point[0], point[1], query[0], query[1]) <= r2)
                    ++cnt;
            res.emplace_back(cnt);
        }
        return res;
    }

    string getSmallestString(int n, int k)
    {
        string res(n, 'a');
        k -= n;
        auto it = res.end();
        while (k > 0)
        {
            *(--it) += (k > 25 ? 25 : k);
            k -= 25;
        }
        return res;
    }

    string greatestLetter(string_view s)
    {
        using flag = unsigned char;
        constexpr flag UPPER = 0X01;
        constexpr flag LOWER = 0X02;
        constexpr flag GOOD  = UPPER | LOWER;
        array<flag, 26> flags{0};
        for (const auto &ch : s)
        {
            if (ch <= 'Z')
                flags[ch - 'A'] |= UPPER;
            else
                flags[ch - 'a'] |= LOWER;
        }
        for (int i{25}; i >= 0; --i)
            if ((flags[i] & GOOD) == GOOD)
                return {char('A' + i)};
        return {};
    }

    ListNode *mergeInBetween(ListNode *list1, int a, int b, ListNode *list2)
    {
        auto advance = [](ListNode *it, size_t cnt = 1) constexpr
        {
            while (cnt--)
                it = it->next;
            return it;
        };

        auto start = advance(list1, a - 1);
        auto end = advance(list1, b + 1);

        start->next = list2;

        auto list2End = list2;
        while (list2End->next)
            list2End = list2End->next;

        list2End->next = end;
        return list1;
    }

    bool checkXMatrix(vector<vector<int>> &grid)
    {
        auto n = grid.size();
        for (int i{0}; i < n; ++i)
            if (grid[i][i] == 0)
                return false;

        for (int i{0}; i < n; ++i)
            if (grid[i][n - i - 1] == 0)
                return false;

        for (int i{0}; i < n; ++i)
            for (int j{0}; j < n; ++j)
                if (i != j && j != n - i - 1 && grid[i][j] != 0)
                    return false;
        return true;
    }

    string decodeMessage(string key, string message)
    {
        unordered_map<char, char> keyMap;
        char it = 'a';
        for (const auto &ch : key)
            if (keyMap.count(ch) == 0 && ch != ' ')
                keyMap[ch] = it++;
        keyMap[' '] = ' ';

        for (auto &ch : message)
            ch = keyMap[ch];
        return message;
    }

    vector<int> shortestAlternatingPaths(int n, vector<vector<int>> &redEdges, vector<vector<int>> &blueEdges)
    {
        vector<vector<int>> redGraph(n);
        vector<vector<int>> blueGraph(n);
        for (const auto &edge : redEdges)
            redGraph[edge[0]].emplace_back(edge[1]);
        for (const auto &edge : blueEdges)
            blueGraph[edge[0]].emplace_back(edge[1]);

        vector<int> res(n, -1);
        vector<uint8_t> visited(n, 0);
        res[0] = 0;
        queue<pair<int, bool>> q;
        q.emplace(0, true);
        q.emplace(0, false);
        for (int step{1}; !q.empty(); ++step)
        {
            for (size_t i{q.size()}; i > 0; --i)
            {
                auto &[node, isRed] = q.front();
                auto &graph = isRed ? redGraph : blueGraph;
                for (const auto &next : graph[node])
                {
                    if (!(visited[next] & (isRed ? 0X02 : 0X01)))
                    {
                        res[next] = min((uint32_t)res[next], (uint32_t)step);
                        q.emplace(next, !isRed);
                        visited[next] |= isRed ? 0X02 : 0X01;
                    }
                }
                q.pop();
            }
        }
        return res;
    }

    bool btreeGameWinningMove(TreeNode *root, int n, int x)
    {
        std::function<size_t(TreeNode *)> getTreeNum = [&getTreeNum](TreeNode *root) noexcept -> size_t
        {
            size_t res{0};
            if (root)
            {
                res = 1;
                res += getTreeNum(root->left);
                res += getTreeNum(root->right);
            }
            return res;
        };

        // dfs find x
        std::function<TreeNode *(TreeNode *)> findX = [&findX, x](TreeNode *root) noexcept -> TreeNode *
        {
            if (root)
            {
                if (root->val == x)
                    return root;
                auto left = findX(root->left);
                if (left)
                    return left;
                return findX(root->right);
            }
            return nullptr;
        };
        auto xNode = findX(root);
        auto leftNum = getTreeNum(xNode->left);
        auto rightNum = getTreeNum(xNode->right);
        auto topNum = n - leftNum - rightNum - 1;
        return max({leftNum, rightNum, topNum}) > n / 2;
    }

    int getMaximumConsecutive(vector<int> &coins)
    {
        sort(coins.begin(), coins.end());
        int res{1};
        for (const auto &coin : coins)
        {
            if (coin > res)
                break;
            res += coin;
        }
        return res;
    }
};
}

/*
auto __FAST_IO__ = []() noexcept
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    return 0;
}() ;
*/

namespace JianZhiOffer
{

class Solution
{
    /**
     * @brief 
     * 
     * @param nums 
     * @return int 
     */
    int findRepeatNumber(vector<int> &nums)
    {
        unordered_set<int> numSet;
        for (auto &i : nums)
        {
            if (numSet.count(i))
                return i;
            else
                numSet.insert(i);
        }
        return -1;
    }

    bool findNumberIn2DArray(vector<vector<int>> &matrix, int target)
    {
        if (matrix.size() < 1)
            return false;

        auto x_size = matrix.size();
        auto y_size = matrix[0].size();

        size_t it[2]{0, y_size - 1};

        while (it[0] >=0 && it[0] < x_size && it[1] >= 0 && it[1] < y_size && matrix[it[0]][it[1]] != target)
        {
            if (matrix[it[0]][it[1]] > target)
                --it[1];
            else
                ++it[0];
        }

        return it[0] >= 0 && it[0] < x_size && it[1] >= 0 && it[1] < y_size;
    }

    string replaceSpace(string &s)
    {
        std::regex reg(" ");
        return std::regex_replace(s,reg,"%20");
    }

    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
    };

    
    
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
     

    vector<int>& reversePrint(ListNode *head)
    {
        if (head)
        {
            auto &res = reversePrint(head->next);
            res.emplace_back(head->val);
            return res;
        }
        else
            return *(new vector<int>);
    }

    TreeNode *buildTree(vector<int> &_preorder, vector<int> &_inorder)
    {
        struct vector_viewer
        {
            size_t begin{};
            size_t end{};
        };

        function<TreeNode *(vector_viewer, vector_viewer)> core = [&](vector_viewer preorder, vector_viewer inorder)
        {
            auto res = new TreeNode(_preorder[preorder.begin]);

            size_t resIndex{UINT64_MAX};
            for (auto it{inorder.begin}; it < inorder.end; ++it)
            {
                if (_inorder[it] == res->val)
                {
                    resIndex = it;
                    break;
                }
            }

            auto leftNums = resIndex - inorder.begin;
            auto rightNums = inorder.end - resIndex - 1;

            if (leftNums > 0)
                res->left = core({preorder.begin + 1, preorder.begin + 1 + leftNums}, {inorder.begin, resIndex});
            if (rightNums > 0)
                res->right = core({preorder.begin + 1 + leftNums, preorder.end}, {resIndex + 1, inorder.end});
            return res;
        };

        return core({0, _preorder.size()}, {0, _inorder.size()});

    }

    class CQueue
    {
        stack<int> m_dataStack;
        stack<int> m_popStack;
    public:
        CQueue()
        {
        }

        void appendTail(int value)
        {
            m_dataStack.push(value);
        }

        int deleteHead()
        {
            if (!m_popStack.empty())
            {
                auto res = m_popStack.top();
                m_popStack.pop();
                return res;
            }
            else if (!m_dataStack.empty())
            {
                while (!m_dataStack.empty())
                {
                    m_popStack.push(m_dataStack.top());
                    m_dataStack.pop();
                }
                auto res = m_popStack.top();
                m_popStack.pop();
                return res;
            }
            else
                return -1;

        }
    };

    int numWays(int n)
    {
        if (n <= 2)
            return n;
        vector<int> dp(n);
        dp[0] = 1;
        dp[1] = 2;
        for (int i{2}; i < n; ++i)
            dp[i] = (dp[i - 1] + dp[i - 2]) % 1000000007;
        return dp[n - 1];
    }

    int minArray(vector<int> &numbers)
    {
        int l = 0, r = numbers.size() - 1;
        int mid = (r - l) / 2 + l;

        while (r > l)
        {
            if (numbers[mid] < numbers[r])
                r = mid;
            else if (numbers[mid] > numbers[r])
                l = mid + 1;
            else
                --r;
            mid = (r - l) / 2 + l;
        }

        return numbers[l];
    }

    bool exist(vector<vector<char>> &board_raw, string &word)
    {
        auto board = board_raw;
        function<bool(int x, int y, string::iterator wordIt)> bfs = [&](int x, int y, string::iterator wordIt)
        {
            if (x >= board.size() || y >= board[0].size() || x < 0 || y < 0)
                return false;
            if (board[x][y] != *wordIt)
                return false;
            auto tmp = board[x][y];
            board[x][y] = 0;
            if (wordIt == word.end() - 1)
                return true;
            ++wordIt;
            if (bfs(x + 1, y, wordIt) || bfs(x, y + 1, wordIt) || bfs(x - 1, y, wordIt) || bfs(x, y - 1, wordIt))
                return true;
            board[x][y] = tmp;
            return false;
        };

        for (int x{}; x < board_raw.size(); ++x)
            for (int y{}; y < board_raw[0].size(); ++y)
                if (board_raw[x][y] == word.front())
                {
                    if (bfs(x, y, word.begin()))
                        return true;
                    else
                        board = board_raw;
                }

        return false;
    }

    int movingCount(int m, int n, int k)
    {
        auto fun = [](int num)
        {
            int res{};
            while (num)
            {
                res += num % 10;
                num /= 10;
            }
            return res;
        };

        vector<vector<int8_t>> tab(m, vector<int8_t>(n));
        tab[0][0] = 1;

        int res{1};
        for (int i{}; i < m; ++i)
        {
            for (int j{}; j < n; ++j)
            {
                if (i + j == 0 || fun(n) + fun(m) > k)
                    continue;
                if (i - 1 > 0)
                    tab[i][j] |= tab[i - 1][j];
                if (j - 1 > 0)
                    tab[i][j] |= tab[i][j - 1];
                if (tab[i][j])
                    ++res;
            }
        }
        return res;

    }

    int cuttingRope(int n)
    {
        if (n == 2)
            return 1;
        if (n == 3)
            return 2;

        int _3powNums = n / 3;
        int _residue = n % 3;
        if (_residue == 1)
        {
            --_3powNums;
            _residue = 4;
        }
        return (int)pow(3, _3powNums) * (_residue == 0 ? 1 : _residue);
    }

    int cuttingRopePro(int n)
    {
        if (n == 2)
            return 1;
        if (n == 3)
            return 2;

        int _3powNums = n / 3;
        int _residue = n % 3;
        if (_residue == 1)
        {
            --_3powNums;
            _residue = 4;
        }

        uint64_t res{1};
        for (int i{}; i < _3powNums; ++i)
        {
            res *= 3;
            res %= 1000000007;
        }
        res *= (_residue == 0 ? 1 : _residue);
        res %= 1000000007;
        return res;
    }

    int hammingWeight(uint32_t n)
    {
        return __builtin_popcount(n);
    }

    class MovingAverage
    {
        const int m_ciSize;
        queue<int> m_q{};
        int m_iSum{0};

    public:
        /** Initialize your data structure here. */
        MovingAverage(int size) : m_ciSize(size)
        {
        }

        double next(int val)
        {
            m_q.push(val);
            m_iSum += val;
            if (m_q.size() > m_ciSize)
            {
                m_iSum -= m_q.front();
                m_q.pop();
            }
            return (double)m_iSum / (double)m_q.size();
        }
    };

    double myPow(double x, int n)
    {
        if (x == 0.0)
            return 0.0;
        if (n == 0)
            return 1;
        if (n == 1)
            return x;
        if (n > 0)
        {
            auto tmp = x;
            return myPow(x * x, n / 2) * ((n & 1) ? x : 1);
        }
        else
            return 1 / myPow(x, -n);
    }

    vector<int> printNumbers(int n)
    {
        size_t size = pow(10, n) - 0.5;
        vector<int> res(size);
        int i{0};
        for (auto &it : res)
            it = ++i;
        return res;
    }

    ListNode *deleteNode(ListNode *head, int val)
    {
        if (head->val == val)
            return head->next;
        auto it = head;
        while (it->next && it->next->val != val)
        {
            it = it->next;
        }
        if (it->next)
            it->next = it->next->next;
        return head;
    }

    vector<int> exchange(vector<int> &nums)
    {
        auto specifyQsort = [](vector<int>::iterator left, vector<int>::iterator right)
        {
            --right;
            auto tmp = *right;
            while (left < right)
            {
                while (left < right && *left & 1)
                    ++left;
                *right = *left;
                while (left < right && !(*right & 1))
                    --right;
                *left = *right;
            }
            *right = tmp;
        };
        specifyQsort(nums.begin(), nums.end());
        return nums;
    }

    bool isMatch(string s, string p)
    {
        std::regex reg{p};
        return std::regex_match(s,reg);
    }

    bool isNumber(string &s)
    {
        std::regex num1(R"((\s*[+-]?(\.)?[0-9]+([Ee][+-]?[0-9]+)?\s*)|(\s*[+-]?[0-9]+(\.[0-9]*)?([Ee][+-]?[0-9]+)?\s*))");
        return std::regex_match(s, num1);
    }

    ListNode *reverseList(ListNode *head)
    {
        auto makeNode = [](int val, ListNode *next)
        {
            ListNode *node = new ListNode(val);
            node->next = next;
            return node;
        };
        ListNode *node = new ListNode(head->val);
        while (head->next)
        {
            head = head->next;
            node = makeNode(head->val, node);
        }
        return node;
    }

    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
        if (l1 == nullptr || l2 == nullptr)
            return (ListNode*)((uint64_t)l1 + (uint64_t)l2);
        ListNode *root;
        if (l1->val > l2->val)
        {
            root = l2;
            l2 = l2->next;
        }
        else
        {
            root = l1;
            l1 = l1->next;
        }
        auto it = root;
        while (l1 && l2)
        {
            if (l1->val > l2->val)
            {
                it->next = l2;
                l2 = l2->next;
            }
            else
            {
                it->next = l1;
                l1 = l1->next;
            }
            it = it->next;
        }
        if (l1)
            it->next = l1;
        else if (l2)
            it->next = l2;
        return root;
    }

    bool isSubStructure(TreeNode *A, TreeNode *B)
    {
        if (!B)
            return false;
        auto sameStruct = [&B](TreeNode *root) -> bool
        {
            function<bool(TreeNode *, TreeNode *)> dfs = [&](TreeNode *it, TreeNode *b) -> bool
            {
                if (b == nullptr)
                    return true;
                if (it == nullptr)
                    return false;
                if (b->val != it->val)
                    return false;
                return dfs(it->left, b->left) && dfs(it->right, b->right);
            };
            return dfs(root, B);
        };

        function<bool(TreeNode *)> dfs = [&B, &sameStruct, &dfs](TreeNode *node)
        {
            if (!node)
                return false;
            if (node->val == B->val && sameStruct(node))
                return true;
            return dfs(node->left) || dfs(node->right);
        };

        return dfs(A);
    }

    TreeNode *mirrorTree(TreeNode *root)
    {
        function<void(TreeNode *)> dfs = [&dfs](TreeNode *node)
        {
            if (!node)
                return;
            dfs(node->left);
            dfs(node->right);
            std::swap(node->left, node->right);
        };

        dfs(root);
        return root;
    }

    bool isSymmetric(TreeNode *root)
    {
        if (!root)
            return true;
        function<bool(TreeNode * node1, TreeNode * node2)> dfs = [&dfs](TreeNode *node1, TreeNode *node2)
        {
            if (!node1 && !node2)
                return true;
            if (!node1 || !node2)
                return false;
            if (node1->val != node2->val)
                return false;
            return dfs(node1->left, node2->right) && dfs(node1->right, node2->left);
        };

        return dfs(root->left, root->right);
    }
    bool checkOnesSegment(string s)
    {
        return std::regex_match(s, std::regex(R"(1+0*)"));
    }

    vector<int> spiralOrder(vector<vector<int>> &matrix)
    {
        constexpr int flag = INT_MAX;
        vector<int> res;
        res.reserve(matrix.size() * matrix.front().size());
        res.emplace_back(matrix[0][0]);
        matrix[0][0] = flag;
        int i = 0, j = 0;
        int direction = 0;
        for (;;)
        {
            switch(direction)
            {
            case 0:
                if (j + 1 < matrix[i].size() && matrix[i][j + 1] != flag)
                {
                    res.emplace_back(matrix[i][++j]);
                    matrix[i][j] = flag;
                }
                else
                    ++direction;
                break;
            case 1:
                if (i + 1 < matrix.size() && matrix[i + 1][j] != flag)
                {
                    res.emplace_back(matrix[++i][j]);
                    matrix[i][j] = flag;
                }
                else
                    ++direction;
                break;
            case 2:
                if (j - 1 >= 0 && matrix[i][j - 1] != flag)
                {
                    res.emplace_back(matrix[i][--j]);
                    matrix[i][j] = flag;
                }
                else
                    ++direction;
                break;
            case 3:
                if (i - 1 >= 0 && matrix[i - 1][j] != flag)
                {
                    res.emplace_back(matrix[--i][j]);
                    matrix[i][j] = flag;
                }
                else
                    direction = 0;
                break;
            }
            if (res.size() == matrix.size() * matrix.front().size())
                return res;
        }
    }

    class MinStack
    {
    public:
        MinStack() = default;

        void push(int x)
        {
            st.push(x);
            if (minSt.empty() || x <= minSt.top())
                minSt.push(x);
        }

        void pop()
        {
            if (st.top() == minSt.top())
                minSt.pop();
            st.pop();
        }

        int top()
        {
            return st.top();
        }

        int min()
        {
            return minSt.top();
        }

    private:
        std::stack<int> st{};
        std::stack<int> minSt{};
    };

    bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
    {
        std::stack<int> st{};
        auto pushIt = pushed.begin();
        auto popIt = popped.begin();
        while(pushIt != pushed.end())
        {
            if (*pushIt == *popIt)
            {
                ++popIt;
                while (!st.empty() && st.top() == *(popIt))
                {
                    st.pop();
                    ++popIt;
                }
                
            }
            else
                st.push(*pushIt);
            ++pushIt;
        }
        return st.empty();
    }
};
}


/*
auto __FAST_IO__{ []() noexcept
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    return 0;
}() };
*/
