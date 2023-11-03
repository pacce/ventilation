#ifndef VENTILATION_CYCLE_HPP__
#define VENTILATION_CYCLE_HPP__

#include <chrono>
#include <iostream>
#include <optional>
#include "ventilation-frequency.hpp"
#include "ventilation-ratio.hpp"

namespace ventilation  {
namespace cycle  {
    enum class State    {
          INSPIRATION
        , INSPIRATORY_PAUSE
        , EXPIRATION
        , EXPIRATORY_PAUSE
    };
    enum class Mark     { START_OF_EXPIRATION, START_OF_INSPIRATION };

    template <typename Precision>
    class Interval {
        static_assert(std::is_floating_point<Precision>::value);
        public:
            Interval(
                      const std::chrono::duration<Precision>&   start
                    , const std::chrono::duration<Precision>&   finish
                    , State                                     state
                    )
                : start_(start)
                , finish_(finish)
                , state_(state)
            {}

            bool
            inside(const std::chrono::duration<Precision>& instant) const {
                return (start_ <= instant) and (instant < finish_);
            }

            bool
            outside(const std::chrono::duration<Precision>& instant) const {
                return not inside(instant);
            }

            State
            state() const {
                return state_;
            }
        private:
            std::chrono::duration<Precision>    start_;
            std::chrono::duration<Precision>    finish_;
            State                               state_;
    };

    template <typename Precision>
    class Cycle {
        static_assert(std::is_floating_point<Precision>::value);
        public:
            Cycle(
                      const std::chrono::duration<Precision>& i     // Inspiratory Time
                    , const std::chrono::duration<Precision>& fst   // Inspiratory Pause
                    , const std::chrono::duration<Precision>& e     // Expiratory Time
                    , const std::chrono::duration<Precision>& snd   // Inspiratory Pause
                    )
                : current_(Precision())
                , index_(0)
            {
                using namespace std::chrono_literals;

                intervals_.emplace_back(         0s,         i        , State::INSPIRATION);
                intervals_.emplace_back(          i,         i + fst  , State::INSPIRATORY_PAUSE);
                intervals_.emplace_back(    i + fst,       i + fst + e, State::EXPIRATION);
                intervals_.emplace_back(i + fst + e, i + fst + e + snd, State::EXPIRATORY_PAUSE);
            }

            Cycle(
                      const std::chrono::duration<Precision>& i // Inspiratory Time
                    , const std::chrono::duration<Precision>& p // Inspiratory Pause
                    , const std::chrono::duration<Precision>& e // Expiratory Time
                    )
                : current_(Precision())
                , index_(0)
            {
                using namespace std::chrono_literals;

                intervals_.emplace_back(   0s, i        , State::INSPIRATION);
                intervals_.emplace_back(    i, i + p    , State::INSPIRATORY_PAUSE);
                intervals_.emplace_back(i + p, i + p + e, State::EXPIRATION);
            }

            Cycle(
                      const std::chrono::duration<Precision>& i // Inspiratory Time
                    , const std::chrono::duration<Precision>& e // Expiratory Time
                    )
                : current_(Precision())
                , index_(0)
            {
                using namespace std::chrono_literals;

                intervals_.emplace_back(0s, i    , State::INSPIRATION);
                intervals_.emplace_back( i, i + e, State::EXPIRATION);
            }

            Cycle(const frequency::Frequency<Precision>& f, const ratio::Ratio<Precision>& r)
                : Cycle(r.inspiration(f), r.expiration(f))
            {}

            std::optional<Mark>
            operator()(const std::chrono::duration<Precision>& step) {
                using namespace std::chrono_literals;

                current_ += step;
                if (intervals_[index_].inside(current_)) { return {}; }

                index_ = (index_ + 1) % intervals_.size();
                if (index_ == 0) { current_ = 0s; }

                if (intervals_[index_].state() == State::INSPIRATION) {
                    return Mark::START_OF_INSPIRATION;
                } else if (intervals_[index_].state() == State::EXPIRATION) {
                    return Mark::START_OF_EXPIRATION;
                } else {
                    return {};
                }
            }

            State
            state() const { return intervals_[index_].state(); }
        private:
            std::chrono::duration<Precision>    current_;
            std::size_t                         index_;
            std::vector<Interval<Precision>>    intervals_;
    };
} // namespace cycle
} // namespace ventilation

#endif // VENTILATION_CYCLE_HPP__
