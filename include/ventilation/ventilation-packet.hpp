#ifndef VENTILATION_PACKET_HPP__
#define VENTILATION_PACKET_HPP__

#include "ventilation-flow.hpp"
#include "ventilation-pressure.hpp"
#include "ventilation-volume.hpp"

namespace ventilation {
    template <typename Precision>
    struct Packet {
        Flow<Precision>        flow;
        Pressure<Precision>    pressure;
        Volume<Precision>      volume;

        friend std::ostream&
        operator<<(std::ostream& os, const Packet<Precision>& packet) {
            os  << packet.pressure
                << ", "
                << packet.flow
                << ", "
                << packet.volume
                ;
            return os;
        }

        Packet<Precision>&
        operator+=(const Packet<Precision>& rhs) {
            flow        += rhs.flow;
            pressure    += rhs.pressure;
            volume      += rhs.volume;
            return *this;
        }

        Packet<Precision>&
        operator-=(const Packet<Precision>& rhs) {
            flow        -= rhs.flow;
            pressure    -= rhs.pressure;
            volume      -= rhs.volume;
            return *this;
        }

        Packet<Precision>&
        operator*=(const Packet<Precision>& rhs) {
            flow        *= rhs.flow;
            pressure    *= rhs.pressure;
            volume      *= rhs.volume;
            return *this;
        }

        Packet<Precision>&
        operator*=(const Precision& rhs) {
            flow        *= rhs;
            pressure    *= rhs;
            volume      *= rhs;
            return *this;
        }

        friend Packet<Precision>
        operator+(const Packet<Precision>& lhs, const Packet<Precision>& rhs) {
            return 
            { lhs.flow      + rhs.flow
            , lhs.pressure  + rhs.pressure
            , lhs.volume    + rhs.volume
            };
        }

        friend Packet<Precision>
        operator-(const Packet<Precision>& lhs, const Packet<Precision>& rhs) {
            return 
            { lhs.flow      - rhs.flow
            , lhs.pressure  - rhs.pressure
            , lhs.volume    - rhs.volume
            };
        }

        friend Packet<Precision>
        operator*(const Packet<Precision>& lhs, const Packet<Precision>& rhs) {
            return 
            { lhs.flow      * rhs.flow
            , lhs.pressure  * rhs.pressure
            , lhs.volume    * rhs.volume
            };
        }

        friend Packet<Precision>
        operator*(const Packet<Precision>& packet, const Precision& scalar) {
            return 
            { packet.flow      * scalar
            , packet.pressure  * scalar
            , packet.volume    * scalar
            };
        }

        friend Packet<Precision>
        operator*(const Precision& scalar, const Packet<Precision>& packet) {
            return 
            { packet.flow      * scalar
            , packet.pressure  * scalar
            , packet.volume    * scalar
            };
        }

        friend bool
        operator==(const Packet<Precision>& lhs, const Packet<Precision>& rhs) {
            return lhs.flow     == rhs.flow
                && lhs.pressure == rhs.pressure
                && lhs.volume   == rhs.volume
                ;
        }

        friend bool
        operator!=(const Packet<Precision>& lhs, const Packet<Precision>& rhs) {
            return !(lhs == rhs);
        }
    };
} // namespace ventilation

#endif // VENTILATION_PACKET_HPP__
