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

//����� ���������� ��'������ � ������� �� ����� ��� ���

void Graph::passDepth(std::vector<bool>& isVisited, index_t i, bool isOutput) const
{
	for (index_t j = 0; j < isVisited.size(); ++j)
	{
		if (m_adjacency[i][j] != 0 && isVisited[j] == false)
		{
			isVisited[j] = true;

			if (isOutput)
			{
				std::cout << " - " << m_vertex[j].getData();
				passDepth(isVisited, j);
			}
			else
				passDepth(isVisited, j, false);
		}
	}
}

//��������� ��� �� ����� ������� �������

auto Graph::getSimpleAdj() const -> adj_t
{
	adj_t simpleAdj;
	size_t V = m_adjacency.size();
	for (size_t i = 0; i < V; i++)
	{
		simpleAdj.push_back(std::vector<weight_t>(V, 0));
	}
	for (size_t i = 0; i < V; i++)
	{
		for (size_t j = i; j < V; j++)
		{
			simpleAdj[i][j] = m_adjacency[i][j];
		}
	}

	return simpleAdj;
}

//~~~�������� ��������� ������~~~

auto Graph::showMatrix(const adj_t& matrix) const -> void
{
	for (std::vector<weight_t> i : matrix)
	{
		for (bool j : i)
		{
			std::cout << j << " ";
		}
		std::cout << "\n";
	}
}

//��������� ������� ����� � �, ����� �� �� �������

auto Graph::getRelatives(index_t i, std::vector<bool>& isVisited) const -> std::vector<index_t>
{
	std::vector<index_t> relatives;
	for (index_t j = 0; j < isVisited.size(); j++)
	{
		if (m_adjacency[i][j] != 0 && isVisited[j] == false)
		{
			isVisited[j] = true;
			relatives.push_back(j);
		}
	}

	return relatives;
}

//�������� �-��� ��'������ ������ connected

void Graph::countConnected(std::vector<bool>& isVisited, index_t i, index_t& connected) const
{
	//����� � �������
	for (index_t j = 0; j < isVisited.size(); j++)
	{
		if (isVisited[j] == false && m_adjacency[i][j] != 0)
		{
			isVisited[j] = true;
			++connected;
			countConnected(isVisited, j, connected);
		}
	}
}

auto Graph::getNumConnected(std::vector<bool>& isVisited) const -> index_t
{
	for (size_t i = 0; i < isVisited.size(); i++)
	{
		if (isVisited[i] == false)
		{
			isVisited[i] = true;
			index_t connected{ 1 };
			countConnected(isVisited, i, connected);
			return connected;
		}
	}

	return static_cast<index_t>(0);
}

auto Graph::getDegree(const int idx) const -> int
{
	assert(0 <= idx && idx < m_vertex.size());

	int degree{ 0 };
	for (auto& i : m_adjacency[idx])
	{
		if (i != 0)
			++degree;
	}

	return degree;
}

bool Graph::is_bipartity_3_3(std::vector<Vertex>* badsub) const
{
	if (m_vertex.size() != 6 || getEdgeNumber() != 9) return false;

	//����� ������ ��������� 3 �����
	std::array<bool, 6> isVisited{};
	isVisited[0] = true;
	for (index_t i = 1; i < 6; ++i)
		if (m_adjacency[0][i] != 0)
			isVisited[i] = true;

	std::vector< index_t> remained;
	for (index_t i = 0; i < 6; ++i)
	{
		if (isVisited[i] == false)
		{
			remained.push_back(i);
		}
	}

	//������ ������ �� ���� ��������� 3 �����
	if (remained.size() != 2) return false;

	// ��������� 2 ������� �� ����������
	if (m_adjacency[remained[0]][remained[1]] != 0) return false;

	badsub = new std::vector<Vertex>(m_vertex);

	return true;
}

template<index_t N>
std::vector<Graph> Graph::combinations() const
{
	std::array<int, N> arr;
	std::vector< std::array<int, N> > verteces_combs;
	struct Choose {
		vertex_t vertex;
		void comb(std::vector< std::array<int, N> >& verteces_combs, std::array<int, N>& arr, index_t arr_idx = 0, index_t vert_idx = 0)
		{
			if (arr_idx == N)
			{
				verteces_combs.push_back(arr);
				return;
			}
			//���� �-��� ������ ��� ������ >= �-��� ������ �� ���������� � �����
			for (; vertex.size() - vert_idx >= N - arr_idx && vert_idx < vertex.size(); ++vert_idx)
			{
				arr[arr_idx] = vert_idx;
				comb(verteces_combs, arr, arr_idx + 1, vert_idx + 1);
			}
		}
	}choose;
	choose.vertex = m_vertex;
	choose.comb(verteces_combs, arr);

	std::vector<Graph> subgraphs;
	vertex_t verts;
	adj_t adj(N, std::vector<weight_t>(N, 0));

	for (auto& arr : verteces_combs)									 //���������� �� ��������� ������
	{
		for (index_t j = 0, arr_j = 0; arr_j < N && j < m_vertex.size(); j++)
		{
			if (arr[arr_j] == j)
			{
				verts.push_back(m_vertex[j]);

				for (index_t k = 0, arr_k = 0; arr_k < N && k < m_vertex.size(); k++)
				{
					if (arr[arr_k] == k)
					{
						adj[arr_j][arr_k] = m_adjacency[j][k];
						arr_k++;
					}
				}
				arr_j++;
			}
		}

		subgraphs.push_back(Graph(adj, verts));
	}

	return subgraphs;
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
		std::cout << "���� �� ��'�����! ��������� �������� ����� � ������.\n";
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


//�� � ���������

bool Graph::isAcyclic() const
{
	std::vector<index_t> v;							//�-��� ������ � ����� ��������� ��'������
	std::vector<bool> isVisited(m_vertex.size(), false);


	index_t temp{};
	while ((temp = getNumConnected(isVisited)) != 0)
	{
		v.push_back(temp);
	}

	index_t edgesNumber{ 0 };
	for (auto& i : v)
	{
		edgesNumber += i - 1;
	}

	return edgesNumber == getEdgeNumber();
}

//�� � ������ ������

bool Graph::isEulerGraph() const
{
	for (size_t i = 0; i < m_vertex.size(); i++)
	{
		//���� ���� ��������� ��� � ����� ��� ���� ������ ����� ������� �����
		if (getDegree(i) % 2 != 0)
			return false;
	}

	return true;
}

//�������� �� � ���� ���������

bool Graph::isPlanar(std::vector<Vertex>* badsub) const				//�������� ���� �� ����������
{
	//������� �� ���������� ��'������
	for (auto& subgraph : connectivityComponents(1))
	{
		if (subgraph.m_vertex.size() >= 6)
		{
			for (auto& sub : subgraph.combinations<6>())
			{
				if (sub.is_bipartity_3_3(badsub))
					return false;
			}
		}
		if (subgraph.m_vertex.size() >= 5)
		{
			for (auto& sub : subgraph.combinations<5>())
			{
				if (sub.getEdgeNumber() == 10)
				{
					badsub = new std::vector<Vertex>(sub.m_vertex);
					return false;
				}
			}
		}
	}

	return true;
}

auto Graph::connectivityComponents() const -> size_t
{
	std::vector<bool> isVisited(m_vertex.size(), false);
	size_t count{ 0 };
	//���������� �� ���������� ��'������
	for (index_t i = 0; i < isVisited.size(); ++i)
	{
		if (isVisited[i] == false)
		{
			isVisited[i] = true;
			std::cout << "���������� ��'������ " << ++count << ": " << m_vertex[i].getData();
			passDepth(isVisited, i);
			std::cout << "\n";
		}
	}

	return count;
}

//������� �-��� ��������� ��'������

auto Graph::connectivityComponents(int) const -> std::vector<Graph>
{
	std::vector<bool> isVisited(m_vertex.size(), false);
	auto fir{
		[&isVisited]()
		{
			for (index_t i = 0; i < isVisited.size(); i++)
			{
				if (isVisited[i] == false)
				{
					isVisited[i] = true;
					return i;
				}
			}
			return (static_cast<index_t>(-1));
	}
	};
	std::vector<Graph> res;
	while (true)
	{
		std::vector<index_t> connected;					//������ ������� ��'������ �� ����� ������
		connected.push_back(fir());
		if (connected[0] == static_cast<index_t>(-1))
			break;									//������� �� ���������� ��'������
		else
		{
			//��������� ���� ��
			for (index_t i = 0; i < connected.size(); i++)
			{
				for (index_t j = 0; j < m_vertex.size(); j++)
				{
					if (m_adjacency[connected[i]][j] != 0 && isVisited[j] == false)
					{
						isVisited[j] = true;
						connected.push_back(j);
					}
				}
			}
			std::sort(connected.begin(), connected.end());
			//������� �������� ��� ���� ��
			adj_t adj(connected.size(), std::vector<weight_t>(connected.size(), 0));
			for (index_t i = 0, row = 0; i < m_vertex.size(); i++)
			{
				if (row >= connected.size())
					break;
				if (connected[row] == i)
				{
					for (size_t j = 0, col = 0; j < m_vertex.size(); j++)
					{
						if (col >= connected.size())
							break;
						if (connected[col] == j)
						{
							adj[row][col] = m_adjacency[i][j];
							col++;
						}
					}
					row++;
				}
			}
			//������� ���� ��
			vertex_t vert;
			for (auto& i : connected)
			{
				vert.push_back(m_vertex[i]);
			}
			res.push_back(Graph(adj, vert));
		}
	}

	return res;
}
