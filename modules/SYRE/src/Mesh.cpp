#include <fstream>
#include <iostream>
#include "Mesh.h"

syre::Mesh::Mesh(std::string fileName)
{
	std::vector<unsigned int> indexedVertices;
	std::vector<float> vertAsFloat;
	std::vector<glm::vec2> vertUVs;
	std::vector<glm::vec3> vertNormals;

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
						//printf("found vertex line\n");
						glm::vec3 temp = Vector3Parser(curLine, 2);
						vertAsFloat.push_back(temp.x);
						vertAsFloat.push_back(temp.y);
						vertAsFloat.push_back(temp.z);
						break;
					case 't':
						//printf("found uv coord line\n");
						vertUVs.push_back(Vector2Parser(curLine, 3));
						break;
					case 'n':
						//printf("found normal line\n");
						vertNormals.push_back(Vector3Parser(curLine, 3));
						break;
					}
				}
				else if (curLine.at(0) == 'f')
				{
					//printf("found face line\n");
					FaceLineProcessor(curLine,indexedVertices);
				}
			}
			//Fill Vertex arrays up here
			//vbo = VertexBuffer::Create();
			vbo->LoadData(vertAsFloat.data(), vertAsFloat.size());
			vbo->Bind();
			//ibo = IndexBuffer::Create();
			ibo->LoadData(indexedVertices.data(), sizeof(int), indexedVertices.size(), GL_UNSIGNED_INT);
			//vao = VertexArrayObject::Create();
			vao->AddVertexBuffer(vbo, {
				BufferAttribute(0, 3, GL_FLOAT, false, 0, NULL)
				});
			vao->SetIndexBuffer(ibo);
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
	//std::cout << xCoord << std::endl << yCoord << std::endl << zCoord << std::endl;


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
	//std::cout << xCoord << std::endl << yCoord << std::endl;
	return glm::vec2(std::stof(xCoord), std::stof(yCoord));
}

void syre::Mesh::FaceLineProcessor(std::string line, std::vector<unsigned int> indexVec)
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

					indexVec.push_back(unsigned int(std::stoi(vertHolder)-1));
					//std::cout << vertHolder;
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
					//std::cout << vertHolder;
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
		indexVec.push_back(verts[0]);
		indexVec.push_back(verts[1]);
		indexVec.push_back(verts[2]);
		indexVec.push_back(verts[0]);
		indexVec.push_back(verts[2]);
		indexVec.push_back(verts[3]);
	}
	std::cout << std::endl;
}

void syre::Mesh::Render()
{
	vao->Render();
}



