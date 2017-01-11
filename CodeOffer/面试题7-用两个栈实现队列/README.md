[TOC]



# 题目

**内容**：用两个栈实现一个队列。队列的声明如下，请实现它的两个函数appendTail和deleteHead，分别完成在队列尾部插入节点和在队列头部删除节点的功能。

预置代码：

``` c++
template <typename T> 
class StackQueue {
public:
  StackQueue();
  ~StackQueue();
  
  void appendTail(const T &node);
  T deleteHead();
  
private:
  stack<T> stack1;
  stack<T> stack2;
};
```

# 思路

如上预置代码所示，我们设stack1为压入栈，并设stack2为弹出栈。于是，整体的思路就是：

* 元素入队：直接将元素压入stack1即可
* 元素出队：如果stack2为空，则首先将stack1中的所有元素依次压入到stack2中，然后从stack2中弹出元素；如果stack2不为空，则直接从stack2中弹出元素即可。

详细代码：

``` c++
template <typename T>
class StackQueue {
public:
	StackQueue() { 
	}

	~StackQueue() { 
	}

	void appendTail(const T &node) {
		stack1.push(node);
	}

	T deleteHead() {
		if (stack2.empty()) {
			while (!stack1.empty()) {
				T node = stack1.top();
				stack1.pop();
				stack2.push(node);
			}
		}
      
      	if (stack2.empty())
          throw new exception("Empty queue.");

		T val = stack2.top();
		stack2.pop();

		return val;
	}


private:
	std::stack<T> stack1; // Used for pushing
	std::stack<T> stack2; // Used for poping
};
```



# 测试用例

* 往空的队列里添加元素、删除元素；
* 往非空的队列中添加、删除元素；
* 连续删除元素直至队列为空。

# 拓展

**用两个队列实现一个栈**。

``` c++
template <typename T>
class QueueStack  {
public:
	QueueStack();
	~QueueStack();

	void pushStack(const T &node);
	T popStack();

private:
	std::queue<T> queue1; // Used for pushing and poping
	std::queue<T> queue2; // Used for transfer station
};
```

**思路：**

一个队列为压入队列，一个队列作为中转栈。

整体过程如下：

* 元素入栈：直接push进入queue1即可。
* 元素出栈：先将queue1中除最后一个元素的其他所有元素push到queue2中，然后pop队列queue1中的剩余一个元素，最后再将queue2中的所有元素push进入queue1中即可。

详细代码：

``` c++
template <typename T>
class QueueStack  {
public:
	QueueStack() {
	}

	~QueueStack() {
	}

	void pushStack(const T &node) {
		queue1.push(node);
	}

	T popStack() {
		if (queue1.empty())
			throw new exception("Empty stack.");

		while (queue1.size() > 1) {
			T node1 = queue1.front();
			queue1.pop();
			queue2.push(node1);
		}

		T val = queue1.front();
		queue1.pop();

		while (!queue2.empty()) {
			T node2 = queue2.front();
			queue2.pop();
			queue1.push(node2);
		}

		return val;
	}

private:
	std::queue<T> queue1; // Used for pushing and poping
	std::queue<T> queue2; // Used for transfer station
};
```

