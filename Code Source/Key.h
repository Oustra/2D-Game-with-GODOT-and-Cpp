#pragma once
#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <Input.hpp>
#include <PackedScene.hpp>
#include <SceneTree.hpp>
#include <Sprite.hpp>
#include <Area2D.hpp>
#include <AnimationPlayer.hpp>
#include <CollisionPolygon2D.hpp>
namespace godot {
	bool Key_taken = false;
	class Key :public Area2D
	{
		// Godot structure
	private:
		GODOT_CLASS(Key, Area2D)
	public:
		static void _register_methods() {
			register_method((char*)"_process", &Key::_process);
			register_method("_on_HitBox4_body_entered", &Key::_on_HitBox4_body_entered);
			register_method("_on_HitBox5_body_entered", &Key::_on_HitBox5_body_entered);
			register_method("_on_HitBox6_body_entered", &Key::_on_HitBox6_body_entered);
			register_method("_on_HitBox7_body_entered", &Key::_on_HitBox7_body_entered);
			register_method("_on_Ending_finished", &Key::_on_Ending_finished);
			register_method("_on_INTRO_finished", &Key::_on_INTRO_finished);
			register_method("_on_SKIP_pressed", &Key::_on_SKIP_pressed);
			
		}

		Key() {
		}

		~Key() {
		}
		void _init() {
		}
	public:
		bool Player_in_zone = false;
		bool END = false;
	public:

		void _on_HitBox4_body_entered(Node* body) {
			if (body->is_in_group("Player"))
			{
				if (Key_taken == false) {
					Sprite* Key = (Sprite*)get_node("SpriteKey");
					Key->queue_free();
					Key_taken = true;
				}
			}
		}
		//Skip to World2--------------------------------------
		void _on_HitBox5_body_entered(Node* body) {
			if (body->is_in_group("Player"))
					Player_in_zone = true;
		}
		//Skip To World3--------------------------------------
		void _on_HitBox6_body_entered(Node* body) {
			if (body->is_in_group("Player"))
				get_tree()->change_scene("res://World3.tscn");
		}
		//Skip To Ending--------------------------------------
		void _on_HitBox7_body_entered(Node* body) {
			if (body->is_in_group("Player")) {
				END = true;
			}
		}
		//Enter The House With The Key------------------------
		void _process(float delta) {
			Input* i = Input::get_singleton();
			if (Player_in_zone && Key_taken) {
				if (i->is_action_pressed("Entre")){
					Key_taken = false;
					get_tree()->change_scene("res://World2.tscn");
				}
			}
			if (END == true) {
				get_tree()->change_scene("res://Ending.tscn");
			}
		}

		//Ending
		void _on_Ending_finished() {
			get_tree()->change_scene("res://Menu.tscn");
		}
		
		void _on_SKIP_pressed() {
			get_tree()->change_scene("res://World.tscn");
		}

		void _on_INTRO_finished() {
			get_tree()->change_scene("res://World.tscn");
		}
	};

}
