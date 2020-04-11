// Copyright (c) 2014-2020 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/PEGTL/

#include "test.hpp"
#include "verify_seqs.hpp"

namespace TAO_PEGTL_NAMESPACE
{
   struct test_state_state
   {
      template< typename ParseInput >
      explicit test_state_state( const ParseInput& /*unused*/ )
      {}

      template< typename ParseInput >
      void success( const ParseInput& /*unused*/ ) const
      {}
   };

   template< typename... Rules >
   using test_state_rule = state< test_state_state, Rules... >;

   void unit_test()
   {
      verify_seqs< test_state_rule >();
   }

}  // namespace TAO_PEGTL_NAMESPACE

#include "main.hpp"
