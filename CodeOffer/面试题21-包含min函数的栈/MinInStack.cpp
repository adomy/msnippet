#include <iostream>
#include <stack>

template <typename T>
class StackWithMin {
public:
	StackWithMin() {
	}

	~StackWithMin() {
	}

	void push(const T &val) {
		m_data.push(val);

		if (m_min.size() == 0 || val < m_min.top())
			m_min.push(val);
		else
			m_min.push(m_min.top());
	}

	void pop() {
		m_data.pop();
		m_min.pop();
	}

	const T &min() {
		return m_min.top();
	}
private:
	std::stack<T> m_data;
	std::stack<T> m_min;
};


int main() {
	StackWithMin<int> minStack;
	minStack.push(1);
	minStack.push(2);
	minStack.push(3);
	minStack.push(-2);
	minStack.push(99);
	std::cout << minStack.min() << std::endl;
	minStack.pop();
	std::cout << minStack.min() << std::endl;
	minStack.pop();
	std::cout << minStack.min() << std::endl;
	minStack.pop();
	minStack.push(2);
	minStack.push(0);
	minStack.push(-1);
	std::cout << minStack.min() << std::endl;
	minStack.pop();
	return 0;
}