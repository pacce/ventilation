#ifndef VENTILATION_CYCLE_HPP__
#define VENTILATION_CYCLE_HPP__

#include <chrono>

namespace ventilation  {
namespace cycle  {
    enum class State { EXPIRATION, INSPIRATION };

    template <typename Precision>
    class Cycle {
        static_assert(std::is_floating_point<Precision>::value);
        public:
            Cycle(const std::chrono::duration<Precision>& i, const std::chrono::duration<Precision>& e) 
                : current_(Precision())
                , inspiration_(i)
                , expiration_(e)
            {}

            State
            operator()(const std::chrono::duration<Precision>& step) {
                current_ += step;
                if (current_ >= (inspiration_ + expiration_)) {
                    current_ = std::chrono::duration<Precision>(Precision());
                }

                if (current_ <= inspiration_) {
                    return State::INSPIRATION;
                } else {
                    return State::EXPIRATION;
                }
            }
        private:
            std::chrono::duration<Precision> current_;
            std::chrono::duration<Precision> inspiration_;
            std::chrono::duration<Precision> expiration_;
    };
} // namespace cycle
} // namespace ventilation

#endif // VENTILATION_CYCLE_HPP__
