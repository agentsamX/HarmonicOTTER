#include "PathAnimator.h"

syre::PathAnimator::PathAnimator(PathType initType)
{
	pathType = initType;
    Reset();
}

syre::PathAnimator::PathAnimator(PathType initType, bool speedCont)
{
}

syre::PathAnimator::PathAnimator(PathType initType, bool speedCont, glm::vec3 startPoint)
{
}

void syre::PathAnimator::AddPoint(glm::vec3 pos, glm::vec3 rot)
{
	points.push_back(glm::mat2x3(pos, rot));
}

void syre::PathAnimator::AddPoint(std::vector<glm::vec3>& pos, std::vector<glm::vec3>& rot)
{
	for (int i = 0; i < pos.size(); i++)
	{
		points.push_back(glm::mat2x3(pos[i], rot[i]));
	}
}

void syre::PathAnimator::Update(Transform* curTrans, float delta)
{
}

void syre::PathAnimator::Reset()
{
    if (pathType == PathType::LERP)
    {
        currentIndex = 0;
        nextIndex = 1;
    }
    else if (pathType == PathType::CATMULL)
    {
        handleIndex1 = 0;
        currentIndex = 1;
        nextIndex = 2;
        handleIndex2 = 3;
    }
    else if (pathType== PathType::BEZIER)
    {
        currentIndex = 0;
        handleIndex1 = 1;
        handleIndex2 = 2;
        nextIndex = 3;
    }
}
