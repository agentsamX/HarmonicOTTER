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

void syre::PathAnimator::Update(Transform& curTrans, float delta)
{

        if (points.size() > 5 && points.size() % 3 == 0)
        {
            float t = 0.0f;
            curTrans.SetPosition(Bezier(points[currentIndex][0],points[handleIndex1][0], points[handleIndex2][0], points[nextIndex][0], t));
            curTrans.SetRotQuat(glm::slerp(glm::quat(glm::radians(points[currentIndex][1])), glm::quat(glm::radians(points[nextIndex][1])), t));

            if (t >= 1.f)
            {
                currentIndex += 3;
                nextIndex += 3;
                handleIndex1 += 3;
                handleIndex2 += 3;
                t = 0.f;
              
              
                if (nextIndex >= points.size())
                {
                     currentIndex = 0;
                     handleIndex1 = 1;
                     handleIndex2 = 2;
                     nextIndex = 3;
                    // isPlay = false;
                }
               
            }

        }
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


