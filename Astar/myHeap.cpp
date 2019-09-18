#include "myHeap.h"


myHeap::myHeap()
{
	init();	
}


bool myHeap::Insert(Node & node)
{
	elemBuff.push_back(node);	// ���������Ԫ��
	elemNum++;					// Ԫ��������һ

	this->AdjustHeapInsert();
	return true;
}

bool myHeap::GetOptimal(Node &optElem, bool Delete)
{
	optElem = elemBuff[1];
	if (Delete)					// ɾ���ڵ�
	{
		Swap(elemBuff[1], elemBuff[elemNum]);
		elemNum--;
		elemBuff.pop_back();	// ɾ�����һ��Ԫ��
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
	Node first = { {0},0,0,0,nullptr };		// ��һ���ڵ�ʲô�����ţ����е�һ���ڵ��±�Ϊ1��
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
		// ����
		if (childNode <= elemNum && preNode <= elemNum)
		{
			Swap(elemBuff[preNode], elemBuff[childNode]);
		}
		// ���µ�ǰ�ڵ�
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
			// ����
			Swap(elemBuff[parentNode], elemBuff[preNode]);

			// ���µ�ǰ�ڵ�
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
