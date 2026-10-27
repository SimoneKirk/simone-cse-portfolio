import random

def print_grid(grid):
    print(grid[0][0], "|", grid[0][1], "|", grid[0][2])
    print(grid[1][0], "|", grid[1][1], "|", grid[1][2])
    print(grid[2][0], "|", grid[2][1], "|", grid[2][2])

def check_winner(grid):
    # Check rows
    for row in grid:
        if row.count(row[0]) == len(row) and row[0] != ' ':
            return True

    # Check columns
    for col in range(len(grid[0])):
        if all(grid[row][col] == grid[0][col] and grid[row][col] != ' ' for row in range(len(grid))):
            return True

    if grid[0][0] == grid[1][1] == grid[2][2] != ' ' or grid[0][2] == grid[1][1] == grid[2][0] != ' ':
        return True

    return False

def check_tie(grid):
    return all(cell != ' ' for row in grid for cell in row)

def check_game_over(grid):
    return check_winner(grid) or check_tie(grid)

def computer_move(grid):
    available_moves = [(i, j) for i in range(3) for j in range(3) if grid[i][j] == ' ']
    if available_moves:
        return random.choice(available_moves)
    return None

grid = [[' ', ' ', ' '],
        [' ', ' ', ' '],
        [' ', ' ', ' ']]

print_grid(grid)

while not check_game_over(grid):
    # Player's move
    player_choice = input("Choose 'X' or 'O': ")

    if player_choice == "X" or player_choice == "O":
        row = int(input("Enter the row (0, 1, or 2): "))
        col = int(input("Enter the column (0, 1, or 2): "))

        if grid[row][col] == " ":
            grid[row][col] = player_choice
        else:
            print("That position is already taken. Try again.")
    else:
        print("Invalid choice. Please choose 'X' or 'O.'")

    print_grid(grid)

    if check_game_over(grid):
        break

    # Computer's move
    print("Computer's move:")
    computer_move_result = computer_move(grid)
    if computer_move_result:
        grid[computer_move_result[0]][computer_move_result[1]] = "O"
        print_grid(grid)

if check_winner(grid):
    print("Player wins!")
elif check_tie(grid):
    print("It's a tie!")
else:
    print("Computer wins!")
