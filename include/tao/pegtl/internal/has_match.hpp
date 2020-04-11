// Copyright (c) 2019-2020 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/PEGTL/

#ifndef TAO_PEGTL_INTERNAL_HAS_MATCH_HPP
#define TAO_PEGTL_INTERNAL_HAS_MATCH_HPP

#include <type_traits>
#include <utility>

#include "../apply_mode.hpp"
#include "../config.hpp"
#include "../rewind_mode.hpp"

namespace TAO_PEGTL_NAMESPACE::internal
{
   template< typename,
             typename Rule,
             apply_mode A,
             rewind_mode M,
             template< typename... >
             class Action,
             template< typename... >
             class Control,
             typename ParseInput,
             typename... States >
   struct has_match
      : std::false_type
   {};

   template< typename Rule,
             apply_mode A,
             rewind_mode M,
             template< typename... >
             class Action,
             template< typename... >
             class Control,
             typename ParseInput,
             typename... States >
   struct has_match< decltype( (void)Action< Rule >::template match< Rule, A, M, Action, Control >( std::declval< ParseInput& >(), std::declval< States&& >()... ), void() ), Rule, A, M, Action, Control, ParseInput, States... >
      : std::true_type
   {};

   template< typename Rule,
             apply_mode A,
             rewind_mode M,
             template< typename... >
             class Action,
             template< typename... >
             class Control,
             typename ParseInput,
             typename... States >
   inline constexpr bool has_match_v = has_match< void, Rule, A, M, Action, Control, ParseInput, States... >::value;

}  // namespace TAO_PEGTL_NAMESPACE::internal

#endif
