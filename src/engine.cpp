#include "engine.hpp"

Engine::Engine()
    : window(sf::VideoMode(1280, 720), "SFML")
    , eventManager(&window)
{
    window.setFramerateLimit(60);
    eventManager.addCallback(sf::Event::Closed, [&](const sf::Event&){ window.close(); });
}

Engine::~Engine()
{
    for (auto it = m_mapScenes.begin(); it != m_mapScenes.end(); ++it)
        delete it->second;
}

void Engine::run()
{
    create();

    while (window.isOpen())
    {
        window.clear();
        
        eventManager.processEvents();

        step();

        window.display();
    }

    end();
}

void Engine::createScene(System::Scenes scene)
{
    if (m_mapScenes.find(scene) == m_mapScenes.end())
    {
        Scene* newScene = new Scene(&window);
        m_mapScenes.insert(std::pair<System::Scenes, Scene*>(scene, newScene));
    }
}

void Engine::switchScene(System::Scenes scene)
{
    activeScene = scene;
}

void Engine::addElement(System::Scenes scene, Element* element)
{
    if (m_mapScenes.find(scene) != m_mapScenes.end()) // Check if scene exists
    {
        m_mapScenes[scene]->addElement(element);
    }
}

void Engine::renderScene(System::Scenes scene)
{
    if (m_mapScenes.find(scene) != m_mapScenes.end()) // Check if scene exists
        m_mapScenes[scene]->render();
}

void Engine::updateScene(System::Scenes scene)
{
    if (m_mapScenes.find(scene) != m_mapScenes.end()) // Check if scene exists
        m_mapScenes[scene]->updateElements();
}

Scene* Engine::getScene(System::Scenes scene)
{
    if (m_mapScenes.find(scene) != m_mapScenes.end()) // Check if scene exists
        return m_mapScenes[scene];

    return nullptr;
}
