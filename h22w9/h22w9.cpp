#include <iostream>
#include <string>
#include <exception>

using namespace std;

// Task 1
int StringToInt(const string& str) {
    if (str.empty()) {
        throw invalid_argument("Empty string");
    }

    long long result = 0;
    int startIndex = 0;
    bool isNegative = false;

    if (str[0] == '-') {
        isNegative = true;
        startIndex = 1;
    }
    else if (str[0] == '+') {
        startIndex = 1;
    }

    if (startIndex == (int)str.length()) {
        throw invalid_argument("Invalid format");
    }

    for (int i = startIndex; i < (int)str.length(); i++) {
        if (str[i] < '0' || str[i] > '9') {
            throw invalid_argument("Invalid character");
        }
        int digit = str[i] - '0';
        result = result * 10 + digit;

        if (!isNegative && result > 2147483647) {
            throw out_of_range("Overflow for int");
        }
        if (isNegative && -result < -2147483648) {
            throw out_of_range("Underflow for int");
        }
    }

    if (isNegative) {
        result = -result;
    }

    return (int)result;
}

// Task 2
class DynamicCharStack {
private:
    char* _data;
    int _top;
    int _capacity;

public:
    DynamicCharStack(int initialCapacity = 2) {
        if (initialCapacity <= 0) {
            throw invalid_argument("Initial capacity must be greater than zero");
        }
        _capacity = initialCapacity;
        _data = new char[_capacity];
        _top = -1;
    }

    ~DynamicCharStack() {
        delete[] _data;
    }

    void Push(char val) {
        if (_top >= _capacity - 1) {
            int newCapacity = _capacity * 2;
            char* newData = nullptr;
            try {
                newData = new char[newCapacity];
            }
            catch (const bad_alloc& e) {
                throw;
            }
            for (int i = 0; i <= _top; i++) {
                newData[i] = _data[i];
            }
            delete[] _data;
            _data = newData;
            _capacity = newCapacity;
        }
        _top++;
        _data[_top] = val;
    }

    char Pop() {
        if (IsEmpty()) {
            throw underflow_error("Stack underflow");
        }
        char val = _data[_top];
        _top--;
        return val;
    }

    int GetCount() const {
        return _top + 1;
    }

    bool IsEmpty() const {
        return _top == -1;
    }

    void Clear() {
        _top = -1;
    }

    char Peek() const {
        if (IsEmpty()) {
            throw underflow_error("Stack is empty");
        }
        return _data[_top];
    }
};