// Copyright (c) 2014-2020 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/PEGTL/

#ifndef TAO_PEGTL_CONTRIB_COUNTER_HPP
#define TAO_PEGTL_CONTRIB_COUNTER_HPP

#include <cstddef>
#include <map>
#include <string_view>

#include "../config.hpp"
#include "../normal.hpp"

#include "../internal/demangle.hpp"

namespace TAO_PEGTL_NAMESPACE
{
   struct counter_data
   {
      std::size_t start = 0;
      std::size_t success = 0;
      std::size_t failure = 0;
   };

   struct counter_state
   {
      std::map< std::string_view, counter_data > counts;
   };

   template< typename Rule >
   struct counter
      : normal< Rule >
   {
      template< typename ParseInput >
      static void start( const ParseInput& /*unused*/, counter_state& ts )
      {
         ++ts.counts[ internal::demangle< Rule >() ].start;
      }

      template< typename ParseInput >
      static void success( const ParseInput& /*unused*/, counter_state& ts )
      {
         ++ts.counts[ internal::demangle< Rule >() ].success;
      }

      template< typename ParseInput >
      static void failure( const ParseInput& /*unused*/, counter_state& ts )
      {
         ++ts.counts[ internal::demangle< Rule >() ].failure;
      }
   };

}  // namespace TAO_PEGTL_NAMESPACE

#endif
