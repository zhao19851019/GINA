
#include "simpleNavigationSolution.h"
#include "utility.h"



#define MAXSATNUMBER 15
#define CONVERGENCE_LIMIT 1E-5

using namespace Eigen;

static int WN;
static double ToW;
static int satId[MAXSATNUMBER] = { -1 };
static double pr[MAXSATNUMBER] = { -1 };
static int vectorSize = 0;

static const double wie_e = 7.292115e-5;
static const double c_mps = 299792458;


static double roverPos[4] = {0, 0, 0, 0};
//static Matrix3d designMatrix;

void get_Result(double sol[]) {

	sol[0] = roverPos[0];
	sol[1] = roverPos[1];
	sol[2] = roverPos[2];
	sol[3] = roverPos[3];
}

void print_Result(void) {

	cout << "" << roverPos[0] << " ";
	cout << " " << roverPos[1] << " ";
	cout << " " << roverPos[2] << "	";
	cout << "Clock bias: " << roverPos[3] << endl;
}

void set_time(int wn, double tow) {
	WN = wn;
	ToW = tow;
}

void set_satId(int* id, int size) {

	for (int i = 0; i < size; i++) {

		if ( i >= MAXSATNUMBER) {
			break;
		}

		satId[i] = id[i];
	}

	vectorSize = size;
}

void set_pseudoRange(double* psoudoRange, int size) {

	for (int i = 0; i < size; i++) {

		if (i >= MAXSATNUMBER) {
			break;
		}

		pr[i] = psoudoRange[i];
	}

	vectorSize = size;
}

void calculatePosition(void) {

	while (updatePosition() > CONVERGENCE_LIMIT);
	reset();
}

static double updatePosition(void) {

	//vectorSize = getNumberofVisibleSatelites(WN, ToW);
	double rho = 0;

	satId[0];
	double temp_satPos[3], temp_iter_satPos[3];
	double temp_satClock, temp_satRelCorr;
	double time_of_transmission, time_of_arrival;
	double travelTime = 0.0, travelTime_old = 0.0;
	double temp_dist;

	MatrixXd covMatrix = MatrixXd::Zero(4,4);
	MatrixXd designMatrix(vectorSize, 4);
	VectorXd geometryDistance = VectorXd::Zero(vectorSize);
	VectorXd PRObservations = VectorXd::Zero(vectorSize);
	VectorXd y(vectorSize);
	VectorXd x(4);
	
	for (int i = 0; i < MAXSATNUMBER; i++) {
		
		if (satId[i] < 0) {
			continue;
		}

		// Get i. satelite position at given time
		if (get_satPos(WN, ToW, satId[i], temp_satPos) == 0) {
			continue;
		}

		PRObservations(i) = pr[i];
	
		// Calculate geometry distance from i. svh
		// Calculate normal vector to i. svh
		rho = 0;
		geometryDistance(i) = 0;

		// Correct with earth roation
		temp_iter_satPos[0] = temp_satPos[0];
		temp_iter_satPos[1] = temp_satPos[1];
		temp_iter_satPos[2] = temp_satPos[2];

		time_of_arrival = ToW;
		time_of_transmission = ToW;
		for (int iter = 0; iter < 2; iter++) {

			temp_dist = calculateDistance(roverPos, temp_iter_satPos);

			travelTime_old = travelTime;
			travelTime = temp_dist / c_mps;

			get_satPos(WN, time_of_transmission, satId[i], temp_satPos);

			
			time_of_transmission = time_of_arrival - travelTime;							// TODO we shall check week rollover
			get_satRelCorr(WN, time_of_transmission, satId[i], temp_satRelCorr);
			get_satClock(WN, time_of_transmission, satId[i], temp_satClock);
			get_satPos(WN, time_of_transmission, satId[i], temp_satPos);
			

			if ( (travelTime - travelTime_old) * c_mps < 0.01) break;
		}

		correctwSagnacEffect(time_of_transmission - time_of_arrival, temp_satPos, temp_iter_satPos);

		temp_satPos[0] = temp_iter_satPos[0];
		temp_satPos[1] = temp_iter_satPos[1];
		temp_satPos[2] = temp_iter_satPos[2];

		// Geometry distance
		geometryDistance(i) = calculateDistance(roverPos, temp_satPos);

		// Correct the PR with clock correction
		get_satClock(WN, time_of_transmission, satId[i], temp_satClock);
		get_satRelCorr(WN, time_of_transmission, satId[i], temp_satRelCorr);
		PRObservations(i) += (temp_satClock + temp_satRelCorr) * c_mps;

		// Set up design matrix
		rho = calculateDistance(roverPos, temp_satPos);

		designMatrix(i, 0) = (roverPos[0] - temp_satPos[0]) / rho;
		designMatrix(i, 1) = (roverPos[1] - temp_satPos[1]) / rho;
		designMatrix(i, 2) = (roverPos[2] - temp_satPos[2]) / rho;
		designMatrix(i, 3) = 1.0;
	}

	// Create covariance matrix
	covMatrix = designMatrix.transpose() * designMatrix;
	covMatrix = covMatrix.inverse();

	// Set up observetion vector 
	// Multiply Covariance matrix with A.' and PR residual matrix
	y = PRObservations - geometryDistance;						
	x = covMatrix * designMatrix.transpose() * y;

	// Update rover position and clock bias
	roverPos[0] += x(0);
	roverPos[1] += x(1);
	roverPos[2] += x(2);

	roverPos[3] = x(3);

	double res_norm = Norm(x);
	return res_norm;
}

static void reset(void) {

	for (int i = 0; i < MAXSATNUMBER; i++) {
		satId[i] = 0;
		pr[i] = 0;
		vectorSize = 0;
	}
}

static int getNumberofVisibleSatelites(int WN, int ToW) {

	double temp_satPos[3];

	int numberofSats = 0;
	for (int Id = 0; Id < 33; Id++){
		if (get_satPos(WN, ToW, Id, temp_satPos)) {
			numberofSats++;
		}
	}

	return numberofSats;
}

static void correctwSagnacEffect(double deltat, double* old_pos, double* new_pos) {

	Matrix3d rotMatrix = Matrix3d::Zero();

	rotMatrix <<	cos(wie_e*deltat),  -sin(wie_e*deltat),		0,
					sin(wie_e*deltat),	 cos(wie_e*deltat),		0,
					0,					 0,						1;

	Vector3d posV;
	posV << old_pos[0], old_pos[1], old_pos[2];

	posV = rotMatrix*posV;

	new_pos[0] = posV(0);
	new_pos[1] = posV(1);
	new_pos[2] = posV(2);

}

static double calculateDistance(double* rover, double* sat) {

	double dist = 0;
	for (int a = 0; a < 3; a++) {
		dist += pow((rover[a] - sat[a]), 2);
	}

	return sqrt(dist);
}

static double Norm(double* x) {

	return sqrt(x[0] * x[0] + x[1] * x[1] + x[2] * x[2]);
}

static double Norm(VectorXd x) {

	return sqrt(x(0) * x(0) + x(1) * x(1) + x(2) * x(2));
}