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
		graph.addEdge(3, 6, 9);
		graph.addEdge(4, 5, 3);
		graph.addEdge(4, 6, 10);
		graph.addEdge(5, 6, 2);
	}
	std::cout << "Чи планарний граф? " << ((graph.isPlanar()) ? "Так\n" : "Ні\n");
	std::cout << "Зв'язки кожної вершини з іншими:\n";
	graph.show();
	std::cout << "Кількість вершин: " << graph.getVertexNumber() << "\n";
	std::cout << "Кількість ребер: " << graph.getEdgeNumber() << "\n";
	std::cout << "Граф зв'язний? " << ((graph.isConnected()) ? "Так\n" : "Ні\n");
	std::cout << "Граф містить цикли? " << ((!graph.isAcyclic()) ? "Так\n" : "Ні\n");
	std::cout << "Чи є граф деревом? " << ((graph.isTree()) ? "Так\n" : "Ні\n");
	std::cout << "Матриця суміжності:\n";
	graph.showAdjancencyMatrix();
	std::cout << "Обхід у глибину:\n";
	graph.passInDepth();
	std::cout << "Обхід у ширину:\n";
	graph.passInWidth();
	std::cout << "Кістякове дерево мінімальної ваги (алгоритм Крускала):\n";
	Graph(graph.kruskal(), graph.getVerteces()).show();
}
void test2()
{
	//пошук компонент зв'язності
	Graph graph;
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
	std::cout << "Зв'язки кожної вершини з іншими\n";
	graph.show();
	std::cout << "Кількість вершин: " << graph.getVertexNumber() << "\n";
	std::cout << "Кількість ребер: " << graph.getEdgeNumber() << "\n";
	std::cout << "Граф зв'язний? " << ((graph.isConnected()) ? "Так\n" : "Ні\n");
	std::cout << "Граф містить цикли? " << ((!graph.isAcyclic()) ? "Так\n" : "Ні\n");
	std::cout << "Обхід у глибину:\n";
	graph.passInDepth();
	std::cout << "Обхід у ширину:\n";
	graph.passInWidth();
	std::cout << "Компоненти зв'язності\n";
	graph.connectivityComponents();
}
void test3()
{
	//знайти Ейлеровий цикл, якщо він є
	Graph graph;
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
	std::cout << "Зв'язки кожної вершини з іншими\n";
	graph.show();
	std::cout << "Кількість вершин: " << graph.getVertexNumber() << "\n";
	std::cout << "Кількість ребер: " << graph.getEdgeNumber() << "\n";
	std::cout << "Граф зв'язний? " << ((graph.isConnected()) ? "Так\n" : "Ні\n");
	std::cout << "Граф містить цикли? " << ((!graph.isAcyclic()) ? "Так\n" : "Ні\n");
	std::cout << "Обхід у ширину:\n";
	graph.passInWidth();
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
	std::cout << "Кількість вершин: " << graph.getVertexNumber() << "\n";
	std::cout << "Кількість ребер: " << graph.getEdgeNumber() << "\n";
	std::cout << "Граф зв'язний? " << ((graph.isConnected()) ? "Так\n" : "Ні\n");
	std::cout << "Граф містить цикли? " << ((!graph.isAcyclic()) ? "Так\n" : "Ні\n");
	std::cout << "Компоненти зв'язності\n";
	graph.connectivityComponents();
}
void test5()
{
	Graph graph;
	{
		graph.addVertex(Vertex('A'));	// index - 0
		graph.addVertex(Vertex('B'));	// index - 1
		graph.addVertex(Vertex('C'));	// index - 2
		graph.addVertex(Vertex('D'));	// index - 3
		graph.addVertex(Vertex('E'));	// index - 4
		graph.addVertex(Vertex('F'));	// index - 5
		graph.addEdge(1, 3);
		graph.addEdge(3, 2);
		graph.addEdge(2, 0);
		graph.addEdge(4, 5);
	}
	std::cout << "Граф зв'язний? " << ((graph.isConnected()) ? "Так\n" : "Ні\n");
	std::cout << "Граф містить цикли? " << ((!graph.isAcyclic()) ? "Так\n" : "Ні\n");
	for (auto& i : graph.connectivityComponents(1))
	{
		i.passInDepth();
	}
}
void test6()
{
	Graph graph;
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
		graph.addEdge(0, 1);
		graph.addEdge(0, 2);
		graph.addEdge(0, 3);
		graph.addEdge(1, 4);
		graph.addEdge(1, 5);
		graph.addEdge(2, 8);
		graph.addEdge(3, 6);
		graph.addEdge(3, 7);
	}
	std::cout << "Граф містить цикли? " << ((!graph.isAcyclic()) ? "Так\n" : "Ні\n");
	std::cout << "Чи є граф деревом? " << ((graph.isTree()) ? "Так\n" : "Ні\n");
	std::cout << "Чи планарний граф? " << ((graph.isPlanar()) ? "Так\n" : "Ні\n");
}
void test7()
{
	//граф К(3, 3)
	Graph graph;
	{
		graph.addVertex(Vertex('A'));	// index - 0
		graph.addVertex(Vertex('B'));	// index - 1
		graph.addVertex(Vertex('C'));	// index - 2
		graph.addVertex(Vertex('D'));	// index - 3
		graph.addVertex(Vertex('E'));	// index - 4
		graph.addVertex(Vertex('F'));	// index - 5
		graph.addEdge(0, 3);
		graph.addEdge(0, 4);
		graph.addEdge(0, 5);
		graph.addEdge(1, 3);
		graph.addEdge(1, 4);
		graph.addEdge(1, 5);
		graph.addEdge(2, 3);
		graph.addEdge(2, 4);
		graph.addEdge(2, 5);
	}
	std::cout << "K(3,3) ? " << ((graph.is_bipartity_3_3()) ? "Yes\n" : "No\n");
}

int main()
{
	SetConsoleOutputCP(1251);
	test1();
}