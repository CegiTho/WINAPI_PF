#include "Framework.h"

SoundManager* SoundManager::instance = nullptr;

SoundManager::SoundManager()
{
	System_Create(&soundSystem);
	soundSystem->init(MAXCHANNEL, FMOD_INIT_NORMAL, nullptr);
	//channel�� Play�޼����� playSound�Լ����� �����ȴ�.
	//���� �� �������� channel�� SetVolume�� �ص� �ҿ� ����.
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
		//����� ���ѷ���,��������� ��������Ǵ� ��� ���� -> ���� createStream���� ����
	}
	else
	{
		soundSystem->createSound(file.c_str(), FMOD_DEFAULT, nullptr, &sound);
		//ȿ������ ��ø����ϴ� ��� ����
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

//channel ����Ÿ�̹��� play�޼����� playSound�Լ� ������.
//���� �� ������ Set~Volume ȣ���غ��� �ǹ̾���.
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
