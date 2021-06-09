#ifndef _GRAPH_HPP
#define _GRAPH_HPP

#include <iostream>
#include "../hash_table2/hash.hpp"

namespace experis {

typedef std::string VertexId;
class Vertex;
	class Edge;
class Graph {
public:
    typedef experis::HashTable<VertexId, Vertex> container;
    
    Graph();
    //~Graph() = default;
    //Graph(const Graph&) = default;
    //Graph& operator=(const Graph&) = default;
    
	Vertex& AddVertex(const VertexId& a_name); //throws std::invalid_argument exeption if Vertex not found
	void AddEdge(Vertex& a_vertex, Vertex& a_neighbor, double a_weigth = 1);  //throws std::invalid_argument 
    const Vertex& GetVertex(const VertexId& a_vertexId) const;
	Vertex& GetVertex(const VertexId& a_vertexId);
    
    bool AreConnected(const Vertex& a_v1, const Vertex& a_v2) const;
    size_t NumOfVertex() const { return m_numOfVertex; }
    
private:
	container m_vertexContainer;
	size_t m_numOfVertex;
};

class Vertex {
public:
	typedef std::vector<Edge> Vec;
	friend class Graph;
	
	size_t GetNumEdges() const { return m_numEdges; }
	const VertexId& GetId() const { return m_id; }
	const VertexId& SetId(const VertexId& a_name) { m_id = a_name; }
	const Vec GetEdges() const { return m_edges; }
	Vec GetEdges() { return m_edges; }
	void AddEdge(Vertex& a_vertex, Vertex& a_neighbor, double a_weigth);
	bool IsConnectedTo(const Vertex& a_vertex) const;
	
	//~Vertex = default;
	//Vertex(const Vertex&) = default;
	//Vertex& operator=(const Vertex&) = default;
	
private:
	Vertex(const VertexId& a_name);
	VertexId m_id;
	Vec m_edges;
	size_t m_numEdges;
};

class Edge {
public:
	friend class Vertex;
	
	Edge(const Vertex& a_vertex, const Vertex& a_neighbor, double a_weigth);
	//~Edge = default;
	//Edge(const Edge&) = default;
	//Edge& operator=(const Edge&) = default;
	
	double GetWeigth() const { return m_weigth; }
	const Vertex& GetVertex() const { return m_v1; }
	const Vertex& GetNeighbor() const { return m_v2; }
private:
	double m_weigth;
	const Vertex& m_v1;
	const Vertex& m_v2;
};

Edge::Edge(const Vertex& a_vertex, const Vertex& a_neighbor, double a_weigth)
	: m_v1(a_vertex)
	, m_v2(a_neighbor)
	, m_weigth(a_weigth)
{}

Vertex::Vertex(const VertexId& a_name)
: m_id(a_name)
, m_edges()
, m_numEdges(0)
{}

} //experis

#include "graph_inl.hpp"

#endif // _GRAPH_HPP

