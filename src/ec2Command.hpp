/*
 * @file   ec2Command.hpp
 * @date   2011-10-17
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

#ifndef _ec2Command_hpp_
#define _ec2Command_hpp_
#include <boost/program_options.hpp>

#include <ec2-api/ec2.hpp>
#include <ec2-api/SimpleRequestObserver.hpp>

#include <options.hpp>

namespace po = boost::program_options;


namespace ec2 {
  class ec2Command {
  public:
    ec2Command(const ec2::options::optionCommand::Ptr specific);
    
    ~ec2Command() {}
    
    void Run(int argc, char **argv);
    
  private:
    void _command(const std::string &arg);
    bool _parse_commandline(int argc, char **argv);

  private:
    ec2::RequestObserver::Ptr _Observer;
    ec2::CFRuntime            _sdk;
    ec2::Map_Type             _opt;
    ec2::xml::parse::type::EC2Response_t _ret;

    std::string _url;         /**< EC2_URL : https://ec2.amazonaws.com */

    std::string _commandStr;
    ec2::options::optionCommand::Ptr _Command;
  };
  
    
} // namespace ec2
/*
 * Local variables:
 *  tab-width: 2
 *  c-indent-level: 2
 *  c-basic-offset: 2
 *  project-name: ec2-api
 * End:
 */
#endif /* _ec2Command_hpp_ */
