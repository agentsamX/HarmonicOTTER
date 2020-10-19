#include "..\include\Mesh.h"
#include <fstream>
#include <iostream>

syre::Mesh::Mesh(std::string fileName)
{
	if (fileName.substr(fileName.size() - 4, 4) == ".obj")
	{
		std::ifstream objToLoad;
		std::string curLine;
		objToLoad.open(fileName,std::ios::in);
		if (objToLoad)
		{
			while (std::getline(objToLoad, curLine))
			{
				if (curLine.at(0) == 'v')
				{
					switch (curLine.at(1))
					{
					case ' ':
						printf("found vertex line\n");
						vertices.push_back(Vector3Parser(curLine, 2));
						break;
					case 't':
						printf("found uv coord line\n");
						vertUVs.push_back(Vector2Parser(curLine, 3));
						break;
					case 'n':
						printf("found normal line\n");
						vertNormals.push_back(Vector3Parser(curLine, 3));
						break;
					}
				}
				else if (curLine.at(0) == 'f')
				{
					printf("found face line\n");
					FaceLineProcessor(curLine);
				}
			}
		}
		else
		{
			printf("file could not be opened");
		}

	}
	else
	{
		printf("not an obj");
	}

}

glm::vec3 syre::Mesh::Vector3Parser(std::string line, int offset)
{
	std::string xCoord;
	std::string yCoord;
	std::string zCoord;
	int coordNum = 0;
	for (int i = offset; i < line.size(); i++)
	{
		if (line[i] == ' ')
		{
			coordNum++;
		}
		else
		{
			switch (coordNum)
			{
			case 0:
				xCoord += line[i];
				break;
			case 1:
				yCoord += line[i];
				break;
			case 2:
				zCoord += line[i];
				break;
			}
		}
	}
	std::cout << xCoord << std::endl << yCoord << std::endl << zCoord << std::endl;
	return glm::vec3(std::stof(xCoord),std::stof(yCoord),std::stof(zCoord));
}

glm::vec2 syre::Mesh::Vector2Parser(std::string line, int offset)
{
	std::string xCoord;
	std::string yCoord;
	int coordNum = 0;
	for (int i = offset; i < line.size(); i++)
	{
		if (line[i] == ' ')
		{
			coordNum++;
		}
		else
		{
			switch (coordNum)
			{
			case 0:
				xCoord += line[i];
				break;
			case 1:
				yCoord += line[i];
				break;
			}
		}
	}
	std::cout << xCoord << std::endl << yCoord << std::endl;
	return glm::vec2(std::stof(xCoord), std::stof(yCoord));
}

void syre::Mesh::FaceLineProcessor(std::string line)
{
	int vertCounter=0;
	std::string vertHolder;
	bool reading = false;
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] == ' ')
		{
			vertCounter++;
		}
	}
	if (vertCounter == 3)
	{
		for (int i = 0; i < line.size(); i++)
		{
			if (reading)
			{
				if (line[i] == '/')
				{
					reading = false;

					indexedVertices.push_back(std::stoi(vertHolder));
					std::cout << vertHolder;
					vertHolder = "";
				}
				else
				{
					vertHolder += line[i];
				}
			}
			else if (line[i] == ' ')
			{
				reading = true;
			}
		}
	}
	else if (vertCounter == 4)
	{
		int verts[4];
		int j = 0;
		for (int i = 0; i < line.size(); i++)
		{
			if (reading)
			{
				if (line[i] == '/')
				{
					reading = false;

					verts[j]=std::stoi(vertHolder);
					j++;
					std::cout << vertHolder;
					vertHolder = "";
				}
				else
				{
					vertHolder += line[i];
				}
			}
			else if (line[i] == ' ')
			{
				reading = true;
			}
		}
		indexedVertices.push_back(verts[0]);
		indexedVertices.push_back(verts[1]);
		indexedVertices.push_back(verts[2]);
		indexedVertices.push_back(verts[0]);
		indexedVertices.push_back(verts[2]);
		indexedVertices.push_back(verts[3]);
	}
}
