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
#include "MeshGenerator.h"

/**
 * default constructor
 */
MeshGenerator::MeshGenerator(const std::vector<std::vector<double>>& coor,
		const std::vector<std::vector<int>>& m):
coordinates{coor}, mesh{m}
{
}

/**
 * This is engine for generating the mesh
 */
MeshGenerator::MeshGenerator(const Variables& a){

	const std::vector<double>& dim = a.getDimension();
	const std::vector<int>& num_mesh = a.getNumMesh();

	int num_nodes = (num_mesh[0]+1)*(num_mesh[1]+1)*(num_mesh[2]+1);
	int num_ele = num_mesh[0] * num_mesh[1] * num_mesh[2];

	// resize the coordinates
	coordinates.resize(num_nodes, std::vector<double>(3));

	// resize the mesh
	mesh.resize(num_ele, std::vector<int>(8));

	// openmp parallel for loop
#pragma omp parallel for
    for (int i = 0; i <= num_mesh[0]; i++){

    	// find the index number of the first node with same face on axis z
    	int index_i = i*(num_mesh[1]+1)*(num_mesh[2]+1);

    	// find the z coordinate of the node
    	double coor_z = i*dim[0]/num_mesh[0];

    	for (int j = 0; j <= num_mesh[1]; j++){

    		// find the index number of the first node with same line parallel to axis x
    		int index_j = j*(num_mesh[2]+1);

    		// find the y coordinate of the node
    		double coor_y = j*dim[1]/num_mesh[1];

    		for (int k = 0; k <= num_mesh[2]; k++){

    			// get the index number of desired node
    			int index = index_i + index_j + k;

    			// get the x coordinate of the desired node
    			double coor_x = k*dim[2]/num_mesh[2];

    			// Assign coordinates to the desired node
    			coordinates[index][0] = coor_x;
    			coordinates[index][1] = coor_y;
    			coordinates[index][2] = coor_z;
//    			std::cout << "index: " << index+1 << " " << coor_x;
//    			std::cout << " " << coor_y << " " << coor_z << "\n";
    		}
    	}
	}
//#pragma omp barrier
#pragma omp for
    for (int i = 0; i < num_mesh[0]; i++){

    	// find the number of elements below (with lower z)
    	int index_i = i*num_mesh[1]*num_mesh[2];

    	// find the number of nodes below (with lower z)
    	int node_i = i*(num_mesh[1]+1)*(num_mesh[2]+1);

    	for (int j = 0; j < num_mesh[1]; j++){

    		// find the number of elements with lower y and same z
    		int index_j = j*num_mesh[2];

    		// find the number of nodes with lower y and same z
    		int node_j = j*(num_mesh[2]+1);

    		for (int k = 0; k < num_mesh[2]; k++){

    			// find the index of the desired element
    			int index = index_i + index_j + k;

    			// find the index of the first node of the element
    			int index_nd1 = node_i + node_j + k + 1;

    			// save the index of all nodes
    			mesh[index][0] = index_nd1;
    			mesh[index][1] = mesh[index][0] + 1;
    			mesh[index][3] = mesh[index][0] + num_mesh[2] + 1;
    			mesh[index][2] = mesh[index][3] + 1;
    			mesh[index][4] = mesh[index][0] + (num_mesh[1] + 1)*(num_mesh[2] + 1);
    			mesh[index][5] = mesh[index][4] + 1;
    			mesh[index][7] = mesh[index][4] + num_mesh[2] + 1;
    			mesh[index][6] = mesh[index][7] + 1;
    		}
    	}
    }

}
/**
 * get nodes coordinates
 */
const std::vector<std::vector<double>>& MeshGenerator::getCoordinates() const{
	return coordinates;
}

/**
 * get mesh
 */
const std::vector<std::vector<int>>& MeshGenerator::getMesh() const{
	return mesh;
}
