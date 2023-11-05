#ifndef VENTILATION_INTEGRATION_HPP__
#define VENTILATION_INTEGRATION_HPP__

#include <chrono>
#include <numeric>
#include <vector>

#include "ventilation-flow.hpp"
#include "ventilation-time.hpp"
#include "ventilation-volume.hpp"

namespace ventilation {
namespace integration {
    template<typename Precision>
    Volume<Precision>
    square(const Flow<Precision>& f, const Time<Precision>& t) {
        static_assert(std::is_floating_point<Precision>::value);

        Precision seconds   = static_cast<Precision>(t.count());
        Precision flow      = static_cast<Precision>(f);

        return Volume<Precision>(flow * seconds);
    }

    template<typename Precision>
    Volume<Precision>
    squares(const std::vector<Flow<Precision>>& fs, const Time<Precision>& t) {
        static_assert(std::is_floating_point<Precision>::value);

        return std::accumulate(
                  fs.begin()
                , fs.end()
                , Volume<Precision>()
                , [=](Volume<Precision> v, Flow<Precision> f) { return v + square(f, t); }
                );
    }
}
} // namespace ventilation

#endif // VENTILATION_INTEGRATION_HPP__
