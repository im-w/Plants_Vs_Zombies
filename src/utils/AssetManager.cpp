#include "AssetManager.hpp"

void AssetManager::LoadTexture(std::string name, std::string fileName)
{
    if (m_textures.find(name) != m_textures.end())
    {
        return;
    }

    sf::Texture texture;

    if (texture.loadFromFile(fileName))
    {
        this->m_textures[name] = texture;
    }
}

void AssetManager::LoadAnimation(std::string name, std::string fileName, int each_frame_x_size, int each_frame_y_size, int total_frame_number, int frame_time_in_ms, bool isLoop)
{
    if (m_animations.find(name) != m_animations.end())
    {
        return;
    }

    sf::Texture texture;
    if (texture.loadFromFile(fileName))
    {
        Animation animation;
        animation.init(texture, each_frame_x_size, each_frame_y_size, total_frame_number, frame_time_in_ms, isLoop);
        this->m_animations[name] = animation;
    }
}

sf::Texture &AssetManager::GetTexture(std::string name)
{
    return this->m_textures.at(name);
}

Animation &AssetManager::GetAnimation(std::string name)
{
    return this->m_animations.at(name);
}
