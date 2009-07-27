#include "Sky.h"

Sky::Sky()
{
	scale = 10;
	
	object = &perm_object;
	
	object->name = "sky";
	object->vertices = new Vertex[8];
	
	object->v_poss = new Vector3f[8];
	object->v_norms = new Vector3f[8];
	object->v_texts = new Vector2f[8];
	
	object->v_poss[0].init(0,0,0);		//front bottom right
	object->v_poss[1].init(0,0,scale);	//back bottom right
	object->v_poss[2].init(0,scale,scale);	//back top right
	object->v_poss[3].init(0,scale,0);	//front top right
	object->v_poss[4].init(scale,0,0);	//front bottom left
	object->v_poss[5].init(scale,0,scale);	//back bottom left
	object->v_poss[6].init(scale,scale,scale);//back top left
	object->v_poss[7].init(scale,scale,0);	//front top left
	
	/*
	object->v_norms[0].init(1,0,1);
	object->v_norms[1].init(1,0,-1);
	object->v_norms[2].init(1,-1,-1);
	object->v_norms[3].init(1,-1,1);
	object->v_norms[4].init(-1,0,1);
	object->v_norms[5].init(-1,0,-1);
	object->v_norms[6].init(-1,-1,-1);
	object->v_norms[7].init(-1,-1,1);
	*/
	
	for (int i = 0; i < 8; i++)
		object->v_norms[i].normalise();
	
	object->v_texts[0].init(0,0);
	object->v_texts[1].init(1,0);
	object->v_texts[2].init(1,1);
	object->v_texts[3].init(0,1);
	object->v_texts[4].init(0,0);
	object->v_texts[5].init(1,0);
	object->v_texts[6].init(1,1);
	object->v_texts[7].init(0,1);
	
	for (int i = 0; i < 8; i++) {
		object->vertices[i].pos = &object->v_poss[1];
		object->vertices[i].normal = &object->v_norms[1];
		object->vertices[i].text = &object->v_texts[1];
	}
	
	object->face_count = 5;
	object->faces = new Face[5];
	
	object->faces[0].vertex_count = 4;
	object->faces[0].vertices = new Vertex[4];
	object->faces[0].vertices[0] = object->vertices[0];
	object->faces[0].vertices[1] = object->vertices[1];
	object->faces[0].vertices[2] = object->vertices[2];
	object->faces[0].vertices[3] = object->vertices[3];
	
	object->faces[1].vertex_count = 4;
	object->faces[1].vertices = new Vertex[4];
	object->faces[1].vertices[0] = object->vertices[5];
	object->faces[1].vertices[1] = object->vertices[1];
	object->faces[1].vertices[2] = object->vertices[2];
	object->faces[1].vertices[3] = object->vertices[6];
	
	object->faces[2].vertex_count = 4;
	object->faces[2].vertices = new Vertex[4];
	object->faces[2].vertices[0] = object->vertices[4];
	object->faces[2].vertices[1] = object->vertices[5];
	object->faces[2].vertices[2] = object->vertices[6];
	object->faces[2].vertices[3] = object->vertices[7];
	
	object->faces[3].vertex_count = 4;
	object->faces[3].vertices = new Vertex[4];
	object->faces[3].vertices[0] = object->vertices[0];
	object->faces[3].vertices[1] = object->vertices[4];
	object->faces[3].vertices[2] = object->vertices[7];
	object->faces[3].vertices[3] = object->vertices[3];
	
	object->faces[4].vertex_count = 4;
	object->faces[4].vertices = new Vertex[4];
	object->faces[4].vertices[0] = object->vertices[2];
	object->faces[4].vertices[1] = object->vertices[3];
	object->faces[4].vertices[2] = object->vertices[6];
	object->faces[4].vertices[3] = object->vertices[7];
}

void Sky::set_scale(float scale)
{
	this->scale = scale;
	
	object->v_poss[0].init(0,0,0);		//front bottom right
	object->v_poss[1].init(0,0,scale);	//back bottom right
	object->v_poss[2].init(0,scale,scale);	//back top right
	object->v_poss[3].init(0,scale,0);	//front top right
	object->v_poss[4].init(scale,0,0);	//front bottom left
	object->v_poss[5].init(scale,0,scale);	//back bottom left
	object->v_poss[6].init(scale,scale,scale);//back top left
	object->v_poss[7].init(scale,scale,0);	//front top left
}
