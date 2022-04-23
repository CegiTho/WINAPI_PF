#include "Framework.h"

SoundManager* SoundManager::instance = nullptr;

SoundManager::SoundManager()
{
	System_Create(&soundSystem);
	soundSystem->init(CHANNEL_COUNT, FMOD_INIT_NORMAL, nullptr);

	//channel은 Play메서드의 playSound함수에서 지정된다.
	//따라서 그 이전에는 channel에 SetVolume을 해도 소용 없음.
	//bgChannel->setVolume(1.0f);
	//fxChannel->setVolume(1.0f);
	channelVolume[MAIN_FX_CHANNEL] = 0.0f;
	channelVolume[SUB_FX_CHANNEL] = 0.0f;
	channelVolume[BG_CHANNEL] = 0.0f;
}

SoundManager::~SoundManager()
{
	for (auto sound : sounds)
		sound.second->release();

	soundSystem->release();
	soundSystem->close();
}

void SoundManager::Update()
{
	soundSystem->update();
}

void SoundManager::Add(string key, string file, CHANNEL channel)
{
	Sound* sound = nullptr;

	switch (channel)
	{
	case MAIN_FX_CHANNEL:
		soundSystem->createSound(file.c_str(), FMOD_DEFAULT, nullptr, &sound);
		keyAndChannel[key] = channel;
		channelVolume[channel] = 0.0f;
		break;
	case SUB_FX_CHANNEL:
		soundSystem->createSound(file.c_str(), FMOD_DEFAULT, nullptr, &sound);
		keyAndChannel[key] = channel;
		channelVolume[channel] = 0.0f;
		break;
	case BG_CHANNEL:
		soundSystem->createStream(file.c_str(), FMOD_LOOP_NORMAL, nullptr, &sound);
		keyAndChannel[key] = channel;
		channelVolume[channel] = 0.0f;
		//배경은 무한루프,배경음끼리 겹쳐재생되는 경우 없음 -> 따라서 createStream으로 만듬
		break;
	}

	sounds[key] = sound;
}

void SoundManager::Add(string key, string file, CHANNEL channel, float volume)
{
	Sound* sound = nullptr;

	switch (channel)
	{
	case MAIN_FX_CHANNEL:
		soundSystem->createSound(file.c_str(), FMOD_DEFAULT, nullptr, &sound);
		keyAndChannel[key] = channel;
		channelVolume[channel] = volume;
		break;
	case SUB_FX_CHANNEL:
		soundSystem->createSound(file.c_str(), FMOD_DEFAULT, nullptr, &sound);
		keyAndChannel[key] = channel;
		channelVolume[channel] = volume;		
		break;
	case BG_CHANNEL:
		soundSystem->createStream(file.c_str(), FMOD_LOOP_NORMAL, nullptr, &sound);
		keyAndChannel[key] = channel;
		channelVolume[channel] = volume;		//배경은 무한루프,배경음끼리 겹쳐재생되는 경우 없음 -> 따라서 createStream으로 만듬
		break;
	}

	sounds[key] = sound;
}

void SoundManager::Play(string key)
{
	if (sounds.find(key) == sounds.end())
		return;

	//Stop(key);
	switch (keyAndChannel[key])
	{
	case MAIN_FX_CHANNEL:
		soundSystem->playSound(sounds[key], nullptr, true, &mainFXChannel);
		mainFXChannel->setVolume(channelVolume[MAIN_FX_CHANNEL]);
		mainFXChannel->setPaused(false);
		break;
	case SUB_FX_CHANNEL:
		soundSystem->playSound(sounds[key], nullptr, true, &subFXChannel);
		subFXChannel->setVolume(channelVolume[SUB_FX_CHANNEL]);
		subFXChannel->setPaused(false);
		break;
	case BG_CHANNEL:
		soundSystem->playSound(sounds[key], nullptr, true, &bgChannel);
		bgChannel->setVolume(channelVolume[BG_CHANNEL]);
		bgChannel->setPaused(false);
		bgChannel->setPriority(0);
		break;
	}

}

void SoundManager::Play(string key, float volume)
{
	if (sounds.find(key) == sounds.end())
		return;

	//Stop(key);
	switch (keyAndChannel[key])
	{
	case MAIN_FX_CHANNEL:
		soundSystem->playSound(sounds[key], nullptr, true, &mainFXChannel);
		channelVolume[MAIN_FX_CHANNEL] = volume;
		mainFXChannel->setVolume(channelVolume[MAIN_FX_CHANNEL]);
		mainFXChannel->setPaused(false);
		break;
	case SUB_FX_CHANNEL:
		soundSystem->playSound(sounds[key], nullptr, true, &subFXChannel);
		channelVolume[SUB_FX_CHANNEL] = volume;
		subFXChannel->setVolume(channelVolume[SUB_FX_CHANNEL]);
		subFXChannel->setPaused(false);
		break;
	case BG_CHANNEL:
 		soundSystem->playSound(sounds[key], nullptr, true, &bgChannel);
		channelVolume[BG_CHANNEL] = volume;
		bgChannel->setVolume(channelVolume[BG_CHANNEL]);
		bgChannel->setPaused(false);
		bgChannel->setPriority(0);
		break;
	}
}


void SoundManager::Stop(string key)
{
	if (sounds.find(key) == sounds.end())
		return;

	switch (keyAndChannel[key])
	{
	case MAIN_FX_CHANNEL:
		mainFXChannel->stop();
		break;
	case SUB_FX_CHANNEL:
		subFXChannel->stop();
		break;
	case BG_CHANNEL:
		bgChannel->stop();
		break;
	}
}

void SoundManager::Pause(string key)
{
	if (keyAndChannel.find(key) == keyAndChannel.end())
		return;

	switch (keyAndChannel[key])
	{
	case MAIN_FX_CHANNEL:
		mainFXChannel->setPaused(true);
		break;
	case SUB_FX_CHANNEL:
		subFXChannel->setPaused(true);
		break;
	case BG_CHANNEL:
		bgChannel->setPaused(true);
		break;

	}
}

void SoundManager::Resume(string key)
{
	if (keyAndChannel.find(key) == keyAndChannel.end())
		return;

	switch (keyAndChannel[key])
	{
	case MAIN_FX_CHANNEL:
		mainFXChannel->setPaused(false);
		break;
	case SUB_FX_CHANNEL:
		subFXChannel->setPaused(false);
		break;
	case BG_CHANNEL:
		bgChannel->setPaused(false);
		break;

	}
}

//channel 지정타이밍이 play함수의 playSound함수 이후임.
//따라서 그 이전엔 Set~Volume 호출해봐야 의미없음.
void SoundManager::SetVolume(string tag, float volume)
{
	float test;

	if (tag.find("FX") != string::npos)
	{//fxChannel
		channelVolume[MAIN_FX_CHANNEL] = volume;
		channelVolume[SUB_FX_CHANNEL] = volume;
	}
	else if (tag.find("Music Volume") != string::npos)
	{//bgChannel
		//BGM은 처음 bgChannel 지정된 다음 안바뀌니까 여기서 setVolume도 처리해야함.
		//FXChannel은 playSound호출될때마다 계속 바뀌기 때문에 여기서 setVolume호출해봐야 의미 없음.
		channelVolume[BG_CHANNEL] = volume;
		bgChannel->setVolume(volume);
	}

}
