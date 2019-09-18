#include "AStar.h"
#include "myHead.h"
#include <cmath>

AStar::AStar()
{
	// ��ʼ��
	init();
}

void AStar::SetMap(int ** map, int col, int row)
{
	if (this->map != nullptr)				// ����ǰ���ݻ��ڣ���ô��ɾ�����ٴ�������
	{
		// ���ԭ������
		for (int i = 0; i < col; i++) {
			delete[] map[i];
		}
		delete[] map;

		// ��ʼ��
		init();
	}
	if (this->mapNode != nullptr)				// ����ǰ���ݻ��ڣ���ô��ɾ�����ٴ�������
	{
		// ���ԭ������
		for (int i = 0; i < col; i++) {
			delete[] mapNode[i];
		}
		delete[] mapNode;

		// ��ʼ��
		init();
	}

	this->col = col;
	this->row = row;

	this->map = new int*[col];
	this->mapNode = new Node*[col];
	for (int i = 0; i < col; i++) {
		this->map[i] = new int[row];
		this->mapNode[i] = new Node[row];
	}

	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			this->map[i][j] = map[i][j];
			this->mapNode[i][j].parent = nullptr;
		}
	}
}

void AStar::SetStartEnd(const MyPoint start, const MyPoint end)
{
	this->start = start;
	this->end = end;
}

/*-------------------------------------------- �㷨���� -----------------------------------------------------
	<1> �����㵱ǰ��ֵ�����߼�ֵ�����ҽ����У����׽ڵ��ÿգ�,
	<2> ��ǰ�ڵ㲻Ϊ�յ�ѭ��
		<2.1> ȡĿǰ�ܼ�ֵ��С�ڵ����Ϊ parentNode
		<2.2> ѭ��Ѱ�Ҹ��׽ڵ����һ���ɵ���ڵ����Ϊ curNode
			<2.2.1> ����curNode�ĸ��׽ڵ�Ϊ parentNode��
			<2.2.2> �����½ڵ�����߼�ֵ�����Ƽ�ֵ��Ȼ�������
	<3> ������¼�����·��
	<4> ����·��

-----------------------------------------------------------------------------------------------------------*/
void AStar::run(bool display)
{
	Node parentNode;	// ���׽ڵ�
	Node curNode;		// ��ǰ�ڵ�

	parentNode.location = start;
	CalAssessValue(parentNode);				// ���㵱ǰ���Ƽ�ֵ
	parentNode.currentValue = 0;			// ��ǰ���߼�ֵΪ0
	UpdataNodeMap(parentNode);				// ���¼�¼����

	minHeap.Insert(parentNode);


	minHeap.GetOptimal(curNode, true);

	while (curNode.location.col != end.col || curNode.location.row != end.row)		// ���ڵ㲻���յ�ѭ��
	{
		parentNode = curNode;
		int dir = 0;						// ��ȡ��������Ľڵ�
		while (GetCurNode(curNode,parentNode,dir))
		{
			curNode.parent = &parentNode;
			CalAssessValue(curNode);		// ������Ƽ�ֵ
			CalCurrentValue(curNode);		// �������߼�ֵ

			curNode.totalValue = curNode.accessValue + curNode.currentValue;

			UpdataNodeMap(curNode);			// ���¼�¼����
			minHeap.Insert(curNode);		// ����ڵ�
		}
	}

	PutWayInResult();
}

void AStar::init()
{
	start.col	= INVALID;		// ���
	end.col		= INVALID;
	map			= nullptr;		// ��ͼ
	col			= INVALID;		// ����
	mapNode		= nullptr;		// ����ͼ

	if (!result.empty())
	{
		result.clear();
	}
}

void AStar::CalAssessValue(Node & node)
{
	node.accessValue = sqrt((end.col - node.location.col) * (end.col - node.location.col) + (end.row - node.location.row)*(end.row - node.location.row));
}

void AStar::UpdataNodeMap(Node & node)
{
	mapNode[node.location.col][node.location.row].accessValue	= node.accessValue;
	mapNode[node.location.col][node.location.row].currentValue	= node.currentValue;
	mapNode[node.location.col][node.location.row].location		= node.location;
	mapNode[node.location.col][node.location.row].parent		= node.parent;
	mapNode[node.location.col][node.location.row].totalValue	= node.totalValue;
}

bool AStar::GetCurNode(Node &curNode, Node parentNode ,int &dir,int step)
{
	int direction[8][2] = {
		{1,0},		// ��
		{1,1},		// ����
		{0,1},		// ��
		{-1,1},		// ����
		{-1,0},		// ��
		{-1,-1},	// ����
		{0,-1},		// ��
		{1,-1},		// ����
	};

	if (dir > 7 && dir < 0)
		return false;
	do {
		curNode.location.col = parentNode.location.col + direction[dir][0];
		curNode.location.row = parentNode.location.row + direction[dir][1];
		dir += step;
	} while (curNode.location.col >= 0 && curNode.location.col <= col && curNode.location.row >= 0 && curNode.location.row <= row && map[curNode.location.col][curNode.location.row] != WALL);
	return true;
}

void AStar::CalCurrentValue(Node & node)
{
	node.currentValue = node.parent->currentValue + 1;
}

void AStar::PutWayInResult()
{
	vector<node> temp;
	int x = end.col;
	int y = end.row;

	while (x != start.col || y != start.row)
	{
		temp.push_back(mapNode[x][y]);
		int t;
		t = mapNode[x][y].parent->location.col;
		y = mapNode[x][y].parent->location.row;
		x = t;
	}

	for (int i = temp.size() - 1;i >= 0;i--)
	{
		result.push_back(temp[i].location);
	}
}

AStar::~AStar()
{
	for (int i = 0; i < col; i++) {
		delete[] map[i];
	}
	delete[] map;
}
