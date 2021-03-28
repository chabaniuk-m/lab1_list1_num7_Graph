#pragma once
#include <vector>
#include <iostream>

class Vertex;
using index_t = std::uint8_t;						//������� ���� �-��� ������ 
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
	vertex_t m_vertex;														//���� ������ �������
	adj_t m_adjacency;														//������� �������� ��������� ������������� �����
																			//���� = 0 - ����� �� ��������� ������
																			//������ ������� � ������� �������� ������� ������� � ����� ������ m_vertex

public:
	Graph() : m_vertex{}, m_adjacency{} {}
	Graph(adj_t&& adjacency, vertex_t&& vertex) : m_adjacency(adjacency), m_vertex(vertex) {}

	void addVertex(Vertex&& vertex);
	void addEdge(index_t idx1, index_t idx2, weight_t weight = 1);
	auto getVertexNumber() const->size_t;
	auto getEdgeNumber() const->size_t;
	void show() const;
	auto getVerteces() const ->vertex_t { return m_vertex; }
	//�������� ���������� ������ ������� ��������
	auto kruskal() const->adj_t;
	//����� � �������
	void passInDepth() const;
	//����� � ������
	void passInWidth() const;
	//�� ��'����� ����
	bool isConnected() const;
	bool isTree() const;
	//�� � ���������
	bool isAcyclic() const;
	//���������� ��'������
	auto connectivityComponents() const->size_t;
	void showAdjancencyMatrix() const;

private:
	//����� ���������� ��'������ � ������� �� ����� ��� ���
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
	//��������� ��� �� ����� ������� �������
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
	//~~~�������� ��������� ������~~~
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
	//��������� ������� ����� � �, ����� �� �� �������
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
	//�������� �-��� ��'������ ������ connected
	void countConnected(std::vector<bool>& isVisited, index_t i, index_t& connected) const
	{
		//����� � �������
		for (size_t j = 0; j < isVisited.size(); j++)
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
};