#include <kruskal.h>
int main(void){

	int V{}, E{};
	std::cin >> V;
	std::cin >> E;

	Graph g(V, E);

	g.AddEdge(3, 2, 2);

	int mst_wt = g.KruskalMST();

	return 0;
}

