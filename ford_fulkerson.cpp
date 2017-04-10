#include <iostream>
#include <limits.h>
#include <string>
#include <queue>

#define V 6

using namespace std;

/*
return true if there is a path from source to sink in residual graph
fills parent[] to store the parth
*/

bool bfs(int Graph[V][V], int s, int t, int parent[]) {
	bool visited[V];
	for(int i = 0; i < V; i++) {
		visited[i] = false;
	}

	//enqueue source vertex and mark source vertex as visited
	queue <int> queue;
	queue.push(s);
	visited[s] = true;
	parent[s] = -1;

	//do a bfs
	while(!queue.empty()) {
		int u = queue.front();
		queue.pop();

		for(int v = 0; v < V; v++) {
			if(!visited[v] && Graph[u][v] > 0) {
				queue.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}

	//return true if we hit the sink after doing bfs from source
	return(visted[t]);
}

//return max flow from source to sink in the given graph
int forkFulkerson(int graph[V][V], int source, int sink) {
	//create a residual graph and fill the residual graph with given
	//capacities in the original graph as residual capacities in residual graph
	int residualG[V][V];

	int u, v;

	for(u = 0; u < V; u++){
		for(int v = 0; v < V; v++) {
			residualG[u][v] = graph[u][v];
		}
	}

	//bfs will fill this array and use it to store path
	int parent[V];
	int maxFlow = 0;

	//augment the flow while there is path from source to sink
	while(bfs(residualG, source, sink, parent)) {
		//find the min residual capacity of the edges along the path filled by bfs 
		int pathFlow = INT_MAX;
		for(v = sink; v != source; v = parent[v]) {
			u = parent[v];
			pathFlow = min(pathFlow, residualG[u][v]);
		}
		//update residual capacities of the edges and reverse edges along the path
		for(v = sink; v != source; v = parent[v]) {
			u = parent[v];
			residualG[u][v] -= pathFlow;
			residualG[v][u] += pathFlow;
		} 
		//add path flow to overflow
		maxFlow += pathFlow;
	}

	return maxFlow;
}


int main() {
	int graph[V][V] = {
		{0,16,13,0,0,0},
		{0,0,10,12,0,0},
		{0,4,0,0,14,0},
		{0,0,9,9,9,20},
		{0,0,0,7,0,4},
		{0,0,0,0,0,0}
	};
cout << "The max possible flow is " << forkFulkerson(graph, 0, 5);
	return 0;
}





















