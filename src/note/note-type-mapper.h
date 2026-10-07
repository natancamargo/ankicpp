#pragma once

#include "note/note-type-dto.h"
#include "note/note-type.h"
namespace ankicpp {
namespace noteTypeMapper {
NoteTypeDTO modelToDTO(NoteType &model);
NoteType modelFromDTO(NoteTypeDTO &dto);
} // namespace noteTypeMapper
} // namespace ankicpp
