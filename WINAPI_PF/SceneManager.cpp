#include "Framework.h"

SceneManager* SceneManager::instance = nullptr;

SceneManager::SceneManager()
    :curScene(nullptr)
{
}

SceneManager::~SceneManager()
{
    for (auto scene : scenes)
        delete scene.second;
}

void SceneManager::Update()
{
    if (curScene == nullptr)
        return;

    curScene->Update();
}

void SceneManager::Render(HDC hdc)
{
    if (curScene == nullptr)
        return;

    curScene->Render(hdc);
}

Scene* SceneManager::Add(string key, Scene* scene)
{
    if (scenes.count(key) > 0)
        return scenes[key];

    scenes[key] = scene;
    if (key.find("Stage") != string::npos)
        stageSeq.emplace_back(key);

    return scene;
}

void SceneManager::ChangeScene(string key)
{
    if (scenes.count(key) == 0)
        return;

    if (scenes[key] == curScene)
        return;

    sceneSeq.push(scenes[key]);

    curScene->End();
}

void SceneManager::SetScene(string key)
{
    if (scenes.count(key) == 0)
        return;

    if (scenes[key] == curScene)
        return;

    curScene = scenes[key];
    curScene->Start();
}

void SceneManager::DequeueScene()
{
    if (sceneSeq.empty() == true)
        return;

    curScene = sceneSeq.front();
    curScene->Start();
    sceneSeq.pop();
}
