# Overview

This project is supposed to be a Wolfenstein 3D Engine with some modifications. This Engine uses three different Methods for displaying: raycasting, billboarding and rasterization. All techniques
are implemented from scratch, no libraries except OpenGL for window-management-purposes are used. 

# Folder Structure

**documentation:** All files for documentation purposes

**include:** header files

**ressources:** Game Textures

**src:** source code

**tests:** tests for the game

# Concept
Firstly the game needs to initialize and open a window for drawing.
To achieve this, we use the **WindowManager**. This Component handles the initialization and updating of our game.

The **Screem** Class is our Inteface between the **WindowManager** and the **Renderer** which draws the objects contained in the **Game** class.

The **Renderer** makes use of the **Player** class to infer the position and rotation of the camera. The **Player** object is updated
once per framecycle and uses the inputs provided by the **WindowManager**. Wall collision in the movement is checked via the **Map** Component contained in the **Game**. For drawing the games Walls, the **Render** checks the distance to all walls for each pixel in the horizontal axis. The size of the Walls is then calculated by the distance to the player after which the corresponding **Texture** is sampled vertically and the pixels are drawn to the **Screen**'s buffer. The **Screen's** zBuffer is updated accordingly.

Afterwards every **Billboard** contained in the **Game** is rendered.
The position and size is calculated in the same way as the walls are.
Afterwards the **Billboard**'s **Texture** is sampled and drawn to the **Screen**.

At last the **Meshes** are drawn. Every **Mesh** constists of **Triangles** with a specicied **Color** in contrast to a **Texture**.
Every Triangle is then drawn using the **Edge** and **Span** class.