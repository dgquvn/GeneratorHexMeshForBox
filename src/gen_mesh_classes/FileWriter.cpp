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
#include "FileWriter.h"

/**
 * template member function for output data
 */
template <typename T>
void FileWriter::writing(const std::vector<std::vector<T>>& a, const std::string& name,
		const std::string& file_loc){
	std::ofstream file(file_loc);
	if (file.is_open()){
		file << "c\n" << name << "\n*echo off\n";

		for (int i = 0; i < a.size(); i++){
			file << "\t" << i+1;
			for (int j = 0; j < a[i].size(); j++){
				file << "\t" << a[i][j];
			}
			file << "\n";
		}
		file << "*echo on\nc ";
		file.close();
	}
	else{
		throw("Not a output file");
	}
}
/**
 * This function write output log to output file
 */
void FileWriter::writer(const std::vector<std::vector<double>>& coor,
		const std::vector<std::vector<int>>& mesh,
		const std::string& coor_loc, const std::string& incid_loc){
	// output coordinates
	writing(coor, "coordinates", coor_loc);

	// output mesh/incidences
	writing(mesh, "incidences", incid_loc);
}



