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
		graph.addEdge(3, 6, 9);
		graph.addEdge(4, 5, 3);
		graph.addEdge(4, 6, 10);
		graph.addEdge(5, 6, 2);
	}
	std::cout << "�� ��������� ����? " << ((graph.isPlanar()) ? "���\n" : "ͳ\n");
	std::cout << "��'���� ����� ������� � ������:\n";
	graph.show();
	std::cout << "ʳ������ ������: " << graph.getVertexNumber() << "\n";
	std::cout << "ʳ������ �����: " << graph.getEdgeNumber() << "\n";
	std::cout << "���� ��'�����? " << ((graph.isConnected()) ? "���\n" : "ͳ\n");
	std::cout << "�� � ��������� ������? " << ((graph.isEulerGraph()) ? "���" : "ͳ") << std::endl;
	std::cout << "���� ������ �����? " << ((!graph.isAcyclic()) ? "���\n" : "ͳ\n");
	std::cout << "�� � ���� �������? " << ((graph.isTree()) ? "���\n" : "ͳ\n");
	std::cout << "������� ��������:\n";
	graph.showAdjancencyMatrix();
	std::cout << "����� � �������:\n";
	graph.passInDepth();
	std::cout << "����� � ������:\n";
	graph.passInWidth();
	std::cout << "ʳ������� ������ �������� ���� (�������� ��������):\n";
	Graph(graph.kruskal(), graph.getVerteces()).show();
}
void test2()
{
	//����� ��������� ��'������
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
	std::cout << "ʳ������ ������: " << graph.getVertexNumber() << "\n";
	std::cout << "ʳ������ �����: " << graph.getEdgeNumber() << "\n";
	std::cout << "���� ��'�����? " << ((graph.isConnected()) ? "���\n" : "ͳ\n");
	std::cout << "�� � ��������� ������? " << ((graph.isEulerGraph()) ? "���" : "ͳ") << std::endl;
	std::cout << "���� ������ �����? " << ((!graph.isAcyclic()) ? "���\n" : "ͳ\n");
	std::cout << "����� � �������:\n";
	graph.passInDepth();
	std::cout << "����� � ������:\n";
	graph.passInWidth();
	std::cout << "���������� ��'������\n";
	graph.connectivityComponents();
}
void test3()
{
	//������ ��������� ����, ���� �� �
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
	std::cout << "ʳ������ ������: " << graph.getVertexNumber() << "\n";
	std::cout << "ʳ������ �����: " << graph.getEdgeNumber() << "\n";
	std::cout << "�� � ��������� ������? " << ((graph.isEulerGraph()) ? "���" : "ͳ") << std::endl;
	std::cout << "���� ��'�����? " << ((graph.isConnected()) ? "���\n" : "ͳ\n");
	std::cout << "���� ������ �����? " << ((!graph.isAcyclic()) ? "���\n" : "ͳ\n");
	std::cout << "����� � ������:\n";
	graph.passInWidth();
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
	std::cout << "ʳ������ ������: " << graph.getVertexNumber() << "\n";
	std::cout << "ʳ������ �����: " << graph.getEdgeNumber() << "\n";
	std::cout << "���� ��'�����? " << ((graph.isConnected()) ? "���\n" : "ͳ\n");
	std::cout << "���� ������ �����? " << ((!graph.isAcyclic()) ? "���\n" : "ͳ\n");
	std::cout << "���������� ��'������\n";
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
	std::cout << "���� ��'�����? " << ((graph.isConnected()) ? "���\n" : "ͳ\n");
	std::cout << "���� ������ �����? " << ((!graph.isAcyclic()) ? "���\n" : "ͳ\n");
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
	std::cout << "���� ������ �����? " << ((!graph.isAcyclic()) ? "���\n" : "ͳ\n");
	std::cout << "�� � ���� �������? " << ((graph.isTree()) ? "���\n" : "ͳ\n");
	std::cout << "�� ��������� ����? " << ((graph.isPlanar()) ? "���\n" : "ͳ\n");
}
void test7()
{
	//���� �(3, 3)
	Graph graph;
	{
		graph.addVertex(Vertex('A'));	// index - 0
		graph.addVertex(Vertex('B'));	// index - 1
		graph.addVertex(Vertex('C'));	// index - 2
		graph.addVertex(Vertex('D'));	// index - 3
		graph.addVertex(Vertex('E'));	// index - 4
		graph.addVertex(Vertex('F'));	// index - 5
		graph.addEdge(0, 1);
		graph.addEdge(0, 2);
		graph.addEdge(0, 4);
		graph.addEdge(0, 5);
		graph.addEdge(1, 2);
		graph.addEdge(1, 4);
		graph.addEdge(1, 5);
		graph.addEdge(2, 3);
		graph.addEdge(2, 4);
		graph.addEdge(2, 5);
		graph.addEdge(3, 4);
		graph.addEdge(4, 5);

	}
	
	std::cout << "�� ��������� ����? " << ((graph.isPlanar()) ? "���\n" : "ͳ\n");
	std::cout << "K(3,3) ? " << ((graph.is_bipartity_3_3()) ? "Yes\n" : "No\n");
	std::cout << "�� � ��������� ������? " << ((graph.isEulerGraph()) ? "���" : "ͳ") << std::endl;
}

int main()
{
	SetConsoleOutputCP(1251);
	test1();
}