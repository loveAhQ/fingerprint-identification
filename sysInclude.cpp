#include"sysInclude.h"

int CTool::index = 0;
void CTool::ShowImage(cv::Mat & tMat)
{
	char winName[20];
	sprintf(winName, "window: %d\n", index);
	cv::namedWindow(winName, cv::WINDOW_AUTOSIZE);  
	cv::imshow(winName, tMat);              
	index++;
}

void CTool::WaitCV()
{

	cv::waitKey(0);
}

void CTool::Wait()
{
	system("pause");
}

void CTool::Error(char* error)
{
	std::cout << error << std::endl;
}

void CTool::ErrorFile(char* error)
{
	FILE* fp = fopen("error.txt", "a");

	fprintf(fp, "error: %s\n", error);

	fclose(fp);
}