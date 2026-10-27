
grid = [[' ', ' ', ' '],
        [' ', ' ', ' '],
        [' ', ' ', ' ']]
        
def print_grid(grid):
    print(grid[0][0],"|",grid[0][1],"|",grid[0][2])
    print(grid[1][0],"|",grid[1][1],"|",grid[1][2])
    print(grid[2][0],"|",grid[2][1],"|",grid[2][2])

print_grid(grid)

player_choice = input("Choose 'X' or 'O':")

if player_choice == "X":
    row = int(input("Enter the row (0, 1, or 2): "))
    col = int(input("Enter the column (0, 1, or 2): "))

    if grid[row][col] == " ":
        grid[row][col] = "X"
    else:
        print("That position is already taken. Try again.")
        
elif player_choice == "O":
    
    if grid[1][1] == " ":
        grid[1][1] = "X"
    else:
        print("The center position is already taken. Try again.")
        
else:
    print("Invalid choice. Please choose 'X' or 'O'.")

print_grid(grid)


