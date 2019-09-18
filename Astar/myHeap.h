/*********************** 最优队列 *****************************
* 描述：使用堆排序维护一个最小队列
* 实现：用线性表来做一个小根堆，元素用一个Vector来存储，用一个指针数组来进行排序
*
*/
#pragma once
#include "myHead.h"
#include <vector>
using namespace std;

#ifndef ASTARMAXELEM
#define ASTARMAXELEM 1000		// 队列最大元素个数
#endif							// !ASTARMAXELEM

class myHeap
{
public:
	myHeap();

public :

	/****************** Insert **********************
	*param node: 待插入节点
	*function  : 向队列中插入一个节点
	**************************************************/
	bool Insert(Node &node);

	/****************** GetOptimal **********************
	*param optElem	: 待插入节点
	*param Delete	: 是否删除最优节点
	*function		: 取出最优节点
	****************************************************/
	bool GetOptimal(Node &optElem,bool Delete = false);

	/****************** GetOptimal **********************
	*function	: 清除所有节点
	****************************************************/
	bool ClearAll();

private:
	/****************** init **********************
	*function  : 初始化私有变量
	***********************************************/
	void init();

	/******************  AdjustHeap **********************
	*function  : 删除时调整堆
	*****************************************************/
	void AdjustHeapDelete();

	/****************** AdjustHeap **********************
	*function  : 插入时调整堆
	*****************************************************/
	void AdjustHeapInsert();

	/****************** Swap *****************************
	*function  : 交换A B的值
	*****************************************************/
	void Swap(Node &A, Node &B);

private:

	vector<Node> elemBuff;				// 元素存储区
	int elemNum;						// 元素数量
};

