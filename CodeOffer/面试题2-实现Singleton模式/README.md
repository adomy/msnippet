[TOC]

# 题目

**内容**：设计一个类，我们只能生成该类的一个实例。

# 分析

只能生成一个实例的类是实现了Singleton（单例）模式的类型。由于设计模式在面向对象程序设计中起着举足轻重的作用，在面试过程中很多公司都喜欢问一些与设计模式相关的问题。

# 不好的解法

## 解法一：只使用单线程环境

由于要求只能生成一个实例，因此我们必须把构造函数设为私有函数以禁止他人创建实例。

``` c++
class Singleton {
public:
	static Singleton* getInstance() {
		if (this->instance == NULL) 
			this->instance = new Singleton();

		return this->instance;
	}

private:
	Singleton();
	~Singleton();

	static Singleton *instance;
};
```

这里，说句题外话，私有化析构函数。

> 私有析构函数的作用：令对象只能在堆上生成，即用new方法。原理是C++是一个静态绑定语言，在编译过程中，所有的非虚函数调用都必须分析完成（虚函数也要检查可访问性）。因此，当在栈上生成对象时，对象会自动析构，即析构函数必须可以访问。而在堆上生成对象时，析构步骤由程序员控制，不一定需要析构函数。同时，此生成对象不能直接delete删除，析构过程还需要一个专门的成员函数（代码中的destory()函数）。



## 解法二：虽然在多线程环境中能够工作但效率不高

解法一不适用于多线程环境，因此，需要通过加锁来实现互斥。

``` c++
class Singleton {
public:
	static Singleton* getInstance() {
      	MutexLockGurad mlg(&mutex);
		if (this->instance == NULL) 
			this->instance = new Singleton();

		return this->instance;
	}

private:
	Singleton();
	~Singleton();

  	static Mutex mutex;
	static Singleton *instance;
};
```

无疑，该方法能够正常工作于多线程环境。但是，每次都需要进行加锁和解锁过程，这是一个极为耗时的过程。因此，在没有必要的时候我们应该尽量避免。

# 可行的解法

## 解法三：加同步锁前后两次判断实例是否已存在



我们只是在实例没有创建之前需要加锁操作，以保证只有一个线程创建出实例。而当实例已经创建后，我们已经不需要再做加锁操作了。

``` c++
class Singleton {
public:
	static Singleton* getInstance() {
		if (this->instance == NULL) {
			MutexLockGurad mlg(&mutex);

			if (this->instance == NULL)
				this->instance = new Singleton();
		}

		return this->instance;
	}

private:
	Singleton();
	~Singleton();

	static MutexLock mutex;
	static Singleton *instance;
};
```

在该解法中，只有当instance为NULL即没有创建时，需要进行加锁操作。当instance已经创建出来之后，则无需加锁。

该解法用加锁机制来确保在多线程环境下只创建一个实例，并且用两个if来提高效率。

## 解法四：静态构造函数（静态初始化块）

**备注**：C++本身不支持静态构造函数，因此，从某种程度上来说，前面所讲的C++中的单例模式是所谓的饿汉模式，而不是饱汉模式。

下面的代码是java单例模式（饱汉）：

``` java
public class Singleton {
	private Singleton() {
      
	}
  
  	private static Singleton instance = new Singleton();
  
  	public static Singleton getInstance() {
      	return instance;
  	}
}
```

还有一种解法是按需创建实例。但C++本身不能很好地支持某些特性。故不详解。



# 解法比较

**解法一**在多线程环境下不能正常工作。

**解法二**虽然能在多线程环境下正常工作，但时间效率很低。

**解法三**通过两次判断一次加锁确保在多线程环境能高效工作。

**解法四**利用java的静态构造函数（静态初始化块）等特性，实现了基于饱汉型的单例模式。

