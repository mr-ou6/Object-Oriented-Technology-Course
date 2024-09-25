#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Sudoku {
public:
    // ���캯��������һ������Ϊ81���ַ�����ʾ��������
    Sudoku(const string& board_str) {
        if (board_str.length() != 81) {
            throw invalid_argument("��Ч�ַ�������.");
        }
        // ��ʼ��9x9�Ķ�ά���飬�������ַ���ת��Ϊ���̵�����
        board.resize(9, vector<int>(9));
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                board[i][j] = board_str[i * 9 + j] - '0';  // ���ַ�ת��Ϊ����
            }
        }
    }
    // ����������⣬�����Ƿ�ɹ����
    bool solveSudoku() {
        return solve();
    }
    // ��ӡ��ǰ��������
    void printBoard() const {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == 0) {
                    cout << ". ";  // ��� . ����հ׸�
                } else {
                    cout << board[i][j] << " ";  // �������
                }
            }
            cout << endl;  // ����
        }
    }

private:
    vector<vector<int>> board;  // 9x9�Ķ�ά���飬��ʾ��������
    // �����㷨���ݹ��������
    bool solve() {
        // �����������̣�Ѱ��δ��Ŀո񣨼�ֵΪ0�ĵ�Ԫ��
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                if (board[row][col] == 0) {  // �ҵ�һ���ո�
                    // ������������1��9
                    for (int num = 1; num <= 9; ++num) {
                        if (isValid(row, col, num)) {  // �����������Ƿ��������
                            board[row][col] = num;  // ����Ϸ������������
                            if (solve()) {  // �ݹ����ʣ�������
                                return true;  // ����ܹ����ɹ�������true
                            }
                            board[row][col] = 0;  // ���ݣ�����������ɹ������˸�����Ϊ��
                        }
                    }
                    return false;  // ����������ֶ����Ϸ�������false���л���
                }
            }
        }
        return true;  // ������и��Ӷ��������������
    }
    // �ж��� (row, col) λ�����Ƿ���Է������� num
    bool isValid(int row, int col, int num) const {
        // ����������Ƿ����ظ������� num
        for (int i = 0; i < 9; ++i) {
            if (board[row][i] == num) return false;
        }
        // ����������Ƿ����ظ������� num
        for (int i = 0; i < 9; ++i) {
            if (board[i][col] == num) return false;
        }
        // ������ڵ� 3x3 �����Ƿ����ظ������� num
        int boxRow = row / 3 * 3;  // �������ڹ������ʼ��
        int boxCol = col / 3 * 3;  // �������ڹ������ʼ��
        for (int i = 0; i < 3; ++i) {  // ���� 3x3 ����
            for (int j = 0; j < 3; ++j) {
                if (board[boxRow + i][boxCol + j] == num) return false;  // ������������ظ����֣�����false
            }
        }
        return true;  // ���û�г�ͻ������true
    }
};

// �����������ڲ����������
int main() {
    // ���������ַ�����0��ʾ�ո�
    string sudoku_str = "017903600000080000900000507072010430000402070064370250701000065000030000005601720";
    try {
        // ����Sudoku���󣬳�ʼ����������
        Sudoku sudoku(sudoku_str);
        cout << "��ʼ������:" << endl;
        sudoku.printBoard();  // ��ӡ��ʼ����������
        // ����������⺯��
        if (sudoku.solveSudoku()) {
            cout << "\n����ɹ�:" << endl;
            sudoku.printBoard();  // �ɹ���������󣬴�ӡ���ս��
        } else {
            cout << "\n����ʧ��." << endl;  // ����޷���������������ʾ
        }
    } catch (const exception& e) {
        cout << "������: " << e.what() << endl;  // ��׽������쳣��Ϣ
    }

    return 0;
}
