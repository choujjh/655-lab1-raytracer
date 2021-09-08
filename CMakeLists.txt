cmake_minimum_required(VERSION 3.17)
project(Lab_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab_1
        main.cpp
        Scene/Light/AmbientLight.cpp
        Scene/Light/AmbientLight.h
        Scene/Light/DirectionLight.cpp
        Scene/Light/DirectionLight.h
        Scene/Light/Light.cpp
        Scene/Light/Light.h

        Scene/RenderObj/Object.cpp
        Scene/RenderObj/Object.h
        Scene/RenderObj/Plane.cpp
        Scene/RenderObj/Plane.h
        Scene/RenderObj/Sphere.cpp
        Scene/RenderObj/Sphere.h
        Scene/RenderObj/Triangle.cpp
        Scene/RenderObj/Triangle.h

        Scene/Materials/Material.cpp
        Scene/Materials/Material.h

        Scene/Scene.cpp
        Scene/Scene.h

        Scene/Cam.cpp
        Scene/Cam.h
        Render/RenderController.cpp
        Render/RenderController.h

        Model/RenderCompCreator.cpp
        Model/RenderCompCreator.h

        Model/Ops/RenderOps.cpp
        Model/Ops/RenderOps.h
        Model/Ops/LinAlgOp.cpp
        Model/Ops/LinAlgOp.h
        Model/Vec/Ray.cpp
        Model/Vec/Ray.h
        Model/Vec/Vec3.cpp
        Model/Vec/Vec3.h

        Model/Material/MatComponent.cpp
        Model/Material/MatComponent.h
        Model/Material/MatCompSolid.cpp
        Model/Material/MatCompSolid.h

        Model/File/ImageFileManager.cpp
        Model/File/ImageFileManager.h
        Model/File/PPMFileManager.cpp
        Model/File/PPMFileManager.h

        Render/RenderController.cpp
        Render/RenderController.h
        Render/Integrator.cpp
        Render/Integrator.h

        )