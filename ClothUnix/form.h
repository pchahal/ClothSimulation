#ifndef FD_form_h_
#define FD_form_h_
/* Header file generated with fdesign. */

/**** Callback routines ****/

extern void StructK_callback(FL_OBJECT *, long);
extern void ShearK_callback(FL_OBJECT *, long);
extern void FlexK_callback(FL_OBJECT *, long);
extern void gravityx_callback(FL_OBJECT *, long);
extern void gravityy_callback(FL_OBJECT *, long);
extern void gravityz_callback(FL_OBJECT *, long);
extern void windx_callback(FL_OBJECT *, long);
extern void windy_callback(FL_OBJECT *, long);
extern void windz_callback(FL_OBJECT *, long);
extern void Damping_callback(FL_OBJECT *, long);
extern void Viscous_callback(FL_OBJECT *, long);
extern void VertexMass_callback(FL_OBJECT *, long);
extern void Play_callback(FL_OBJECT *, long);
extern void TimeStep_callback(FL_OBJECT *, long);
extern void Stop_callback(FL_OBJECT *, long);
extern void NextFrame_callback(FL_OBJECT *, long);
extern void CameraX_callback(FL_OBJECT *, long);
extern void CameraY_callback(FL_OBJECT *, long);
extern void CameraZ_callback(FL_OBJECT *, long);
extern void Collision_callback(FL_OBJECT *, long);
extern void Hang_callback(FL_OBJECT *, long);
extern void TransformX_callback(FL_OBJECT *, long);
extern void TransformY_callback(FL_OBJECT *, long);
extern void TransformZ_callback(FL_OBJECT *, long);
extern void Translate_callback(FL_OBJECT *, long);
extern void Scale_callback(FL_OBJECT *, long);
extern void Rotate_callback(FL_OBJECT *, long);
extern void HideObject_callback(FL_OBJECT *, long);
extern void Reset_callback(FL_OBJECT *, long);
extern void ShowClothMesh_callback(FL_OBJECT *, long);
extern void ShowSprings_callback(FL_OBJECT *, long);
extern void ShowVertexMass_callback(FL_OBJECT *, long);


/**** Forms and Objects ****/

typedef struct {
	FL_FORM *form;
	void *vdata;
	long ldata;
	FL_OBJECT *canvas;
	FL_OBJECT *StructK;
	FL_OBJECT *ShearK;
	FL_OBJECT *FlexK;
	FL_OBJECT *gravityx;
	FL_OBJECT *gravityy;
	FL_OBJECT *gravityz;
	FL_OBJECT *windx;
	FL_OBJECT *windy;
	FL_OBJECT *windz;
	FL_OBJECT *Damping;
	FL_OBJECT *Viscous;
	FL_OBJECT *VertexMass;
	FL_OBJECT *quit_button;
	FL_OBJECT *Play_button;
	FL_OBJECT *TimeStep;
	FL_OBJECT *Stop_button;
	FL_OBJECT *NextFrame_button;
	FL_OBJECT *CameraX;
	FL_OBJECT *CameraY;
	FL_OBJECT *CameraZ;
	FL_OBJECT *Collision_button;
	FL_OBJECT *Hang_button;
	FL_OBJECT *TransformX;
	FL_OBJECT *TransformY;
	FL_OBJECT *TransformZ;
	FL_OBJECT *Translate_button;
	FL_OBJECT *Scale_button;
	FL_OBJECT *Rotate_button;
	FL_OBJECT *HideObject;
	FL_OBJECT *Reset;
	FL_OBJECT *ShowClothMesh;
	FL_OBJECT *ShowSprings;
	FL_OBJECT *ShowVertexMass;
} FD_form;

extern FD_form * create_form_form(void);

#endif /* FD_form_h_ */
