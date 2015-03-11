// EnergyPlus::DXCoils unit tests
// DX heating coil defrost capacity with electric resistance

// Google test headers
#include <gtest/gtest.h>

// C++ Headers
#include <cassert>
#include <cmath>
#include <string>

// ObjexxFCL Headers
#include <ObjexxFCL/FArray.functions.hh>
#include <ObjexxFCL/Fmath.hh>
#include <ObjexxFCL/gio.hh>

// EnergyPlus Headers
#include <DataAirflowNetwork.hh>
#include <AirflowNetworkBalanceManager.hh>
#include <DataSurfaces.hh>

using namespace EnergyPlus;
using namespace AirflowNetworkBalanceManager;
using namespace DataAirflowNetwork;
using namespace DataSurfaces;

TEST( AirflowNetworkBalanceManagerTest, TestOtherSideCoefficients )
{

	int i = 2;

	AirflowNetworkNumOfExtSurfaces = 2;
	AirflowNetworkNumOfSurfaces = 2;

	MultizoneSurfaceData.allocate( i );
	Surface.allocate( i );
	Surface( 1 ).ExtBoundCond = -2;
	Surface( 2 ).ExtBoundCond = -2;
	Surface( 1 ).ExtWind = true;
	Surface( 2 ).ExtWind = true;
	Surface( 1 ).Tilt = 90.0;
	Surface( 2 ).Tilt = 90.0;
	Surface( 1 ).Azimuth = 0.0;
	Surface( 2 ).Azimuth = 180.0;

	MultizoneSurfaceData( 1 ).SurfNum =	1;
	MultizoneSurfaceData( 2 ).SurfNum = 2;

	CalcWindPressureCoeffs( );
	EXPECT_EQ( 1, MultizoneSurfaceData( 1 ).NodeNums( 2 ) );
	EXPECT_EQ( 2, MultizoneSurfaceData( 2 ).NodeNums( 2 ) );
	EXPECT_EQ( 1, MultizoneExternalNodeData( 1 ).CPVNum );
	EXPECT_EQ( 3, MultizoneExternalNodeData( 2 ).CPVNum );

	MultizoneSurfaceData.deallocate( );
	MultizoneExternalNodeData.deallocate( );
}


