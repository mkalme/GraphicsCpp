#pragma once
#include "../../../ItemSerializer.h"
#include "../../../../Scene/Shape/Traced/TriangleMesh.h"
#include "../../../../Math/Vec3f.h"
#include "../../../../Scene/Shape/Object.h"
#include "../../../../Scene/Surface/Flat/FlatSurface.h"

class TriangleMeshSerializer : public ItemSerializer<Object*>
{
public:
	TriangleMeshSerializer(ItemSerializer<SurfaceResult>* surfaceSerializer) {
		m_surfaceSerializer = surfaceSerializer;
	}

	nlohmann::json Serialize(Object* item) override {
		TriangleMesh* triangleMesh = (TriangleMesh*)item;

		nlohmann::json data;
		nlohmann::json meshArray = nlohmann::json::array();
		for (int i = 0; i < triangleMesh->Count; i++) {
			Triangle t = triangleMesh->Triangles[i];

			nlohmann::json triangle = nlohmann::json::array({
				t.Vertex0.X, t.Vertex0.Y, t.Vertex0.Z,
				t.Vertex1.X, t.Vertex1.Y, t.Vertex1.Z,
				t.Vertex2.X, t.Vertex2.Y, t.Vertex2.Z,});
		
			meshArray.push_back(triangle);
		}

		data["Surface"] = m_surfaceSerializer->Serialize(triangleMesh->Surface);
		data["Mesh"] = meshArray;

		return data;
	}

	Object* Deserialize(nlohmann::json data) override {
		TriangleMesh* triangleMesh = new TriangleMesh();

		nlohmann::json meshArray = data["Mesh"];
		
		bool useCustomNormals = data.contains("CustomNormals");
		nlohmann::json normalArray;
		if (useCustomNormals) {
			normalArray = data["CustomNormals"];
		}

		triangleMesh->Count = meshArray.size() / 9;
		triangleMesh->Triangles = new Triangle[triangleMesh->Count];

		for (int i = 0; i < triangleMesh->Count; i++) {
			Vec3f v0 = Vec3f(meshArray[i * 9], meshArray[i * 9 + 1], meshArray[i * 9 + 2]);
			Vec3f v1 = Vec3f(meshArray[i * 9 + 3], meshArray[i * 9 + 4], meshArray[i * 9 + 5]);
			Vec3f v2 = Vec3f(meshArray[i * 9 + 6], meshArray[i * 9 + 7], meshArray[i * 9 + 8]);

			Triangle triangle;
			if (!useCustomNormals) triangle = Triangle(v0, v1, v2);
			else triangle = Triangle(v0, v1, v2, Vec3f(normalArray[i * 3, i * 3 + 1, i * 3 + 2]));
		
			triangleMesh->Triangles[i] = triangle;
		}

		triangleMesh->Surface = m_surfaceSerializer->Deserialize(data["Surface"]);
		triangleMesh->UseCustomNormals = useCustomNormals;

		return triangleMesh;
	}
private:
	ItemSerializer<SurfaceResult>* m_surfaceSerializer;
};