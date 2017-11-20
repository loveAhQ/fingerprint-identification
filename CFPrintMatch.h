#pragma once
#include "CFinPrint.h"

//the mathching finger print class
//This class is used to mathch two different fingerprints

typedef 
int(*Hash)(int); //the hash function pointer that is used in minimum hash algorithm

class CFPrintMatch
{
public:
	const static int INFINITE = 1000;//defind the infinite that is used in minimum
	struct FMesh //the mesh used for matching finger print
	{
		int gWidth, gHeight;//the grid witdth and height
		int cols, rows;//the number of cols and rows of the Mesh. For example, int the 8X4 Mesh, cols =8 and rows = 4
	};
public:
	CFPrintMatch()//construction function
	{
		m_mesh.gWidth = 0;
		m_mesh.gHeight = 0;
		m_mesh.cols = 0;
		m_mesh.rows = 0;
	}
	CFPrintMatch(int gWidth, int gHeight, int cols, int rows)
	{
		SetMesh(gWidth, gHeight, cols, rows);
	}
	CFPrintMatch(FMesh & mesh)
	{
		SetMesh(mesh);
	}

	//Set the Mesh
	void SetMesh(int gWidth, int gHeight, int cols, int rows)
	{
		m_mesh.gWidth = gWidth;
		m_mesh.gHeight = gHeight;
		m_mesh.cols = cols;
		m_mesh.rows = rows;
	}

	void SetMesh(FMesh & mesh)
	{
		m_mesh.gWidth = mesh.gWidth;
		m_mesh.gHeight = mesh.gHeight;
		m_mesh.rows = mesh.rows;
		m_mesh.cols = mesh.cols;
	}

	// Matching algorithm (one matches many)
	// tfp = the fingerprint templete
	//fps = the fingerprint list to be match
	virtual std::vector<int>  Matching(CFinPrint & tfp, std::vector<CFinPrint> & fps);

	//Mathing algorim (one matches one)
	//fp1 = the fingerprint tempelete 
	//fp2 = the fingerprint to be matched
	virtual bool Matching(CFinPrint & fp1, CFinPrint & fp2);
protected:
	//calculate the similarity between two different fingerprints using the Jaccard similarity
	//set1 = the characteristic vector of the first fingerprint
	//set2 = the characteristic vector of the second fingerprint
	// threshold = the similarity threshold
	virtual bool Sim(std::vector<uchar> & set1, std::vector<uchar> & set2, float threshold = 0.8f);


	//obtain a col vector of the characteristic matrix
	// list = the feature point list
	virtual std::vector<uchar> GetCVector(std::vector<CFinPrint::FFP> & list);

	// obtain a col vector of the signal matrix
	//virtual std::vector<int> GetSVector(std::vector<uchar> cvec, std::vector<Hash> hs);

	//LSH lagorithm
	// cMat = the characteristic matrix
	virtual std::vector<int> LSH(std::vector<std::vector<uchar>> & cMat);

	//obtain the intersetion of two sets
	virtual std::vector<int> Intersect(std::vector<int> & set1, std::vector<int> & set2);

protected:
	FMesh m_mesh;//the mesh usd for matching
};
