#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;

struct Edge {
    int to, capacity, flow;
    Edge(int t, int c) : to(t), capacity(c), flow(0) {}
};

int maxFlow(vector<vector<Edge>>& graph, int source, int sink) {
    int n = graph.size();
    vector<int> parent(n);
    int maxFlow = 0;

    while (true) {
        fill(parent.begin(), parent.end(), -1);
        parent[source] = source;
        queue<pair<int, int>> q;
        q.push({ source, INF });

        while (!q.empty()) {
            int cur = q.front().first;
            int flow = q.front().second;
            q.pop();

            for (Edge& edge : graph[cur]) {
                int to = edge.to;
                if (parent[to] == -1 && edge.capacity - edge.flow > 0) {
                    int newFlow = min(flow, edge.capacity - edge.flow);
                    parent[to] = cur;
                    if (to == sink) {
                        maxFlow += newFlow;
                        int v = sink;
                        while (v != source) {
                            int u = parent[v];
                            for (Edge& e : graph[u]) {
                                if (e.to == v) {
                                    e.flow += newFlow;
                                    break;
                                }
                            }
                            for (Edge& e : graph[v]) {
                                if (e.to == u) {
                                    e.flow -= newFlow;
                                    break;
                                }
                            }
                            v = u;
                        }
                        break;
                    }
                    q.push({ to, newFlow });
                }
            }
        }

        if (parent[sink] == -1) {
            break;
        }
    }

    return maxFlow;
}

int main() {
    int n, m;
    cin >> n >> m;

    // Создаем граф с n вершинами
    vector<vector<Edge>> graph(n);

    // Читаем данные о дугах и пропускных способностях
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; // Вершины нумеруются с 1, но в массиве с 0
        v--;
        graph[u].emplace_back(v, w);
    }

    int source = 0; // Источник
    int sink = n - 1; // Сток

    int maxFlowValue = maxFlow(graph, source, sink);
    cout << maxFlowValue << endl;

    return 0;
}
