#include "widget.h"
#include "./ui_widget.h"
#include "expressionEveluationCalculator.hpp"
#include "polynomial.hpp"
#include <QMessageBox>
#include <sstream>
#include <iomanip>
#include <regex>
#include <QDebug>

std::string useNormalExpressionCalculator(std::string expression);
std::string usePolynomialCalculator(std::string expression);
std::string readPolynomial(UnivariatePolynomial& poly, const std::string& expression);
std::string useCalculator(std::string expression);

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::calculator)
{
    ui->setupUi(this);

    this->setWindowTitle("Calculator");
    this->setWindowIcon(QIcon(":/icon/calculator.png"));

    this->setFocusPolicy(Qt::StrongFocus);
    this->setFocus();
    
    ui->expression_line_edit->setFocusPolicy(Qt::NoFocus);
    ui->expression_line_edit->setReadOnly(true);

    QList<QPushButton*> buttons = this->findChildren<QPushButton*>();
    for (QPushButton* btn : buttons) {
        btn->installEventFilter(this);
    }

    ui->expression_line_edit->installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::Resize) {
        if (QPushButton *button = qobject_cast<QPushButton*>(obj)) {
            int fontSize = qMin(button->width(), button->height()) / 3;
            fontSize = qMax(14, fontSize);
            QFont font = button->font();
            font.setPointSize(fontSize);
            button->setFont(font);
        }
    }

    if (obj == ui->expression_line_edit && event->type() == QEvent::Resize) {
        QLineEdit *edit = static_cast<QLineEdit*>(obj);
        int fontSize = qMin(edit->height() / 5, edit->width() / 20);
        fontSize = qMax(14, fontSize);
        fontSize = qMin(48, fontSize);

        QFont font = edit->font();
        font.setPointSize(fontSize);
        edit->setFont(font);
    }
    return QWidget::eventFilter(obj, event);
}


void Widget::on_number_button_1_clicked()
{
    expression += "1";
    ui->expression_line_edit->setText(expression);
}


void Widget::on_number_button_2_clicked()
{
    expression += "2";
    ui->expression_line_edit->setText(expression);
}


void Widget::on_number_button_3_clicked()
{
    expression += "3";
    ui->expression_line_edit->setText(expression);
}


void Widget::on_number_button_4_clicked()
{
    expression += "4";
    ui->expression_line_edit->setText(expression);
}


void Widget::on_number_button_5_clicked()
{
    expression += "5";
    ui->expression_line_edit->setText(expression);
}


void Widget::on_number_button_6_clicked()
{
    expression += "6";
    ui->expression_line_edit->setText(expression);
}


void Widget::on_number_button_7_clicked()
{
    expression += "7";
    ui->expression_line_edit->setText(expression);
}


void Widget::on_number_button_8_clicked()
{
    expression += "8";
    ui->expression_line_edit->setText(expression);
}


void Widget::on_number_button_9_clicked()
{
    expression += "9";
    ui->expression_line_edit->setText(expression);
}


void Widget::on_number_button_0_clicked()
{
    expression += "0";
    ui->expression_line_edit->setText(expression);
}


void Widget::on_alpha_button_x_clicked()
{
    expression += "x";
    ui->expression_line_edit->setText(expression);
}


void Widget::on_symbol_button_point_clicked()
{
    expression += ".";
    ui->expression_line_edit->setText(expression);
}


void Widget::on_symbol_button_plus_clicked()
{
    expression += "+";
    ui->expression_line_edit->setText(expression);
}


void Widget::on_symbol_button_substract_clicked()
{
    expression += "-";
    ui->expression_line_edit->setText(expression);
}


void Widget::on_symbol_button_multiple_clicked()
{
    expression += "*";
    ui->expression_line_edit->setText(expression);
}


void Widget::on_symbol_button_division_clicked()
{
    expression += "/";
    ui->expression_line_edit->setText(expression);
}


void Widget::on_symbol_button_power_clicked()
{
    expression += "^";
    ui->expression_line_edit->setText(expression);
}


void Widget::on_symbol_button_left_bracket_clicked()
{
    expression += "(";
    ui->expression_line_edit->setText(expression);
}


void Widget::on_symbol_button_right_bracket_clicked()
{
    expression += ")";
    ui->expression_line_edit->setText(expression);
}


void Widget::on_function_button_all_clear_clicked()
{
    expression.clear();
    ui->expression_line_edit->clear();
}


void Widget::on_function_button_delete_clicked()
{
    expression.chop(1);
    ui->expression_line_edit->setText(expression);

}


void Widget::on_expression_line_edit_textEdited(const QString &arg1)
{
    expression = arg1;
}


void Widget::on_symbol_button_factorial_clicked()
{
    expression += "!";
    ui->expression_line_edit->setText(expression);
}


void Widget::on_symbol_button_equal_clicked()
{
    if (expression.size() <= 0) return;
    QString answer = QString::fromStdString(useCalculator(expression.toStdString()));
    // QString answer = expression;
    if (answer.size() < 20) {
        expression = answer;
        ui->expression_line_edit->setText(expression);
    }
    else {
        QMessageBox msg_box(this);
        msg_box.setWindowTitle("Long Answer");
        msg_box.setText(answer);

        msg_box.setStyleSheet(R"(
            QMessageBox {
                background: rgb(32,32,32);
                font-family: "Consolas";
                font-size: 16px;
                color: white;

            }
            QLabel {
                background: rgb(32,32,32);
                font-family: "Consolas";
                font-size: 16px;
                color: white;
            }

            QPushButton {
                background: #000000;
                color: #ffffff;
                padding: 3px 15px;
                border: 2px solid rgb(20,250,250);
                border-radius: 8px;
            }
            )"
        );

        msg_box.exec();
    }
}


void Widget::on_expression_line_edit_returnPressed()
{
    on_symbol_button_equal_clicked();
}


void Widget::keyPressEvent(QKeyEvent *event) {
    qDebug() << "Key:" << event->key() << "Text:" << event->text();

    if (event->key() >= Qt::Key_A && event->key() <= Qt::Key_Z) {
        on_alpha_button_x_clicked();
        return;
    }
    switch (event->key()) {
    case Qt::Key_1:
        on_number_button_1_clicked();
        break;
    case Qt::Key_2:
        on_number_button_2_clicked();
        break;
    case Qt::Key_3:
        on_number_button_3_clicked();
        break;
    case Qt::Key_4:
        on_number_button_4_clicked();
        break;
    case Qt::Key_5:
        on_number_button_5_clicked();
        break;
    case Qt::Key_6:
        on_number_button_6_clicked();
        break;
    case Qt::Key_7:
        on_number_button_7_clicked();
        break;
    case Qt::Key_8:
        on_number_button_8_clicked();
        break;
    case Qt::Key_9:
        on_number_button_9_clicked();
        break;
    case Qt::Key_0:
        on_number_button_0_clicked();
        break;
    case Qt::Key_ParenLeft:
        on_symbol_button_left_bracket_clicked();
        break;
    case Qt::Key_ParenRight:
        on_symbol_button_right_bracket_clicked();
        break;
    case Qt::Key_Period:
        on_symbol_button_point_clicked();
        break;
    case Qt::Key_Plus:
        on_symbol_button_plus_clicked();
        break;
    case Qt::Key_Minus:
        on_symbol_button_substract_clicked();
        break;
    case Qt::Key_multiply:
    case Qt::Key_Asterisk:
        on_symbol_button_multiple_clicked();
        break;
    case Qt::Key_Slash:
    case Qt::Key_division:
        on_symbol_button_division_clicked();
        break;
    case Qt::Key_AsciiCircum:
        on_symbol_button_power_clicked();
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
    case Qt::Key_Equal:
        on_symbol_button_equal_clicked();
        break;
    case Qt::Key_Backspace:
        on_function_button_delete_clicked();
        break;
    case Qt::Key_Delete:
        on_function_button_all_clear_clicked();
        break;
    case Qt::Key_Exclam:
        on_symbol_button_factorial_clicked();
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

// ------------------------------

std::string useNormalExpressionCalculator(std::string expression) {

    calculator::NormalExpression cal;

    double result = cal.calculate(expression);
    std::ostringstream oss;
    if (std::isnan(result)) {
        oss << "Oops! You've got a NaN! Check your expression.\n" << cal.return_string << '\n';
    }
    else if (std::isinf(result)) {
        oss << "Oops! You've got a Infinity! Check your expression.\n" << cal.return_string << '\n';
    }
    else if (cal.return_string != "") {
        oss << cal.return_string;
    }
    oss << result;
    return oss.str();
}

std::string usePolynomialCalculator(std::string expression) {

    auto deleteSpace = [] (const std::string& _str) {
        std::string _result = "";
        for (size_t i = 0; i < _str.size(); ++i) {
            if (!std::isspace(_str[i])) {
                _result += _str[i];
            }
        }

        return _result;
    };

    auto deleteBrackets = [] (const std::string& _str) {
        std::string _result = "";

        calculator::Stack<int> _sym;
        _sym.push(1);
        for (size_t _i = 0; _i < _str.size(); ++_i) {
            if (_str[_i] == '(' && _i == 0) {
                _sym.push(1);
            }
            else if (_str[_i] == '(' && _str[_i - 1] == '-') {
                _sym.push(-1 * _sym.top());
            }
            else if (_str[_i] == '(') {
                _sym.push(_sym.top());
            }
            else if (_str[_i] == ')') {
                _sym.pop();
            }
            else if (_str[_i] == '+') {
                _result += _sym.top() == 1 ? '+' : '-';
            }
            else if (_str[_i] == '-') {
                _result += _sym.top() == 1 ? '-' : '+';
            }
            else {
                _result += _str[_i];
            }
        }
        return _result;
    };

    std::regex times_sign_pattern(R"(([^\*]+)\*(.+)|([^\*]+))");
    std::smatch matches;

    std::string remaining = expression;
    UnivariatePolynomial result, temp;

    std::string error_string = "";
    while (remaining != "" && std::regex_match(remaining, matches, times_sign_pattern)) {
        if (matches[3].matched) {
            error_string = readPolynomial(temp, deleteBrackets(matches[3].str()));
            remaining = "";
        }
        else {
            error_string = readPolynomial(temp, deleteBrackets(matches[1].str()));
            remaining = matches[2].str();
        }

        if (error_string != "") {
            return error_string;
        }

        if (result.empty()) {
            result = temp;
        }
        else {
            result = result * temp;
        }
    }

    UnivariatePolynomial result_derivative = result.derivative();
    std::ostringstream oss;
    oss << result << std::endl << "derivative is: " << result_derivative;
    return oss.str();
}

std::string readPolynomial(UnivariatePolynomial& poly, const std::string& expression) {
    poly.clear();

    if (expression.empty()) return "The expression is empty!";

    size_t i = 0;
    std::regex var_pattern(R"(([+-]?(?:\d*\.\d+|\d+\.?))[a-zA-Z](?:\^([+-]?\d+))?)");
    std::regex simple_var_pattern(R"(([+-]?)[a-zA-Z](?:\^([+-]?\d+))?)");
    std::regex const_pattern(R"(^[+-]?(?:\d*\.\d+|\d+\.?))");

    std::smatch matches;

    while (i < expression.size()) {
        std::string remaining = expression.substr(i);
        double coef = 1.0;
        int exp = 0;
        size_t length = 0;
        bool is_matched = false;

        if (std::regex_search(remaining, matches, var_pattern)) {
            if (matches.position() == 0) {
                length = matches[0].length();
                coef = std::stod(matches[1].str());
                exp = matches[2].matched ? std::stoi(matches[2].str()) : 1;
                is_matched = true;
            }
        }

        if (!is_matched && std::regex_search(remaining, matches, simple_var_pattern)) {
            if (matches.position() == 0) {
                length = matches[0].length();
                coef = (matches[1].str() == "-") ? -1.0 : 1.0;
                exp = matches[2].matched ? std::stoi(matches[2].str()) : 1;
                is_matched = true;
            }
        }

        if (!is_matched && std::regex_search(remaining, matches, const_pattern)) {
            if (matches.position() == 0) {
                length = matches[0].length();
                coef = std::stod(matches[0].str());
                exp = 0;
                is_matched = true;
            }
        }

        if (!is_matched) {
            std::ostringstream oss;
            oss << "Error parsing polynomial. Remaining: \"" << remaining << "\"\n";
            poly.clear();
            return oss.str();
        }

        poly.add(coef, exp);
        i += length;
    }
    return "";
}

std::string useCalculator(std::string expression) {
    qDebug() << "Using calculator.";
    std::regex factorial_pattern(R"((\d*)!)");
    std::smatch matches;
    if (std::regex_match(expression, matches, factorial_pattern)) {
        int number = std::stoi(matches[0].str());
        if (number > 20) {
            return "Number too big for factorial!";
        }
        uint64_t result = 1;
        for (int i = 1; i <= number; ++i) {
            result *= i;
        }
        return std::to_string(result);
    }

    bool is_polynomial = false;
    for (const auto& c : expression) {
        if (std::isalpha(c)) {
            is_polynomial = true;
            break;
        }
    }

    std::string result;
    if (is_polynomial) {
        result = usePolynomialCalculator(expression);
    }else {
        result = useNormalExpressionCalculator(expression);
    }
    return result;
}
