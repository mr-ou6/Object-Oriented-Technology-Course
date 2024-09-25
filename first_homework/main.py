
import copy
import json
class Sudoku:
    def __init__(self, board_str):
        self.size = 9
        self.board = self._parse_board(board_str)
    def _parse_board(self, board_str):
        """解析字符串为9x9的Sudoku棋盘"""
        if len(board_str) != self.size * self.size:
            raise ValueError("无效字符串输入.")
        board = [[int(board_str[i * self.size + j]) for j in range(self.size)] for i in range(self.size)]
        return board
    def clone(self):
        """克隆当前Sudoku对象"""
        return copy.deepcopy(self)
    def to_json(self):
        """将棋盘序列化为JSON格式"""
        return json.dumps(self.board)
    def get_candidates(self, row, col):
        """推理给定单元格的候选值"""
        if self.board[row][col] != 0:
            return []  # 已经有数字，返回空列表
        candidates = set(range(1, 10))
        candidates -= set(self.board[row])  # 排除所在行的数字
        candidates -= set(self.board[i][col] for i in range(9))  # 排除所在列的数字
        candidates -= set(self.board[r][c]
                          for r in range(row // 3 * 3, row // 3 * 3 + 3)
                          for c in range(col // 3 * 3, col // 3 * 3 + 3))  # 排除所在3x3宫内的数字
        return list(candidates)
    def solve_sudoku(self):
        """使用回溯算法求解数独"""
        return self._solve()
    def _solve(self):
        """回溯算法实现求解"""
        for row in range(self.size):
            for col in range(self.size):
                if self.board[row][col] == 0:  # 找到一个空格
                    candidates = self.get_candidates(row, col)
                    for candidate in candidates:
                        self.board[row][col] = candidate  # 尝试填入候选值
                        if self._solve():  # 递归继续求解
                            return True
                        self.board[row][col] = 0  # 回溯，将单元格重置为空
                    return False  # 无法填入有效的候选值，回溯
        return True  # 全部填满，数独解出
    def __eq__(self, other):
        """比较两个Sudoku对象是否相同"""
        if isinstance(other, Sudoku):
            return self.board == other.board
        return False
    def __str__(self):
        """返回棋盘的字符串表示"""
        return '\n'.join(' '.join(str(cell) if cell != 0 else '.' for cell in row) for row in self.board)

# 测试用例
if __name__ == "__main__":
    # 从给定字符串创建Sudoku实例
    sudoku_str = "217943600000080000900000507072010430000402070064370250701000065000030000005601720"
    sudoku = Sudoku(sudoku_str)
    # 打印Sudoku棋盘
    print("初始化棋盘:")
    print(sudoku)
    # 使用回溯算法求解数独
    if sudoku.solve_sudoku():
        print("\n推理成功:")
        print(sudoku)
    else:
        print("\n推理失败.")
