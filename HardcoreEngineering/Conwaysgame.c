#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WIDTH 25
#define HEIGHT 50
#define BACKGROUND '-'
#define CELL 'O'
#define VELOCIDADE 100

typedef enum {
    MORTO,
    VIVO,
} State;

typedef struct {
    State state;

}Cell;

Cell grid[WIDTH][HEIGHT] = {0};


void init_grid(){
       for(size_t i = 0; i < WIDTH; i++){
        for(size_t j = 0; j < HEIGHT; j++){
            grid[i][j].state = MORTO;
        }
    }
}

void proxima_cell(){

    for(size_t i = 0; i < WIDTH; i++){
        for(size_t j = 0; j < HEIGHT; j++){
            int cell_vivos = 0;
            for(int k = -1; k <= 1; k++){
                for(int n = -1; n <= 1; n++){
                    if(k == 0 && n == 0) continue;
                    if((int)i + k >= 0 && (int)i + k <= WIDTH && (int)j + n >= 0 && (int)j + n <= HEIGHT){
                        if (grid[i+k][j+n].state == VIVO){
                            cell_vivos++;
                        }
                    }
                }
            }
            switch (cell_vivos){
            case 0:
            case 1:
                grid[i][j].state = MORTO;
                break;

            case 2:
                if(grid[i][j].state == VIVO){
                    grid[i][j].state = VIVO;
                }
                break;
            case 3:
                if(grid[i][j].state == MORTO && cell_vivos == 3){
                    grid[i][j].state = VIVO;
                }
                else if(grid[i][j].state == VIVO){
                    grid[i][j].state = VIVO;
                }
                break;
             default:
                grid[i][j].state = MORTO;
                break;
            }
        }    
    }
}

int print_grid(){
    int cell_vivos = 0;
    for(size_t i = 0; i < WIDTH; i++){
        for(size_t j = 0; j < HEIGHT; j++){
            if (grid[i][j].state == VIVO){
                printf("%c", CELL);
                cell_vivos++;
            }
            else{
                printf("%c", BACKGROUND);
            }
        } printf("\n");
    }
    return cell_vivos;
}

int main(){
    init_grid();
    for(size_t  i = 0; i < WIDTH/5; i++){
        for(size_t  j = 0; j < HEIGHT/5; j++){
            grid[i][j].state = VIVO;
        }
    }
    
    while (print_grid() != 0){
        usleep(VELOCIDADE * 1000);
        proxima_cell();
        system("clear");

    }

}
