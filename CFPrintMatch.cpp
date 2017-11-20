#include"CFPrintMatch.h"

//matching function(one to one)
bool CFPrintMatch::Matching(CFinPrint & fp1, CFinPrint & fp2)
{
	//obtain the feature point lists of the two fingerprints
	std::vector<CFinPrint::FFP> list1 = fp1.GetFList();
	std::vector<CFinPrint::FFP> list2 = fp2.GetFList();

	//otbain the corresponding col of the characteristic matrix
	std::vector<uchar> cvec1 = GetCVector(list1);
	std::vector<uchar> cvec2 = GetCVector(list2);
	
	return Sim(cvec1, cvec2);
}

//one mathes many
std::vector<int>  CFPrintMatch::Matching(CFinPrint & tfp, std::vector<CFinPrint> & fps)
{
	

	//create the characteristic matrix
	std::vector<std::vector<uchar>> cMat(fps.size()+1);
	cMat[0] = GetCVector(tfp.GetFList());
	for (int i = 1; i < cMat.size(); i++)
	{
		cMat[i] = GetCVector(fps[i-1].GetFList());
	}
	return LSH(cMat);
}

//protected funtions .......................................................................................

//similarity
bool CFPrintMatch::Sim(std::vector<uchar> & set1, std::vector<uchar> & set2, float threshold)
{
	int count = 0;//obtain the intersection
	for (int i = 0; i < set1.size(); i++)
	{
		if (set1[i] == set2[i])
			count++;
	}

	//calculate the Jaccard similarity
	float d = (float)count / (float)set1.size();

	return (d > threshold) ? true : false;
}

//obtain the corresponding col of a characteristic matrix
std::vector<uchar> CFPrintMatch::GetCVector(std::vector<CFinPrint::FFP> & list)
{
	int msize = m_mesh.rows*m_mesh.cols;//calculate how many grids in the mesh

	std::vector<uchar> svec(msize, 0);
	
	int gx = 0; //the row number of a grid
	int gy = 0; //the col number of a grid
	int gid = 0;//the index of a grid
	for (int i = 0; i < list.size(); i++)
	{
		//calculate which grid include a feature point 
		gx = list[i].x / m_mesh.gWidth;
		gy = list[i].y / m_mesh.gHeight;

		// set the grid to 1
		gid = gx + gy *m_mesh.cols; 
		svec[gid] = 1;
	}
	return svec;
}

//Intersection
std::vector<int> CFPrintMatch::Intersect(std::vector<int> & set1, std::vector<int> & set2)
{
	std::vector<int> is;
	for (int i = 0; i < set1.size(); i++)
	{
		for (int j = 0; j < set2.size(); j++)
		{
			if (set1[i] == set2[j])
			{
				is.push_back(set1[i]);
			}
		}
	}
	return is;
}

//LSH
std::vector<int> CFPrintMatch::LSH(std::vector<std::vector<uchar>> & cMat)
{
	//LSH
	std::vector< std::vector<int>> idMat(m_mesh.rows);
	std::vector<uchar> fband(m_mesh.cols); //the band of fingerprint to be match
	std::vector<uchar> tband(m_mesh.cols); //the band of fingerprint tempelete
	int pr = 0;

	for (int i = 0; i < m_mesh.rows; i++)//the ith hash operation
	{
		for (int j = 1; j < cMat.size(); j++)
		{
			
			for (int k = pr; k < pr + m_mesh.cols; k++)//obtain the bands
			{
				fband[k - pr] = cMat[j][k];
				tband[k - pr] = cMat[0][k];
			}

			if (Sim(fband, tband))// if the two bands are similar
			{
				idMat[i].push_back(j);//record the index of fingerprint in the fingerprint list
			}
		}// end hash
		pr += m_mesh.cols;// the next hash
	}

	//obtain the intersection of all results of hashes
	std::vector<int> ids = idMat[0];
	for (int i = 1; i < idMat.size(); i++)
	{
		ids = Intersect(idMat[i], ids);
	}
	return ids;
}

//获得签名矩阵列
//std::vector<int> CFPrintMatch::GetSVector(std::vector<uchar> cvec, std::vector<Hash> hs)
//{
//	std::vector<int> svec(hs.size(),INFINITE);//签名列
//
//	//
//	std::vector<std::vector<int>> hMat(cvec.size()); //建立哈希矩阵
//	//填充哈希矩阵
//	for (int i = 0; i < cvec.size(); i++)
//	{
//		for (int j = 0; j < hs.size(); j++)
//		{
//			hMat[i].push_back(hs[j](i));//对每行进行哈希
//		}
//	}
//
//	//最小哈希
//	for (int j = 0; j < cvec.size(); j++)//比较每个特征
//	{
//		for (int i = 0; i < hs.size(); i++)
//		{
//			if (cvec[j] == 1 && //有特征
//				svec[i] > hMat[j][i])
//			{
//				svec[i] = hMat[j][i];
//			}
//		}
//	}
//	return svec;
//}