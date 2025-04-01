#include <SFML/Graphics.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main()
{
	std::string path;
	std::cout << "path to images: ";
	std::cin >> path;

	int r, g, b, a;
	std::cout << "r g b a (0-255): ";
	std::cin >> r >> g >> b >> a;
	sf::Color background(r, g, b, a);

	sf::Image base, temp;

	bool first = true;
	size_t count = 0;
	fs::directory_iterator dir(path);
	for (fs::directory_entry e : dir)
	{
		if (!e.is_directory())
		{
			temp.loadFromFile(e.path().string());

			if (first)
			{
				first = false;
				base.create(temp.getSize().x, temp.getSize().y, sf::Color(0));
			}

			count++;
			for (int x = 0; x < base.getSize().x; x++)
				for (int y = 0; y < base.getSize().y; y++)
					if (temp.getPixel(x, y) != background && !base.getPixel(x, y).toInteger())
						base.setPixel(x, y, sf::Color(count));
		}

	}
	base.saveToFile(path + "/steps.png");

	return 0;
}