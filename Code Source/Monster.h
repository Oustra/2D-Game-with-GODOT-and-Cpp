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

namespace godot {
	class Monster:public KinematicBody2D
	{
		// Godot structure
	private:
		GODOT_CLASS(Monster, KinematicBody2D)
	public:
		static void _register_methods();
		void _init();
		void _process(float delta);
		void _physics_process(float delta);
		void _on_HitBox2_body_entered(Node* body);
		void _ready();
		Monster();
		~Monster();

		// Gameplay variables
	public:
		const int speed = 100;
		const int gravity = 180;
		const int MaxSpeed = 100;
		int dir = -1;
		bool Death=false;
	private:
		Vector2 motion;
		Vector2 direction;
		bool facingRight;
	};
}

