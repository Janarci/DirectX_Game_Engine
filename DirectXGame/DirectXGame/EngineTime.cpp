#include "EngineTime.h"
EngineTime* EngineTime::sharedInstance = NULL;

void EngineTime::initialize()
{
	sharedInstance = new EngineTime();
}

double EngineTime::getDeltaTime()
{
	return sharedInstance->deltaTime;
}

double EngineTime::getAngle()
{
	if (sharedInstance->Angle > 15.0f)
	{
		sharedInstance->max = true;

	}
	else if (sharedInstance->Angle < 0.0f)
	{
		sharedInstance->max = false;

	}

	if (!sharedInstance->max)
	{
		sharedInstance->Angle = sharedInstance->Angle + sharedInstance->deltaTime;

	}
	else
	{
		sharedInstance->Angle = sharedInstance->Angle - sharedInstance->deltaTime;

	}

	return sharedInstance->Angle;
}

EngineTime::EngineTime()
{
}

EngineTime::~EngineTime()
{
}

void EngineTime::LogFrameStart()
{
	sharedInstance->start = std::chrono::system_clock::now();
}

void EngineTime::LogFrameEnd()
{
	sharedInstance->end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = sharedInstance->end - sharedInstance->start;

	sharedInstance->deltaTime = elapsed_seconds.count();





}
