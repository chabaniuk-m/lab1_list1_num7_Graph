#pragma once
#include <vector>
#include <array>
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
	//компоненти зв'язності
	bool isPlanar(std::vector<Vertex>* v = nullptr) const
	{
		//розбити на компоненти зв'язності
		auto subgraphs{ connectivityComponents(1) };
		for (auto& subgraph : subgraphs)
		{
			if (subgraph.m_vertex.size() >= 6)
			{
				for (auto& sub : subgraph.combinations<6>())
				{
					if (is_bipartity_3_3(sub))
						return false;
				}
			}
			if (subgraph.m_vertex.size() >= 5)
			{
				for (auto& sub : subgraph.combinations<5>())
				{
					//if sub is full graph
					//return false
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

	template <std::size_t N>
	std::vector< std::array<std::array<int, N>, N> > combinations(std::vector<Vertex>* v = nullptr) const
	{

	}
	bool is_bipartity_3_3(const std::array < std::array<int, 6>, 6>& adj) const;
};