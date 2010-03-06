#include "LuaBinder.h"

#include "Block.h"
#include "Block3D.h"
#include "Block2D.h"
#include "Vector3f.h"
#include "Vector2f.h"
#include "ModelLoader.h"
#include "Obj.h"
#include "Texture.h"
#include "Controller.h"
#include "Camera.h"
#include "Sky.h"
#include "BlockFactory.h"
#include "Block3DImaginary.h"
#include "World.h"
#include "Display.h"
#include "Buttons.h"
#include "AudioFile.h"
#include "AudioMixer.h"
#include "HasPosDir3D.h"

void LuaBinder::bind(lua_State *l)
{
	
	// Export our classes with luaBind
	
	luabind::module(l) [
		luabind::class_<Vector3f>("Vector3f")
			.def(luabind::constructor<float,float,float>())
			.def_readwrite("x", &Vector3f::x)
			.def_readwrite("y", &Vector3f::y)
			.def_readwrite("z", &Vector3f::z)
			.def("normalise", &Vector3f::normalise)
			.def("magnitude", &Vector3f::magnitude)
			/*.def(luabind::self + Vector3f())
			.def(luabind::self * float())*/
	];
	
	luabind::module(l) [
		luabind::class_<Vector2f>("Vector2f")
			.def(luabind::constructor<float,float>())
			.def_readwrite("x", &Vector2f::x)
			.def_readwrite("y", &Vector2f::y)
	];
	
	luabind::module(l) [
		luabind::class_<Vector2i>("Vector2i")
			.def(luabind::constructor<int,int>())
			.def_readwrite("x", &Vector2i::x)
			.def_readwrite("y", &Vector2i::y)
	];
	
	luabind::module(l) [
		luabind::class_<Timer>("Timer")
			.def("get_time", &Timer::get_time)
			.def("time_since", &Timer::time_since)
	];
	
	luabind::module(l) [
		luabind::class_<HasPosDir3D>("HasPosDir3D")
		.def("get_pos", &HasPosDir3D::get_pos)
		.def("set_pos", &HasPosDir3D::set_pos)
		.def("get_dir", &HasPosDir3D::get_dir)
		.def("set_dir", &HasPosDir3D::set_dir)
	];
	
	luabind::module(l) [
		luabind::class_<Block>("Block")
	];
	
	luabind::module(l) [
		luabind::class_<Block3D, HasPosDir3D>("Block3D")
			.def("move", &Block3D::move)
			.def("rotate", &Block3D::rotate)
			.def("get_rot", &Block3D::get_rot)
			.def("set_rot", &Block3D::set_rot)
			.def("get_pos", &Block3D::get_pos)
			.def("set_pos", &Block3D::set_pos)
			.def("get_dir", &Block3D::get_dir)
			.def("set_dir", &Block3D::set_dir)
			.def("change_dir", &Block3D::change_dir)
			.def("nudge", &Block3D::nudge)
			.def("set_offset", &Block3D::set_offset)
			.def("collide", &Block3D::collide)
			.def("add_child", &Block3D::add_child)
			.def("set_scale", &Block3D::set_scale)
			.def("clear_children", &Block3D::clear_children)
	];
	
	luabind::module(l) [
		luabind::class_<Block3DImaginary, Block3D>("Block3DImaginary")
		  .def("toggle_debug", &Block3DImaginary::toggle_debug)
	];
	
	luabind::module(l) [
		luabind::class_<Block3DFlat, HasPosDir3D>("Block3DFlat")
			.def("move", &Block3DFlat::move)
			.def("rotate", &Block3DFlat::rotate)
			.def("set_depth", &Block3DFlat::set_pos)
			.def("set_tex_size", &Block3DFlat::set_tex_size)
			.def("get_pos", &Block3DFlat::get_pos)
			.def("set_transparency", &Block3DFlat::set_transparency)
			.def("change_size", &Block3DFlat::change_size)
			.def("set_rel_centre", &Block3DFlat::set_rel_centre)
	];
	
	luabind::module(l) [
		luabind::class_<Block2D>("Block2D")
			.def("move", &Block2D::move)
			.def("rotate", &Block2D::rotate)
			.def("set_depth", &Block2D::set_depth)
			.def("set_tex_size", &Block2D::set_tex_size)
			.def("get_pos", &Block2D::get_pos)
			.def("set_pos", &Block2D::set_pos)
	];
	
	luabind::module(l) [
		luabind::class_<Block2DText, Block2D>("Block2DText")
	];
	
	luabind::module(l) [
		luabind::class_<Floor>("Floor")
			.def("get_height", &Floor::get_height)
			.def("get_size", &Floor::get_size)
	];
	
	luabind::module(l) [
		luabind::class_<Sky>("Sky")
			.def("set_scale", &Sky::set_scale)
	];
	
	luabind::module(l) [
		luabind::class_<BlockFactory>("BlockFactory")
			.def("new_block3d", &BlockFactory::new_block3d)
			.def("new_character", &BlockFactory::new_character)
			.def("new_blockHUD", &BlockFactory::new_blockHUD)
			.def("new_blockText", &BlockFactory::new_blockText)
			.def("new_floor", &BlockFactory::new_floor)
			.def("new_sky", &BlockFactory::new_sky)
			.def("new_imaginary_block", &BlockFactory::new_imaginary_block)
			.def("new_flat_block", &BlockFactory::new_flat_block)
			.def("remove_blockText", &BlockFactory::remove_blockText)
			.def("remove_blockHUD", &BlockFactory::remove_blockHUD)
			.def("remove_flat_block", &BlockFactory::remove_flat_block)
			.def("new_distance_block", &BlockFactory::new_distance_block)
			.def("clear_all", &BlockFactory::clear_all)
			.def("remove_3d_block", &BlockFactory::remove_3d_block)
	];
	
	luabind::module(l) [
		luabind::class_<Camera>("Camera")
			.def("follow", &Camera::follow)
			.def("set_height", &Camera::set_height)
			.def("set_distance", &Camera::set_distance)
	];
	
	luabind::module(l) [
		luabind::class_<Display>("Display")
			.def("get_camera", &Display::get_camera)
			.def("get_width", &Display::get_width)
			.def("get_height", &Display::get_height)
	];
	
	luabind::module(l) [
		luabind::class_<Controller>("Controller")
			.def(luabind::constructor<string>())
	];
	
	luabind::module(l) [
		luabind::class_<Buttons>("Buttons")
			.def_readonly("up", &Buttons::up)
			.def_readonly("down", &Buttons::down)
			.def_readonly("right", &Buttons::right)
			.def_readonly("left", &Buttons::left)
			.def_readonly("space", &Buttons::space)
			.def_readonly("a", &Buttons::a)
			.def_readonly("s", &Buttons::s)
			.def_readonly("w", &Buttons::w)
			.def_readonly("d", &Buttons::d)
	];
	
	luabind::module(l) [
		luabind::class_<AudioMixer>("AudioMixer")
			.def("fade_out_all", &AudioMixer::fade_out_all)
	];
	
	luabind::module(l) [
		luabind::class_<AudioFile>("AudioFile")
			.def("play", &AudioFile::play)
			.def("play_loop", &AudioFile::play_loop)
			.def("stop", &AudioFile::stop)
	];
	
	luabind::module(l) [
		luabind::class_<World>("World")
			.def("get_display", &World::get_display)
			.def("get_block_factory", &World::get_block_factory)
			.def("get_buttons", &World::get_buttons)
			.def("new_audio_file", &World::new_audio_file)
			.def("quit", &World::quit)
			.def("get_timer", &World::get_timer)
			.def("get_mixer", &World::get_mixer)
	];
	
}
