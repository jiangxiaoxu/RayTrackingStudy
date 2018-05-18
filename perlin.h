#pragma once
#include "vec3.h"
#include <ctime>
#include <random>
inline double trilinear_interp(double c[2][2][2], double u, double v, double w) {
	double accum = 0;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++)
				accum += (i*u + (1 - i)*(1 - u))*(j*v + (1 - j)*(1 - v))*(k*w + (1 - k)*(1 - w))*c[i][j][k];
	return accum;
}

class perlin
{
public:
	perlin(){}
	double noise(const vec3& p) const {
		double u = p.x() - floor(p.x());
		double v = p.y() - floor(p.y());
		double w = p.z() - floor(p.z());
		//int i = int(4 * p.x()) & 255;
		//int j = int(4 * p.y()) & 255;
		//int k = int(4 * p.z()) & 255;
		int i = floor(p.x());
		int j = floor(p.y());
		int k = floor(p.z());
		double c[2][2][2];
		for (int di = 0; di < 2; di++)
			for (int dj = 0; dj < 2; dj++)
				for (int dk = 0; dk < 2; dk++)
					c[di][dj][dk] = ranfloat[perm_x[(i+di)&255]^ perm_y[(j + dj) & 255]^ perm_z[(k + dk) & 255]];
		return trilinear_interp(c, u, v, w);
	/*	return ranfloat[perm_x[i] ^ perm_y[j] ^ perm_z[k]];*/
	}
	static double *ranfloat;
	static int *perm_x;
	static int *perm_y;
	static int *perm_z;
};

static double* perlin_generate() {
	double *p = new double[256];
	for (int i = 0; i < 256; ++i) 
		p[i] = uni_dist(reng);
	return p;
}

void permute(int *p, int n) {
	for (int i=n-1;i>0;i--){
		int target = int(uni_dist(reng)*(i+1));
		int tmp = p[i];
		p[i] = p[target];
		p[target] = tmp;
	}
	return;
}

static int* perlin_generate_perm() {
	int *p = new int[256];
	for (int i = 0; i < 256; i++)
		p[i] = i;
	permute(p, 256);
	return p;
}

double *perlin::ranfloat = perlin_generate();
int *perlin::perm_x = perlin_generate_perm();
int *perlin::perm_y = perlin_generate_perm();
int *perlin::perm_z = perlin_generate_perm();