#include "AssetManager.h"

AssetManager* AssetManager::m_instance = nullptr;

void AssetManager::LoadTexture(std::string textureName, std::string fileName)
{
    sf::Texture texture;

    if(texture.loadFromFile(fileName))
    {
        m_textures[textureName] = texture;
    }
}

sf::Texture &AssetManager::GetTexture(std::string textureName)
{
    return m_textures.at(textureName);
}

void AssetManager::LoadFont(std::string fontName, std::string fileName)
{
    sf::Font font;

    if(font.loadFromFile(fileName))
    {
        m_fonts[fontName] = font;
    }
}

sf::Font &AssetManager::GetFont(std::string fontName)
{
    return m_fonts.at(fontName);
}

AssetManager *AssetManager::GetInstance()
{
    if(m_instance == nullptr)
    {
        m_instance = new AssetManager();
    }
    return m_instance;
}
