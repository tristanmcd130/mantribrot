#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define HEIGHT 1000
#define WIDTH 1200
#define DEPTH 101
// MAKE SURE THE STARTS AND ENDS ARE FLOATS
#define RE_START -2
#define RE_END 1.0
#define I_START 1.2
#define I_END -1.2
#define J_START -1.4
#define J_END 1.4
#define RE_STEP ((RE_END - RE_START) / (WIDTH - 1))
#define I_STEP ((I_END - I_START) / (HEIGHT - 1))
#define J_STEP ((J_END - J_START) / (DEPTH - 1))
struct triplex // what are these actually called?
{
	double re;
	double i;
	double j;
};
double tabs(struct triplex t)
{
	return sqrt(pow(t.re, 2) + pow(t.i, 2) + pow(t.j, 2));
}
struct triplex tadd(struct triplex a, struct triplex b)
{
	struct triplex result = {a.re + b.re, a.i + b.i, a.j + b.j};
	return result;
}
struct triplex tsquare(struct triplex t)
{
	struct triplex result = {pow(t.re, 2) - pow(t.i, 2) - pow(t.j, 2), t.i * (2 * t.re + t.j), t.j * (t.re + 2 * t.i)};
	return result;
}
int mantribrot(struct triplex t)
{
	struct triplex t2 = t;
	for(int iteration = 0; iteration < 256; iteration++)
	{
		if(tabs(t2) >= 2) return iteration;
		t2 = tadd(tsquare(t2), t);
	}
	return 0;
}
int main(int argc, char *argv[])
{
	FILE *f;
	unsigned long start_time = (unsigned long)time(NULL);
	unsigned long elapsed_time = 0;
	int row;
	int image = 1;
	char *filename = (char *)calloc(20, 1);
	struct triplex t;
	for(t.j = J_START; t.j <= J_END + J_STEP / 2; t.j += J_STEP)
	{
		sprintf(filename, "mantribrot_%04d.pgm", image);
		f = fopen(filename, "wb");
		if(!f)
		{
			perror("");
			return 1;
		}
		fprintf(f, "P2\n%d %d\n%d\n", WIDTH, HEIGHT, 255);
		row = 1;
		for(t.i = I_START; t.i >= I_END + I_STEP / 2; t.i += I_STEP)
		{
			for(t.re = RE_START; t.re <= RE_END + RE_STEP / 2; t.re += RE_STEP) fprintf(f, "%d ", mantribrot(t));
			elapsed_time = (unsigned long)time(NULL) - start_time;
			printf("\n\x1B[F\x1B[G\x1B[2K%02lu:%02lu:%02lu: %d/%d: %d/%d", (unsigned long)(elapsed_time / 3600), (unsigned long)(elapsed_time / 60 % 60), (unsigned long)(elapsed_time % 60), image, DEPTH, row++, HEIGHT);
			fprintf(f, "\n");
		}
		fclose(f);
		image++;
	}
	printf("\n");
	return 0;
}
