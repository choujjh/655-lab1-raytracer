cmake_minimum_required(VERSION 3.17)
project(Lab_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab_1 main.cpp Model/Scene/Light/AmbientLight.cpp Model/Scene/Light/AmbientLight.h Model/Scene/Light/DirectionLight.cpp Model/Scene/Light/DirectionLight.h Model/Scene/Light/Light.cpp Model/Scene/Light/Light.h Model/Scene/RenderObj/Object.cpp Model/Scene/RenderObj/Object.h Model/Scene/RenderObj/Plane.cpp Model/Scene/RenderObj/Plane.h Model/Scene/RenderObj/Sphere.cpp Model/Scene/RenderObj/Sphere.h Model/Scene/RenderObj/Triangle.cpp Model/Scene/RenderObj/Triangle.h Model/Scene/Cam.cpp Model/Scene/Cam.h Scene.cpp Scene.h Ops/RenderOps.cpp Ops/RenderOps.h Ops/LinAlgOp.cpp Ops/LinAlgOp.h Model/VecModel/Ray.cpp Model/VecModel/Ray.h Model/VecModel/Vec3.cpp Model/VecModel/Vec3.h Ops/Ops.h Model/Model.h Model/Render/Materials/Material.cpp Model/Render/Materials/Material.h Model/Render/RenderAlg.cpp Model/Render/RenderAlg.h)