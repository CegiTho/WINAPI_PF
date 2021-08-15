#pragma once

#define MAXCHANNEL 2		//배경채널,이펙트채널

using namespace FMOD;

class SoundManager
{
private:
	SoundManager();
	~SoundManager();

	System* soundSystem;
	map<string, Sound*> sounds;
	
	Channel* bgChannel;
	Channel* fxChannel;

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
	void Add(string key, string file, bool bgm = false);

	void Play(string key, bool bgm = false);
	void Play(string key, float volume, bool bgm = false);
	void Play(string key, float volume, float frequencyRate, bool bgm = false);

	void Stop(bool bgm);
	void Pause(bool bgm);
	void Resume(bool bgm);

	void SetBGMVolume(float volume);
	void SetFXVolume(float volume);

};


