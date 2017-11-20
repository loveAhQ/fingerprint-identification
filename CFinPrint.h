#pragma once
#include"sysInclude.h"


//fingerprint class
//this class is based on the OpenCV liberay
class CFinPrint
{
public:
	struct FFP //fingerprint feature point
	{
		int x, y;//the station of the ffp
		uchar type;// the type of the ffp. 1 = end point 2=branch point
	};
public:
	//construction  function
	CFinPrint();

	//construction  function
	//imgFile = the name of image that contains a fingerprint
	CFinPrint(char* imgFile);

	//desctruction
	~CFinPrint();

	// create a fingerprint object used for matching
	// imgFile = the name of image that contains a fingerprint
	void Create(char* imgFile);

	//get the feature vector that represents the fingerprint
	std::vector<FFP>& GetFList()
	{
		return m_flist;
	}

private:
	//calculate the skeleton line of the fingerprint
	//scr = fingerprint image that should be a binary image. In the image, the 1 is the fringprint color and 0 is the background color
	//return the skeletion image
	cv::Mat thinImage(const cv::Mat & src);

	//Create the feature point list according to the skeletion imgage
	void CreateFList(cv::Mat & sk);

	//the feature point vector
	std::vector<FFP> m_flist;

};