//test Graph
#include "Graph.h"
#include <Windows.h>

void test1()
{
	//�������� ����
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
	std::cout << "��'���� ����� ������� � ������:\n";
	graph.show();
	std::cout << "���� ��'�����? ";
	std::string isconected = (graph.isConnected()) ? "���\n" : "ͳ\n";
	std::cout << isconected;
	std::cout << "������� ��������:\n";
	graph.showAdjancencyMatrix();
	std::cout << "����� � �������:\n";
	graph.passInDepth();
	std::cout << "ʳ������� ������ �������� ���� (�������� ��������):\n";
	Graph(graph.kruskal(), graph.getVerteces()).show();
}
void test2()
{
	//����� ��������� ��'������
	Graph graph;
	std::cout << "��'���� ����� ������� � ������\n";
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
	std::cout << "���� ��'�����? ";
	std::string isconected = (graph.isConnected()) ? "���\n" : "ͳ\n";
	std::cout << isconected;
	std::cout << "����� � �������:\n";
	graph.passInDepth();
}
void test3()
{
	//������ ��������� ����, ���� �� �
	Graph graph;
	std::cout << "��'���� ����� ������� � ������\n";
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
	std::cout << "���� ��'�����? ";
	std::string isconected = (graph.isConnected()) ? "���\n" : "ͳ\n";
	std::cout << isconected;
}
void test4()
{
	//����� ���������� �����
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
	std::cout << "���� ��'�����? ";
	std::string isconected = (graph.isConnected()) ? "���\n" : "ͳ\n";
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
	std::cout << "���� ��'�����? ";
	std::string isconected = (graph.isConnected()) ? "���\n" : "ͳ\n";
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