#include <stdio.h>
#include <stdlib.h>
#include <conio.h>



int ROW, COL;

void PrintMat(int **mat);
int calculatePath(int **mat);

int main() {
    printf("Enter the dimentions of the maze (rows and columns):");
    scanf("%d %d", &ROW, &COL);
    
    int** input_mat = (int**)malloc(ROW * sizeof(int*));
    for (int i = 0; i < ROW; i++) {
        input_mat[i] = (int*)malloc(COL * sizeof(int));
    }
    
    
    printf("Enter the maze (row by row, with 0 for open and 1 for wall):\n\nInput Maze:\n");
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            scanf("%d", &input_mat[i][j]);
        }
    }

    if (calculatePath(input_mat) == 0)
        printf("\nNo path exists.");
    else {
        printf("\nSolution Path:\n");
        PrintMat(input_mat);
    }
    

    return 0;
}

void PrintMat(int **mat) {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if(mat[i][j] == 2) {
                printf("0 ");
            } else {
                if (mat[i][j] == -1) {
                    printf("* ");
                } else
                    printf("%d ", mat[i][j]);
            }
            
        }
        printf("\n");
    }
}

int calculatePath(int **mat) {
    int current_row = 0;
    int current_col = 0;
    int moveable_paths = 0;
    int moveable_path_coor[20][2] = {0};
    int ismoveable;
    int moved;

    
    if (mat[0][0] != 0)
        return 0;

    mat[0][0] = -1;

    while (1) {
        moved = 0;
        ismoveable = 1;
        

        
        if (current_row + 1 < ROW && mat[current_row + 1][current_col] == 0) {// Move Down
            current_row++;
            mat[current_row][current_col] = -1;
            moved = 1;
        }
        
        if (current_col + 1 < COL && mat[current_row][current_col + 1] == 0) {// Move Right
            if(moved == 0) {
                current_col++;
                moved = 1;
            } else {
                if(ismoveable) {
                    moveable_path_coor[moveable_paths][0] = current_row;
                    moveable_path_coor[moveable_paths][1] = current_col;
                    moveable_paths++;
                    ismoveable = 0;
                }
            }
        }
        
        if (current_row - 1 >= 0 && mat[current_row - 1][current_col] == 0) {// Move Up
            if(moved != 1) {
                current_row--;
                moved = 1;
            } else {
                if(ismoveable) {
                    moveable_path_coor[moveable_paths][0] = current_row;
                    moveable_path_coor[moveable_paths][1] = current_col;
                    moveable_paths++;
                    ismoveable = 0;
                }
            }
        }
        
        if (current_col - 1 >= 0 && mat[current_row][current_col - 1] == 0) {// Move Left
            if(moved != 1) {
                current_col--;
                moved = 1;
            } else {
                if(ismoveable) {
                    moveable_path_coor[moveable_paths][0] = current_row;
                    moveable_path_coor[moveable_paths][1] = current_col;
                    moveable_paths++;
                    ismoveable = 0;
                }
            }
        }
        
        mat[current_row][current_col] = -1;
        
        if (current_row == ROW - 1 && current_col == COL - 1)
            return 1;


        if (!moved) {
            if(moveable_paths == 0)
                return 0;
            else {
                mat[current_row][current_col] = 2;
                current_row = moveable_path_coor[moveable_paths-1][0];
                current_col = moveable_path_coor[moveable_paths-1][1];
                moveable_paths--;
            }
                
        }
    }
}