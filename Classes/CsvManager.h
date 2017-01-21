#ifndef CsvManager_H
#define CsvManager_H

#include "cocos2d.h"
USING_NS_CC;
class CsvManager : public Ref
{
public:
	CREATE_FUNC(CsvManager);
	virtual bool init();

	void addLineData(ValueVector lineData);//添加一行数据

	ValueVector getSingleLineData(int iLine);//获取某行数据

	Size getRowColNum();//获取行列大小
protected:
private:

	ValueVector m_allLineVec; //存放Csv文件所有行的数据，试试这样理解：ValueVector<Value<ValueVector>)
};

#endif
