#ifndef __LINE_HH__
#define __LINE_HH__

class Line{
public:
	Line(int x1,int y1,int x2,int y2);
	~Line();

	void printLine() const;
private:
	//类的前向声明
	class LineImp1;
	LineImp1* _pImp1;
};
#endif
