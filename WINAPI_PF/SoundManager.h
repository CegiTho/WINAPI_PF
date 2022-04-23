#pragma once


using namespace FMOD;

class SoundManager
{
private:
	SoundManager();
	~SoundManager();

	System* soundSystem;
	map<string, Sound*> sounds;
	map<string, CHANNEL> keyAndChannel;
	map<CHANNEL, float> channelVolume;

	Channel* bgChannel;
	Channel* mainFXChannel;
	Channel* subFXChannel;

	static SoundManager* instance;

public:
	static SoundManager* Get()
	{
		return instance;
	}

	static void Create()
	{
		instance = new SoundManager();
	}
	
	static void Delete()
	{
		delete instance;
	}

	void Update();
	void Add(string key, string file, CHANNEL channel);
	void Add(string key, string file, CHANNEL channel,float volume);

	void Play(string key);
	void Play(string key, float volume);

	void Stop(string key);
	void Pause(string key);
	void Resume(string key);

	void SetVolume(string tag, float volume);

	map<CHANNEL, float> GetVolume() { return channelVolume; }
};


