#include "Player.h"
#include <ResourceLoader.hpp>
#include <Node2D.hpp>
#include <assert.h>
#include <Sprite.hpp>
#include <Area2D.hpp>
#include<SceneTree.hpp>
#include <PhysicsBody2D.hpp>
#include <Node.hpp>
#include <AudioStreamPlayer2D.hpp>
#include <VisibilityEnabler2D.hpp>
#include <CanvasLayer.hpp>
#include <Control.hpp>
#include <CollisionPolygon2D.hpp>

using namespace godot;

void Player::_register_methods() {
	register_method((char*)"_process", &Player::_process);
	register_method((char*)"_physics_process", &Player::_physics_process);
	register_method("_on_HitBox_body_entered", &Player::_on_HitBox_body_entered);
	register_method("_on_Spawn1_body_entered", &Player::_on_Spawn1_body_entered);
	register_method("_on_Spawn2_body_entered", &Player::_on_Spawn2_body_entered);
	register_method("_on_Spawn3_body_entered", &Player::_on_Spawn3_body_entered);
	register_method("_on_shy_body_entered", &Player::_on_shy_body_entered);
	register_method("_on_shy_body_exited", &Player::_on_shy_body_exited);
	register_method("_on_Spawn1_body_exited", &Player::_on_Spawn1_body_exited);
}

void Player::_init() {
}

Player::Player() {
	motion = Vector2(0,0);
}

void Player::_ready() {
	respawn_position = get_global_position();
}

Player::~Player() {}

void Player::_process(float delta) {
	//movement physics----------------------
	move_and_slide(motion, Vector2(0,0).UP);
}

void Player::_physics_process(float delta)
{

	//Variables---------------------------------
	motion = Vector2(0,0);
	

	//Gravity-----------------------------------
	motion.y += gravity;
	

	//Import Animations-------------------------
	AnimationPlayer* _Anim = (AnimationPlayer*)get_node("AnimationPlayer");

	//Import Sprite-----------------------------
	Sprite* _Me = (Sprite*)get_node("Holloo");

	//Import Input------------------------------
	Input* i = Input::get_singleton();

	//Change Facing Direction-------------------
	if (facingRight) {
		_Me->set_flip_h(0);
	}
	else
		_Me->set_flip_h(1);

	//Limite Fall Speed-------------------------
	if (motion.y > Maxfallspeed) {
		motion.y = Maxfallspeed;
	}

	//Walk Left---------------------------------
	if (i->is_action_pressed("ui_left")) {
		motion.x -= speed;
		facingRight = false;
		if (is_on_floor()) {
			if (i->is_action_pressed("run")) {
				_Anim->play("Run");
				motion.x -= 80;
				if (i->is_action_just_pressed("jump") && is_on_floor()) {
					motion.x -= 500;
				}
			}
			else if(i->is_action_pressed("Alt"))
				_Anim->play("worm_move");
			else
				_Anim->play("Walk");
		}
	}

	//Walk right--------------------------------
	else if (i->is_action_pressed("ui_right")) {
		motion.x += speed;
		facingRight = true;
		if (is_on_floor()) {
			if (i->is_action_pressed("run")) {
				_Anim->play("Run");
				motion.x += 80;
				if (i->is_action_just_pressed("jump") && is_on_floor()) {
					motion.x += 500;
				}	
			}
			else if (i->is_action_pressed("Alt"))
				_Anim->play("worm_move");
			else {
				_Anim->play("Walk");
			}
		}
	}

	//change Look--------------
	else if(i->is_action_pressed("ui_up") && is_on_floor() && motion.x==0)
			_Anim->play("LookBack");

	else if (i->is_action_pressed("ui_down") && is_on_floor() && motion.x == 0)
			_Anim->play("LookFront");

	//Stop Animations----------
	else {
		motion.x = 0;
		if (is_on_floor())
			_Anim->play("Stand");
	}

	//Jump && Double Jump--------------------------------------
	if (is_on_floor() && JumpCount != 0) {
		JumpCount = 0;
	}
	//Two jumps
	if (JumpCount<JumpMax && i->is_action_just_pressed("jump")) {
		motion.y -= jumpForce;
		JumpCount += 1;
		if (motion.y < -gravity) {
			_Anim->play("Jump");
		}
		if (motion.x == 0 && is_on_floor())
			_Anim->play("Jump");
		if (JumpCount == 2 && i->is_action_just_pressed("jump")) {
			motion.y -= 1400;
			_Anim->play("DoubleJump");
		}
	}

	//Wall Jump-------------------------------------------------
	if (!is_on_floor() && is_on_wall() && (i->is_action_pressed("ui_right") || i->is_action_pressed("ui_left"))) {
		Can_jump = true;
		JumpCount = 0;
		if (JumpCount != 0)
			JumpCount=0;

		if (motion.y >= 0) {
			motion.y = fmin(motion.y + Wall_slide_Speed, Max_Wall_slide);
			if (is_on_wall() && !is_on_floor()) {
				_Anim->play("WallJump2");
			}
		}
	}
	//stop animation on floor
	if (!is_on_floor() && !is_on_wall() && JumpCount==0) {
		_Anim->play("Fall");
	}

	//Pause Menu-------------------------------------------
	CanvasLayer* PauseMenu = (CanvasLayer*)get_node("PauseMenu");
	Control* child = (Control*)PauseMenu->get_node("Pause");
	if (i->is_action_pressed("Pause")) {
		get_tree()->set_pause(true);
		child->set_visible(true);
	}

	//Sounds Player----------------------------------------
	AudioStreamPlayer2D* Sound = (AudioStreamPlayer2D*)get_node("Sound");
	if (!Sound->is_playing()) {
		Sound->_set_playing(1);
	}

	//Play shy Animation-----------------------------------
	if (shy && is_on_floor() && motion.x==0) {
		_Anim->play("Shy");
	}
	else if (sit && is_on_floor() && motion.x == 0) {
		_Anim->play("Sit");
		if (i->is_action_just_pressed("jump"))
			motion.y = 0;
	}
	else if (i->is_action_pressed("ui_up") && is_on_floor() && motion.x == 0)
		_Anim->play("LookBack");

	else if (i->is_action_pressed("ui_down") && is_on_floor() && motion.x == 0)
		_Anim->play("LookFront");
	

	//Hp player--------------------------------------------
	Sprite* Hp1 = (Sprite*)get_node("HPZONE/HpBar/Hp1");
	Sprite* Hp2 = (Sprite*)get_node("HPZONE/HpBar/Hp2");
	Sprite* Hp3 = (Sprite*)get_node("HPZONE/HpBar/Hp3");

	if (HP==2) {
		Hp3->set_visible(false);
	}
	else if (HP==1) {
		Hp2->set_visible(false);
	}
	else if (HP==0) {
		Hp1->set_visible(false);
		get_tree()->change_scene("res://DeathMenu.tscn");
	}	
}

void Player::_on_shy_body_entered(Node* body) {
	if (body->is_in_group("Player")) {
		shy = true;
		sit = false;
	}
}

void Player::_on_shy_body_exited(Node* body) {
	if (body->is_in_group("Player")) {
		shy = false;
		sit = false;
	}
}

//Hitbox to Die----------------------------------------
void Player::_on_HitBox_body_entered(Node* body) {
	{
		if (body->is_in_group("Enemy"))
		{
			set_global_position(respawn_position);
			HP--;
		}
	}
}

//respawn world1--------------------------------------
void Player::_on_Spawn1_body_entered(Node* body) {
	if (body->is_in_group("Player")) {
		respawn_position = get_global_position();
		shy = false;
		sit = true;
	}
}

void Player::_on_Spawn1_body_exited(Node* body) {
	if (body->is_in_group("Player")) {
		shy = false;
		sit = false;
	}
}

//respawn world2--------------------------------------
void Player::_on_Spawn2_body_entered(Node* body) {
	respawn_position = get_global_position();
}

//respawn world3--------------------------------------
void Player::_on_Spawn3_body_entered(Node* body) {
	respawn_position = get_global_position();
}








