#pragma once
#include "Transform.h"
#include <vector>

namespace syre
{
	enum class PathType
	{
		LERP,
		BEZIER,
		CATMULL
	};
	class PathAnimator
	{
	public:
		PathAnimator(PathType initType);
		PathAnimator(PathType initType, bool speedCont);
		PathAnimator(PathType initType, bool speedCont,glm::vec3 startPoint);
		void AddPoint(glm::vec3 pos, glm::vec3 rot);
		void AddPoint(std::vector<glm::vec3>& pos, std::vector<glm::vec3>& rot);
		void Update(Transform& curTrans, float delta);
		void SpeedControl();
		void Reset();
	private:
		PathType pathType;
		float InvLerp(float start, float end, float cur);
		bool speedControl = true;
		bool absolutePos = true;
		std::vector<glm::mat2x3> points;
		glm::vec3 startPoint;
		std::vector<std::vector<glm::vec2>> bezierTable;//t value is x, total distance is z
		bool isPlay = true;
		float distTravelled = 0.f;
		int samplesPerSeg = 10;
		int currentIndex = 0;
		int handleIndex1 = 1;
		int handleIndex2 = 2;
		int nextIndex = 1;
		int stopPoint;
		int maxSegment = 0;//putting 0 does not limit the segment
	};
}

static inline glm::vec3 Bezier(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, float t)
{
	return glm::mix(glm::mix(glm::mix(p0, p1, t), glm::mix(p1, p2, t), t), glm::mix(glm::mix(p1, p2, t), glm::mix(p2, p3, t), t), t);
}