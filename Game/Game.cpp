#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include <string.h>
#include <random>
#include <windows.h>
#include <cmath>

bool compareTreeY(const sf::Sprite& a, const sf::Sprite& b) {
    return a.getPosition().y < b.getPosition().y;
}

int main()
{
    sf::RenderWindow window;
    
    window.create(sf::VideoMode(1920, 1080), "Survarium");
    window.setPosition(sf::Vector2i(-10, 0));
    sf::Texture player_sprite_texture;
    sf::Texture tree_sprite_texture;
    sf::Texture rock_sprite_texture;
    player_sprite_texture.loadFromFile("./images/player_sprite.png");
    tree_sprite_texture.loadFromFile("./images/tree_sprite3.png");
    rock_sprite_texture.loadFromFile("./images/rock_sprite.png");
    sf::Sprite tree_sprite[1000];
    sf::Sprite rock_sprite[1000];
    sf::IntRect src_sprite(0, 0, 100, 74);
    sf::Sprite player_sprite(player_sprite_texture,src_sprite);
    player_sprite.setPosition(window.getSize().x / static_cast<float>(2), window.getSize().y / static_cast<float>(2));
    
    sf::SoundBuffer running_grass_buffer;
    running_grass_buffer.loadFromFile("./sounds/running_grass.ogg");
    sf::Sound running_grass;
    running_grass.setBuffer(running_grass_buffer);

    sf::SoundBuffer ambience_day_buffer;
    ambience_day_buffer.loadFromFile("./sounds/ambience_day.ogg");
    sf::Sound ambience_day;
    ambience_day.setBuffer(ambience_day_buffer);
    
    sf::SoundBuffer day_music_buffer;
    day_music_buffer.loadFromFile("./sounds/background_music1.ogg");
    sf::Sound day_music;
    day_music.setBuffer(day_music_buffer);
    
    //running_grass.setVolume(0.8);
    ambience_day.setVolume(5);
    day_music.setVolume(5);

    sf::Image image;
    image.loadFromFile("./images/cursor_inactive.png");
    sf::Cursor cursor;
    cursor.loadFromPixels(image.getPixelsPtr(), sf::Vector2u(image.getSize().x/10,image.getSize().y/10), { 0, 0 });
    window.setMouseCursor(cursor);

    sf::Clock clock;
    const float rectangleSpeed = 1.0f;
    const float rotationSpeed = 1.0f;

    sf::View view;
    view.setSize(1920, 1080);
    sf::Image background;
    background.loadFromFile("./images/background.png");
    sf::Texture texture;
    texture.loadFromImage(background);
    texture.setRepeated(true);
    sf::Sprite sprite;

    sf::Font font;
    font.loadFromFile("./font/kongtext.ttf");
    sf::Text coords;
    coords.setFont(font);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.05, 0.15);
    for (int i = 0; i < 1000; i++) {
        tree_sprite[i].setPosition(player_sprite.getPosition().x + (rand() % 100000), player_sprite.getPosition().y + (rand() % 100000));
        tree_sprite[i].setTexture(tree_sprite_texture);
        rock_sprite[i].setPosition(player_sprite.getPosition().x + (rand() % 100000), player_sprite.getPosition().y + (rand() % 100000));
        rock_sprite[i].setTexture(rock_sprite_texture);
        auto scale = dis(gen);
        tree_sprite[i].setScale(scale, scale);
        rock_sprite[i].setScale(scale, scale);
    }
    std::sort(tree_sprite, tree_sprite + 1000, compareTreeY);
    std::sort(rock_sprite, rock_sprite + 1000, compareTreeY);
    ambience_day.setLoop(true);
    ambience_day.play();
    day_music.setLoop(true);
    day_music.play();
    while (window.isOpen()) { 
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            running_grass.setLoop(true);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                if (running_grass.getStatus() != sf::Sound::Playing) {
                    running_grass.play();
                }
                src_sprite.top = 74;
                if (clock.getElapsedTime().asSeconds() > 0.15f) {
                    if (src_sprite.left == 500) {
                        src_sprite.left = 100;
                    }
                    else {
                        src_sprite.left += 100;
                    }
                    if (src_sprite.width > 0) {
                        src_sprite.left = 500;  // Set the left value to the right edge of the image
                        src_sprite.width = -src_sprite.width;
                    }
                    player_sprite.setTextureRect(src_sprite);
                    clock.restart();
                }
                if (player_sprite.getPosition().x > window.getSize().x / static_cast<float>(2)) {
                    player_sprite.move(-rectangleSpeed, 0.0f);
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                if (running_grass.getStatus() != sf::Sound::Playing) {
                    running_grass.play();
                }
                src_sprite.top = 74;
                if (clock.getElapsedTime().asSeconds() > 0.15f) {
                    if (src_sprite.left == 500) {
                        src_sprite.left = 100;
                    }
                    else {
                        src_sprite.left += 100;
                    }
                    if (src_sprite.width < 0) {
                        src_sprite.width = -src_sprite.width;
                    }
                    player_sprite.setTextureRect(src_sprite);
                    clock.restart();
                }
                player_sprite.move(rectangleSpeed, 0.0f);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                if (running_grass.getStatus() != sf::Sound::Playing) {
                    running_grass.play();
                }
                src_sprite.top = 74;
                if (clock.getElapsedTime().asSeconds() > 0.15f) {
                    if (src_sprite.left == 500) {
                        src_sprite.left = 100;
                    }
                    else {
                        src_sprite.left += 100;
                    }
                    player_sprite.setTextureRect(src_sprite);
                    clock.restart();
                }
                if (player_sprite.getPosition().y > window.getSize().y / static_cast<float>(2)) {
                    player_sprite.move(0.0f, -rectangleSpeed);
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                if (running_grass.getStatus() != sf::Sound::Playing) {
                    running_grass.play();
                }
                src_sprite.top = 74;
                if (clock.getElapsedTime().asSeconds() > 0.15f) {
                    if (src_sprite.left == 500) {
                        src_sprite.left = 100;
                    }
                    else {
                        src_sprite.left += 100;
                    }
                    player_sprite.setTextureRect(src_sprite);
                    clock.restart();
                }
                player_sprite.move(0.0f, rectangleSpeed);
            }
        }

        else{
            running_grass.stop();
            running_grass.setLoop(false);
            if (clock.getElapsedTime().asSeconds() > 0.15f) {
                if (src_sprite.top > 0) {
                    src_sprite.top = 0;
                }
                if (src_sprite.left >= 300) {
                    src_sprite.left = 100;
                }
                else {
                    src_sprite.left += 100;
                }
                player_sprite.setTextureRect(src_sprite);
                clock.restart();
            }  
        }
        

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
            HWND hwnd = static_cast<HWND>(window.getSystemHandle());
            LONG style = GetWindowLong(hwnd, GWL_STYLE);
            if (style & WS_CAPTION)
                window.create(sf::VideoMode(1920, 1080), "Survarium", sf::Style::Fullscreen);
            else {
                window.create(sf::VideoMode(1920, 1080), "Survarium", sf::Style::Default);
                window.setSize(sf::Vector2u(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
                window.setPosition(sf::Vector2i(-10, 0));
            }       
        }
        
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0,0, window.getSize().x + player_sprite.getPosition().x, window.getSize().y + player_sprite.getPosition().y)); // Set the texture rectangle to the size of the window
        view.setCenter(sf::Vector2f(player_sprite.getPosition().x + player_sprite.getScale().x, player_sprite.getPosition().y + player_sprite.getScale().y / 2.0f));
        window.setView(view);
        window.draw(sprite);
        window.draw(player_sprite);
        for (int i = 0; i < 1000; i++) {
            window.draw(tree_sprite[i]);
            window.draw(rock_sprite[i]);
        }
        coords.setString("X: " + std::to_string(player_sprite.getPosition().x) + "\nY: " + std::to_string(player_sprite.getPosition().y));
        coords.setCharacterSize(24);
        coords.setFillColor(sf::Color::Black);
        coords.setPosition(player_sprite.getPosition().x - window.getSize().x/2, player_sprite.getPosition().y - window.getSize().y / 2);
        window.draw(coords);
        window.display();
        
    }

    return 0;
}
