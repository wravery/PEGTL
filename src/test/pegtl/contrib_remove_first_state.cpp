// Copyright (c) 2020 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/PEGTL/

#include "test.hpp"

#include <tao/pegtl/contrib/remove_first_state.hpp>

namespace TAO_PEGTL_NAMESPACE
{
   template< typename Rule >
   struct test_action
      : nothing< Rule >
   {};

   template<>
   struct test_action< one< 'F' > >
   {
      static void apply0( unsigned& u ) noexcept
      {
         u |= 1;
      }
   };

   template<>
   struct test_action< eof >
   {
      template< typename ActionInput >
      static void apply( const ActionInput& /*unused*/, unsigned& u ) noexcept
      {
         u |= 2;
      }
   };

   template< typename Rule >
   struct control_impl
      : normal< Rule >
   {
      template< typename ParseInput >
      static void start( ParseInput& /*unused*/, unsigned& u ) noexcept
      {
         u |= 64;
      }

      template< typename ParseInput >
      static void success( ParseInput& /*unused*/, unsigned& u ) noexcept
      {
         u |= 32;
      }

      template< typename ParseInput >
      static void failure( ParseInput& /*unused*/, unsigned& u ) noexcept
      {
         u |= 16;
      }

      template< typename ParseInput >
      [[noreturn]] static void raise( ParseInput& in, unsigned& u )
      {
         u |= 4;
         throw parse_error( "raise", in );
      }

      template< typename ParseInput >
      static void unwind( ParseInput& /*unused*/, unsigned& u ) noexcept
      {
         u |= 8;
      }
   };

   template< typename Rule >
   struct test_control
      : remove_first_state< control_impl< Rule > >
   {};

   struct test_rule
      : seq< sor< try_catch< must< one< 'a' > > >, one< 'F' > >, eof >
   {};

   void unit_test()
   {
      unsigned u = 0;
      const std::string d = "F";
      memory_input in( d, __FUNCTION__ );
      parse< test_rule, test_action, test_control >( in, d, u );

      TAO_PEGTL_TEST_ASSERT( u == 127 );
   }

}  // namespace TAO_PEGTL_NAMESPACE

#include "main.hpp"
