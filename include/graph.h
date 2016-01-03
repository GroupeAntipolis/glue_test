//
//
//  	G.L.U.E. by M.C.G. 2015 
//
//  	Glue stands for 
// 	Genetically Led Universal Evaluator.
//
// 		Add some glue in your code... 
//

#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "node.h"
#include "node_factory.h"

/** \brief The graph class
*
*	The graph class represents an oriented graph of node objects.
*/
extern "C" class graph
{

	public:
	/// constructor for the graph object
	graph();
	~graph();


	/// node types factory
	node_factory* nfactory;

	/// create inputs outputs and some things
	void initialize(int pinput_width,int poutput_width);

	/// free all those things (like nodes, etc...)
	void uninitialize();

	/// we set the object id of each node
	/// this is usefull before a graph::toArray
	/// call
	void identificate_nodes();

	std::deque<node*> nodes;

	/// iterator fo pointing in graph.nodes list
	std::deque<node*>::iterator node_iterator;
	int input_width;
	int output_width;

	/// returns an array of bytes representing the graph
	byte* toArray(int* size);
	
	/// reify a graph from a byte array
	bool fromArray(byte* parray);
	
	/// clones a graph
	graph* clone();
	
	/// Fast clone will be implemented in future
	graph* fast_clone();

    /// is graph initialized
    bool is_init();


	const static int version=2;

	int min_nodes;
	int max_nodes;

private:

	bool initialized;

};

#endif
