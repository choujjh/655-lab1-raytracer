//
// Created by chouj on 3/7/2021.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H


#include "../../Model/Vec/Vec3.h"
#include "MaterialComponent/MatComponent.h"

class BaseMaterial {
private:
    MatComponent<Vec3>* Diff_Refl_Transm;
    MatComponent<Vec3>* Rough_Gloss_Transl;
    MatComponent<Vec3>* color;
    MatComponent<Vec3>* KGLS_IOR_gamma;
public:
    BaseMaterial(MatComponent<Vec3> *diffReflTransm, MatComponent<Vec3> *glossTransl, MatComponent<Vec3> *color,
                 MatComponent<Vec3> *kglsIorGamma);

    double diffuse(Vec2 uv){
        return Diff_Refl_Transm->getColor(uv).x;
    }
    double reflective(Vec2 uv){
        return Diff_Refl_Transm->getColor(uv).y;
    }
    double transmission(Vec2 uv){
        return Diff_Refl_Transm->getColor(uv).z;
    }
    double roughness(Vec2 uv){
        return Rough_Gloss_Transl->getColor(uv).x;
    }
    double gloss(Vec2 uv){
        return Rough_Gloss_Transl->getColor(uv).y;
    }
    double translucency(Vec2 uv){
        return Rough_Gloss_Transl->getColor(uv).z;
    }
    double kgls(Vec2 uv){
        return KGLS_IOR_gamma->getColor(uv).x;
    }
    double ior(Vec2 uv){
        return KGLS_IOR_gamma->getColor(uv).y;
    }
    double gamma(Vec2 uv){
        return Rough_Gloss_Transl->getColor(uv).y;
    }
    Vec3 getColor(Vec2 uv){
        return color->getColor(uv);
    }
};


#endif //RAYTRACER_MATERIAL_H
