[TOC]

# 题目

**内容**：如下为类型MyString的声明，请为该类型添加赋值运算符函数。

``` c++
class MyString {
public:
	MyString(char *pData = NULL);
	MyString(const MyString &str);
	~MyString();
  
private:
	char *m_pData;
};
```

# 分析

当面试官要求应聘者定义一个赋值运算符函数时，他会在检查应聘者写出的代码时关注如下几点：

* **是否把返回值的类型声明为该类型的引用，并在函数结束前返回实例自身的引用（即*this）**。只有返回一个引用，才可以允许连续赋值。否则，如果函数的返回值是void，应用该赋值运算符将不能做连续赋值。


* **是否把传入的参数的类型声明为常量引用**。如果传入的参数不是引用而是实例，那么从形参到实参会调用一次复制构造函数。把参数声明为引用可以避免这样的无谓消耗，能提高代码的效率。同时，我们在赋值运算符函数内不会改变传入的实例的状态，因此应该为传入的引用参数加上const关键字。
* **是否释放实例自身已有的内存**。如果我们忘记在分配新内存之前释放自身已有的空间，程序将出现内存泄露。
* **是否判断传入的参数和当前的实例（*this）是不是同一个实例**。如果是同一个，则不进行赋值操作，直接返回。如果事先不判断就进行赋值，那么在释放实例自身的内存的时候就会导致严重的问题：当*this和传入的参数是同一个实例时，那么一旦释放了自身的内存，传入的参数的内存也同时被释放了。

# 经典解法

``` c++
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
```

该解法适用于初级程序员。

# 考虑异常安全性的解法

在前面的函数中，我们在分配内存之前先用delete释放了实例m_pData的内存。如果此时内存不足导致new char时抛出异常，m_pData将是一个空指针，这样非常容易导致程序崩溃。也就是说，一旦在赋值运算符函数内抛出一个异常，MyString的实例不再保持有效的状态，这就违背了异常安全性（Exception Safety）原则。

两种方法：

* 先new char分配新内容，再delete释放已有的内容。
* 创建临时实例，再交换临时实例和原来的实例。

``` c++
	//考虑异常安全性的解法，高级程序员必备
	MyString& operator = (const MyString &str) {
		if (this != &str) {
			MyString strTemp(str);
			char *pTemp = strTemp.m_pData;
			strTemp.m_pData = this->m_pData;
			this->m_pData = pTemp;
		}
		
		return *this;
	}
```

在新的代码中，我们在MyString的构造函数里用new分配内存。如果由于内存不足抛出诸如bad_alloc等异常，我们还没有修改原来实例的状态，因此实例的状态还是有效的，这也就保证了异常安全性。

