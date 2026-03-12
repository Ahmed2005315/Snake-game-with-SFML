#pragma once
#include<memory>
#include<string>
#include<map>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

using namespace std;

namespace Engine {
	class Asset_Manager
	{
	private:
		map<int, unique_ptr<sf::Texture>>m_Textures;
		map<int, unique_ptr<sf::Font>>m_Fonts;
	public:
		Asset_Manager();
		~Asset_Manager();
		void AddTexture(int id, const string& filePath, bool wantRepeat=false);
		void AddFont(int id, const string& filePath);
		const sf::Texture& GetTexture(int id)const;
		const sf::Font& GetFont(int id)const;
	};
}

