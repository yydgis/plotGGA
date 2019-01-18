//------------------------------------------------------------------------------
// GNSS/IMU integration
// Developed by Dr. Yudan Yi
// Created on 11/21/2012
// Modified on 01/26/2016
//------------------------------------------------------------------------------
#ifndef _NEMA_GGA_H_
#define _NEMA_GGA_H_
//------------------------------------------------------------------------------
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
//------------------------------------------------------------------------------
#include "geoconst.h"
#include "geotrans.h"
//------------------------------------------------------------------------------
namespace gnssimu_lib
{
	//--------------------------------------------------------------------------
	class TGPGGA
	{
	public:
		//----------------------------------------------------------------------
        double time, blh[3], N, HDOP, xyz[3], ned[3];
		int numOfSat, solType;
		//----------------------------------------------------------------------
	public:
		~TGPGGA() {}
		TGPGGA()
		{
			memset(this, '\0', sizeof(TGPGGA)); 
		}
		TGPGGA(const TGPGGA& src)
		{
			memcpy(this, &src, sizeof(TGPGGA));
		}
		TGPGGA& operator= (const TGPGGA& src)
		{
			if (this!=&src)
			{
				memcpy(this, &src, sizeof(TGPGGA));
			}
			return *this;
		}
		//----------------------------------------------------------------------
		void ReSet()
		{
			memset(this, '\0', sizeof(TGPGGA)); 
		}
		//----------------------------------------------------------------------
		bool read(std::string& line)
		{
			ReSet();

			std::string curstr;

			std::string::size_type nLoc = line.find("$GPGGA"), nPreLoc; if (nLoc == std::string::npos) return false;
			//$GPGGA,201615.60,3946.9431210,N,08404.9232523,W,5,07,1.19,255.0887,M,0.0,M,0.0,0000*6A
			nPreLoc = 0;
			nLoc = line.find(',', nPreLoc); if (nLoc == std::string::npos) return false;
			// GPGGA
			nPreLoc = nLoc+1; 
			nLoc = line.find(',', nPreLoc); if (nLoc == std::string::npos) return false;
			// UTC time
			curstr = line.substr(nPreLoc, nLoc-nPreLoc); if (curstr.length()<6) return false;
			double hh = atof(curstr.substr(0,2).c_str());
			double mm = atof(curstr.substr(2,2).c_str());
			double ss = atof(curstr.substr(4).c_str());
			time = hh*3600.0+mm*60.0+ss;
			// latitude
			nPreLoc = nLoc+1; 
			nLoc = line.find(',', nPreLoc); if (nLoc == std::string::npos) return false;
			curstr = line.substr(nPreLoc, nLoc-nPreLoc); if (curstr.length()<4) return false;
			double dd = atof(curstr.substr(0,2).c_str());
			       mm = atof(curstr.substr(2).c_str());
			blh[0] = (dd+mm/60.0)*PI/180.0;
			// S/N for latitude
			nPreLoc = nLoc+1; 
			nLoc = line.find(',', nPreLoc); if (nLoc == std::string::npos) return false;
			curstr = line.substr(nPreLoc, nLoc-nPreLoc); if (curstr.length()<1) return false;
			if (curstr[0]=='S'||curstr[0]=='s') blh[0] =-blh[0];
			// longitude
			nPreLoc = nLoc+1; 
			nLoc = line.find(',', nPreLoc); if (nLoc == std::string::npos) return false;
			curstr = line.substr(nPreLoc, nLoc-nPreLoc); if (curstr.length()<5) return false;
			dd = atof(curstr.substr(0,3).c_str());
			mm = atof(curstr.substr(3).c_str());
			blh[1] = (dd+mm/60.0)*PI/180.0;
			// E/W for longitude
			nPreLoc = nLoc+1; 
			nLoc = line.find(',', nPreLoc); if (nLoc == std::string::npos) return false;
			curstr = line.substr(nPreLoc, nLoc-nPreLoc); if (curstr.length()<1) return false;
			if (curstr[0]=='W'||curstr[0]=='w') blh[1] =-blh[1];
			// solution type
			nPreLoc = nLoc+1; 
			nLoc = line.find(',', nPreLoc); if (nLoc == std::string::npos) return false;
			curstr = line.substr(nPreLoc, nLoc-nPreLoc); if (curstr.length()<1) return false;
			solType = atoi(curstr.c_str());
			// number of satellite
			nPreLoc = nLoc+1; 
			nLoc = line.find(',', nPreLoc); if (nLoc == std::string::npos) return false;
			curstr = line.substr(nPreLoc, nLoc-nPreLoc); if (curstr.length()<1) return false;
			numOfSat = atoi(curstr.c_str());
			// HDOP
			nPreLoc = nLoc+1; 
			nLoc = line.find(',', nPreLoc); if (nLoc == std::string::npos) return false;
			curstr = line.substr(nPreLoc, nLoc-nPreLoc); if (curstr.length()<1) return false;
			HDOP = atof(curstr.c_str());
			// altitude
			nPreLoc = nLoc+1; 
			nLoc = line.find(',', nPreLoc); if (nLoc == std::string::npos) return false;
			curstr = line.substr(nPreLoc, nLoc-nPreLoc); if (curstr.length()<1) return false;
			blh[2] = atof(curstr.c_str());
			// M/m
			nPreLoc = nLoc+1; 
			nLoc = line.find(',', nPreLoc); if (nLoc == std::string::npos) return false;
			curstr = line.substr(nPreLoc, nLoc-nPreLoc); if (curstr.length()<1) return false;
			if (curstr[0]!='M'&&curstr[0]!='m') return false; 
			// geo height N
			nPreLoc = nLoc+1; 
			nLoc = line.find(',', nPreLoc); if (nLoc == std::string::npos) return false;
			curstr = line.substr(nPreLoc, nLoc-nPreLoc); if (curstr.length()<1) return false;
			N = atof(curstr.c_str());
			// M/m
			nPreLoc = nLoc+1; 
			nLoc = line.find(',', nPreLoc); if (nLoc == std::string::npos) return false;
			curstr = line.substr(nPreLoc, nLoc-nPreLoc); if (curstr.length()<1) return false;
			if (curstr[0]!='M'&&curstr[0]!='m') return false; 
			blh[2] += N;
			if (blh[0]==0.0&&blh[1]==0.0&&blh[2]==0.0) return false;
			return true;
		}
		//----------------------------------------------------------------------
		std::string write()
		{

		}
	};
	//--------------------------------------------------------------------------
	class TNEMAGGAReader
	{
    private:
        double refBLH[3], refXYZ[3], C_en[3][3];
	protected:
	public:
		std::vector<TGPGGA> vGGA_;
		~TNEMAGGAReader() {}
		TNEMAGGAReader()
		{
            memset(refBLH, '\0', sizeof(refBLH));
            memset(refXYZ, '\0', sizeof(refXYZ));
            memset(C_en, '\0', sizeof(C_en));
		}
		TNEMAGGAReader(const TNEMAGGAReader& src)
		{
            memcpy(refBLH, src.refBLH, sizeof(refBLH));
            memcpy(refXYZ, src.refXYZ, sizeof(refXYZ));
            memcpy(C_en, src.C_en, sizeof(C_en));
            vGGA_ = src.vGGA_;
		}
		TNEMAGGAReader& operator= (const TNEMAGGAReader& src)
		{
			if (this!=&src)
			{
                memcpy(refBLH, src.refBLH, sizeof(refBLH));
                memcpy(refXYZ, src.refXYZ, sizeof(refXYZ));
                memcpy(C_en, src.C_en, sizeof(C_en));
                vGGA_ = src.vGGA_;
			}
			return *this;
		}
		//----------------------------------------------------------------------
		void ReSet()
		{
            memset(refBLH, '\0', sizeof(refBLH));
            memset(refXYZ, '\0', sizeof(refXYZ));
            memset(C_en, '\0', sizeof(C_en));
            vGGA_.clear();
		}
		//----------------------------------------------------------------------
		void ReadGGA(const char *fileName)
		{
			std::ifstream fGGA(fileName, std::ios::in);
			if (fGGA.is_open()) {
                TGPGGA curGGA;
				char buffer[1024];
				while (!fGGA.eof())
				{
					fGGA.getline(buffer, sizeof(buffer));
                    if (curGGA.read(std::string(buffer)))
                    {
                        if (refXYZ[0]==0.0&&refXYZ[1]==0.0&&refXYZ[2]==0.0)
                        {
                            refBLH[0] = curGGA.blh[0];
                            refBLH[1] = curGGA.blh[1];
                            refBLH[2] = curGGA.blh[2];
                            blh2xyz(refBLH, refXYZ);
                            blh2C_en(refBLH, C_en);
                        }
                        else
                        {
                            blh2xyz(curGGA.blh, curGGA.xyz);
                            double dXYZ[] = { curGGA.xyz[0]-refXYZ[0],
                                              curGGA.xyz[1]-refXYZ[1],
                                              curGGA.xyz[2]-refXYZ[2] };
                            curGGA.ned[0] =  C_en[0][0]*dXYZ[0]+C_en[1][0]*dXYZ[1]+C_en[2][0]*dXYZ[2];
                            curGGA.ned[1] =  C_en[0][1]*dXYZ[0]+C_en[1][1]*dXYZ[1]+C_en[2][1]*dXYZ[2];
                            curGGA.ned[2] =-(C_en[0][2]*dXYZ[0]+C_en[1][2]*dXYZ[1]+C_en[2][2]*dXYZ[2]);
                        }
                        vGGA_.push_back(curGGA);
                    }
				}
				fGGA.close();
			}
			return;
		}
		//----------------------------------------------------------------------
	};
	//--------------------------------------------------------------------------
};
#endif
