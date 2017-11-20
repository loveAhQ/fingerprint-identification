#include"CFinPrint.h"

//consruction
CFinPrint::CFinPrint()
{
	m_flist.clear();
}

CFinPrint::CFinPrint(char * imgFile)
{
	Create(imgFile);
}

//destruction
CFinPrint::~CFinPrint()
{
	if(!m_flist.empty())
	{
		m_flist.clear();
	}
}

//Create a fingerprint
void CFinPrint::Create(char* imgFile)
{
	cv::Mat tMat = cv::imread(imgFile, cv::IMREAD_GRAYSCALE);//load a fringerprint image by grayscale
	
	 //obtain binary image
	threshold(tMat, tMat, 128, 255, CV_THRESH_BINARY_INV);
	threshold(tMat, tMat, 128, 1, CV_THRESH_BINARY);

	
	cv::Mat sk = thinImage(tMat);//obtain the skeletion image
	//sk = sk * 255;
	//CTool::ShowImage(sk);
	//CTool::WaitCV();
	
	CreateFList(sk); //create the characterisitc vector

	return;
}


//private member ------------------------------------------------------------------------------

//create the skeleton image
cv::Mat CFinPrint::thinImage(const cv::Mat & src)
{
	cv::Mat dst;
	int width = src.cols;
	int height = src.rows;
	src.copyTo(dst);
	
	while (true)
	{
		
		std::vector<uchar *> mFlag; //the flag mat
		
		// the Zhang algorithm
		//first loops
		for (int i = 0; i < height; ++i)
		{
			uchar * p = dst.ptr<uchar>(i);
			for (int j = 0; j < width; ++j)
			{
				//the 8 neibors of the p1
				//  p9 p2 p3  
				//  p8 p1 p4  
				//  p7 p6 p5  
				uchar p1 = p[j];
				if (p1 != 1) continue;
				uchar p4 = (j == width - 1) ? 0 : *(p + j + 1);
				uchar p8 = (j == 0) ? 0 : *(p + j - 1);
				uchar p2 = (i == 0) ? 0 : *(p - dst.step + j);
				uchar p3 = (i == 0 || j == width - 1) ? 0 : *(p - dst.step + j + 1);
				uchar p9 = (i == 0 || j == 0) ? 0 : *(p - dst.step + j - 1);
				uchar p6 = (i == height - 1) ? 0 : *(p + dst.step + j);
				uchar p5 = (i == height - 1 || j == width - 1) ? 0 : *(p + dst.step + j + 1);
				uchar p7 = (i == height - 1 || j == 0) ? 0 : *(p + dst.step + j - 1);
				if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 2 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) <= 6)
				{
					int ap = 0;
					if (p2 == 0 && p3 == 1) ++ap;
					if (p3 == 0 && p4 == 1) ++ap;
					if (p4 == 0 && p5 == 1) ++ap;
					if (p5 == 0 && p6 == 1) ++ap;
					if (p6 == 0 && p7 == 1) ++ap;
					if (p7 == 0 && p8 == 1) ++ap;
					if (p8 == 0 && p9 == 1) ++ap;
					if (p9 == 0 && p2 == 1) ++ap;

					if (ap == 1 && p2 * p4 * p6 == 0 && p4 * p6 * p8 == 0)
					{  
						mFlag.push_back(p + j);
					}
				}
			}
		}

		//second loops
		for (std::vector<uchar *>::iterator i = mFlag.begin(); i != mFlag.end(); ++i)
		{
			**i = 0;
		}

		
		if (mFlag.empty())
		{
			break;
		}
		else
		{
			mFlag.clear();
		}

		 //
		for (int i = 0; i < height; ++i)
		{
			uchar * p = dst.ptr<uchar>(i);
			for (int j = 0; j < width; ++j)
			{
				
				uchar p1 = p[j];
				if (p1 != 1) continue;
				uchar p4 = (j == width - 1) ? 0 : *(p + j + 1);
				uchar p8 = (j == 0) ? 0 : *(p + j - 1);
				uchar p2 = (i == 0) ? 0 : *(p - dst.step + j);
				uchar p3 = (i == 0 || j == width - 1) ? 0 : *(p - dst.step + j + 1);
				uchar p9 = (i == 0 || j == 0) ? 0 : *(p - dst.step + j - 1);
				uchar p6 = (i == height - 1) ? 0 : *(p + dst.step + j);
				uchar p5 = (i == height - 1 || j == width - 1) ? 0 : *(p + dst.step + j + 1);
				uchar p7 = (i == height - 1 || j == 0) ? 0 : *(p + dst.step + j - 1);

				if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 2 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) <= 6)
				{
					int ap = 0;
					if (p2 == 0 && p3 == 1) ++ap;
					if (p3 == 0 && p4 == 1) ++ap;
					if (p4 == 0 && p5 == 1) ++ap;
					if (p5 == 0 && p6 == 1) ++ap;
					if (p6 == 0 && p7 == 1) ++ap;
					if (p7 == 0 && p8 == 1) ++ap;
					if (p8 == 0 && p9 == 1) ++ap;
					if (p9 == 0 && p2 == 1) ++ap;

					if (ap == 1 && p2 * p4 * p8 == 0 && p2 * p6 * p8 == 0)
					{
						mFlag.push_back(p + j);
					}
				}
			}
		}

		//obtain the skeleton
		for (std::vector<uchar *>::iterator i = mFlag.begin(); i != mFlag.end(); ++i)
		{
			**i = 0;
		}

	
		if (mFlag.empty())
		{
			break;
		}
		else
		{
			mFlag.clear();
		}
	}
	return dst;
}

//ceate the characteristic vector
void CFinPrint::CreateFList(cv::Mat & src)
{
	m_flist.clear();//clear vector

	uchar sum = 0;// the sum of 8 neighbors of the center point
	uchar neighbors[8];// the 8 neighbors
	FFP tf; 
	int cols = src.cols;
	int rows = src.rows;
	for (int i = 1; i < rows; i++)
	{
		
		for (int j = 1; j < cols; j++)
		{
				
			if (src.at<uchar>(i, j) == 1)// if center point is a skeleton
			{
				//obtain the 8 neighbors
				neighbors[0] = (i==0||j==0) ? 0 : src.at<uchar>(i-1, j-1);
				neighbors[1] = (i==0) ? 0 : src.at<uchar>(i-1, j);
				neighbors[2] = (i==0|| j==cols-1) ? 0 : src.at<uchar>(i-1, j+1);
				neighbors[3] = (j==cols-1) ? 0 : src.at<uchar>(i, j+1);
				neighbors[4] = (i==rows-1 || j==cols-1) ? 0 : src.at<uchar>(i+1, j+1);
				neighbors[5] = (i==rows-1) ? 0 : src.at<uchar>(i+1, j);
				neighbors[6] = (i==rows-1 || j==0) ? 0 : src.at<uchar>(i+1, j-1);
				neighbors[7] = (j==0) ? 0 : src.at<uchar>(i, j-1);
				//sum
				for (int k = 0; k < 8; k++)
				{
					sum += abs(neighbors[k + 1] - neighbors[k]);
				}
				
				if (sum == 2)//the center is a end point
				{
					tf.type = 1;
					tf.x = i;
					tf.y = j;
					m_flist.push_back(tf);
				}
				else if (sum == 6) // the center is a branch point
				{
					tf.type = 2;
					tf.x = i;
					tf.y = j;
					m_flist.push_back(tf);
				}
				
			}
				

		}//end for j
	}//end for i

}