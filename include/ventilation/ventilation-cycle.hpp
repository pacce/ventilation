#ifndef VENTILATION_CYCLE_HPP__
#define VENTILATION_CYCLE_HPP__

#include <chrono>
#include <iostream>
#include <optional>

#include "ventilation-frequency.hpp"
#include "ventilation-ratio.hpp"
#include "ventilation-time.hpp"

namespace ventilation {
namespace cycle {
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
            Interval(const Time<Precision>& start, const Time<Precision>& finish, State state)
                : start_(start)
                , finish_(finish)
                , state_(state)
            {}

            bool
            inside(const Time<Precision>& instant) const {
                return (start_ <= instant) and (instant < finish_);
            }

            bool
            outside(const Time<Precision>& instant) const {
                return not inside(instant);
            }

            State
            state() const {
                return state_;
            }
        private:
            Time<Precision> start_;
            Time<Precision> finish_;
            State           state_;
    };

    template <typename Precision>
    class Cycle {
        static_assert(std::is_floating_point<Precision>::value);
        public:
            Cycle(
                      const Inspiration<Precision>&         i
                    , const inspiratory::Pause<Precision>&  fst
                    , const Expiration<Precision>&          e
                    , const expiratory::Pause<Precision>&   snd
                 )
                : current_(Precision())
                , index_(0)
            {
                using namespace std::chrono_literals;

                // Inspiratory phase
                Time<Precision> prev = 0s;
                Time<Precision> next = i;
                intervals_.emplace_back(prev, next, State::INSPIRATION);
                // Inspiratory pause
                if (fst) {
                    prev  = next;
                    next += *fst;
                    intervals_.emplace_back(prev, next, State::INSPIRATORY_PAUSE);
                }
                // Expiratory phase
                prev  = next;
                next += e;
                intervals_.emplace_back(prev, next, State::EXPIRATION);
                // Expiratory pause
                if (snd) {
                    prev  = next;
                    next += *snd;
                    intervals_.emplace_back(prev, next, State::EXPIRATORY_PAUSE);
                }
            }

            Cycle(const Time<Precision>& i, const Time<Precision>& e) : Cycle(i, {}, e, {})
            {}

            Cycle(const frequency::Frequency<Precision>& f, const ratio::Ratio<Precision>& r)
                : Cycle(r.inspiration(f), r.expiration(f))
            {}

            std::optional<Mark>
            operator()(const Time<Precision>& step) {
                using namespace std::chrono_literals;

                current_ += step;
                if (intervals_[index_].inside(current_)) { return {}; }

                index_ = (index_ + 1) % intervals_.size();
                if (index_ == 0) { current_ = 0s; }

                if (this->state() == State::INSPIRATION) {
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
            Time<Precision>                     current_;

            std::size_t                         index_;
            std::vector<Interval<Precision>>    intervals_;
    };
} // namespace cycle
} // namespace ventilation

#endif // VENTILATION_CYCLE_HPP__
