#include "disc.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>

double* disc(const double *times, const double *artConc, const double *pvConc, const double af, const double dv, const double mtt, const double tauA, const double tauP)
{
	// Convert perfusion properties to rates
	double k1a = af * dv / mtt;
	double k1p = dv * (1.0f - af) / mtt;
	double k2 = 1.0f / mtt;

	// Calculate the temporal resolution and number of time points
	double dt = times[1] - times[0];
	int t = sizeof(times) / sizeof(times[0]);

	// Allocate memory for the output
	double *contrast = (double *)malloc(sizeof(double) * t);
	
	for (int i = 0; i < t; i++) {
		double sum = 0.0f;
		for (int j = 0; j < i; j++) {
			double sumA = 0.0f;
			double sumP = 0.0f;
			int tauAOffset = round(j - tauA);
			int tauPOffset = round(j - tauP);

			if (tauAOffset < t && tauAOffset >= 0) {
				sumA += k1a * artConc[tauAOffset];
			}
			if (tauPOffset < t && tauPOffset >= 0) {
				sumP += k1p * pvConc[tauPOffset];
			}
			sum += sumA + sumP * exp(-1.0f * k2 * (i - j) * dt) * dt;
		}
		contrast[i] = sum;
	}

	return contrast;
}