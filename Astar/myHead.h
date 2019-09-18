#pragma once

#define WALL		1			// 墙
#define ROAD		0			// 路
#define INVALID		-1			// 非法标志
#define VISITED		2

typedef struct point
{
	int col;	// 行
	int row;	// 列
}MyPoint;

typedef struct node
{
	MyPoint location;		// 位置信息
	double currentValue;	// 当前已走路径
	double accessValue;		// 预估价值
	double totalValue;		// 总价值
	struct node *parent;	// 父节点
}Node;