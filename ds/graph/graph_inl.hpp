#ifndef _GRAPH_INL_
#define _GRAPH_INL_

#include "graph.hpp"

namespace experis {

typedef experis::Item<VertexId, Vertex> ItemT;
typedef std::vector<Edge> VecEdges;
typedef typename VecEdges::const_iterator VectorCIter;
typedef typename VecEdges::iterator VectorIter;

size_t HashString(const std::string& a_str) {
	return a_str[0];
}

void Vertex::AddEdge(Vertex& a_vertex, Vertex& a_neighbor, double a_weigth) {
	VectorIter itr = m_edges.begin();
	VectorIter itrEnd = m_edges.end();
	
	if(IsConnectedTo(a_neighbor)) {
		throw(std::invalid_argument("Multi edges are not allowed"));
	}
	
    m_edges.push_back(Edge(a_vertex, a_neighbor, a_weigth));
    ++m_numEdges;
}

bool Vertex::IsConnectedTo(const Vertex& a_vertex) const {
	VectorCIter itr = m_edges.begin();
	VectorCIter itrEnd = m_edges.end();
	
	for( ; itr != itrEnd ; ++itr) {
        if(itr->GetNeighbor().GetId() == a_vertex.GetId()) {
            return true;
        }
    }
    return false;
}

Graph::Graph()
: m_vertexContainer(10, HashString)
, m_numOfVertex(0)
{}

Vertex& Graph::AddVertex(const VertexId& a_vertexName) {
    Vertex v(a_vertexName);
    m_vertexContainer.Insert(a_vertexName, v);
    ++m_numOfVertex;
    return m_vertexContainer.Find(a_vertexName);
}

void Graph::AddEdge(Vertex& a_vertex, Vertex& a_neighbor, double a_weigth) {
	a_vertex.AddEdge(a_vertex, a_neighbor, a_weigth);
	a_neighbor.AddEdge(a_neighbor, a_vertex, a_weigth);
}

bool Graph::AreConnected(const Vertex& a_v1, const Vertex& a_v2) const {
	return a_v1.IsConnectedTo(a_v2);
}

const Vertex& Graph::GetVertex(const VertexId& a_vertexId) const {
	return m_vertexContainer.Find(a_vertexId);
}

Vertex& Graph::GetVertex(const VertexId& a_vertexId) {
	return m_vertexContainer.Find(a_vertexId);
}

} // experis

#endif // _GRAPH_INL_

