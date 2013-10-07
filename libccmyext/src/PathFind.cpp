#include "PathFind.h"

CMZMap2D::CMZMap2D()
{
	m_maxX = 0;
	m_maxY = 0;
	m_cells = NULL;
}

CMZMap2D::~CMZMap2D()
{
	if(m_cells)
	{
		delete[] m_cells;
		m_cells = NULL;
	}
}

bool CMZMap2D::init(int maxX, int maxY)
{
	bool ret = false;
	do{
		if(m_cells != NULL || maxX <=0 || maxY<=0)
			break;
		m_maxX=maxX;
		m_maxY=maxY;
		m_cells = new MAP_CELL_INFO[m_maxX*m_maxY];
		if(!m_cells)
			break;
		for(int i=0; i<m_maxX*m_maxY; ++i)
		{
			m_cells[i].flag = 0;
		}
		ret = true;
	}while(0);
	return ret;
}

bool CMZMap2D::setWall(int x, int y)
{
	bool ret = false;
	do{
		if(!m_cells || x <0 || y<0)
			break;

		m_cells[cellIdx(x,y)].flag = 1;

		ret = true;
	}while(0);
	return ret;
}

bool CMZMap2D::setWalls(int* xyArray, unsigned int arraySize)
{
	bool ret = false;
	do{
		if(!m_cells || !xyArray || arraySize==0 || arraySize%2!=0)
			break;

		for(unsigned int i=0; i<arraySize/2; ++i)
		{
			int x = i*2;
			int y = i*2+1;
			if(x <=0 || y <=0)
				break;
			m_cells[cellIdx(x,y)].flag = 1;
		}

		ret = true;
	}while(0);
	return ret;
}

bool CMZMap2D::findPath(CMZMap2DStack& stack, int srcX, int srcY, int desX, int desY)
{
	bool ret = false;
	do{
		int STEP_X[] = {1,-1,0,0};
		int STEP_Y[] = {0,0,1,-1};
		//A*
		vector<FIND_PATH_TABLE_NODE> cacheTable;
		cacheTable.reserve(m_maxX*m_maxY);
		vector<int> openTable;
		openTable.reserve(m_maxX*m_maxY);
		vector<int> closeTable;
		closeTable.reserve(m_maxX*m_maxY);

		//初始化源节点
		FIND_PATH_TABLE_NODE srcNode;
		srcNode.parentIdx = -1;
		srcNode.mapX = srcX;
		srcNode.mapY = srcY;
		srcNode.costFromParent = 0;
		srcNode.estimatedValue = estimateFunc(srcX-desX, srcY-desY, 0);
		cacheTable.push_back(srcNode);
		openTable.push_back(0);

		int dstIdx = -1;
	
		//循环
		while(openTable.size() > 0)
		{
			//寻找最短
			int minIdx = -1;
			for(unsigned int i=0; i<openTable.size(); ++i)
			{
				if(minIdx == -1 || 
					cacheTable[openTable[i]].estimatedValue < cacheTable[openTable[minIdx]].estimatedValue)
						minIdx = i;
			}

			int idxInCacheTable = openTable[minIdx];
			FIND_PATH_TABLE_NODE& minNode = cacheTable[idxInCacheTable];

			//找到目的节点
			if(minNode.mapX == desX && minNode.mapY == desY)
			{
				dstIdx = openTable[minIdx];
				break;
			}

			//目的节点到close表
			closeTable.push_back(openTable[minIdx]);

			//从open表中删除
			openTable[minIdx] = openTable[openTable.size()-1];
			openTable.pop_back();

			//继续4方向寻找
			for(int i=0; i<4; ++i)
			{
				int stepX = STEP_X[i];
				int stepY = STEP_Y[i];

				int mapX = minNode.mapX+stepX;
				int mapY = minNode.mapY+stepY;
				
				//死路，放弃
				if(!passable(mapX, mapY))
				{
					continue;
				}

				//是否在close表内
				bool inClose = false;
				for(int closeIdx = closeTable.size()-1; closeIdx>=0; --closeIdx)
				{
					FIND_PATH_TABLE_NODE& tmpCloseNode = cacheTable[closeTable[closeIdx]];
					if(tmpCloseNode.mapX == mapX && tmpCloseNode.mapY == mapY)
					{
						inClose = true;
						break;
					}
				}

				if(inClose)
					continue;

				//计算估算值
				int currentCost = minNode.costFromParent+1;
					
				//已经在open表内?
				bool inOpen = false;
				for(unsigned int openIdx=0; openIdx<openTable.size(); ++openIdx)
				{
					FIND_PATH_TABLE_NODE& tmpOpenNode = cacheTable[openTable[openIdx]];
					if(tmpOpenNode.mapX == mapX && tmpOpenNode.mapY == mapY)
					{
						inOpen = true;
						//比较下估算值
						if(currentCost < tmpOpenNode.costFromParent)
						{
							//更新
							tmpOpenNode.parentIdx = idxInCacheTable;
							tmpOpenNode.costFromParent = currentCost;
							tmpOpenNode.estimatedValue = estimateFunc(mapX-desX, mapY-desY, currentCost);
						}
						break;
					}
				}

				if(inOpen)
					continue;

				//新增
				FIND_PATH_TABLE_NODE newNode;
				newNode.mapX = mapX;
				newNode.mapY = mapY;
				newNode.costFromParent = currentCost;
				newNode.estimatedValue = estimateFunc(mapX-desX, mapY-desY, currentCost);
				newNode.parentIdx = idxInCacheTable;

				cacheTable.push_back(newNode);
				openTable.push_back(cacheTable.size()-1);
			}
		}
		
		if(dstIdx>=0)
		{
			//copy 结果
			int tmpIdx = dstIdx;
			while(tmpIdx >= 0)
			{
				stack.push(cacheTable[tmpIdx].mapX, cacheTable[tmpIdx].mapY);
				tmpIdx = cacheTable[tmpIdx].parentIdx;
			}
			ret = true;
		}
	}while(0);
	return ret;
}

