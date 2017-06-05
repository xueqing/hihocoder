/*
 *  时间限制:20000ms
    单点时限:2000ms
    内存限制:256MB
    描述
    小Hi最近在分析一支股票的价格走势，他需要一个程序来辅助分析。这个程序会接收3种消息（指令）：

    价格信息，格式是P timestamp price：表示这支股票在 timestamp 时刻价格是 price。

    删除价格指令，格式是R timestamp：随着时间推移，小Hi会积累越来越多的价格数据。一些老旧的数据会变得不重要。这个指定会删除 timestamp 以前（包括 timestamp 时刻）的价格数据。

    价格查询指令，格式是Q：小Hi希望程序返回这只股票最高、最低和最近的价格。注意已经被删除的价格不应该被统计。

    给定一个包含以上3种信息（指令）的序列，你能否帮助小Hi完成这个程序呢？

    输入
    第1行包含一个整数 N (1 ≤ N ≤ 500000)，表示消息（指令）序列的长度。

    第2 - N+1行，每行包含一条消息或指令。

    输入保证价格信息是按照 timestamp 升序排列的，并且出现的 timestamp 和价格小于100000000。

    输出
    对于输入中每一条价格查询指令，输出当时最高、最低和最近的价格。

    样例输入
    10
    P 1 77
    P 2 73
    P 5 70
    P 7 74
    Q
    R 4
    Q
    P 8 78
    R 5
    Q
    样例输出
    77 70 74
    74 70 74
    78 74 78
 */

#include <iostream>
#include <list>
#include <set>
#include <utility>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    list<pair<int, set<int>::iterator> > price;
    multiset<int> prices;

    int n=-1;
    cin >> n;
    cin.get();

    string strCommand;
    char *str, *saveptr;
    int nTime, nPrice;
    while(n--)
    {
        getline(cin, strCommand);
        if(strCommand.at(0) == 'P')
        {
            // warning:strtok uses a static buffer while parsing, so it's not thread safe.  Use strtok_r() instead
//            str = strtok((char*)strCommand.c_str(), " ");
//            nTime = atoi(strtok(NULL, " "));
//            nPrice = atoi(strtok(NULL, " \r\n"));
            str = strtok_r((char*)strCommand.c_str(), " ", &saveptr);
            nTime = atoi(strtok_r(NULL, " ", &saveptr));
            nPrice = atoi(strtok_r(NULL, " \r\n", &saveptr));

//            auto it = prices.insert(nPrice); //c++11
//            price.emplace_back(make_pair(nTime, it)); //c++11

            set<int>::iterator it = prices.insert(nPrice);
            pair<int, set<int>::iterator> timePrice = make_pair(nTime, it);
            price.push_back(timePrice);
        }
        else if(strCommand[0] == 'R')
        {
//            str = strtok((char*)strCommand.c_str(), " ");
//            nTime = atoi(strtok(NULL, " \r\n"));
            str = strtok_r((char*)strCommand.c_str(), " ", &saveptr);
            nTime = atoi(strtok_r(NULL, " \r\n", &saveptr));

            while(price.size()!=0 && price.begin()->first<=nTime)
            {
                prices.erase(price.begin()->second);
                price.erase(price.begin());
            }
        }
        else if(strCommand[0] == 'Q')
        {
            cout << *(prices.rbegin()) << " " << *(prices.begin())
                 << " " << *(price.rbegin()->second) << endl;
        }
    }

    return 0;
}
