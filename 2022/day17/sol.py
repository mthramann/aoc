f = open("input.txt", "r")
shift, *rest = f.readlines()
shift = shift.strip()

WIDTH = 7
shapes = ["-", "+", "j", "|", "a"]

class Rock:
    _heights = {"-": 0, "+": 2, "j": 2, "|": 3, "a": 1}
    _squares = {"-": [(0, 0), (1, 0), (2, 0), (3, 0)],
                "+": [(1, 0), (0, -1), (1, -1), (2, -1), (1, -2)],
                "j": [(2, 0), (2, -1), (2, -2), (1, -2), (0, -2)],
                "|": [(0, 0), (0, -1), (0, -2), (0, -3)],
                "a": [(0, 0), (1, 0), (0, -1), (1, -1)]}
    def __init__(self, shape, col, height):
        self.col = col
        self.row = height + 4 + self._heights[shape]
        self._shape = shape
        self.squares = self._squares[shape]

    def can_shift(self, shift_right, board):
        shift = 1 if shift_right else -1
        for dx, dy in self.squares:
            nx = self.col + dx + shift
            ny = self.row + dy
            if nx < 0 or nx >= WIDTH or (nx, ny) in board:
                return False
        return True

    def can_fall(self, board):
        for dx, dy in self.squares:
            nx = self.col + dx
            ny = self.row + dy - 1
            if ny < 0 or (nx, ny) in board:
                return False
        return True

    def add_to_board(self, board, height):
        for dx, dy in self.squares:
            board.add((self.col + dx, self.row + dy))

height = -1
NUM_ROCKS = 2022
shift_ind = 0
board = set()
seen = {}

for i in range(NUM_ROCKS):
    if i % len(shapes) == 0:
        k = shift_ind % len(shift)
        if k in seen:
            print(f"Last seen {k} at height {height + 1}: {seen[k]} -> {i}")
        seen[k] = i
         
    rock = Rock(shapes[i % len(shapes)], 2, height)
    while True:
        shift_right = True if shift[shift_ind % len(shift)] == ">" else False
        shift_ind += 1
        if rock.can_shift(shift_right, board):
            rock.col += 1 if shift_right else -1
        if rock.can_fall(board):
            rock.row -= 1
        else:
            height = max(height, rock.row)
            rock.add_to_board(board, height)
            break

print(height + 1)
