#pragma once

#define WALL		1			// ǽ
#define ROAD		0			// ·
#define INVALID		-1			// �Ƿ���־
#define VISITED		2

typedef struct point
{
	int col;	// ��
	int row;	// ��
}MyPoint;

typedef struct node
{
	MyPoint location;		// λ����Ϣ
	double currentValue;	// ��ǰ����·��
	double accessValue;		// Ԥ����ֵ
	double totalValue;		// �ܼ�ֵ
	struct node *parent;	// ���ڵ�
}Node;