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

#ifndef VARIABLES_H_
#define VARIABLES_H_

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "InputProperties.h"

/**
 * A class for converting data from unordered_map to needed variables
 */
class Variables{
public:

	/**
	 * default constructor for testing files
	 * @param geo_dim, mesh correspond to private members, namely
	 * dimension, num_mesh
	 */
	Variables(const std::vector<double>& geo_dim, const std::vector<int>& mesh);

	/**
	 * constructor for converting data from general input to needed variables
	 * @param input a instance of class GeneralInputProperties with input file parameters
	 */
	Variables(const InputProperties& input);

	/**
	 * static function for update dimension and num_mesh
	 */
	static void updateVar(const std::vector<std::string>& var, std::vector<double>& dim,
			std::vector<int>& n_mesh);

	/**
	 * get dimension
	 */
    const std::vector<double> getDimension() const;

    /**
     * get number of mesh
     */
    const std::vector<int>& getNumMesh() const;

private:

	/**
	 * the dimension of the box as ordered by length, width, and height
	 */
	std::vector<double> dimensions;

	/**
	 * the number of mesh for each dimension as ordered by length, width, and height
	 */
	std::vector<int> num_mesh;
};




#endif /* VARIABLES_H_ */
