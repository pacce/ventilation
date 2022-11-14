#ifndef VENTILATION_CYCLE_HPP__
#define VENTILATION_CYCLE_HPP__

#include <chrono>

namespace ventilation  {
namespace cycle  {
    enum class State {
          EXPIRATION
        , INSPIRATION
        , START_OF_EXPIRATION
        , START_OF_INSPIRATION
    };

    template <typename Precision>
    class Cycle {
        static_assert(std::is_floating_point<Precision>::value);
        public:
            Cycle(const std::chrono::duration<Precision>& i, const std::chrono::duration<Precision>& e)
                : state_(State::INSPIRATION)
                , current_(Precision())
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
                    if (state_ != State::INSPIRATION) {
                        state_ = State::INSPIRATION;
                        return State::START_OF_INSPIRATION;
                    } else {
                        return state_;
                    }
                } else {
                    if (state_ != State::EXPIRATION) {
                        state_ = State::EXPIRATION;
                        return State::START_OF_EXPIRATION;
                    } else {
                        return state_;
                    }
                }
            }
        private:
            State state_;

            std::chrono::duration<Precision> current_;
            std::chrono::duration<Precision> inspiration_;
            std::chrono::duration<Precision> expiration_;
    };
} // namespace cycle
} // namespace ventilation

#endif // VENTILATION_CYCLE_HPP__
