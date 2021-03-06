
/**----------------------------------------------------------------------------
 Copyright (c) 2015-, UT-Battelle, LLC
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.

 * Neither the name of fern nor the names of its
 contributors may be used to endorse or promote products derived from
 this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 Author(s): Guoqiang Deng (dgquvn <at> gmail <dot> com)
 -----------------------------------------------------------------------------*/
#define BOOST_TEST_MODULE TEST_WRITING_TO_FILE
#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include "../../gen_mesh_classes/FileWriter.h"
#include "FizzBuzz_config.hpp"

/**
 * test writing to outputfile from output log
 */
BOOST_AUTO_TEST_CASE(test_writer){

	// subdirectory for outputfile
    std::string fileloc_rest{"/src/FizzBuzz_classes/tests/data/output.txt"};

    // source file diectory
    std::string source_dir{FizzBuzz_source_dir};

    // full directory
    std::string fileloc{source_dir + fileloc_rest};

    // log
    std::vector<std::string> log{"who", "are", "you"};

    FileWriter w;

    // output log to output file
    w.writer(log, fileloc);

    std:: ifstream file(fileloc);

    // check output file content
    if (file.is_open()){
    	std::string line;
    	for (int i = 0; i < 3; i++){
    		std::getline(file, line);
    		BOOST_CHECK_EQUAL(line, log[i]);
    	}
    	file.close();
    }
}



