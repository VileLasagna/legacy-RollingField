
#ifndef TIMELINE_KEY_H
#define TIMELINE_KEY_H


class TimelineKey
{

	TimelineKey(){}
	TimelineKey(float T)
	{
		time = T;
	}
	virtual void Trigger() = 0;

	bool operator< (const TimelineKey& other)
	{
		return time<other.time;
	}

	float getTime()
	{
		return time;
	}

private:

	float time;
};

#endif //TIMELINE_KEY_H