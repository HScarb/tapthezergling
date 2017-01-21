#ifndef CsvManager_H
#define CsvManager_H

#include "cocos2d.h"
USING_NS_CC;
class CsvManager : public Ref
{
public:
	CREATE_FUNC(CsvManager);
	virtual bool init();

	void addLineData(ValueVector lineData);//���һ������

	ValueVector getSingleLineData(int iLine);//��ȡĳ������

	Size getRowColNum();//��ȡ���д�С
protected:
private:

	ValueVector m_allLineVec; //���Csv�ļ������е����ݣ�����������⣺ValueVector<Value<ValueVector>)
};

#endif
