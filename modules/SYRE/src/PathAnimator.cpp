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
        if (points.size() > 5 && points.size() % 3 == 0)
        {
            int curSeg = currentIndex / 3;
            if (maxSegment <= curSeg&&maxSegment!=0)
                return;
            distTravelled += delta*speed;
            //printf("CurSeg: %i\n", curSeg);
            //printf("CurDistance : %f\n", distTravelled);
            float t = 0.0f;
            for (int i = 0; i <= samplesPerSeg; ++i)
            {
                if (bezierTable[curSeg][i].y > distTravelled)
                {
                    if (i == 0)
                    {
                        t = 0.0f;
                        break;
                    }
                    float tSample = InvLerp(bezierTable[curSeg][i - 1].y, bezierTable[curSeg][i].y, distTravelled);
                    t = glm::mix(bezierTable[curSeg][i - 1].x, bezierTable[curSeg][i].x, tSample);
                    if (t <= lastT)
                    {
                        t = lastT;
                    }
                    break;
                }
                else if (bezierTable[curSeg][i].y == distTravelled)
                {
                    t = bezierTable[curSeg][i].x;
                    break;
                }
                else
                {
                    t = 1.0f;
                }
            }

            curTrans.SetPosition(Bezier(points[currentIndex][0], points[handleIndex1][0], points[handleIndex2][0], points[nextIndex][0], t));
            curTrans.SetRotQuat(glm::slerp(glm::quat(glm::radians(points[currentIndex][1])), glm::quat(glm::radians(points[nextIndex][1])), t));
            //printf("t value: %f\n", t);

            if (t >= 1.f)
            {
                currentIndex += 3;
                nextIndex += 3;
                handleIndex1 += 3;
                handleIndex2 += 3;
                lastT = 0.0f;
                t = 0.f;

                if (nextIndex >= points.size())
                {
                    currentIndex = 0;
                    handleIndex1 = 1;
                    handleIndex2 = 2;
                    nextIndex = 3;
                    if (!looping)
                    {
                        isPlay = false;
                        hardStop = true;
                    }
                    else
                    {
                        distTravelled = 0.0f;
                    }
                }
             
            }

        }
    }
}

bool syre::PathAnimator::HitMax()
{
    int curSeg = currentIndex / 3;
    return maxSegment <= curSeg && maxSegment != 0;
}

void syre::PathAnimator::SpeedControl()
{
    for (int i = 0; i < points.size()-3; i += 3)
    {
        std::vector<glm::vec2> samples;
        float distTotal = 0.0f;
        for (float t = 0.0f; t <= 1.01f; t += 1.0f / samplesPerSeg)
        {
            if (t == 0.0f)
            {
                if (i != 0)
                  distTotal = bezierTable.back().back().y;
            }
            else
            {
                distTotal =samples.back().y+glm::distance(Bezier(points[i][0], points[i + 1][0], points[i + 2][0], points[i + 3][0],t), Bezier(points[i][0], points[i + 1][0], points[i + 2][0], points[i + 3][0], t+1.0f/samplesPerSeg));
            }
            samples.push_back(glm::vec2(t, distTotal));
        }
        //for (int j = 0; j <= samplesPerSeg; ++j)
        //{
        //    printf("t val : %f, dist : %f\n", samples[j].x, samples[j].y);
        //    //prints values of the speed control table
        //}
        
        bezierTable.push_back(samples);
    }
}

void syre::PathAnimator::Stop()
{
    isPlay = false;
}

void syre::PathAnimator::Resume()
{
    if(!hardStop)
        isPlay = true;
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

void syre::PathAnimator::SetMaxSegment(int newSegemt)
{
    maxSegment += newSegemt;
}

void syre::PathAnimator::IncrementSegment(int inc)
{
    if(maxSegment<points.size()/3)
        maxSegment += inc;
  
}

void syre::PathAnimator::SetSpeed(int newSpeed, bool dir)
{
    if (dir == true)
    {
        if (speed + newSpeed <= 45.f)
        {
            speed += newSpeed;
        }
    }
    if (dir == false)
    {
        if (speed - newSpeed >= 35.f)
        {
            speed -= newSpeed;
        }
    }
}

float syre::PathAnimator::InvLerp(float start, float end, float cur)
{
    return abs(cur - start) / abs(end - start);
}


