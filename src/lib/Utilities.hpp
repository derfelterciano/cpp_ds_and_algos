#pragma once

using vrtx = std::pair<int, int>;

namespace std {
template <>
struct hash<std::pair<int, int>> {
    std::size_t operator()(const std::pair<int, int>& p) const noexcept {
        return std::hash<int>{}(p.first) ^ (std::hash<int>{}(p.second) << 1);
    }
};
};  // namespace std