/**
 * @file project.hpp
 * @brief Geometry project
 *
 * @author H. Q. Bovik (hqbovik)
 * @bug Unimplemented
 */

#ifndef _462_GEOMETRY_PROJECT_HPP_
#define _462_GEOMETRY_PROJECT_HPP_

#include "math/camera.hpp"


/*
   A namespace declaration. All project files use this namespace.
   Add this declaration (and its closing) to all source/headers you create.
   Note that all #includes should be BEFORE the namespace declaration.
 */
namespace _462 {

struct Triangle
{
    // index into vertex list of the 3 vertices of this triangle
    unsigned int vertices[3];
};

struct Vertex
{
    // the position of the vertex
    Vector3 position;
    // the normal of the vertex
    Vector3 normal;
    // the texture coordinate of the vertex
    Vector2 texture_coord;
};

struct MeshData
{
    // array of vertices
    Vertex* vertices;
    // size of vertex array
    size_t num_vertices;

    // array of triangles
    Triangle* triangles;
    // size of triangle array
    size_t num_triangles;
};

struct nvtPair
{
	Vector3 vertex;
	Vector3 normal;
	Vector2 texture;
};

// struct for half edge data structure edges
struct heEdge
{
	struct heVertex* startVertex;
	struct heEdge* nextEdge;
	heEdge* pairEdge;
	struct heFace* leftFace;
};

//struct for half edge data structure vertices
struct heVertex
{
	Vector3 point;
	Vector3 normal;
	Vector2 texture;
	heEdge* edge;
};

//struct for half edge data structure faces
struct heFace
{
	heEdge* edge;
};

class GeometryProject
{
public:

    // constructor, invoked when object is created
    GeometryProject();
    // destructor, invoked when object is destroyed
    ~GeometryProject();

    // more detailed specifications for each function are in project.cpp.

    // Initialize the project, loading the mesh from the given filename.
    // Returns true on success.
    bool initialize( const Camera* camera, const MeshData* mesh, const char* texture_filename );
    // Clean up the project, free any memory, etc.
    void destroy();
    // Render the mesh using the given camera.
    void render( const Camera* camera );
    // Subdivide the mesh
    void subdivide();
	void checkMatch(heEdge* edge1, heEdge* edge2);
	void findMatches(heEdge* curEdge, heEdge* compEdge);
	void myDraw();
	Vector3 round(Vector3 vector);
	nvtPair splitInteriorEdge(heEdge* edge);
	nvtPair splitBoundaryEdge(heEdge* edge);
	nvtPair computeEvenInteriorVertex(heEdge* startEdge);
	nvtPair computeEvenBoundaryVertex(heEdge* startEdge);
	void freeFaceList(heFace* faceList);
	void createFace(heFace* tmpFaceList, nvtPair a, nvtPair b, nvtPair c);
	void updateFaceList(heFace* tmpFaceList, int i, nvtPair aPrime, nvtPair bPrime, nvtPair cPrime, nvtPair ab, nvtPair bc, nvtPair ca);


private:

    MeshData mesh;

    // TODO add any other private members/functions here.

    // since this has no meaningful assignment/copy, prevent the compiler from
    // automatically generating those functions
    GeometryProject( const GeometryProject& );
    GeometryProject& operator=( const GeometryProject& );

	heFace* faceList;
	int count;
	int numFaces;
	unsigned char* texture;
	bool hasTexture;
	unsigned int hTex;
};

} /* _462 */

#endif /* _462_GEOMETRY_PROJECT_HPP_ */

