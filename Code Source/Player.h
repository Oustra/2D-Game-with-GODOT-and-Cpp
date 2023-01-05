#pragma once
#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <Input.hpp>
#include <Animation.hpp>
#include <AnimationPlayer.hpp>
#include <Camera.hpp>
#include <AnimatedSprite.hpp>
#include <PackedScene.hpp>
#include <ResourceLoader.hpp>
#include <Node2D.hpp>
#include <Sprite.hpp>
#include <Area2D.hpp>
#include <CollisionShape2D.hpp>


namespace godot {

	class Player : public KinematicBody2D
	{

		// Godot structure
	private:
		GODOT_CLASS(Player, KinematicBody2D)
	public:
		Player();
		static void _register_methods();
		void _init();
		void _process(float delta);
		void _physics_process(float delta);
		void _on_shy_body_entered(Node* body);
		void _on_shy_body_exited(Node* body);
		void _on_Spawn1_body_exited(Node* body);
		void _on_HitBox_body_entered(Node* body);
		void _on_Spawn1_body_entered(Node* body);
		void _on_Spawn2_body_entered(Node* body);
		void _on_Spawn3_body_entered(Node* body);
		void _ready();
		~Player();

		// Gameplay variables
	public:
		const int speed = 100; //Character Speed
		const int gravity = 160; //World Gravity
		const int Maxfallspeed = 180; //Character Max fall Speed
		const int MaxSpeed = 300; //Character Max Speed
		const int jumpForce = 3300; //Character Jump
		const int JumpMax = 2; //Character Max jumps numbre
		const int Max_Wall_slide = 40; //Character Max wall slide speed
		const int Wall_slide_Speed = 100; //Character wall slide speed
		int JumpCount = 0; //Jumps Counter
		bool Jump_was_pressed = false; //Jump condition
		bool Can_jump = false; //Jump condition
		bool facingRight = true; //Character facing condition
		bool is_paused = false; //Paused scene condition
		bool visible = false; //visibility condition
		bool shy = false; //Character shy condition
		bool sit = false; //Character sit condition
		int HP = 3; //Character Max Hp
	private:
		Vector2 motion; //vector
		Vector2 respawn_position; //Character respawn position

	};
}




