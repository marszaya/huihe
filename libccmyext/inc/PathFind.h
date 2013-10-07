#pragma once

#include <stdlib.h>
#include <vector>
using namespace std;


class CMZMap2DStack
{
public:
	struct POINT_2D
	{
		int x;
		int y;
	};

public:
	inline void push(int x, int y)
	{
		POINT_2D p;
		p.x = x;
		p.y = y;
		m_points.push_back(p);
	}

	inline void pop()
	{
		m_points.pop_back();
	}

	inline unsigned int size()
	{
		return m_points.size(); 
	}

	inline void clear()
	{
		return m_points.clear();
	}

	//自己当心idx范围
	inline const POINT_2D& pointAt(unsigned int idx)
	{
		return m_points[idx];
	}

protected:
	vector<POINT_2D> m_points;
};

class CMZMap2D
{
public:
	struct MAP_CELL_INFO
	{
		char flag;
	};

public:
	CMZMap2D();
	virtual ~CMZMap2D();

	bool init(int maxX, int maxY);

	bool setWall(int x, int y);

	//array = [x0,y0,x1,y1,....]
	bool setWalls(int* xyArray, unsigned int arraySize);

	inline bool passable(int x, int y)
	{
		if(x<0 || x>=m_maxX || y<0 || y>=m_maxY)
			return false;
		return m_cells[cellIdx(x,y)].flag != 1;
	}

	bool findPath(CMZMap2DStack& stack, int srcX, int srcY, int desX, int desY);

	inline int getMaxX()
	{
		return m_maxX;
	}

	inline int getMaxY()
	{
		return m_maxY;
	}

	

protected:
	inline int cellIdx(int x, int y)
	{
		return y*m_maxX+x;
	}

	inline int getX(int cellIdx)
	{
		return cellIdx%m_maxX;
	}

	inline int getY(int cellIdx)
	{
		return cellIdx/m_maxX;
	}

	inline int estimateFunc(int deltaX, int deltaY, int realCost)
	{
		int ret = 0;
		if(deltaX < 0)
			ret -= deltaX;
		else
			ret += deltaX;

		if(deltaY < 0)
			ret -= deltaY;
		else
			ret += deltaY;

		return ret*2+realCost;
	}

protected:
	struct FIND_PATH_TABLE_NODE
	{
		int parentIdx;
		int mapX;
		int mapY;
		int costFromParent; //=1
		int estimatedValue;
	};

protected:
	int m_maxX;
	int m_maxY;
	MAP_CELL_INFO* m_cells;
};