#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "gfc_vector.h"
#include "gfc_shape.h"

GFC_Vector2D camera_get_position();

GFC_Vector2D camera_get_offset();

void camera_set_position(GFC_Vector2D position);

void camera_apply_bounds();

void camera_set_bounds(GFC_Rect bounds);

void camera_enable_binding(Bool bindCamera);

void camera_set_size(GFC_Vector2D size);

void camera_center_on(GFC_Vector2D target);

#endif
