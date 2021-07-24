#include<stdio.h>
#include<stdlib.h>

#ifndef KSOURCE_H
#define KSOURCE_H

#include "mcpl.h"

#include "aux.h"
#include "metrics.h"
#include "plists.h"


typedef struct KSource KSource;
typedef struct MultiSource MultiSource;

typedef double (*WeightFun)(const mcpl_particle_t* part);

struct KSource{
	double J;
	PList* plist;
	Geometry* geom;
};

KSource* KS_create(double J, PList* plist, Geometry* geom);
KSource* KS_open(const char* filename);
int KS_sample2(KSource* ks, mcpl_particle_t* part, int perturb, double w_crit, WeightFun bias, int loop);
int KS_sample(KSource* ks, mcpl_particle_t* part);
double KS_w_mean(KSource* ks, int N, WeightFun bias);
void KS_destroy(KSource* ks);

struct MultiSource{
	int len;
	KSource** s;
	double J; // Corriente total
	double* ws; // Pesos de cada fuente
	double* cdf; // cdf de los pesos de fuentes
};

MultiSource* MS_create(int len, KSource** s, const double* ws);
MultiSource* MS_open(int len, const char** filenames, const double* ws);
int MS_sample2(MultiSource* ms, mcpl_particle_t* part, int perturb, double w_crit, WeightFun bias, int loop);
int MS_sample(MultiSource* ms, mcpl_particle_t* part);
double MS_w_mean(MultiSource* ms, int N, WeightFun bias);
void MS_destroy(MultiSource* ms);


#endif
