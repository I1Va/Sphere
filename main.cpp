#include <SFML/Graphics.hpp>

const unsigned width = 640u, height = 480u;
    
int main()
{
    sf::RenderWindow window(sf::VideoMode({width, height}), "My window");

    std::vector<sf::Vertex> vertices(width * height);

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            vertices[i * width + j] = sf::Vertex{{i, j}, sf::Color(i + j, 0, 0)};
        }
    }

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(vertices.data(), vertices.size(), sf::PrimitiveType::Points);
        window.display();
    }
}