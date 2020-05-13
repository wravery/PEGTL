// Copyright (c) 2020 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/PEGTL/

#include "test.hpp"

#include "verify_meta.hpp"

namespace TAO_PEGTL_NAMESPACE
{
   void unit_test()
   {
      verify_meta< raise< int >, internal::raise< int > >();
      verify_meta< raise< any >, internal::raise< any > >();

      verify_analyze< raise< int > >( __LINE__, __FILE__, true, false );
      verify_analyze< raise< any > >( __LINE__, __FILE__, true, false );

      memory_input in( "foo", __FUNCTION__ );

      TAO_PEGTL_TEST_THROWS( parse< raise< int > >( in ) );
      TAO_PEGTL_TEST_ASSERT( in.size( 4 ) == 3 );
      TAO_PEGTL_TEST_THROWS( parse< raise< any > >( in ) );
      TAO_PEGTL_TEST_ASSERT( in.size( 4 ) == 3 );
   }

}  // namespace TAO_PEGTL_NAMESPACE

#include "main.hpp"