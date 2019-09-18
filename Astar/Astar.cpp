#include "AStar.h"
#include "myHead.h"
#include <cmath>

AStar::AStar()
{
	// 初始化
	init();
}

void AStar::SetMap(int ** map, int col, int row)
{
	if (this->map != nullptr)				// 若先前数据还在，那么先删除，再从新设置
	{
		// 清除原来数据
		for (int i = 0; i < col; i++) {
			delete[] map[i];
		}
		delete[] map;

		// 初始化
		init();
	}
	if (this->mapNode != nullptr)				// 若先前数据还在，那么先删除，再从新设置
	{
		// 清除原来数据
		for (int i = 0; i < col; i++) {
			delete[] mapNode[i];
		}
		delete[] mapNode;

		// 初始化
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

/*-------------------------------------------- 算法过程 -----------------------------------------------------
	<1> 起点计算当前价值与已走价值，并且进队列（父亲节点置空）,
	<2> 当前节点不为终点循环
		<2.1> 取目前总价值最小节点更新为 parentNode
		<2.2> 循环寻找父亲节点的下一步可到达节点更新为 curNode
			<2.2.1> 更新curNode的父亲节点为 parentNode；
			<2.2.2> 计算新节点的已走价值，估计价值，然后进队列
	<3> 读出记录数组的路径
	<4> 保存路径

-----------------------------------------------------------------------------------------------------------*/
void AStar::run(bool display)
{
	Node parentNode;	// 父亲节点
	Node curNode;		// 当前节点

	parentNode.location = start;
	CalAssessValue(parentNode);				// 计算当前估计价值
	parentNode.currentValue = 0;			// 当前已走价值为0
	UpdataNodeMap(parentNode);				// 更新记录数组

	minHeap.Insert(parentNode);


	minHeap.GetOptimal(curNode, true);

	while (curNode.location.col != end.col || curNode.location.row != end.row)		// 当节点不是终点循环
	{
		parentNode = curNode;
		int dir = 0;						// 获取各个方向的节点
		while (GetCurNode(curNode,parentNode,dir))
		{
			curNode.parent = &parentNode;
			CalAssessValue(curNode);		// 计算估计价值
			CalCurrentValue(curNode);		// 计算已走价值

			curNode.totalValue = curNode.accessValue + curNode.currentValue;

			UpdataNodeMap(curNode);			// 更新记录数组
			minHeap.Insert(curNode);		// 插入节点
		}
	}

	PutWayInResult();
}

void AStar::init()
{
	start.col	= INVALID;		// 起点
	end.col		= INVALID;
	map			= nullptr;		// 地图
	col			= INVALID;		// 行数
	mapNode		= nullptr;		// 求解地图

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
		{1,0},		// 右
		{1,1},		// 右下
		{0,1},		// 下
		{-1,1},		// 左下
		{-1,0},		// 左
		{-1,-1},	// 左上
		{0,-1},		// 上
		{1,-1},		// 右上
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
