#ifndef VECTOR_EXTENSIONS_HPP
#define VECTOR_EXTENSIONS_HPP

#include <SFML/System/Vector2.hpp>

#include <Tank/Utility/Vector.hpp>

#include <cmath>

namespace sf {

template<typename T>
T dot(sf::Vector2<T> const& v1, sf::Vector2<T> const& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

template<typename T>
T magnitudeSquared(sf::Vector2<T> const& v) {
    return dot(v,v);
}

template<typename T>
T magnitude(sf::Vector2<T> const& v) {
    return std::sqrt(magnitudeSquared(v));
}

template<typename T>
sf::Vector2<T> unit(sf::Vector2<T> const& v) {
    return v / magnitude(v);
}

template<typename T>
sf::Vector2<T> vector_cast(tank::Vector<T> const& v) {
    return {v.x, v.y};
}

}

#endif // VECTOR_EXTENSIONS_HPP
