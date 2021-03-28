#include "Graph.h"
#include <iomanip>

void Graph::addVertex(Vertex&& vertex)
{
	m_vertex.push_back(vertex);

	if (m_adjacency.size() == 0)
	{
		m_adjacency.push_back(std::vector<weight_t>({ 0 }));
	}
	else
	{
		for (std::vector<weight_t>& k : m_adjacency)
		{
			k.push_back(0);
		}

		m_adjacency.push_back(std::vector<weight_t>(m_adjacency[0].size(), 0));
	}
}

void Graph::addEdge(index_t idx1, index_t idx2, weight_t weight)
{
	m_adjacency[idx1][idx2] = weight;
	m_adjacency[idx2][idx1] = weight;
}

void Graph::showAdjancencyMatrix() const
{
	std::cout << std::left << "   ";

	for (auto& i : m_vertex)
	{
		std::cout << std::setw(3) << i.getData() << " ";
	}

	std::cout << "\n";
	
	for (size_t i = 0; i < m_adjacency.size(); ++i)
	{
		std::cout << std::setw(3) << m_vertex[i].getData();

		for (int j : m_adjacency[i])
		{
			std::cout << std::setw(3) << j << " ";
		}
		std::cout << "\n";
	}
}

// Повертає матрицю суміжності мінімального кістякового дерева
std::vector< std::vector<weight_t> > Graph::kruskal() const{
using namespace std;
	size_t V = m_adjacency.size();                  //к-сть вершин
	vector< vector<weight_t> > skeletalTree(V);
	vector<int> belong(V);                          // позначає, чи належить дереву вершина

	for (int i = 0; i < V; i++)
	{
		skeletalTree[i] = vector<weight_t>(V, 0);
		belong[i] = i;								//спочатку V дерев
	}

	int A;
	int B;
	int treeEges = 1;
	while (treeEges < V)
	{
		// Знайти найлегше ребро, що не утворює циклів і зберегти вершини і вагу
		weight_t min = UINT_MAX;
		for (size_t i = 0; i < V; i++)
			for (size_t j = 0; j < V; j++)
				if (min > m_adjacency[i][j] && belong[i] != belong[j] && m_adjacency[i][j] != 0) {
					min = m_adjacency[i][j];
					A = i;
					B = j;
				}

		// Якщо вершини не належать до одного дерева, додаємо ребро між ними до дерева
		if (belong[A] != belong[B]) {
			skeletalTree[A][B] = min;
			skeletalTree[B][A] = min;

			// Усі вершини дерева B тепер належать до дерева A
			int temp = belong[B];
			belong[B] = belong[A];
			for (int k = 0; k < V; k++)
				if (belong[k] == temp)
					belong[k] = belong[A];

			treeEges++;
		}
	}

	return skeletalTree;
}

//виводимо кожну вершину та вершини з якими вона зв'язана
void Graph::show() const
{
	for (size_t i = 0; i < m_vertex.size(); i++)
	{
		std::cout << m_vertex[i].getData() << " -\n";

		for (size_t j = 0; j < m_adjacency[i].size(); j++)
		{
			if (m_adjacency[i][j] > 0)
			{
				std::cout << "-> " << m_vertex[j].getData() << " (" << m_adjacency[i][j] << ")" << "\n";
			}
		}
	}
}

//обхід у глибину

void Graph::passInDepth() const
{
	std::vector<bool> isVisited(m_vertex.size(), false);
	//перебираємо усі компоненти зв'язності
	for (index_t i = 0; i < isVisited.size(); ++i)
	{
		if (isVisited[i] == false)
		{
			isVisited[i] = true;
			std::cout << m_vertex[i].getData();
			passDepth(isVisited, i);
			std::cout << "\n";
		}
	}
}

//чи зв'язний граф

bool Graph::isConnected() const
{
	std::vector<bool> isVisited(m_vertex.size(), false);

	passDepth(isVisited, 0, false);

	for (bool i : isVisited)
	{
		if (i == false)
			return false;
	}

	return true;
}
