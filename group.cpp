/* 构成群的条件：
 * 1、运算封闭 2、含有单位元 3、每个元素都有逆元
 * D：非负整数集 +：模M加法
 */

/* 一、如何判断是否满足运算的封闭
 *
 */

/* 二、如何判断单位元
 *    如果存在一个元素大于M，就不可能存在单位元
 */

/* 三、确定每个元素的逆元
 *
 */

// 题意不理解的地方  1、元素去重后|D|会产生变化吗？ 我认为会，开发者采取删去的操作
#include <iostream>
#include <set>
#include <map>

using namespace std;

class Group
{
private:
    set<int> s; // 顺序存放元素的集合
    // int identity_element = 0; // 单位元 为0
    int modulo; // 模数
public:
    Group(set<int> &_s, int _modulo) : s(_s), modulo(_modulo){};
    bool IsGroup();
    map<int, int> GetInverse(); // 返回每个元素对应的逆元
    ~Group(){};
};

bool Group::IsGroup()
{
    // 如果最小元素不等于0，这样就不存在单位元，直接返回false
    if (*(s.begin()))
        return false;
    // 如果最大元素大于modulo，这样就不存在单位元，直接返回false
    if (*(--s.end()) >= modulo)
        return false;
    // 判断元素的逆元是否在集合中
    for (int identity : s)
    {
        // 存在找不到逆元的元素，直接返回false
        if (s.find((modulo - identity) % modulo) == s.end())
            return false;
    }
    return true;
};

map<int, int> Group::GetInverse()
{
    map<int, int> inverse_map;
    for (int identity : s)
        inverse_map[identity] = (modulo - identity) % modulo;
    return inverse_map;
};

int main()
{
    // first line input
    int identity;
    set<int> S;
    while (cin >> identity)
    {
        S.insert(identity);
        if (getchar() == '\n')
            break;
    }
    // second line input
    int M;
    cin >> M;
    // 实例化群
    Group *g = new Group(S, M); // 安全起见，如何将集合S的管理权全部交给g呢？ 一种解决办法是，值传递后销毁原集合
    if (g->IsGroup())
    {
        map<int, int> res = g->GetInverse();
        for (auto [identity_1, identity_2] : res)
            cout << identity_1 << " " << identity_2 << endl;
    }
    else
    { // group 不构成群
        cout << -1;
    }

    return 0;
}