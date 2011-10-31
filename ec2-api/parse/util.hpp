/*
 * @file   util.hpp
 * @date   2010-07-14
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

#ifndef _xml_parse_util_hpp_
#define _xml_parse_util_hpp_
#include <ec2-api/parse/util/maybe.hpp>
#include <ec2-api/parse/util/show_node_type.hpp>
#include <ec2-api/parse/util/join.hpp>
#include <ec2-api/parse/util/skip.hpp>
#include <ec2-api/parse/util/expect.hpp>
#include <ec2-api/parse/util/required.hpp>
#include <ec2-api/parse/util/optional.hpp>
#include <ec2-api/parse/util/name_element.hpp>
#include <ec2-api/parse/util/cdata.hpp>
#include <ec2-api/parse/util/read_bool.hpp>


#include <strstream>
/** Konvertiert String <s> in einen Wert des Datentyps (chr, char*, long, int, ...)
    @param s

    @return <ReturnValue>
**/
template<class VALUE>
VALUE fromString(const std::string & s)
{
    VALUE tmp;
    std::strstream strBuffer;
    strBuffer.clear();
    strBuffer << s;
    strBuffer >> tmp;
    strBuffer.freeze(false);
    return tmp;
} // Aufruf: type wert = fromString<type>( (char* oder string) wert )

/*
 * Local variables:
 *  tab-width: 2
 *  c-indent-level: 2
 *  c-basic-offset: 2
 * End:
 */
#endif /* _xml_parse_util_hpp_ */
