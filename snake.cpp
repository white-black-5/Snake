#include "pch.h"
#include "snake.h"


snake::snake()
{
	//��ʼ����Ϊ3
	s_snakelength.AddTail(CPoint(20, 15));
	s_snakelength.AddTail(CPoint(20, 16));
	s_snakelength.AddTail(CPoint(20, 17));
	//��ʼ����������
	s_direction.SetPoint(0, -1);
}



CList<CPoint>* snake::Getlength()
{
	// TODO: �ڴ˴����ʵ�ִ���.
	return &s_snakelength;
}


bool snake::onself(CPoint point)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	POSITION p = s_snakelength.GetHeadPosition();
	while (p)
	{
		if (point == s_snakelength.GetNext(p))
			return true;
	}
	return false;
}


bool snake::Move(CPoint bean)
{
	CPoint newHead = s_snakelength.GetHead() + s_direction;//������ͷ��λ��
	if (onself(newHead))//���ײ������
		return false;
	else {//���ײ��ǽ
		if (newHead.x < 0 ){
		newHead.x= newHead.x + 30;
		

	}
	if (newHead.x >= 30){
		newHead.x = newHead.x - 30;
		

	}
	if (newHead.y < 0) {
		newHead.y = newHead.y + 30;
		
	}
	if (newHead.y >= 30) {
		newHead.y = newHead.y - 30;
		
		}
}
	if (newHead != bean)//���û�Ե�ʳ��
	{
		s_snakelength.RemoveTail();//ɾ����β
	}
	s_snakelength.AddHead(newHead);//������ͷ�ӵ���ǰ��
	return true;
}


void snake::Direction(CPoint direction) 
{
	s_direction = direction;
}


