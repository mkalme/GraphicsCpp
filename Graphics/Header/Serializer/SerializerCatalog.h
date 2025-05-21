#pragma once
#include <map>
#include <string>
#include "ItemSerializer.h"
#include "SerializerId.h"
#include "Math/Vec3fSerializer.h"
#include "Math/Vec2fSerializer.h"
#include "Math/RotationSerializer.h"
#include "Scene/Camera/PerspectiveCameraSerializer.h"
#include "Scene/Camera/ParallelCameraSerializer.h"
#include "Scene/Sky/SolidColorSkySerializer.h"
#include "Scene/Sky/SkyBoxSerializer.h"
#include "Scene/Light/PointLightSerializer.h"
#include "Scene/Light/DirectionalLightSerializer.h"
#include "Scene/Surface/SurfaceResultSerializer.h"
#include "Scene/Surface/Flat/SolidFlatSurfaceSerializer.h"
#include "Scene/Surface/Flat/CheckedFlatSurfaceSerializer.h"
#include "Scene/Surface/Flat/RotatedFlatSurfaceSerializer.h"
#include "Scene/Surface/Flat/LineFlatSurfaceSerializer.h"
#include "Scene/Surface/Uv/SolidUvSurfaceSerializer.h"
#include "Scene/Surface/Uv/GeneratedSquareUvSurfaceSerializer.h"
#include "Scene/Surface/Uv/TexturedUvSurfaceSerializer.h"
#include "Scene/Surface/Uv/CheckedUvSurfaceSerializer.h"
#include "KeyedItemSerializer.h"
#include "Scene/Shape/Traced/SphereSerializer.h"
#include "Scene/Shape/Traced/PlaneSerializer.h"
#include "Scene/Shape/Traced/CylinderSerializer.h"
#include "Scene/Shape/Traced/TriangleMeshSerializer.h"
#include "Scene/Shape/Traced/BoxSerializer.h"
#include "Scene/Shape/Traced/PrismSerializer.h"
#include "Scene/Shape/Traced/PyramidSerializer.h"
#include "Scene/Shape/Traced/ConeSerializer.h"
#include "Scene/Shape/Marched/TorusSerializer.h"
#include "Scene/Shape/Marched/MarchedSphereSerializer.h"
#include "Scene/Shape/Marched/MarchedConeSerializer.h"
#include "Scene/Shape/Marched/MarchedCylinderSerializer.h"
#include "Scene/Shape/Marched/Composite/RepeatedMarchedObjectSerializer.h"
#include "Scene/Shape/Traced/FlatPolygonSerializer.h"
#include "Scene/Shape/Set/SetDifferenceObjectSerializer.h"
#include "Scene/Shape/Set/UnionObjectSerializer.h"
#include "Scene/Shape/Composite/TransformableObjectSerializer.h"
#include "Scene/Fog/FormulaFogSerializer.h"
#include "../Utilities/Reference.h"

class SerializerCatalog
{
public:
	ItemSerializer<Vec3f>* Vec3f = new Vec3fSerializer();
	ItemSerializer<Vec2f>* Vec2f = new Vec2fSerializer();
	ItemSerializer<Rotation>* Rotation = new RotationSerializer();
	ItemSerializer<SurfaceResult>* SurfaceResult;

	KeyedItemSerializer<FlatSurface*>* FlatSurfaces;
	KeyedItemSerializer<UvSurface*>* UvSurfaces;
	KeyedItemSerializer<Object*>* Objects;
	KeyedItemSerializer<Camera*>* Cameras;
	KeyedItemSerializer<Light*>* Lights;
	KeyedItemSerializer<Fog*>* Fogs;
	KeyedItemSerializer<Sky*>* Skies;

	std::map<std::string, ItemSerializer<Camera*>*>* CameraMap = new std::map<std::string, ItemSerializer<Camera*>*>();
	std::map<std::string, ItemSerializer<Object*>*>* ObjectMap = new std::map<std::string, ItemSerializer<Object*>*>();
	std::map<std::string, ItemSerializer<Light*>*>* LightMap = new std::map<std::string, ItemSerializer<Light*>*>();
	std::map<std::string, ItemSerializer<Fog*>*>* FogMap = new std::map<std::string, ItemSerializer<Fog*>*>();
	std::map<std::string, ItemSerializer<Sky*>*>* SkyMap = new std::map<std::string, ItemSerializer<Sky*>*>();
	std::map<std::string, ItemSerializer<FlatSurface*>*>* FlatSurfaceMap = new std::map<std::string, ItemSerializer<FlatSurface*>*>();
	std::map<std::string, ItemSerializer<UvSurface*>*>* UvSurfaceMap = new std::map<std::string, ItemSerializer<UvSurface*>*>();

	Reference<std::string>* CurrentDirectory = new Reference<std::string>();

	SerializerCatalog() {
		SurfaceResult = new SurfaceResultSerializer(Vec3f);

		FlatSurfaces = new KeyedItemSerializer<FlatSurface*>(FlatSurfaceMap);
		UvSurfaces = new KeyedItemSerializer<UvSurface*>(UvSurfaceMap);
		Objects = new KeyedItemSerializer<Object*>(ObjectMap);
		Cameras = new KeyedItemSerializer<Camera*>(CameraMap);
		Fogs = new KeyedItemSerializer<Fog*>(FogMap);
		Lights = new KeyedItemSerializer<Light*>(LightMap);
		Skies = new KeyedItemSerializer<Sky*>(SkyMap);

		CameraMap->emplace(SerializerId::Id[typeid(PerspectiveCamera)], new PerspectiveCameraSerializer(Vec3f, Rotation));
		CameraMap->emplace(SerializerId::Id[typeid(ParallelCamera)], new ParallelCameraSerializer(Vec3f, Rotation));

		ObjectMap->emplace(SerializerId::Id[typeid(Sphere)], new SphereSerializer(Vec3f, UvSurfaces));
		ObjectMap->emplace(SerializerId::Id[typeid(Plane)], new PlaneSerializer(Vec3f, FlatSurfaces));
		ObjectMap->emplace(SerializerId::Id[typeid(Cylinder)], new CylinderSerializer(Vec3f, UvSurfaces));
		ObjectMap->emplace(SerializerId::Id[typeid(TriangleMesh)], new TriangleMeshSerializer(SurfaceResult));
		ObjectMap->emplace(SerializerId::Id[typeid(Box)], new BoxSerializer(Vec3f, SurfaceResult));
		ObjectMap->emplace(SerializerId::Id[typeid(Prism)], new PrismSerializer(Vec3f, SurfaceResult));
		ObjectMap->emplace(SerializerId::Id[typeid(Pyramid)], new PyramidSerializer(Vec3f, SurfaceResult));
		ObjectMap->emplace(SerializerId::Id[typeid(Cone)], new ConeSerializer(Vec3f, UvSurfaces));
		ObjectMap->emplace(SerializerId::Id[typeid(Torus)], new TorusSerializer(Vec3f, UvSurfaces));
		ObjectMap->emplace(SerializerId::Id[typeid(MarchedSphere)], new MarchedSphereSerializer(Vec3f, UvSurfaces));
		ObjectMap->emplace(SerializerId::Id[typeid(MarchedCone)], new MarchedConeSerializer(Vec3f, UvSurfaces));
		ObjectMap->emplace(SerializerId::Id[typeid(MarchedCylinder)], new MarchedCylinderSerializer(Vec3f, UvSurfaces));
		ObjectMap->emplace(SerializerId::Id[typeid(RepeatedMarchedObject)], new RepeatedMarchedObjectSerializer(Vec2f, Objects));
		ObjectMap->emplace(SerializerId::Id[typeid(FlatPolygon)], new FlatPolygonSerializer(Vec3f, FlatSurfaces));
		ObjectMap->emplace(SerializerId::Id[typeid(SetDifferenceObject)], new SetDifferenceObjectSerializer(Objects));
		ObjectMap->emplace(SerializerId::Id[typeid(UnionObject)], new UnionObjectSerializer(Objects));
		ObjectMap->emplace(SerializerId::Id[typeid(TransformableObject)], new TransformableObjectSerializer(Vec2f, Vec3f, Rotation, Objects));

		LightMap->emplace(SerializerId::Id[typeid(PointLight)], new PointLightSerializer(Vec3f));
		LightMap->emplace(SerializerId::Id[typeid(DirectionalLight)], new DirectionalLightSerializer(Vec3f));

		FogMap->emplace(SerializerId::Id[typeid(FormulaFog)], new FormulaFogSerializer(Vec3f));

		SkyMap->emplace(SerializerId::Id[typeid(SolidColorSky)], new SolidColorSkySerializer(Vec3f));
		SkyMap->emplace(SerializerId::Id[typeid(SkyBox)], new SkyBoxSerializer(Vec3f, CurrentDirectory));

		FlatSurfaceMap->emplace(SerializerId::Id[typeid(SolidFlatSurface)], new SolidFlatSurfaceSerializer(SurfaceResult));
		FlatSurfaceMap->emplace(SerializerId::Id[typeid(CheckedFlatSurface)], new CheckedFlatSurfaceSerializer(SurfaceResult));
		FlatSurfaceMap->emplace(SerializerId::Id[typeid(RotatedFlatSurface)], new RotatedFlatSurfaceSerializer(Rotation, FlatSurfaces));
		FlatSurfaceMap->emplace(SerializerId::Id[typeid(LineFlatSurface)], new LineFlatSurfaceSerializer(SurfaceResult));

		UvSurfaceMap->emplace(SerializerId::Id[typeid(SolidUvSurface)], new SolidUvSurfaceSerializer(SurfaceResult));
		UvSurfaceMap->emplace(SerializerId::Id[typeid(GeneratedSquareUvSurface)], new GeneratedSquareUvSurfaceSerializer(Vec3f, SurfaceResult));
		UvSurfaceMap->emplace(SerializerId::Id[typeid(TexturedUvSurface)], new TexturedUvSurfaceSerializer(SurfaceResult, CurrentDirectory));
		UvSurfaceMap->emplace(SerializerId::Id[typeid(CheckedUvSurface)], new CheckedUvSurfaceSerializer(SurfaceResult));
	}
};