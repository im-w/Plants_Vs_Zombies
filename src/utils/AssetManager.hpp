#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "../game/Animation.hpp"

class AssetManager
{
public:
    void LoadTexture(std::string name, std::string fileName);
    void LoadAnimation(std::string name, std::string fileName, int each_frame_x_size, int each_frame_y_size, int total_frame_number, int frame_time_in_ms, bool isLoop);
    sf::Texture &GetTexture(std::string name);
    Animation &GetAnimation(std::string name);

private:
    std::map<std::string, sf::Texture> m_textures;
    std::map<std::string, Animation> m_animations;
};

#endif // ASSETMANAGER_H
