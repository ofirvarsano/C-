#ifndef _GRAPH_ALGORITHM_
#define _GRAPH_ALGORITHM_

#include "graph.hpp"
#include <queue>

namespace experis {

typedef std::string VertexId;
typedef typename std::vector<Edge>::iterator neighborsItr;
typedef typename std::list<VertexId>::iterator idIter;
	
bool Bfs(const Graph& a_graph, const Vertex& a_from, const Vertex& a_to, std::vector<Vertex>& a_path) {
	std::queue<Vertex> que;
	std::list<VertexId> visited;
	
	que.push(a_from);
	//a_path.push_back(a_from);
    visited.push_back(a_from.GetId());
	
	while(!que.empty()) {
        Vertex& next = que.front();
        que.pop();
        if(next.GetId() == a_to.GetId()) {
            return true;
        }
		
		std::vector<Edge> neighbors = next.GetEdges();
		
        for(neighborsItr it = neighbors.begin() ; it != neighbors.end() ; ++it) {
            idIter itVisited = find(visited.begin(), visited.end(), it->GetNeighbor().GetId());
            if(itVisited == visited.end()) {
                que.push(it->GetNeighbor());
                visited.push_back(it->GetNeighbor().GetId());
                //a_path.push_back(it->GetNeighbor());
            }
        }
    }
    return false;
}

bool DfsUntil(const Graph& a_graph, const Vertex& a_from, const Vertex& a_to, std::list<VertexId>& a_visited, std::vector<Vertex>& a_path) {
	if(a_from.GetId() == a_to.GetId()) {
        return true;
    }
	
    a_visited.push_back(a_from.GetId());
	
	std::vector<Edge> neighbors = a_from.GetEdges();
	for(neighborsItr it = neighbors.begin() ; it != neighbors.end() ; ++it) {
		idIter itvisited = find(a_visited.begin(), a_visited.end(), it->GetNeighbor().GetId());
        if(itvisited == a_visited.end()) {
            return DfsUntil(a_graph, it->GetNeighbor(), a_to, a_visited, a_path);
        }
	}
    return false;
}

bool Dfs(const Graph& a_graph, const Vertex& a_from, const Vertex& a_to, std::vector<Vertex>& a_path) {	
	std::list<VertexId> visited;

	return DfsUntil(a_graph, a_from, a_to, visited, a_path);
}

} //experis

#endif // _GRAPH_ALGORITHM_
