#ifndef EXPRESSION_EVELUATION_CALCULATOR_HPP
#define EXPRESSION_EVELUATION_CALCULATOR_HPP

#include <string>
#include <limits>
#include <stdexcept>
#include <cmath>
#include <cctype>

namespace calculator {
	const size_t default_stack_buffer_size = 256;
	
    template<typename T>
    class Stack {
        T* data;
        size_t top_index;
        size_t buffersize;

    public:
        Stack();
        Stack(const Stack& );
        Stack(const size_t );
        ~Stack();

        void resize(const size_t );

        void push(const T );
        T& top() const;
        void pop();


        bool empty() const;

        void clear();
    };

    class NormalExpression {
        bool isSpace(const char& );

    public:
		std::string return_string;
		
		NormalExpression();

        std::string deleteSpace(const std::string& );

        double calculate(std::string );
        
    };
    
    template<typename T>
	Stack<T>::Stack(): 
	data(new T[default_stack_buffer_size]),  top_index(0), buffersize(default_stack_buffer_size) {}
	
	template<typename T>
	Stack<T>::Stack(const size_t customized_stack_buffer_size):
	data(new T[customized_stack_buffer_size]), top_index(0), buffersize(customized_stack_buffer_size) {}
	
	template<typename T>
	Stack<T>::Stack(const Stack& other):
	data(new T[other.buffersize]), top_index(0), buffersize(other.buffersize) {
	    while (top_index < other.top_index) {
	        data[top_index] = other.data[top_index];
	        ++top_index;
	    }
	
	    top_index = other.top_index;
	}
	
	template<typename T>
	Stack<T>::~Stack() {
	    delete[] data;
	}
	
	template<typename T>
	void Stack<T>::resize(const size_t new_stack_buffer_size) {
	    T* newdata = new T[new_stack_buffer_size];
	    for (int i = 0; i < top_index; i++) {
	        newdata[i] = data[i];
	    }
	
	    delete[] data;
	    data = newdata;
	    buffersize = new_stack_buffer_size;
	}
	
	template<typename T>
	void Stack<T>::push(const T value) {
	    if (top_index == buffersize && buffersize < std::numeric_limits<size_t>::max() / 2) {
	        this->resize(buffersize << 1);
	    }else if (top_index == buffersize && buffersize < std::numeric_limits<size_t>::max()) {
	        this->resize(std::numeric_limits<size_t>::max());
	    }else if (top_index == buffersize && buffersize == std::numeric_limits<size_t>::max()) {
	        throw std::runtime_error("Stack capacity overflow: Buffersize cannot be larger!");
	        return;
	    }
	    data[top_index++] = value;
	}
	
	template<typename T>
	T& Stack<T>::top() const {
	    if (top_index == 0) {
	        throw std::out_of_range("Cannot get the top data! The Stack is empty!");
	    }
	
	    return data[top_index - 1];
	}
	
	template<typename T>
	void Stack<T>::pop() {
	    if (top_index == 0) {
	        throw std::out_of_range("Cannot pop! The Stack is empty!");
	    }
	
	    --top_index;
	}
	
	template<typename T>
	bool Stack<T>::empty() const {
	    return top_index == 0;
	}
	
	template<typename T>
	void Stack<T>::clear() {
	    top_index = 0;
	}
	
	template class Stack<int>;
	template class Stack<double>;
};

#endif
