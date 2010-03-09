#include "LuaBinder.h"

#include <luabind/operator.hpp>

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

// class LuaBlock3DFlat : public Block3DFlat {
// 	public:
// 		void set_animation(Vector2f size, int width, int height, luabind::object const& times) {
// 			list<float> list_times;
// 			std::vector<float> floats;
// // 			for( int i = 0; i < count; i++ ) {
// // 				list_times.push_back(luabind::object_cast<float>(times[i]));
// // 			}
// 			for (luabind::iterator it(times) , end ; it != end ; ++it) {
// 				list_times.push_back(luabind::object_cast<float>(*it));
// 			}
// 			Block3DFlat::set_animation(size, width, height, list_times);
// 		}
// };

// class LuaBlockFactory : public BlockFactory {
// 	public:
// 		Block3DFlat* new_animated_flat_block(string texture, Vector2f size, int width, int height, luabind::object const& times, bool mask, bool transparent) {
// 			list<float> list_times;
// 			for (luabind::iterator it(times) , end ; it != end ; ++it) {
// 				list_times.push_back(luabind::object_cast<float>(*it));
// 			}
// 			return BlockFactory::new_animated_flat_block(texture, size, width, height, list_times, mask, transparent);
// 		}
// };

// class LuaConverter {
// 	public:
// 		list<float> to_list(luabind::object const& an_object) {
// 			list<float> a_list;
// 			for (luabind::iterator it(an_object) , end ; it != end ; ++it) {
// 				a_list.push_back(luabind::object_cast<float>(*it));
// 			}
// 			return a_list;
// 		}
// };

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
			.def(luabind::self + Vector3f())
			.def(luabind::self - Vector3f())
			.def(luabind::self == Vector3f())
			.def(- luabind::self)
			.def(luabind::self * float())
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
			.def("get_z_depth", &Block::get_z_depth)
			.def("get_centre", &Block::get_centre)
			.def_readonly("cam_dist", &Block::cam_dist)
	];
	
	luabind::module(l) [
		luabind::class_<Block3D, luabind::bases<HasPosDir3D, Block> >("Block3D")
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
		luabind::class_<Block3DFlat, luabind::bases<HasPosDir3D, Block> >("Block3DFlat")
			.def("move", &Block3DFlat::move)
			.def("rotate", &Block3DFlat::rotate)
			.def("set_depth", &Block3DFlat::set_pos)
			.def("set_tex_size", &Block3DFlat::set_tex_size)
			.def("get_pos", &Block3DFlat::get_pos)
			.def("set_transparency", &Block3DFlat::set_transparency)
			.def("change_size", &Block3DFlat::change_size)
			.def("set_rel_centre", &Block3DFlat::set_rel_centre)
			.def("start", &Block3DFlat::start)
			.def("stop", &Block3DFlat::stop)
			.def("reset", &Block3DFlat::reset)
			.def("flipY", &Block3DFlat::flipY)
			.def("set_facing", &Block3DFlat::set_facing)
			.def(luabind::self == luabind::other<Block3DFlat>())
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
			.def("new_animated_flat_block", &BlockFactory::new_animated_flat_block_lua)
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
			.def("pick", &Display::pick)
			.def("project_xy", &Display::project_xy)
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
			.def_readonly("rmb", &Buttons::rmb)
			.def_readonly("lmb", &Buttons::lmb)
			.def_readonly("mouse_x", &Buttons::mouse_x)
			.def_readonly("mouse_y", &Buttons::mouse_y)
			.def_readonly("mouse_x_move", &Buttons::mouse_x_move)
			.def_readonly("mouse_y_move", &Buttons::mouse_y_move)
			.def_readonly("mouse_wheel_move", &Buttons::mouse_wheel_move)
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
	
// 	luabind::module(l) [
// 		luabind::class_<LuaConverter>("Converter")
// 			.def(luabind::constructor<>())
// 			.def("to_list", &LuaConverter::to_list) //apparently this is how you do static functions !?!?
// 			
// 	];
}
