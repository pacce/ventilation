#ifndef VENTILATION_TIME_HPP__
#define VENTILATION_TIME_HPP__

#include <chrono>
#include <optional>

namespace ventilation {
    template <typename Precision> using Time        = std::chrono::duration<Precision>;

    template <typename Precision> using Expiration  = Time<Precision>;
    template <typename Precision> using Inspiration = Time<Precision>;
namespace expiratory {
    template <typename Precision> using Pause   = std::optional<Time<Precision>>;
} // namespace expiratory
namespace inspiratory {
    template <typename Precision> using Pause   = std::optional<Time<Precision>>;
} // namespace inspiratory
} // namespace

#endif // VENTILATION_TIME_HPP__
