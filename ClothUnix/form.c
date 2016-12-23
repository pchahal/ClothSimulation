/* Form definition file generated with fdesign. */

#include "forms.h"
#include <stdlib.h>
#include "form.h"

FD_form *create_form_form(void)
{
  FL_OBJECT *obj;
  FD_form *fdui = (FD_form *) fl_calloc(1, sizeof(*fdui));

  fdui->form = fl_bgn_form(FL_NO_BOX, 600, 800);
  obj = fl_add_box(FL_UP_BOX,0,0,600,800,"");
  fdui->canvas = obj = fl_add_glcanvas(FL_NORMAL_CANVAS,10,10,590,400,"");
  fdui->StructK = obj = fl_add_input(FL_FLOAT_INPUT,80,480,60,30,"Structural");
    fl_set_object_callback(obj,StructK_callback,0);
  fdui->ShearK = obj = fl_add_input(FL_FLOAT_INPUT,80,520,60,30,"Shear       ");
    fl_set_object_callback(obj,ShearK_callback,0);
  fdui->FlexK = obj = fl_add_input(FL_FLOAT_INPUT,80,560,60,30,"Bending    ");
    fl_set_object_callback(obj,FlexK_callback,0);
  obj = fl_add_text(FL_NORMAL_TEXT,20,450,120,20,"Spring Stiffness");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,260,420,160,20,"External Forces");
    fl_set_object_lsize(obj,FL_NORMAL_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_NORMAL_STYLE+FL_EMBOSSED_STYLE);
  fdui->gravityx = obj = fl_add_input(FL_FLOAT_INPUT,270,450,40,30,"X");
    fl_set_object_callback(obj,gravityx_callback,0);
  fdui->gravityy = obj = fl_add_input(FL_FLOAT_INPUT,330,450,40,30,"Y");
    fl_set_object_callback(obj,gravityy_callback,0);
  fdui->gravityz = obj = fl_add_input(FL_FLOAT_INPUT,390,450,40,30,"Z");
    fl_set_object_callback(obj,gravityz_callback,0);
  obj = fl_add_text(FL_NORMAL_TEXT,160,450,90,20,"Gravity Vector");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->windx = obj = fl_add_input(FL_FLOAT_INPUT,270,480,40,30,"X");
    fl_set_object_callback(obj,windx_callback,0);
  fdui->windy = obj = fl_add_input(FL_FLOAT_INPUT,330,480,40,30,"Y");
    fl_set_object_callback(obj,windy_callback,0);
  fdui->windz = obj = fl_add_input(FL_FLOAT_INPUT,390,480,40,30,"Z");
    fl_set_object_callback(obj,windz_callback,0);
  obj = fl_add_text(FL_NORMAL_TEXT,160,480,80,20,"Wind Vector");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->Damping = obj = fl_add_input(FL_FLOAT_INPUT,270,520,80,30,"Spring Damping       ");
    fl_set_object_callback(obj,Damping_callback,0);
  fdui->Viscous = obj = fl_add_input(FL_FLOAT_INPUT,270,550,80,30,"Viscous Damping    ");
    fl_set_object_callback(obj,Viscous_callback,0);
  fdui->VertexMass = obj = fl_add_input(FL_FLOAT_INPUT,80,600,60,30,"mass       ");
    fl_set_object_callback(obj,VertexMass_callback,0);
  fdui->quit_button = obj = fl_add_button(FL_NORMAL_BUTTON,10,760,90,30,"Quit");
  fdui->Play_button = obj = fl_add_button(FL_PUSH_BUTTON,100,760,110,30,"Play");
    fl_set_object_callback(obj,Play_callback,0);
  fdui->TimeStep = obj = fl_add_input(FL_FLOAT_INPUT,510,760,60,30,"Time Step");
    fl_set_object_callback(obj,TimeStep_callback,0);
  fdui->Stop_button = obj = fl_add_button(FL_PUSH_BUTTON,210,760,120,30,"Stop");
    fl_set_object_callback(obj,Stop_callback,0);
  fdui->NextFrame_button = obj = fl_add_button(FL_NORMAL_BUTTON,330,760,120,30,"Next Frame");
    fl_set_object_callback(obj,NextFrame_callback,0);
  fdui->CameraX = obj = fl_add_input(FL_FLOAT_INPUT,180,610,120,30,"X");
    fl_set_object_callback(obj,CameraX_callback,0);
  fdui->CameraY = obj = fl_add_input(FL_FLOAT_INPUT,180,640,120,30,"Y");
    fl_set_object_callback(obj,CameraY_callback,0);
  fdui->CameraZ = obj = fl_add_input(FL_FLOAT_INPUT,180,670,120,30,"Z");
    fl_set_object_callback(obj,CameraZ_callback,0);
  fdui->Collision_button = obj = fl_add_roundbutton(FL_PUSH_BUTTON,20,630,120,30,"Collsion");
    fl_set_object_callback(obj,Collision_callback,0);
  fdui->Hang_button = obj = fl_add_roundbutton(FL_PUSH_BUTTON,20,660,130,30,"Hang Cloth");
    fl_set_object_callback(obj,Hang_callback,0);
  obj = fl_add_text(FL_NORMAL_TEXT,180,590,100,20,"Camera Position");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,460,420,120,20,"Object Properties");
    fl_set_object_lsize(obj,FL_NORMAL_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_NORMAL_STYLE+FL_EMBOSSED_STYLE);
  obj = fl_add_text(FL_NORMAL_TEXT,30,420,120,20,"Cloth Parameters");
    fl_set_object_lsize(obj,FL_NORMAL_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_NORMAL_STYLE+FL_EMBOSSED_STYLE);
  fdui->TransformX = obj = fl_add_input(FL_FLOAT_INPUT,470,450,90,30,"X");
    fl_set_object_callback(obj,TransformX_callback,0);
  fdui->TransformY = obj = fl_add_input(FL_FLOAT_INPUT,470,480,90,30,"Y");
    fl_set_object_callback(obj,TransformY_callback,0);
  fdui->TransformZ = obj = fl_add_input(FL_FLOAT_INPUT,470,510,90,30,"Z");
    fl_set_object_callback(obj,TransformZ_callback,0);
  fdui->Translate_button = obj = fl_add_button(FL_NORMAL_BUTTON,470,550,90,30,"Translate");
    fl_set_object_callback(obj,Translate_callback,0);
  fdui->Scale_button = obj = fl_add_button(FL_NORMAL_BUTTON,470,590,90,30,"Scale");
    fl_set_object_callback(obj,Scale_callback,0);
  fdui->Rotate_button = obj = fl_add_button(FL_NORMAL_BUTTON,470,630,90,30,"Rotate");
    fl_set_object_callback(obj,Rotate_callback,0);
  fdui->HideObject = obj = fl_add_button(FL_PUSH_BUTTON,100,710,110,30,"Hide Objects");
    fl_set_object_callback(obj,HideObject_callback,0);
  fdui->Reset = obj = fl_add_button(FL_NORMAL_BUTTON,10,710,90,30,"Reset");
    fl_set_object_callback(obj,Reset_callback,0);
  fdui->ShowClothMesh = obj = fl_add_button(FL_PUSH_BUTTON,450,710,120,30,"Show Cloth Mesh");
    fl_set_object_callback(obj,ShowClothMesh_callback,0);
  fdui->ShowSprings = obj = fl_add_button(FL_PUSH_BUTTON,210,710,120,30,"Show Springs");
    fl_set_object_callback(obj,ShowSprings_callback,0);
  fdui->ShowVertexMass = obj = fl_add_button(FL_PUSH_BUTTON,330,710,120,30,"Show Vertex Mass");
    fl_set_object_callback(obj,ShowVertexMass_callback,0);
  fl_end_form();

  fdui->form->fdui = fdui;

  return fdui;
}
/*---------------------------------------*/

