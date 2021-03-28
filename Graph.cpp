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

auto Graph::getVertexNumber() const -> size_t
{
	return m_vertex.size();
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

auto Graph::getEdgeNumber() const -> size_t
{
	adj_t v(getSimpleAdj());
	size_t edgesNumber{ 0 };
	for (size_t i = 0; i < v.size() - 1; i++)
	{
		for (size_t j = i + 1; j < v.size(); j++)
		{
			if (v[i][j] != 0)
			{
				++edgesNumber;
			}
		}
	}

	return edgesNumber;
}

// ������� ������� �������� ���������� ���������� ������
std::vector< std::vector<weight_t> > Graph::kruskal() const{
using namespace std;
	size_t V = m_adjacency.size();                  //�-��� ������
	vector< vector<weight_t> > skeletalTree(V);
	vector<int> belong(V);                          // �������, �� �������� ������ �������

	for (int i = 0; i < V; i++)
	{
		skeletalTree[i] = vector<weight_t>(V, 0);
		belong[i] = i;								//�������� V �����
	}

	int A;
	int B;
	int treeEges = 1;
	while (treeEges < V)
	{
		// ������ �������� �����, �� �� ������� ����� � �������� ������� � ����
		weight_t min = UINT_MAX;
		for (size_t i = 0; i < V; i++)
			for (size_t j = 0; j < V; j++)
				if (min > m_adjacency[i][j] && belong[i] != belong[j] && m_adjacency[i][j] != 0) {
					min = m_adjacency[i][j];
					A = i;
					B = j;
				}

		// ���� ������� �� �������� �� ������ ������, ������ ����� �� ���� �� ������
		if (belong[A] != belong[B]) {
			skeletalTree[A][B] = min;
			skeletalTree[B][A] = min;

			// �� ������� ������ B ����� �������� �� ������ A
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

//�������� ����� ������� �� ������� � ����� ���� ��'�����
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

//����� � �������

void Graph::passInDepth() const
{
	std::vector<bool> isVisited(m_vertex.size(), false);
	//���������� �� ���������� ��'������
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

void Graph::passInWidth() const
{
	if (!isConnected())
	{
		std::cout << "���� �� ��'�����! ��������� �������� ����� � ������\n";
		return;
	}
	std::vector< std::vector<index_t> > currentStage;
	std::vector<index_t> previousStage;
	std::vector<bool> isVisited(m_vertex.size(), false);
	previousStage.push_back(0);								//�������� � ����� �������
	isVisited[0] = true;
	currentStage.push_back(previousStage);
	bool empty;
	//������ ��� ���������� �� ������ ����� currentStage
	auto isEmpty{ [](const std::vector< std::vector<index_t> >& passStage) {
		for (std::vector<index_t> i : passStage)
		{
			if (i.size() > 0)
				return false;
		}

		return true; } };
	do
	{
		//�������� �� ������� ����� � ����������
		{
			bool isOutput = false;
			for (auto& k : currentStage)
			{
				if (k.empty())
					continue;
				if (!isOutput)
				{
					std::cout << m_vertex[k[0]].getData();
					isOutput = true;
					for (size_t i = 1; i < k.size(); i++)
						std::cout << " - " << m_vertex[k[i]].getData();
				}
				else
					for (size_t i = 0; i < k.size(); i++)
						std::cout << " - " << m_vertex[k[i]].getData();
			}
			std::cout << "\n";
		}
		//�������� ������ ����� ������� ������
		{
			for (auto& i : currentStage)
			{
				for (auto& j : i)
				{
					previousStage.push_back(j);
				}
			}
			currentStage.clear();
			for (auto& i : previousStage)
			{
				currentStage.push_back(getRelatives(i, isVisited));
			}
		}

		empty = isEmpty(currentStage);
	} 		while (!empty);
}

//�� ��'����� ����

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

bool Graph::isTree() const
{
	//��������� ��'����� ���� � �������, ��� � ����� ���, ���� V - E = 1 (wikipedia)
	return (getEdgeNumber()) == (getVertexNumber() - 1);
}
