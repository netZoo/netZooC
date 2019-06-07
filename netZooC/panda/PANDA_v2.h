/*
Description:
	This file contains the header functions for PANDA.

Auhtors:
	Marouen Ben Guebila 5/19

*/

#ifndef __PANDA_v2_h__
#define __PANDA_v2_h__

#ifdef __cplusplus
extern "C"
{
#endif

#define CR 13
#define LF 10
#define BOLD "\033[1m"
#define NORMAL "\033[0m"

#define MAXGENES 20000
#define MAXTFS 1000
#define MAXCONDITIONS 500
#define BUFSIZE 10000
#define MAXPATHLENGTH 500

/*PANDA functions declaration */

typedef struct{
char name[64];                  // name of regulator
float W[MAXGENES];              // Current Weight of edge
float M[MAXGENES];              // Prior knowledge from chip-chip/motif data
float P[MAXTFS];                // PPI data
float T[MAXGENES][2];           // Temporary storage of estimates
double exp;
double stdev;
} REGULATION;
REGULATION Regulation[MAXTFS];

typedef struct{
char name[32];
char temp[32];
float expression[MAXCONDITIONS];
double exp;                     // expected value of expression across conditions
double stdev;                   // standard deviation of expression across conditions
float corr[MAXGENES];
} GENES;
GENES Genes[MAXGENES];

int Initialize(REGULATION *reg, GENES *gen);

int ReadInExpressionData(GENES *gen, char filename[]);

int ReadInPriorData(REGULATION *reg, GENES *gen, char filename[]);

int ReadInInteractionData(REGULATION *reg, GENES *gen, char filename[]);

int NormalizePriorData(REGULATION *reg, GENES *gen);

int Correlation(REGULATION *reg, GENES *gen);

int IdentityPPI(REGULATION *reg, GENES *gen);

int IdentityCorrelation(GENES *gen);

float LearnNetwork(REGULATION *reg, GENES *gen, int step);

float UpdateCorrelation(REGULATION *reg, GENES *gen, int step);

float UpdatePPI(REGULATION *reg, GENES *gen, int step);

#ifdef __cplusplus
}
#endif

#endif /* __PANDA_v2_h__ */
