#include <iostream>
#include <cstring>

class MyString {
public:
	MyString(char *pData = NULL) {
		this->m_pData = pData;
	}

	MyString(const MyString &str) {
		delete this->m_pData;
		this->m_pData = NULL;

		this->m_pData = new char[std::strlen(str.m_pData) + 1];
		std::strcpy(this->m_pData, str.m_pData);
	}

	~MyString() {
		delete m_pData;
	}

	// 经典的解法，适用于初级程序员
	MyString& operator = (const MyString &str) {
		if (this == &str)
			return *this;

		delete this->m_pData;
		this->m_pData = NULL;

		this->m_pData = new char[std::strlen(str.m_pData) + 1];
		std::strcpy(this->m_pData, str.m_pData);

		return *this;
	}

	//考虑异常安全性的解法，高级程序员必备
	MyString& operator = (const MyString &str) {
		if (this != &str) {
			MyString strTemp(str);

			// 交换临时实例和原来的实例
			char *pTemp = strTemp.m_pData;
			strTemp.m_pData = this->m_pData;
			this->m_pData = pTemp;
		}
		
		return *this;
	}

private:
	char *m_pData;
};




