#ifndef __CSVDATA_H__
#define __CSVDATA_H__

#include "cocos2d.h"
USING_NS_CC;
class CsvData : public Ref
{
public:
	CREATE_FUNC(CsvData);
	virtual bool init();

	void addLineData(ValueVector lineData);//���һ������

	ValueVector getSingleLineData(int iLine);//��ȡĳ������

	Size getRowColNum();//��ȡ���д�С
protected:
private:

	ValueVector m_allLineVec; //���Csv�ļ������е����ݣ�����������⣺ValueVector<Value<ValueVector>)
};

#endif
