#pragma once

#include "template/template.h"
namespace ankicpp {
namespace templateMapper {
TemplateDTO modelToDTO(Template &model);
Template modelFromDTO(TemplateDTO &dto);
} // namespace templateMapper
} // namespace ankicpp
