#pragma once
#include <vector>
#include <array>
#include <cassert>
#include <algorithm>
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
	Graph(const adj_t& adj, const vertex_t& vert) : m_adjacency(adj), m_vertex(vert) {}

	void addVertex(Vertex&& vertex);										//���� �������
	void addEdge(index_t idx1, index_t idx2, weight_t weight = 1);			//���� �����
	auto getVertexNumber() const->size_t;									//�-��� ������
	auto getEdgeNumber() const->size_t;										//�-��� �����
	void show() const;														//��������� �������� ��'���� �� ���������
	auto getVerteces() const ->vertex_t { return m_vertex; }
	auto kruskal() const->adj_t;											//�������� �������� ���������� ������ ������� ��������
	void passInDepth() const;												//����� ����� � �������
	void passInWidth() const;												//����� ����� � ������
	bool isConnected() const;												//�������� ���� �� ��'������ (� ����-��� ������� ���� ���� �� ����-��� ����)
	bool isTree() const;													//�������� �� � ���� ������� (��'����� � ������ �����)
	bool isAcyclic() const;													//�������� �� � ���� ��������� (������ �����)
	bool isEulerGraph() const;												//�������� �� � ���� ���������
	bool isPlanar(std::vector<Vertex>* badsub = nullptr) const;				//�������� ���� �� ����������
	auto connectivityComponents() const->size_t;							//������� �-��� ��������� ��'������
	auto connectivityComponents(int) const->std::vector<Graph>;				//������� ����� ��������� ��'������
	void showAdjancencyMatrix() const;										//�������� �� ����� ������� ��������

private:
	//����� ���������� ��'������ � ������� �� ����� ��� ���
	void passDepth(std::vector<bool>& isVisited, index_t i, bool isOutput = true) const;
	//��������� ��� �� ����� ������� �������
	auto getSimpleAdj() const->adj_t;
	//~~~�������� ��������� ������~~~
	auto showMatrix(const adj_t& matrix) const -> void;
	//��������� ������� ����� � �, ����� �� �� �������
	auto getRelatives(index_t i, std::vector<bool>& isVisited) const->std::vector<index_t>;
	//�������� �-��� ��'������ ������ connected
	void countConnected(std::vector<bool>& isVisited, index_t i, index_t& connected) const;
	auto getNumConnected(std::vector<bool>& isVisited) const->index_t;

	template <index_t N>
	std::vector< Graph > combinations() const;

	auto getDegree(const int idx) const -> int;

	//temp
	public:
		bool is_bipartity_3_3(std::vector<Vertex>* badsub = nullptr) const;
};

//������'����� ������
class LinkedList
{
public:
	struct Node
	{
		int data;
		Node* next = nullptr;

		Node(int v, Node* n = nullptr)
			: data(v), next(n) {}
	};

	void insert(int data)
	{
		head = new Node(data, head);
	}

	Node* head = nullptr;
};

//���� �� ����� ��������� ��������
class LinkedGraph
{
public:
	struct Node
	{
		int row;
		LinkedList list;
		LinkedGraph::Node* next;

		Node(int r, LinkedList l = LinkedList(), LinkedGraph::Node* n = nullptr)
			: row(r), list(l), next(n) {}
	};

	//������� ���� � n ����������� ������
	LinkedGraph(int n = 0);

	auto row(int row) const->Node*;

	Node* first;
	const int count;
};
