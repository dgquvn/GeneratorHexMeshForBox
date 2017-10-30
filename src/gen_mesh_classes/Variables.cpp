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
#include "Variables.h"

/**
 * default setting of constructor
 */
Variables::Variables(const std::vector<double>& geo_dim, const std::vector<int>& mesh):
dimensions{geo_dim}, num_mesh{mesh}
{
}

/**
 * static function for update variables
 */
void Variables::updateVar(const std::vector<std::string>& var, std::vector<double>& dim,
		std::vector<int>& n_mesh){
	if (var.size() != 4)
		throw "Wrong number of input for dimension and number of mesh";
	double len;
	int num;
	if (var[0] == "DIM" && var[2] == "NUM"){
		len = std::stod(var[1]);
		num = std::stoi(var[3]);
	}
	else if (var[0] == "NUM" && var[2] == "DIM"){
		len = std::stod(var[3]);
		num = std::stoi(var[1]);
	}
	else
		throw "Wrong format of dimension or mesh";
	dim.push_back(len);
	n_mesh.push_back(num);
}

/**
 * This is for setting variables from InputProperties
 */
Variables::Variables(const InputProperties& input){


	// store the data from InputProperties
	std::unordered_map<std::string, std::vector<std::string>> mp{input.getVar()};

    if (mp.find("LENGTH") != mp.end()){
    	updateVar(mp["LENGTH"], dimensions, num_mesh);
    }
    else
    	throw "Missing Length";

    if (mp.find("WIDTH") != mp.end()){
        updateVar(mp["WIDTH"], dimensions, num_mesh);
    }
    else
        throw "Missing Width";

    if (mp.find("HEIGHT") != mp.end()){
        updateVar(mp["HEIGHT"], dimensions, num_mesh);
    }
    else
        throw "Missing Length";

}

/**
 * get dimension
 */
const std::vector<double> Variables::getDimension() const{
	return dimensions;
}

/**
 * get num_mesh
 */
const std::vector<int>& Variables::getNumMesh() const{
	return num_mesh;
}

