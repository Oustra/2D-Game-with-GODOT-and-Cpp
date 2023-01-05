#pragma once
#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <Input.hpp>
#include <Node2D.hpp>
#include <control.h>
#include <Control.hpp>
#include <SceneTree.hpp>

using namespace godot;

class MainMenu : public Control {
    GODOT_CLASS(MainMenu, Control)

private:
    // Private member variables and functions go here.

public:
    static void _register_methods() {
        register_method("_on_StartButton_pressed", &MainMenu::_on_StartButton_pressed);
        //register_method("_on_OptionsButton_pressed", &MainMenu::_on_OptionsButton_pressed);
        register_method("_on_QuitButton_pressed", &MainMenu::_on_QuitButton_pressed);
    }

    MainMenu() {
        // Constructor code goes here.
    }

    ~MainMenu() {
        // Destructor code goes here.
    }

    void _init() {
        // Initialization code goes here.
    }

    void _on_StartButton_pressed() {
        get_tree()->change_scene("res://INTRO.tscn");
    }

    //void _on_OptionsButton_pressed() {
        // This function is called when the options button is pressed.
        // You can use it to open the options menu or display the options screen.
    //}

    void _on_QuitButton_pressed() {
        get_tree()->quit();
    }
    
};
