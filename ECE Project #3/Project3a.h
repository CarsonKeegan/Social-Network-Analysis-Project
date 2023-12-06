#include "Project3a.cpp"

void addEdge(vector<vector<int>>& adj, int follower, int followed);

void addEdgeForSearch(vector<vector<int>>& adj, int s, int d);

vector<int> findRoot(vector<vector<int>> adj, vector<pair <int, string>> acctPair);

void PrintFollowers(int root, vector<vector<int>> adj, vector<pair<int, string>> acctPair);

