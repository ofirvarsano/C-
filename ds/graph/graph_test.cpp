#include "../mu_test.hpp"
#include "graph.hpp"
#include "graph_algorithm.hpp"

void PrintPath(std::vector<experis::Vertex>& a_path) {
	std::vector<experis::Vertex>::iterator it = a_path.begin();
	std::vector<experis::Vertex>::iterator itEnd = a_path.end();
	for( ; it != itEnd ; ++it) {
		std::cout << it->GetId();
	}
	std::cout << std::endl;
}

UNIT(test_add_vertex)
    experis::Graph g;
    int x = 5;
    experis::Vertex v1 = g.AddVertex("a");
    experis::Vertex v2 = g.AddVertex("b");
    try {
    	experis::Vertex v3 = g.AddVertex("b");
    }
    catch(const std::invalid_argument& ex) {
    	std::cout << ex.what() << std::endl;
    }
    g.AddEdge(v1, v2, 5);
    try {
    	g.AddEdge(v1, v2, 5);
    }
    catch(const std::invalid_argument& ee) {
    	std::cout << ee.what() << std::endl;
    }
    
    experis::Vertex v4 = g.AddVertex("c");
    experis::Vertex v5 = g.AddVertex("d");
    try {
    	experis::Vertex v6 = g.AddVertex("b");
    }
    catch(const std::invalid_argument& ex) {
    	std::cout << ex.what() << std::endl;
    }
    experis::Vertex v7 = g.AddVertex("z");
    g.AddEdge(v1, v5, 5);
    try {
    	g.AddEdge(v2, v4, 5);
    }
    catch(const std::invalid_argument& ee) {
    	std::cout << ee.what() << std::endl;
    }
    std::vector<experis::Vertex> path;
    std::cout << experis::Dfs(g, v1,v4, path) << std::endl;
    //PrintPath(path);
    std::cout << experis::Dfs(g, v1,v7, path) << std::endl;
    std::cout << experis::Bfs(g, v1,v7, path) << std::endl;
    std::cout << experis::Bfs(g, v1,v4, path) << std::endl;
END_UNIT

TEST_SUITE(graph_Test)
    TEST(test_add_vertex)
END_SUITE
