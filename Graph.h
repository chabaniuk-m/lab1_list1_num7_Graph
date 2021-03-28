#pragma once
#include <vector>
#include <iostream>

class Vertex;
using index_t = std::uint8_t;						//������� ���� �-��� ������ 
using weight_t = std::uint32_t;
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
	vertex_t m_vertex;											//���� ������ �������
	adj_t m_adjacency;														//������� �������� ��������� ������������� �����
																			//���� = 0 - ����� �� ��������� ������
																			//������ ������� � ������� �������� ������� ������� � ����� ������ m_vertex

public:
	Graph() : m_vertex{}, m_adjacency{} {}
	Graph(adj_t&& adjacency, vertex_t&& vertex) : m_adjacency(adjacency), m_vertex(vertex) {}

	void addVertex(Vertex&& vertex);
	void addEdge(index_t idx1, index_t idx2, weight_t weight = 1);
	void showAdjancencyMatrix() const;
	auto kruskal() const ->adj_t;
	void show() const;
	auto getVerteces() const ->vertex_t { return m_vertex; }
	//����� � �������
	void passInDepth() const
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
	//���� ���� ��'����� ���� � ������� ������� ����� �������� �� ��� �����
	//����� ����� ����������� ������������� passInDepth()
	//��� �������� ����� ������ �-�� ��������� ��'������
	bool isConnected() const;

private:
	//����� ���������� ��'������
	void passDepth(std::vector<bool>& isVisited, index_t i) const
	{
		for (index_t j = 0; j < isVisited.size(); ++j)
		{
			if (m_adjacency[i][j] != 0 && isVisited[j] == false)
			{
				std::cout << " - " << m_vertex[j].getData();
				isVisited[j] = true;
				passDepth(isVisited, j);
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
	//�������� ��������� ������
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
};