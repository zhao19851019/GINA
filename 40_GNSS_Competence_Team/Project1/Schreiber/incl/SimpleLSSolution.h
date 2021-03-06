#pragma once

#include "util.h"

using namespace gpstk;
using namespace std;
using namespace Eigen;


namespace simpleLS {

	

	void calculateSolution(CommonTime time,vector<SatID> &prnVec,vector<double> &rangeVec,GPSEphemerisStore &bceStore);
	
	double getGeometricDistance(VectorXd &solution,Triple satPos);

	VectorXd getSolution();

	void setConvLimit(double val);

	void corrW_Sagnac(double rho, Triple* PVT);

	void calcCorrections(VectorXd & prvec, vector<SatID> prnvec, CommonTime time);

	Xvt getSatXVT(CommonTime time, SatID sat);

	double getClockBias(SatID, CommonTime);
	double getSatRelCorr(SatID, CommonTime);
}