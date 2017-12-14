#ifndef KRUSKAL_MST
#define KRUSKAL_MST

#include <bits/stdc++.h>

typedef std::pair<int, int> int_pair;

class Graph {
public :
	int V, E;
	std::vector< std::pair<int, int_pair> > edges;

	Graph(int V, int E){
		this->V = V;
		this->E = E;
	}

	void AddEdge(int u, int v, int w){
		edges.push_back({w, {u, v}});
	}

	int KruskalMST();
};

class DisjointSets {
public :
	int *parent, *height;
	int n;

	DisjointSets(int n){
		this->n = n;
		parent = new int[n+1];
		height = new int[n+1];

		for (int i {0}; i <= n; i++){
			height[i] = 0;
			parent[i] = i;
		}
	}

	int Find(int u){
		if (u != parent[u])
			parent[u] = Find(parent[u]);
		return parent[u];
	}

	void Merge(int x, int y){
		x = Find(x), y = Find(y);

		if (height[x] > height[y])
			parent[y] = x;
		else
			parent[x] = y;

		if (height[x] == height[y])
			height[y]++;
	}
};


int Graph::KruskalMST(){
	int mst_wt {0};

	sort(edges.begin(), edges.end());

	DisjointSets ds(V);

	std::vector< std::pair<int, int_pair> >::iterator it;
	for (it=edges.begin(); it!=edges.end(); it++){
		int u = it->second.first;
		int v = it->second.second;

		int set_u = ds.Find(u);
		int set_v = ds.Find(v);

		if (set_u != set_v){
			std::cout << u << " - " << v << std::endl;
			mst_wt += it->first;
			ds.Merge(set_u, set_v);
		}
	}

	return mst_wt;
}

#endif // KRUSKAL_MST
