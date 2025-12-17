#include "expressionEveluationCalculator.hpp"
#include <cmath>
#include <array>
#include <QDebug>
using namespace calculator;
const size_t default_stack_buffer_size = 256;
constexpr std::array<unsigned long long, 21> factorial20 = {
    1ULL, 1ULL, 2ULL, 6ULL, 24ULL, 120ULL, 720ULL, 5040ULL, 40320ULL, 362880ULL,
    3628800ULL, 39916800ULL, 479001600ULL, 6227020800ULL, 87178291200ULL,
    1307674368000ULL, 20922789888000ULL, 355687428096000ULL,
    6402373705728000ULL, 121645100408832000ULL, 2432902008176640000ULL
};


NormalExpression::NormalExpression(): return_string("") {}

bool NormalExpression::isSpace(const char& c) {
    return (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f');
}

std::string NormalExpression::deleteSpace(const std::string& str) {
        std::string result = "";
    for (int i = 0; i < str.size(); i++) {
        if (!isSpace(str[i])) {
            result += str[i];
        }
    }

    return result;
}

double NormalExpression::calculate(std::string expression) {

    auto applyOperator = [&] (const double _number1, const double _number2, const char _operator) -> double {
        switch (_operator) {
            case '+':
                return _number1 + _number2;
            case '-':
                return _number1 - _number2;
            case '*':
                return _number1 * _number2;
            case '/':
                if (_number2 == 0.0)
                    return_string += "ERROR: Divided by zero!\n";
                return _number1 / _number2;
            case '^':
                return std::pow(_number1, _number2);
            default:
                return std::numeric_limits<double>::quiet_NaN();
        }
    };

    auto getPrecedence = [] (const char _operator) -> int {
        if (_operator == '+' || _operator == '-') {
            return 1;
        }
        if (_operator == '*' || _operator == '/') {
            return 2;
        }
        if (_operator == '^') {
            return 3;
        }
        return 0;
    };

    auto isInteger = [] (const double _number) -> bool {
        if (std::isnan(_number) || std::isinf(_number))
            return false;

        if (std::abs(_number) > 1e15)
            return _number == std::floor(_number);
        
        double epsilon = std::numeric_limits<double>::epsilon() * std::abs(_number);
        double diff = std::abs(_number - std::round(_number));

        return diff <= std::max(epsilon, 1e-15);
    };

    auto factorial = [&isInteger] (const double _number) -> double {
        // qDebug() << "calculating the factorial of " << _number;
        if (!isInteger(_number) || _number < 0)
            return std::numeric_limits<double>::quiet_NaN();
        if (_number > 20)
            return std::numeric_limits<double>::infinity();

        return static_cast<double>(factorial20[static_cast<int>(_number)]);
    };

    Stack<double> values;
    Stack<char> ops;
    size_t i = 0;
    
    try {
    while (i < expression.size()) {
        if (std::isdigit(expression[i])) {
            double value = 0;
            bool has_met_decimal_point = false;
            while(i < expression.size() && std::isdigit(expression[i])) {
                value = value * 10 + (expression[i] - '0');
                ++i;
            }

            if (expression[i] == '.') {
                has_met_decimal_point = true;
                ++i;
            }
            
            for (int decimal_place = 1; has_met_decimal_point && i < expression.size() && std::isdigit(expression[i]); ++i, ++decimal_place) {
                value += (expression[i] - '0') * std::pow(0.1, decimal_place);
            }

            values.push(value);
        }

        else if (expression[i] == '(' ) {
            ops.push(expression[i]);
            ++i;
        }

        else if (expression[i] == ')' ) {
            while (!ops.empty() && ops.top() != '(' ) {
                int number2 = values.top();
                values.pop();
                int number1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                double value = applyOperator(number1, number2, op);
                if (std::isnan(value) || std::isinf(value)) {
                    return value;
                }
                values.push(value);
            }
            ops.pop();
            ++i;
        }

        else if (expression[i] == '!') {
            if (values.empty()) {
                return_string += "No number was found befor \'!\'!\n";
                return std::numeric_limits<double>::quiet_NaN();
            }

            double value = values.top();
            values.pop();
            value = factorial(value);
            if (std::isinf(value)) {
                return_string += "Too big number for factorial!\n";
                return value;
            }
            if (std::isnan(value)) {
                return_string += "Factorials cannot be applied to non-integers!\n";
                return value;
            }
            values.push(value);
            ++i;
        }

        else if (expression[i] == '-' && (i == 0 || !isdigit(expression[i - 1]) && expression[i - 1] != ')')) {
            ++i;
            double value = 0;
            bool has_met_decimal_point = false;
            while(i < expression.size() && std::isdigit(expression[i])) {
                value = value * 10 + (expression[i] - '0');
                ++i;
            }

            if (expression[i] == '.') {
                has_met_decimal_point = true;
                ++i;
            }
            
            for (int decimal_place = 1; has_met_decimal_point && i < expression.size() && std::isdigit(expression[i]); ++i, ++decimal_place) {
                value += (expression[i] - '0') * std::pow(0.1, decimal_place);
            }

            values.push(-value);
        }

        else {
            while (!ops.empty() && getPrecedence(ops.top()) >= getPrecedence(expression[i])) {
                double number2 = values.top();
                values.pop();
                double number1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                double value = applyOperator(number1, number2, op);
                if (std::isnan(value) || std::isinf(value)) {
                    return value;
                }
                values.push(value);
            }
            ops.push(expression[i]);
            ++i;
        }
    }

    while (!ops.empty()) {
        double number2 = values.top();
        values.pop();
        double number1 = values.top();
        values.pop();
        char op = ops.top();
        ops.pop();
        double value = applyOperator(number1, number2, op);
        if (std::isnan(value) || std::isinf(value)) {
            return value;
        }
        values.push(value);
    }
    

    }
    catch (std::out_of_range& e) {
        return_string += "Invalid input! ";
        return_string += e.what();
        return_string += "\n";
        return 0;
    }
    catch (std::runtime_error& e) {
        return_string += "Expression too long! ";
        return_string += e.what();
        return_string += "\n";
    }
    catch (std::exception& e) {
        return_string += "Something went wrong... ";
        return_string += e.what();
        return_string += "\n";
    }
    return values.top();
}
