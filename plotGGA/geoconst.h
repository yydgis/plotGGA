//------------------------------------------------------------------------------
// GNSS/IMU integration
// Developed by Dr. Yudan Yi
// Created on 11/21/2012
//------------------------------------------------------------------------------
#ifndef _GEO_CONST_H_
#define _GEO_CONST_H_
//------------------------------------------------------------------------------
namespace gnssimu_lib
{
	//--------------------------------------------------------------------------
	const double PI				= 3.14159265358979;
	//--------------------------------------------------------------------------
    const double VEL_LIGHT  	= 299792458.0;				// Vacuum speed of light
	//--------------------------------------------------------------------------
    const double We_WGS84   	= 7.2921151467e-5;
    const double GM_WGS84   	= 3.9860050e+14;
    const double ae_WGS84   	= 6378137.0;
    const double finv_WGS84 	= 298.257223563;
    const double finv_Pz90  	= 298.257839303;
	const double grav_WGS84     = 9.7803267714e0;
	//--------------------------------------------------------------------------
	const int MAX_GPS_PRN = 40;
	const int MAX_GLO_PRN = 30;
	const int MAX_GAL_PRN = 30;
	const int MAX_GEO_PRN = 10;
	//--------------------------------------------------------------------------
	const int BEG_GPS_PRN = 0;
	const int END_GPS_PRN = BEG_GPS_PRN+MAX_GPS_PRN-1;
	const int BEG_GLO_PRN = END_GPS_PRN+1;
	const int END_GLO_PRN = BEG_GLO_PRN+MAX_GLO_PRN-1;
	const int BEG_GAL_PRN = END_GLO_PRN+1;
	const int END_GAL_PRN = BEG_GAL_PRN+MAX_GAL_PRN-1;
	const int BEG_GEO_PRN = END_GAL_PRN+1;
	const int END_GEO_PRN = BEG_GEO_PRN+MAX_GEO_PRN-1;
	//--------------------------------------------------------------------------
	const char SYS_ID_GPS = 'G';
	const char SYS_ID_GLO = 'R';
	const char SYS_ID_GAL = 'E';
	const char SYS_ID_GEO = 'S';
	const char SYS_ID_NULL= 'U';
	//--------------------------------------------------------------------------
	const int SYS_INDEX_GPS = 1;
	const int SYS_INDEX_GLO = 2;
	const int SYS_INDEX_GAL = 3;
	const int SYS_INDEX_GEO = 4;
	const int SYS_INDEX_NULL= 0;
	//--------------------------------------------------------------------------
	const int FREQ_NUM_NULL = -99;
	const int FREQ_NUM_GLO[] = { FREQ_NUM_NULL,
								   1 ,//01|  730  | 2456 | 1/01 |  01  | 14.12.2009 | 30.01.2010 | operating | .......... |
								  -4 ,//02|  728  | 2448 | 1/02 |  -4  | 25.12.2008 | 20.01.2009 | operating | .......... |
								  -5 ,//03|  722  | 2435 | 1/03 |  -5  | 25.12.2007 | 25.01.2008 |  unusable | 01.10.2010 |
								   6 ,//04|  727  | 2447 | 1/04 |  06  | 25.12.2008 | 17.01.2009 |  unusable | 08.09.2010 |
								   1 ,//05|  734  | 2458 | 1/05 |  01  | 14.12.2009 | 10.01.2010 | operating | .......... |
								  -4 ,//06|  733  | 2457 | 1/06 |  -4  | 14.12.2009 | 24.01.2010 | operating | .......... |
								   5 ,//07|  712  | 2413 | 1/07 |  05  | 26.12.2004 | 06.10.2005 | operating | .......... |
								   6 ,//08|  729  | 2449 | 1/08 |  06  | 25.12.2008 | 12.02.2009 | operating | .......... |
								  -2 ,//09|  736  | 2464 | 2/09 |  -2  | 02.09.2010 | 04.10.2010 | operating | .......... |
								  -7 ,//10|  717  | 2426 | 2/10 |  -7  | 25.12.2006 | 03.04.2007 | operating | .......... |
								   0 ,//11|  723  | 2436 | 2/11 |  00  | 25.12.2007 | 22.01.2008 | operating | .......... |
								  -1 ,//12|  737  | 2465 | 2/12 |  -1  | 02.09.2010 | 11.10.2010 | operating | .......... |
								  -2 ,//13|  721  | 2434 | 2/13 |  -2  | 25.12.2007 | 08.02.2008 | operating | .......... |
								  -7 ,//14|  715  | 2424 | 2/14 |  -7  | 25.12.2006 | 03.04.2007 |  unusable | 24.10.2010 |
								   0 ,//15|  716  | 2425 | 2/15 |  00  | 25.12.2006 | 12.10.2007 | operating | .......... |
								  -1 ,//16|  738  | 2466 | 2/16 |  -1  | 02.09.2010 | 12.10.2010 | operating | .......... |
								   4 ,//17|  718  | 2431 | 3/17 |  04  | 26.10.2007 | 04.12.2007 |  unusable | 29.11.2010 |
								  -3 ,//18|  724  | 2442 | 3/18 |  -3  | 25.09.2008 | 26.10.2008 | operating | .......... |
								   3 ,//19|  720  | 2433 | 3/19 |  03  | 26.10.2007 | 25.11.2007 | operating | .......... |
								   2 ,//20|  719  | 2432 | 3/20 |  02  | 26.10.2007 | 27.11.2007 | operating | .......... |
								   4 ,//21|  725  | 2443 | 3/21 |  04  | 25.09.2008 | 05.11.2008 | operating | .......... |
								  -3 ,//22|  731  | 2459 | 3/22 |  -3  | 02.03.2010 | 28.03.2010 | operating | .......... |
								   3 ,//23|  732  | 2460 | 3/23 |  03  | 02.03.2010 | 28.03.2010 | operating | .......... |
								   2  //24|  735  | 2461 | 3/24 |  02  | 02.03.2010 | 28.03.2010 | operating | .......... |
								};
	//--------------------------------------------------------------------------
	const double FREQ_F0_GPS = 10230000.0;
	const double FREQ_F1_GPS = 154.0*FREQ_F0_GPS;
	const double FREQ_F2_GPS = 120.0*FREQ_F0_GPS;
	const double FREQ_F1_GLO = 1602000000.0;
	const double FREQ_F2_GLO = 1246000000.0;
	const double DELT_FREQ_F1_GLO = 562500.0;
	const double DELT_FREQ_F2_GLO = 437500.0;
	//--------------------------------------------------------------------------
}
#endif