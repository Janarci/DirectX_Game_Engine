#pragma once
#include <iostream>
#include <chrono>
#include <ctime>

class Window;

class EngineTime
{

public:
	static void initialize();
	static double getDeltaTime();
	static double getAngle();

private:

	EngineTime();

	EngineTime(EngineTime const&) {};
	EngineTime& operator=(EngineTime const&) {};

	~EngineTime();

	static EngineTime* sharedInstance;


	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;

	double deltaTime = 0.0f;
	double Angle = 0.0f;
	bool max = false;

	static void LogFrameStart();
	static void LogFrameEnd();


	friend class Window;


};

