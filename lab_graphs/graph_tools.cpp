/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"
#include <unordered_map>

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    /* Your code here! */
	Vertex a = Vertex();
	Vertex b = Vertex();
	Vertex c = Vertex();
	vector<Vertex> storeV = graph.getVertices();
	vector<Edge> storeE = graph.getEdges();
	for (size_t i = 0; i < storeE.size(); i++)
	{
		a = storeE[i].source;
		b = storeE[i].dest;
		graph.setEdgeLabel(a, b, "UNEXPLORED");
	}
	for (size_t i = 0; i < storeV.size(); i++)
	{
		graph.setVertexLabel(storeV[i], "UNEXPLORED");
	}
	queue<Vertex> traversalq;
	traversalq.push(storeV[0]);
	graph.setVertexLabel(storeV[0], "VISITED");
	vector<Vertex> adjV;
	adjV = graph.getAdjacent(storeV[0]);
	c = storeV[0];
	b = adjV[0];
	int min;
	int temp = 0;
	min = graph.getEdgeWeight(storeV[0], adjV[0]);
	while (!traversalq.empty())
	{
		a = traversalq.front();
		traversalq.pop();
		adjV = graph.getAdjacent(a);
		for (size_t j = 0; j < adjV.size(); j++)
		{
			if (graph.getVertexLabel(adjV[j]) == "UNEXPLORED")
			{
				graph.setEdgeLabel(a, adjV[j], "DISCOVERY");
				graph.setVertexLabel(adjV[j], "VISITED");
				traversalq.push(adjV[j]);
				temp = graph.getEdgeWeight(a, adjV[j]);
				if (temp < min)
				{
					min = temp;
					b = adjV[j];
					c = a;
				}
			}
			else if (graph.getEdgeLabel(a, adjV[j]) == "UNEXPLORED")
			{
				graph.setEdgeLabel(a, adjV[j], "CROSS");
				temp = graph.getEdgeWeight(a, adjV[j]);
				if (temp < min)
				{
					min = temp;
					b = adjV[j];
					c = a;
				}
			}
		}
	}
	graph.setEdgeLabel(b, c, "MIN");
	return min;
	
//    return -1;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    /* Your code here! */
	Vertex a = Vertex();
	Vertex b = Vertex();
	int flag = 0;
	//Vertex c = Vertex();
	vector<Vertex> storeV = graph.getVertices();
	vector<Edge> storeE = graph.getEdges();
	for (size_t i = 0; i < storeE.size(); i++)
	{
		a = storeE[i].source;
		b = storeE[i].dest;
		graph.setEdgeLabel(a, b, "UNEXPLORED");
	}
	for (size_t i = 0; i < storeV.size(); i++)
	{
		graph.setVertexLabel(storeV[i], "UNEXPLORED");
	}
	queue<Vertex> traversalq;
	traversalq.push(start);
	graph.setVertexLabel(start, "VISITED");
	vector<Vertex> adjV;
	adjV = graph.getAdjacent(start);
	std::unordered_map<Vertex, Vertex> findmap;
	while (!traversalq.empty())
	{
		a = traversalq.front();
		traversalq.pop();
		adjV = graph.getAdjacent(a);
		for (size_t j = 0; j < adjV.size(); j++)
		{
			if (graph.getVertexLabel(adjV[j]) == "UNEXPLORED")
			{
				graph.setEdgeLabel(a, adjV[j], "DISCOVERY");
				graph.setVertexLabel(adjV[j], "VISITED");
				traversalq.push(adjV[j]);
				findmap[adjV[j]] = a;
				if (adjV[j] == end)
				{
					flag = 1;
					break;
				}
			}
			else if (graph.getEdgeLabel(a, adjV[j]) == "UNEXPLORED")
				graph.setEdgeLabel(a, adjV[j], "CROSS");
		}
		if (flag == 1)
			break;
	}
	a = start;
	b = end;
	int count = 0;
	while (b != a)
	{
		graph.setEdgeLabel(findmap[b], b, "MINPATH");
		b = findmap[b];
		count++;
	}
	return count;
	
  //  return -1;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    /* Your code here! */
	Vertex a = Vertex();
	Vertex b = Vertex();
	//Vertex c = Vertex();
	unsigned long counter = 0;
	vector<Vertex> storeV = graph.getVertices();
	vector<Edge> storeE = graph.getEdges();
	for (size_t i = 0; i < storeE.size(); i++)
	{
		a = storeE[i].source;
		b = storeE[i].dest;
		graph.setEdgeLabel(a, b, "UNEXPLORED");
	}
	for (size_t i = 0; i < storeV.size(); i++)
	{
		graph.setVertexLabel(storeV[i], "UNEXPLORED");
	}
	std::sort(storeE.begin(), storeE.end(), sorthelper);
	DisjointSets dset = DisjointSets();
	dset.addelements(storeV.size());
	for (size_t i = 0; i < storeE.size(); i++)
		std::cout << graph.getVertexName(storeE[i].source) << "     " << graph.getVertexName(storeE[i].dest) << "\n" << std::endl;
	for (size_t i = 0; i < storeE.size(); i++)
	{
		a = storeE[i].source;
		b = storeE[i].dest;
		//graph.snapshot();
		if (dset.find(a) != dset.find(b))
		{
			dset.setunion(a, b);
			graph.setEdgeLabel(a, b, "MST");
			counter++;
		}
		if (counter >= storeV.size() - 1)
			break;
	}
}

bool GraphTools::sorthelper(Edge a, Edge b)
{
	/*if (a.weight > b.weight)
		return false;
	return true;*/
	return (a.weight < b.weight);
}
