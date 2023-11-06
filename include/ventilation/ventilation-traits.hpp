#ifndef VENTILATION_TRAITS_HPP__
#define VENTILATION_TRAITS_HPP__

#include <type_traits>

#include "ventilation-compliance.hpp"
#include "ventilation-elastance.hpp"
#include "ventilation-flow.hpp"
#include "ventilation-packet.hpp"
#include "ventilation-pressure.hpp"
#include "ventilation-resistance.hpp"
#include "ventilation-volume.hpp"


namespace ventilation {
    template <typename T>
    struct is_flow_type : std::integral_constant<
                          bool
                          ,  std::is_same<Flow<      float>, typename std::remove_cv<T>::type>::value
                          || std::is_same<Flow<     double>, typename std::remove_cv<T>::type>::value
                          || std::is_same<Flow<long double>, typename std::remove_cv<T>::type>::value
                          > {};

    template <typename T>
    struct is_pressure_type : std::integral_constant<
                          bool
                          ,  std::is_same<       Pressure<      float>, typename std::remove_cv<T>::type>::value
                          || std::is_same<       Pressure<     double>, typename std::remove_cv<T>::type>::value
                          || std::is_same<       Pressure<long double>, typename std::remove_cv<T>::type>::value
                          || std::is_same<           PEEP<      float>, typename std::remove_cv<T>::type>::value
                          || std::is_same<           PEEP<     double>, typename std::remove_cv<T>::type>::value
                          || std::is_same<           PEEP<long double>, typename std::remove_cv<T>::type>::value
                          || std::is_same< pressure::Peak<      float>, typename std::remove_cv<T>::type>::value
                          || std::is_same< pressure::Peak<     double>, typename std::remove_cv<T>::type>::value
                          || std::is_same< pressure::Peak<long double>, typename std::remove_cv<T>::type>::value
                          || std::is_same<pressure::Delta<      float>, typename std::remove_cv<T>::type>::value
                          || std::is_same<pressure::Delta<     double>, typename std::remove_cv<T>::type>::value
                          || std::is_same<pressure::Delta<long double>, typename std::remove_cv<T>::type>::value
                          > {};

    template <typename T>
    struct is_volume_type : std::integral_constant<
                          bool
                          ,  std::is_same<       Volume<      float>, typename std::remove_cv<T>::type>::value
                          || std::is_same<       Volume<     double>, typename std::remove_cv<T>::type>::value
                          || std::is_same<       Volume<long double>, typename std::remove_cv<T>::type>::value
                          || std::is_same<volume::Tidal<      float>, typename std::remove_cv<T>::type>::value
                          || std::is_same<volume::Tidal<     double>, typename std::remove_cv<T>::type>::value
                          || std::is_same<volume::Tidal<long double>, typename std::remove_cv<T>::type>::value
                          > {};

    template <typename T>
    struct is_packet_type : std::integral_constant<
                          bool
                          ,  std::is_same<Packet<      float>, typename std::remove_cv<T>::type>::value
                          || std::is_same<Packet<     double>, typename std::remove_cv<T>::type>::value
                          || std::is_same<Packet<long double>, typename std::remove_cv<T>::type>::value
                          > {};

    template <typename T>
    struct is_airway_type : std::integral_constant<
                            bool
                            , is_flow_type<T>::value || is_pressure_type<T>::value || is_volume_type<T>::value
                            > {};

    template <typename T>
    struct is_elastance_type : std::integral_constant<
                          bool
                          ,  std::is_same<Elastance<      float>, typename std::remove_cv<T>::type>::value
                          || std::is_same<Elastance<     double>, typename std::remove_cv<T>::type>::value
                          || std::is_same<Elastance<long double>, typename std::remove_cv<T>::type>::value
                          > {};

    template <typename T>
    struct is_compliance_type : std::integral_constant<
                          bool
                          ,  std::is_same<Compliance<      float>, typename std::remove_cv<T>::type>::value
                          || std::is_same<Compliance<     double>, typename std::remove_cv<T>::type>::value
                          || std::is_same<Compliance<long double>, typename std::remove_cv<T>::type>::value
                          > {};

    template <typename T>
    struct is_resistance_type : std::integral_constant<
                          bool
                          ,  std::is_same<Resistance<      float>, typename std::remove_cv<T>::type>::value
                          || std::is_same<Resistance<     double>, typename std::remove_cv<T>::type>::value
                          || std::is_same<Resistance<long double>, typename std::remove_cv<T>::type>::value
                          > {};

    template <typename T>
    struct is_lung_type : std::integral_constant<
                            bool
                            , is_elastance_type<T>::value || is_compliance_type<T>::value || is_resistance_type<T>::value
                            > {};

    template <typename T>
    struct is_ventilation_type : std::integral_constant<
                                 bool
                                 ,  is_airway_type<T>::value
                                 || is_lung_type<T>::value
                                 || is_packet_type<T>::value
                                 >
    {};

    // Extracts precision from ventilation types
    template <typename T> struct precision;
    template <typename U> struct precision<Compliance<U>>   { typedef U type; };
    template <typename U> struct precision<Elastance<U>>    { typedef U type; };
    template <typename U> struct precision<Flow<U>>         { typedef U type; };
    template <typename U> struct precision<Pressure<U>>     { typedef U type; };
    template <typename U> struct precision<Resistance<U>>   { typedef U type; };
    template <typename U> struct precision<Volume<U>>       { typedef U type; };
} // namespace ventilation

#endif // VENTILATION_TRAITS_HPP__
