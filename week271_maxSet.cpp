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

/*
 * 版本 1：使用 map 保存下标和值，使用 set 分割下标
 * 遍历 map，如果在 set 中插入值成功，则从 map 删除键值对，继续找下一个下标，直到找不到对应下标
 * 根据 set 的大小更新最大值
 * 重复上述循环，直到 map 为空
 */
/*
 *
#include <iostream>
#include <map>
#include <string>
#include <string.h>
#include <algorithm>
#include <set>

using namespace std;

static size_t n=0;
static map<size_t, size_t> numMap;

size_t GetMaxSet()
{
    size_t maxval = 0;
    while(!numMap.empty())
    {
        set<size_t> resSet;
        auto it=numMap.begin();
        while(it != numMap.end())
        {
            if(resSet.insert(it->second).second)
                numMap.erase(it);
            it = numMap.find(it->second);
        }
        maxval = max(maxval, resSet.size());
    }
    return maxval;
}

int main()
{
#define TEST 0
#if TEST
    cin >> n;
    cin.get();

    string strnum;
    getline(cin, strnum);
    strnum += " ";

    size_t cpos = strnum.find(" "), lpos = 0, sum = 0;
    while(cpos != string::npos)
    {
        numMap.emplace(++sum, stoul(strnum.substr(lpos, cpos-lpos)));
        lpos = cpos;
        cpos = strnum.find(" ", cpos+1);
    }
#else
    n = 7;
    int arr[] = {0, 6, 5, 1, 4, 2, 7, 3};
    for(size_t i=1; i<=n; ++i)
        numMap.emplace(i, arr[i]);
#endif
    cout << GetMaxSet() << endl;
    return 0;
}
 */

/*
 * 版本 2：深度遍历，返回树最大深度
 * 遍历 vector，更新下标，访问过就更新下标为 0，访问到 0 代表到达树的叶子节点，返回
 */
#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
#include <set>

using namespace std;

static size_t n=0;
static vector<size_t> numVec;

size_t DFS(size_t index, size_t depth)
{
    if(numVec.at(index) == 0) return depth;
    size_t next = numVec.at(index);
    numVec.at(index) = 0;
    return DFS(next, depth+1);

}

size_t GetMaxSet()
{
    size_t maxval = 0;
    for(size_t i=1; i<=n; ++i) maxval = max(maxval, DFS(i, 0));
    return maxval;
}

int main()
{
#define TEST 1
#if TEST
    cin >> n;
    cin.get();

    numVec.resize(n+1, 0);

    string strnum;
    getline(cin, strnum);
    strnum += " ";

    size_t cpos = strnum.find(" "), lpos = 0, sum = 0;
    while(cpos != string::npos)
    {
        numVec.at(++sum) = stoul(strnum.substr(lpos, cpos-lpos));
        lpos = cpos;
        cpos = strnum.find(" ", cpos+1);
    }
#else
    n = 7;
    numMap.resize(n+1, 0);
    int arr[] = {0, 6, 5, 1, 4, 2, 7, 3};
    numMap = vector<size_t>(arr, arr+n+1);
#endif
    cout << GetMaxSet() << endl;
    return 0;
}
