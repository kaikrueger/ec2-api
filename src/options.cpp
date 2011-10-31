/*
 * @file   options.cpp
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

#include <src/options.hpp>

using namespace ec2::options;


optionCommand::optionCommand(
  const std::string command
  , const std::string resptag
) : _general("GENERAL OPTIONS")
  , _command(command)
  , _resptag(resptag)
{
  _general.add_options()
    ("private-key,K",po::value< std::string >(), 
     "Specify KEY as the private key to use. Defaults to the value of the "
     "EC2_PRIVATE_KEY environment variable (if set). Overrides the default.")
    ("cert,C",po::value< std::string >(), 
     "Specify CERT as the X509 certificate to use. Defaults to the value "
     "of the EC2_CERT environment variable (if set). Overrides the default.")
    ("url,U",po::value< std::string>(), 
     "Specify URL as the web service URL to use. Defaults to the value of "
     "'https://ec2.amazonaws.com' or to that of the EC2_URL environment "
     "variable (if set). Overrides the default.")
/*      ("region", po::value< std::string>(), "Specify REGION as the web service region to use."
        "This option will override the URL specified by the \"-U URL\" option"
        "and EC2_URL environment variable.")
*/
    ("help,h,?", "this help message")
    ("verbose,v", "verbose output")
    ("debug","Display additional debugging information.")

    ;
}

void optionCommand::complete(const po::options_description &specific) {
  _cmdline_options.add(_general).add(specific);
}

