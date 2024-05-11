#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Animation {
public:
    Animation();
    void init(const sf::Texture& sheet, int each_frame_x_size, int each_frame_y_size, int total_frame_number, int frame_time_in_ms, bool isLoop);

    void addFrame(sf::IntRect frame);
    void setSpriteSheet(const sf::Texture& texture);
    void setFrameTime(sf::Time time);
    void play();
    void pause();
    void stop();
    void setLooped(bool looped);
    void update(sf::Time deltaTime);
    void setFrame(size_t frame);
    sf::IntRect getFrame() const;
    const sf::Texture* getSpriteSheet() const;

private:
    std::vector<sf::IntRect> m_frames;
    sf::Texture m_spriteSheet;
    sf::Time m_frameTime;
    sf::Time m_elapsedTime;
    size_t m_currentFrame;
    bool m_isPaused;
    bool m_isLooped;
};

#endif // ANIMATION_HPP
