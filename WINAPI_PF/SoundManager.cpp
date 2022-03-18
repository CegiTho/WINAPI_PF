#include "Framework.h"

SoundManager* SoundManager::instance = nullptr;

SoundManager::SoundManager()
{
	System_Create(&soundSystem);
	soundSystem->init(MAXCHANNEL, FMOD_INIT_NORMAL, nullptr);
	//channel은 Play메서드의 playSound함수에서 지정된다.
	//따라서 그 이전에는 channel에 SetVolume을 해도 소용 없음.
	//bgChannel->setVolume(1.0f);
	//fxChannel->setVolume(1.0f);
}

SoundManager::~SoundManager()
{
	for (auto sound : sounds)
		sound.second->release();

	soundSystem->release();
}

void SoundManager::Update()
{
	soundSystem->update();
}

void SoundManager::Add(string key, string file, bool bgm)
{
	Sound* sound = nullptr;

	if (bgm == true)
	{
		soundSystem->createStream(file.c_str(), FMOD_LOOP_NORMAL, nullptr, &sound);
		//배경은 무한루프,배경음끼리 겹쳐재생되는 경우 없음 -> 따라서 createStream으로 만듬
	}
	else
	{
		soundSystem->createSound(file.c_str(), FMOD_DEFAULT, nullptr, &sound);
		//효과음은 중첩재생하는 경우 흔함
	}
	sounds[key] = sound;
}

void SoundManager::Play(string key, bool bgm)
{
	if (sounds.count(key) == 0)
		return;

	if (bgm == true)
	{
		Stop(true);
		soundSystem->playSound(sounds[key], nullptr, false, &bgChannel);
	}
	else
	{
		soundSystem->playSound(sounds[key], nullptr, false, &fxChannel);
	}
}

void SoundManager::Play(string key, float volume, bool bgm)
{
	if (sounds.count(key) == 0)
		return;

	if (bgm == true)
	{
		Stop(true);
		soundSystem->playSound(sounds[key], nullptr, false, &bgChannel);
		bgChannel->setVolume(volume);
	}
	else
	{
		soundSystem->playSound(sounds[key], nullptr, false, &fxChannel);
		fxChannel->setVolume(volume);
	}
}

void SoundManager::Play(string key, float volume, float frequencyRate, bool bgm)
{
	if (sounds.count(key) == 0)
		return;

	if (bgm == true)
	{
		Stop(true);
		soundSystem->playSound(sounds[key], nullptr, false, &bgChannel);
		bgChannel->setVolume(volume);
		float frequency;
		bgChannel->getFrequency(&frequency);
		bgChannel->setFrequency(frequency * frequencyRate);
	}
	else
	{
		soundSystem->playSound(sounds[key], nullptr, false, &fxChannel);
		fxChannel->setVolume(volume);
		float frequency;
		fxChannel->getFrequency(&frequency);
		fxChannel->setFrequency(frequency * frequencyRate);
	}
}

void SoundManager::Stop(bool bgm)
{
	if (bgm == true)
		bgChannel->stop();
	else
		fxChannel->stop();
}

void SoundManager::Pause(bool bgm)
{
	if (bgm == true)
		bgChannel->setPaused(true);
	else
		fxChannel->setPaused(true);
}

void SoundManager::Resume(bool bgm)
{
	if (bgm == true)
		bgChannel->setPaused(false);
	else
		fxChannel->setPaused(false);
}

//channel 지정타이밍이 play메서드의 playSound함수 이후임.
//따라서 그 이전엔 Set~Volume 호출해봐야 의미없음.
void SoundManager::SetBGMVolume(float volume)
{
	bgChannel->setVolume(volume);
}

void SoundManager::SetFXVolume(float volume)
{
	fxChannel->setVolume(volume);
}

void SoundManager::SetVolume(string tag, float volume)
{
	if (tag.find("FX") != string::npos)
		fxChannel->setVolume(volume);
	else if (tag.find("Music Volume") != string::npos)
		bgChannel->setVolume(volume);
}
