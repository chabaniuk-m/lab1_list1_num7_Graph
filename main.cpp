//test Graph
#include "Graph.h"
#include <Windows.h>

void test1()
{
	//зважений граф
	Graph graph;
	{
		graph.addVertex(Vertex('A'));	// index - 0
		graph.addVertex(Vertex('B'));	// index - 1
		graph.addVertex(Vertex('C'));	// index - 2
		graph.addVertex(Vertex('D'));	// index - 3
		graph.addVertex(Vertex('E'));	// index - 4
		graph.addVertex(Vertex('F'));	// index - 5
		graph.addVertex(Vertex('G'));	// index - 6
		graph.addEdge(0, 4, 4);
		graph.addEdge(0, 5, 8);
		graph.addEdge(0, 6, 3);
		graph.addEdge(1, 2, 1);
		graph.addEdge(1, 4, 7);
		graph.addEdge(1, 5, 5);
		graph.addEdge(2, 4, 6);
		graph.addEdge(2, 3, 5);
		graph.addEdge(3, 4, 2);
		graph.addEdge(4, 5, 3);
		graph.addEdge(5, 6, 2);
	}
	std::cout << "Зв'язки кожної вершини з іншими:\n";
	graph.show();
	std::cout << "Граф зв'язний? ";
	std::string isconected = (graph.isConnected()) ? "Так\n" : "Ні\n";
	std::cout << isconected;
	std::cout << "Матриця суміжності:\n";
	graph.showAdjancencyMatrix();
	std::cout << "Обхід у глибину:\n";
	graph.passInDepth();
	std::cout << "Кістякове дерево мінімальної ваги (алгоритм Крускала):\n";
	Graph(graph.kruskal(), graph.getVerteces()).show();
}
void test2()
{
	//пошук компонент зв'язності
	Graph graph;
	std::cout << "Зв'язки кожної вершини з іншими\n";
	{
		graph.addVertex(Vertex('A'));	// index - 0
		graph.addVertex(Vertex('B'));	// index - 1
		graph.addVertex(Vertex('C'));	// index - 2
		graph.addVertex(Vertex('D'));	// index - 3
		graph.addVertex(Vertex('E'));	// index - 4
		graph.addVertex(Vertex('F'));	// index - 5
		graph.addVertex(Vertex('G'));	// index - 6
		graph.addVertex(Vertex('H'));	// index - 7
		graph.addVertex(Vertex('I'));	// index - 8
		graph.addVertex(Vertex('J'));	// index - 9
		graph.addVertex(Vertex('K'));	// index - 10
		graph.addEdge(0, 1);
		graph.addEdge(0, 2);
		graph.addEdge(1, 2);
		graph.addEdge(2, 3);
		graph.addEdge(4, 5);
		graph.addEdge(5, 6);
		graph.addEdge(5, 7);
		graph.addEdge(9, 10);
	}
	graph.show();
	std::cout << "Граф зв'язний? ";
	std::string isconected = (graph.isConnected()) ? "Так\n" : "Ні\n";
	std::cout << isconected;
	std::cout << "Обхід у глибину:\n";
	graph.passInDepth();
}
void test3()
{
	//знайти Ейлеровий цикл, якщо він є
	Graph graph;
	std::cout << "Зв'язки кожної вершини з іншими\n";
	{
		graph.addVertex(Vertex('A'));	// index - 0
		graph.addVertex(Vertex('B'));	// index - 1
		graph.addVertex(Vertex('C'));	// index - 2
		graph.addVertex(Vertex('D'));	// index - 3
		graph.addVertex(Vertex('E'));	// index - 4
		graph.addEdge(0, 2);
		graph.addEdge(2, 4);
		graph.addEdge(4, 1);
		graph.addEdge(1, 3);
		graph.addEdge(3, 0);
	}
	graph.show();
	std::cout << "Граф зв'язний? ";
	std::string isconected = (graph.isConnected()) ? "Так\n" : "Ні\n";
	std::cout << isconected;
}
void test4()
{
	//пошук найменшого циклу
	Graph graph;
	{
		graph.addVertex(Vertex('A'));	// index - 0
		graph.addVertex(Vertex('B'));	// index - 1
		graph.addVertex(Vertex('C'));	// index - 2
		graph.addVertex(Vertex('D'));	// index - 3
		graph.addVertex(Vertex('E'));	// index - 4
		graph.addVertex(Vertex('F'));	// index - 5
		graph.addVertex(Vertex('G'));	// index - 6
		graph.addEdge(0, 2);
		graph.addEdge(2, 1);
		graph.addEdge(2, 3);
		graph.addEdge(2, 5);
		graph.addEdge(1, 4);
		graph.addEdge(1, 3);
		graph.addEdge(3, 5);
		graph.addEdge(4, 5);
	}
	std::cout << "Граф зв'язний? ";
	std::string isconected = (graph.isConnected()) ? "Так\n" : "Ні\n";
	std::cout << isconected;
}
void test5()
{
	Graph graph;
	{
		graph.addVertex(Vertex('A'));	// index - 0
		graph.addVertex(Vertex('B'));	// index - 1
		graph.addVertex(Vertex('C'));	// index - 2
		graph.addVertex(Vertex('D'));	// index - 3
		graph.addEdge(0, 1);
		graph.addEdge(1, 3);
		graph.addEdge(3, 2);
		graph.addEdge(2, 0);
	}
	std::cout << "Граф зв'язний? ";
	std::string isconected = (graph.isConnected()) ? "Так\n" : "Ні\n";
	std::cout << isconected;
}

int main()
{
	SetConsoleOutputCP(1251);
	/*Graph graph;
	graph.addVertex(Vertex('A'));
	graph.addVertex(Vertex('B'));
	graph.addVertex(Vertex('C'));
	graph.addVertex(Vertex('D'));
	graph.addEdge(0, 1);
	graph.addEdge(1, 2);
	graph.addEdge(1, 2);
	graph.addEdge(3, 0);
	graph.showAdjancencyMatrix();
	graph.show();
	Graph(graph.kruskal(), graph.getVerteces()).show();
	graph.passInDepth();*/
	test5();
}