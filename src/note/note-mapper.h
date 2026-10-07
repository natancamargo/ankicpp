#pragma once

#include "note/note-dto.h"
#include "note/note.h"
namespace ankicpp {
namespace noteMapper {
NoteDTO modelToDTO(Note &model);
Note modelFromDTO(NoteDTO &dto);
} // namespace noteMapper
} // namespace ankicpp
