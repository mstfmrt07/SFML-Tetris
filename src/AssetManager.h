#pragma once
#include <SFML/Graphics.hpp>
#include <map>

class AssetManager
{
public:
    AssetManager() = default;
    ~AssetManager() = default;

    void LoadTexture(std::string textureName, std::string fileName);
    sf::Texture &GetTexture(std::string textureName);

    void LoadFont(std::string textureName, std::string fileName);
    sf::Font &GetFont(std::string fontName);

private:
    std::map<std::string, sf::Texture> m_textures;
    std::map<std::string, sf::Font> m_fonts;
};