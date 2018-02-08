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

double* artSignal2contrast(const double *artSignal, const double *pvSignal, const double flipAngle, const double t1Blood, const double tr, const double t1Contrast, const int startFrame, const int addFrames)
{
	int t = sizeof(artSignal) / sizeof(artSignal[0]);
	double alpha = flipAngle * M_PI / 180.0f;
	double r1Blood = 1 / t1Blood / 1000.0f;
	double hematocrit = 0.4;

	// Take absolute value of signals
	double *artSignalAbs = (double *)malloc(sizeof(artSignal));
	double *pvSignalAbs = (double *)malloc(sizeof(pvSignal));
	for (int i = 0; i < t; i++) {
		artSignalAbs[i] = fabs(artSignal[i]);
		pvSignalAbs[i] = fabs(pvSignal[i]);
	}

	// Calculate M0
	double m0 = 0.0f;
	for (int i = startFrame; i < startFrame + addFrames; i++) {
		m0 += pvSignalAbs[i];
	}
	m0 /= addFrames;

	double s0b = m0 * ((1.0f - exp(-1.0f * r1Blood * tr) * cos(alpha)) / (1.0f - exp(-1.0f * r1Blood * tr)) / sin(alpha));
	double *r1b = (double *)sizeof(artSignal);
	for (int i = 0; i < t; i++) {
		r1b[i] = log( ( (s0b * sin(alpha)) - (artSignal[i] * cos(alpha)) ) / (s0b * sin(alpha) - artSignal[i]) ) / tr;
	}

	// Allocate memory for the output
	double *artContrast = (double *)malloc(sizeof(artSignal));
	for (int i = 0; i < t; i++) {
		artContrast[i] = (r1b[i] - r1Blood) * 1000.0f / t1Contrast / (1.0f - hematocrit);
	}

	return artContrast;
}
