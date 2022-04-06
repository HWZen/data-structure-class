#include <algorithm>
#include <array>
#include <cmath>
#include <climits>
#ifdef _MSC_VER
#include <corecrt_math_defines.h>
#include <vcruntime.h>
#include <intrin0.inl.h>
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
#include <memory>


#ifdef _MSC_VER
#include <intrin.h>
#define __builtin_popcount __popcnt
#define __builtin_clz __lzcnt
#endif

using namespace std;

class Solution
{
public:
    Solution() = default;

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
            input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) { return !isspace(ch); }));
        }

        void trimRightTrailingSpaces(string &input)
        {
            input.erase(find_if(input.rbegin(), input.rend(), [](int ch) { return !isspace(ch); })
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

    //TODO:
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

        function<void(string, vector<string>&, string)> backtracking = [&](string source, vector<string> & date, string temp)
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
        auto col = lower_bound(matrix.begin(), matrix.end(), target, [](const vector<int> &v, const int &tar) { return v.at(0) < tar; });
        col--;
        return binary_search((*col).begin(), (*col).end(), target);
    };

    class NestedInteger
    {
    public:
        // Return true if this NestedInteger holds a single integer, rather than a nested list.
        bool isInteger() const;

        // Return the single integer that this NestedInteger holds, if it holds a single integer
        // The result is undefined if this NestedInteger holds a nested list
        int getInteger() const;
        // Return the nested list that this NestedInteger holds, if it holds a nested list
        // The result is undefined if this NestedInteger holds a single integer
        [[nodiscard]] const vector<NestedInteger> &getList() const;
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

        function<void(set<vector<int>> &, vector<int>, vector<int>::iterator)> dfs = [&](set<vector<int>> & res, vector<int> tmp, vector<int>::iterator it)
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
        function<void(int,int)> upDP = [&](int i, int j)
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
        sort(index.begin(), index.end(), [&](int left, int right) { return capital[left] < capital[right]; });
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
        function<void(int, int)> upDP = [&](int i, int j) {
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

        function<void(TreeNode * &root, int val)> dfs=[&](TreeNode * &root, int val)
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
        sort(index.begin(), index.end(), [&score](int l, int r) -> bool { return score[l] > score[r]; });
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
            dfs = [&grid, &edge, &dfs, &visited, &m, &n, &originalColor](int x, int y) {
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
        sort(courses.begin(), courses.end(), [](const vector<int> &l, const vector<int> &r) { return l[1] < r[1]; });
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
        function<void(int)> dfs = [&graph, &quiet, &dfs, &ans](int index) {
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
        int small = INT_MAX, mid = INT_MAX;
        for (int i : nums)
        {
            if (i > mid)
                return true;
            if (i < small)
                small = i;
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

    vector<string> uncommonFromSentences(const string& s1, const string& s2)
    {
        unordered_map<string, int> Map;
        auto it_front = s1.begin();
        auto it_back = it_front;
        while (it_back != s1.end())
        {
            if (*(++it_back) == ' ')
            {
                ++Map[move(string(it_front,it_back))];
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
        auto check = [&](int typeNum) {
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
        std::function<void(int, int)> dfs = [&](int height, int weight) {
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
            dfs(height, weight -1);
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

    string pushDominoes(string& dominoes)
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
            int col = j; // ��ĳ�ʼ��??
            for (auto &row : grid)
            {
                int dir = row[col];
                col += dir; // �ƶ���
                if (col < 0 || col == n || row[col] != dir)
                { // �����߻� V ��
                    col = -1;
                    break;
                }
            }
            ans[j] = col; // col >= 0 Ϊ�ɹ�����ײ�??
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
                res+=to_string(*it++)+"/";
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
                    else if(to != -1)
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
        while (num) {
            res += num % 10;
            num/=10;
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
        cnt[0] = {0,0};
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

        void inc(const string& key)
        {
            if (index.count(key))
            {
                index[key]->inc(); 
            }
            else
            {
                if(!index.empty())
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

        void dec(const string& key)
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
            MyList(string &&str, PListNode root = nullptr):_str(str)
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
                if(has_prev_prev)
                    _prev->_prev->_next = this;
                if(_next)
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
            { // key ����������
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
            { // key ������һ�Σ������Ƴ� nodes
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
        sort(words.begin(), words.end(), [](const string &l, const string &r){return l.size() != r.size()? l.size() > r.size() : l < r;});
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
            if(str.empty())
                return ref_str;
        }
        return {};
    }

    class Bank
    {
    public:
        Bank(vector<long long> &balance):size(data.size()), data(std::move(balance)){}

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

        function<int(int, int)> getSteps = [](int curr, int n) {
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

        auto [tab, cnt] = [] () constexpr
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
                    tab[cnt++] =i;
                }
            }
            return pair(tab,cnt);
        }();

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
            // 替换次数和删除次数
            int replace = 0, remove = n - 20;
            // k mod 3 = 1 的组数，即删除 2 个字符可以减少 1 次替换操作
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
                            // 如果是 k % 3 = 0 的组，那么优先删除 1 个字符，减少 1 次替换操作
                            --remove;
                            --replace;
                        }
                        else if (cnt % 3 == 1)
                        {
                            // 如果是 k % 3 = 1 的组，那么存下来备用
                            ++rm2;
                        }
                        // k % 3 = 2 的组无需显式考虑
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

            // 使用 k % 3 = 1 的组的数量，由剩余的替换次数、组数和剩余的删除次数共同决定
            int use2 = min({replace, rm2, remove / 2});
            replace -= use2;
            remove -= use2 * 2;
            // 由于每有一次替换次数就一定有 3 个连续相同的字符（k / 3 决定），因此这里可以直接计算出使用 k % 3 = 2 的组的数量
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
};

/*
int __FAST_IO__ = []()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return 0;
}();
*/
