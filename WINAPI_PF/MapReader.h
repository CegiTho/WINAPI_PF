#pragma once

class MapReader
{
private:
	MapReader();
	~MapReader();

	vector<T_Object*> obj;


public:
	MapReader* Get()
	{
		static MapReader instance;
		return &instance;
	}


};

