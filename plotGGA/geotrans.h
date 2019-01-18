//------------------------------------------------------------------------------
// GNSS/IMU integration
// Developed by Dr. Yudan Yi
// Created on 11/24/2012
//------------------------------------------------------------------------------
#ifndef _GEO_TRANS_H_
#define _GEO_TRANS_H_
//------------------------------------------------------------------------------
#include "geoconst.h"
//------------------------------------------------------------------------------
namespace gnssimu_lib
{
	//--------------------------------------------------------------------------
	//--------------------------------------------------------------------------
	//**************************************************************************
	// GNSS receiver and satellite related models and transformations
	//**************************************************************************
	//--------------------------------------------------------------------------
    // functions relatingt to coordinate transformation and matrix (vector) rotation
	void	blh2xyz(const double *blh, double *xyz)
	{
		// lat, lon, ht => ecef xyz
		double a = ae_WGS84, finv = finv_WGS84;
		double f	= 1.0/finv, e2=2*f-f*f;
		double lat	= blh[0], lon = blh[1], ht = blh[2];
		double Rw	= sqrt(1-e2*sin(lat)*sin(lat));
		double Rn	= a/Rw;
		xyz[0] = (Rn+ht)*cos(lat)*cos(lon);
		xyz[1] = (Rn+ht)*cos(lat)*sin(lon);
		xyz[2] = (Rn*(1-e2)+ht)*sin(lat);
		return;
	}
	void	xyz2blh(const double *xyz, double *blh)
	{
		// ecef xyz => blh
		double a = ae_WGS84, finv = finv_WGS84;
		double f = 1.0/finv, e2=2*f-f*f;
		double x = xyz[0], y = xyz[1], z = xyz[2], lat, lon, ht;
		double R = sqrt(x*x+y*y+z*z);
		double ang = atan(fabs(z/sqrt(x*x+y*y)));
		if (z<0.0) ang = -ang;
		double lat1 = ang;
		double Rw = sqrt(1-e2*sin(lat1)*sin(lat1));
		lat = atan(fabs(tan(ang)*(1+(a*e2*sin(lat1))/(z*Rw))));
		if (z<0.0) lat =-lat;
		while (fabs(lat-lat1)>1e-12)
		{
			lat1 = lat;
			Rw = sqrt(1-e2*sin(lat1)*sin(lat1));
			lat = atan(fabs(tan(ang)*(1+(a*e2*sin(lat1))/(z*Rw))));
			if (z<0.0) lat =-lat;
		}
		if (lat>PI) lat = lat-2.0*PI;
		if (fabs(x)<1e-12) { if (y>=0.0) lon = PI/2.0; else lon = 3.0*PI/2.0; }
		else
		{
			lon = atan(fabs(y/x));
			if (x>0.0) { if (y>=0.0) lon =lon; else lon = 2.0*PI-lon; }
			else { if (y>=0.0) lon = PI-lon; else lon = PI+lon; }
		}
		Rw = sqrt(1-e2*sin(lat)*sin(lat));
		double Rn = a/Rw;
		ht = R*cos(ang)/cos(lat)-Rn;
		if (lon>PI) lon = lon-2.0*PI;
		blh[0] = lat;
		blh[1] = lon;
		blh[2] = ht;
		return ;
	}
	void    blh2C_en(const double *blh, double C_en[3][3])
	{
		// blh => C_en
		double lat = blh[0], lon = blh[1];//, ht = blh[2];
		C_en[0][0] =-sin(lat)*cos(lon);
		C_en[1][0] =-sin(lat)*sin(lon);
		C_en[2][0] = cos(lat)         ;
		C_en[0][1] =-         sin(lon);
		C_en[1][1] =          cos(lon);
		C_en[2][1] =               0.0;
		C_en[0][2] =-cos(lat)*cos(lon);
		C_en[1][2] =-cos(lat)*sin(lon);
		C_en[2][2] =-sin(lat);
		return;
	}
	void    blh2C_en(const double *blh, double **C_en)
	{
		double lat = blh[0], lon = blh[1];//, ht = blh[2];
		C_en[0][0] =-sin(lat)*cos(lon);
		C_en[1][0] =-sin(lat)*sin(lon);
		C_en[2][0] = cos(lat)        ;
		C_en[0][1] =-         sin(lon);
		C_en[1][1] =          cos(lon);
		C_en[2][1] =               0.0;
		C_en[0][2] =-cos(lat)*cos(lon);
		C_en[1][2] =-cos(lat)*sin(lon);
		C_en[2][2] =-sin(lat);
		return;
	}
	//--------------------------------------------------------------------------
}
#endif