#pragma once
#include <string>
#include "Graphviz.h"

namespace Graphviz
{
	void GenGraph()
	{
		system("dot -Tjpg graph.dot -o graph.jpg");
	}

	void OpenGraph()
	{
		system("graph.jpg");
	}
}