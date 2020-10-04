#include <stack>
#include <stdio.h>
using namespace std;
/*
https://www.luogu.com.cn/problem/P2947

约翰的N(1≤N≤10^5)头奶牛站成一排，奶牛i的身高是Hi(l≤Hi≤1,000,000)．
现在，每只奶牛都在向右看齐．
对于奶牛i，如果奶牛j满足i<j且Hi<Hj，我们可以说奶牛i可以仰望奶牛j． 
求出每只奶牛离她最近的仰望对象

Input: 

* Line 1: A single integer: N

* Lines 2..N+1: Line i+1 contains the single integer: H_i

Output:

* Lines 1..N: Line i contains a single integer representing the smallest index of a cow up to which cow i looks. If no such cow exists, print 0.


*/
int main()
{
    stack<int> st;
    int N;
    scanf("%d", &N);
    int *arrey;
    int *anser;
    arrey = new int[N + 1];
    anser = new int[N + 1];
    for (int i = 1; i <= N; i++)
        scanf("%d", &arrey[i]);

    for (int i = N; i >= 1; i--)
    {
        while (!st.empty() && arrey[i] >= arrey[st.top()])
            st.pop();

        st.empty() ? anser[i] = 0 : anser[i] = st.top();
        st.push(i);
    }
    for (int i = 1; i <= N; i++)
        printf("%d\n", anser[i]);

    delete[] arrey;
    delete[] anser;

    return 0;
}