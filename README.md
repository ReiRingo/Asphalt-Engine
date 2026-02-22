# Asphalt Engine

Asphalt is a lightweight, scene-based 2D engine framework built on top of Raylib. It is designed to bridge the gap between low-level framework coding and high-level game engine workflows, providing a structured Actor-Scene architecture reminiscent of classic 2D engines like GameMaker or Godot, but within a pure C++ environment.

## Key Features

Scene Management: Automatic lifecycle handling for scenes, including seamless transitions and memory management.

**Actor-Oriented Design:** A flexible Actor class with built-in hooks for initialization, logic updates, and dual-pass drawing (World Space and UI Space).

**AABB Collision System:** Simplified mask-based collision detection integrated into the actor workflow.

**Type-Safe Utilities:** Modern C++ template-based functions for spawning and finding instances (instanceCreate, instanceFind).

**Y-Sorting:** Native support for depth-based rendering, essential for top-down 2D perspectives.

**Global Drawing Context"** Centralised font and color management to streamline UI and text rendering.

## Core Architecture

Asphalt operates on a hierarchical structure to keep game logic decoupled and organized:

**Scene Manager:** The global orchestrator. It handles the loading/unloading of scenes and ensures the game loop remains consistent.

Scene: A container for game logic and entities. It manages its own camera and a collection of Actors.

Actor: The base unit of interaction. Actors handle their own behavior, sprites, and collision masks.

# Getting Started

## Prerequisites:

Ensure you have a C++17 (or newer) compatible compiler.

## Installation:

**METHOD 1**:

Copy the core headers (asphalt.h, actor.h, scene.h, scene_manager.h) into your project directory.

**METHOD 2**:

Use the provided create_project.bat to initialize a new project structure instantly.

> For detailed instructions on implementation and utility functions, please refer to the Getting Started Guide.

# Project Philosophy

Asphalt is built for developers who find Raylib's procedural nature powerful but want more internal organization for larger projects. It provides the "scaffolding" so you can focus on game mechanics rather than reinventing the scene-graph for the tenth time.

> Project Lead: Rei Taylor

> Built with: Raylib 5.0+ and C++ 