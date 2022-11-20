#ifndef VENTILATION_MEAN_HPP__
#define VENTILATION_MEAN_HPP__

#include <numeric>
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

    template <typename Iterator>
    typename std::iterator_traits<Iterator>::value_type
    mean(Iterator begin, Iterator end) {
        using T = typename std::iterator_traits<Iterator>::value_type;
        static_assert(is_ventilation_type<T>::value);
        static_assert(std::is_default_constructible<T>::value);

        using Precision = typename ventilation::precision<T>::type;

        std::size_t count   = std::distance(begin, end);
        Precision scale     = (count == 0) ? 1.0 : (1.0 / static_cast<Precision>(count));
        return std::accumulate(
                  begin
                , end
                , T()
                , [=](const T& acc, const T& x) { return acc + (x * scale); }
                );
    }
} // namespace ventilation

#endif // VENTILATION_MEAN_HPP__
