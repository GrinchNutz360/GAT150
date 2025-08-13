#include "Font.h"
#include "Core/Logger.h"



/// <summary>
/// Destroys a Font object and releases associated resources.
/// </summary>
viper::Font::~Font() {
	if (m_ttfFont != nullptr) {
		TTF_CloseFont(m_ttfFont);
	}
}
/// <summary>
/// Loads a font from a file with the specified size.
/// </summary>
/// <param name="name">The path to the font file to load.</param>
/// <param name="fontSize">The desired size of the font.</param>
/// <returns>True if the font was loaded successfully; false otherwise.</returns>
bool viper::Font::Load(const std::string& name, float fontSize) {
	m_ttfFont = TTF_OpenFont(name.c_str(), fontSize);
	if (m_ttfFont == nullptr) {
		Logger::Error("Could not load font: {} - {}", name, SDL_GetError());
		return false;
	}

	return true;
}