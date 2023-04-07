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

The **Screen** Class is our Inteface between the **WindowManager** and the **Renderer** which draws the objects contained in the **Game** class.

The **Renderer** makes use of the **Player** class to infer the position and rotation of the camera. The **Player** object is updated
once per framecycle and uses the inputs provided by the **WindowManager**. Wall collision in the movement is checked via the **Map** Component contained in the **Game**. For drawing the games Walls, the **Render** checks the distance to all walls for each pixel in the horizontal axis. The size of the Walls is then calculated by the distance to the player after which the corresponding **Texture** is sampled vertically and the pixels are drawn to the **Screen**'s buffer. The **Screen's** zBuffer is updated accordingly.

Afterwards every **Billboard** contained in the **Game** is rendered.
The position and size is calculated in the same way as the walls are.
Afterwards the **Billboard**'s **Texture** is sampled and drawn to the **Screen**.

At last the **Meshes** are drawn. Every **Mesh** constists of **Triangles** with a specicied **Texture**.
Every Triangle is then drawn using the **Edge** and **Span** class.

# The Camera

The Camera is represented by the **Player** class. It has three properties: position, angle and FOV (field of view).
Therefore the camera is able to freely move around the scene. The movement of the camera is handled by the user input
provided by the **WindowManager**

```C++
    if (WindowManager::buttons['a'])
        angle -= turn_speed * deltaTime;
    if (WindowManager::buttons['d'])
        angle += turn_speed * deltaTime;
    if (WindowManager::buttons['w'])
    {
        new_pos_x += forward;
        new_pos_y += left;
    }
    if (WindowManager::buttons['s'])
    {
        new_pos_x -= forward;
        new_pos_y -= left;
    }
```

# The Screen

The **Screen** consists of a color- and a depth-buffer. It is automatically created by the **WindowManager** class.

# Rendering the Walls

In the first step the Skybox is drawn to the screen. 

In this method we loop through every **Pixel** of the **Screen** in the xAxis.
For every pixel we want to shoot a ray to detect the distance to the nearest wall.
For this it is necessary to know the angle and position the ray is to be shot from.

```C++
void Renderer::renderWalls()
{
    for (int x = 0; x < game->window_manager.screen->width; x++)
        renderWallCollum(x);
}
```

The position is easy as it is the position of the camera.
For determining the angle of the camera we simply map the value of the x position of the screen across 
the FOV of the player.

```C++
double Renderer::getRayAngle(const int &x)
{
    const double minangle = game->player.angle - game->player.field_of_view / 2;
    return Renderer::map(x, 0, game->window_manager.screen->width, minangle, minangle + game->player.field_of_view);
}
```


Now we need to do a raycast to get the distance to the nearest wall
```C++
    double ray_x, ray_y;
    const auto distance = Raycast::raycast(player, &game->map, ray_angle, &ray_x, &ray_y);
```

Now we apply some correction to prevent a curvature in the display of the walls when rendering

```C++
const auto fish_eye_fixed_distance = distance * cos_angle_diff;
```


After that we can calculate the size of the wall at that position.
We add a factor to make the Player to appear bigger. Otherwise the players
camera always center the height of the walls.

```C++
int Renderer::getFloorScreenYPos(const int &screen_height, const double &distance)
{
    return (screen_height / 2) - (int)((screen_height / distance) * 1.3);
}

int Renderer::getCeilScreenYPos(const int &screen_height, const double &distance)
{
    return (screen_height / 2) + (int)((screen_height / distance) * 0.7);
}
```

Once we know the size of the walls we can start to draw them.
For this we start to loop over every y pixel and have to check
which element we have to draw at this specific pixel.

```C++
    bool rendered = false;

    if (y >= ceiling) // draw a ceiling
        rendered = renderCeiling(x, y, cos_ray_angle, sin_ray_angle, cos_angle_diff);
    else if (y >= floor) //draw a wall
        rendered = renderWall(x, y, distance, floor, ceiling, texture, sample_x);
    else // draw a floor
        rendered = renderFloor(x, y, cos_ray_angle, sin_ray_angle, cos_angle_diff);

    if (!rendered) //draw a sky
        renderSkybox(x, y, sky_image, sky_sample_x);

```

If any of our functions did not draw, we instead draw the skybox. This happens for example
if we have no ceiling at the specified pixel.

### Rendering the Ceiling

We first need to calculate the distance our pixel has to the camera.
From this we can infer the x and y coordinates when we take the players rotation into account.

Before we start drawing we have to check if our point is covered in the map or in other
words if the texture at this position is defined at all. 

If we are inside the map we can sample the texture to recieve the color we 
want to sample. To do this we just take the mantissa of our coordinates and update the
color- and depth-buffer. 

```C++
    const auto cos_angle_diff = std::cos(ray_angle - player->angle);
    const auto z_plane = (0.7 * screen->height) / (std::max(1.0, (double)(y - screen->height / 2)) * cos_angle_diff);

    const auto plane_point_x = player->pos_x + std::sin(player->angle) * z_plane;
    const auto plane_point_y = player->pos_y + std::cos(player->angle) * z_plane;

    const int sample_x_int = (int)std::floor(plane_point_x);
    const int sample_y_int = (int)std::floor(plane_point_y);

    if (!game->map.covers(sample_x_int, sample_y_int))
        return false;

    auto ceil_tile = game->map(sample_x_int, sample_y_int);

    if (ceil_tile->ceiling_transparent)
        return false;

    auto sample_x = plane_point_x - sample_x_int;
    auto sample_y = plane_point_y - sample_y_int;

    const auto ceiling_texture = game->map(sample_x_int, sample_y_int)->ceiling_texture;
    screen->setColor(x, y, (*ceiling_texture)(sample_x, sample_y));
    screen->setDepth(x, y, (float)z_plane);

    return true;
```

### Rendering the Wall

Rendering the wall is a little bit more difficult. For this we need to
take into account the side (North, East, South, West) our ray has hit the wall.
If we got that we can just map the y value from our ceiling and floor to 0-1.
And set the color and depth in our buffer.

```C++
    const double sample_x = getTextureSampleX(ray_x, ray_y);
    const auto texture = game->map((int)ray_x, (int)ray_y)->texture;

    const double sample_y = map(y,floor,ceiling,0,1);

    Pixel sample = (*texture)(sample_x, sample_y);
    if (sample.a == 0)
        return false;

    screen->setDepth(x, y, (float)distance);
    screen->setColor(x, y, sample);

    return true;
```

To retrieve the side we hit our ray on we use the atan2 function.
And sample our Texture depending on the side from L-R or R-L.

```C++
    double blockX = (double)((int)ray_x) + 0.5f;
    double blockY = (double)((int)ray_y) + 0.5f;

    double testAngle = atan2(ray_y - blockY, ray_x - blockX);

    double sample_x = 0;
    // depending on which side of the wall we are we need to sample differently
    if (testAngle >= -M_PI * 0.25f && testAngle < M_PI * 0.25f)
        sample_x = ray_y - (int)ray_y;
    if (testAngle >= M_PI * 0.25f && testAngle < M_PI * 0.75f)
        sample_x = 1 - (ray_x - (int)ray_x);
    if (testAngle < -M_PI * 0.25f && testAngle >= -M_PI * 0.75f)
        sample_x = ray_x - (int)ray_x;
    if (testAngle >= M_PI * 0.75f || testAngle < -M_PI * 0.75f)
        sample_x = 1 - (ray_y - (int)ray_y);

    return sample_x;
```

### Rendering the Floor

Rendering the floor is analogue to the ceiling. But we have to sample a different texture, respect our 
height scaling, and change the signs of our y and screen height.

```C++
const double z_plane = (1.3 * screen->height) / (std::max(1.0, (double)(screen->height / 2 - y)) * cos_angle_diff);

    const auto plane_point_x = player->pos_x + sin_ray_angle * z_plane;
    const auto plane_point_y = player->pos_y + cos_ray_angle * z_plane;

    const int sample_x_int = (int)std::floor(plane_point_x);
    const int sample_y_int = (int)std::floor(plane_point_y);

    auto ceil_tile = game->map(sample_x_int, sample_y_int);

    if (!game->map.covers(sample_x_int, sample_y_int))
        return false;

    if (ceil_tile->ceiling_transparent)
        return false;

    auto sample_x = plane_point_x - sample_x_int;
    auto sample_y = plane_point_y - sample_y_int;

    screen->setDepth(x, y, (float)z_plane);

    const auto floor_texture = game->map(sample_x_int, sample_y_int)->floor_texture;
    screen->setColor(x, y, (*floor_texture)(sample_x, sample_y));

    return true;
```

### Rendering the Skybox

To render the Skybox we need 4 textures to represent each side. We map the angle of our ray to the
specifc image and sample point. It would be better to use a sphere as representation but I wasn't able to find
a fitting one.

```C++
std::tuple<std::size_t, double> Renderer::getSkyboxSampleX(double angle)
{
    angle -= floor(angle / (2 * M_PI)) * 2 * M_PI;

    double percent = 4 * angle / (2 * M_PI);

    if (percent < 0.5)
        return {0, Renderer::map(percent, 0.0, 0.5, 0.5, 1.0)};
    if (percent < 1.5)
        return {2, Renderer::map(percent, 0.5, 1.5, 0.0, 1.0)};
    if (percent < 2.5)
        return {1, Renderer::map(percent, 1.5, 2.5, 0.0, 1.0)};
    if (percent < 3.5)
        return {3, Renderer::map(percent, 2.5, 3.5, 0.0, 1.0)};

    return {0, Renderer::map(percent, 3.5, 4.0, 0.0, 0.5)};
}
```

The drawing itself is rather easy. If we are drawing the upper part we draw the skybox and
otherwise a green color to represent grass.

```C++
if (screen->getDepth(x, y) != __FLT_MAX__)
        return;

Pixel color;
if (y > screen->height / 2)
{
    double sample_y = (double)y / (double)screen->height;
    color = (*(sky_textures[sky_image]))(sky_sample_x, sample_y);
}
else
{
    color = Color::green;
}
screen->setColor(x, y, color);
```

# Rendering the Billboards

Billboards are a simple rendering technique for drawing objects. They are essentially 
just pictures which always face the player.

We first check if the object is visible, then calculate the distance, get the height of the object and 
determine the width of the object through its object ration. After that we map the center position from the angle
in the field of view from zero to screen-width. 

```C++
if (!object.isVisible(&game->player))
    return;

// get object information
double dist = object.pos.getDistance(&game->player);

int object_ceiling = getCeilScreenYPos(screen->height, dist);
int object_floor = getFloorScreenYPos(screen->height, dist);

int unit_height = object_ceiling - object_floor;
int object_height = (int)(unit_height * object.height);

double object_ratio = object.height / object.width;
double object_width = object_height / object_ratio;

int object_center = (int)((0.5 * (object.pos.getAngle(&game->player) / (game->player.field_of_view / 2)) + 0.5) * screen->width);

// loop through every pixel
for (int x = 0; x < object_width; x++)
    renderBillboardColumn(object, x, object_center, object_width,object_height, object_floor, unit_height, dist);

```


Now we only check if the column is on the screen and calculate the x coord sample.

```C++
std::size_t screen_x = object_center + x - (int)(object_width / 2);

// skip if not visible
if (screen_x < 0 || screen_x >= screen->width)
    return;

// get sample of x chord
const double sample_x = ((double)x / object_width);

// loop through the heights
for (int y = 0; y < object_height; y++)
    renderBillboardPixel(object, screen_x,y, object_center, object_width, object_height, object_floor, unit_height, dist, sample_x);

```
Here we calculate the y position on the screen, check for screen bounds and check the zBuffer.
After that we sample the pixel and draw it.

```C++
std::size_t screen_y = object_floor + y + (std::size_t)(unit_height * object.pos.z);
// skip if out of screen
if (screen_y < 0 || screen_y >= screen->height)
    return;

    // skip if billboard is hidden
if (dist > screen->getDepth(screen_x, screen_y))
    return;

const double sample_y = (double)y / object_height;

Pixel sampled_pixel = (*object.texture)(sample_x, sample_y);

// skip if texture is transparent at pixel
if (sampled_pixel.a == 0)
    return;

// draw pixel
screen->setColor(screen_x, screen_y, sampled_pixel);
screen->setDepth(screen_x, screen_y, (float)dist);
```

# Rendering of the Meshes

For the mesh rendering, we load the models from the .obj and the uv_texture.
Then we apply the transformations on the points of the verticies, and draw the triangles.

```C++
        world_points[i]={transform.rot *  obj.vertexes[i].p * transform.scale + transform.pos};
        screen_points[i]={game, world_points[i]};   
```

To convert the world points to screen points we use the same logic we used for billboards.


```C++
const auto object_angle = point.getAngle(&game->player);
z = (float)point.getDistance(&game->player);

// map the angle to screenspace
x = (int)Renderer::map(object_angle, -game->player.field_of_view / 2, game->player.field_of_view / 2, 0, game->window_manager.screen->width);

int floor = Renderer::getFloorScreenYPos(game->window_manager.screen->height,z);
int ceil = Renderer::getCeilScreenYPos(game->window_manager.screen->height,z);

// interpolate z from floor to ceil
y = (int)Renderer::map(point.z, 0, 1, floor, ceil);
```

## Drawing of the triangles
For the drawing we split the triangle in an upper and a lower half. 

Then we interpolate the uv coords and the depth linearly between the three points.
For every point in the triangle we draw the triangle like so:

```C++
if(x < 0 || x >= (int)t->screen->width) continue;

//skip if hidden
if(t->screen->getDepth(x,y) < depth)
    continue;

int sample_x = (int)(u * (t->texture->width-1));
int sample_y = (int)(v * (t->texture->height-1));


Pixel texture_sample = (*t->texture)(sample_x,sample_y);

texture_sample.setBrightness(t->light_intensity);

t->screen->setColor(x,y,texture_sample);
t->screen->setDepth(x,y,depth);
```

First we check if we are in screen bounds. Then we sample our uv texture and draw the 
pixel. We take into consideration the lambertian lighting of the triangle. 
For calculating the light intensity we just map the scalar product of the normal with our
triangle normal and map it to a value from 0 to 1.

```C++
    light_intensity = 0.5f * (float)(1+(mesh->game->light.getDirection() * normal));
```

We then alter the color of the pixel according to the brightness like so

```C++
void Pixel::setBrightness(float brightness)
{
    r = (unsigned char)((float)r * brightness);
    g = (unsigned char)((float)g * brightness);
    b = (unsigned char)((float)b * brightness);
}
```

# Conclusion

There is more to describe, but describing the whole project would be a little excessive.
I've attached a good amount of inline documentation and tried to follow clean code practice
to make the code pretty readable imho :)