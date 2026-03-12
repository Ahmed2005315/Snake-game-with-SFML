#include "Asset_Manager.h"
#include<iostream>
Engine::Asset_Manager::Asset_Manager() {}
Engine::Asset_Manager::~Asset_Manager(){}

void Engine::Asset_Manager::AddTexture(int id, const string& filePath, bool wantRepeat) {
	auto texture = make_unique<sf::Texture>();
	if (!texture->loadFromFile(filePath)) {
		cout << "Failed " << filePath << endl;
		throw runtime_error("Failed to load texture: " + filePath);
	}

	texture->setRepeated(wantRepeat);
	m_Textures[id] = move(texture);
}
void Engine::Asset_Manager::AddFont(int id, const string& filePath) {
	auto font = make_unique<sf::Font>();
	if (!font->openFromFile(filePath)) {
		cout << "Failed " << filePath << endl;
		throw runtime_error("Failed to load font: " + filePath);
	}

	m_Fonts[id] = move(font);
}
//.at(id)	-> if id not found throw exception'GOOD', return reference to unique_ptr
//.get()	->	Extracts the raw pointer  Type: sf::Texture*
//*(...at(id).get())	-> convert  sf::Texture* to sf::Texture& 

const sf::Texture& Engine::Asset_Manager::GetTexture(int id)const {
	auto it = m_Textures.find(id);

	if (it == m_Textures.end()) {
		cout << "Texture ID not found: " << id << endl;
		throw runtime_error("Texture ID not found: " + to_string(id));
	}

	return *(it->second);
}
const sf::Font& Engine::Asset_Manager::GetFont(int id)const {
	auto it = m_Fonts.find(id);

	if (it == m_Fonts.end()) {
		cout << "Font ID not found: " << id<<endl;
		throw runtime_error("Font ID not found: " + to_string(id));
	}

	return *(it->second);
}
