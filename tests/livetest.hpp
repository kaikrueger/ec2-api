/*
 * @file   livetest.hpp
 *  @date   2011-09-28
 *
 * Created by Kai Krueger <kai.krueger@itwm.fraunhofer.de>
 *
 * Copyright (c) 2011 Fraunhofer ITWM
 * All rights reserved.
 * 
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _livetest_hpp_
#define _livetest_hpp_
#include <cppunit/extensions/HelperMacros.h>

namespace ec2 {
  namespace tests {
    class LiveTest :  public CppUnit::TestFixture {
      CPPUNIT_TEST_SUITE( ec2::tests::LiveTest );
      CPPUNIT_TEST( AuthNoKey );
      CPPUNIT_TEST( AuthBadAccessKey );
      CPPUNIT_TEST( AuthBadSignature );
      CPPUNIT_TEST( DescribeImagesAll );
      CPPUNIT_TEST( DescribeInstances );
      CPPUNIT_TEST( TerminateInstancesNotExisting );
//      CPPUNIT_TEST(  );
//      CPPUNIT_TEST(  );
//      CPPUNIT_TEST(  );
//      CPPUNIT_TEST(  );
      CPPUNIT_TEST_SUITE_END();

    public:
      LiveTest();
      ~LiveTest();
      
    protected:
      void AuthNoKey();
      void AuthBadAccessKey();
      void AuthBadSignature();
      void DescribeImagesAll();
      void DescribeInstances();
      void TerminateInstancesNotExisting();
      
    private:
    };
    
  } // namspace tests
} // namspace ec2
#endif /* _livetest_hpp_ */

/*
 * Local variables:
 *  tab-width: 2
 *  c-indent-level: 2
 *  c-basic-offset: 2
 *  project-name: ec2-api
 * End:
 */
