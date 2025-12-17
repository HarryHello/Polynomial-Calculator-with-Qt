# 计算器

这是一个基于Qt6框架开发的计算器应用程序，支持普通表达式计算和多项式计算两种模式。
本项目是*数据结构与算法*课程的作业，实现了一个简单的计算器应用程序。

## 功能特性

### 普通表达式计算
- 支持基本算术运算：加(+)、减(-)、乘(*)、除(/)
- 支持高级数学运算：幂运算(^)、阶乘(!)
- 支持括号运算和表达式优先级
- 支持小数计算

### 多项式计算
- 支持一元多项式的输入和显示
- 支持多项式的加法、减法和乘法运算
- 支持多项式的求导运算
- 实现特性：多项式乘法的优先级**最低**，无需在多项式中使用括号，乘号自动分割多项式

### 用户界面
- 直观的数字按钮和符号按钮布局
- 支持键盘输入和鼠标点击 (所有字母都输入为 x)
- 自适应字体大小，根据按钮和输入框大小调整
- 美观的图标和标题栏

### 其他特性
- 支持表达式的清除(AC)和删除(DEL)操作
- 支持回车键计算结果

## 技术栈

- **框架**: Qt 6
- **语言**: C++
- **构建系统**: CMake
- **UI设计**: Qt Designer

## 项目结构
```plaintext
calculator-Qt/
├── CMakeLists.txt                # CMake构建配置文件，用于项目构建
├── CMakeLists.txt.user           # Qt Creator用户配置文件
├── README.md                     # 项目说明文档
├── app.rc                        # Windows资源文件
├── build/                        # 构建输出目录
├── calculator.ico                # 应用程序图标（Windows）
├── calculator.png                # 应用程序图标
├── expressionEveluationCalculator.cpp  # 普通表达式计算器实现文件
├── expressionEveluationCalculator.hpp  # 普通表达式计算器头文件
├── main.cpp                      # 程序入口点文件
├── polynomial.cpp                # 多项式计算实现文件
├── polynomial.hpp                # 多项式计算头文件
├── project1_qt_version_zh_CN.ts  # 中文翻译文件
├── resources.qrc                 # Qt资源文件
├── widget.cpp                    # 主窗口实现文件
├── widget.h                      # 主窗口头文件
└── widget.ui                     # Qt Designer设计文件
```

## 构建与运行

### 环境要求
- Qt 6 开发环境
- CMake 3.16+ (或使用Qt Creator内置的CMake)
- 支持C++17的编译器

### 构建步骤
1. 克隆或下载项目到本地
2. 使用Qt Creator打开CMakeLists.txt文件
3. 选择合适的构建套件(Kit)
4. 点击构建按钮(或按Ctrl+B)
5. 构建完成后，点击运行按钮(或按Ctrl+R)

### 手动构建
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## 使用说明

### 普通计算
1. 点击数字按钮或使用键盘输入数字
2. 点击运算符按钮或使用键盘输入运算符
3. 点击等号按钮(=)或按回车键计算结果

### 多项式计算
1. 输入多项式表达式，例如：`3x^2 + 2x + 1`
2. 使用运算符进行多项式运算
3. 点击等号按钮(=)或按回车键计算结果

### 支持的运算符
- `+`: 加法
- `-`: 减法
- `*`: 乘法
- `/`: 除法 (仅普通计算)
- `^`: 幂运算
- `!`: 阶乘 (仅普通计算)
- `()`: 括号

## 代码说明

### 核心类

#### Widget类
- 主窗口类，负责UI交互和事件处理
- 管理表达式输入和结果显示
- 处理按钮点击和键盘输入事件

#### NormalExpression类
- 普通表达式计算器类
- 实现中缀表达式的解析和计算
- 使用栈数据结构进行表达式求值

#### UnivariatePolynomial类
- 一元多项式类
- 支持多项式的各种运算
- 基于链表实现的多项式存储

### 关键函数

#### `useCalculator(std::string expression)`
- 根据表达式类型选择合适的计算器
- 支持普通表达式和多项式表达式

#### `NormalExpression::calculate(std::string expression)`
- 解析并计算普通数学表达式
- 支持基本运算和高级运算

#### `UnivariatePolynomial::operator+`、`operator-`、`operator*`
- 多项式的加法、减法和乘法运算实现

## 许可证

本项目采用MIT许可证，详见LICENSE文件。
