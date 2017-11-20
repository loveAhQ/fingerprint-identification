#include"CFinPrint.h"
#include"CFPrintMatch.h"
using namespace std;


int main() 
{
	//the the size of fingerprint images should be 256x256
	

	CFinPrint f1("fp1.jpg");
	CFinPrint f2("fp2.jpg");

	CFPrintMatch m(32, 64, 8, 4);
		
	cout << "An example of matching fingerprint(one to one) " << endl;

	cout << "match f1 with f2" << endl;
	if (m.Matching(f1, f2))
	{
		cout << "the two fingerprints are similar" << endl;
	}
	else
	{
		cout << "the two fingerprints are different" << endl;
	}
	
	cout << "match f1 with f1" << endl;
	if (m.Matching(f1, f1))
	{
		cout << "the two fingerprints are similar" << endl;
	}
	else
	{
		cout << "the two fingerprints are different" << endl;
	}
		

	CFinPrint f3("fp3.jpg");
	CFinPrint f4("fp2.jpg");
	CFinPrint f5("fp1.jpg");

	vector<CFinPrint> fps;
	fps.push_back(f1);
	fps.push_back(f2);
	fps.push_back(f3);
	fps.push_back(f4);
	fps.push_back(f5);

	cout << endl;
	cout << endl;
	cout << "An example of matching fingerprint(one to many)" << endl;
	vector<int> ids = m.Matching(f1, fps);
	
	cout << "match f1 with f2,f3,f4 and f5." << endl;
	for (int i = 0; i < ids.size(); i++)
	{
		cout << "f1 is similar to f"<< ids[i] << endl;
	}
	CTool::Wait();

	return 1;
}

