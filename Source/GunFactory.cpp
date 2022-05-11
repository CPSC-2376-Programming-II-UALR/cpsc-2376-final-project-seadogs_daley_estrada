#include "GunFactory.h"
#include "SingleShot.h"
#include <memory>
#include <vector>

std::unique_ptr<GunFactory> GunFactory::create(GunTypes type )
{
    if (type == GunFactory::GunTypes::singleShot)
        return std::make_unique<SingleShot>();
    //else if (type == GunFactory::GunType::tripleShot)
    //    return std::make_unique <TripleShot>();
    else return NULL;
    return NULL;
}
