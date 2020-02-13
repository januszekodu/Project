#pragma once
#include <string>
#include "Graphviz.h"

namespace Graphviz
{
	void GenGraph()
	{
		system("dot -Tjpg graph.dot -o graph.jpg"); //generowanie grafu na pomoc¹ GraphViz
	}

	void OpenGraph()
	{
		system("graph.jpg"); //wyœwietlenie pliku .jpeg z grafem
	}
}