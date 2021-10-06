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

	void addVertex(Vertex&& vertex);										//додає вершину
	void addEdge(index_t idx1, index_t idx2, weight_t weight = 1);			//додає ребро
	auto getVertexNumber() const->size_t;									//к-сть вершин
	auto getEdgeNumber() const->size_t;										//к-сть ребер
	void show() const;														//примітивно відображає зв'язки між вершинами
	auto getVerteces() const ->vertex_t { return m_vertex; }
	auto kruskal() const->adj_t;											//алгоритм побудови кістякового дерева методом Крускала
	void passInDepth() const;												//обхід графа у глибину
	void passInWidth() const;												//обхід графа у ширину
	bool isConnected() const;												//перевіряє граф на зв'язність (з будь-якої вершини існує шлях до будь-якої іншої)
	bool isTree() const;													//перевіряє чи є граф деревом (зв'язний і відсутні цикли)
	bool isAcyclic() const;													//перевіряє чи є граф ациклічним (відсутні цикли)
	bool isEulerGraph() const;												//перевіряє чи є граф ейлеровим
	bool isPlanar(std::vector<Vertex>* badsub = nullptr) const;				//перевіряє граф на планарність
	auto connectivityComponents() const->size_t;							//повертає к-сть компонент зв'язності
	auto connectivityComponents(int) const->std::vector<Graph>;				//повертає масив компонент зв'язності
	void showAdjancencyMatrix() const;										//виводить на екран матрицю суміжності

private:
	//обхід компоненти зв'язності з виводом на екран або без
	void passDepth(std::vector<bool>& isVisited, index_t i, bool isOutput = true) const;
	//прибираємо все що нижче головної діагоналі
	auto getSimpleAdj() const->adj_t;
	//~~~виводимо двовиміний вектор~~~
	auto showMatrix(const adj_t& matrix) const -> void;
	//непройдені вершини суміжні з А, відмічає їх як пройдені
	auto getRelatives(index_t i, std::vector<bool>& isVisited) const->std::vector<index_t>;
	//підраховує к-сть зв'язаних вершин connected
	void countConnected(std::vector<bool>& isVisited, index_t i, index_t& connected) const;
	auto getNumConnected(std::vector<bool>& isVisited) const->index_t;

	template <index_t N>
	std::vector< Graph > combinations() const;

	auto getDegree(const int idx) const -> int;

	//temp
	public:
		bool is_bipartity_3_3(std::vector<Vertex>* badsub = nullptr) const;
};

//однозв'язний список
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

//граф на основі структари суміжності
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

	//створює граф з n ізольованих вершин
	LinkedGraph(int n = 0);

	auto row(int row) const->Node*;

	Node* first;
	const int count;
};
