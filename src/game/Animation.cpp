#include "Animation.hpp"

Animation::Animation() : m_frameTime(sf::seconds(0.1f)), m_currentFrame(0), m_isPaused(true), m_isLooped(false) {}

void Animation::init(const sf::Texture& sheet, int each_frame_x_size, int each_frame_y_size, int total_frame_number, int frame_time_in_ms, bool isLoop) {
    setSpriteSheet(sheet);
    int framesPerRow = sheet.getSize().x / each_frame_x_size;
    for (int i = 0; i < total_frame_number; i++) {
        int frameX = (i % framesPerRow) * each_frame_x_size;
        int frameY = (i / framesPerRow) * each_frame_y_size;
        sf::IntRect frameRect(frameX, frameY, each_frame_x_size, each_frame_y_size);
        addFrame(frameRect);
    }

    setFrameTime(sf::milliseconds(frame_time_in_ms)); // Adjust frame time as needed
    play();
    setLooped(isLoop);
}

void Animation::addFrame(sf::IntRect frame) {
    m_frames.push_back(frame);
}

void Animation::setSpriteSheet(const sf::Texture& texture) {
    m_spriteSheet = texture;
}

void Animation::setFrameTime(sf::Time time) {
    m_frameTime = time;
}

void Animation::play() {
    m_isPaused = false;
}

void Animation::pause() {
    m_isPaused = true;
}

void Animation::stop() {
    m_isPaused = true;
    m_currentFrame = 0;
}

void Animation::setLooped(bool looped) {
    m_isLooped = looped;
}

void Animation::update(sf::Time deltaTime) {
    if (!m_isPaused && m_frameTime != sf::Time::Zero) {
        m_elapsedTime += deltaTime;
        if (m_elapsedTime >= m_frameTime) {
            m_elapsedTime -= m_frameTime;
            if (m_currentFrame + 1 < m_frames.size()) {
                ++m_currentFrame;
            } else {
                m_currentFrame = 0;
                if (!m_isLooped) {
                    m_isPaused = true;
                }
            }
        }
    }
}

void Animation::setFrame(size_t frame) {
    if (frame < m_frames.size()) {
        m_currentFrame = frame;
    }
}

sf::IntRect Animation::getFrame() const {
    return m_frames[m_currentFrame];
}

const sf::Texture* Animation::getSpriteSheet() const {
    return &m_spriteSheet;
}
