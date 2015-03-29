
#ifndef TIMELINE_H
#define TIMELINE_H


#include <set>
#include <string>
#include "TimelineKey.h"

class Timeline
{
public:
	
	Timeline();
	
	void Load(const std::string& file);
	void Update();


private:

	std::multiset<TimelineKey*> keys;

	float time;

	std::multiset<TimelineKey*>::iterator lastKey;
};

#endif //TIMELINE_H