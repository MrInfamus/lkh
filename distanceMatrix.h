
typedef struct halfmatrix {
	int height;
	int width;
	double **data;
} halfmatrix;

/*
1 2 3 4 5
1 2 3 4 *
1 2 3 * *
1 2 * * *
1 * * * *

h(h+1)/2

21 - element
*/
void finalizehalfmatrix(halfmatrix *m)
{
	for(int i = 0; i < m->height; i++)
	    free(m->data[i]);

	free(m->data);
}

//Если не будет работать нужно дописать... TODO
void fillhalfmatrix(halfmatrix *canvas, double elem) {
    int i;
    for(i = 0; i < canvas->height; i++) {
        int j;
        for(j = 0; j < canvas->width; j++) {
            canvas->data[i][j] = elem;
        }
    }
}

void inithalfmatrix(halfmatrix *m, int h)
{
	m->height = h;
	m->width = h;
	m->data = (double**)malloc((h*(h+1)/2) * sizeof(double*));
	if(canvas->data == NULL) {printf("Error malloc\n");exit(-1);}
	for(int i = 0; i < h; i++) {
		m->data[i] = (double*)malloc((h-i-1)*sizeof(double));
		if(canvas->data[i] == NULL) {printf("Error malloc\n");finalizehalfmatrix(m);exit(-1);}
	}
}

//Проверяет вышел ли элемент за пределы половинчетой матрицы TODO
bool checkPositionhalfmatrix(const halfmatrix *canvas, int x, int y) {
    return x >= 0 && x < canvas->width
           && y >= 0 && y < canvas->height;
}

//Кладет элемент в матрицу с учетом, что ты не вышел за границу TODO
void pointAthalfmatrix(halfmatrix *canvas, int x, int y, double elem) {
    if (!checkPositionAthalfmatrix(canvas, position))
        return;

    canvas->data[y][x] = symbol;
}

//Печатае половинную матрицу: TODO
void printhalfmatrix(const halfmatrix *canvas) {
    int i;
    for(i = 0; i < canvas->height; i++) {
        int j;
        for (j = 0; j < canvas->width; j++) {
            putchar(canvas->data[i][j]);putchar(' ');putchar(' ');
        }
        putchar('\n');
    }
}
