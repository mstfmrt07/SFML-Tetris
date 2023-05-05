#pragma once
#include <SFML/Graphics.hpp>
#include <map>

class AssetManager
{
public:
    AssetManager(AssetManager &other) = delete;
    void operator=(const AssetManager &) = delete;
    static AssetManager* GetInstance();

    void LoadTexture(std::string textureName, std::string fileName);
    sf::Texture &GetTexture(std::string textureName);

    void LoadFont(std::string textureName, std::string fileName);
    sf::Font &GetFont(std::string fontName);

private:
    AssetManager() = default;
    ~AssetManager() = default;

    static AssetManager* m_instance;
    std::map<std::string, sf::Texture> m_textures;
    std::map<std::string, sf::Font> m_fonts;
};