/*********************** ���Ŷ��� *****************************
* ������ʹ�ö�����ά��һ����С����
* ʵ�֣������Ա�����һ��С���ѣ�Ԫ����һ��Vector���洢����һ��ָ����������������
*
*/
#pragma once
#include "myHead.h"
#include <vector>
using namespace std;

#ifndef ASTARMAXELEM
#define ASTARMAXELEM 1000		// �������Ԫ�ظ���
#endif							// !ASTARMAXELEM

class myHeap
{
public:
	myHeap();

public :

	/****************** Insert **********************
	*param node: ������ڵ�
	*function  : ������в���һ���ڵ�
	**************************************************/
	bool Insert(Node &node);

	/****************** GetOptimal **********************
	*param optElem	: ������ڵ�
	*param Delete	: �Ƿ�ɾ�����Žڵ�
	*function		: ȡ�����Žڵ�
	****************************************************/
	bool GetOptimal(Node &optElem,bool Delete = false);

	/****************** GetOptimal **********************
	*function	: ������нڵ�
	****************************************************/
	bool ClearAll();

private:
	/****************** init **********************
	*function  : ��ʼ��˽�б���
	***********************************************/
	void init();

	/******************  AdjustHeap **********************
	*function  : ɾ��ʱ������
	*****************************************************/
	void AdjustHeapDelete();

	/****************** AdjustHeap **********************
	*function  : ����ʱ������
	*****************************************************/
	void AdjustHeapInsert();

	/****************** Swap *****************************
	*function  : ����A B��ֵ
	*****************************************************/
	void Swap(Node &A, Node &B);

private:

	vector<Node> elemBuff;				// Ԫ�ش洢��
	int elemNum;						// Ԫ������
};

