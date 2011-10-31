/*
 * @file   options.hpp
 * @date   2011-10-18
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

#ifndef _options_hpp_
#define _options_hpp_

#include <sstream>

#include <boost/program_options.hpp>

#include <ec2-api/ec2.hpp>

namespace po = boost::program_options;

namespace ec2 {
  namespace options {
    class optionCommand {
    public:
      typedef ec2::shared_ptr<optionCommand> Ptr;

      optionCommand() {}//  : _general("GENERAL OPTIONS") {};
      optionCommand(const std::string command, const std::string resptag);
      virtual ~optionCommand() {}
      
      const po::options_description cmdline_options() const { return _cmdline_options; }
      const std::string command() const { return _command; }
      const std::string resptag() const { return _resptag; }
      
      void complete(const po::options_description &specific);

      virtual void setOptions(const po::variables_map &vm, const std::vector<std::string> rest, ec2::Map_Type &opt) =0; 

      virtual  void  help() = 0;
      virtual  const po::options_description &specific() = 0;
      virtual  void  printResponse(const ec2::xml::parse::type::EC2Response_t &response) = 0;
      
    private:
      po::options_description _cmdline_options;
      po::options_description _general;
      std::string _command;   /**< value of ACTION field in query */
      std::string _resptag;   /**< Response Tag in xml response */
      
    };
    
  } // namespace options
} // namespace ec2
#endif /* _options_hpp_ */
