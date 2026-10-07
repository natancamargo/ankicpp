#pragma once

#include "field/field-dto.h"
#include "field/field.h"
namespace ankicpp {
namespace fieldMapper {
FieldDTO modelToDTO(Field &model);
Field modelFromDTO(FieldDTO &dto);
} // namespace fieldMapper
} // namespace ankicpp
