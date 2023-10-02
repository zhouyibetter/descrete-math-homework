#include <iostream>
#include <map>
#include <unordered_map>
#include <queue>

using namespace std;

const int u_left_move = 10;
const int v_left_move = 0;

// minimum spanning tree
class MST
{
private:
    int vertex_num;
    map<int, int> labeled_edges;                               // <label,edge>
    bool isTherePath(vector<vector<int>> &g, vector<int> deg); // 是否存在圈图
public:
    MST(int _vertex_num, map<int, int> &_labeled_edges) : vertex_num(_vertex_num), labeled_edges(_labeled_edges){};
    bool canMakeSpanningTree(); // 能够构造生成树
    int MinimumSpanningTree();  // 返回最小生成树的权值
    ~MST(){};
};

// 需要知道所有顶点的度（包括出度和入度）
// 根据度进行拓扑排序
/*
 * 1、求出图中所有结点的度。
 * 2、将所有度 == 1 的结点入队。
 * 3、当队列不空时，弹出队首元素，把与队首元素相邻节点的度减一。如果相邻节点的度变为一，则将相邻结点入队。
 * 4、循环结束时判断已经访问的结点数是否等于 n。等于 n 说明全部结点都被访问过，无环；反之，则有环。
 */
bool MST::isTherePath(vector<vector<int>> &g, vector<int> deg)
{
    queue<int> q;
    for (int i = 1; i <= vertex_num; ++i)
    {
        if (deg[i] == 1)
            q.push(i);
    }
    while (!q.empty())
    {
        int vertex = q.front();
        q.pop();
        for (int point : g[vertex])
            if ((--deg[point]) == 1)
                q.push(point);
    }
    for (int i = 1; i <= vertex_num; ++i)
        if (deg[i] > 1)
            return true;
    return false;
};

bool MST::canMakeSpanningTree()
{
    unordered_map<int, bool> hash_vertexs;
    for (auto &mp : labeled_edges)
    {
        int u = (mp.second) >> u_left_move;
        int v = (mp.second) & ((1 << u_left_move) - 1);
        hash_vertexs[u] = true;
        hash_vertexs[v] = true;
    }
    for (int i = 1; i <= vertex_num; ++i)
        if (hash_vertexs[i] == false)
            return false;
    return true;
};

int MST::MinimumSpanningTree()
{
    int weight = 0;
    // Kruskal's algorithm
    vector<vector<int>> g(vertex_num + 1);
    vector<int> deg(vertex_num + 1);
    int edge = 0; // g中存在的边数
    for (auto &mp : labeled_edges)
    {
        int u = (mp.second) >> u_left_move;
        int v = (mp.second) & ((1 << u_left_move) - 1);
        g[u].emplace_back(v);
        g[v].emplace_back(u);
        ++deg[u];
        ++deg[v];
        // 构成圈图，删去新加入的边
        if (isTherePath(g, deg))
        {
            g[u].pop_back();
            g[v].pop_back();
            --deg[u];
            --deg[v];
            continue;
        }
        // 没有构成圈图，更新weight
        weight += mp.first;
        ++edge;
        // g中边数达到 vertext_num-1，形成了最小生成树，直接退出循环
        if (edge == vertex_num - 1)
            break;
    }
    return weight;
};

int main()
{
    int n, m;
    cin >> n >> m;
    map<int, int> mp;
    int u, v, w;
    for (int i = 0; i < m; ++i)
    {
        cin >> u >> v >> w;
        mp[w] = (u << u_left_move) + (v << v_left_move);
    }
    MST *mst = new MST(n, mp);
    if (mst->canMakeSpanningTree())
        cout << mst->MinimumSpanningTree();
    else
        cout << -1;

    return 0;
}
