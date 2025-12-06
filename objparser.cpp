// Simple parser program that converts an .obj file 
// to the format used in this tutorial https://www.rastertek.com/dx11win10tut07.html
// 
// Used blender 4.0 to export a 3D model and generate an .obj file.
// The .obj should only use:
//  - UV Coordinates
//  - Normals
// be triangulated and have Z+.

// Not the most efficient or robust parser but it gets the job done for these tutorials.

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

// Used to store vertex position and normal information
struct float3 {
	float x, y, z;
};

// Used to store texture information
struct float2 {
	float u, v;
};

// Used to store face data (as formated in the f section of the .obj file)
// This parser assumes a1/b1/c1 a2/b2/c2 a3/b3/c3

// The f section of the .obj file describes a single triangle, since it has 3 columns of information
// a1,a2,a3 are the indices of the vertices descried in the v section of the file
// same goes for b and c.

// So we will store vertices in the following vector<float3> verts vector
// and use the indices from to access the correct vertices from the the vector. (Look at header == "f" section)

struct face {
	int vert, tex, normal;
};

int main(void) {
	ifstream fin;
	ofstream fout;
	// Supply your own .obj file here
	// TODO: Have the user supply the .obj file and output file from the command line
	fin.open("drybonestexfin.obj");
	fout.open("model.txt");

	int vertexCount{ 0 };

	vector<float3> verts;
	vector<float3> normals;
	vector<float2> textureCoord;

	// We are storing data per vertex, per face
	// So each line of our output file will have the following format:
	// vert.x vert.y vert.z tex.u tex.v normal.x normal.y normal.z

	// Resulting in a total of faces * 3 entries 
	vector<vector<float>> vertexData;

	// We assume a line isnt longer than 128 bytes
	char buffer[128];
	while (fin.getline(buffer, sizeof buffer)) {
		
		// We trust that the .obj file (generated with Blender) follows the format of
		// <type of information> <space> [information...]
		// Type of information could be v, vn, vt.
		// So we insert buffer[i] to the header until a space is found.
		string header;
		int i = 0;
		while (buffer[i] != ' ') {
			header.insert(header.begin() + i, buffer[i]);
			i++;
		}

		// We use stringstream for easier retrieval of the information to our structs
		stringstream s;
		char junk;

		// Supply the current line into the stringstream
		s << buffer;

		// We only care for the vertex positions, texture positions, normal positions and face information
		// For each one, we create a temp float3 or float2 object and supply it with the data
		// Then we push that struct to its corresponding vector.
		if (header == "v") {
			float3 v;

			s >> junk >> v.x >> v.y >> v.z;
			verts.push_back(v);
		}

		if (header == "vt") {
			float2 tex;

			s >> junk >> junk >> tex.u >> tex.v;
			textureCoord.push_back(tex);
		}

		if (header == "vn") {
			float3 vn;

			s >> junk >> junk >> vn.x >> vn.y >> vn.z;
			normals.push_back(vn);
		}

		// Get the indices and store them in a vector<face> object.
		if (header == "f") {
			vector<face> vf;
			s >> junk;
			for (int i = 0; i < 3; i++) {
				face f;
				s >> f.vert >> junk >> f.tex >> junk >> f.normal;
				vf.push_back(f);
			}

			// Access the correct vertex, texture coordinate and normal from the vectors we previously created
			// using the indices described by the face information
			for (int i = 0; i < 3; i++) {
				vertexCount++;
				face f = vf[i];
				
				float3 v = verts[f.vert - 1];
				float2 t = textureCoord[f.tex - 1];
				float3 n = normals[f.normal - 1];

				// Create the line of our format
				vector<float> vData{ v.x, v.y, v.z, t.u, t.v, n.x, n.y, n.z };
				vertexData.push_back(vData);

			}

		}
	}

	// Header information, as described in the tutorial
	fout << "Vertex Count: " << vertexCount << '\n' << endl;
	fout << "Data:" << '\n' << endl;

	// Fill in the rest of the file
	for (const vector<float>& vec : vertexData) {
		for (float data : vec) {
			fout << data << " ";
		}
		fout << endl;
	}


	// Close files we opened
	fout.close();
	fin.close();

	return 0;
}
