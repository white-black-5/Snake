#include "pch.h"
#include "snake.h"


snake::snake()
{
	//初始长度为3
	s_snakelength.AddTail(CPoint(20, 15));
	s_snakelength.AddTail(CPoint(20, 16));
	s_snakelength.AddTail(CPoint(20, 17));
	//初始化方向向上
	s_direction.SetPoint(0, -1);
}



CList<CPoint>* snake::Getlength()
{
	// TODO: 在此处添加实现代码.
	return &s_snakelength;
}


bool snake::onself(CPoint point)
{
	// TODO: 在此处添加实现代码.
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
	CPoint newHead = s_snakelength.GetHead() + s_direction;//计算蛇头新位置
	if (onself(newHead))//如果撞到蛇身
		return false;
	else {//如果撞到墙
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
	if (newHead != bean)//如果没吃到食物
	{
		s_snakelength.RemoveTail();//删除蛇尾
	}
	s_snakelength.AddHead(newHead);//将新蛇头加到最前面
	return true;
}


void snake::Direction(CPoint direction) 
{
	s_direction = direction;
}


