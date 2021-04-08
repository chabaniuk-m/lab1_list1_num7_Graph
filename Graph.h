#pragma once
#include <vector>
#include <array>
#include <cassert>
#include <algorithm>
#include <iostream>

class Vertex;
using index_t = std::uint8_t;						//визначає макс к-сть вершин 
using weight_t = std::uint16_t;
using vertex_t = std::vector<Vertex>;
using adj_t = std::vector < std::vector<weight_t> >;

class Vertex
{
	char m_data;
public:
	Vertex(char&& data): m_data(data) {}

	char getData() const { return m_data; }
};
class Graph
{
	vertex_t m_vertex;														//граф містить вершини
	adj_t m_adjacency;														//матрицю суміжності зваженого неорієнтованого графу
																			//вага = 0 - ребро між вершинами відсутнє
																			//індекс вершини в матриці суміжності відповідає індексу в масиві вершин m_vertex

public:
	Graph() : m_vertex{}, m_adjacency{} {}
	Graph(adj_t&& adjacency, vertex_t&& vertex) : m_adjacency(adjacency), m_vertex(vertex) {}
	Graph(const adj_t& adj, const vertex_t& vert) : m_adjacency(adj), m_vertex(vert) {}

	void addVertex(Vertex&& vertex);
	void addEdge(index_t idx1, index_t idx2, weight_t weight = 1);
	auto getVertexNumber() const->size_t;
	auto getEdgeNumber() const->size_t;
	void show() const;
	auto getVerteces() const ->vertex_t { return m_vertex; }
	//побудова кістякового дерева методом Крускала
	auto kruskal() const->adj_t;
	//обхід у глибину
	void passInDepth() const;
	//обхід у ширину
	void passInWidth() const;
	//чи зв'язний граф
	bool isConnected() const;
	bool isTree() const;
	//чи є ациклічним
	bool isAcyclic() const;
	//чи є графом ейлера
	bool isEulerGraph() const;
	//компоненти зв'язності
	bool isPlanar(std::vector<Vertex> *badsub = nullptr) const
	{
		//розбити на компоненти зв'язності
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
	auto connectivityComponents() const->size_t;
	auto connectivityComponents(int) const->std::vector<Graph>
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
			std::vector<index_t> connected;					//містить індекси зв'язаних між собою вершин
			connected.push_back(fir());
			if (connected[0] == static_cast<index_t>(-1))
				break;									//відвідали всі компоненти зв'язності
			else
			{
				//визначаємо комп зв
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
				//матриця суміжності для комп зв
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
				//вершини комп зв
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
	void showAdjancencyMatrix() const;

private:
	//обхід компоненти зв'язності з виводом на екран або без
	void passDepth(std::vector<bool>& isVisited, index_t i, bool isOutput = true) const
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
	//прибираємо все що нижче головної діагоналі
	auto getSimpleAdj() const -> adj_t
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
	//~~~виводимо двовиміний вектор~~~
	auto showMatrix(const adj_t& matrix) const -> void
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
	//непройдені вершини суміжні з А, відмічає їх як пройдені
	auto getRelatives(index_t i, std::vector<bool>& isVisited) const->std::vector<index_t>
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
	//підраховує к-сть зв'язаних вершин connected
	void countConnected(std::vector<bool>& isVisited, index_t i, index_t& connected) const
	{
		//обхід у глибину
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
	auto getNumConnected(std::vector<bool>& isVisited) const -> index_t
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

	template <index_t N>
	std::vector< Graph > combinations() const
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
				//поки к-сть вершин для вибору >= к-сть ячейок що залишилися в масиві
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

		for (auto& arr : verteces_combs)									 //перебираємо всі комбінації вершин
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

	auto getDegree(const int idx) const -> int
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

	//temp
	public:
	bool is_bipartity_3_3(std::vector<Vertex>* badsub = nullptr) const
	{
		if (m_vertex.size() != 6 || getEdgeNumber() != 9) return false;

		//кожній вершині інцидентні 3 ребра
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

		//першій вершині не були інцидентні 3 ребра
		if (remained.size() != 2) return false;

		// досліджуємо 2 вершини що залишилися
		if (m_adjacency[remained[0]][remained[1]] != 0) return false;

		badsub = new std::vector<Vertex>(m_vertex);

		return true;
	}
};