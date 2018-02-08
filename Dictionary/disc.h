
// Dual-input single-compartment model
double* disc(const double *times, const double *artConc, const double *pvConc, const double af, const double dv, const double mtt, const double tauA, const double tauP);

// Signal to contrast conversion
double* artSignal2contrast(const double *artSignal, const double *pvSignal, const double flipAngle, const double t1Blood, const double tr, const double t1Contrast, const int startFrame, const int addFrames);
double* pvSignal2contrast(const double *pvSignal, const double flipAngle, const double t1Plasma, const double tr, const double t1Contrast, const int startFrame, const int addFrames);
double* signal2contrast(const double *signal, const double flipAngle, const double t1Liver, const double tr, const double t1Contrast, const int startFrame, const int addFrames, const double scaleFactor);