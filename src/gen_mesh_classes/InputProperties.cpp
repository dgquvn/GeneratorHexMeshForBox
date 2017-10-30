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
#include "InputProperties.h"

/**
 * default constructor initilized by a two dimensional vector
 */
InputProperties::InputProperties(const std::unordered_map<std::string, std::vector<std::string>>& input_mp):
mp{input_mp}
{
}

/**
 * Get a word or line from the string
 */
std::string InputProperties::getWord(const std::string& line, int& pos){
	std::string word;

	if (pos < 0 || pos >= line.size())
		return word;

	// move forward if it is white space
	while(line[pos] == ' ') { pos++; }

	// the position of next space or the size of line if it is at end
	auto next_space = line.find(' ', pos);
	if (next_space == std::string::npos)
		next_space = line.size();


	word = line.substr(pos, next_space - pos);
	pos = next_space;

	return word;
}

/**
 * read parameters from input file and store the information
 * as {"LENGTH", "DIM", "val", "NUM" "val"}, and the same for
 * key "WIDTH", and "HEIGHT"
 */
InputProperties::InputProperties(const std::string& file_loc){

	std::ifstream file(file_loc);

	// point to the row of mp for adding strings
	std::string key;
	std::vector<std::string> value;

	if (file.is_open()){
		std::string line;
        while(std::getline(file,line)){
        	int pos = 0;
        	std::string word{getWord(line, pos)};

        	while(!word.empty()){
        		std::string word_up{word};

        		// convert the word to upper case to store keys
        		std::transform(word_up.begin(), word_up.end(), word_up.begin(), ::toupper);

        		// look for "MAX_INT" or "_DIVISOR" as the key
        		if (word_up == "LENGTH" || word_up == "WIDTH" || word_up == "HEIGHT"){
        			key = word_up;
        			mp[key] = value;
        		}
        		else if (key.empty())
        			throw("wrong format of input parameters");
        		else
        			mp[key].push_back(word_up);

        		// continue to next word or number
        		word = getWord(line, pos);
        	}
		}

		file.close();
	}
	else{
		throw("wrong input file location");
	}
}

/**
 * return the saved pairs of key and values
 */
const std::unordered_map<std::string, std::vector<std::string>>& InputProperties::getVar() const{
	return mp;
}



