#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 100
#define MAX_COLS 100
#define MAX_LINE_LEN 1024

int main() {
    FILE *fp_in = fopen("input.csv", "r");
    if (!fp_in) {
        perror("input.csvを開けませんでした");
        return 1;
    }

    int matrix[MAX_ROWS][MAX_COLS];
    int row = 0;
    int col_count = 0;

    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), fp_in) && row < MAX_ROWS) {
        int col = 0;
        char *token = strtok(line, ",");
        while (token != NULL && col < MAX_COLS) {
            matrix[row][col] = atoi(token);
            token = strtok(NULL, ",");
            col++;
        }
        if (row == 0) {
            col_count = col;
        }
        row++;
    }
    fclose(fp_in);

    // 出力ファイルオープン
    FILE *fp_out = fopen("output.txt", "w");
    if (!fp_out) {
        perror("output.txtを開けませんでした");
        return 1;
    }

    // C言語の配列初期化文を書き込む
    fprintf(fp_out, "int matrix[%d][%d] = {\n", row, col_count);
    for (int i = 0; i < row; i++) {
        fprintf(fp_out, "    {");
        for (int j = 0; j < col_count; j++) {
            fprintf(fp_out, "%d", matrix[i][j]);
            if (j != col_count - 1) {
                fprintf(fp_out, ", ");
            }
        }
        fprintf(fp_out, "}");
        if (i != row - 1) {
            fprintf(fp_out, ",");
        }
        fprintf(fp_out, "\n");
    }
    fprintf(fp_out, "};\n");

    fclose(fp_out);

    printf("ok\n");
    return 0;
}
