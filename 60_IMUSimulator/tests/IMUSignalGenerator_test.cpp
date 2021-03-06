#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "GPSWeekSecond.hpp"

#include <Eigen/Dense>

#include "strapdown_ecef.h"
#include "geoparam_wgs84.h"
#include "lib_Frames.h"

#include "Trajectory.h"
#include "IMUSignalGenerator.h"
#include "IMUStore.h"

using namespace std;

void test1(void);
void test2(void);

int main(int argc, char **argv) {

	test1();
	test2();
}


void test1(void) {
	/*Refine this test*/
	/*
	typedef std::numeric_limits< double > dbl;
	std::cout.precision(dbl::max_digits10);

	double llh_array[3] = { 0,0,0 };
	double Rn, Re, g, sL, cL, WIE_E;

	IMUSimulator::IMUSignalGenerator imuGenerator;

	IMUSimulator::WGS84Ellipsoid myellip(llh_array, IMUSimulator::LLH_Frame);
	myellip.getParams(Rn, Re, g, sL, cL, WIE_E);

	std::cout << Rn << "   " <<
		Re << "   " <<
		g << "   " <<
		sL << "   " <<
		cL << "   " <<
		WIE_E << std::endl;

	Eigen::Vector3d ab, wb, Vb, ab_comp, wb_comp, Vb_comp;
	ab << 0, 0, 0;
	Eigen::Vector3d bode2ecef_angle, nav2ecef_angle, local_angle;
	wb << 0, 0, 0;

	Eigen::Matrix3d Cnb;
	Eigen::Vector3d ecef;
	Eigen::Vector3d llh;
	llh << 0, 0, 0;
	ecef = IMUSimulator::Lib::transform_llh2ecef(llh);
	IMUSimulator::strapdown_ecef str_e(ecef);
	IMUSimulator::IMUStore imuStore;
	IMUSimulator::Trajectory traj;

	IMUSimulator::Measure_IMU meas;

	

	double dt = 0.1;
	double time = 0.0;
	double time_max = 10.0;
	*/
	/*
	for (time = 0; time < time_max; time += dt) {

	std:cout << endl;

		Cnb = str_e.Cne.transpose()*str_e.Cbe;
		local_angle = IMUSimulator::Lib::dcm2euler(Cnb);

		Vb = str_e.getVbody();
		llh = str_e.getLLH();
		*/
		/*Calculate what acc and ang vel value should be added to the dummy acc and w inputs. Dummy means without g, wie_e, and cetripetal force compenstation*/
		/*meas = imuGenerator.calculate(ab, wb, Vb, llh, local_angle);

		meas.wn = 1956;
		meas.tow = time;

		std::cout << "IMU measurement: " << std::endl << meas << std::endl;			// Print out the actual IMU measurement

		imuStore.add_measure(IMUSimulator::GPSTime, meas);

		str_e.update(meas, dt);
		std::cout << str_e << endl;													// Print out the actual data stored in the strapdown_ecef object
		traj << str_e;
		traj.updateTime(IMUSimulator::GPSTime, meas.wn, meas.tow);
	}



	std::cout << imuStore << endl;													// Print out all the IMU signal element
	std::cout << traj << endl;														//  Print out all the position element

	IMUSimulator::Position_IMU last_traj_elements = traj.traj_data.back();
	std::cout << last_traj_elements;												// Print out just the last position element

	getchar();
	return;
	*/
}

void test2(void) {
	/*Refine this test*/
	/*typedef std::numeric_limits< double > dbl;
	std::cout.precision(dbl::max_digits10);

	double llh_array[3] = { 0,0,0 };
	double Rn, Re, g, sL, cL, WIE_E;

	IMUSimulator::IMUSignalGenerator imuGenerator;

	IMUSimulator::WGS84Ellipsoid myellip(llh_array, IMUSimulator::LLH_Frame);
	myellip.getParams(Rn, Re, g, sL, cL, WIE_E);

	std::cout << Rn << "   " <<
		Re << "   " <<
		g << "   " <<
		sL << "   " <<
		cL << "   " <<
		WIE_E << std::endl;

	Eigen::Vector3d ab, wb, Vb, ab_comp, wb_comp, Vb_comp;
	ab << 0, 0, 0;
	Eigen::Vector3d bode2ecef_angle, nav2ecef_angle, local_angle;
	wb << 0, 0, 0;

	Eigen::Matrix3d Cnb;
	Eigen::Vector3d ecef;
	Eigen::Vector3d llh;
	llh << 0, 0, 0;
	ecef = IMUSimulator::Lib::transform_llh2ecef(llh);
	IMUSimulator::strapdown_ecef str_e(ecef);
	IMUSimulator::IMUStore imuStore;
	IMUSimulator::Trajectory traj;

	IMUSimulator::Measure_IMU meas;

	double dt = 0.1;
	double time = 0.0;
	double time_max = 100.0;

	for (time = 0; time < time_max; time += dt) {

	std:cout << endl;

		/*nav2ecef_angle = IMUSimulator::Lib::dcm2euler(str_e.Cne);
		std::cout << "Roll, pitch, yaw: " << nav2ecef_angle << std::endl;
		bode2ecef_angle = IMUSimulator::Lib::dcm2euler(str_e.Cbe);
		std::cout << "Roll, pitch, yaw: " << bode2ecef_angle << std::endl;*/
		/*
		Cnb = str_e.Cne.transpose()*str_e.Cbe;
		local_angle = IMUSimulator::Lib::dcm2euler(Cnb);

		Vb = str_e.getVbody();
		llh = str_e.getLLH();
		*/
		/*std::cout << "Acc body: " << std::endl << ab << std::endl;
		std::cout << "Angular rate body: " << std::endl << wb << std::endl;
		std::cout << "Velocity body: " << std::endl << Vb << std::endl;
		std::cout << "Lat lon height: " << std::endl << llh << std::endl;
		std::cout << "Roll, pitch, yaw: " << std::endl << local_angle << std::endl;*/
		/*
		meas = imuGenerator.calculate(ab, wb, Vb, llh, local_angle);

		meas.wn = 1956;
		meas.tow = time;

		//std::cout << "IMU measurement: " << std::endl << meas << std::endl;

		imuStore.add_measure(IMUSimulator::GPSTime, meas);

		str_e.update(meas, dt);
		//std::cout << str_e << endl;
		traj << str_e;
		traj.updateTime(IMUSimulator::GPSTime, meas.wn, meas.tow);
	}

	IMUSimulator::Position_IMU last_traj_elements = traj.traj_data.back();

	//std::cout << imuStore << endl;
	//std::cout << traj << endl;
	std::cout << last_traj_elements;


	getchar();
	return;*/
}