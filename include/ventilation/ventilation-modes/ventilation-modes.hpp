#ifndef VENTILATION_MODES_HPP__
#define VENTILATION_MODES_HPP__

#include "ventilation-modes-empty.hpp"
#include "ventilation-modes-pcv.hpp"
#include "ventilation-modes-vcv.hpp"
#include <variant>

namespace ventilation {
    template <typename Precision>
    using Modes = std::variant<
          modes::Empty<Precision>
        , modes::PCV<Precision>
        , modes::VCV<Precision>
        >;
namespace modes {
    enum class Names { EMPTY, PCV, VCV };
} // namespace modes
} // namespace ventilation

#endif // VENTILATION_MODES_HPP__
