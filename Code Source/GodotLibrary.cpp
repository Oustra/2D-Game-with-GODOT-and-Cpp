#include "Pause.h"
#include "Menu.h"
#include "Player.h"
#include "Monster.h"
#include "Throns.h"
#include "Key.h"
#include "DeathMenu.h"

using namespace godot;

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options * o) {
	Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options * o) {
	Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void* handle) {
	Godot::nativescript_init(handle);
	register_class<MainMenu>();
	register_class<Player>();
	register_class<Monster>();
	register_class<Pause>();
	register_class<Throns>();
	register_class<Key>();
	register_class<DeathMenu>();
}