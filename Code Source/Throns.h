#pragma once
#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <Input.hpp>
#include <PackedScene.hpp>
#include <SceneTree.hpp>

namespace godot {
	class Throns :public KinematicBody2D
	{
		// Godot structure
	private:
		GODOT_CLASS(Throns, KinematicBody2D)
	public:
		
		static void _register_methods() {
			register_method("_on_HitBox_body_entered", &Throns::_on_HitBox_body_entered);
		}

		void _ready() {}

		Throns() {}

		~Throns() {}

		void _init(){}

		void _on_HitBox_body_entered(Node* body) {
			if (body->is_in_group("Player"))
			{
				KinematicBody2D* Player = (KinematicBody2D*)body;
				Player->set_global_position(get_global_position());
			}
		}
	public:
		Vector2 respawn_position;
	};
}

