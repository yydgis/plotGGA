#ifndef _GGA_INFO_
#define _GGA_INFO_

#include <vector>

struct TGgaInfo
{
	int year;
	int doy;
	int hh;
	int mm;
	double ss;
	double lat;
	double lon;
	int flag;
	int satnum;
	double dop;
	double ht;
	double geoht;
	double lag;
	double neu[3];
	double xyz[3];
	int outlierFlag;
	TGgaInfo()
	{
		memset(this, '\0', sizeof(TGgaInfo));
	}
	TGgaInfo(const TGgaInfo& src)
	{
		if (this!=&src)
		{
			memcpy(this, &src, sizeof(TGgaInfo));
		}
	}
	TGgaInfo operator=(TGgaInfo src)
	{
		if (this!=&src)
		{
			memcpy(this, &src, sizeof(TGgaInfo));
		}
		return *this;
	}
	double time() const { return doy+(hh+mm/60.0+ss/3600.0)/24.0; }
	bool operator==(const TGgaInfo& src) const 
	{ 
		return time()==src.time(); 
	}
	bool operator< (const TGgaInfo& src) const 
	{ 
		return time()< src.time(); 
	}
	bool valid() const { return flag>0; }
	void reset()
	{
		memset(this, '\0', sizeof(TGgaInfo));
	}
};

//int readGGA(QString& fname, std::vector<TGgaInfo>& vGGA, int year, int doy);

#endif
