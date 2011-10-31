/*
 * @file   parsertest.hpp
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

#ifndef _parsertest_hpp_
#define _parsertest_hpp_
#include <cppunit/extensions/HelperMacros.h>

#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

namespace ec2 {
  namespace tests {
    class ParserTest :  public CppUnit::TestFixture {
      CPPUNIT_TEST_SUITE( ec2::tests::ParserTest );
      CPPUNIT_TEST( AuthorizeSecurityGroupIngressTest );
      CPPUNIT_TEST( CreateSecurityGroupResponseTest );
      CPPUNIT_TEST( DescribeImagesResponseTest );
      CPPUNIT_TEST( DescribeInstancesResponse1Test );
      CPPUNIT_TEST( DescribeInstancesResponse2Test );
      CPPUNIT_TEST( DescribeInstancesResponse3Test );
      CPPUNIT_TEST( DescribeInstancesResponse4Test );
      CPPUNIT_TEST( DescribeSecurityGroupsResponseTest );
      CPPUNIT_TEST( RunInstancesResponse1Test );
      CPPUNIT_TEST( RunInstancesResponse2Test );
      CPPUNIT_TEST( TerminateInstancesResponseTest );

      CPPUNIT_TEST( ResponseAuthFailureTest );
      CPPUNIT_TEST( ResponseInvalidGroupDuplicateTest );
      CPPUNIT_TEST( ResponseInvalidGroupNotFoundTest );
      CPPUNIT_TEST( ResponseUnknownParameterTest );
      CPPUNIT_TEST_SUITE_END();

    public:
      ParserTest();
      ~ParserTest();
      void setUp();
      void tearDown();
      
    protected:
      void AuthorizeSecurityGroupIngressTest();
      void CreateSecurityGroupResponseTest();
      void DescribeImagesResponseTest();
      void DescribeInstancesResponse1Test();
      void DescribeInstancesResponse2Test();
      void DescribeInstancesResponse3Test();
      void DescribeInstancesResponse4Test();
      void DescribeSecurityGroupsResponseTest();

      void RunInstancesResponse1Test();
      void RunInstancesResponse2Test();
      void TerminateInstancesResponseTest();
      
      void ResponseAuthFailureTest();
      void ResponseInvalidGroupDuplicateTest();
      void ResponseInvalidGroupNotFoundTest();
      void ResponseUnknownParameterTest();
      

    private:
      const std::string _convert(const std::string &in);
      const std::string _loadFile(const fs::path &file);
    };
    
  } // namspace tests
} // namspace ec2
#endif /* _parsertest_hpp_ */

/*
 * Local variables:
 *  tab-width: 2
 *  c-indent-level: 2
 *  c-basic-offset: 2
 *  project-name: ec2-api
 * End:
 */
