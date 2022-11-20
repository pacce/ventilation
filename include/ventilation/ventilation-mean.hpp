#ifndef VENTILATION_MEAN_HPP__
#define VENTILATION_MEAN_HPP__

#include <type_traits>
#include <vector>

#include "ventilation-traits.hpp"

namespace ventilation {
    template <typename Precision, template <typename> typename T>
    T<Precision>
    mean(const std::vector<T<Precision>>& xs) {
        static_assert(is_ventilation_type<T<Precision>>::value);
        static_assert(std::is_default_constructible<T<Precision>>::value);

        std::size_t count   = xs.size();
        Precision scale     = (count == 0) ? 1.0 : (1.0 / static_cast<Precision>(count));
        return std::accumulate(
                  xs.begin()
                , xs.end()
                , T<Precision>()
                , [=](const T<Precision>& acc, const T<Precision>& x) { return acc + (x * scale); }
                );
    }
} // namespace ventilation

#endif // VENTILATION_MEAN_HPP__
