#include "CsvUtils.h"


namespace CSVUtils {

	CSVUtils::Csv::Csv(const string& filename)
	{
		Parse(filename);
	}

	CSVUtils::Csv::~Csv()
	{

	}


	void CSVUtils::Csv::Load(const string& filename, string& Data)
	{
		// ��ȡ�ļ�����
		FILE* pFile = fopen(filename.c_str(), "rb");
		if (!pFile) {
			return;
		}

		fseek(pFile, 0, SEEK_END);
		long len = ftell(pFile);

		char* pBuffer = new char[len + 1];

		fseek(pFile, 0, SEEK_SET);
		fread(pBuffer, 1, len, pFile);
		fclose(pFile);

		pBuffer[len] = 0;
		Data.assign(pBuffer, len);

		delete[] pBuffer;
	}


	void CSVUtils::Csv::Parse(const string& filename)
	{
		// ���֮ǰ������
		m_content.clear();
		m_strErrorInfo.clear();

		string text;
		Load(filename, text);

		if (text.size() == 0) {
			return;
		}

		// ����״̬
		enum StateType {
			NewFieldStart,      // ���ֶο�ʼ
			NonQuotesField,     // �������ֶ�
			QuotesField,        // �����ֶ�
			FieldSeparator,     // �ֶηָ�
			QuoteInQuotesField, // �����ֶ��е�����
			RowSeparator,       // �зָ����ַ�1���س�
			Error,              // �﷨����
		};

		Row Fields = Row();
		string strField;

		// ���ó�ʼ״̬
		StateType State = NewFieldStart;

		for (int i = 0, size = text.size(); i < size; ++i) {
			const char& ch = text[i];

			switch (State) {
			case NewFieldStart: { // ���ֶο�ʼ
									if (ch == '"') {
										State = QuotesField;
									}
									else if (ch == ',') {
										Fields.push_back("");
										State = FieldSeparator;
									}
									else if (ch == '\r' || ch == '\n') {
										m_strErrorInfo = "�﷨�����п���";
										State = Error;
									}
									else {
										strField.push_back(ch);
										State = NonQuotesField;
									}
			}
				break;

			case NonQuotesField: { // �������ֶ�
									 if (ch == ',') {
										 Fields.push_back(strField);
										 strField.clear();
										 State = FieldSeparator;
									 }
									 else if (ch == '\r') {
										 Fields.push_back(strField);
										 State = RowSeparator;
									 }
									 else {
										 strField.push_back(ch);
									 }
			}
				break;

			case QuotesField: { // �����ֶ�
								  if (ch == '"') {
									  State = QuoteInQuotesField;
								  }
								  else {
									  strField.push_back(ch);
								  }
			}
				break;

			case FieldSeparator: { // �ֶηָ�
									 if (ch == ',') {
										 Fields.push_back("");
									 }
									 else if (ch == '"') {
										 strField.clear();
										 State = QuotesField;
									 }
									 else if (ch == '\r') {
										 Fields.push_back("");
										 State = RowSeparator;
									 }
									 else {
										 strField.push_back(ch);
										 State = NonQuotesField;
									 }
			}
				break;

			case QuoteInQuotesField: { // �����ֶ��е�����
										 if (ch == ',') {
											 // �����ֶαպ�
											 Fields.push_back(strField);
											 strField.clear();
											 State = FieldSeparator;
										 }
										 else if (ch == '\r') {
											 // �����ֶαպ�
											 Fields.push_back(strField);
											 State = RowSeparator;
										 }
										 else if (ch == '"') {
											 // ת��
											 strField.push_back(ch);
											 State = QuotesField;
										 }
										 else {
											 m_strErrorInfo = "�﷨���� ת���ַ� \" �������ת�� �� �����ֶν�β����û�н����ֶηָ���";
											 State = Error;
										 }
			}
				break;

			case RowSeparator: { // �зָ����ַ�1���س�
								   if (ch == '\n') {
									   m_content.push_back(Fields);
									   Fields = Row(); // Fields.clear();
									   strField.clear();
									   State = NewFieldStart;
								   }
								   else {
									   m_strErrorInfo = "�﷨���� �зָ����˻س� \\r����δʹ�ûس����� \\r\\n ";
									   State = Error;
								   }
			}
				break;

			case Error: { // �﷨����
							return;
			}
				break;

			default: break;
			}
		}
		// end for

		switch (State) {
		case NewFieldStart: {
								// Excel������CSVÿ�ж���/r/n��β���������һ��
		}
			break;

		case NonQuotesField: {
								 Fields.push_back(strField);
								 m_content.push_back(Fields);
		}
			break;

		case QuotesField: {
							  m_strErrorInfo = "�﷨���� �����ֶ�δ�պ�";
		}
			break;

		case FieldSeparator: {
								 Fields.push_back("");
								 m_content.push_back(Fields);
		}
			break;

		case QuoteInQuotesField: {
									 Fields.push_back(strField);
									 m_content.push_back(Fields);
		}
			break;

		case RowSeparator: {

		}
			break;

		case Error: {

		}
			break;

		default: break;
		}

		setHeader();
	}


	void CSVUtils::Csv::setHeader()
	{
		m_header.clear();
		for (int i = 0; i < m_content[0].size(); i++) {
			m_header.push_back(m_content[0][i]);
		}
		for (int i = 0; i < m_content.size(); i++) {
			m_content[i].setHeader(&m_header);
		}
	}


	CSVUtils::Row& CSVUtils::Csv::operator[](unsigned int key)
	{
		if (key < m_content.size()) return m_content[key];
		throw "can't return this row (doesn't exist)";
	}
}