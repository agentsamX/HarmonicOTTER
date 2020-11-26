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
    if (isPlay)
    {
        distTravelled += delta / 10;

        if (points.size() > 5 && points.size() % 3 == 0)
        {
            int curSeg = currentIndex / 3;
            float t = 0.0f;
            for (float i = 0; i < samplesPerSeg; ++i)
            {
                if (bezierTable[curSeg][i].y > distTravelled)
                {
                    t = InvLerp(bezierTable[curSeg][i].x, bezierTable[curSeg][i - 1].x, distTravelled);
                    break;
                }
                else if (bezierTable[curSeg][i].y == distTravelled)
                {
                    t = bezierTable[curSeg][i].x;
                    break;
                }

            }

            curTrans.SetPosition(Bezier(points[currentIndex][0], points[handleIndex1][0], points[handleIndex2][0], points[nextIndex][0], t));
            curTrans.SetRotQuat(glm::slerp(glm::quat(glm::radians(points[currentIndex][1])), glm::quat(glm::radians(points[nextIndex][1])), t));

            if (t >= 1.f)
            {
                distTravelled = 0.0f;
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
                    isPlay = false;
                }

            }

        }
    }
}

void syre::PathAnimator::SpeedControl()
{
    for (int i = 0; i < points.size()-3; i += 3)
    {
        std::vector<glm::vec2> samples;
        float distTotal = 0.0f;
        for (float t = 0.0f; t <= 1.0f; t += 1.0f / samplesPerSeg)
        {
            if (t == 0.0f)
            {
                distTotal = 0.0f;
            }
            else
            {
                distTotal =samples.back().y+glm::distance(Bezier(points[i][0], points[i + 1][0], points[i + 2][0], points[i + 3][0],t), Bezier(points[i][0], points[i + 1][0], points[i + 2][0], points[i + 3][0], t+1.0f/samplesPerSeg));
            }
            samples.push_back(glm::vec2(t, distTotal));
        }
        bezierTable.push_back(samples);
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
    isPlay = true;
}

float syre::PathAnimator::InvLerp(float start, float end, float cur)
{
    return abs(cur - start) / abs(end - start);
}


