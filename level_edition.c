#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void ajout_sol_vie(int mat[200][300], int pos_x_deb, int pos_y_deb, int pos_x_fin, int pos_y_fin)
{
    srand(time(0));
    int r = rand();

    if ((pos_x_deb >= 0) && (pos_y_deb >= 0) && (pos_x_fin < 200) && (pos_y_fin < 300))
    {
        for (int i = pos_x_deb; i < pos_x_fin + 1; i++)
        {
            for (int j = pos_y_deb; j < pos_y_fin + 1; j++)
            {
                if ((i < pos_x_deb + 3) && (mat[i][j] == 0))
                    mat[i][j] = 2;
                else
                {
                    if ((i == pos_x_deb + 3) && (mat[i][j] == 0) && (j % 2 == 1))
                        mat[i][j] = 2;
                    else
                    {
                        if (r % 25 == 1)
                            mat[i][j] = 5;
                        else
                            mat[i][j] = 1;
                    }
                    r = rand();
                }
            }
        }
    }
}

void ajout_sol_mort(int mat[200][300], int pos_x_deb, int pos_y_deb, int pos_x_fin, int pos_y_fin)
{
    srand(time(0));
    int r = rand();

    if ((pos_x_deb >= 0) && (pos_y_deb >= 0) && (pos_x_fin < 200) && (pos_y_fin < 300))
    {
        for (int i = pos_x_deb; i < pos_x_fin + 1; i++)
        {
            for (int j = pos_y_deb; j < pos_y_fin + 1; j++)
            {
                if ((i < pos_x_deb + 3) && (mat[i][j] == 6))
                    mat[i][j] = 7;
                else
                {
                    if ((i == pos_x_deb + 3) && (mat[i][j] == 6) && (j % 2 == 1))
                        mat[i][j] = 7;
                    else
                    {
                        if (r % 25 == 1)
                            mat[i][j] = 9;
                        else
                            mat[i][j] = 8;
                    }
                    r = rand();
                }
            }
        }
    }
}

void ajout_caillou(int mat[200][300], int pos_x, int pos_y)
{
    if ((pos_x >= 0) && (pos_y >= 0) && (pos_x + 7 < 200) && (pos_y + 6 < 300))
    {
        for (int i = pos_x; i < pos_x + 7; i++)
        {
            for (int j = pos_y; j < pos_y + 6; j++)
            {
                if ((i == pos_x) && ((j == pos_y + 1) || (j == pos_y + 2)))
                    mat[i][j] = 4;
                if (((i == pos_x + 1) && (j < pos_y + 4)))
                    mat[i][j] = 4;
                if (((i == pos_x + 2) || (i == pos_x + 3)) && (j < pos_y + 5))
                    mat[i][j] = 4;
                if ((i == pos_x + 4) || (i == pos_x + 5))
                    mat[i][j] = 4;
                if ((i == pos_x + 6) && (j > pos_y + 1) && (j < pos_y + 5))
                    mat[i][j] = 4;
            }
        }
    }
}

void faire_pic(int mat[200][300], int pos_x, int pos_y)
{
    if ((pos_x >= 0) && (pos_y>=0))
    {
        for (int i = 0; i< 8; i++)
        {
            for (int j = 0; j<5; j++)
            {
                if (((i==4) && (j == 2)) || (((i == 5) || (i == 6)) && (j>0) && (j<4)))
                    mat[pos_x + i][pos_y + j] = 20;
                else
                {
                    if ((i == 7))
                        mat[pos_x + i][pos_y + j] = 21;
                    else 
                        mat[pos_x + i][pos_y + j] = 0;
                }
            }
        }
    }
}

void mat_to_file(int mat[200][300], const char * file)
{
    FILE * level1_a = fopen(file, "w");

    if (level1_a)
    {
        fprintf(level1_a, "20 180\n");

        for (int i=0;i<200;i++)
        {
            for (int j=0;j<300;j++)
            {
                fprintf(level1_a, "%d ", mat[i][j]);
            }
            fprintf(level1_a, "\n");
        }

        fclose(level1_a);
    }
}


int main()
{
    int i,j;

    int mat1[200][300];
    int mat2[200][300];

    for (i=0;i<200;i++)
    {
        for (j=0; j<300; j++)
        {
            mat1[i][j] = 0;
            mat2[i][j] = 6;
        }
    }

    ajout_sol_vie(mat1, 70, 230, 199, 299);
    ajout_sol_vie(mat1, 180, 0, 199, 299);

    ajout_sol_mort(mat2, 70, 230, 199, 299);
    ajout_sol_mort(mat2, 180, 0, 199, 299);

    faire_pic(mat1, 180, 20);
    faire_pic(mat1, 180, 25);
    faire_pic(mat1, 180, 30);

    ajout_caillou(mat1, 85, 250);
    ajout_caillou(mat1, 190, 25);
    ajout_caillou(mat1, 187, 240);
    ajout_caillou(mat1, 105, 250);
    ajout_caillou(mat1, 115, 280);
    ajout_caillou(mat1, 135, 240);
    ajout_caillou(mat1, 185, 290);

    mat_to_file(mat1, "level1_alive.txt");
    mat_to_file(mat2, "level1_death.txt");

    return 0;
}