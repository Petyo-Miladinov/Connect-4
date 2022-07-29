#include <stdio.h>
#include<stdlib.h>

char scores[40][20];

int cell = 0;
char token = 'X';

void init_scores(int rows, int cols);
void test_scores(int rows, int cols);
void board(int rows, int cols);
void choose(int rows, int cols);
void fill_bin(int rows, int cols);
int check(char token, int rows, int cols);

int main() {
    int rows = 0, cols = 0; 
    printf("Rows: "); 
    scanf("%d", &rows); 
    printf("\nColumns: "); 
    scanf("%d", &cols); 
    printf("\n"); 

    init_scores(rows, cols);
    test_scores(rows, cols);
    board(rows, cols);
    
    while (1) {
        printf("Player %c, your turn!\n", token);
        choose(rows, cols);
        printf("\n\n");
        board(rows, cols);
        if (check('X', rows, cols)) {
            printf("\n\nPlayer X wins!\n\n");
            break;  
        } else if (check('O', rows, cols)) {
            printf("\n\nPlayer O wins!\n\n");
            break;  
        } else {
            printf("\n\nDraw!\n"); 
        }  
    }
    
    return 0; 
}

void init_scores(int rows, int cols) {
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scores[i][j] = ' ';
        }
    }
}

void test_scores(int rows, int cols) {
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c ", scores[i][j]);
        }
        printf("\n");
    }
}

void board(int rows, int cols) {
    
    printf("|");
    for(int i = 0; i < cols; i++) {
        printf("---|");
    }
    printf("\n"); 
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("| %c ", scores[i][j]);
        }
        printf("|\n");

        printf("|"); 
        for(int i = 0; i < cols; i++) {
            printf("---|");
        }
        printf("\n"); 
    }

    FILE *fp; 
    fp = fopen("connect_4.txt", "a"); 

    fprintf(fp, "|"); 
    for(int i = 0; i < cols; i++) {
        fprintf(fp, "---|");
    }
    fprintf(fp, "\n"); 

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(fp, "| "); 
            fputc(scores[i][j], fp); 
            fprintf(fp, " "); 
        }
        fprintf(fp, "|\n");

        fprintf(fp, "|"); 
        for(int i = 0; i < cols; i++) {
            fprintf(fp, "---|");
        }
        fprintf(fp, "\n"); 
    }
    fprintf(fp, "\n\n"); 
    fclose(fp); 
}

void choose(int rows, int cols) {
    
    int c;
    
    while (1) {
        printf("\nChoose: ");
        scanf(" %d", &c);
        cell = c - 1; 
        
        if ((cell >= 0 && cell <= cols) && (scores[0][cell] == ' ')) {
            fill_bin(rows, cols);
            token = (token == 'X') ? 'O' : 'X';
            break;
        }
    }
}

void fill_bin(int rows, int cols) {
    int level ; 

    for (level = rows-1; level >= 0; level--) {
        if (scores[level][cell] == ' ') {
            scores[level][cell] = token;
            break;
        }   
    }               
}

int check(char token, int rows, int cols) {

    int count;
    int ways = 4;
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < ways; ++j) {
            count = 0;
            for (int k = 0; k < 4; ++k) {
                if (scores[i][j + k] == token) 
                    count++;
            }
            if (count == 4) 
                return 1;
        }
    }
    
    ways = 3;
    
    for (int j = 0; j < cols; ++j) {
        for (int i = 0; i < ways; ++i) {
            count = 0;
            for (int k = 0; k < 4; ++k) {
                if (scores[i + k][j] == token) 
                    count++;
            }
            if (count == 4) 
                return 1;
        }
    }

    return 0;       
}