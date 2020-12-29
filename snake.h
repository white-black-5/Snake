#pragma once
class snake 
{
public:
	snake();
	CList<CPoint>* Getlength();
	bool onself(CPoint point);
	bool Move(CPoint bean);
	void Direction(CPoint direction);
private:
	CList<CPoint> s_snakelength;
	CPoint s_direction;

};

