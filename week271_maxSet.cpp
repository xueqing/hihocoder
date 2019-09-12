/*
 *
时间限制:10000ms
单点时限:1000ms
内存限制:256MB

描述
给定一个1-N的排列A[1], A[2], ... A[N]，定义集合S[K] = {A[K], A[A[K]], A[A[A[K]]] ... }。
显然对于任意的K=1..N，S[K]都是有限集合。
你能求出其中包含整数最多的S[K]的大小吗？

输入
第一行包含一个整数N。(1 <= N <= 100000)
第二行包含N个两两不同的整数，A[1], A[2], ... A[N]。(1 <= A[i] <= N)

输出
最大的S[K]的大小。

样例输入
7
6 5 1 4 2 7 3
样例输出
4
 */

#include <iostream>
#include <vector>
#include <string>
#include <string.h>

using namespace std;

int n=-1;

int GetMaxSet(vector<int> &numVec)
{
    vector<int> resVec;
    resVec.resize(n, 0);

    for(int i=0, k=i; i<n; i++)
    {
        while(numVec[i] == numVec[k])
        {
            resVec[i]++;
            k = numVec;
        }
    }
}

int main1()
{
    cin >> n;
    cin.get();

    vector<int> numVec;
    numVec.resize(n);

    string strnum;
    getline(cin, strnum);
    strnum += " ";

    size_t cpos = strnum.find(" "), lpos = 0, sum = 0;
    while(cpos != string::npos)
    {
        numVec[sum++] = stoi(strnum.substr(lpos, cpos-lpos));
        lpos = cpos;
        cpos = strnum.find(" ", cpos+1);
    }

    cout << GetMaxSet(numVec) << endl;

    return 0;
}
