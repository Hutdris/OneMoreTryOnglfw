#include "stdafx.h"
#include <iostream>
#include <istream>
#include <fstream>
#include <ostream>
#include <string>
#include <stack>
#include <ios>

const int DIMENSION = 3;
class Vertex {
public:
	int triangleID;
	float normal[DIMENSION];
	float point[DIMENSION];
};
/*
class Triangle {
	const int DIMENSION = 3;
	public:
		float normal[DIMENSION];
		float points[3][DIMENSION];

		float point1[DIMENSION];
		float point2[DIMENSION];
		float point3[DIMENSION];
};
*/

void main()
{
	std::ifstream stlFile;
	stlFile.open("test.stl");
	if (!stlFile) // check if file can be found
	{
		std::cout << "STL file not found.";
		exit(1);
	}


	std::string ignore;
	stlFile >> ignore >> ignore; //ignore header: solid t=x.xx
	std::string endcase = ignore;
	int index = 0;
	int iIndex = 0;
	int triangleIndex = 0;
	int indexTmp = 0;
	std::stack<Vertex> vertexs;

	while (1)
	{
		stlFile >> ignore >> ignore; // ignore "normal"
		if (ignore == endcase)
			break;

		float normal[3];

		stlFile >> normal[0] >> normal[1] >> normal[2]; // read and save the face normal
		stlFile >> ignore >> ignore; // ignore "outer loop"
		for (int i = 0; i <= 2; ++i) // read the three vertices of a face
		{
			Vertex vertexTmp;
			vertexTmp.normal[0] = normal[0]; vertexTmp.normal[1] = normal[1]; vertexTmp.normal[2] = normal[2];
			stlFile >> ignore >> vertexTmp.point[0] >> vertexTmp.point[1] >> vertexTmp.point[2];// >> ignore >> ignore;  
			vertexTmp.triangleID = triangleIndex;
			vertexs.push(vertexTmp);
		}
		stlFile >> ignore >> ignore; // endloop // endfacet
		triangleIndex++;
	}

	stlFile.close();
	while (!vertexs.empty()) std::cout << vertexs.top().normal<<' '<< vertexs.top().point;
	vertexs.pop();
}