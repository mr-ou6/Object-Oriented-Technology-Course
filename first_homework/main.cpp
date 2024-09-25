#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Sudoku {
public:
    // 构造函数，接受一个长度为81的字符串表示数独棋盘
    Sudoku(const string& board_str) {
        if (board_str.length() != 81) {
            throw invalid_argument("无效字符串输入.");
        }
        // 初始化9x9的二维数组，将输入字符串转化为棋盘的数字
        board.resize(9, vector<int>(9));
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                board[i][j] = board_str[i * 9 + j] - '0';  // 将字符转化为数字
            }
        }
    }
    // 启动数独求解，返回是否成功求解
    bool solveSudoku() {
        return solve();
    }
    // 打印当前数独棋盘
    void printBoard() const {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == 0) {
                    cout << ". ";  // 输出 . 代表空白格
                } else {
                    cout << board[i][j] << " ";  // 输出数字
                }
            }
            cout << endl;  // 换行
        }
    }

private:
    vector<vector<int>> board;  // 9x9的二维数组，表示数独棋盘
    // 回溯算法：递归求解数独
    bool solve() {
        // 遍历整个棋盘，寻找未填的空格（即值为0的单元格）
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                if (board[row][col] == 0) {  // 找到一个空格
                    // 尝试填入数字1到9
                    for (int num = 1; num <= 9; ++num) {
                        if (isValid(row, col, num)) {  // 检查这个数字是否可以填入
                            board[row][col] = num;  // 如果合法，填入该数字
                            if (solve()) {  // 递归求解剩余的棋盘
                                return true;  // 如果能够求解成功，返回true
                            }
                            board[row][col] = 0;  // 回溯：如果不能求解成功，将此格重置为空
                        }
                    }
                    return false;  // 如果所有数字都不合法，返回false进行回溯
                }
            }
        }
        return true;  // 如果所有格子都填满，数独解出
    }
    // 判断在 (row, col) 位置上是否可以放置数字 num
    bool isValid(int row, int col, int num) const {
        // 检查所在行是否有重复的数字 num
        for (int i = 0; i < 9; ++i) {
            if (board[row][i] == num) return false;
        }
        // 检查所在列是否有重复的数字 num
        for (int i = 0; i < 9; ++i) {
            if (board[i][col] == num) return false;
        }
        // 检查所在的 3x3 宫格是否有重复的数字 num
        int boxRow = row / 3 * 3;  // 计算所在宫格的起始行
        int boxCol = col / 3 * 3;  // 计算所在宫格的起始列
        for (int i = 0; i < 3; ++i) {  // 遍历 3x3 宫格
            for (int j = 0; j < 3; ++j) {
                if (board[boxRow + i][boxCol + j] == num) return false;  // 如果宫格内有重复数字，返回false
            }
        }
        return true;  // 如果没有冲突，返回true
    }
};

// 主函数：用于测试数独求解
int main() {
    // 输入数独字符串，0表示空格
    string sudoku_str = "017903600000080000900000507072010430000402070064370250701000065000030000005601720";
    try {
        // 创建Sudoku对象，初始化数独棋盘
        Sudoku sudoku(sudoku_str);
        cout << "初始化棋盘:" << endl;
        sudoku.printBoard();  // 打印初始的数独棋盘
        // 调用数独求解函数
        if (sudoku.solveSudoku()) {
            cout << "\n推理成功:" << endl;
            sudoku.printBoard();  // 成功解出数独后，打印最终结果
        } else {
            cout << "\n推理失败." << endl;  // 如果无法解出数独，输出提示
        }
    } catch (const exception& e) {
        cout << "错误结果: " << e.what() << endl;  // 捕捉并输出异常信息
    }

    return 0;
}
