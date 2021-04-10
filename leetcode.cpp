#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <set>
#include <fstream>
using namespace std;
bool cmp(const vector<int> &v, const int &tar)
{
    return v.at(0) < tar;
}

vector<int> *H;

class Solution
{
public:
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
                if ((res > 214748364 || res < -214748364) && x != 0)
                    return 0;
                else if (res == 214748364 && x > 7)
                    return 0;
                else if (res == -214748364 && x < -8)
                    return 0;
            }

            if (x == 0)
                return res;
        }
        return 0;
    }

    int myAtoi(string s)
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
                        res += sign * (ch - '0');
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
                        return res;
                }
                else
                {
                    res *= 10;
                    res += (sign ? 1 : -1) * (ch - '0');
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
            return res;
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
    }

    int maxArea(vector<int> &height)
    {
        int hand_ptr = 0;
        int last_ptr = height.size() - 1;
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

        //     while(num>=1000)
        //     {
        //         res += 'M';
        //         num -= 1000;
        //     }
        //     if(num>=900)
        //     {
        //         res += "CM";
        //         num -= 900;
        //     }
        //     if(num>=500)
        //     {
        //         res += 'D';
        //         num -= 500;
        //     }
        //     if(num>=400)
        //     {
        //         res += "CD";
        //         num -= 400;
        //     }
        //     while(num>=100)
        //     {
        //         res += "C";
        //         num -= 100;
        //     }
        //     if(num>=90)
        //     {
        //         res += "XC";
        //         num -= 90;
        //     }
        //     if(num>=50)
        //     {
        //         res += 'L';
        //         num -= 50;
        //     }
        //     if(num>=40)
        //     {
        //         res += "XL";
        //         num -= 40;
        //     }
        //     while(num>=10)
        //     {
        //         res += "X";
        //         num -= 10;
        //     }
        //     if(num==9)
        //     {
        //         res += "IX";
        //         return res;
        //     }
        //     if(num==4)
        //     {
        //         res += "IV";
        //         return res;
        //     }
        //     if(num>=5)
        //     {
        //         res += 'V';
        //         num -= 5;
        //     }
        //     while(num>=1)
        //     {
        //         res += 'I';
        //         num--;
        //     }

        return res;
    };

    string longestCommonPrefix(vector<string> &strs)
    {
        string res;
        if (strs.size() == 0)
            return res;

        int num = 0;
        while (1)
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
            return vector<vector<int>>();

        sort(nums.begin(), nums.end());

        char index[200000] = {0};
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

    string n2s[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

    void backtracking(string source, vector<string> &date, string temp = string())
    {
        if (source.length() == 0)
        {
            if (!temp.empty())
                date.push_back(temp);
            return;
        }
        for (char ch : n2s[source[0] - '0'])
            backtracking(string(++source.begin(), source.end()), date, temp + ch);
    }

    vector<string> letterCombinations(string digits)
    {
        vector<string> res;
        backtracking(digits, res);
        return res;
    }
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
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
        struct TreeNode
        {
            int val;
            TreeNode *left;
            TreeNode *right;
            TreeNode() : val(0), left(nullptr), right(nullptr) {}
            TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
            TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
        };

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
        auto col = lower_bound(matrix.begin(), matrix.end(), target, &cmp);
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
        const vector<NestedInteger> &getList() const;
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

    vector<int> *Pnums;
    void dfs(set<vector<int>> &res, vector<int> tmp, vector<int>::iterator it)
    {
        if(it==Pnums->end())
            res.insert(tmp);
        else
        {
            dfs(res, tmp, it + 1);
            tmp.push_back(*it);
            dfs(res, tmp, it + 1);
        };
    };
    vector<vector<int>> set2vector(set<vector<int>> s)
    {
        vector<vector<int>> res;
        for (vector<int> tmp:s)
            res.push_back(tmp);
        return res;
    };
    vector<vector<int>> subsetsWithDup(vector<int> &nums)
    {
        Pnums = &nums;
        sort(nums.begin(), nums.end());
        set<vector<int>> res;
        dfs(res, vector<int>(), nums.begin());
        return set2vector(res);
    };

    int clumsy(int N)
    {
        int top_three[4] = { 0, 1, 2, 7 };
        if(N<=3)
            return top_three[N];


        enum Operator{A,S} oper = A;
        int res = N-- * N-- / N--;
        while(N>=1)
        {
            switch(oper)
            {
                case A:
                    res += N--;
                    oper = S;
                    break;
                case S:
                    {
                        int tmp = N--;
                        if(N>=1)
                            tmp *= N--;
                        if(N>=1)
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

    bool static trap_cmp(int l, int r)
    {
        return H->at(l) >= H->at(r);
    };

    int trap(vector<int> &height)
    {
        if (height.size() < 3)
            return 0;

        H = &height;
        vector<int> index;
        index.resize(height.size());
        for (int i = 0; i < height.size(); i++)
            index[i] = i;

        bool (*cmp)(int l, int r) = Solution::trap_cmp;
        sort(index.begin(), index.end(), cmp);

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


    vector<vector<int>> DP;
    string TXT1, TXT2;
    void upDP(int i,int j)
    {
        if(TXT1[i]==TXT2[j])
            DP[i][j] = max(DP[i - 1][j - 1] + 1, max(DP[i - 1][j], DP[i][j - 1]));
        else
            DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);
    };
    int longestCommonSubsequence(string text1, string text2)
    {
        if(text1.size()<=1&&text2.size()<=1)
            return text1[0] == text2[0];
        text1 = " " + text1;
        text2 = " " + text2;
        TXT1 = text1;
        TXT2 = text2;
        DP.resize(text1.size());
        for (int i = 0; i < DP.size();i++)
            DP[i].resize(text2.size());

        for (int i = 0; i < text1.size(); i++)
            DP[i][0] = 1;
        for (int i = 0; i < text2.size(); i++)
            DP[0][i] = 1;

        for (int i = 1; i < text1.size();i++)
            for (int j = 1; j < text2.size();j++)
                upDP(i, j);

        return DP[text1.size() - 1][text2.size() - 1] - 1;
    };

    int removeDuplicates(vector<int> &nums)
    {
        if(nums.size()<=2)
            return 2;
        int res = 2;
        for (int i = 2; i < nums.size();i++)
        {
            if(nums[i]!=nums[res-2])
                nums[res++] = nums[i];
        }
        return res;
    }

    vector<int> NUMS;
    int dich(int l, int r)
    {
        if (NUMS[(l + r) / 2] > NUMS[(l + r) / 2 + 1])
            return NUMS[(l + r) / 2 + 1];
        if (NUMS[(l + r) / 2] > NUMS[r])
            return dich((l + r) / 2, r);
        else
            return dich(l, (l + r) / 2);
    }
    int findMin(vector<int> &nums)
    {
        if(nums.size()<=1)
            return *nums.begin();
        if (*(nums.end() - 1) > *nums.begin())
            return *nums.begin();
        NUMS = nums;
        return dich(0, nums.size() - 1);
    }
};


int main()
{
    cout << Solution().findMin(vector<int>({11,13,15,17}));
    return 0;
}