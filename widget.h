#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class calculator;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void on_number_button_1_clicked();

    void on_number_button_2_clicked();

    void on_number_button_3_clicked();

    void on_number_button_4_clicked();

    void on_number_button_5_clicked();

    void on_number_button_6_clicked();

    void on_number_button_7_clicked();

    void on_number_button_8_clicked();

    void on_number_button_9_clicked();

    void on_number_button_0_clicked();

    void on_alpha_button_x_clicked();

    void on_symbol_button_point_clicked();

    void on_symbol_button_plus_clicked();

    void on_symbol_button_substract_clicked();

    void on_symbol_button_multiple_clicked();

    void on_symbol_button_division_clicked();

    void on_symbol_button_power_clicked();

    void on_symbol_button_left_bracket_clicked();

    void on_symbol_button_right_bracket_clicked();

    void on_function_button_all_clear_clicked();

    void on_function_button_delete_clicked();

    void on_expression_line_edit_textEdited(const QString &arg1);

    void on_symbol_button_factorial_clicked();

    void on_symbol_button_equal_clicked();

    void on_expression_line_edit_returnPressed();


private:
    Ui::calculator *ui;
    QString expression;
};
#endif // WIDGET_H
