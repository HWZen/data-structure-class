#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;

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

    string intToRoman(int num) {
        string res;
        int M_num = num / 1000;
        num -= 1000 * M_num;
        for (int i = 0; i < M_num;i++)
            res += 'M';
        
        int C_num = num / 100;
        num -= 100 * C_num;
        if (C_num==4)
            res += "CD";
        else if (C_num==9)
            res += "CM";
        else
        {
            if (C_num>=5)
            {
                res += 'D';
                C_num -= 5;
            }
            while(C_num--)
                res += 'C';
        }
        
        int X_num = num / 10;
        num -= 10 * X_num;
        if (X_num==4)
            res += "XL";
        else if (X_num==9)
            res += "XC";
        else
        {
            if (X_num>=5)
            {
                res += 'L';
                X_num -= 5;
            }
            while(X_num--)
                res += 'X';
        }
        
        int I_num = num / 1;
        num -= 1 * I_num;
        if (I_num==4)
            res += "IV";
        else if (I_num==9)
            res += "IX";
        else
        {
            if (I_num>=5)
            {
                res += 'V';
                I_num -= 5;
            }
            while(I_num--)
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

    //     return res;
    // };
};

int main()
{
    // string s;
    // cin >> s;
    // vector<int> temp({1, 8, 6, 2, 5, 4, 8, 3, 7});
    cout << Solution().intToRoman(1994) << endl;
    return 0;
}