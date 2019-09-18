#include "myHeap.h"


myHeap::myHeap()
{
	init();	
}


bool myHeap::Insert(Node & node)
{
	elemBuff.push_back(node);	// 存入待插入元素
	elemNum++;					// 元素数量加一

	this->AdjustHeapInsert();
	return true;
}

bool myHeap::GetOptimal(Node &optElem, bool Delete)
{
	optElem = elemBuff[1];
	if (Delete)					// 删除节点
	{
		Swap(elemBuff[1], elemBuff[elemNum]);
		elemNum--;
		elemBuff.pop_back();	// 删除最后一个元素
		this->AdjustHeapDelete();
	}
	return true;
}

bool myHeap::ClearAll()
{
	elemBuff.clear();
	init();
	return true;
}

void myHeap::init()
{
	Node first = { {0},0,0,0,nullptr };		// 第一个节点什么都不放，队列第一个节点下标为1；
	elemBuff.resize(1,first);
	elemNum = 0;
}

void myHeap::AdjustHeapDelete()
{
	int preNode = 1;
	int childNode = 2;

	while (childNode <= elemNum)
	{
		childNode = 2 * preNode;
		if (childNode + 1 <= elemNum && elemBuff[childNode].totalValue > elemBuff[childNode + 1].totalValue)
		{
			childNode++;
		}
		if (childNode <= elemNum && preNode <= elemNum && elemBuff[preNode].totalValue <= elemBuff[childNode].totalValue)
		{
			break;
		}
		// 交换
		if (childNode <= elemNum && preNode <= elemNum)
		{
			Swap(elemBuff[preNode], elemBuff[childNode]);
		}
		// 更新当前节点
		preNode = childNode;
	}
}

void myHeap::AdjustHeapInsert()
{
	int preNode = elemNum;
	int parentNode = elemNum / 2;
	while (parentNode > 0)
	{
		parentNode = preNode / 2;
		if (parentNode > 0 && preNode > 0 && elemBuff[parentNode].totalValue > elemBuff[preNode].totalValue)
		{
			// 交换
			Swap(elemBuff[parentNode], elemBuff[preNode]);

			// 更新当前节点
			preNode = parentNode;
		}
		else
		{
			break;
		}
	}
}

void myHeap::Swap(Node & A, Node & B)
{
	Node temp;
	temp = A;
	A = B;
	B = temp;
}
