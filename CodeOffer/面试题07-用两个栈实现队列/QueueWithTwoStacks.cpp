#include <stack>
#include <queue>
#include <exception>
#include <iostream>

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

int main() {
	StackQueue<int> q;
	q.appendTail(12);
	q.appendTail(123);
	q.appendTail(88);
	q.appendTail(82);
	int val;
	val = q.deleteHead();
	std::cout << val << std::endl;
	val = q.deleteHead();
	std::cout << val << std::endl;
	val = q.deleteHead();
	std::cout << val << std::endl;
	val = q.deleteHead();
	std::cout << val << std::endl;

	QueueStack<int> s;
	s.pushStack(12);
	s.pushStack(1);
	s.pushStack(122);
	s.pushStack(92);
	val = s.popStack();
	std::cout << val << std::endl;
	val = s.popStack();
	std::cout << val << std::endl;
	val = s.popStack();
	std::cout << val << std::endl;
	val = s.popStack();
	std::cout << val << std::endl;

	return 0;
}