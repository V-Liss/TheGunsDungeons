#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <string>
#include <stdlib.h>


using namespace sf;


int width=640;
int height=360;

int room_count=16;
int stage_count=15;
int template_types=5;

int particle_count=150;
int platform_types = 4;
int item_types = 13;
int drop_count = 100;
int common = 0;
int uncommon = 1;
int rare = 2;
int epic = 3;
int legendary = 4;
int mythic = 5;
//Entity

int dmgToPlayer = 0;
int types = 4;
int projectiles_count = 100;
double gravity = 1;
int friction = 1;
bool isF11Released = false;
bool wasF11Pressed = false;
bool isFullScreen = true;
bool wasSpacePressed=false;
bool spacePressed=false;
float PI = 3.14159265358;
int guns_count = 3;
double scroll_speed = 30;
int quit = -1;
int jump_on = -2;
int fall_off = -3;
int start_game=-4;
bool wasCtrlPressed=false;
bool ctrlPressed=false;

std::string to_str (int number) //function for converting numbers to strings
{
    std::string t = "";
    int temp = number;
    int temp2;
    for (temp2 = 0; temp > 0; temp2++)
    {
        temp = temp / 10;
    }
    if (temp2 == 0)
    {
        t = "0";
    }
    else
    {
        for (int i = temp2; i > 0; i--)
        {
            std::string ch = "0";
            ch[0] = ch[0] + (number % 10);
            t = ch + t;
            number = number / 10;
        }
    }
    return t;
}




double prc (double a, double b)
{
    for (double i = a - b; i > 0; i = a - b)
    {
        a -= b;
    }
    while (a < 0)
    {
        a += b;
    }
    if (a < b)
        return a;
    else
        return 0.1;
}

int round1 (float a)
{
    if (a - int (a) >= 0.5)
    {
        return int (a) + 1;
    }
    else
        return int (a);
}
double rt (double x, double y)
{
    if (x != 0)
    {
        return atan (y / x);
    }
    else if (y >= 0)
    {
        return 90.0 / 57;
    }
    else
    {
        return -90.0 / 57;
    }
}

double rotation (double x, double y)
{
    if (x > 0 && y >= 0)
    {
        return atan (y / x);
    }
    if (x < 0 && y >= 0)
    {
        return atan (y / x) + PI;
    }
    if (x < 0 && y < 0)
    {
        return atan (y / x) + PI;
    }
    if (x > 0 && y < 0)
    {
        return atan (y / x);
    }
    if (x == 0)
    {
        if (y > 0)
            return (PI / 2);
        else
            return (3 * PI / 2);
    }
}

double random (int max)
{
    if (max > 0)
        return (double ( (rand() % max) ) - double (max) / 2) / 57;
    else
        return 0;
}

int sign (float a)
{
    if (a > 0)
        return 1;
    else if (a < 0)
        return -1;
    else return 0;
}

int sign1 (float a)
{
    if (a >= 0)
        return 1;
    else
        return -1;
}

class vec
{
public:
    double x = 0;
    double y = 0;
    vec (double newx, double newy)
    {
        x = newx;
        y = newy;
    }
    vec()
    {
        x = 0;
        y = 0;
    }
    void setXY (int newx, int newy)
    {
        x = newx;
        y = newy;
    }
    vec operator+ (vec v)
    {
        v.x += x;
        v.y += y;
        return v;
    }
    vec operator- (vec v)
    {
        v.x -= x;
        v.y -= y;
        return v;
    }
    void operator+= (vec v)
    {
        x += v.x;
        y += v.y;
        return;//Entity
    }
    void operator-= (vec v)
    {
        x -= v.x;
        y -= v.y;
        return;
    }
    void operator= (vec v)
    {
        x = v.x;
        y = v.y;
        return;
    }
    bool operator== (vec v)
    {
        if (x == v.x && y == v.y)
        {
            return true;
        }
        else
            return false;
    }
};




class Animation
{
public:
    //int scale=1;
    double step_length = 1;
    double pos = 0.1;
    int length = 0;
    int f_count = 0;
    Texture* texture;
    int height = 0;
    int width = 0;
    int shift_x = 0;
    int shift_y = 0;
    Sprite sprite;
    double shift_rotation;
    double shift;
    double* frame_pos;
    Animation()
    {
    }
    void create (int l, int w, int h, int sh_x, int sh_y, double newstep)
    {
        width = w;
        height = h;
        texture = new Texture[l];
        length = l;
        sprite.setTexture (texture[0]);
        sprite.setTextureRect (IntRect (0, 0, width,  height) );
        shift_x = sh_x;
        shift_y = sh_y;
        shift = sqrt (shift_x * shift_x + shift_y * shift_y);
        shift_rotation = rotation (-shift_x, shift_y);
        step_length = newstep;
        //std::cout << shift_rotation/PI;
        return;
    }
    void step (double l)
    {
        pos += l;
        pos = prc (pos, length);
        int temp = int (pos);
        if (temp < length)
        {
            sprite.setTexture (texture[temp]);
        }
        else
        {
            sprite.setTexture (texture[0]);
        }
        sprite.setTextureRect (IntRect (0, 0, width, height) );
        return;
    }
    void step1()
    {
        pos += step_length;
        pos = prc (pos, length);
        int temp = int (pos);
        if (temp < length)
        {
            sprite.setTexture (texture[temp]);
        }
        else
        {
            sprite.setTexture (texture[0]);
        }
        sprite.setTextureRect (IntRect (0, 0, width, height) );
        return;
    }
    void setPos (double newpos)
    {
        pos = newpos;
        pos = prc (pos, length);
        int temp = int (pos);
        if (temp < length)
        {
            sprite.setTexture (texture[temp]);
        }
        else
        {
            sprite.setTexture (texture[0]);
        }
        sprite.setTextureRect (IntRect (0, 0, width, height) );
        return;
    }
    void setFrame (int frame)
    {
        if (frame < f_count && frame >= 0)
        {
            setPos (frame_pos[frame]);
        }
    }
    void fill_frames (std::string str, int frames)
    {
        for (int i = 0; i < length; i++)
        {
            int j = i / frames;
            std::string str1 = str;
            str1 += to_str (j);
            str1 += ".png";
            texture[i].loadFromFile (str1);
        }
        sprite.setTexture (texture[0]);
        return;
    }
    void setPR (int scale, int x, int y, double rotation)
    {
        sprite.setRotation (rotation * 57);
        double rot = scale * shift_rotation - rotation;
        //std::cout << rot/PI << std::endl;
        //sprite.setPosition(x, y);
        //sprite.setPosition(x-shift_x*scale, y-shift_y);
        sprite.setPosition (x + shift * cos (rot) *scale, y - shift * sin (rot) *scale);
        sprite.setScale (scale, 1);
        return;
    }
    void movePR(int scale, int x, int y, double rotation)
    {
        sprite.setRotation (rotation * 57);
        double rot = scale * shift_rotation - rotation;
        //std::cout << rot/PI << std::endl;
        //sprite.setPosition(x, y);
        //sprite.setPosition(x-shift_x*scale, y-shift_y);
        sprite.move(x, y);
        sprite.setScale (scale, 1);
        return;
    }
};
class Map
{
public:
    vec pos;
    vec speed;
    int width = 0;
    int height = 0;
    int twidth = 0;
    int theight = 0;
    Texture back_texture;
    Sprite back_sprite;
    Texture** texture = NULL;
    Sprite** sprite = NULL;
    int** M = NULL;
    Map()
    {
        width = 0;
        height = 0;
        twidth = 0;
        theight = 0;
    }
    Map (int w, int h, std::string path)
    {
        for (int i = 0; i < width; i++)
        {
            delete[] M[i];
        }
        delete[] M;
        M = new int*[w];
        for (int i = 0; i < w; i++)
        {
            M[i] = new int[h];
        }
        for (int i = 0; i < w; i++)
        {
            for (int j = 0; j < h; j++)
            {
                M[i][j] = 0;
            }
        }
        for (int i = 0; i < w; i++)
        {
            M[i][0] = 1;
            M[i][h - 1] = 1;
        }
        for (int i = 0; i < w; i++)
        {
            M[0][i] = 1;
            M[w - 1][i] = 1;
        }
        width = w;
        height = h;
        if (width % 1280 == 0)
        {
            twidth = width / 1280;
        }
        else
        {
            twidth = width / 1280 + 1;
        }
        if (height % 720 == 0)
        {
            theight = height / 720;
        }
        else
        {
            theight = height / 720 + 1;
        }
        texture = new Texture*[twidth];
        sprite = new Sprite*[twidth];
        for (int i = 0; i < twidth; i++)
        {
            texture[i] = new Texture[theight];
            sprite[i] = new Sprite[theight];
            for (int j = 0; j < theight; j++)
            {
                std::string str = "";
                str += path;
                str += to_str (i);
                str += "-";
                str += to_str (j);
                str += ".png";
                texture[i][j].loadFromFile (str);
                sprite[i][j].setTexture (texture[i][j]);
                sprite[i][j].setTextureRect (IntRect (0, 0, 1280, 720) );
            }
        }
    }
    void create (int w, int h, std::string path, std::string back_path)
    {
        for (int i = 0; i < width; i++)
        {
            delete[] M[i];
        }
        delete[] M;
        M = new int*[w];
        for (int i = 0; i < w; i++)
        {
            M[i] = new int[h];
        }
        for (int i = 0; i < w; i++)
        {
            for (int j = 0; j < h; j++)
            {
                M[i][j] = 0;
            }
        }
        for (int i = 0; i < w; i++)
        {
            M[i][0] = 1;
            M[i][h - 1] = 1;
        }
        for (int i = 0; i < h; i++)
        {
            M[0][i] = 1;
            M[w - 1][i] = 1;
        }
        width = w;
        height = h;
        for (int i = 0; i < twidth; i++)
        {
            delete[] texture[i];
        }
        delete[] texture;
        for (int i = 0; i < twidth; i++)
        {
            delete[] sprite[i];
        }
        delete[] sprite;
        if (width % 1280 == 0)
        {
            twidth = width / 1280;
        }
        else
        {
            twidth = width / 1280 + 1;
        }
        if (height % 720 == 0)
        {
            theight = height / 720;
        }
        else
        {
            theight = height / 720 + 1;
        }
        texture = new Texture*[twidth];
        sprite = new Sprite*[twidth];
        for (int i = 0; i < twidth; i++)
        {
            texture[i] = new Texture[theight];
            sprite[i] = new Sprite[theight];
            for (int j = 0; j < theight; j++)
            {
                std::string str = "";
                str += path;
                str += to_str (i);
                str += "-";
                str += to_str (j);
                str += ".png";
                texture[i][j].loadFromFile (str);
                sprite[i][j].setTexture (texture[i][j]);
                sprite[i][j].setTextureRect (IntRect (0, 0, 1280, 720) );
            }
        }
        back_texture.loadFromFile (back_path);
        back_sprite.setTexture (back_texture);
        return;
    }
    void create_noback(int w, int h)
    {
        for (int i = 0; i < width; i++)
        {
            delete[] M[i];
        }
        delete[] M;
        M = new int*[w];
        for (int i = 0; i < w; i++)
        {
            M[i] = new int[h];
        }
        for (int i = 0; i < w; i++)
        {
            for (int j = 0; j < h; j++)
            {
                M[i][j] = 0;
            }
        }
        for (int i = 0; i < w; i++)
        {
            M[i][0] = 1;
            M[i][h - 1] = 1;
        }
        for (int i = 0; i < h; i++)
        {
            M[0][i] = 1;
            M[w - 1][i] = 1;
        }
        width = w;
        height = h;
        for (int i = 0; i < twidth; i++)
        {
            delete[] texture[i];
        }
        delete[] texture;
        for (int i = 0; i < twidth; i++)
        {
            delete[] sprite[i];
        }
        delete[] sprite;
        if (width % 1280 == 0)
        {
            twidth = width / 1280;
        }
        else
        {
            twidth = width / 1280 + 1;
        }
        if (height % 720 == 0)
        {
            theight = height / 720;
        }
        else
        {
            theight = height / 720 + 1;
        }
        texture = new Texture*[twidth];
        sprite = new Sprite*[twidth];
        for (int i = 0; i < twidth; i++)
        {
            texture[i] = new Texture[theight];
            sprite[i] = new Sprite[theight];
            /*for (int j = 0; j < theight; j++)
            {
                std::string str = "";
                str += path;
                str += to_str (i);
                str += "-";
                str += to_str (j);
                str += ".png";
                texture[i][j].loadFromFile (str);
                sprite[i][j].setTexture (texture[i][j]);
                sprite[i][j].setTextureRect (IntRect (0, 0, 1280, 720) );
            }*/
        }
        //back_texture.loadFromFile (back_path);
        //back_sprite.setTexture (back_texture);
        return;
    }
    void setBlock (int x1, int y1, int x2, int y2, int block)
    {
        for (int i = x1; i <= x2 && i < width; i++)
        {
            for (int j = y1; j <= y2 && j < height; j++)
            {
                M[i][j] = block;
            }
        }
    }
};
class Position
{
public:
    vec pos;
    vec speed;
    void punch (vec newspeed)
    {
        speed += newspeed;
        return;
    }

    void engine (int head_height, int height, int width, Map mp)
    {
        //speed.y+=gravity;
        bool bumped_x = false;
        bool bumped_y = false;
        double a1 = speed.x;
        double b1 = speed.y;
        double cosinus = cos (rotation (speed.x, speed.y) );
        double sinus = sin (rotation (speed.x, speed.y) );
        //std::cout << std::endl;
        while ( (sign (speed.x) == sign (a1) && speed.x != 0) || (sign (speed.y) == sign (b1) && speed.y != 0) )
        {
            //std::cout << position.x << " " << cosinus << std::endl;
            //std::cout << position.speed_x << std::endl;
            //std::cout << position.y << std::endl;
            //std::cout << position.speed_y << std::endl << std::endl;
            for (int i = -head_height; i <= height; i++)
            {
                if (mp.M[round1 (pos.x) + (width + 1) *sign (speed.x)][round1 (pos.y) + i] > 0)
                {
                    bumped_x = true;
                    speed.x = 0;
                }
            }
            if (sign (speed.x) == sign (a1) && speed.x != 0)
            {
                if (abs (speed.x) > abs (cosinus) )
                {
                    pos.x += cosinus;
                    speed.x -= cosinus;
                }
                else
                {
                    pos.x += speed.x;
                    speed.x = 0;
                }
            }
            for (int i = -width; i <= width; i++)
            {
                if (speed.y > 0 && (mp.M[round1 (pos.x) + i][round1 (pos.y) + height + 1] > 0 || mp.M[round1 (pos.x) + i][round1 (pos.y) + height + 1] == jump_on) )
                {
                    bumped_y = true;
                    speed.y = 0;
                }
                else if (speed.y < 0 && (mp.M[round1 (pos.x) + i][round1 (pos.y) - head_height - 1] > 0 || mp.M[round1 (pos.x) + i][round1 (pos.y) - head_height - 1] == fall_off) )
                {
                    bumped_y = true;
                    speed.y = 0;
                }
            }
            if (sign (speed.y) == sign (b1) && speed.y != 0)
            {
                if (abs (speed.y) > abs (sinus) )
                {
                    pos.y += sinus;
                    speed.y -= sinus;
                }
                else
                {
                    pos.y += speed.y;
                    speed.y = 0;
                }
            }
        }
        if (!bumped_x)
            speed.x = a1;
        else
            speed.x = 0;
        if (!bumped_y)
            speed.y = b1;
        else
            speed.y = 0;
        return;
    }
};

class Gun
{
public:
    int item=0;
    SoundBuffer buffer;
    Sound sound;
    int self_explosion_knockback = 0;
    double self_damage_multiplier = 0;
    int explosion_knockback = 1;
    Texture icon_texture;
    Sprite icon;
    int predelay = 0;
    int max_predelay = 0;
    //int state=0;
    int knockback = 2;
    int self_knockback = 0;
    int proj_type=0;
    int proj_grav=0;
    Animation blast;
    Animation projectile;
    SoundBuffer exp_buffer;
    Texture bullet_texture;
    Sprite bullet;
    //Texture icon_texture;
    //Sprite icon;
    //Animation crosshair;
    Animation animation;
    Animation upper_animation;

    int max_delay = 10;
    int damage = 10;
    int min_damage = 10;
    int delay = 0;
    //bool isPistol=true;
    int max_distance = 960;
    double spread = 0;
    int pellets = 0;
    double pellet_spread = 0.04;
    double swiftness = 1;
    int type = 0;
    int radius = 5;
    int proj_speed = 32;
    int max_projectile_time = 5;
    int proj_width = 10;
    int proj_length = 100;
    int proj_acceleration = 0;
    double splash_multiplier = 2;
    int max_deploy = 10;
    int deploy_counter = 0;
    void create (int newmax_delay)
    {
        max_delay = newmax_delay;
        animation.frame_pos = new double[max_delay + 1];
        animation.f_count = max_delay + 1;
        upper_animation.frame_pos = new double[max_delay + 1];
        upper_animation.f_count = max_delay + 1;
    }
};
class Entity
{
public:
    SoundBuffer hit_buffer;
    Sound hit_sound;

    SoundBuffer shoot_buffer;
    Sound shoot_sound;

    SoundBuffer exp_buffer;
    Sound exp_sound;

    Animation proj;
    Animation blast;

    Animation heat[5];

    bool boss=false;

    int overheat=0;

    int max_overheat=180;

    double rotation_speed=0.025;
    double rotation=0;

    int hit_cooldown=0;
    int max_hit_cooldown=30;

    bool isStanding = false;
    bool onPlatform = false;

    int room=0;

    int shoot_timer=0;

    //int idle_timer=0;

    int weight=1;

    int death_timer=0;
    int max_death_timer;

    int gun=0;

    int money = 0;
    double not_fortune=1;
    int dynamite=3;
    int shells=0;
    double shells_multiplier=1.3;

    int max_run = 60;
    int max_aim = 10;

    int damage = 1;
    int recoil = 6;

    int max_startup = 42;
    int timer = 0;//rand
    int quantity = 0;

    int gun_holding = 0;
    int breath_count = 0;

    int dir_x = 1;
    int dir_y = 0;

    int* drop_min;
    int* drop_max;
    int* drop_type;
    int drops=0;

    bool is=false;
    bool was=false;
    Texture idle;
    Texture up;
    Texture down;
    Animation body;
    Animation head;
    Animation tracks;
    Animation head_up;
    Animation head_down;
    Animation death;
    Animation startup;
    Position position;
    int health = 5;
    int armor = 0;
    int max_health = 5;
    int max_armor = 20;
    int max_dynamite=6;
    int jump_force = 24;
    int head_height = 9;
    int height = 23;
    int air_strafe_force = 3;
    int strafe_force = 4;
    int max_guns_delay = 15;
    int sight_x = 300;
    int sight_y = 180;
    int max_speed = 8;
    int width = 10;
    int phase = 0;
};
//type
class Projectile
{
public:
    bool is = false;
    int knockback = 0;
    int explosion_knockback = 0;
    double x = 0;
    double y = 0;
    int damage = 0;
    int min_damage = 0;
    int speed = 0;
    double rotation = 0;
    int radius = 0;
    int distance_left = 0;
    int time = 0;
    int acceleration = 0;
    Animation animation;
    Sound explosion;
    Animation blast;
    int gun = 0;
    double multiplier = 1;
    int type=0;
    int grav=0;
};


struct Bullet
{
    int damage = 0;
    double final_x = 0;
    double final_y = 0;
    bool hit = false;
    int distance = 0;
};



Bullet shoot (double ent_x, double ent_y, int head_height, int height, int width, double angle, double x, double y, int damage, int max_distance, Map mp)
{
    Bullet bullet;
    double sinus = sin (angle);
    double cosinus = cos (angle);
    int temp_block=1;
    if (sinus>0)
    {
        temp_block=jump_on;
    }
    else if (sinus<0)
    {
        temp_block=fall_off;
    }
    if (sinus<=0.05&&sinus>=-0.05)
    {
        temp_block=1;
    }
    for (; bullet.distance < max_distance && mp.M[round1 (x)][round1 (y)] < 1 && mp.M[round1 (x)][round1 (y)] != temp_block; bullet.distance++)
    {
        if (x >= ent_x - width && x <= ent_x + width)
        {
            if (y >= ent_y && y <= ent_y + height)
            {
                bullet.hit = true;
                bullet.damage = damage;
                bullet.final_x = x;
                bullet.final_y = y;
                return bullet;
            }
            else if (y >= ent_y - head_height && y <= ent_y)
            {
                bullet.hit = true;
                bullet.damage = damage * 2;
                bullet.final_x = x;
                bullet.final_y = y;
                return bullet;
            }
        }
        x += cosinus;
        y += sinus;
    }
    bullet.final_x = x;
    bullet.final_y = y;
    return bullet;
}

Bullet enemy_shoot (double ent_x, double ent_y, int head_height, int height, int width, double angle, double x, double y, int damage, int max_distance, Map mp)
{
    Bullet bullet;
    double sinus = sin (angle);
    double cosinus = cos (angle);
    for (; bullet.distance < max_distance && mp.M[round1 (x)][round1 (y)] == 0; bullet.distance++)
    {
        if (x >= ent_x - width && x <= ent_x + width)
        {
            if (y >= ent_y - head_height && y <= ent_y)
            {
                bullet.hit = true;
                bullet.damage = damage * 2;
                bullet.final_x = x;
                bullet.final_y = y;
                return bullet;
            }
            if (y >= ent_y && y <= ent_y + height)
            {
                bullet.hit = true;
                bullet.damage = damage;
                bullet.final_x = x;
                bullet.final_y = y;
                return bullet;
            }
        }
        x += cosinus;
        y += sinus;
    }
    bullet.final_x = x;
    bullet.final_y = y;
    return bullet;
}


bool canShoot (double x1, double y1, double x2, double y2, int** M)
{
    double sinus = sin (rotation (x2 - x1, y2 - y1) );
    double cosinus = cos (rotation (x2 - x1, y2 - y1) );
    int sign2 = sign (x2 - x1);
    while (sign2 == sign (x2 - x1) )
    {
        if (M[round1 (x1)][round1 (y1)]>0||(y2>y1&&M[round1(x1)][round1(y1)]==jump_on)||(y2<y1&&M[round1(x1)][round1(y1)]==fall_off))
        {
            return false;
        }
        x1 += cosinus;
        y1 += sinus;
    }
    return true;
}

Bullet damage (double multiplier, double enemy_x, double enemy_y, int width, double enemy_y1, double enemy_y2, double projectile_x, double projectile_y, double radius, int dmg, int** M)
{
    Bullet bullet;
    bullet.hit = false;
    //int dmg1=0;
    for (double i = enemy_y1; i < enemy_y; i++)
    {
        for (double j = enemy_x - width; j <= enemy_x + width; j++)
        {
            if (radius * radius > (j - projectile_x) * (j - projectile_x) + (i - projectile_y) * (i - projectile_y) )
            {
                bullet.hit = true;
            }
            double dmg2 = ( (radius - sqrt ( (j - projectile_x) * (j - projectile_x) + (i - projectile_y) * (i - projectile_y) ) ) * dmg / radius) * multiplier;
            if (bullet.damage < dmg2 && canShoot (projectile_x, projectile_y, j, i, M) )
            {
                bullet.damage = dmg2;
                bullet.final_x = j - projectile_x;
                bullet.final_y = i - projectile_y;
            }
        }
    }
    for (double i = enemy_y; i <= enemy_y2; i++)
    {
        for (double j = enemy_x - width; j <= enemy_x + width; j++)
        {
            if (radius * radius > (j - projectile_x) * (j - projectile_x) + (i - projectile_y) * (i - projectile_y) )
            {
                bullet.hit = true;
            }
            double dmg2 = ( (radius - sqrt ( (j - projectile_x) * (j - projectile_x) + (i - projectile_y) * (i - projectile_y) ) ) * dmg / radius);
            if (bullet.damage < dmg2 && canShoot (projectile_x, projectile_y, j, i, M) )
            {
                bullet.damage = dmg2;
                bullet.final_x = j - projectile_x;
                bullet.final_y = i - projectile_y;
            }
        }
    }
    if ( (bullet.final_y < 2 && bullet.final_y > -2) && (bullet.final_x < 2 && bullet.final_x > -2) )
    {
        double rot = rotation (enemy_x - projectile_x, enemy_y - projectile_y);
        bullet.final_x = cos (rot);
        bullet.final_y = sin (rot);
    }
    return bullet;
}
class Rectangle
{
public:
    int x_min = 0;
    int width = 1280;
    int y_min = 0;
    int height = 720;
    bool contains (vec v)
    {
        return (x_min <= v.x && x_min + width >= v.x && y_min <= v.y && y_min + height >= v.y);
    }
    bool contains1(int x, int y)
    {
        return (x_min <= x && x_min + width >= x && y_min <= y && y_min + height >= y);
    }
    bool canClose (vec v, int w, int head_height, int h)
    {
        return (x_min <= v.x - w - 1 && x_min + width >= v.x + w + 1 && y_min <= v.y - head_height - 1 && y_min + height >= v.y + h + 1);
    }
    void setPosition (int x, int y)
    {
        x_min = x;
        y_min = y;
    }
    void setWH (int w, int h)
    {
        width = w;
        height = h;
    }
};
class Item
{
public:
    SoundBuffer pickup_buffer;
    Sound pickup_sound;
    int stock_price=5;

    Animation animation;
    //Animation glint;
    int rarity = 0;
    bool auto_pickup = false;
    std::string name = "";
    std::string description = "";
};
class Drop
{
public:
    bool onPlatform=false;
    bool trade=false;
    //int price=0;
    int type;
    int timer=0;
    Position position;
    Animation animation;
    Animation glint;
    int counter = 0;
    bool is = false;
};
class Platform
{
public:

    Animation up;
    Animation down;
    void create (int x_start, int y_start, int x_finish, int y_finish, int newX, int newY, int newBlock, int newWidth, int newHeight)
    {
        pos_start.setXY (x_start, y_start);
        pos_finish.setXY (x_finish, y_finish);
        pos.setXY (newX, newY);
        //type=newType;
        block = newBlock;
        width = newWidth;
        height = newHeight;
    }
    vec pos_start;
    vec pos_finish;
    vec pos;
    vec speed;
    //int type=0;
    int block = 1;
    int width = 100;
    int height = 1;
    int quantity = 0;
    bool is = false;
    int phase=0;

    bool canMove (int x, int y, int** M, Entity player, Entity** enemy, Drop* drop)
    {
        for (int i = pos.x + x; i < pos.x + x + width; i++)
        {
            for (int j = pos.y + y; j < pos.y + y + height; j++)
            {
                if (M[i][j] != 0)
                {
                    //std::cout <<"1";
                    return false;
                }
            }
        }
        if (block == jump_on || block > 0)
        {
            if (y < 0)
            {
                if (player.position.speed.y > 0)
                {
                    if (pos.y > round1 (player.position.pos.y + player.height) && pos.y + y <= round1 (player.position.pos.y + player.height) )
                    {
                        //std::cout <<"2";
                        return false;
                    }
                }
                for (int i = 0; i < types; i++)
                {
                    for (int j = 0; j < enemy[i][0].quantity; j++)
                    {
                        if (enemy[i][j].is)
                        {
                            if (enemy[i][j].position.speed.y > 0)
                            {
                                if (pos.y > round1 (enemy[i][j].position.pos.y + enemy[i][j].height) && pos.y + y <= round1 (enemy[i][j].position.pos.y + enemy[i][j].height) )
                                {
                                    //std::cout << bool(pos.y > round1 (enemy[i][j].position.pos.y + enemy[i][j].height)) << bool(pos.y + y <= round1 (enemy[i][j].position.pos.y + enemy[i][j].height)) << "\n";
                                    //std::cout << i << " " << j << "\n";
                                    return false;
                                }
                            }
                        }

                    }
                }
                for (int j = 0; j < drop_count; j++)
                    {
                        if (drop[j].is)
                        {
                            if (drop[j].position.speed.y > 0)
                            {
                                if (pos.y > round1 (drop[j].position.pos.y + 1) && pos.y + y <= round1 (drop[j].position.pos.y + 1) )
                                {
                                    //std::cout << bool(pos.y > round1 (enemy[i][j].position.pos.y + enemy[i][j].height)) << bool(pos.y + y <= round1 (enemy[i][j].position.pos.y + enemy[i][j].height)) << "\n";
                                    //std::cout << i << " " << j << "\n";
                                    return false;
                                }
                            }
                        }

                    }
            }
        }
        if (block == fall_off || block > 0)
        {
            if (y > 0)
            {
                if (player.position.speed.y < 0)
                {
                    if (pos.y + height < round1 (player.position.pos.y + height - player.head_height) && pos.y + height + y >= round1 (player.position.pos.y + height - player.head_height) )
                    {
                        return false;
                    }
                }
                for (int i = 0; i < types; i++)
                {
                    for (int j = 0; j < enemy[i][0].quantity; j++)
                    {
                        if (enemy[i][j].is)
                        {
                            if (enemy[i][j].position.speed.y < 0)
                            {
                            if (pos.y + height < round1 (enemy[i][j].position.pos.y + height - enemy[i][j].head_height) && pos.y + height + y >= round1 (enemy[i][j].position.pos.y + height - enemy[i][j].head_height) )
                                {
                                    return false;
                                }
                            }
                        }
                    }
                }
                for (int j = 0; j < drop_count; j++)
                    {
                        if (drop[j].is)
                        {
                            if (drop[j].position.speed.y > 0)
                            {
                                if (pos.y+height > round1 (drop[j].position.pos.y+height - 1) && pos.y+height + y <= round1 (drop[j].position.pos.y+height - 1) )
                                {
                                    //std::cout << bool(pos.y > round1 (enemy[i][j].position.pos.y + enemy[i][j].height)) << bool(pos.y + y <= round1 (enemy[i][j].position.pos.y + enemy[i][j].height)) << "\n";
                                    //std::cout << i << " " << j << "\n";
                                    return false;
                                }
                            }
                        }

                    }
            }
        }
        if (block > 0||(block==fall_off&&y>0)||(block==jump_on&&y<0))
        {
            if (sign (pos.x + width - player.position.pos.x + player.width) != sign (pos.x + width + x - player.position.pos.x + player.width) )
            {
                return false;
            }
            if (sign (pos.x - player.position.pos.x - player.width) != sign (pos.x + x - player.position.pos.x - player.width) )
            {
                return false;
            }
            for (int i = 0; i < types; i++)
            {
                for (int j = 0; j < enemy[i][0].quantity; j++)
                {
                    if (enemy[i][j].is)

                    {


                        if (sign (pos.x + width - enemy[i][j].position.pos.x + enemy[i][j].width) != sign (pos.x + width + x - enemy[i][j].position.pos.x + enemy[i][j].width) )
                        {
                            return false;
                        }
                        if (sign (pos.x - enemy[i][j].position.pos.x - enemy[i][j].width) != sign (pos.x + x - enemy[i][j].position.pos.x - enemy[i][j].width) )
                        {
                            return false;
                        }
                    }
                }
            }
            for (int j = 0; j < drop_count; j++)
                {
                    if (drop[j].is)

                    {


                        if (sign (pos.x + width - drop[j].position.pos.x + 1) != sign (pos.x + width + x - drop[j].position.pos.x + 1) )
                        {
                            return false;
                        }
                        if (sign (pos.x - drop[j].position.pos.x - 1) != sign (pos.x + x - drop[j].position.pos.x - 1) )
                        {
                            return false;
                        }
                    }
                }
        }
        return true;
    }
    bool canAppear(int x, int y, Entity player, Entity** enemy, Drop* drop)
    {
        if (player.position.pos.x+player.width>pos.x&&player.position.pos.x-player.width<pos.x+width)
        {
            if (player.position.pos.y+player.height>pos.y&&player.position.pos.y-player.head_height<pos.y+height)
            {
                return false;
            }
        }
        for (int i=0; i<types; i++)
        {
            for (int j=0; j<enemy[i][0].quantity; j++)
            {
                if (enemy[i][j].is)
                {
                    if (enemy[i][j].position.pos.x+enemy[i][j].width>pos.x&&enemy[i][j].position.pos.x-enemy[i][j].width<pos.x+width)
                    {
                        if (enemy[i][j].position.pos.y+enemy[i][j].height>pos.y&&enemy[i][j].position.pos.y-enemy[i][j].head_height<pos.y+height)
                        {
                            return false;
                        }
                    }
                }

            }
        }
         for (int j=0; j<drop_count; j++)
            {
                if (drop[j].is)
                {
                    if (drop[j].position.pos.x+1>pos.x&&drop[j].position.pos.x-1<pos.x+width)
                    {
                        if (drop[j].position.pos.y+1>pos.y&&drop[j].position.pos.y-1<pos.y+height)
                        {
                            return false;
                        }
                    }
                }

            }
        return true;
    }
    void move1 (int x, int y, int** M, Entity player, Entity** enemy, Drop* drop)
    {
        if (canMove (x, y, M, player, enemy, drop) )
        {
            pos.x += x;
            pos.y += y;
        }
    }
};


class Particle
{
public:
    //bool is=false;
    Animation animation;
    int timer=0;
    vec pos;
    int type=0;
};
class Spawn
{//rand
public:
    Position position;
    int weight=1;
};
class platf
{
public:
    int type;
    vec pos;
    vec pos_start;
    vec pos_finish;
    vec speed;
};
class Room
{
public:
    bool boss=false;
    bool* drop_discovered;
    int** M;
    Animation background;
    vec pos;
    bool is=false;
    Rectangle rectangle;
    Spawn* spawn;
    platf* platforms;
    Drop* drop;
    int drop_count=0;
    int quantity=0;
    int probability=1;
    int platform_count=0;
    int spawn_count=0;
    bool visited=false;
    int width=0;
    int height=0;
    void create(int newPlatf, int newSpawn, int newWidth, int newHeight)
    {
        width=newWidth;
        height=newHeight;
        M=new int*[width];
        for (int i=0; i<width; i++)
        {
            M[i]=new int[height];
            for (int j=0; j<height; j++)
            {
                M[i][j]=0;
            }
        }
        platform_count=newPlatf;
        spawn_count=newSpawn;
        if (spawn_count>0)
        spawn = new Spawn[spawn_count];
        if (platform_count>0)
        platforms = new platf[platform_count];
    }
};
class Stage
{
public:
    int* quantity=new int[template_types];
    void create0()
    {
        for (int i=0; i<template_types; i++)
        {
            quantity[i]=0;
        }
    }
};

int main()
{//knockback
    double temp_cos;
    double temp_sin;
    Texture bar_texture;
    Sprite bar_sprite;
    Texture hp_texture;
    Sprite hp_sprite;

    bar_texture.loadFromFile("Textures/misc/boss_frame.png");
    bar_sprite.setTexture(bar_texture);

    hp_texture.loadFromFile("Textures/misc/boss_bar.png");
    hp_sprite.setTexture(hp_texture);

    Entity **enemy = new Entity*[types];
    enemy[1]=new Entity[20];
    enemy[2]=new Entity[1];
    Item* item;
    Drop* drop;
    bool escPressed=false;
    bool wasEscPressed=false;
    bool paused=false;
    Texture pause_texture;
    Sprite pause_sprite;

    pause_texture.loadFromFile("Textures/backgrounds/pause.png");
    pause_sprite.setTexture(pause_texture);
    pause_sprite.setPosition(0, 0);

    Text pause_text;
    Entity player_stock;
    player_stock.max_armor=10;
    //player_stock.gun=2;
    Entity player;
    Gun *guns = new Gun[guns_count];
    item = new Item[item_types];

    int hurt_timer=0;
    Animation hurt;
    hurt.create(3, 640, 360, 0, 0, 0.1);
    hurt.frame_pos=new double[6];
    hurt.frame_pos[0]=2.1;
    hurt.frame_pos[1]=2.1;
    hurt.frame_pos[2]=1.1;
    hurt.frame_pos[3]=1.1;
    hurt.frame_pos[4]=0.1;
    hurt.frame_pos[5]=0.1;
    hurt.fill_frames("Textures/misc/hurt/", 1);
    bool resp=true;
    bool toRespawn=false;
    int temp_spawn_x=100;
    int temp_spawn_y=100;

    srand(time(NULL));
    //bool t=true;

    int stage=-1;
    Stage* cave=new Stage[stage_count];
    for (int i=0; i<stage_count; i++)
    {
        cave[i].create0();
    }

    cave[0].quantity[0]=3;//3
    cave[0].quantity[1]=1;//1
    cave[0].quantity[2]=1;
    cave[0].quantity[3]=0;
    cave[0].quantity[4]=0;//0

    cave[1].quantity[0]=4;
    cave[1].quantity[1]=1;
    cave[1].quantity[2]=1;
    cave[1].quantity[3]=0;
    cave[1].quantity[4]=0;

    cave[2].quantity[0]=5;
    cave[2].quantity[1]=2;
    cave[2].quantity[2]=1;
    cave[2].quantity[3]=0;
    cave[2].quantity[4]=0;

    cave[3].quantity[0]=4;
    cave[3].quantity[1]=3;
    cave[3].quantity[2]=2;
    cave[3].quantity[3]=1;
    cave[3].quantity[4]=0;

    cave[4].quantity[0]=5;
    cave[4].quantity[1]=3;
    cave[4].quantity[2]=2;
    cave[4].quantity[3]=1;
    cave[4].quantity[4]=1;

    cave[5].quantity[0]=5;
    cave[5].quantity[1]=4;
    cave[5].quantity[2]=2;
    cave[5].quantity[3]=1;
    cave[5].quantity[4]=0;

    cave[6].quantity[0]=3;
    cave[6].quantity[1]=5;
    cave[6].quantity[2]=2;
    cave[6].quantity[3]=2;
    cave[6].quantity[4]=0;

    cave[7].quantity[0]=4;
    cave[7].quantity[1]=5;
    cave[7].quantity[2]=2;
    cave[7].quantity[3]=2;
    cave[7].quantity[4]=0;

    cave[8].quantity[0]=1;
    cave[8].quantity[1]=6;
    cave[8].quantity[2]=3;
    cave[8].quantity[3]=2;
    cave[8].quantity[4]=0;

    cave[9].quantity[0]=0;
    cave[9].quantity[1]=6;
    cave[9].quantity[2]=3;
    cave[9].quantity[3]=3;
    cave[9].quantity[4]=1;


    cave[10].quantity[0]=0;//self_knockback
    cave[10].quantity[1]=6;
    cave[10].quantity[2]=3;
    cave[10].quantity[3]=3;
    cave[10].quantity[4]=0;

    cave[11].quantity[0]=0;
    cave[11].quantity[1]=7;
    cave[11].quantity[2]=3;
    cave[11].quantity[3]=3;
    cave[11].quantity[4]=0;

    cave[12].quantity[0]=0;
    cave[12].quantity[1]=5;
    cave[12].quantity[2]=4;
    cave[12].quantity[3]=4;
    cave[12].quantity[4]=0;

    cave[13].quantity[0]=0;
    cave[13].quantity[1]=6;
    cave[13].quantity[2]=4;
    cave[13].quantity[3]=4;
    cave[13].quantity[4]=0;

    cave[14].quantity[0]=0;
    cave[14].quantity[1]=3;
    cave[14].quantity[2]=4;
    cave[14].quantity[3]=5;
    cave[14].quantity[4]=1;

    //cave[0].create();
    //cave[0].weight=4;
    //cave[0].weight_delta=1;player.position.speed.y

    Room** room_template=new Room*[template_types];//dynamite_count
    int quant1=3;
    room_template[0]=new Room[quant1];
    room_template[0][0].quantity=quant1;
    quant1=1;
    room_template[1]=new Room[quant1];
    room_template[1][0].quantity=quant1;
    quant1=1;
    room_template[2]=new Room[quant1];
    room_template[2][0].quantity=quant1;
    quant1=1;
    room_template[3]=new Room[quant1];
    room_template[3][0].quantity=quant1;
    quant1=1;
    room_template[4]=new Room[quant1];
    room_template[4][0].quantity=quant1;
    //room_template[0].weight=1;
    room_template[0][0].create (7, 4, 1280, 720);
    room_template[0][0].background.create(2, 1280, 720, 0, 0, 0.1);
    room_template[0][0].background.fill_frames("Textures/backgrounds/0/", 1);
    //room_template[0][0].drop_count=0;


    room_template[0][0].spawn[0].position.speed.x=0;
    room_template[0][0].spawn[0].position.speed.y=0;
    room_template[0][0].spawn[0].position.pos.x=75;
    room_template[0][0].spawn[0].position.pos.y=360;

    room_template[0][0].spawn[1].position.speed.x=0;
    room_template[0][0].spawn[1].position.speed.y=0;
    room_template[0][0].spawn[1].position.pos.x=1205;
    room_template[0][0].spawn[1].position.pos.y=360;

    room_template[0][0].spawn[2].position.speed.x=0;
    room_template[0][0].spawn[2].position.speed.y=0;
    room_template[0][0].spawn[2].position.pos.x=400;
    room_template[0][0].spawn[2].position.pos.y=360;

    room_template[0][0].spawn[3].position.speed.x=0;
    room_template[0][0].spawn[3].position.speed.y=0;
    room_template[0][0].spawn[3].position.pos.x=880;
    room_template[0][0].spawn[3].position.pos.y=360;

    /*room_template[0][0].platforms[0].type=2;
    room_template[0][0].platforms[0].pos.x=595;
    room_template[0][0].platforms[0].pos.y=5;

    room_template[0][0].platforms[0].type=2;
    room_template[0][0].platforms[0].pos.x=595;
    room_template[0][0].platforms[0].pos.y=715;

    room_template[0][0].platforms[2].type=3;
    room_template[0][0].platforms[2].pos.x=5;
    room_template[0][0].platforms[2].pos.y=315;

    room_template[0][0].platforms[3].type=3;
    room_template[0][0].platforms[3].pos.x=1275;
    room_template[0][0].platforms[3].pos.y=315;*/

    room_template[0][0].platforms[0].type=1;
    room_template[0][0].platforms[0].pos.x=31;
    room_template[0][0].platforms[0].pos.y=509;

    room_template[0][0].platforms[1].type=1;
    room_template[0][0].platforms[1].pos.x=31;
    room_template[0][0].platforms[1].pos.y=599;

    room_template[0][0].platforms[2].type=1;
    room_template[0][0].platforms[2].pos.x=121;
    room_template[0][0].platforms[2].pos.y=599;

    room_template[0][0].platforms[3].type=1;
    room_template[0][0].platforms[3].pos.x=1160;
    room_template[0][0].platforms[3].pos.y=510;

    room_template[0][0].platforms[4].type=1;
    room_template[0][0].platforms[4].pos.x=1160;
    room_template[0][0].platforms[4].pos.y=599;

    room_template[0][0].platforms[5].type=1;
    room_template[0][0].platforms[5].pos.x=1070;
    room_template[0][0].platforms[5].pos.y=599;

    room_template[0][0].platforms[6].type=0;
    room_template[0][0].platforms[6].pos_start.setXY(590, 100);
    room_template[0][0].platforms[6].pos_finish.setXY(590, 620);
    room_template[0][0].platforms[6].pos.setXY(590, 360);
    room_template[0][0].platforms[6].speed.setXY(0, 1);




    //room_template[1].weight=1;
    room_template[0][1].create(3, 4, 1280, 720);
    room_template[0][1].background.create(2, 1280, 720, 0, 0, 0.1);
    room_template[0][1].background.fill_frames("Textures/backgrounds/0/", 1);


    room_template[0][1].spawn[0].position.speed.x=0;
    room_template[0][1].spawn[0].position.speed.y=0;
    room_template[0][1].spawn[0].position.pos.x=75;
    room_template[0][1].spawn[0].position.pos.y=360;

    room_template[0][1].spawn[1].position.speed.x=0;
    room_template[0][1].spawn[1].position.speed.y=0;
    room_template[0][1].spawn[1].position.pos.x=1205;
    room_template[0][1].spawn[1].position.pos.y=360;

    room_template[0][1].spawn[2].position.speed.x=0;
    room_template[0][1].spawn[2].position.speed.y=0;
    room_template[0][1].spawn[2].position.pos.x=400;
    room_template[0][1].spawn[2].position.pos.y=360;

    room_template[0][1].spawn[3].position.speed.x=0;
    room_template[0][1].spawn[3].position.speed.y=0;
    room_template[0][1].spawn[3].position.pos.x=880;
    room_template[0][1].spawn[3].position.pos.y=360;


    /*room_template[0][1].platforms[0].type=2;
    room_template[0][1].platforms[0].pos.x=595;
    room_template[0][1].platforms[0].pos.y=5;

    room_template[0][1].platforms[0].type=2;
    room_template[0][1].platforms[0].pos.x=595;
    room_template[0][1].platforms[0].pos.y=715;

    room_template[0][1].platforms[2].type=3;
    room_template[0][1].platforms[2].pos.x=5;
    room_template[0][1].platforms[2].pos.y=315;

    room_template[0][1].platforms[3].type=3;
    room_template[0][1].platforms[3].pos.x=1275;
    room_template[0][1].platforms[3].pos.y=315;*/

    room_template[0][1].platforms[0].type=0;
    room_template[0][1].platforms[0].pos_start.setXY(590, 100);
    room_template[0][1].platforms[0].pos_finish.setXY(590, 620);
    room_template[0][1].platforms[0].pos.setXY(590, 100);
    room_template[0][1].platforms[0].speed.setXY(0, 1);

    room_template[0][1].platforms[1].type=0;
    room_template[0][1].platforms[1].pos_start.setXY(390, 100);
    room_template[0][1].platforms[1].pos_finish.setXY(390, 620);
    room_template[0][1].platforms[1].pos.setXY(390, 620);
    room_template[0][1].platforms[1].speed.setXY(0, -1);

    room_template[0][1].platforms[2].type=0;
    room_template[0][1].platforms[2].pos_start.setXY(790, 100);
    room_template[0][1].platforms[2].pos_finish.setXY(790, 620);
    room_template[0][1].platforms[2].pos.setXY(790, 620);
    room_template[0][1].platforms[2].speed.setXY(0, -1);



    room_template[0][2].create(7, 4, 1280, 720);
    room_template[0][2].background.create(2, 1280, 720, 0, 0, 0.1);
    room_template[0][2].background.fill_frames("Textures/backgrounds/0/", 1);


    room_template[0][2].spawn[0].position.speed.x=0;
    room_template[0][2].spawn[0].position.speed.y=0;
    room_template[0][2].spawn[0].position.pos.x=75;
    room_template[0][2].spawn[0].position.pos.y=360;

    room_template[0][2].spawn[1].position.speed.x=0;
    room_template[0][2].spawn[1].position.speed.y=0;
    room_template[0][2].spawn[1].position.pos.x=1205;
    room_template[0][2].spawn[1].position.pos.y=360;

    room_template[0][2].spawn[2].position.speed.x=0;
    room_template[0][2].spawn[2].position.speed.y=0;
    room_template[0][2].spawn[2].position.pos.x=400;
    room_template[0][2].spawn[2].position.pos.y=360;

    room_template[0][2].spawn[3].position.speed.x=0;
    room_template[0][2].spawn[3].position.speed.y=0;
    room_template[0][2].spawn[3].position.pos.x=880;
    room_template[0][2].spawn[3].position.pos.y=360;



    room_template[0][2].platforms[0].type=0;
    room_template[0][2].platforms[0].pos_start.setXY(390, 100);
    room_template[0][2].platforms[0].pos_finish.setXY(390, 520);
    room_template[0][2].platforms[0].pos.setXY(390, 100);
    room_template[0][2].platforms[0].speed.setXY(0, 1);

    room_template[0][2].platforms[1].type=0;
    room_template[0][2].platforms[1].pos_start.setXY(790, 100);
    room_template[0][2].platforms[1].pos_finish.setXY(790, 520);
    room_template[0][2].platforms[1].pos.setXY(790, 520);
    room_template[0][2].platforms[1].speed.setXY(0, -1);

    room_template[0][2].platforms[2].type=1;
    room_template[0][2].platforms[2].pos.x=31;
    room_template[0][2].platforms[2].pos.y=599;

    room_template[0][2].platforms[3].type=1;
    room_template[0][2].platforms[3].pos.x=355;
    room_template[0][2].platforms[3].pos.y=599;

    room_template[0][2].platforms[4].type=1;
    room_template[0][2].platforms[4].pos.x=835;
    room_template[0][2].platforms[4].pos.y=599;

    room_template[0][2].platforms[5].type=1;
    room_template[0][2].platforms[5].pos.x=1160;
    room_template[0][2].platforms[5].pos.y=599;


    room_template[0][2].platforms[6].type=0;
    room_template[0][2].platforms[6].pos_start.setXY(590, 100);
    room_template[0][2].platforms[6].pos_finish.setXY(590, 205);
    room_template[0][2].platforms[6].pos.setXY(590, 100);
    room_template[0][2].platforms[6].speed.setXY(0, 1);



    room_template[1][0].create (8, 6, 1280, 720);
    room_template[1][0].drop_count=1;
    room_template[1][0].drop=new Drop[room_template[1][0].drop_count];
    room_template[1][0].drop_discovered=new bool[room_template[1][0].drop_count];
    room_template[1][0].drop_discovered[0]=true;
    room_template[1][0].background.create(2, 1280, 720, 0, 0, 0.1);
    room_template[1][0].background.fill_frames("Textures/backgrounds/0/", 1);
    //room_template[0][0].drop_count=0;


    room_template[1][0].spawn[0].position.speed.x=0;
    room_template[1][0].spawn[0].position.speed.y=0;
    room_template[1][0].spawn[0].position.pos.x=75;
    room_template[1][0].spawn[0].position.pos.y=360;

    room_template[1][0].spawn[1].position.speed.x=0;
    room_template[1][0].spawn[1].position.speed.y=0;
    room_template[1][0].spawn[1].position.pos.x=1205;
    room_template[1][0].spawn[1].position.pos.y=360;

    room_template[1][0].spawn[2].position.speed.x=0;
    room_template[1][0].spawn[2].position.speed.y=0;
    room_template[1][0].spawn[2].position.pos.x=400;
    room_template[1][0].spawn[2].position.pos.y=360;

    room_template[1][0].spawn[3].position.speed.x=0;
    room_template[1][0].spawn[3].position.speed.y=0;
    room_template[1][0].spawn[3].position.pos.x=880;
    room_template[1][0].spawn[3].position.pos.y=360;

    room_template[1][0].spawn[4].position.speed.x=0;
    room_template[1][0].spawn[4].position.speed.y=0;
    room_template[1][0].spawn[4].position.pos.x=1045;
    room_template[1][0].spawn[4].position.pos.y=360;

    room_template[1][0].spawn[5].position.speed.x=0;
    room_template[1][0].spawn[5].position.speed.y=0;
    room_template[1][0].spawn[5].position.pos.x=235;
    room_template[1][0].spawn[5].position.pos.y=360;




    room_template[1][0].platforms[0].type=1;
    room_template[1][0].platforms[0].pos.x=31;
    room_template[1][0].platforms[0].pos.y=509;

    room_template[1][0].platforms[1].type=1;
    room_template[1][0].platforms[1].pos.x=31;
    room_template[1][0].platforms[1].pos.y=599;

    room_template[1][0].platforms[2].type=1;
    room_template[1][0].platforms[2].pos.x=121;
    room_template[1][0].platforms[2].pos.y=599;

    room_template[1][0].platforms[3].type=1;
    room_template[1][0].platforms[3].pos.x=1160;
    room_template[1][0].platforms[3].pos.y=510;

    room_template[1][0].platforms[4].type=1;
    room_template[1][0].platforms[4].pos.x=1160;
    room_template[1][0].platforms[4].pos.y=599;

    room_template[1][0].platforms[5].type=1;
    room_template[1][0].platforms[5].pos.x=1070;
    room_template[1][0].platforms[5].pos.y=599;
//guns
    room_template[1][0].platforms[6].type=0;
    room_template[1][0].platforms[6].pos_start.setXY(590, 100);
    room_template[1][0].platforms[6].pos_finish.setXY(590, 500);
    room_template[1][0].platforms[6].pos.setXY(590, 360);
    room_template[1][0].platforms[6].speed.setXY(0, 1);

    room_template[1][0].platforms[7].type=1;
    room_template[1][0].platforms[7].pos.x=595;
    room_template[1][0].platforms[7].pos.y=510;

    room_template[1][0].drop[0].type=8;
    room_template[1][0].drop[0].position.pos.x=640;
    room_template[1][0].drop[0].position.pos.y=490;

    room_template[2][0].create (1, 0, 1280, 720);
    room_template[2][0].background.create(1, 1280, 720, 0, 0, 0.1);
    room_template[2][0].background.fill_frames("Textures/backgrounds/1/", 1);

    room_template[2][0].platforms[0].type=0;
    room_template[2][0].platforms[0].pos_start.setXY(590, 100);
    room_template[2][0].platforms[0].pos_finish.setXY(590, 620);
    room_template[2][0].platforms[0].pos.setXY(590, 360);
    room_template[2][0].platforms[0].speed.setXY(0, 1);

    room_template[2][0].drop_count=4;
    room_template[2][0].drop=new Drop[room_template[2][0].drop_count];
    room_template[2][0].drop_discovered=new bool[room_template[2][0].drop_count];
    room_template[2][0].drop_discovered[0]=false;
    room_template[2][0].drop_discovered[1]=false;
    room_template[2][0].drop_discovered[2]=false;
    room_template[2][0].drop_discovered[3]=false;

    room_template[2][0].drop[0].position.pos.setXY(274, 600);
    room_template[2][0].drop[1].position.pos.setXY(518, 600);
    room_template[2][0].drop[2].position.pos.setXY(762, 600);
    room_template[2][0].drop[3].position.pos.setXY(1006, 600);

    room_template[2][0].drop[0].trade=true;
    room_template[2][0].drop[1].trade=true;
    room_template[2][0].drop[2].trade=true;
    room_template[2][0].drop[3].trade=true;


    room_template[3][0].create (9, 8, 1280, 720);
    room_template[3][0].background.create(2, 1280, 720, 0, 0, 0.1);
    room_template[3][0].background.fill_frames("Textures/backgrounds/0/", 1);


    room_template[3][0].platforms[0].type=1;
    room_template[3][0].platforms[0].pos.x=31;
    room_template[3][0].platforms[0].pos.y=509;

    room_template[3][0].platforms[1].type=1;
    room_template[3][0].platforms[1].pos.x=31;
    room_template[3][0].platforms[1].pos.y=599;

    room_template[3][0].platforms[2].type=1;
    room_template[3][0].platforms[2].pos.x=121;
    room_template[3][0].platforms[2].pos.y=599;

    room_template[3][0].platforms[3].type=1;
    room_template[3][0].platforms[3].pos.x=1160;
    room_template[3][0].platforms[3].pos.y=510;

    room_template[3][0].platforms[4].type=1;
    room_template[3][0].platforms[4].pos.x=1160;
    room_template[3][0].platforms[4].pos.y=599;

    room_template[3][0].platforms[5].type=1;
    room_template[3][0].platforms[5].pos.x=1070;
    room_template[3][0].platforms[5].pos.y=599;

    room_template[3][0].platforms[6].type=0;
    room_template[3][0].platforms[6].pos_start.setXY(590, 100);
    room_template[3][0].platforms[6].pos_finish.setXY(590, 620);
    room_template[3][0].platforms[6].pos.setXY(590, 360);
    room_template[3][0].platforms[6].speed.setXY(0, 1);

    room_template[3][0].platforms[7].type=1;
    room_template[3][0].platforms[7].pos.x=211;
    room_template[3][0].platforms[7].pos.y=599;

    room_template[3][0].platforms[8].type=1;
    room_template[3][0].platforms[8].pos.x=980;
    room_template[3][0].platforms[8].pos.y=599;

    room_template[3][0].spawn[0].position.speed.x=0;
    room_template[3][0].spawn[0].position.speed.y=0;
    room_template[3][0].spawn[0].position.pos.x=75;
    room_template[3][0].spawn[0].position.pos.y=360;

    room_template[3][0].spawn[1].position.speed.x=0;
    room_template[3][0].spawn[1].position.speed.y=0;
    room_template[3][0].spawn[1].position.pos.x=1205;
    room_template[3][0].spawn[1].position.pos.y=360;

    room_template[3][0].spawn[2].position.speed.x=0;
    room_template[3][0].spawn[2].position.speed.y=0;
    room_template[3][0].spawn[2].position.pos.x=175;
    room_template[3][0].spawn[2].position.pos.y=360;

    room_template[3][0].spawn[3].position.speed.x=0;
    room_template[3][0].spawn[3].position.speed.y=0;
    room_template[3][0].spawn[3].position.pos.x=1145;
    room_template[3][0].spawn[3].position.pos.y=360;

    room_template[3][0].spawn[4].position.speed.x=0;
    room_template[3][0].spawn[4].position.speed.y=0;
    room_template[3][0].spawn[4].position.pos.x=285;
    room_template[3][0].spawn[4].position.pos.y=360;

    room_template[3][0].spawn[5].position.speed.x=0;
    room_template[3][0].spawn[5].position.speed.y=0;
    room_template[3][0].spawn[5].position.pos.x=1055;
    room_template[3][0].spawn[5].position.pos.y=360;

    room_template[3][0].spawn[6].position.speed.x=0;
    room_template[3][0].spawn[6].position.speed.y=0;
    room_template[3][0].spawn[6].position.pos.x=965;
    room_template[3][0].spawn[6].position.pos.y=360;

    room_template[3][0].spawn[7].position.speed.x=0;
    room_template[3][0].spawn[7].position.speed.y=0;
    room_template[3][0].spawn[7].position.pos.x=375;
    room_template[3][0].spawn[7].position.pos.y=360;


    room_template[4][0].create (0, 1, 1280, 720);
    room_template[4][0].background.create(1, 1280, 720, 0, 0, 0.1);
    room_template[4][0].background.fill_frames("Textures/backgrounds/1/", 1);
    room_template[4][0].spawn[0].position.pos.setXY(900, 600);
    room_template[4][0].spawn[0].position.speed.setXY(0, 100);
    room_template[4][0].spawn[0].weight=2;
    room_template[4][0].boss=true;
    Music music;
    music.setLoop(true);




    Room* room=new Room[room_count];
    Room lobby;

    /*lobby.platforms=new platf[1];
    lobby.platform_count=1;

    lobby.platforms[0].pos.setXY(497, 250);
    lobby.platforms[0].pos_start.setXY(497, 250);
    lobby.platforms[0].pos_finish.setXY(497, 500);
    lobby.platforms[0].type=0;
    lobby.platforms[0].speed.setXY(0, 1);*/

    Animation spark;
    spark.create(1, 8, 8, 4, 4, 0.1);
    spark.fill_frames("Textures/misc/spark-", 1);
    int wasButtons=0;
    Particle* particle=new Particle[particle_count];

    Texture money_texture;
    Sprite money;
//Text
    money_texture.loadFromFile("Textures/misc/money.png");
    money.setTexture(money_texture);


    Texture dynamite_texture;
    Sprite dynamite;
//Text
    dynamite_texture.loadFromFile("Textures/misc/dynamite.png");
    dynamite.setTexture(dynamite_texture);


//height
    Texture frame_texture;
    Sprite frame;
    Texture price_texture;
    Sprite price_sprite;



    frame_texture.loadFromFile("Textures/misc/frame.png");
    frame.setTexture(frame_texture);

    Font font;
    font.loadFromFile("Textures/misc/font.ttf");
    Text name;
    Text stats;
    Text price;

    pause_text.setFont(font);
    pause_text.setCharacterSize(40);
    pause_text.setPosition(100, 160);
    pause_text.setString("Paused");
    pause_text.setFillColor(Color(0, 127, 0));

    name.setFont(font);
    stats.setFont(font);
    price.setFont(font);


    name.setCharacterSize(20);
    stats.setCharacterSize(10);
    price.setCharacterSize(10);


    name.setFillColor(Color(0, 127, 0));
    stats.setFillColor(Color(0, 127, 0));


    Text money_count;
    money_count.setFont(font);

    Text dynamite_count;
    dynamite_count.setFont(font);

    money_count.setCharacterSize(32);
    money_count.setFillColor(Color(0, 255, 40));

    dynamite_count.setCharacterSize(32);
    dynamite_count.setFillColor(Color(255, 0, 0));

    //name.setStyle(Text::Bold);
    //stats.setStyle(Text::Bold);

    Animation rarity[6];
    rarity[0].create (1, 32, 32, 16, 16, 0.1);
    rarity[1].create (1, 32, 32, 16, 16, 0.1);
    rarity[2].create (1, 32, 32, 16, 16, 0.1);
    rarity[3].create (1, 32, 32, 16, 16, 0.1);
    rarity[4].create (2, 64, 64, 32, 32, 0.06);
    rarity[5].create (4, 64, 64, 32, 32, 0.08);
    rarity[0].fill_frames("Textures/misc/empty-", 1);
    rarity[1].fill_frames ("Textures/misc/uncommon-", 1);
    rarity[2].fill_frames ("Textures/misc/rare-", 1);
    rarity[3].fill_frames ("Textures/misc/epic-", 1);
    rarity[4].fill_frames ("Textures/misc/leg-", 1);
    rarity[5].fill_frames ("Textures/misc/myth-", 1);

    drop = new Drop[drop_count];
    Platform** platform = new Platform*[platform_types];
    platform[0] = new Platform[100];
    platform[0][0].quantity = 100;
    platform[1] = new Platform[100];
    platform[1][0].quantity=100;
    platform[2]=new Platform[100];
    platform[2][0].quantity=100;
    platform[3]=new Platform[100];
    platform[3][0].quantity=100;

    enemy[0] = new Entity[100];
    enemy[0][0].quantity = 100;
    for (int i = 0; i < enemy[0][0].quantity; i++)
    {

        enemy[0][i].hit_buffer.loadFromFile("Sounds/robots/0/hit.wav");
        enemy[0][i].hit_sound.setBuffer(enemy[0][i].hit_buffer);

        //std::cout << "test1";
        enemy[0][i].drops=2;
        enemy[0][i].drop_max=new int[enemy[0][i].drops];
        enemy[0][i].drop_min=new int[enemy[0][i].drops];
        enemy[0][i].drop_type=new int[enemy[0][i].drops];
        //std::cout << "test2";
        enemy[0][i].drop_type[0]=0;
        enemy[0][i].drop_max[0]=1001;
        enemy[0][i].drop_min[0]=999;
        enemy[0][i].drop_type[1]=7;
        enemy[0][i].drop_max[1]=1001;
        enemy[0][i].drop_min[1]=993;//width
        //std::cout << "test3";
        enemy[0][i].shoot_buffer.loadFromFile("Sounds/robots/0/shoot.wav");
        enemy[0][i].shoot_sound.setBuffer(enemy[0][i].shoot_buffer);

        enemy[0][i].proj.create (1, 32, 12, 16, 6, 0.1);
        enemy[0][i].proj.fill_frames ("Textures/robots/0/bullet-", 1);
        enemy[0][i].blast.create (1, 16, 16, 8, 8, 0.1);
        enemy[0][i].blast.fill_frames ("Textures/robots/0/blast-", 1);
        enemy[0][i].blast.frame_pos=new double[5];
        enemy[0][i].blast.frame_pos[0]=0.1;
        enemy[0][i].blast.frame_pos[1]=0.1;
        enemy[0][i].blast.frame_pos[2]=0.1;
        enemy[0][i].blast.frame_pos[3]=0.1;
        enemy[0][i].blast.frame_pos[4]=0.1;
        enemy[0][i].head.create (2, 21, 24, 11, 7, 0.175);
        enemy[0][i].head.fill_frames ("Textures/robots/0/shoot-", 1);
        enemy[0][i].body.create (2, 21, 24, 11, 7, 0.175);
        enemy[0][i].tracks.create (2, 17, 8, 9, -13, 0.175);
        enemy[0][i].startup.create (4, 22, 24, 12, 7, 0.1);
        enemy[0][i].body.fill_frames ("Textures/robots/0/body-", 1);
        enemy[0][i].tracks.fill_frames ("Textures/robots/0/tracks-", 1);
        enemy[0][i].startup.fill_frames ("Textures/robots/0/startup-", 1);
        enemy[0][i].down.loadFromFile ("Textures/robots/0/jump.png");
        enemy[0][i].startup.frame_pos = new double[enemy[0][i].max_startup + 1];
        enemy[0][i].max_speed = 2;
        enemy[0][i].max_armor = 30;
        enemy[0][i].max_health = 0;
        enemy[0][i].startup.f_count = enemy[0][i].max_startup + 1;
        enemy[0][i].height = 19;
        enemy[0][i].head_height = 16;
        enemy[0][i].width=16;
        enemy[0][i].strafe_force = 1;
        //enemy[0][i].position.pos.x = 550;
        //enemy[0][i].position.pos.y = 400;
        for (int j = 0; j < 14; j++)
        {
            enemy[0][i].startup.frame_pos[j] = 3.1;
        }
        for (int j = 14; j < 28; j++)
        {
            enemy[0][i].startup.frame_pos[j] = 2.1;
        }
        for (int j = 28; j < 42; j++)
        {
            enemy[0][i].startup.frame_pos[j] = 1.1;
        }
        enemy[0][i].startup.frame_pos[42] = 0.1;
    }
    //enemy[0][0].armor = enemy[0][0].max_armor;
    /*enemy[0][0].phase = 0;
    //enemy[0][0].is=true;
    //enemy[0][1].armor = enemy[0][0].max_armor;
    enemy[0][1].phase = 0;
    enemy[0][1].position.pos.x = 650;
    enemy[0][1].position.pos.y = 400;
    //enemy[0][1].is=true;
    //enemy[0][2].armor = enemy[0][0].max_armor;
    enemy[0][2].phase = 0;
    enemy[0][2].position.pos.x = 750;
    enemy[0][2].position.pos.y = 400;
    //enemy[0][2].is=true;
    //enemy[0][3].armor = enemy[0][0].max_armor;
    enemy[0][3].phase = 0;
    enemy[0][3].position.pos.x = 850;
    enemy[0][3].position.pos.y = 400;*/
    //enemy[0][3].is=true;

    lobby.is=true;
    lobby.pos.x=0;
    lobby.pos.y=0;
    lobby.rectangle.setPosition(36, 0);
    lobby.rectangle.setWH(929, 715);
    lobby.visited=true;




    enemy[1][0].quantity=20;


    for (int i=0; i<enemy[1][0].quantity; i++)
    {
        enemy[1][i].exp_buffer.loadFromFile("Sounds/guns/1/explosion0.wav");
        enemy[1][i].exp_sound.setBuffer(enemy[1][i].exp_buffer);
        enemy[1][i].blast.create (5, 64, 64, 32, 32, 0.1);
        enemy[1][i].blast.fill_frames ("Textures/guns/1/blast-", 1);
        enemy[1][i].body.create(8, 34, 34, 17, 17, 0.12);
        enemy[1][i].body.fill_frames("Textures/guns/1/bullet-", 1);
        enemy[1][i].damage=50;
        enemy[1][i].width=9;
        enemy[1][i].head_height=20;
        enemy[1][i].height=4;
        enemy[1][i].weight=3;
        enemy[1][i].max_health=90;

    }


    enemy[2][0].quantity = 1;
    for (int i = 0; i < enemy[2][0].quantity; i++)
    {

        enemy[2][i].hit_buffer.loadFromFile("Sounds/robots/0/hit.wav");
        enemy[2][i].hit_sound.setBuffer(enemy[2][i].hit_buffer);

        //std::cout << "test1";
        enemy[2][i].drops=2;
        enemy[2][i].drop_max=new int[enemy[2][i].drops];
        enemy[2][i].drop_min=new int[enemy[2][i].drops];
        enemy[2][i].drop_type=new int[enemy[2][i].drops];
        //std::cout << "test2";
        enemy[2][i].drop_type[0]=0;
        enemy[2][i].drop_max[0]=15501;
        enemy[2][i].drop_min[0]=10001;
        enemy[2][i].drop_type[1]=7;
        enemy[2][i].drop_max[1]=6501;
        enemy[2][i].drop_min[1]=4501;//width
        //std::cout << "test3";
        enemy[2][i].shoot_buffer.loadFromFile("Sounds/guns/0/0.wav");
        enemy[2][i].shoot_sound.setBuffer(enemy[2][i].shoot_buffer);

        enemy[2][i].proj.create (1, 32, 12, 16, 6, 0.1);
        enemy[2][i].proj.fill_frames ("Textures/robots/0/bullet-", 1);
        enemy[2][i].blast.create (1, 16, 16, 8, 8, 0.1);
        enemy[2][i].blast.fill_frames ("Textures/robots/0/blast-", 1);
        enemy[2][i].blast.frame_pos=new double[5];
        enemy[2][i].blast.frame_pos[0]=0.1;
        enemy[2][i].blast.frame_pos[1]=0.1;
        enemy[2][i].blast.frame_pos[2]=0.1;
        enemy[2][i].blast.frame_pos[3]=0.1;
        enemy[2][i].blast.frame_pos[4]=0.1;
        enemy[2][i].head.create (2, 64, 14, 20, 9, 0.175);
        enemy[2][i].head.fill_frames ("Textures/robots/2/head-", 1);
        enemy[2][i].heat[0].create (2, 64, 14, 20, 9, 0.175);
        enemy[2][i].heat[1].create (2, 64, 14, 20, 9, 0.175);
        enemy[2][i].heat[2].create (2, 64, 14, 20, 9, 0.175);
        enemy[2][i].heat[3].create (2, 64, 14, 20, 9, 0.175);
        enemy[2][i].heat[4].create (2, 64, 14, 20, 9, 0.175);
        enemy[2][i].heat[0].fill_frames ("Textures/robots/2/head1-", 1);
        enemy[2][i].heat[1].fill_frames ("Textures/robots/2/head2-", 1);
        enemy[2][i].heat[2].fill_frames ("Textures/robots/2/head3-", 1);
        enemy[2][i].heat[3].fill_frames ("Textures/robots/2/head4-", 1);
        enemy[2][i].heat[4].fill_frames ("Textures/robots/2/head5-", 1);
        enemy[2][i].body.create (1, 44, 23, 22, 0, 0.175);
        //enemy[2][i].tracks.create (2, 17, 8, 9, -13, 0.175);
        //enemy[2][i].startup.create (4, 22, 24, 12, 7, 0.1);
        enemy[2][i].body.fill_frames ("Textures/robots/2/body-", 1);
        //enemy[2][i].tracks.fill_frames ("Textures/robots/0/tracks-", 1);
        //enemy[2][i].startup.fill_frames ("Textures/robots/0/startup-", 1);
        //enemy[2][i].down.loadFromFile ("Textures/robots/0/jump.png");
        //enemy[2][i].startup.frame_pos = new double[enemy[2][i].max_startup + 1];
        //enemy[2][i].max_speed = 2;
        enemy[2][i].max_armor = 320;
        enemy[2][i].max_health = 0;
        //enemy[2][i].startup.f_count = enemy[2][i].max_startup + 1;
        enemy[2][i].height = 23;
        enemy[2][i].head_height = 20;
        enemy[2][i].width=24;
        enemy[2][i].max_aim=12;
        enemy[2][i].boss=true;
        enemy[2][i].weight=2;

        //enemy[2][i].strafe_force = 1;
        //enemy[2][i].position.pos.x = 550;
        //enemy[2][i].position.pos.y = 400;
        /*for (int j = 0; j < 14; j++)
        {
            enemy[2][i].startup.frame_pos[j] = 3.1;
        }
        for (int j = 14; j < 28; j++)
        {
            enemy[2][i].startup.frame_pos[j] = 2.1;
        }
        for (int j = 28; j < 42; j++)
        {
            enemy[2][i].startup.frame_pos[j] = 1.1;
        }
        enemy[2][i].startup.frame_pos[42] = 0.1;
        */
    }
    //std::cout << "1";

    enemy[3] = new Entity[1];
    enemy[3][0].quantity = 1;
    for (int i = 0; i < enemy[3][0].quantity; i++)
    {

        enemy[3][i].hit_buffer.loadFromFile("Sounds/robots/0/hit.wav");
        enemy[3][i].hit_sound.setBuffer(enemy[3][i].hit_buffer);

        //std::cout << "test1";
        enemy[3][i].drops=2;
        enemy[3][i].drop_max=new int[enemy[3][i].drops];
        enemy[3][i].drop_min=new int[enemy[3][i].drops];
        enemy[3][i].drop_type=new int[enemy[3][i].drops];
        //std::cout << "test2";
        enemy[3][i].drop_type[0]=0;
        enemy[3][i].drop_max[0]=2501;
        enemy[3][i].drop_min[0]=999;
        enemy[3][i].drop_type[1]=7;
        enemy[3][i].drop_max[1]=4501;
        enemy[3][i].drop_min[1]=1993;//width
        //std::cout << "test3";
        enemy[3][i].shoot_buffer.loadFromFile("Sounds/robots/0/shoot.wav");
        enemy[3][i].shoot_sound.setBuffer(enemy[3][i].shoot_buffer);

        enemy[3][i].proj.create (1, 40, 15, 25, 12, 0.1);
        enemy[3][i].proj.fill_frames ("Textures/robots/3/projectile-", 1);
        enemy[3][i].blast.create (5, 64, 64, 32, 32, 0.1);
        enemy[3][i].blast.fill_frames ("Textures/guns/1/blast-", 1);
        enemy[3][i].blast.f_count=51;
        enemy[3][i].blast.frame_pos=new double[enemy[3][i].blast.f_count];
        for (int j=0; j<10; j++)
        {
            enemy[3][i].blast.frame_pos[j]=4.1;
        }
        for (int j=10; j<20; j++)
        {
            enemy[3][i].blast.frame_pos[j]=3.1;
        }
        for (int j=20; j<30; j++)
        {
            enemy[3][i].blast.frame_pos[j]=2.1;
        }
        for (int j=30; j<40; j++)
        {
            enemy[3][i].blast.frame_pos[j]=1.1;
        }
        for (int j=40; j<51; j++)
        {
            enemy[3][i].blast.frame_pos[j]=0.1;
        }

        /*enemy[3][i].blast.frame_pos[0]=0.1;
        enemy[3][i].blast.frame_pos[1]=0.1;
        enemy[3][i].blast.frame_pos[2]=0.1;
        enemy[3][i].blast.frame_pos[3]=0.1;
        enemy[3][i].blast.frame_pos[4]=0.1;*/
        enemy[3][i].head.create (2, 26, 7, 4, 4, 0.1);
        enemy[3][i].head.fill_frames ("Textures/robots/3/head-", 1);
        enemy[3][i].body.create (1, 41, 11, 21, 2, 0.175);
        //enemy[2][i].tracks.create (2, 17, 8, 9, -13, 0.175);
        //enemy[2][i].startup.create (4, 22, 24, 12, 7, 0.1);
        enemy[3][i].body.fill_frames ("Textures/robots/3/body-", 1);

        //enemy[2][i].tracks.fill_frames ("Textures/robots/0/tracks-", 1);
        //enemy[2][i].startup.fill_frames ("Textures/robots/0/startup-", 1);
        //enemy[2][i].down.loadFromFile ("Textures/robots/0/jump.png");
        //enemy[2][i].startup.frame_pos = new double[enemy[2][i].max_startup + 1];
        //enemy[2][i].max_speed = 2;
        enemy[3][i].max_armor = 600;
        enemy[3][i].max_health = 0;
        //enemy[2][i].startup.f_count = enemy[2][i].max_startup + 1;
        enemy[3][i].height = 9;
        enemy[3][i].head_height = 30;
        enemy[3][i].width=24;
        enemy[3][i].max_aim=60;
        enemy[3][i].boss=true;
        enemy[3][i].weight=2;
        enemy[3][i].damage=5;

        //enemy[2][i].strafe_force = 1;
        //enemy[2][i].position.pos.x = 550;
        //enemy[2][i].position.pos.y = 400;
        /*for (int j = 0; j < 14; j++)
        {
            enemy[2][i].startup.frame_pos[j] = 3.1;
        }
        for (int j = 14; j < 28; j++)
        {
            enemy[2][i].startup.frame_pos[j] = 2.1;
        }
        for (int j = 28; j < 42; j++)
        {
            enemy[2][i].startup.frame_pos[j] = 1.1;
        }
        enemy[2][i].startup.frame_pos[42] = 0.1;
        */
    }
    //std::cout << "2";
    for (int i = 0; i < platform[0][0].quantity; i++)
    {
        platform[0][i].create (497, 250, 497, 500, 497, 250, jump_on, 100, 1);
        platform[0][i].up.create (2, 118, 37, 9, 3, 0.2);
        platform[0][i].up.fill_frames ("Textures/platforms/0/up-", 1);
        platform[0][i].down.create (2, 118, 37, 9, 3, 0.2);
        platform[0][i].down.fill_frames ("Textures/platforms/0/down-", 1);
    }
    for (int i=0; i<platform[1][0].quantity; i++)
    {
        platform[1][i].create(0, 0, 0, 0, 0, 0, 1, 90, 90);
        platform[1][i].up.create(3, 90, 90, 0, 0, 0.1);
        platform[1][i].up.fill_frames("Textures/platforms/1/", 1);
    }
    for (int i=0; i<platform[2][0].quantity; i++)
    {
        platform[2][i].create(0, 0, 0, 0, 0, 0, 1, 100, 29);
        platform[2][i].up.create(2, 100, 30, 0, 2, 0.1);
        platform[2][i].up.fill_frames("Textures/platforms/2/", 1);
    }
    for (int i=0; i<platform[3][0].quantity; i++)
    {
        platform[3][i].create(0, 0, 0, 0, 0, 0, 1, 29, 100);
        platform[3][i].up.create(2, 30, 100, 2, 0, 0.1);
        platform[3][i].up.fill_frames("Textures/platforms/3/", 1);
    }

    //platform[1][0].is=true;
    //platform[1][0].pos.setXY(37, 449);
    Projectile *proj = new Projectile[projectiles_count];
    Projectile *enemy_proj = new Projectile[projectiles_count];
    for (int i = 0; i < projectiles_count; i++)
    {
        proj[i].is = false;
    }
    RenderWindow window (VideoMode (width, height), "The Guns Dungeons", Style::None);
    window.create (VideoMode (width, height), "The Guns Dungeons", Style::None);
    View camera;
    camera.reset (FloatRect (0, 0, width, height) );
    float camera_x = 0;
    float camera_y = 0;
    window.setMouseCursorVisible (false);
    window.setSize (Vector2u (VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height) );
    window.setPosition (Vector2i (0, 0) );
    window.setMouseCursorVisible (false);
    Clock clock;
    //CircleShape shape(250.f);
    //shape.setFillColor(Color::Green);
    //rectangle

    //player.gun_holding=1;


    //player=player_stock;

    player_stock.body.create (4, 12, 24, 6, 0, 0.073);
    player_stock.body.fill_frames ("Textures/player/walk-", 1);
    player_stock.head.create (1, 6, 9, 3, 9, 0.1);
    player_stock.head.fill_frames ("Textures/player/head-", 1);
    player_stock.head_up.create (1, 6, 8, 4, 8, 0.1);
    player_stock.head_up.fill_frames ("Textures/player/head_up-", 1);
    player_stock.head_down.create (1, 7, 7, 2, 7, 0.1);
    player_stock.head_down.fill_frames ("Textures/player/head_down-", 1);
    player_stock.position.pos.x = 50;
    player_stock.position.pos.y = 400;
    player_stock.idle.loadFromFile ("Textures/player/idle.png");
    player_stock.up.loadFromFile ("Textures/player/up.png");
    player_stock.down.loadFromFile ("Textures/player/down.png");
    player_stock.armor = 0;
    player_stock.hit_buffer.loadFromFile("Sounds/misc/hit.wav");
    player_stock.hit_sound.setBuffer(player_stock.hit_buffer);


    //int i=0;
    guns[0].type = 0;
    guns[0].item=10;

    guns[0].buffer.loadFromFile("Sounds/guns/0/0.wav");
    guns[0].sound.setBuffer(guns[0].buffer);
    //std::cout << guns[0].sound.getVolume();
    //guns[0].sound.setVolume(100);
    //std::cout << guns[0].sound.getVolume();
    //guns[0].sound.play();
    guns[0].max_distance=300;
    guns[0].projectile.create (1, 32, 8, 10, 4, 0.1);
    guns[0].projectile.fill_frames ("Textures/guns/0/bullet-", 1);
    guns[0].blast.create (1, 16, 16, 8, 8, 0.1);
    guns[0].blast.frame_pos=new double[5];
    guns[0].blast.frame_pos[0]=0.1;
    guns[0].blast.frame_pos[1]=0.1;
    guns[0].blast.frame_pos[2]=0.1;
    guns[0].blast.frame_pos[3]=0.1;
    guns[0].blast.frame_pos[4]=0.1;
    guns[0].blast.fill_frames ("Textures/guns/0/blast-", 1);
    guns[0].create (10);
    guns[0].animation.create (2, 28, 9, 11, 4, 0.1);
    guns[0].animation.fill_frames ("Textures/guns/0/", 1);
    guns[0].upper_animation.create (2, 22, 24, 9, 13, 0.1);
    guns[0].upper_animation.fill_frames ("Textures/guns/0/up-", 1);
    for (int i = 6; i < 11; i++)
    {//play
        guns[0].animation.frame_pos[i] = 1.1;
        guns[0].upper_animation.frame_pos[i] = 1.1;
    }
    for (int i = 0; i < 6; i++)
    {
        guns[0].animation.frame_pos[i] = 0.1;
        guns[0].upper_animation.frame_pos[i] = 0.1;
    }
    //guns[1].exp_buffer.loadFromFile("Sounds/guns/1/explosion0.wav");
    guns[1].type=1;
    guns[1].create(5);
    guns[1].animation.create(3, 17, 17, 8, 11, 0.1);
    guns[1].animation.fill_frames("Textures/guns/1/animation-", 1);
    guns[1].upper_animation.create(3, 17, 18, 11, 8, 0.1);
    guns[1].upper_animation.fill_frames("Textures/guns/1/upper_animation-", 1);
    guns[1].animation.frame_pos[0] = 0.1;
    guns[1].upper_animation.frame_pos[0] = 0.1;
    guns[1].animation.frame_pos[5] = 1.1;
    guns[1].upper_animation.frame_pos[5] = 1.1;
    guns[1].radius=60;
    guns[1].explosion_knockback=12;
    guns[1].damage=40;
    guns[1].self_damage_multiplier=0.1;
    guns[1].min_damage=0;

    for (int i=1; i<5; i++)
    {
        guns[1].animation.frame_pos[i]=2.1;
        guns[1].upper_animation.frame_pos[i]=2.1;
    }





    guns[2].damage=30;
    guns[2].min_damage=30;
    guns[2].item=11;
    guns[2].knockback=3;
    guns[2].proj_speed=48;
    guns[2].radius=6;
    guns[2].type = 1;
    guns[2].buffer.loadFromFile("Sounds/guns/2/0.wav");
    guns[2].sound.setBuffer(guns[2].buffer);
    //std::cout << guns[0].sound.getVolume();
    //guns[0].sound.setVolume(100);
    //std::cout << guns[0].sound.getVolume();
    //guns[0].sound.play();
    guns[2].max_distance=400;
    guns[2].projectile.create (1, 40, 8, 18, 4, 0.1);
    guns[2].projectile.fill_frames ("Textures/guns/2/bullet-", 1);
    guns[2].blast.create (1, 16, 16, 8, 8, 0.1);
    guns[2].blast.frame_pos=new double[5];
    guns[2].blast.frame_pos[0]=0.1;
    guns[2].blast.frame_pos[1]=0.1;
    guns[2].blast.frame_pos[2]=0.1;
    guns[2].blast.frame_pos[3]=0.1;
    guns[2].blast.frame_pos[4]=0.1;
    guns[2].blast.fill_frames ("Textures/guns/0/blast-", 1);
    guns[2].create (30);
    guns[2].animation.create (3, 35, 12, 11, 4, 0.1);
    guns[2].animation.fill_frames ("Textures/guns/2/", 1);
    guns[2].upper_animation.create (3, 24, 27, 7, 16, 0.1);
    guns[2].upper_animation.fill_frames ("Textures/guns/2/up-", 1);
    guns[2].animation.frame_pos[30] = 0.1;
    guns[2].upper_animation.frame_pos[30] = 0.1;
    for (int i = 18; i < 30; i++)
    {//play
        guns[2].animation.frame_pos[i] = 1.1;
        guns[2].upper_animation.frame_pos[i] = 1.1;
    }
    for (int i = 9; i < 18; i++)
    {
        guns[2].animation.frame_pos[i] = 2.1;
        guns[2].upper_animation.frame_pos[i] = 2.1;
    }
    for (int i = 0; i < 9; i++)
    {
        guns[2].animation.frame_pos[i] = 0.1;
        guns[2].upper_animation.frame_pos[i] = 0.1;
    }
    guns[2].pellet_spread=0.03;
    //start.setBlock(496, 0, 497, 281, 1);
    //start.setBlock(598, 0, 599, 281, 1);
    Map M;
    //int rectangle_count = 1;
    int breath_count = 61;
    bool updn = false;
    /*Rectangle *rectangle;
    rectangle = new Rectangle[rectangle_count];
    rectangle[0].setPosition (36, 0);
    rectangle[0].setWH (929, 715);*/
    Texture heart;
    heart.loadFromFile ("Textures/misc/heart.png");
    Sprite heart_s;
    heart_s.setTexture (heart);
    Texture armor;
    armor.loadFromFile ("Textures/misc/armor.png");
    Sprite armor_s;
    armor_s.setTexture (armor);



    item[0].animation.create (1, 24, 24, 12, 12, 0.1);
    item[0].animation.fill_frames ("Textures/items/1-", 1);
    item[0].rarity = common;
    item[0].auto_pickup=true;
    item[0].pickup_buffer.loadFromFile("Sounds/misc/money_pickup.wav");
    item[0].pickup_sound.setBuffer(item[0].pickup_buffer);
    item[0].stock_price=5;

    /*drop[1].type = 1;
    drop[1].animation = item[drop[1].type].animation;
    drop[1].glint = rarity[item[drop[1].type].rarity];
    drop[1].position.pos.x = 400;//camera_x
    drop[1].position.pos.y = 400;
    drop[1].position.speed.x = 0;
    drop[1].position.speed.y = 0;
    drop[1].counter = 25;*/
    //drop[1].is = true;

    item[1].animation.create (1, 24, 24, 12, 12, 0.1);
    item[1].animation.fill_frames ("Textures/items/2-", 1);
    item[1].rarity = uncommon;
    item[1].auto_pickup=true;
    item[1].pickup_buffer.loadFromFile("Sounds/misc/money_pickup.wav");
    item[1].pickup_sound.setBuffer(item[1].pickup_buffer);
    item[1].stock_price=10;

    /*drop[2].type = 2;
    drop[2].animation = item[drop[2].type].animation;
    drop[2].glint = rarity[item[drop[2].type].rarity];
    drop[2].position.pos.x = 450;//camera_x
    drop[2].position.pos.y = 400;
    drop[2].position.speed.x = 0;
    drop[2].position.speed.y = 0;
    drop[2].counter = 3;*/
    //drop[2].is = true;

    item[2].animation.create (1, 24, 24, 12, 12, 0.1);
    item[2].animation.fill_frames ("Textures/items/3-", 1);
    item[2].rarity = rare;
    item[2].auto_pickup=true;
    item[2].pickup_buffer.loadFromFile("Sounds/misc/money_pickup.wav");
    item[2].pickup_sound.setBuffer(item[2].pickup_buffer);
    item[2].stock_price=100;

    /*drop[3].type = 3;
    drop[3].animation = item[drop[3].type].animation;
    drop[3].glint = rarity[item[drop[3].type].rarity];
    drop[3].position.pos.x = 500;//camera_x
    drop[3].position.pos.y = 400;
    drop[3].position.speed.x = 0;
    drop[3].position.speed.y = 0;
    drop[3].counter = 5;*/
    //drop[3].is = true;

    item[3].animation.create (1, 24, 24, 12, 12, 0.1);
    item[3].animation.fill_frames ("Textures/items/4-", 1);
    item[3].rarity = epic;
    item[3].auto_pickup=true;
    item[3].pickup_buffer.loadFromFile("Sounds/misc/money_pickup.wav");
    item[3].pickup_sound.setBuffer(item[3].pickup_buffer);
    item[3].stock_price=200;

    /*drop[4].type = 4;
    drop[4].animation = item[drop[4].type].animation;
    drop[4].glint = rarity[item[drop[4].type].rarity];
    drop[4].position.pos.x = 550;//camera_x
    drop[4].position.pos.y = 400;
    drop[4].position.speed.x = 0;
    drop[4].position.speed.y = 0;
    drop[4].counter = 50;*/
    //drop[4].is = true;

    item[4].animation.create (1, 24, 24, 12, 12, 0.1);
    item[4].animation.fill_frames ("Textures/items/5-", 1);
    item[4].rarity = legendary;
    item[4].auto_pickup=true;
    item[4].pickup_buffer.loadFromFile("Sounds/misc/money_pickup.wav");
    item[4].pickup_sound.setBuffer(item[4].pickup_buffer);
    item[4].stock_price=1000;

    /*drop[5].type = 5;
    drop[5].animation = item[drop[5].type].animation;
    drop[5].glint = rarity[item[drop[5].type].rarity];
    drop[5].position.pos.x = 600;//camera_x
    drop[5].position.pos.y = 400;
    drop[5].position.speed.x = 0;
    drop[5].position.speed.y = 0;
    drop[5].counter = 30;*/
    //drop[5].is = true;


    item[5].animation.create (1, 24, 24, 12, 12, 0.1);
    item[5].animation.fill_frames ("Textures/items/6-", 1);
    item[5].rarity = mythic;
    item[5].auto_pickup=true;
    item[5].pickup_buffer.loadFromFile("Sounds/misc/money_pickup.wav");
    item[5].pickup_sound.setBuffer(item[5].pickup_buffer);
    item[5].stock_price=2000;

    /*drop[6].type = 6;
    drop[6].animation = item[drop[6].type].animation;
    drop[6].glint = rarity[item[drop[6].type].rarity];
    drop[6].position.pos.x = 650;//camera_x
    drop[6].position.pos.y = 400;
    drop[6].position.speed.x = 0;
    drop[6].position.speed.y = 0;
    drop[6].counter = 22;*/
    item[6].animation.create (1, 24, 24, 12, 12, 0.1);
    item[6].animation.fill_frames ("Textures/items/0-", 1);
    item[6].name = "Stone Of Fortune";
    item[6].description = "Increases probability\nof a good event.";
    item[6].rarity = rare;
    item[6].auto_pickup=false;
    item[6].stock_price=10;

    item[7].animation.create (1, 24, 24, 12, 12, 0.1);
    item[7].animation.fill_frames ("Textures/items/7-", 1);
    item[7].name = "Armor";
    item[7].description = "1 extra point of armor.";

    item[7].rarity = uncommon;
    item[7].auto_pickup=true;
    item[7].pickup_buffer.loadFromFile("Sounds/misc/armor_pickup.wav");
    item[7].pickup_sound.setBuffer(item[7].pickup_buffer);
    item[7].stock_price=6;

    item[8].animation.create (1, 24, 24, 12, 12, 0.1);
    item[8].animation.fill_frames ("Textures/items/8-", 1);
    item[8].name = "Dynamite";
    item[8].description = "Explosive fun!\nBlow 'em up!";

    item[8].rarity = rare;
    item[8].auto_pickup=true;

    //std::cout << item[8].pickup_sound.getVolume();
    item[8].stock_price=8;

    item[9].animation.create (1, 24, 24, 12, 12, 0.1);
    item[9].animation.fill_frames ("Textures/items/9-", 1);
    item[9].name="Medkit";
    item[9].description="Use when hurt to regain\max health.";
    item[9].rarity = epic;
    item[9].auto_pickup=true;
    item[9].pickup_buffer.loadFromFile("Sounds/misc/dynamite_pickup.wav");
    item[9].pickup_sound.setBuffer(item[9].pickup_buffer);
    item[9].stock_price=12;


    item[10].animation.create (1, 25, 8, 13, 4, 0.1);
    item[10].animation.fill_frames ("Textures/items/10-", 1);
    item[10].name="The Machine Gun";
    item[10].description="A good ol' rifle.";
    item[10].rarity = common;
    item[10].auto_pickup=false;
    item[10].pickup_buffer.loadFromFile("Sounds/misc/weapon_pickup.wav");
    item[10].pickup_sound.setBuffer(item[10].pickup_buffer);
    item[10].stock_price=10;

    item[11].animation.create (1, 31, 7, 16, 4, 0.1);
    item[11].animation.fill_frames ("Textures/items/11-", 1);
    item[11].name="The Wild Gunner";
    item[11].description="There ain't no trouble wanters\nwhen you hold this here gun, pardner!";
    item[11].rarity = rare;
    item[11].auto_pickup=false;
    item[11].pickup_buffer.loadFromFile("Sounds/misc/weapon_pickup.wav");
    item[11].pickup_sound.setBuffer(item[11].pickup_buffer);
    item[11].stock_price=20;

    item[12].animation.create (1, 24, 24, 12, 12, 0.1);
    item[12].animation.fill_frames ("Textures/items/12-", 1);
    item[12].name="Shells";
    item[12].description="+2 bullets per shot.";
    item[12].rarity = common;
    item[12].auto_pickup=false;
    item[12].pickup_buffer.loadFromFile("Sounds/misc/weapon_pickup.wav");
    item[12].pickup_sound.setBuffer(item[12].pickup_buffer);
    item[12].stock_price=5;







    item[8].pickup_buffer.loadFromFile("Sounds/misc/dynamite_pickup.wav");
    item[8].pickup_sound.setBuffer(item[8].pickup_buffer);
    /*std::cout << "test1\n";
    std::cout << item[8].pickup_sound.getVolume();*/




    //drop[6].is = true;player_stock
    //
    //M.setBlock(platform[1][0].pos.x, platform[1][0].pos.y, platform[1][0].pos.x+platform[1][0].width, platform[1][0].pos.y+platform[1][0].height, 1);
    while (window.isOpen())
    {
        //std::cout << "test2\n";
    //std::cout << item[8].pickup_sound.getVolume();

        window.clear();
        if (wasF11Pressed && !Keyboard::isKeyPressed (Keyboard::F11) )
            isF11Released = true;
        else
            isF11Released = false;
        if (Keyboard::isKeyPressed (Keyboard::F11) )
            wasF11Pressed = true;
        else
            wasF11Pressed = false;
        if (isF11Released)
        {
            if (isFullScreen)
            {
                window.create (VideoMode (width, height), "The Guns Dungeons", Style::Default);
                isFullScreen = false;
            }
            else
            {
                window.create (VideoMode (width, height), "The Guns Dungeons", Style::None);
                isFullScreen = true;
            }
            window.setMouseCursorVisible (false);
            window.setSize (Vector2u (VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height) );
            window.setPosition (Vector2i (0, 0) );
        }
        Event event;
        while (window.pollEvent (event) )
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (!wasEscPressed&&window.hasFocus()&&(Keyboard::isKeyPressed(Keyboard::Escape)))
        {
            escPressed=true;
        }
        else
        {
            escPressed=false;
        }
        wasEscPressed=false;
        if (Keyboard::isKeyPressed(Keyboard::Escape)&&window.hasFocus())
            {
                wasEscPressed=true;
            }
        while (clock.getElapsedTime().asMicroseconds() < 16667) {}
        clock.restart();
        if (paused)
        {
            camera.reset (FloatRect (camera_x - player.position.pos.x + width/2, camera_y - player.position.pos.y + height/2, width, height) );
            window.setView (camera);
            pause_text.setPosition(camera_x-player.position.pos.x+width/2+500, camera_y-player.position.pos.y+height/2+300);
            pause_sprite.setPosition(camera_x-player.position.pos.x+width/2, camera_y-player.position.pos.y+height/2);
            window.draw(pause_sprite);
            window.draw(pause_text);
            if (escPressed)
            {
                paused=false;
                escPressed=false;
            }
        }
        else//window.close
        {
            if (!window.hasFocus())
            {
                paused=true;
            }
            if (escPressed)
            {
                paused=true;
                escPressed=false;

            }

        if (toRespawn)
        {
            toRespawn=false;
            player.position.pos.setXY(temp_spawn_x, temp_spawn_y);
            player.position.speed.setXY(0, 0);
        }
        else if (resp)
        {
            music.openFromFile("Sounds/music/Time.wav");
            music.play();
            stage=-1;
            camera_x=100;
            camera_y=100;
            for (int i=0; i<room_count; i++)
            {
                room[i].is=false;
            }
            room[0]=lobby;
            for (int i=0; i<platform_types; i++)
            {
                for (int j=0; j<platform[i][0].quantity; j++)
                {
                    platform[i][j].is=false;
                }//enemy
            }
            for (int i=0; i<types; i++)
            {
                for (int j=0; j<enemy[i][0].quantity; j++)
                {
                    enemy[i][j].is=false;
                    enemy[i][j].phase=0;
                }
            }
            for (int i=0; i<drop_count; i++)
            {
                drop[i].is=false;
            }
            /*drop[0].type = 10;
            drop[0].trade=false;
    drop[0].animation = item[drop[0].type].animation;
    drop[0].glint = rarity[item[drop[0].type].rarity];
    drop[0].position.pos.x = 500;//camera_x
    drop[0].position.pos.y = 300;
    drop[0].position.speed.x = 1;
    drop[0].position.speed.y = 0;
    drop[0].counter = 12;
    drop[0].is = true;*/
    //gravity
    /*enemy[2][0].is=true;
    enemy[2][0].armor=enemy[2][0].max_armor;
    enemy[2][0].position.pos.x=600;
    enemy[2][0].position.pos.y=400;
    enemy[2][0].position.speed.y=10;

    enemy[2][1].is=true;
    enemy[2][1].armor=enemy[2][0].max_armor;
    enemy[2][1].position.pos.x=300;
    enemy[2][1].position.pos.y=400;
    enemy[2][1].position.speed.y=10;*/
            for (int i=0; i<projectiles_count; i++)
            {
                proj[i].is=false;
                proj[i].time=0;
                enemy_proj[i].is=false;
                enemy_proj[i].time=0;


            }
            for (int i=0; i<particle_count; i++)
            {
                particle[i].timer=0;
            }
            M.create(965, 541, "Textures/backgrounds/", "Textures/misc/background0.png");
            M.setBlock (0, 0, 965, 240, 1);
            M.setBlock (0, 240, 36, 540, 1);
            M.setBlock (475, 0, 620, 240, quit);
            M.setBlock(900, 1, 960, 539, start_game);

            platform[0][0].pos.setXY(497, 360);//room
            platform[0][0].pos_start.setXY(497, 250);
            platform[0][0].pos_finish.setXY(497, 500);
            platform[0][0].speed.setXY(0, 1);
            platform[0][0].is = true;
            player=player_stock;
            resp=false;
        }
        spacePressed=false;
        if (Keyboard::isKeyPressed(Keyboard::Space))
        {
            if (!wasSpacePressed)
            {
                spacePressed=true;
            }
            wasSpacePressed=true;
        }
        else
        {
            wasSpacePressed=false;
        }
        dmgToPlayer = 0;//guns_count

        //std::cout << "test2";

        //std::cout << "test3";
//M.create



        //enemy[breath_count


        //std::cout<<"test0";
        //std::cout << "test1";
        //std::cout << round1 (player.position.pos.x - player.width) << " ";
        //std::cout << round1 (player.position.pos.y - player.head_height) << " ";
        player.position.engine (player.head_height, player.height, player.width, M);
        //std::cout << round1 (player.position.pos.x - player.width) << " ";
        //std::cout << round1 (player.position.pos.y - player.head_height) << "\n";
        //std::cout << "test2";
        //std::cout << "test1";
        for (int i = round1 (player.position.pos.x - player.width); i <= round1 (player.position.pos.x + player.width); i++)
        {
            for (int j = round1 (player.position.pos.y - player.head_height); j <= round1 (player.position.pos.y + player.height); j++)
            {
                /*std::cout << round1 (player.position.pos.x - player.width) << " ";
                std::cout << M.width << " ";
                std::cout << room[0].pos.x*1280+640 << " ";
                std::cout << round1 (player.position.pos.y - player.head_height) << "\n";*/
                if (M.M[i][j] == quit)
                {
                    window.close();
                }
                //std::cout << "test2";
            }
        }
        //std::cout << "test1";not_fortune
        //std::cout<<"test0.5";//room
        player.isStanding = false;
        for (int i = round1 (player.position.pos.x - player.width); i <= round1 (player.position.pos.x + player.width); i++)
        {
            if (M.M[i][round1 (player.position.pos.y) + player.height + 1] > 0)
            {
                player.isStanding = true;
                //player.position.speed.y=0;
                break;
            }
        }
        //std::cout << M.width << "\n";
        //std::cout << "test2";
        if (!player.isStanding)
        {
            player.position.speed.y += gravity;
        }


        int type = 0;
        for (int i = 0; i < enemy[type][0].quantity; i++)
        {


            if (enemy[type][i].is)
            {

                enemy[type][i].isStanding = false;
                //std::cout << "test2";
                for (int j = round1(enemy[type][i].position.pos.x) - enemy[type][i].width; j <= enemy[type][i].position.pos.x + enemy[type][i].width; j++)
                {
                    //std::cout << j << " ";
                    if (M.M[j][round1 (enemy[type][i].position.pos.y + enemy[type][i].height) + 1] > 0)
                    {
                        //std::cout << "test3";
                        enemy[type][i].isStanding = true;
                        //std::cout << "test4";
                        break;
                        //std::cout << "test5";drop
                    }
                    //std::cout << "test3";
                }
                enemy[type][i].position.engine (enemy[type][i].head_height, enemy[type][i].height, enemy[type][i].width, M);
                if (!enemy[type][i].isStanding)
        {
            enemy[type][i].position.speed.y += gravity;
        }
                //std::cout << "test3";
            }
        }

        //std::cout << "test3";
        type=1;
        for (int i=0; i<enemy[type][0].quantity; i++)
        {
            if (enemy[type][i].is)
            {
                if (enemy[type][i].health>0&&enemy[type][i].armor>0&&enemy[type][i].room==player.room)
                {
                    enemy[type][i].position.engine(enemy[type][i].head_height, enemy[type][i].height, enemy[type][i].width, M);
                    enemy[type][i].position.speed.y+=gravity;
                }
            }
        }
        int temp_dist=60;
        int temp_i=-1;
        for (int i = 0; i < drop_count; i++)
        {
            if (drop[i].is)
            {
                //std::cout << "test7";visited
                //std::cout << drop[i].position.pos.x << " " << drop[i].position.pos.y << "\n";
                drop[i].position.engine (1, 1, 1, M);

                //std::cout << "test8";engine
                bool temm=true;
                for (int n=round1(drop[i].position.pos.x-1); n<round1(drop[i].position.pos.x+1); n++)
                {


                if (M.M[round1(drop[i].position.pos.x)][round1(drop[i].position.pos.y)+2]==1)
                {

                    if (drop[i].position.speed.x>friction)
                    {
                        drop[i].position.speed.x-=friction;
                    }
                    else if (drop[i].position.speed.x<-friction)
                    {
                        drop[i].position.speed.x+=friction;
                    }
                    else
                    {
                        drop[i].position.speed.x=0;
                    }
                    temm=false;
                    break;

                }
                }
                if (temm)
                {
                    drop[i].position.speed.y+=gravity;
                    if (drop[i].onPlatform)
                {
                    if (drop[i].position.speed.x>friction)
                    {
                        drop[i].position.speed.x-=friction;
                    }
                    else if (drop[i].position.speed.x<-friction)
                    {
                        drop[i].position.speed.x+=friction;
                    }
                    else
                    {
                        drop[i].position.speed.x=0;
                    }
                }
                }

                //frameengine
                drop[i].counter++;
                if (drop[i].counter >= 60)
                {
                    drop[i].counter = 0;
                }
                if (std::sqrt((drop[i].position.pos.x-player.position.pos.x)*(drop[i].position.pos.x-player.position.pos.x)+(drop[i].position.pos.y-player.position.pos.y)*(drop[i].position.pos.y-player.position.pos.y))<temp_dist||temp_i<0)
                {
                    if (room[player.room].rectangle.contains(drop[i].position.pos))
                    {
                        temp_dist=std::sqrt((drop[i].position.pos.x-player.position.pos.x)*(drop[i].position.pos.x-player.position.pos.x)+(drop[i].position.pos.y-player.position.pos.y)*(drop[i].position.pos.y-player.position.pos.y));
                        temp_i=i;
                    }
                }
            }
        }

        type=0;
//platform
        //int b = 0;

        //player.room=-1;
        for (int k=0; k<types; k++)
            {
                for (int l=0; l<enemy[k][0].quantity; l++)
                {
                    enemy[k][l].room=-1;
                }
            }

            //player.room++;drop
            for (int k=0; k<types; k++)
            {
                for (int l=0; l<enemy[k][0].quantity; l++)
                {
                    if (enemy[k][l].is)
                    {
                        for (int i=0; i<room_count; i++)
                        {
                            if (room[i].rectangle.contains(enemy[k][l].position.pos)&&room[i].is)
                            {
                                enemy[k][l].room=i;
                            }
                        }
                    }

                }
            }
            //std::cout<< "test1";
            for (int i=0; i<room_count; i++)
        {
            if (room[i].rectangle.contains (player.position.pos)&&room[i].is)
                {
                    player.room=i;
                }


        }
        //std::cout << "test2";
        if (!room[player.room].visited)
        {
            if (room[player.room].boss)
            {
                music.openFromFile("Sounds/music/Boss.wav");
                music.play();
            }
            for (int l=0; l<room[player.room].drop_count; l++)
                            {
                                for (int m=0; m<drop_count; m++)
                                {

                                    if (!drop[m].is)
                                    {//room_template
                                        //std::cout << "test1";
                                        drop[m].trade=room[player.room].drop[l].trade;
                                        //std::cout << "test2";
                                        drop[m].position.pos.x=room[player.room].drop[l].position.pos.x+round1(room[player.room].pos.x)*1280;
                                        drop[m].position.pos.y=room[player.room].drop[l].position.pos.y+round1(room[player.room].pos.y)*720;
                                        drop[m].position.speed.x=0;
                                        drop[m].position.speed.y=0;
                                        drop[m].type=room[player.room].drop[l].type;
                                        drop[m].animation = item[drop[m].type].animation;
                                        drop[m].glint = rarity[item[drop[m].type].rarity];
                                        drop[m].counter = 0;
                                        drop[m].is=true;
                                        //std::cout << "test3";
                                        break;
                                    }
                                }
                            }

            for (int l=0; l<room[player.room].spawn_count; l++)
                            {

                                int temp_weights=0;
                                //std::cout << "test0";
                                for (int m=0; m<types; m++)
                                {
                                    if (enemy[m][0].weight==room[player.room].spawn[l].weight)
                                    {
                                        temp_weights++;//weight
                                    }
                                }
                                int random_robot=0;
                                if (temp_weights>0)
                                {
                                    random_robot=rand()%temp_weights;
                                }
                                temp_weights=0;

                                //std::cout << "test";proj
                                for (int temp_m=0; temp_m<types; temp_m++)
                                {

                                    if (enemy[temp_m][0].weight==room[player.room].spawn[l].weight)
                                    {
                                        temp_weights++;
                                    }
                                    if (temp_weights>random_robot)
                                    {
                                        for (int m=0; m<enemy[temp_m][0].quantity; m++)
                                        {
                                            if (!enemy[temp_m][m].is)
                                            {
                                                enemy[temp_m][m].position.pos.setXY(room[player.room].spawn[l].position.pos.x+room[player.room].pos.x*1280, room[player.room].spawn[l].position.pos.y+room[player.room].pos.y*720);
                                                enemy[temp_m][m].position.speed=room[player.room].spawn[l].position.speed;
                                                enemy[temp_m][m].phase=0;
                                                enemy[temp_m][m].is=true;
                                                enemy[temp_m][m].armor=enemy[temp_m][m].max_armor;
                                                enemy[temp_m][m].hit_cooldown=0;
                                                enemy[temp_m][m].overheat=0;
                                                enemy[temp_m][m].rotation=3*PI/2;
                                                break;
                                            }
                                        }
                                        break;
                                    }

                                }


                            }
            room[player.room].visited=true;
        }
        camera_x += double (player.position.pos.x - width/2 - camera_x) * 0.075;
        if ( (camera_x + width + 20) - double (room[player.room].rectangle.x_min + room[player.room].rectangle.width) > 0) //right
        {
            camera_x -= ( (camera_x + width + 20) - double (room[player.room].rectangle.x_min + room[player.room].rectangle.width) ) * 0.375; //move left
        }
        if (double (room[player.room].rectangle.x_min) - camera_x > -20) //left
        {
            camera_x += (double (room[player.room].rectangle.x_min) - camera_x + 20) * 0.375; //move right
        }
        camera_y += double (player.position.pos.y - height/2 - camera_y) * 0.075;
        if ( (camera_y + height + 12) - double (room[player.room].rectangle.y_min + room[player.room].rectangle.height) > 0)
        {
            camera_y -= ( (camera_y + height + 12) - double (room[player.room].rectangle.y_min + room[player.room].rectangle.height) ) * 0.375;
        }
        if (double (room[player.room].rectangle.y_min) - camera_y > -12)
        {
            camera_y += (double (room[player.room].rectangle.y_min) - camera_y + 12) * 0.375;
        }
        camera.reset (FloatRect (camera_x - player.position.pos.x + width/2, camera_y - player.position.pos.y + height/2, width, height) );
        window.setView (camera);
        //std::cout<<"test1";
        M.back_sprite.setPosition(camera_x-(camera_x)*640/M.width-player.position.pos.x+width/2, camera_y-(camera_y)*360/M.height-player.position.pos.y+height/2);
        M.back_sprite.setScale(2, 2);
        window.draw(M.back_sprite);
        for (int i = 0; i < M.twidth; i++)
        {
            for (int j = 0; j < M.theight; j++)
            {
                /*if ( (player.position.pos.x / 960) - i <= 2 && (player.position.pos.x / 960) - i >= -2 && (player.position.pos.y / 540) - j <= 2 && (player.position.pos.y / 540) - j >= -2)
                {*/
                    M.sprite[i][j].setPosition (i * 1280 - player.position.pos.x + width/2 + 1, j * 720 - player.position.pos.y + height/2 - 1);
                    window.draw (M.sprite[i][j]);


                //}
            }
        }
        //std::cout<<"test1";

        if (player.isStanding || player.onPlatform)
        {
            if (player.position.speed.x < 0.5 && player.position.speed.x > -0.5)
            {
                breath_count--;
                if (breath_count < 0)
                {
                    breath_count = 60;//enemy[
                }
                player.body.setPos (0.1);
                player.body.sprite.setTexture (player.idle);
            }
            else
            {
                breath_count = 61;
                player.body.step (0.075 * sign1 (player.position.speed.x * player.dir_x) );
            }
        }
        else//drop
        {
            breath_count = 61;
            player.body.setPos (0.1);
            if (player.position.speed.y < -4)
            {
                player.body.sprite.setTexture (player.up);
            }
            else if (player.position.speed.y > 4)
            {
                player.body.sprite.setTexture (player.down);
            }
            else
            {
                player.body.sprite.setTexture (player.idle);
            }
        }
        if (player.position.speed.x > 0.5)
        {
            if ((guns[player.gun_holding].delay <= 0 &&wasButtons<=0)|| updn)
                player.dir_x = 1;
        }
        else if (player.position.speed.x < -0.5)
        {
            if ((guns[player.gun_holding].delay <= 0 &&wasButtons<=0)|| updn)
                player.dir_x = -1;
        }
        if (!wasCtrlPressed&&window.hasFocus()&&(Keyboard::isKeyPressed(Keyboard::LControl)||Keyboard::isKeyPressed(Keyboard::RControl)))
        {
            ctrlPressed=true;
        }
        else
        {
            ctrlPressed=false;
        }
        wasCtrlPressed=false;


        if (window.hasFocus() )
        {
            if (Keyboard::isKeyPressed (Keyboard::A) )
            {
                if (player.isStanding || player.onPlatform)
                    player.position.speed.x -= player.strafe_force;
                else
                    player.position.speed.x -= player.air_strafe_force;
            }
            if (Keyboard::isKeyPressed (Keyboard::D) )
            {
                if (player.isStanding || player.onPlatform)
                    player.position.speed.x += player.strafe_force;
                else
                    player.position.speed.x += player.air_strafe_force;
            }
            if ( (player.isStanding || player.onPlatform) && Keyboard::isKeyPressed (Keyboard::W) )
            {
                //std::cout << "test";drop
                if (player.position.speed.y > 0 && !player.onPlatform)
                {
                    player.position.speed.y = -player.jump_force;
                }
                else
                {
                    player.position.speed.y -= player.jump_force;
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::LControl)||Keyboard::isKeyPressed(Keyboard::RControl))
            {
                wasCtrlPressed=true;
            }

        }
        if (ctrlPressed)
        {



        if (player.gun_holding==player.gun)
        {
            if (player.dynamite>0)
            {
                player.gun_holding=1;
            }

        }
        else
        {
            player.gun_holding=player.gun;
        }

        }

//explosion_knockback
        if (player.position.speed.x > player.max_speed)
        {
            player.position.speed.x = player.max_speed;
        }//drop
        if (player.position.speed.x < -player.max_speed)
        {
            player.position.speed.x = -player.max_speed;
        }
        if (player.isStanding || player.onPlatform)
        {
            if (player.position.speed.x < friction && player.position.speed.x > -friction)
            {
                player.position.speed.x = 0;
            }
            else
            {
                player.position.speed.x -= sign1 (player.position.speed.x) * friction;
            }
        }
        bool sh = false;//enemy[
        int buttons=0;

        if (window.hasFocus() && guns[player.gun_holding].delay <= 0)
        {
            if (Keyboard::isKeyPressed (Keyboard::Up))
            {
                //player.dir_y = -1;
                buttons++;
            }
            else if (Keyboard::isKeyPressed (Keyboard::Down))
            {
                //player.dir_y = 1;
                buttons++;
            }
            else
            {
                //player.dir_y = 0;
            }

            if (Keyboard::isKeyPressed (Keyboard::Left))
            {
                //player.dir_x = -1;
                buttons++;

            }
            else if (Keyboard::isKeyPressed (Keyboard::Right) )
            {
                //player.dir_x = 1;//setPR
                buttons++;
            }
        }
        if (buttons>wasButtons)
        {
            wasButtons=buttons;
        }
        if (guns[player.gun_holding].type!=1)
        {
            wasButtons=0;
        }
        if (wasButtons>buttons&&guns[player.gun_holding].type==1)
            {
                guns[player.gun_holding].sound.play();

                //std::cout << "1";

                if (player.gun_holding==1)
                {
                    int k = -1;

                    for (int i = 0; i < enemy[1][0].quantity; i++)
                    {
                        if (! (enemy[1][i].is) )
                        {
                            k = i;
                            break;//guns[player.gun_holding].animation
                        }
                    }
                    guns[player.gun_holding].delay = guns[player.gun_holding].max_delay;
                    wasButtons=0;
                    if (k >= 0)
                    {
                        player.dynamite--;
                        enemy[1][k].is = true;
                        enemy[1][k].position=player.position;
                        enemy[1][k].position.speed.y+=20*sin(rotation (player.dir_x * bool (!updn), player.dir_y))-player.position.speed.y*0.4;
                        enemy[1][k].position.speed.x+=20*cos(rotation (player.dir_x * bool (!updn), player.dir_y))-player.position.speed.x*0.4;
                        enemy[1][k].health=enemy[1][k].max_health;
                        enemy[1][k].armor=1;
                        //enemy[1][k].acceleration = guns[player.gun_holding].proj_acceleration;

                        //enemy[1][k].blast = guns[player.gun_holding].blast;
                        enemy[1][k].damage = guns[player.gun_holding].damage;
                    }
                }
                else
                {
                    guns[player.gun_holding].sound.play();
                    guns[player.gun_holding].delay = guns[player.gun_holding].max_delay;
                    wasButtons=0;
                    //shoot projectiles
                    double temp_mult=1;
                    for (int i=0; i<player.shells; i++)
                    {
                        temp_mult*=player.shells_multiplier;
                    }
                    int temp_dam=round1(double(guns[player.gun_holding].damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1))+bool((double(guns[player.gun_holding].damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1)-int(double(guns[player.gun_holding].damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/(guns[player.gun_holding].pellets*2+player.shells*2+1)))*1000.0*(2-player.not_fortune)>rand()%1000);
                    int temp_min_dam=round1(double(guns[player.gun_holding].min_damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1))+bool((double(guns[player.gun_holding].min_damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1)-int(double(guns[player.gun_holding].min_damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/(guns[player.gun_holding].pellets*2+player.shells*2+1)))*1000.0*(2-player.not_fortune)>rand()%1000);
                    if (temp_min_dam>temp_dam)
                    {
                        temp_min_dam=temp_dam;
                    }
//damage
                    int temp_knockback=round1(double(guns[player.gun_holding].knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1))+bool((double(guns[player.gun_holding].knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1)-int(double(guns[player.gun_holding].knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/(guns[player.gun_holding].pellets*2+player.shells*2+1)))*1000.0*(2-player.not_fortune)>rand()%1000);

                    int temp_exp_knockback=round1(double(guns[player.gun_holding].explosion_knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1))+bool((double(guns[player.gun_holding].explosion_knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1)-int(double(guns[player.gun_holding].explosion_knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/(guns[player.gun_holding].pellets*2+player.shells*2+1)))*1000.0*(2-player.not_fortune)>rand()%1000);
                    int k = -1;
                    for (int i = 0; i < projectiles_count; i++)
                    {
                        if (! (proj[i].is) )
                        {//onPlatform
                            k = i;
                            break;
                        }
                    }
                    if (k >= 0)
                    {
                        proj[k].is = true;
                        proj[k].acceleration = guns[player.gun_holding].proj_acceleration;
                        proj[k].animation = guns[player.gun_holding].projectile;
                        proj[k].blast = guns[player.gun_holding].blast;
                        proj[k].damage = temp_dam;
                        proj[k].min_damage = temp_min_dam;
                        proj[k].distance_left = guns[player.gun_holding].max_distance;
                        proj[k].explosion.setBuffer (guns[player.gun_holding].exp_buffer);
                        proj[k].gun = player.gun_holding;
                        proj[k].knockback = temp_knockback;
                        proj[k].explosion_knockback = temp_exp_knockback;
                        proj[k].multiplier = 1;
                        proj[k].radius = guns[player.gun_holding].radius;
                        proj[k].rotation = rotation (player.dir_x * bool (!updn), player.dir_y);
                        proj[k].speed = guns[player.gun_holding].proj_speed;
                        proj[k].x = player.position.pos.x;
                        proj[k].y = player.position.pos.y;
                        proj[k].time = guns[player.gun_holding].max_projectile_time;
                        proj[k].blast.setPos (0.1);
                        proj[k].animation.setPos (0.1);
                        proj[k].grav=guns[player.gun_holding].proj_grav;
                        proj[k].type=guns[player.gun_holding].proj_type;
                    }

                    for (int l=1; l<=guns[player.gun_holding].pellets+player.shells; l++)
                    {
                        k = -1;
                    for (int i = 0; i < projectiles_count; i++)
                    {
                        if (! (proj[i].is) )
                        {
                            k = i;
                            break;
                        }
                    }
                    if (k >= 0)
                    {
                        temp_dam=round1(double(guns[player.gun_holding].damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1))+bool((double(guns[player.gun_holding].damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1)-int(double(guns[player.gun_holding].damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/(guns[player.gun_holding].pellets*2+player.shells*2+1)))*1000.0*(2-player.not_fortune)>rand()%1000);
                    temp_min_dam=round1(double(guns[player.gun_holding].min_damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1))+bool((double(guns[player.gun_holding].min_damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1)-int(double(guns[player.gun_holding].min_damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/(guns[player.gun_holding].pellets*2+player.shells*2+1)))*1000.0*(2-player.not_fortune)>rand()%1000);
                    if (temp_min_dam>temp_dam)
                    {
                        temp_min_dam=temp_dam;
                    }
//damage
                    temp_knockback=round1(double(guns[player.gun_holding].knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1))+bool((double(guns[player.gun_holding].knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1)-int(double(guns[player.gun_holding].knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/(guns[player.gun_holding].pellets*2+player.shells*2+1)))*1000.0*(2-player.not_fortune)>rand()%1000);

                    temp_exp_knockback=round1(double(guns[player.gun_holding].explosion_knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1))+bool((double(guns[player.gun_holding].explosion_knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1)-int(double(guns[player.gun_holding].explosion_knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/(guns[player.gun_holding].pellets*2+player.shells*2+1)))*1000.0*(2-player.not_fortune)>rand()%1000);
                        proj[k].is = true;
                        proj[k].acceleration = guns[player.gun_holding].proj_acceleration;
                        proj[k].animation = guns[player.gun_holding].projectile;
                        proj[k].blast = guns[player.gun_holding].blast;
                        proj[k].damage = temp_dam;
                        proj[k].min_damage = temp_min_dam;
                        proj[k].distance_left = guns[player.gun_holding].max_distance;
                        proj[k].explosion.setBuffer (guns[player.gun_holding].exp_buffer);
                        proj[k].gun = player.gun_holding;
                        proj[k].knockback = temp_knockback;
                        proj[k].explosion_knockback = temp_exp_knockback;
                        proj[k].multiplier = 1;
                        proj[k].radius = guns[player.gun_holding].radius;
                        proj[k].rotation = rotation (player.dir_x * bool (!updn), player.dir_y)+double(l)*guns[player.gun_holding].pellet_spread;
                        proj[k].speed = guns[player.gun_holding].proj_speed;
                        proj[k].x = player.position.pos.x;
                        proj[k].y = player.position.pos.y;
                        proj[k].time = guns[player.gun_holding].max_projectile_time;
                        proj[k].blast.setPos (0.1);
                        proj[k].animation.setPos (0.1);
                        proj[k].grav=guns[player.gun_holding].proj_grav;
                        proj[k].type=guns[player.gun_holding].proj_type;
                    }
                    k = -1;
                    for (int i = 0; i < projectiles_count; i++)
                    {
                        if (! (proj[i].is) )
                        {
                            k = i;
                            break;
                        }
                    }
                    if (k >= 0)
                    {
                        temp_dam=round1(double(guns[player.gun_holding].damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1))+bool((double(guns[player.gun_holding].damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1)-int(double(guns[player.gun_holding].damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/(guns[player.gun_holding].pellets*2+player.shells*2+1)))*1000.0*(2-player.not_fortune)>rand()%1000);
                    temp_min_dam=round1(double(guns[player.gun_holding].min_damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1))+bool((double(guns[player.gun_holding].min_damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1)-int(double(guns[player.gun_holding].min_damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/(guns[player.gun_holding].pellets*2+player.shells*2+1)))*1000.0*(2-player.not_fortune)>rand()%1000);
                    if (temp_min_dam>temp_dam)
                    {
                        temp_min_dam=temp_dam;
                    }
//damage
                    temp_knockback=round1(double(guns[player.gun_holding].knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1))+bool((double(guns[player.gun_holding].knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1)-int(double(guns[player.gun_holding].knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/(guns[player.gun_holding].pellets*2+player.shells*2+1)))*1000.0*(2-player.not_fortune)>rand()%1000);

                    temp_exp_knockback=round1(double(guns[player.gun_holding].explosion_knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1))+bool((double(guns[player.gun_holding].explosion_knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1)-int(double(guns[player.gun_holding].explosion_knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/(guns[player.gun_holding].pellets*2+player.shells*2+1)))*1000.0*(2-player.not_fortune)>rand()%1000);
                        proj[k].is = true;
                        proj[k].acceleration = guns[player.gun_holding].proj_acceleration;
                        proj[k].animation = guns[player.gun_holding].projectile;
                        proj[k].blast = guns[player.gun_holding].blast;
                        proj[k].damage = temp_dam;
                        proj[k].min_damage = temp_min_dam;
                        proj[k].distance_left = guns[player.gun_holding].max_distance;
                        proj[k].explosion.setBuffer (guns[player.gun_holding].exp_buffer);
                        proj[k].gun = player.gun_holding;
                        proj[k].knockback = temp_knockback;
                        proj[k].explosion_knockback = temp_exp_knockback;
                        proj[k].multiplier = 1;
                        proj[k].radius = guns[player.gun_holding].radius;
                        proj[k].rotation = rotation (player.dir_x * bool (!updn), player.dir_y)-double(l)*guns[player.gun_holding].pellet_spread;
                        proj[k].speed = guns[player.gun_holding].proj_speed;
                        proj[k].x = player.position.pos.x;
                        proj[k].y = player.position.pos.y;
                        proj[k].time = guns[player.gun_holding].max_projectile_time;
                        proj[k].blast.setPos (0.1);
                        proj[k].animation.setPos (0.1);
                        proj[k].grav=guns[player.gun_holding].proj_grav;
                        proj[k].type=guns[player.gun_holding].proj_type;
                    }
                    }

                }
            }//setPR
        if (guns[player.gun_holding].delay <= 0)
        {
            updn = false;
        }
        if (window.hasFocus() && guns[player.gun_holding].delay <= 0)
        {
            if (Keyboard::isKeyPressed (Keyboard::Up))
            {
                sh = true;
                player.dir_y = -1;

            }
            else if (Keyboard::isKeyPressed (Keyboard::Down))
            {
                sh = true;
                player.dir_y = 1;

            }
            else//window.drawposition
            {
                player.dir_y = 0;
            }
            if (Keyboard::isKeyPressed (Keyboard::Left))
            {
                sh = true;
                player.dir_x = -1;

            }
            else if (Keyboard::isKeyPressed (Keyboard::Right) )
            {
                sh = true;
                player.dir_x = 1;

            }
            else
            {
                updn = true;
            }
        }
        if (guns[player.gun_holding].type==1&&!Keyboard::isKeyPressed (Keyboard::Right)&&!Keyboard::isKeyPressed (Keyboard::Left)&&(Keyboard::isKeyPressed (Keyboard::Down)||Keyboard::isKeyPressed (Keyboard::Up))&&wasButtons>0)
        {
            updn=true;
        }

//drop
            if (sh)
            {
                breath_count = 61;



                //std::cout << player.gun_holding;

                //shootplayer.onPlatform
                if (guns[player.gun_holding].type==0)
                {
                    breath_count = 61;
                    guns[player.gun_holding].sound.play();
                    guns[player.gun_holding].delay = guns[player.gun_holding].max_delay;
                    //shoot projectiles
                    double temp_mult=1;
                    for (int i=0; i<player.shells; i++)
                    {
                        temp_mult*=player.shells_multiplier;
                    }


                    int temp_dam=round1(double(guns[player.gun_holding].damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1))+bool((double(guns[player.gun_holding].damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1)-int(double(guns[player.gun_holding].damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/(guns[player.gun_holding].pellets*2+player.shells*2+1)))*1000.0*(2-player.not_fortune)>rand()%1000);
                    int temp_min_dam=round1(double(guns[player.gun_holding].min_damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1))+bool((double(guns[player.gun_holding].min_damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1)-int(double(guns[player.gun_holding].min_damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/(guns[player.gun_holding].pellets*2+player.shells*2+1)))*1000.0*(2-player.not_fortune)>rand()%1000);
                    if (temp_min_dam>temp_dam)
                    {
                        temp_min_dam=temp_dam;
                    }
//damage
                    int temp_knockback=round1(double(guns[player.gun_holding].knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1))+bool((double(guns[player.gun_holding].knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1)-int(double(guns[player.gun_holding].knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/(guns[player.gun_holding].pellets*2+player.shells*2+1)))*1000.0*(2-player.not_fortune)>rand()%1000);

                    int temp_exp_knockback=round1(double(guns[player.gun_holding].explosion_knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1))+bool((double(guns[player.gun_holding].explosion_knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1)-int(double(guns[player.gun_holding].explosion_knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/(guns[player.gun_holding].pellets*2+player.shells*2+1)))*1000.0*(2-player.not_fortune)>rand()%1000);


                    int k = -1;
                    for (int i = 0; i < projectiles_count; i++)
                    {
                        if (! (proj[i].is) )
                        {
                            k = i;
                            break;
                        }
                    }
                    if (k >= 0)
                    {
                        proj[k].is = true;
                        proj[k].acceleration = guns[player.gun_holding].proj_acceleration;
                        proj[k].animation = guns[player.gun_holding].projectile;
                        proj[k].blast = guns[player.gun_holding].blast;
                        proj[k].damage = temp_dam;
                        proj[k].min_damage = temp_min_dam;
                        proj[k].distance_left = guns[player.gun_holding].max_distance;
                        proj[k].explosion.setBuffer (guns[player.gun_holding].exp_buffer);
                        proj[k].gun = player.gun_holding;
                        proj[k].knockback = temp_knockback;
                        proj[k].explosion_knockback = temp_exp_knockback;
                        proj[k].multiplier = 1;
                        proj[k].radius = guns[player.gun_holding].radius;
                        proj[k].rotation = rotation (player.dir_x * bool (!updn), player.dir_y);
                        proj[k].speed = guns[player.gun_holding].proj_speed;
                        proj[k].x = player.position.pos.x;
                        proj[k].y = player.position.pos.y;
                        proj[k].time = guns[player.gun_holding].max_projectile_time;
                        proj[k].blast.setPos (0.1);
                        proj[k].animation.setPos (0.1);
                        proj[k].grav=guns[player.gun_holding].proj_grav;
                        proj[k].type=guns[player.gun_holding].proj_type;
                    }

                    for (int l=1; l<=guns[player.gun_holding].pellets+player.shells; l++)
                    {
                        k = -1;
                    for (int i = 0; i < projectiles_count; i++)
                    {
                        if (! (proj[i].is) )
                        {//enemy[2]
                            k = i;
                            break;
                        }
                    }
                    if (k >= 0)
                    {
                                            temp_dam=round1(double(guns[player.gun_holding].damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1))+bool((double(guns[player.gun_holding].damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1)-int(double(guns[player.gun_holding].damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/(guns[player.gun_holding].pellets*2+player.shells*2+1)))*1000.0*(2-player.not_fortune)>rand()%1000);
                    temp_min_dam=round1(double(guns[player.gun_holding].min_damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1))+bool((double(guns[player.gun_holding].min_damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1)-int(double(guns[player.gun_holding].min_damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/(guns[player.gun_holding].pellets*2+player.shells*2+1)))*1000.0*(2-player.not_fortune)>rand()%1000);
                    if (temp_min_dam>temp_dam)
                    {
                        temp_min_dam=temp_dam;
                    }
//damage
                    temp_knockback=round1(double(guns[player.gun_holding].knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1))+bool((double(guns[player.gun_holding].knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1)-int(double(guns[player.gun_holding].knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/(guns[player.gun_holding].pellets*2+player.shells*2+1)))*1000.0*(2-player.not_fortune)>rand()%1000);

                    temp_exp_knockback=round1(double(guns[player.gun_holding].explosion_knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1))+bool((double(guns[player.gun_holding].explosion_knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1)-int(double(guns[player.gun_holding].explosion_knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/(guns[player.gun_holding].pellets*2+player.shells*2+1)))*1000.0*(2-player.not_fortune)>rand()%1000);

                        proj[k].is = true;
                        proj[k].acceleration = guns[player.gun_holding].proj_acceleration;
                        proj[k].animation = guns[player.gun_holding].projectile;
                        proj[k].blast = guns[player.gun_holding].blast;
                        proj[k].damage = temp_dam;
                        proj[k].min_damage = temp_min_dam;
                        proj[k].distance_left = guns[player.gun_holding].max_distance;
                        proj[k].explosion.setBuffer (guns[player.gun_holding].exp_buffer);
                        proj[k].gun = player.gun_holding;
                        proj[k].knockback = temp_knockback;
                        proj[k].explosion_knockback = temp_exp_knockback;
                        proj[k].multiplier = 1;
                        proj[k].radius = guns[player.gun_holding].radius;
                        proj[k].rotation = rotation (player.dir_x * bool (!updn), player.dir_y)+double(l)*guns[player.gun_holding].pellet_spread;
                        proj[k].speed = guns[player.gun_holding].proj_speed;
                        proj[k].x = player.position.pos.x;
                        proj[k].y = player.position.pos.y;
                        proj[k].time = guns[player.gun_holding].max_projectile_time;
                        proj[k].blast.setPos (0.1);
                        proj[k].animation.setPos (0.1);
                        proj[k].grav=guns[player.gun_holding].proj_grav;
                        proj[k].type=guns[player.gun_holding].proj_type;
                    }
                    k = -1;
                    for (int i = 0; i < projectiles_count; i++)
                    {
                        if (! (proj[i].is) )
                        {
                            k = i;
                            break;
                        }
                    }
                    if (k >= 0)
                    {
                                            temp_dam=round1(double(guns[player.gun_holding].damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1))+bool((double(guns[player.gun_holding].damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1)-int(double(guns[player.gun_holding].damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/(guns[player.gun_holding].pellets*2+player.shells*2+1)))*1000.0*(2-player.not_fortune)>rand()%1000);
                    temp_min_dam=round1(double(guns[player.gun_holding].min_damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1))+bool((double(guns[player.gun_holding].min_damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1)-int(double(guns[player.gun_holding].min_damage*(guns[player.gun_holding].pellets*2+1))*temp_mult/(guns[player.gun_holding].pellets*2+player.shells*2+1)))*1000.0*(2-player.not_fortune)>rand()%1000);
                    if (temp_min_dam>temp_dam)
                    {
                        temp_min_dam=temp_dam;
                    }
//damage
                    temp_knockback=round1(double(guns[player.gun_holding].knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1))+bool((double(guns[player.gun_holding].knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1)-int(double(guns[player.gun_holding].knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/(guns[player.gun_holding].pellets*2+player.shells*2+1)))*1000.0*(2-player.not_fortune)>rand()%1000);

                    temp_exp_knockback=round1(double(guns[player.gun_holding].explosion_knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1))+bool((double(guns[player.gun_holding].explosion_knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/double(guns[player.gun_holding].pellets*2+player.shells*2+1)-int(double(guns[player.gun_holding].explosion_knockback*(guns[player.gun_holding].pellets*2+1))*temp_mult/(guns[player.gun_holding].pellets*2+player.shells*2+1)))*1000.0*(2-player.not_fortune)>rand()%1000);

                        proj[k].is = true;
                        proj[k].acceleration = guns[player.gun_holding].proj_acceleration;
                        proj[k].animation = guns[player.gun_holding].projectile;
                        proj[k].blast = guns[player.gun_holding].blast;
                        proj[k].damage = temp_dam;
                        proj[k].min_damage = temp_min_dam;
                        proj[k].distance_left = guns[player.gun_holding].max_distance;
                        proj[k].explosion.setBuffer (guns[player.gun_holding].exp_buffer);
                        proj[k].gun = player.gun_holding;
                        proj[k].knockback = temp_knockback;
                        proj[k].explosion_knockback = temp_exp_knockback;
                        proj[k].multiplier = 1;
                        proj[k].radius = guns[player.gun_holding].radius;
                        proj[k].rotation = rotation (player.dir_x * bool (!updn), player.dir_y)-double(l)*guns[player.gun_holding].pellet_spread;
                        proj[k].speed = guns[player.gun_holding].proj_speed;
                        proj[k].x = player.position.pos.x;
                        proj[k].y = player.position.pos.y;
                        proj[k].time = guns[player.gun_holding].max_projectile_time;
                        proj[k].blast.setPos (0.1);
                        proj[k].animation.setPos (0.1);
                        proj[k].grav=guns[player.gun_holding].proj_grav;
                        proj[k].type=guns[player.gun_holding].proj_type;
                    }
                    }
                }




                //
            }
            else if (guns[player.gun_holding].delay<=0)
            {
                player.dir_y = 0;
            }
            if (guns[player.gun_holding].type==1&&guns[player.gun_holding].delay>0)
            {
                breath_count = 61;
            }


/*std::cout << "test1: ";
std::cout << player.position.pos.x << "\n";*/

        for (int k = 0; k < projectiles_count; k++)
        {

            //player.armorhealth
            if (!proj[k].is && proj[k].time)
            {
                //std::cout << 1;
                proj[k].time--;
                proj[k].blast.setPR (1, round1 (width/2 - player.position.pos.x + proj[k].x), round1 (height/2 - player.position.pos.y + proj[k].y), 0);
                //std::cout << "test1";
                proj[k].blast.setFrame (proj[k].time);
                //std::cout << proj[k].blast.frame_pos[proj[k].time] << "\n";radius
                //std::cout << "test2";enemy
                window.draw (proj[k].blast.sprite);
            }
            if (proj[k].is)
            {
                int dist = 9999;
                Bullet bullet;
                Bullet subbullet;
                bullet.distance = 0;
                bool b = true;
                for (int i = 0; i < types; i++)
                {
                    for (int j = 0; j < enemy[i][0].quantity; j++)
                    {
//multiplayer_map
                        if (enemy[i][j].armor > 0)
                        {
                            b = false;
                            subbullet = shoot (enemy[i][j].position.pos.x, enemy[i][j].position.pos.y, enemy[i][j].head_height, enemy[i][j].height, enemy[i][j].width, proj[k].rotation, proj[k].x, proj[k].y, proj[k].damage, proj[k].speed, M);
                            if (subbullet.distance < dist)
                            {
                                bullet = subbullet;
                                dist = subbullet.distance;
                            }
                        }
                    }
                }//platform
                if (b)
                    bullet = shoot (0, 0, 0, 0, 0, proj[k].rotation, proj[k].x, proj[k].y, proj[k].damage, proj[k].speed, M);
                dist = bullet.distance;
                //mp[setPR
                if (dist < proj[k].speed || proj[k].distance_left <= 0)
                {
                    //proj[k].explosion.play();
                    proj[k].x += (bullet.distance - 1) * cos (proj[k].rotation);
                    proj[k].y += (bullet.distance - 1) * sin (proj[k].rotation);
                    Bullet dmg = damage (proj[k].multiplier, player.position.pos.x, player.position.pos.y, player.width, player.position.pos.y - player.head_height, player.position.pos.y + player.height, proj[k].x, proj[k].y, proj[k].radius, proj[k].damage - proj[k].min_damage, M.M);
                    dmg.damage += proj[k].min_damage * dmg.hit;
                    player.position.speed.x += cos (rotation (dmg.final_x, dmg.final_y) ) * guns[proj[k].gun].explosion_knockback * double (dmg.damage) / proj[k].damage;
                    player.position.speed.y += sin (rotation (dmg.final_x, dmg.final_y) ) * guns[proj[k].gun].explosion_knockback * double (dmg.damage) / proj[k].damage;//guns
                    dmgToPlayer += round1 (double (dmg.damage) * guns[proj[k].gun].self_damage_multiplier);
                    for (int i = 0; i < types; i++)
                    {
                        for (int j = 0; j < enemy[i][0].quantity; j++)
                        {
                            if (enemy[i][j].armor > 0)
                            {
                                dmg = damage (proj[k].multiplier, enemy[i][j].position.pos.x, enemy[i][j].position.pos.y, enemy[i][j].width, enemy[i][j].position.pos.y - enemy[i][j].head_height, enemy[i][j].position.pos.y + enemy[i][j].height, proj[k].x, proj[k].y, proj[k].radius, proj[k].damage - proj[k].min_damage, M.M);
                                dmg.damage += proj[k].min_damage * dmg.hit;
                                //dmgEnemy+=dmg;
                                if (round1(dmg.damage>0))
                                {
                                    enemy[i][j].hit_sound.play();
                                }

                                enemy[i][j].armor -= round1 (dmg.damage);
                                enemy[i][j].position.speed.x += cos (proj[k].rotation) * proj[k].knockback * double (dmg.damage) / proj[k].damage;
                                enemy[i][j].position.speed.y += sin (proj[k].rotation) * proj[k].knockback * double (dmg.damage) / proj[k].damage;
                                enemy[i][j].position.speed.x += cos (rotation (dmg.final_x, dmg.final_y) ) * proj[k].explosion_knockback * double (dmg.damage) / proj[k].damage;
                                enemy[i][j].position.speed.y += sin (rotation (dmg.final_x, dmg.final_y) ) * proj[k].explosion_knockback * double (dmg.damage) / proj[k].damage;
                            }//setPos
                        }
                    }
                    proj[k].damage = 0;
                    proj[k].is = false;
                    proj[k].explosion.setBuffer (guns[proj[k].gun].exp_buffer);
                    proj[k].explosion.play();
                    //projectile[k].explosion.play();
                    proj[k].blast.setPos (0.1);
                    proj[k].blast.setPR (1, proj[k].x, proj[k].y, 0);
                    //window.draw(projectile[k].blast);
                }
                else
                {
                    temp_cos=cos (proj[k].rotation)*proj[k].speed;
                    temp_sin=sin (proj[k].rotation)*proj[k].speed;
                    temp_sin+=proj[k].grav;
                    proj[k].speed=round1(std::sqrt(temp_cos*temp_cos+temp_sin*temp_sin));
                    proj[k].rotation=rotation(temp_cos, temp_sin);

                    proj[k].x += cos (proj[k].rotation) * (proj[k].speed - 1);
                    proj[k].y += sin (proj[k].rotation) * (proj[k].speed - 1);
                    proj[k].distance_left -= (proj[k].speed - 1);
                }
                //Mouse
                proj[k].animation.setPR (sign1 (cos (proj[k].rotation) ), width/2 + proj[k].x - player.position.pos.x, height/2 + proj[k].y - player.position.pos.y, rt (cos (proj[k].rotation), sin (proj[k].rotation) ) );
                proj[k].animation.step1();
                window.draw (proj[k].animation.sprite);
                proj[k].speed += proj[k].acceleration;
            }
        }
        /*std::cout << "test2: ";
std::cout << player.position.pos.x << "\n";*/
        for (int k = 0; k < projectiles_count; k++)
        {
            //player.armorhealthpos
            if (!enemy_proj[k].is && enemy_proj[k].time)
            {
                //std::cout << 1;
                enemy_proj[k].time--;
                enemy_proj[k].blast.setPR (1, round1 (width/2 - player.position.pos.x + enemy_proj[k].x), round1 (height/2 - player.position.pos.y + enemy_proj[k].y), 0);
                enemy_proj[k].blast.setFrame (enemy_proj[k].time);
                window.draw (enemy_proj[k].blast.sprite);
            }
            if (enemy_proj[k].is)
            {
                //std::cout << "1";
                int dist = 9999;
                Bullet bullet;
                Bullet subbullet;
                bullet.distance = 0;
                bool b = true;
//multiplayer_map
                if (player.health > 0)
                {
                    b = false;
                    subbullet = shoot (player.position.pos.x, player.position.pos.y, player.head_height, player.height, player.width, enemy_proj[k].rotation, enemy_proj[k].x, enemy_proj[k].y, enemy_proj[k].damage - enemy_proj[k].min_damage, enemy_proj[k].speed, M);
                    if (subbullet.distance < dist)
                    {
                        bullet = subbullet;
                        dist = subbullet.distance;
                    }
                }
                if (b)
                    bullet = shoot (0, 0, 0, 0, 0, enemy_proj[k].rotation, enemy_proj[k].x, enemy_proj[k].y, enemy_proj[k].damage, enemy_proj[k].speed, M);
                dist = bullet.distance;
                //mp[setPR
                if (dist < enemy_proj[k].speed || enemy_proj[k].distance_left <= 0)
                {
                    enemy_proj[k].x += (bullet.distance - 1) * cos (enemy_proj[k].rotation);
                    enemy_proj[k].y += (bullet.distance - 1) * sin (enemy_proj[k].rotation);
                    Bullet dmg = damage (enemy_proj[k].multiplier, player.position.pos.x, player.position.pos.y, player.width, player.position.pos.y - player.head_height, player.position.pos.y + player.height, enemy_proj[k].x, enemy_proj[k].y, enemy_proj[k].radius, enemy_proj[k].damage - enemy_proj[k].min_damage, M.M);
                    dmg.damage += enemy_proj[k].min_damage * dmg.hit;
                    //player.position.speed.x+=cos(rotation(dmg.final_x, dmg.final_y))*guns[enemy_proj[k].gun].explosion_knockback*double(dmg.damage)/enemy_proj[k].damage;
                    //player.position.speed.y+=sin(rotation(dmg.final_x, dmg.final_y))*guns[enemy_proj[k].gun].explosion_knockback*double(dmg.damage)/enemy_proj[k].damage;
                    if (player.health > 0)
                    {
                        //dmg=damage(enemy_proj[k].multiplier, player.position.pos.x, player.position.pos.y, player.width, player.position.pos.y-player.head_height, player.position.pos.y+player.height, enemy_proj[k].x, enemy_proj[k].y, enemy_proj[k].radius, enemy_proj[k].damage, M.M);
                        //dmgEnemy+=dmg;
                        //dmgToPlayer=round1(dmg.damage);
                        dmgToPlayer += round1 (dmg.damage);
                        player.position.speed.x += cos (enemy_proj[k].rotation) * enemy_proj[k].knockback * double (dmg.damage) / enemy_proj[k].damage;
                        player.position.speed.y += sin (enemy_proj[k].rotation) * enemy_proj[k].knockback * double (dmg.damage) / enemy_proj[k].damage;
                        player.position.speed.x += cos (rotation (dmg.final_x, dmg.final_y) ) * enemy_proj[k].explosion_knockback * double (dmg.damage) / enemy_proj[k].damage;
                        player.position.speed.y += sin (rotation (dmg.final_x, dmg.final_y) ) * enemy_proj[k].explosion_knockback * double (dmg.damage) / enemy_proj[k].damage;
                    }
                    enemy_proj[k].damage = 0;
                    enemy_proj[k].is = false;
                    enemy_proj[k].explosion.setBuffer (guns[enemy_proj[k].gun].exp_buffer);
                    enemy_proj[k].explosion.play();
                    //projectile[k].explosion.play();
                    enemy_proj[k].blast.setPos (0.1);
                    enemy_proj[k].blast.setPR (1, enemy_proj[k].x, enemy_proj[k].y, 0);
                    //window.draw(projectile[k].blast);enemy
                }
                else
                {

                    temp_cos=cos (enemy_proj[k].rotation)*enemy_proj[k].speed;
                    temp_sin=sin (enemy_proj[k].rotation)*enemy_proj[k].speed;
                    temp_sin+=enemy_proj[k].grav;
                    enemy_proj[k].speed=round1(std::sqrt(temp_cos*temp_cos+temp_sin*temp_sin));
                    enemy_proj[k].rotation=rotation(temp_cos, temp_sin);

                    enemy_proj[k].x += cos (enemy_proj[k].rotation) * (enemy_proj[k].speed - 1);
                    enemy_proj[k].y += sin (enemy_proj[k].rotation) * (enemy_proj[k].speed - 1);
                    enemy_proj[k].distance_left -= (enemy_proj[k].speed - 1);
                }
                //Mouse
                enemy_proj[k].animation.setPR (sign1 (cos (enemy_proj[k].rotation) ), width/2 + enemy_proj[k].x - player.position.pos.x, height/2 + enemy_proj[k].y - player.position.pos.y, rt (cos (enemy_proj[k].rotation), sin (enemy_proj[k].rotation) ) );
                enemy_proj[k].animation.step1();
                window.draw (enemy_proj[k].animation.sprite);
                enemy_proj[k].speed += enemy_proj[k].acceleration;
                //std::cout << "2";
            }
        }
//window
        for (int j=0; j<types; j++)
        {
            for (int k=0; k<enemy[j][0].quantity; k++)
            {
                enemy[j][k].onPlatform=false;
            }
        }
        for (int k=0; k<drop_count; k++)
            {
                drop[k].onPlatform=false;
            }

        player.onPlatform = false;
        //std::cout << platform[0][0].speed.y;
        //std::cout << platform[0][0].canMove(0, 1, M.M, player, enemy) << " " << platform[0][0].canMove(0, -1, M.M, player, enemy) << "\n";
        //std::cout << "test5";
        for (int i = 0; i < platform[0][0].quantity; i++)
        {
            if (platform[0][i].is)
            {
                for (int j=0; j<types; j++)
                {
                    for (int k=0; k<enemy[j][0].quantity; k++)
                    {
                        if (round1 (enemy[j][k].position.pos.y) + enemy[j][k].height + 1 == platform[0][i].pos.y && enemy[j][k].position.pos.x + enemy[j][k].width+1 >= platform[0][i].pos.x && enemy[j][k].position.pos.x - enemy[j][k].width-1 <= platform[0][i].pos.x + platform[0][i].width)
                        {
                            if (enemy[j][k].position.speed.y >= platform[0][i].speed.y-1)
                            {
                                enemy[j][k].onPlatform = true;
                            }
                        }
                    }
                }

                if (round1 (player.position.pos.y) + player.height + 1 == platform[0][i].pos.y && player.position.pos.x + player.width+1 >= platform[0][i].pos.x && player.position.pos.x - player.width-1 <= platform[0][i].pos.x + platform[0][i].width)
                {
                    if (player.position.speed.y >= platform[0][i].speed.y-1)
                    {
                        player.onPlatform = true;
                    }
                }
                for (int k=0; k<drop_count; k++)
                    {
                        if (round1 (drop[k].position.pos.y) + 2 == platform[0][i].pos.y && drop[k].position.pos.x + 2 >= platform[0][i].pos.x && drop[k].position.pos.x - 2 <= platform[0][i].pos.x + platform[0][i].width)
                        {
                            if (drop[k].position.speed.y >= platform[0][i].speed.y-1)
                            {
                                drop[k].onPlatform = true;
                            }
                        }
                    }
                if (platform[0][i].speed.y > 0)
                {
                    platform[0][i].down.step1();
                    platform[0][i].down.setPR (1, platform[0][i].pos.x - player.position.pos.x + width/2, platform[0][i].pos.y - player.position.pos.y + height/2, 0);
                    window.draw (platform[0][i].down.sprite);
                    M.setBlock (platform[0][i].pos.x, platform[0][i].pos.y, platform[0][i].pos.x + platform[0][i].width, platform[0][i].pos.y + platform[0][i].height, 0);
                    platform[0][i].move1 (0, 1, M.M, player, enemy, drop);
                    M.setBlock (platform[0][i].pos.x, platform[0][i].pos.y, platform[0][i].pos.x + platform[0][i].width, platform[0][i].pos.y + platform[0][i].height, platform[0][i].block);
                }
                else
                {
                    platform[0][i].up.step1();
                    platform[0][i].up.setPR (1, platform[0][i].pos.x - player.position.pos.x + width/2, platform[0][i].pos.y - player.position.pos.y + height/2, 0);
                    window.draw (platform[0][i].up.sprite);
                    M.setBlock (platform[0][i].pos.x, platform[0][i].pos.y, platform[0][i].pos.x + platform[0][i].width, platform[0][i].pos.y + platform[0][i].height, 0);
                    platform[0][i].move1 (0, -1, M.M, player, enemy, drop);
                    M.setBlock (platform[0][i].pos.x, platform[0][i].pos.y, platform[0][i].pos.x + platform[0][i].width, platform[0][i].pos.y + platform[0][i].height, platform[0][i].block);
                }
                for (int j=0; j<types; j++)
                {
                    for (int k=0; k<enemy[j][0].quantity; k++)
                    {
                        if (round1 (enemy[j][k].position.pos.y) + enemy[j][k].height + 1 == platform[0][i].pos.y && enemy[j][k].position.pos.x + enemy[j][k].width+1 >= platform[0][i].pos.x && enemy[j][k].position.pos.x - enemy[j][k].width-1 <= platform[0][i].pos.x + platform[0][i].width)
                        {
                            if (enemy[j][k].position.speed.y >= platform[0][i].speed.y-1)
                            {
                                enemy[j][k].onPlatform = true;
                            }
                        }
                    }
                }
                if (round1 (player.position.pos.y) + player.height + 1 == platform[0][i].pos.y && player.position.pos.x + player.width+1 >= platform[0][i].pos.x && player.position.pos.x - player.width-1 <= platform[0][i].pos.x + platform[0][i].width)
                {
                    if (player.position.speed.y >= platform[0][i].speed.y-1)
                    {
                        player.onPlatform = true;
                    }//temp_dist
                }
                for (int k=0; k<drop_count; k++)
                    {
                        if (round1 (drop[k].position.pos.y) + 2 == platform[0][i].pos.y && drop[k].position.pos.x + 2 >= platform[0][i].pos.x && drop[k].position.pos.x - 2 <= platform[0][i].pos.x + platform[0][i].width)
                        {
                            if (drop[k].position.speed.y >= platform[0][i].speed.y-1)
                            {
                                drop[k].onPlatform = true;
                            }
                        }//engine
                    }
                if (platform[0][i].pos.y < platform[0][i].pos_start.y)
                {
                    platform[0][i].down.setPos (platform[0][i].up.pos);
                    platform[0][i].speed.y = 1;
                }
                else if (platform[0][i].pos.y > platform[0][i].pos_finish.y)
                {
                    platform[0][i].up.setPos (platform[0][i].down.pos);
                    platform[0][i].speed.y = -1;
                }
                if (round1 (player.position.pos.y) + player.height + 1 == platform[0][i].pos.y && player.position.pos.x + player.width >= platform[0][i].pos.x && player.position.pos.x - player.width <= platform[0][i].pos.x + platform[0][i].width)
                {
                    //player.onPlatform=true;
                    if (player.position.speed.y > platform[0][i].speed.y)
                    {
                        player.position.speed.y = platform[0][i].speed.y;
                    }
                }
                /*if (round1(player.position.pos.y)-player.head_height-1==platform[0][i].pos.y+platform[0][i].height&&player.position.speed.y<platform[0][i].speed.y&&player.position.pos.x+player.width>=platform[0][i].pos.x&&player.position.pos.x-player.width<=platform[0][i].pos.x+platform[0][i].width)
                {
                    player.position.speed.y=platform[0][i].speed.y;
                }*/
                for (int j = 0; j < types; j++)
                {
                    for (int k = 0; k < enemy[j][0].quantity; k++)
                    {
                        if (round1 (enemy[j][k].position.pos.y) + enemy[j][k].height + 1 == platform[0][i].pos.y && enemy[j][k].position.pos.x + enemy[j][k].width >= platform[0][i].pos.x && enemy[j][k].position.pos.x - enemy[j][k].width <= platform[0][i].pos.x + platform[0][i].width)
                {
                    if (enemy[j][k].position.speed.y > platform[0][i].speed.y)
                    {
                        enemy[j][k].position.speed.y = platform[0][i].speed.y;
                    }
                }

                    }
                }//enemy[i][j].armor
                for (int j = 0; j<drop_count; j++)
                {
                    if (drop[j].is)
                    {
                        if (round1 (drop[j].position.pos.y) + 2 == platform[0][i].pos.y && drop[j].position.pos.x + 1 >= platform[0][i].pos.x && drop[j].position.pos.x - 1 <= platform[0][i].pos.x + platform[0][i].width)
                {
                    if (drop[j].position.speed.y > platform[0][i].speed.y)
                    {
                        drop[j].position.speed.y = platform[0][i].speed.y;
                    }
                }
                    }

                }
                //platform[0][i].animation.setPR(1, platform[0][i].pos.x-player.position.pos.x+480, platform[0][i].pos.y-player.position.pos.y+270, 0);
                //window.draw(platform[0][i].animation.sprite);
            }
        }
        //std::cout << "test6";
        //std::cout << "test2";
        //std::cout << player.onPlatform;
        for (int i=0; i<platform[1][0].quantity; i++)
        {
            if (platform[1][i].is)
            {
                if (platform[1][i].phase==0)
                {
                    if (M.M[round1(platform[1][i].pos.x)+1][round1(platform[1][i].pos.y)+1]==0)
                    {
                        if (platform[1][i].canAppear(platform[1][i].pos.x, platform[1][i].pos.y, player, enemy, drop))
                        {
                            M.setBlock(platform[1][i].pos.x, platform[1][i].pos.y, platform[1][i].pos.x+platform[1][i].width, platform[1][i].pos.y+platform[1][i].height, 1);
                        }
                    }
                    platform[1][i].up.setPos(0.1);
                    platform[1][i].up.sprite.setPosition(platform[1][i].pos.x-player.position.pos.x+width/2, platform[1][i].pos.y-player.position.pos.y+height/2);
                    window.draw(platform[1][i].up.sprite);
                }
                else
                {
                    M.setBlock(platform[1][i].pos.x, platform[1][i].pos.y, platform[1][i].pos.x+platform[1][i].width, platform[1][i].pos.y+platform[1][i].height, 0);
                    int tem_pos=platform[1][i].up.pos;
                    platform[1][i].up.step1();
                    platform[1][i].up.sprite.setPosition(platform[1][i].pos.x-player.position.pos.x+width/2, platform[1][i].pos.y-player.position.pos.y+height/2);
                    window.draw(platform[1][i].up.sprite);
                    if (tem_pos>platform[1][i].up.pos)
                    {
                        platform[1][i].is=false;
                    }
                }
            }
        }
        for (int i=0; i<platform[2][0].quantity; i++)
        {

            if (platform[2][i].is)
            {

                int temp_room=-1;
                for (int j=0; j<room_count; j++)
                {
                    if ((room[j].rectangle.contains1(platform[2][i].pos.x+95, platform[2][i].pos.y+25)||room[j].rectangle.contains1(platform[2][i].pos.x+5, platform[2][i].pos.y+5))&&room[j].is)
                    {
                        temp_room=j;
                        break;
                    }
                }
                //std::cout << "test2";
                if (temp_room==player.room)
                {
                    bool t_bool=true;
                    //std::cout << "test6.5";

                    for (int k=0; k<types&&t_bool==true; k++)
                    {
                        if (k!=1)
                        {
                            for (int l=0; l<enemy[k][0].quantity&&t_bool==true; l++)
                            {
                                if (enemy[k][l].room==player.room&&enemy[k][l].is&&enemy[k][l].armor>0)
                                {
                                    t_bool=false;
                                    //l=enemy[k][0].quantity;
                                    //k=types-1;
                                }


                            }
                        }
                    }
                    //std::cout << "test1.5";gunsbreath_count
                    if (!t_bool)
                    {
                        //std::cout << "test1.5";projectile
                        if (platform[2][i].canAppear(platform[2][i].pos.x, platform[2][i].pos.y, player, enemy, drop))
                        {
                            if (M.M[round1(platform[2][i].pos.x+1)][round1(platform[2][i].pos.y+1)]!=1)
                            {
                                M.setBlock(platform[2][i].pos.x, platform[2][i].pos.y, platform[2][i].pos.x+platform[2][i].width, platform[2][i].pos.y+platform[2][i].height, 1);
                            }
                            platform[2][i].up.setPos(1.1);
                        }
                    }
                    else
                    {
                        M.setBlock(platform[2][i].pos.x, platform[2][i].pos.y, platform[2][i].pos.x+platform[2][i].width, platform[2][i].pos.y+platform[2][i].height, 0);
                        platform[2][i].up.setPos(0.1);
                    }
                }
                else
                {
                    //std::cout << "test0.5";
                    M.setBlock(platform[2][i].pos.x, platform[2][i].pos.y, platform[2][i].pos.x+platform[2][i].width, platform[2][i].pos.y+platform[2][i].height, 0);
                    //std::cout << "test2.5";
                    platform[2][i].up.setPos(0.1);
                }
                //std::cout << "test3";
                platform[2][i].up.sprite.setPosition(platform[2][i].pos.x-player.position.pos.x+width/2, platform[2][i].pos.y-player.position.pos.y+height/2);
                window.draw(platform[2][i].up.sprite);
            }
        }
        //std::cout << "test3";
        for (int i=0; i<platform[3][0].quantity; i++)
        {
            if (platform[3][i].is)
            {
                int temp_room=-1;
                for (int j=0; j<room_count; j++)
                {
                    if ((room[j].rectangle.contains1(platform[3][i].pos.x+25, platform[3][i].pos.y+95)||room[j].rectangle.contains1(platform[3][i].pos.x+5, platform[3][i].pos.y+5))&&room[j].is)
                    {
                        temp_room=j;
                        break;
                    }
                }
                //std::cout << temp_room << " a" << player.room << "";
                if (temp_room==player.room)
                {
                    bool t_bool=true;

                    for (int k=0; k<types&&t_bool==true; k++)
                    {
                        if (k!=1)
                        {
                            for (int l=0; l<enemy[k][0].quantity&&t_bool==true; l++)
                            {
                                //std::cout << enemy[k][l].room << " ";
                                if (enemy[k][l].room==player.room&&enemy[k][l].is&&enemy[k][l].armor>0)
                                {
                                    t_bool=false;
                                    //std::cout << enemy[k][l].position.pos.x << " " << enemy[k][l].position.pos.y << "\n";
                                    //l=enemy[k][0].quantity;
                                    //k=types;
                                }


                            }
                        }
                    }
                    if (!t_bool)
                    {
                        if (platform[3][i].canAppear(platform[3][i].pos.x, platform[3][i].pos.y, player, enemy, drop))
                        {
                            if (M.M[round1(platform[3][i].pos.x+1)][round1(platform[3][i].pos.y+1)]!=1)
                            {
                                M.setBlock(platform[3][i].pos.x, platform[3][i].pos.y, platform[3][i].pos.x+platform[3][i].width, platform[3][i].pos.y+platform[3][i].height, 1);
                            }
                            platform[3][i].up.setPos(1.1);
                        }
                    }
                    else
                    {
                        M.setBlock(platform[3][i].pos.x, platform[3][i].pos.y, platform[3][i].pos.x+platform[3][i].width, platform[3][i].pos.y+platform[3][i].height, 0);
                        platform[3][i].up.setPos(0.1);
                    }
                }
                else
                {
                    M.setBlock(platform[3][i].pos.x, platform[3][i].pos.y, platform[3][i].pos.x+platform[3][i].width, platform[3][i].pos.y+platform[3][i].height, 0);
                    platform[3][i].up.setPos(0.1);
                }
                platform[3][i].up.sprite.setPosition(platform[3][i].pos.x-player.position.pos.x+width/2, platform[3][i].pos.y-player.position.pos.y+height/2);
                window.draw(platform[3][i].up.sprite);
            }
        }
        //std::cout << "test2";
        for (int i = 0; i < guns_count; i++)
        {
            if (guns[i].delay > 0)
            {
                guns[i].delay--;
                if (guns[i].delay<=0&&i==player.gun_holding)
                {
                    player.gun_holding=player.gun;
                }

            }
        }



            player.head.setPR (player.dir_x, width/2, height/2+bool(breath_count < 45 && breath_count > 15), 0);


        if (player.dir_y == 0)
        {
            window.draw (player.head.sprite);//enemy[type
        }
        else if (player.dir_y > 0)
        {
            player.head_down.setPR (player.dir_x, width/2, height/2+bool(breath_count < 45 && breath_count > 15), 0);
            window.draw (player.head_down.sprite);
        }
        else
        {
            player.head_up.setPR (player.dir_x, width/2, height/2+bool(breath_count < 45 && breath_count > 15), 0);
            window.draw (player.head_up.sprite);
        }
        player.body.setPR (player.dir_x, width/2, height/2, 0);
        window.draw (player.body.sprite);

        type=1;
        for (int i=0; i<enemy[type][0].quantity; i++)
        {
            if (enemy[type][i].is)
            {

                if (enemy[type][i].health>0&&enemy[type][i].armor>0)
                {
                    enemy[type][i].was=true;

                    enemy[type][i].body.step1();
                    bool tem_b=false;
                    for (int j=round1(enemy[type][i].position.pos.x-enemy[type][i].width); j<=round1(enemy[type][i].position.pos.x+enemy[type][i].width); j++)
                    {
                        if (((M.M[j][round1(enemy[type][i].position.pos.y+enemy[type][i].height+1)]>0&&M.M[j][round1(enemy[type][i].position.pos.y+enemy[type][i].height+1)]!=fall_off&&enemy[type][i].position.speed.y>0)||enemy[type][i].onPlatform)||(M.M[j][round1(enemy[type][i].position.pos.y+enemy[type][i].height+1)]>0&&M.M[j][round1(enemy[type][i].position.pos.y-enemy[type][i].head_height-1)]!=jump_on&&enemy[type][i].position.speed.y<=0))
                        {
                            if (enemy[type][i].body.pos>=3&&enemy[type][i].body.pos<7)
                            {
                                enemy[type][i].body.setPos(5.1);
                            }
                            else
                            {
                                enemy[type][i].body.setPos(1.1);
                            }
                            tem_b=true;
                            break;//draw
                        }
                    }
                    if (!tem_b)
                    {
                        for (int j=round1(enemy[type][i].position.pos.y-enemy[type][i].head_height); j<=round1(enemy[type][i].position.pos.y+enemy[type][i].height); j++)
                        {
                            if (M.M[round1(enemy[type][i].position.pos.x+enemy[type][i].width+1)][j]>0||M.M[round1(enemy[type][i].position.pos.x-enemy[type][i].width-1)][j]>0)
                    {
                        if (enemy[type][i].body.pos>=1&&enemy[type][i].body.pos<5)
                        {
                            enemy[type][i].body.setPos(3.1);
                        }
                        else
                        {
                            enemy[type][i].body.setPos(7.1);
                        }
                        break;

                    }

                        }
                    }



                    enemy[type][i].body.setPR(1, enemy[type][i].position.pos.x-player.position.pos.x+width/2, enemy[type][i].position.pos.y-player.position.pos.y+height/2, 0);
                    window.draw(enemy[type][i].body.sprite);
                    enemy[type][i].health--;
                    if (enemy[type][i].health%3==0)
                    {
                        int px=0;
                        int py=0;
                        if (enemy[type][i].body.pos>=0&&enemy[type][i].body.pos<3)
                        {
                            px=1;
                        }
                        else if (enemy[type][i].body.pos>=4&&enemy[type][i].body.pos<7)
                        {
                            px=-1;
                        }
                        else
                        {
                            px=0;
                        }

                            if (enemy[type][i].body.pos>=2&&enemy[type][i].body.pos<5)
                        {
                            py=1;
                        }
                        else if (enemy[type][i].body.pos>=6||enemy[type][i].body.pos<1)
                        {
                            py=-1;
                        }
                        else
                        {
                            py=0;
                        }

                        for (int j=0; j<particle_count; j++)
                        {
                            if (particle[j].timer<=0)
                            {
                                particle[j].animation=spark;
                                particle[j].pos.x=enemy[type][i].position.pos.x+(8*enemy[type][i].health/enemy[type][i].max_health+9)*cos(rotation(px, py))+rand()%5-2;
                                particle[j].pos.y=enemy[type][i].position.pos.y+(8*enemy[type][i].health/enemy[type][i].max_health+9)*sin(rotation(px, py))+rand()%5-2;
                                particle[j].timer=45;
                                particle[j].type=1;
                                break;
                            }
                        }
                    }

                }
                else
                {

                    int temp_pos=enemy[type][i].blast.pos;
                    enemy[type][i].blast.step1();

                    if (temp_pos>=enemy[type][i].blast.pos)
                    {
                        enemy[type][i].is=false;
                    }
                    if (enemy[type][i].was)
                    {//type
                        enemy[type][i].exp_sound.play();
                        //std::cout << enemy[type][i].exp_sound.getVolume();
                        Bullet dmg = damage (guns[1].splash_multiplier, player.position.pos.x, player.position.pos.y, player.width, player.position.pos.y - player.head_height, player.position.pos.y + player.height, enemy[type][i].position.pos.x, enemy[type][i].position.pos.y, guns[1].radius, guns[1].damage - guns[1].min_damage, M.M);
                    dmg.damage += guns[1].min_damage * dmg.hit;
                    player.position.speed.x += cos (rotation (dmg.final_x, dmg.final_y) ) * guns[1].explosion_knockback * double (dmg.damage) / guns[1].damage;
                    player.position.speed.y += sin (rotation (dmg.final_x, dmg.final_y) ) * guns[1].explosion_knockback * double (dmg.damage) / guns[1].damage;
                    dmgToPlayer += round1 (double (dmg.damage) * guns[1].self_damage_multiplier);
                    for (int l = 0; l < types; l++)
                    {
                        for (int j = 0; j < enemy[l][0].quantity; j++)
                        {
                            if (enemy[l][j].armor > 0)
                            {
                                dmg = damage (guns[1].splash_multiplier, enemy[l][j].position.pos.x, enemy[l][j].position.pos.y, enemy[l][j].width, enemy[l][j].position.pos.y - enemy[l][j].head_height, enemy[l][j].position.pos.y + enemy[l][j].height, enemy[type][i].position.pos.x, enemy[type][i].position.pos.y, guns[1].radius, guns[1].damage - guns[1].min_damage, M.M);
                                dmg.damage += guns[1].min_damage * dmg.hit;
                                //dmgEnemy+=dmg;
                                if (round1(dmg.damage>0))
                                {
                                    enemy[l][j].hit_sound.play();
                                }

                                enemy[l][j].armor -= round1 (dmg.damage);
                                enemy[l][j].position.speed.x += cos (rotation (dmg.final_x, dmg.final_y) ) * guns[1].explosion_knockback * double (dmg.damage) / guns[1].damage;
                                enemy[l][j].position.speed.y += sin (rotation (dmg.final_x, dmg.final_y) ) * guns[1].explosion_knockback * double (dmg.damage) / guns[1].damage;
                            }//setPoscout
                        }
                    }
                    for (int k=0; k<platform[1][0].quantity; k++)
                    {
                        if (platform[1][k].is&&platform[1][k].phase==0)
                        {
                            if (sqrt((platform[1][k].pos.x+platform[1][k].width/2-enemy[type][i].position.pos.x)*(platform[1][k].pos.x+platform[1][k].width/2-enemy[type][i].position.pos.x)+(platform[1][k].pos.y+platform[1][k].height/2-enemy[type][i].position.pos.y)*(platform[1][k].pos.y+platform[1][k].height/2-enemy[type][i].position.pos.y))<40+guns[1].radius)
                            {
                                platform[1][k].phase=1;
                            }
                        }
                    }


                    //projectile[k].explosion.play();
                    }
                    enemy[type][i].was=false;
                }

            }
        }
        //std::cout<<"test1";
        //window.draw(guns[player.gun_holding].animation.sprite);
        if (player.dir_y == 0)
        {
            guns[player.gun_holding].animation.setFrame (guns[player.gun_holding].delay);
            if (guns[player.gun_holding].type==1&&sh)
            {
                guns[player.gun_holding].animation.setFrame(guns[player.gun_holding].max_delay);
            }
            guns[player.gun_holding].animation.setPR (player.dir_x, width/2, height/2+5-bool(buttons>0) + bool (breath_count < 30 && breath_count > 0) + bool ( ( (player.body.pos >= 1 && player.body.pos < 1.8) || (player.body.pos >= 3 && player.body.pos < 3.8) ) && guns[player.gun_holding].delay <= 0), 0);
            window.draw (guns[player.gun_holding].animation.sprite);
        }
        else if (updn)
        {
            guns[player.gun_holding].animation.setFrame (guns[player.gun_holding].delay);
            if (guns[player.gun_holding].type==1&&sh)
            {
                guns[player.gun_holding].animation.setFrame(guns[player.gun_holding].max_delay);
            }
            guns[player.gun_holding].animation.setPR (player.dir_x, width/2, height/2+5-bool(buttons>0) + bool (breath_count < 30 && breath_count > 0) + bool ( ( (player.body.pos >= 1 && player.body.pos < 1.8) || (player.body.pos >= 3 && player.body.pos < 3.8) ) && guns[player.gun_holding].delay <= 0), player.dir_x * asin (player.dir_y) );
            window.draw (guns[player.gun_holding].animation.sprite);
        }
        else
        {
            guns[player.gun_holding].upper_animation.setFrame (guns[player.gun_holding].delay);
            if (guns[player.gun_holding].type==1&&sh)
            {
                guns[player.gun_holding].upper_animation.setFrame(guns[player.gun_holding].max_delay);
            }
            guns[player.gun_holding].upper_animation.setPR (player.dir_x, width/2, height/2+5-bool(buttons>0) + bool (breath_count < 30 && breath_count > 0) + bool ( ( (player.body.pos >= 1 && player.body.pos < 1.8) || (player.body.pos >= 3 && player.body.pos < 3.8) ) && guns[player.gun_holding].delay <= 0), player.dir_x * asin (bool (player.dir_y > 0) ) );
            window.draw (guns[player.gun_holding].upper_animation.sprite);
        }
        //std::cout << "test3";
        type = 0;
        for (int i = 0; i < enemy[type][0].quantity; i++)
        {
            if (enemy[type][i].is&&enemy[type][i].room==player.room)
            {
                if (enemy[type][i].hit_cooldown<=0)
                {
                    if (player.position.pos.x>=enemy[type][i].position.pos.x-20&&player.position.pos.x<=enemy[type][i].position.pos.x+20&&player.position.pos.y>=enemy[type][i].position.pos.y-20&&player.position.pos.y<=enemy[type][i].position.pos.y+40&&(enemy[type][i].phase==2||enemy[type][i].phase==3))
                    {
                        double temp_rot=rotation(player.position.pos.x-enemy[type][i].position.pos.x, player.position.pos.y-enemy[type][i].position.pos.y);
                        player.position.speed.x+=cos(temp_rot)*12;
                        player.position.speed.y+=sin(temp_rot)*12;
                        dmgToPlayer+=1;
                        enemy[type][i].hit_cooldown=enemy[type][i].max_hit_cooldown;
                    }
                }
                else
                {
                    enemy[type][i].hit_cooldown--;
                }
                //std::cout << "test1";//temp_dist
                if (enemy[type][i].armor<=0)
                {
                    //std::cout << "test1";gravity
                    for (int j=0; j<enemy[type][i].drops; j++)
                    {
                        int random_number=0;
                        if (enemy[type][i].drop_max[j]<=enemy[type][i].drop_min[j])
                        {
                            random_number=enemy[type][i].drop_min[j];
                        }
                        else
                        {
                            random_number=enemy[type][i].drop_min[j]+rand()%(round1(enemy[type][i].drop_max[j]-enemy[type][i].drop_min[j]))*(2.0-player.not_fortune);
                        }
                        random_number=random_number/1000;
                        //std::cout << "test7";
                        for (int k=0; k<random_number; k++)
                        {
                            //std::cout << k << "\n";
                            for (int l=0; l<drop_count; l++)
                            {
                                if (!drop[l].is)
                                {
                                    drop[l].trade=false;
                                    drop[l].position=enemy[type][i].position;
                                    drop[l].position.speed.x=rand()%9-4;
                                    drop[l].position.speed.y=-3;
                                    drop[l].type=enemy[type][i].drop_type[j];
                                    drop[l].animation = item[drop[l].type].animation;
    drop[l].glint = rarity[item[drop[l].type].rarity];
    /*drop[2].position.pos.x = 450;//camera_x
    drop[2].position.pos.y = 400;
    drop[2].position.speed.x = 0;
    drop[2].position.speed.y = 0;*/
    drop[l].counter = 0;

                                    drop[l].is=true;
                                    break;
                                }
                            }
                        }
                    }
                    //std::cout << "test2";
                    enemy[type][i].is=false;
                    //std::cout << "test3";
                }
                //std::cout << "test2";


                if (enemy[type][i].phase == 0) //offhealth
                {
                    if (enemy[type][i].room==player.room)
                    {
                        if (player.position.pos.x - enemy[type][i].position.pos.x < enemy[type][i].sight_x && player.position.pos.x - enemy[type][i].position.pos.x > -enemy[type][i].sight_x && player.position.pos.y - enemy[type][i].position.pos.y < enemy[type][i].sight_y && player.position.pos.y - enemy[type][i].position.pos.y > -enemy[type][i].sight_y)
                        {
                            enemy[type][i].phase = 1;
                            enemy[type][i].timer = enemy[type][i].max_startup;
                            enemy[type][i].dir_x = sign1 (player.position.pos.x - enemy[type][i].position.pos.x);
                        }
                        if (enemy[type][i].armor < enemy[type][i].max_armor)
                    {
                        enemy[type][i].phase = 1;
                        enemy[type][i].timer = enemy[type][i].max_startup;
                        enemy[type][i].dir_x = sign1 (player.position.pos.x - enemy[type][i].position.pos.x);
                    }
                    }


                    enemy[type][i].startup.setPR (enemy[type][i].dir_x, enemy[type][i].position.pos.x - player.position.pos.x + width/2, enemy[type][i].position.pos.y - player.position.pos.y + height/2, 0);
                    enemy[type][i].startup.setPos (0.1);
                    window.draw (enemy[type][i].startup.sprite);
                    enemy[type][i].tracks.setPR (enemy[type][i].dir_x, enemy[type][i].position.pos.x - player.position.pos.x + width/2, enemy[type][i].position.pos.y - player.position.pos.y + height/2, 0);
                    enemy[type][i].tracks.setPos (0.1);
                    window.draw (enemy[type][i].tracks.sprite);
                }
                else if (enemy[type][i].phase == 1)
                {

                    enemy[type][i].timer--;
                    enemy[type][i].startup.setFrame (enemy[type][i].timer);
                    if (enemy[type][i].timer <= 0)
                    {
                        enemy[type][i].dir_x = sign1 (player.position.pos.x - enemy[type][i].position.pos.x);
                        enemy[type][i].phase = 3;
                        enemy[type][i].timer = 5;
                        enemy[type][i].shoot_timer=0;
                    }
                    enemy[type][i].startup.setPR (enemy[type][i].dir_x, enemy[type][i].position.pos.x - player.position.pos.x + width/2, enemy[type][i].position.pos.y - player.position.pos.y + height/2, 0);
                    window.draw (enemy[type][i].startup.sprite);
                    enemy[type][i].tracks.setPR (enemy[type][i].dir_x, enemy[type][i].position.pos.x - player.position.pos.x + width/2, enemy[type][i].position.pos.y - player.position.pos.y + height/2, 0);
                    enemy[type][i].tracks.setPos (0.1);
                    window.draw (enemy[type][i].tracks.sprite);
                }
                else if (enemy[type][i].phase == 2)
                {
                    if (player.position.pos.x - enemy[type][i].position.pos.x < enemy[type][i].sight_x && player.position.pos.x - enemy[type][i].position.pos.x > -enemy[type][i].sight_x && player.position.pos.y - enemy[type][i].position.pos.y < enemy[type][i].sight_y && player.position.pos.y - enemy[type][i].position.pos.y > -enemy[type][i].sight_y)
                    {


                    enemy[type][i].timer--;
                    if (enemy[type][i].timer <= 0)
                    {
                        enemy[type][i].phase = 3;
                        enemy[type][i].timer = enemy[type][i].max_aim;
                    }
                    if (enemy[type][i].isStanding||enemy[type][i].onPlatform)
                    {
                        enemy[type][i].dir_x = sign1 (player.position.pos.x - enemy[type][i].position.pos.x);
                        if (sign (enemy[type][i].position.speed.x) == enemy[type][i].dir_x || enemy[type][i].position.speed.x * enemy[type][i].position.speed.x < 0.05)
                        {
                            if ( (enemy[type][i].position.speed.x + (enemy[type][i].strafe_force) *enemy[type][i].dir_x) *sign (enemy[type][i].position.speed.x - (enemy[type][i].strafe_force) *enemy[type][i].dir_x) < enemy[type][i].max_speed)
                            {
                                enemy[type][i].position.speed.x += (enemy[type][i].strafe_force + friction) * enemy[type][i].dir_x;
                            }
                            else if (enemy[type][i].position.speed.x * sign (enemy[type][i].position.speed.x) < enemy[type][i].max_speed)
                            {
                                enemy[type][i].position.speed.x = sign (enemy[type][i].position.speed.x) * enemy[type][i].max_speed;
                            }
                            enemy[type][i].body.step1();
                            enemy[type][i].tracks.step1();
                        }
                    }
                    else
                    {
                        enemy[type][i].body.setPos (0.1);
                        enemy[type][i].tracks.sprite.setTexture (enemy[type][i].down);
                    }
                    if (enemy[type][i].shoot_timer>0)
                    {
                        enemy[type][i].shoot_timer--;
                        enemy[type][i].head.setPos (enemy[type][i].body.pos);
                        enemy[type][i].body.sprite = enemy[type][i].head.sprite;
                    }

                    }
                    else
                    {
                        enemy[type][i].timer = enemy[type][i].max_run;
                        enemy[type][i].tracks.setPos (0.1);
                        enemy[type][i].body.setPos (0.1);
                    }
                    enemy[type][i].body.setPR (enemy[type][i].dir_x, enemy[type][i].position.pos.x - player.position.pos.x + width/2, enemy[type][i].position.pos.y - player.position.pos.y + height/2, 0);
                    window.draw (enemy[type][i].body.sprite);
                    enemy[type][i].tracks.setPR (enemy[type][i].dir_x, enemy[type][i].position.pos.x - player.position.pos.x + width/2, enemy[type][i].position.pos.y - player.position.pos.y + height/2, 0);
                    window.draw (enemy[type][i].tracks.sprite);
                }
                else if (enemy[type][i].phase == 3)
                {
                    if (player.position.pos.x - enemy[type][i].position.pos.x < enemy[type][i].sight_x && player.position.pos.x - enemy[type][i].position.pos.x > -enemy[type][i].sight_x && player.position.pos.y - enemy[type][i].position.pos.y < enemy[type][i].sight_y && player.position.pos.y - enemy[type][i].position.pos.y > -enemy[type][i].sight_y)
                    {
                    enemy[type][i].timer--;
                    if (enemy[type][i].timer <= 0)
                    {
                        //shoot
                        enemy[type][i].shoot_sound.play();
                        enemy[type][i].position.speed.x -= enemy[type][i].recoil * enemy[type][i].dir_x;
                        int k = -1;
                        for (int j = 0; j < projectiles_count; j++)
                        {
                            if (! (enemy_proj[j].is) )
                            {
                                k = j;
                                break;
                            }
                        }
                        if (k >= 0)
                        {


                            enemy[type][i].shoot_timer=12;

                            enemy_proj[k].is = true;
                            enemy_proj[k].acceleration = 0;
                            enemy_proj[k].animation = enemy[type][i].proj;
                            enemy_proj[k].blast = enemy[type][i].blast;
                            enemy_proj[k].damage = enemy[type][i].damage;
                            enemy_proj[k].min_damage = enemy[type][i].damage;
                            enemy_proj[k].distance_left = 1920;
                            enemy_proj[k].explosion.setBuffer (enemy[type][i].exp_buffer);
                            enemy_proj[k].gun = 0;
                            enemy_proj[k].knockback = 2;
                            enemy_proj[k].explosion_knockback = 1;
                            enemy_proj[k].multiplier = 1;
                            enemy_proj[k].radius = 2;
                            enemy_proj[k].rotation = rotation (enemy[type][i].dir_x, enemy[type][i].dir_y);
                            enemy_proj[k].speed = 10;
                            enemy_proj[k].x = enemy[type][i].position.pos.x;
                            enemy_proj[k].y = enemy[type][i].position.pos.y;
                            enemy_proj[k].time = guns[enemy[type][i].gun_holding].max_projectile_time;
                            enemy_proj[k].blast.setPos (0.1);
                            enemy_proj[k].grav=0;
                            enemy_proj[k].type=0;
                        }
                        //
                        enemy[type][i].phase = 2;
                        enemy[type][i].timer = enemy[type][i].max_run;
                    }
                    if (enemy[type][i].isStanding||enemy[type][i].onPlatform)
                    {
                        if (sign (enemy[type][i].position.speed.x) == -enemy[type][i].dir_x || enemy[type][i].position.speed.x * enemy[type][i].position.speed.x < 0.05)
                        {
                            if ( (enemy[type][i].position.speed.x - (enemy[type][i].strafe_force) *enemy[type][i].dir_x) *sign (enemy[type][i].position.speed.x - (enemy[type][i].strafe_force) *enemy[type][i].dir_x) < enemy[type][i].max_speed)
                            {
                                enemy[type][i].position.speed.x -= (enemy[type][i].strafe_force + friction) * enemy[type][i].dir_x;
                            }
                            else if (enemy[type][i].position.speed.x * sign (enemy[type][i].position.speed.x) < enemy[type][i].max_speed)
                            {
                                enemy[type][i].position.speed.x = sign (enemy[type][i].position.speed.x) * enemy[type][i].max_speed;
                            }
                            enemy[type][i].body.step1();
                            enemy[type][i].tracks.step1();
                        }
                    }

                    }
                    else
                    {
                        enemy[type][i].timer = enemy[type][i].max_aim;
                        enemy[type][i].tracks.setPos (0.1);
                        enemy[type][i].body.setPos (0.1);
                    }
                    enemy[type][i].body.setPR (enemy[type][i].dir_x, enemy[type][i].position.pos.x - player.position.pos.x + width/2, enemy[type][i].position.pos.y - player.position.pos.y + height/2, 0);
                    window.draw (enemy[type][i].body.sprite);
                    enemy[type][i].tracks.setPR (enemy[type][i].dir_x, enemy[type][i].position.pos.x - player.position.pos.x + width/2, enemy[type][i].position.pos.y - player.position.pos.y + height/2, 0);
                    window.draw (enemy[type][i].tracks.sprite);
                }
                //std::cout << "test3";platform
                if (enemy[type][i].isStanding||enemy[type][i].onPlatform)
                {
                    if (enemy[type][i].position.speed.x * sign (enemy[type][i].position.speed.x) > friction)
                    {
                        enemy[type][i].position.speed.x -= friction * sign (enemy[type][i].position.speed.x);
                    }
                    else
                    {
                        enemy[type][i].position.speed.x = 0;
                    }
                }

            }
        }

        for (int i=0; i<enemy[2][0].quantity; i++)
        {

            if (enemy[2][i].is)
            {
                if (enemy[2][i].hit_cooldown<=0)
                {
                    if (player.position.pos.x>=enemy[2][i].position.pos.x-60&&player.position.pos.x<=enemy[2][i].position.pos.x+60&&player.position.pos.y>=enemy[2][i].position.pos.y-40&&player.position.pos.y<=enemy[2][i].position.pos.y+40)
                    {
                        double temp_rot=rotation(player.position.pos.x-enemy[2][i].position.pos.x, player.position.pos.y-enemy[2][i].position.pos.y);
                        player.position.speed.x+=cos(temp_rot)*12;
                        player.position.speed.y+=sin(temp_rot)*12;
                        dmgToPlayer+=(1+enemy[2][i].overheat/65);
                        enemy[2][i].hit_cooldown=enemy[2][i].max_hit_cooldown;
                    }
                }
                else
                {
                    enemy[2][i].hit_cooldown--;
                }
                //std::cout << "test1";
                if (enemy[2][i].armor<=0)
                {
                    for (int j=0; j<enemy[3][i].drops; j++)
                    {
                        int random_number=0;
                        if (enemy[2][i].drop_max[j]<=enemy[2][i].drop_min[j])
                        {
                            random_number=enemy[2][i].drop_min[j];
                        }
                        else
                        {
                            random_number=enemy[2][i].drop_min[j]+rand()%(round1(enemy[2][i].drop_max[j]-enemy[2][i].drop_min[j]))*(2.0-player.not_fortune);
                        }
                        random_number=random_number/1000;
                        //std::cout << "test7";
                        for (int k=0; k<random_number; k++)
                        {
                            //std::cout << k << "\n";
                            for (int l=0; l<drop_count; l++)
                            {
                                if (!drop[l].is)
                                {
                                    drop[l].trade=false;
                                    drop[l].position=enemy[2][i].position;
                                    drop[l].position.speed.x=rand()%9-4;
                                    drop[l].position.speed.y=-3;
                                    drop[l].type=enemy[2][i].drop_type[j];
                                    drop[l].animation = item[drop[l].type].animation;
    drop[l].glint = rarity[item[drop[l].type].rarity];
    /*drop[2].position.pos.x = 450;//camera_x
    drop[2].position.pos.y = 400;
    drop[2].position.speed.x = 0;
    drop[2].position.speed.y = 0;*/
    drop[l].counter = 0;

                                    drop[l].is=true;
                                    break;
                                }
                            }
                        }
                    }



                    enemy[2][i].is=false;
                    music.openFromFile("Sounds/music/Slingshot.wav");
                    music.play();
                }
                else
                {
                    if (enemy[2][i].armor>enemy[2][i].max_armor/2)
                    {
                        enemy[2][i].overheat=0;


                    if (enemy[2][i].position.speed.y<0)
                    {
                        enemy[2][i].position.speed.y=0;
                    }
                    enemy[2][i].position.speed.x=0;
                    enemy[2][i].position.engine(enemy[2][i].head_height, enemy[2][i].height, enemy[2][i].width, M);
                    double temp_rotation=rotation(player.position.pos.x-enemy[2][i].position.pos.x, player.position.pos.y-enemy[2][i].position.pos.y);
                    while (temp_rotation<0)
                    {
                        temp_rotation+=2*PI;
                    }
                    while (temp_rotation>=2*PI)
                    {
                        temp_rotation-=2*PI;
                    }
                        //std::cout << rotation(1, -1) << " " << enemy[2][i].rotation << "\n";
                        if (temp_rotation>enemy[2][i].rotation)
                        {
                            if (temp_rotation-enemy[2][i].rotation<PI)
                            {
                                if (temp_rotation-enemy[2][i].rotation>enemy[2][i].rotation_speed)
                                {
                                    //std::cout << "test0";
                                    enemy[2][i].rotation+=enemy[2][i].rotation_speed;
                                }
                                else
                                {
                                    //std::cout << "test0";
                                    enemy[2][i].rotation=temp_rotation;
                                }
                            }
                            else
                            {
                                if (PI-temp_rotation+enemy[2][i].rotation<-enemy[2][i].rotation_speed)
                                {
                                    //std::cout << "test1";
                                    enemy[2][i].rotation-=enemy[2][i].rotation_speed;
                                }
                                else
                                {
                                    //std::cout << "test1";
                                    enemy[2][i].rotation=temp_rotation;
                                }
                            }
                        }
                        else
                        {
                            if (temp_rotation-enemy[2][i].rotation>-PI)
                            {
                                if (temp_rotation-enemy[2][i].rotation<-enemy[2][i].rotation_speed)
                                {
                                    //std::cout << "test2";
                                    enemy[2][i].rotation-=enemy[2][i].rotation_speed;
                                }
                                else
                                {
                                    //std::cout << "test3";
                                    enemy[2][i].rotation=temp_rotation;
                                }
                            }
                            else
                            {
                                if (PI-temp_rotation+enemy[2][i].rotation>enemy[2][i].rotation_speed)
                                {
                                    //std::cout << enemy[2][i].rotation << " ";
                                    //std::cout << "test4";
                                    enemy[2][i].rotation+=enemy[2][i].rotation_speed;
                                }
                                else
                                {
                                    //std::cout << "test4";
                                    enemy[2][i].rotation=temp_rotation;
                                }
                            }
                        }

                        while (enemy[2][i].rotation<0)
                        {
                            enemy[2][i].rotation+=2*PI;
                        }

                        while (enemy[2][i].rotation>=2*PI)
                        {
                            //std::cout << "test";
                            //std::cout << enemy[2][i].rotation << " ";
                            enemy[2][i].rotation-=2*PI;
                            //std::cout << enemy[2][i].rotation << "\n";
                        }
                    if (enemy[2][i].timer>0)
                    {
                        enemy[2][i].timer--;
                    }
                    else
                    {
                        enemy[2][i].timer=enemy[2][i].max_aim;
                        enemy[2][i].shoot_sound.play();
                        enemy[2][i].head.setPos(1.1);
                        //enemy[type][i].position.speed.x -= enemy[type][i].recoil * enemy[type][i].dir_x;
                        int k = -1;
                        for (int j = 0; j < projectiles_count; j++)
                        {
                            if (! (enemy_proj[j].is) )
                            {
                                k = j;
                                break;
                            }
                        }
                        if (k >= 0)
                        {




                            enemy_proj[k].is = true;
                            enemy_proj[k].acceleration = 0;
                            enemy_proj[k].animation = enemy[2][i].proj;
                            enemy_proj[k].blast = enemy[2][i].blast;
                            enemy_proj[k].damage = enemy[2][i].damage;
                            enemy_proj[k].min_damage = enemy[2][i].damage;
                            enemy_proj[k].distance_left = 1920;
                            enemy_proj[k].explosion.setBuffer (enemy[2][i].exp_buffer);
                            enemy_proj[k].gun = 0;
                            enemy_proj[k].knockback = 2;
                            enemy_proj[k].explosion_knockback = 1;
                            enemy_proj[k].multiplier = 1;
                            enemy_proj[k].radius = 2;
                            enemy_proj[k].rotation = enemy[2][i].rotation;
                            enemy_proj[k].speed = 12;
                            enemy_proj[k].x = enemy[2][i].position.pos.x;
                            enemy_proj[k].y = enemy[2][i].position.pos.y-6;
                            enemy_proj[k].time = guns[enemy[2][i].gun_holding].max_projectile_time;
                            enemy_proj[k].blast.setPos (0.1);
                            enemy_proj[k].grav=0;
                            enemy_proj[k].type=0;
                        }
                    }
                    enemy[2][i].body.setPR(1, enemy[2][i].position.pos.x - player.position.pos.x + width/2, enemy[2][i].position.pos.y - player.position.pos.y + height/2, 0);
                enemy[2][i].head.setPR(bool(cos(enemy[2][i].rotation)>0)*2-1, enemy[2][i].position.pos.x - player.position.pos.x + width/2, enemy[2][i].position.pos.y - player.position.pos.y + height/2, rt(cos(enemy[2][i].rotation), sin(enemy[2][i].rotation)));
                //std::cout << enemy[2][i].position.pos.x - player.position.pos.x + width/2 << " " << enemy[2][i].position.pos.y - player.position.pos.y + height/2 << "\n";
                window.draw(enemy[2][i].body.sprite);
                window.draw(enemy[2][i].head.sprite);
                }
                else
                {

                    if (enemy[2][i].overheat<enemy[2][i].max_overheat&&enemy[2][i].phase==0)
                    {



                    if (enemy[2][i].position.speed.y<0)
                    {
                        enemy[2][i].position.speed.y=0;
                    }
                    enemy[2][i].position.speed.x=0;
                    enemy[2][i].position.engine(enemy[2][i].head_height, enemy[2][i].height, enemy[2][i].width, M);
                    double temp_rotation=rotation(player.position.pos.x-enemy[2][i].position.pos.x, player.position.pos.y-enemy[2][i].position.pos.y);
                        while (temp_rotation<0)
                    {
                        temp_rotation+=2*PI;
                    }
                    while (temp_rotation>=2*PI)
                    {
                        temp_rotation-=2*PI;
                    }
                        //std::cout << rotation(1, -1) << " " << enemy[2][i].rotation << "\n";
                        if (temp_rotation>enemy[2][i].rotation)
                        {
                            if (temp_rotation-enemy[2][i].rotation<PI)
                            {
                                if (temp_rotation-enemy[2][i].rotation>enemy[2][i].rotation_speed*2)
                                {
                                    //std::cout << "test0";
                                    enemy[2][i].rotation+=enemy[2][i].rotation_speed*2;
                                }
                                else
                                {
                                    //std::cout << "test0";
                                    enemy[2][i].rotation=temp_rotation;
                                }
                            }
                            else
                            {
                                if (PI-temp_rotation+enemy[2][i].rotation<-enemy[2][i].rotation_speed*2)
                                {
                                    //std::cout << "test1";
                                    enemy[2][i].rotation-=enemy[2][i].rotation_speed*2;
                                }
                                else
                                {
                                    //std::cout << "test1";
                                    enemy[2][i].rotation=temp_rotation;
                                }
                            }
                        }
                        else
                        {
                            if (temp_rotation-enemy[2][i].rotation>-PI)
                            {
                                if (temp_rotation-enemy[2][i].rotation<-enemy[2][i].rotation_speed*2)
                                {
                                    //std::cout << "test2";
                                    enemy[2][i].rotation-=enemy[2][i].rotation_speed*2;
                                }
                                else
                                {
                                    //std::cout << "test3";
                                    enemy[2][i].rotation=temp_rotation;
                                }
                            }
                            else
                            {
                                if (PI-temp_rotation+enemy[2][i].rotation>enemy[2][i].rotation_speed*2)
                                {
                                    //std::cout << enemy[2][i].rotation << " ";
                                    //std::cout << "test4";
                                    enemy[2][i].rotation+=enemy[2][i].rotation_speed*2;
                                }
                                else
                                {
                                    //std::cout << "test4";
                                    enemy[2][i].rotation=temp_rotation;
                                }
                            }
                        }

                        while (enemy[2][i].rotation<0)
                        {
                            enemy[2][i].rotation+=2*PI;
                        }

                        while (enemy[2][i].rotation>=2*PI)
                        {
                            //std::cout << "test";
                            //std::cout << enemy[2][i].rotation << " ";
                            enemy[2][i].rotation-=2*PI;
                            //std::cout << enemy[2][i].rotation << "\n";
                        }
                    if (enemy[2][i].timer>0)
                    {
                        enemy[2][i].timer--;
                    }
                    else
                    {
                        enemy[2][i].timer=enemy[2][i].max_aim/2;
                        enemy[2][i].shoot_sound.play();
                        enemy[2][i].overheat+=enemy[2][i].max_aim/2;
                        if (enemy[2][i].overheat>=enemy[2][i].max_overheat)
                        {
                            enemy[2][i].phase=1;
                        }
                        enemy[2][i].head.setPos(1.1);
                        enemy[2][i].heat[0].setPos(1.1);
                        enemy[2][i].heat[1].setPos(1.1);
                        enemy[2][i].heat[2].setPos(1.1);
                        enemy[2][i].heat[3].setPos(1.1);
                        enemy[2][i].heat[4].setPos(1.1);
                        //enemy[type][i].position.speed.x -= enemy[type][i].recoil * enemy[type][i].dir_x;
                        int k = -1;
                        for (int j = 0; j < projectiles_count; j++)
                        {
                            if (! (enemy_proj[j].is) )
                            {
                                k = j;
                                break;
                            }
                        }
                        if (k >= 0)
                        {




                            enemy_proj[k].is = true;
                            enemy_proj[k].acceleration = 0;
                            enemy_proj[k].animation = enemy[2][i].proj;
                            enemy_proj[k].blast = enemy[2][i].blast;
                            enemy_proj[k].damage = enemy[2][i].damage;
                            enemy_proj[k].min_damage = enemy[2][i].damage;
                            enemy_proj[k].distance_left = 1920;
                            enemy_proj[k].explosion.setBuffer (enemy[2][i].exp_buffer);
                            enemy_proj[k].gun = 0;
                            enemy_proj[k].knockback = 2;
                            enemy_proj[k].explosion_knockback = 1;
                            enemy_proj[k].multiplier = 1;
                            enemy_proj[k].radius = 2;
                            enemy_proj[k].rotation = enemy[2][i].rotation+random(5);
                            enemy_proj[k].speed = 12;
                            enemy_proj[k].x = enemy[2][i].position.pos.x;
                            enemy_proj[k].y = enemy[2][i].position.pos.y-6;
                            enemy_proj[k].time = guns[enemy[2][i].gun_holding].max_projectile_time;
                            enemy_proj[k].blast.setPos (0.1);
                            enemy_proj[k].grav=0;
                            enemy_proj[k].type=0;
                        }

                    }

                }
                else
                {

                    enemy[2][i].overheat-=2;
                    if (enemy[2][i].overheat<=0)
                    {
                        enemy[2][i].phase=0;
                        enemy[2][i].overheat=0;
                    }
                }


                enemy[2][i].body.setPR(1, enemy[2][i].position.pos.x - player.position.pos.x + width/2, enemy[2][i].position.pos.y - player.position.pos.y + height/2, 0);
                window.draw(enemy[2][i].body.sprite);

                if (enemy[2][i].overheat/30==0)
                {
                    enemy[2][i].head.setPR(bool(cos(enemy[2][i].rotation)>0)*2-1, enemy[2][i].position.pos.x - player.position.pos.x + width/2, enemy[2][i].position.pos.y - player.position.pos.y + height/2, rt(cos(enemy[2][i].rotation), sin(enemy[2][i].rotation)));
                //std::cout << enemy[2][i].position.pos.x - player.position.pos.x + width/2 << " " << enemy[2][i].position.pos.y - player.position.pos.y + height/2 << "\n";

                window.draw(enemy[2][i].head.sprite);
                }
                else if (enemy[2][i].overheat/30==1)
                {

                    enemy[2][i].heat[0].setPR(bool(cos(enemy[2][i].rotation)>0)*2-1, enemy[2][i].position.pos.x - player.position.pos.x + width/2, enemy[2][i].position.pos.y - player.position.pos.y + height/2, rt(cos(enemy[2][i].rotation), sin(enemy[2][i].rotation)));
                //std::cout << enemy[2][i].position.pos.x - player.position.pos.x + width/2 << " " << enemy[2][i].position.pos.y - player.position.pos.y + height/2 << "\n";

                window.draw(enemy[2][i].heat[0].sprite);
                }
                else if (enemy[2][i].overheat/30==2)
                {
                    enemy[2][i].heat[1].setPR(bool(cos(enemy[2][i].rotation)>0)*2-1, enemy[2][i].position.pos.x - player.position.pos.x + width/2, enemy[2][i].position.pos.y - player.position.pos.y + height/2, rt(cos(enemy[2][i].rotation), sin(enemy[2][i].rotation)));
                //std::cout << enemy[2][i].position.pos.x - player.position.pos.x + width/2 << " " << enemy[2][i].position.pos.y - player.position.pos.y + height/2 << "\n";

                window.draw(enemy[2][i].heat[1].sprite);
                }
                else if (enemy[2][i].overheat/30==3)
                {
                    enemy[2][i].heat[2].setPR(bool(cos(enemy[2][i].rotation)>0)*2-1, enemy[2][i].position.pos.x - player.position.pos.x + width/2, enemy[2][i].position.pos.y - player.position.pos.y + height/2, rt(cos(enemy[2][i].rotation), sin(enemy[2][i].rotation)));
                //std::cout << enemy[2][i].position.pos.x - player.position.pos.x + width/2 << " " << enemy[2][i].position.pos.y - player.position.pos.y + height/2 << "\n";

                window.draw(enemy[2][i].heat[2].sprite);
                }
                else if (enemy[2][i].overheat/30==4)
                {
                    enemy[2][i].heat[3].setPR(bool(cos(enemy[2][i].rotation)>0)*2-1, enemy[2][i].position.pos.x - player.position.pos.x + width/2, enemy[2][i].position.pos.y - player.position.pos.y + height/2, rt(cos(enemy[2][i].rotation), sin(enemy[2][i].rotation)));
                //std::cout << enemy[2][i].position.pos.x - player.position.pos.x + width/2 << " " << enemy[2][i].position.pos.y - player.position.pos.y + height/2 << "\n";

                window.draw(enemy[2][i].heat[3].sprite);
                }
                else
                {
                    enemy[2][i].heat[4].setPR(bool(cos(enemy[2][i].rotation)>0)*2-1, enemy[2][i].position.pos.x - player.position.pos.x + width/2, enemy[2][i].position.pos.y - player.position.pos.y + height/2, rt(cos(enemy[2][i].rotation), sin(enemy[2][i].rotation)));
                //std::cout << enemy[2][i].position.pos.x - player.position.pos.x + width/2 << " " << enemy[2][i].position.pos.y - player.position.pos.y + height/2 << "\n";

                window.draw(enemy[2][i].heat[4].sprite);
                }




                }
                if (enemy[2][i].head.pos>1)
                enemy[2][i].head.step1();
                if (enemy[2][i].heat[0].pos>1)
                        enemy[2][i].heat[0].step1();
                        if (enemy[2][i].heat[1].pos>1)
                        enemy[2][i].heat[1].step1();
                        if (enemy[2][i].heat[2].pos>1)
                        enemy[2][i].heat[2].step1();
                        if (enemy[2][i].heat[3].pos>1)
                        enemy[2][i].heat[3].step1();
                        if (enemy[2][i].heat[4].pos>1)
                        enemy[2][i].heat[4].step1();



                }

                //std::cout<<"test";
            }
        }

        for (int i=0; i<enemy[3][0].quantity; i++)
        {

            if (enemy[3][i].is)
            {
                //std::cout << "test1";
                if (enemy[3][i].hit_cooldown<=0)
                {
                    if (player.position.pos.x>=enemy[3][i].position.pos.x-60&&player.position.pos.x<=enemy[3][i].position.pos.x+60&&player.position.pos.y>=enemy[3][i].position.pos.y-40&&player.position.pos.y<=enemy[3][i].position.pos.y+40)
                    {
                        double temp_rot=rotation(player.position.pos.x-enemy[3][i].position.pos.x, player.position.pos.y-enemy[3][i].position.pos.y);
                        player.position.speed.x+=cos(temp_rot)*12;
                        player.position.speed.y+=sin(temp_rot)*12;
                        dmgToPlayer+=1;
                        enemy[3][i].hit_cooldown=enemy[3][i].max_hit_cooldown;
                    }
                }
                else
                {
                    enemy[3][i].hit_cooldown--;
                }
                //std::cout << "test2";
                //std::cout << "test1";
                double temp_rotation;//=rotation(player.position.pos.x-enemy[3][i].position.pos.x, -std::sqrt(1.0-((player.position.pos.x-enemy[3][i].position.pos.x)*(player.position.pos.x-enemy[3][i].position.pos.x))))/2;
                double tem_sin2=(player.position.pos.x-enemy[3][i].position.pos.x)*gravity/900.0;
                //std::cout <<tem_sin2 <<" ";rand
                if (tem_sin2>1)
                {
                    tem_sin2=1;
                }
                else if (tem_sin2<-1)
                {
                    tem_sin2=-1;
                }
                temp_rotation=-rotation(-std::sqrt(1.0-tem_sin2*tem_sin2), tem_sin2)/2;
                if (enemy[3][i].armor<=0)
                {
                    for (int j=0; j<enemy[3][i].drops; j++)
                    {
                        int random_number=0;
                        if (enemy[3][i].drop_max[j]<=enemy[3][i].drop_min[j])
                        {
                            random_number=enemy[3][i].drop_min[j];
                        }
                        else
                        {
                            random_number=enemy[3][i].drop_min[j]+rand()%(round1(enemy[3][i].drop_max[j]-enemy[3][i].drop_min[j]))*(2.0-player.not_fortune);
                        }
                        random_number=random_number/1000;
                        //std::cout << "test7";
                        for (int k=0; k<random_number; k++)
                        {
                            //std::cout << k << "\n";
                            for (int l=0; l<drop_count; l++)
                            {
                                if (!drop[l].is)
                                {
                                    drop[l].trade=false;
                                    drop[l].position=enemy[3][i].position;
                                    drop[l].position.speed.x=rand()%9-4;
                                    drop[l].position.speed.y=-3;
                                    drop[l].type=enemy[3][i].drop_type[j];
                                    drop[l].animation = item[drop[l].type].animation;
    drop[l].glint = rarity[item[drop[l].type].rarity];
    /*drop[2].position.pos.x = 450;//camera_x
    drop[2].position.pos.y = 400;
    drop[2].position.speed.x = 0;
    drop[2].position.speed.y = 0;*/
    drop[l].counter = 0;

                                    drop[l].is=true;
                                    break;
                                }
                            }
                        }
                    }



                    enemy[3][i].is=false;
                    music.openFromFile("Sounds/music/Slingshot.wav");
                    music.play();
                }
                else
                {
                    if (enemy[3][i].position.speed.y<0)
                    {
                        enemy[3][i].position.speed.y=0;
                    }
                    enemy[3][i].position.speed.x=0;
                    //std::cout << "test3";
                    enemy[3][i].position.engine(enemy[3][i].head_height, enemy[3][i].height, enemy[3][i].width, M);
                    //std::cout << "test4";

                    if (enemy[3][i].timer>0)
                    {
                        if (enemy[3][i].head.pos>1)
                        {
                            enemy[3][i].head.step1();
                        }
                        //std::cout << "1 ";
                        enemy[3][i].timer--;
                    }
                    else
                    {
                        //std::cout << "2\n";


                        enemy[3][i].timer=enemy[3][i].max_aim;
                        enemy[3][i].shoot_sound.play();
                        enemy[3][i].head.setPos(1.1);
                        //enemy[type][i].position.speed.x -= enemy[type][i].recoil * enemy[type][i].dir_x;
                        int k = -1;
                        for (int j = 0; j < projectiles_count; j++)
                        {
                            if (! (enemy_proj[j].is) )
                            {
                                k = j;
                                break;
                            }
                        }
                        if (k >= 0)
                        {
                            //std::cout << "test8";




                            enemy_proj[k].is = true;
                            enemy_proj[k].acceleration = 0;
                            enemy_proj[k].animation = enemy[3][i].proj;
                            enemy_proj[k].blast = enemy[3][i].blast;
                            enemy_proj[k].damage = enemy[3][i].damage;
                            enemy_proj[k].min_damage = 0;
                            enemy_proj[k].distance_left = 1920;
                            enemy_proj[k].explosion.setBuffer (enemy[3][i].exp_buffer);
                            enemy_proj[k].gun = 0;
                            enemy_proj[k].knockback = 2;
                            enemy_proj[k].explosion_knockback = 10;
                            enemy_proj[k].multiplier = 1;
                            enemy_proj[k].radius = 80;
                            enemy_proj[k].rotation = temp_rotation;
                            enemy_proj[k].speed = 30;
                            enemy_proj[k].x = enemy[3][i].position.pos.x;
                            enemy_proj[k].y = enemy[3][i].position.pos.y;
                            enemy_proj[k].time = 50;
                            enemy_proj[k].blast.setPos (0.1);
                            enemy_proj[k].grav=1;
                            enemy_proj[k].type=0;
                        }
                    }

                }
                enemy[3][i].body.setPR(1, enemy[3][i].position.pos.x - player.position.pos.x + width/2, enemy[3][i].position.pos.y - player.position.pos.y + height/2, 0);
                enemy[3][i].head.setPR(1, enemy[3][i].position.pos.x - player.position.pos.x + width/2, enemy[3][i].position.pos.y - player.position.pos.y + height/2, temp_rotation);

                //std::cout << enemy[2][i].position.pos.x - player.position.pos.x + width/2 << " " << enemy[2][i].position.pos.y - player.position.pos.y + height/2 << "\n";

                window.draw(enemy[3][i].head.sprite);
                window.draw(enemy[3][i].body.sprite);
                //std::cout<<"test";
            }
        }




        //std::cout << "test7";

        //std::cout << "test8";
        //infoplay
        for (int i=0; i<enemy[1][0].quantity; i++)
        {
            if (enemy[1][i].is)
            {//type
                if (enemy[1][i].health<=0||enemy[1][i].armor<=0)
                {
                    enemy[1][i].blast.setPR(1, enemy[1][i].position.pos.x-player.position.pos.x+width/2, enemy[1][i].position.pos.y-player.position.pos.y+height/2, 0);
                    window.draw(enemy[1][i].blast.sprite);

                }

            }
        }//drop
        if (temp_dist<60&&canShoot(player.position.pos.x, player.position.pos.y, drop[temp_i].position.pos.x, drop[temp_i].position.pos.y, M.M))
        {
            if ((player.money>=item[drop[temp_i].type].stock_price&&spacePressed)||(drop[temp_i].trade==false&&(item[drop[temp_i].type].auto_pickup||spacePressed)))
            {
                bool pickup=true;


                if (drop[temp_i].type==0)
                {
                    item[drop[temp_i].type].pickup_sound.play();
                    player.money++;
                }
                else if (drop[temp_i].type==1)
                {
                    item[drop[temp_i].type].pickup_sound.play();
                    player.money+=5;
                }
                else if (drop[temp_i].type==2)
                {
                    item[drop[temp_i].type].pickup_sound.play();
                    player.money+=10;
                }
                else if (drop[temp_i].type==3)
                {
                    item[drop[temp_i].type].pickup_sound.play();
                    player.money+=25;
                }
                else if (drop[temp_i].type==4)
                {
                    item[drop[temp_i].type].pickup_sound.play();
                    player.money+=50;
                }
                else if (drop[temp_i].type==5)
                {
                    item[drop[temp_i].type].pickup_sound.play();
                    player.money+=100;//setBlock
                }
                else if (drop[temp_i].type==6)
                {
                    item[drop[temp_i].type].pickup_sound.play();
                    player.not_fortune*=0.95;
                }
                else if (drop[temp_i].type==7)
                {

                    if (player.armor<player.max_armor)
                    {
                        item[drop[temp_i].type].pickup_sound.play();
                        player.armor++;
                    }
                    else
                    {
                        pickup=false;
                    }
                }
                else if (drop[temp_i].type==8)
                {

                    if (player.dynamite<player.max_dynamite)
                    {
                        item[drop[temp_i].type].pickup_sound.play();
                        //std::cout << item[drop[temp_i].type].pickup_sound.getVolume();
                        player.dynamite++;
                    }
                    else
                    {
                        pickup=false;
                    }

                }
                else if (drop[temp_i].type==9)
                {

                    if (player.health<player.max_health)
                    {
                        item[drop[temp_i].type].pickup_sound.play();
                        player.health=player.max_health;
                    }
                    else
                    {
                        pickup=false;
                    }
                }
                else if (drop[temp_i].type==10)
                {
                    item[drop[temp_i].type].pickup_sound.play();
                    player.money-=item[drop[temp_i].type].stock_price*bool(drop[temp_i].trade);
                    pickup=false;
                    drop[temp_i].type=guns[player.gun].item;
                    drop[temp_i].trade=false;
                    drop[temp_i].glint=rarity[item[drop[temp_i].type].rarity];
                    drop[temp_i].animation=item[drop[temp_i].type].animation;
                    player.gun=0;
                    player.gun_holding=player.gun;
                    drop[temp_i].position=player.position;
                    drop[temp_i].position.speed.y-=3;

                }
                else if (drop[temp_i].type==11)
                {
                    item[drop[temp_i].type].pickup_sound.play();
                    player.money-=item[drop[temp_i].type].stock_price*bool(drop[temp_i].trade);
                    pickup=false;
                    drop[temp_i].type=guns[player.gun].item;
                    drop[temp_i].trade=false;
                    drop[temp_i].glint=rarity[item[drop[temp_i].type].rarity];
                    drop[temp_i].animation=item[drop[temp_i].type].animation;
                    player.gun=2;
                    player.gun_holding=player.gun;
                    drop[temp_i].position=player.position;
                    drop[temp_i].position.speed.y-=3;

                }
                else if (drop[temp_i].type==12)
                {
                    item[drop[temp_i].type].pickup_sound.play();
                    player.shells++;
                }
                if (pickup)
                {
                    player.money-=item[drop[temp_i].type].stock_price*bool(drop[temp_i].trade);
                //pick_up
                int t=-1;
                for (int i=0; i<particle_count; i++)
                {
                    if (particle[i].timer<=0)
                    {
                        t=i;
                        break;
                    }
                }
                if (t>=0)
                {
                    particle[t].timer=10;
                    particle[t].pos=drop[temp_i].position.pos;
                    particle[t].animation=drop[temp_i].animation;
                    particle[t].type=0;
                }


                drop[temp_i].is=false;
                }
            }//proj
            else
            {
                frame.setPosition(drop[temp_i].position.pos.x-player.position.pos.x+width/2-150, drop[temp_i].position.pos.y-player.position.pos.y);

                name.setString(item[drop[temp_i].type].name);
                stats.setString(item[drop[temp_i].type].description);
                price.setString("price: " + to_str(item[drop[temp_i].type].stock_price));

                name.setPosition(drop[temp_i].position.pos.x-player.position.pos.x+width/2-130, drop[temp_i].position.pos.y-player.position.pos.y+20);
                stats.setPosition(drop[temp_i].position.pos.x-player.position.pos.x+width/2-130, drop[temp_i].position.pos.y-player.position.pos.y+60);
                price.setPosition(drop[temp_i].position.pos.x-player.position.pos.x+width/2-130, drop[temp_i].position.pos.y-player.position.pos.y+175);

                if (frame.getPosition().x+player.position.pos.x-width/2<camera_x)//height/2
                {
                    frame.setPosition(camera_x-player.position.pos.x+width/2, frame.getPosition().y);
                    name.setPosition(camera_x-player.position.pos.x+width/2+20, frame.getPosition().y+20);
                    stats.setPosition(camera_x-player.position.pos.x+width/2+20, frame.getPosition().y+60);
                    price.setPosition(camera_x-player.position.pos.x+width/2+20, frame.getPosition().y+175);
                }
                else if (frame.getPosition().x+player.position.pos.x-width/2>camera_x+width-300)
                {
                    frame.setPosition(camera_x-player.position.pos.x+width/2+width-300, frame.getPosition().y);
                    name.setPosition(camera_x-player.position.pos.x+width/2+width-280, frame.getPosition().y+20);
                    stats.setPosition(camera_x-player.position.pos.x+width/2+width-280, frame.getPosition().y+60);
                    price.setPosition(camera_x-player.position.pos.x+width/2+width-280, frame.getPosition().y+175);
                }
                if (frame.getPosition().y+player.position.pos.y-height/2<camera_y)
                {
                    frame.setPosition(frame.getPosition().x, camera_y-player.position.pos.y+height/2);
                    name.setPosition(frame.getPosition().x+20, camera_y-player.position.pos.y+height/2+20);
                    stats.setPosition(frame.getPosition().x+20, camera_y-player.position.pos.y+height/2+60);
                    price.setPosition(frame.getPosition().x+20, camera_y-player.position.pos.y+height/2+175);
                }
                else if (frame.getPosition().y+player.position.pos.y-height/2>camera_y+340)
                {
                    frame.setPosition(frame.getPosition().x, camera_y-player.position.pos.y+height-200);
                    name.setPosition(frame.getPosition().x+20, camera_y-player.position.pos.y+height-180);
                    stats.setPosition(frame.getPosition().x+20, camera_y-player.position.pos.y+height-140);
                    price.setPosition(frame.getPosition().x+20, camera_y-player.position.pos.y+height-25);
                }
                if (player.money>=item[drop[temp_i].type].stock_price)
                {//room
                    price.setFillColor(Color::Green);
                }
                else
                {
                    price.setFillColor(Color::Red);
                }

                window.draw(frame);
                window.draw(name);
                window.draw(stats);
                if (drop[temp_i].trade)
                {
                    window.draw(price);
                }

            }
        }

        for (int i=0; i<particle_count; i++)
        {
            if (particle[i].timer>0)
            {
                if (particle[i].type==0)
                {

                    particle[i].animation.sprite.setColor(Color(255, 255, 255, 255-(20*(10-particle[i].timer))));
                    particle[i].animation.setPR(1, particle[i].pos.x-player.position.pos.x+width/2, particle[i].pos.y-player.position.pos.y+height/2-14-(10-particle[i].timer)*(10-particle[i].timer)*0.7, 0);
                    window.draw(particle[i].animation.sprite);
                    particle[i].animation.step1();
                    particle[i].timer--;
                }
                else if (particle[i].type==1)
                {
                    particle[i].animation.sprite.setColor(Color(255, 255, 255, 255-(4*(45-particle[i].timer))));
                    particle[i].animation.setPR(1, particle[i].pos.x-player.position.pos.x+width/2+random(1), particle[i].pos.y-player.position.pos.y+height/2+(45-particle[i].timer)*(45-particle[i].timer)*0.05, 0);
                    window.draw(particle[i].animation.sprite);
                    //particle[i].animation.step1();camera_x
                    particle[i].timer--;
                }

            }
        }
        for (int i=0; i<drop_count; i++)
        {
            if (drop[i].is)
            {
                drop[i].glint.step1();
                drop[i].animation.step1();
                if (drop[i].counter<15)
                {
                    drop[i].glint.setPR (1, drop[i].position.pos.x - player.position.pos.x + width/2, drop[i].position.pos.y - player.position.pos.y + height/2-15, 0);
                    drop[i].animation.setPR (1, drop[i].position.pos.x - player.position.pos.x + width/2, drop[i].position.pos.y - player.position.pos.y + height/2-15, 0);
                }
                else if ((drop[i].counter<30&&drop[i].counter>=15)||(drop[i].counter<60&&drop[i].counter>=45))
                {
                    drop[i].glint.setPR (1, drop[i].position.pos.x - player.position.pos.x + width/2, drop[i].position.pos.y - player.position.pos.y + height/2-14, 0);
                    drop[i].animation.setPR (1, drop[i].position.pos.x - player.position.pos.x + width/2, drop[i].position.pos.y - player.position.pos.y + height/2-14, 0);
                }
                else
                {
                    drop[i].glint.setPR (1, drop[i].position.pos.x - player.position.pos.x + width/2, drop[i].position.pos.y - player.position.pos.y + height/2-13, 0);
                    drop[i].animation.setPR (1, drop[i].position.pos.x - player.position.pos.x + width/2, drop[i].position.pos.y - player.position.pos.y + height/2-13, 0);
                }
                window.draw (drop[i].glint.sprite);
                window.draw (drop[i].animation.sprite);
            }

        }
        //std::cout << "test5";
        for (int i = round1 (player.position.pos.x - player.width)&&!toRespawn; i <= round1 (player.position.pos.x + player.width)&&i<M.width; i++)
        {
            for (int j = round1 (player.position.pos.y - player.head_height); j <= round1 (player.position.pos.y + player.height)&&j<M.height; j++)
            {
                if (M.M[i][j] == start_game)
                {
                    //std::cout << "test1";
                    //t=false;enemy
                    /*bool** temp_room = new bool*[room_count*2-1];
                    for (int k=0; k<room_count*2-1; k++)
                    {
                        temp_room[k]=new bool[room_count*2-1];draw
                    }*/
                    //
                    int temp_room_num=0;

                    stage++;
                    if (stage<stage_count)
                    {
                        if (stage==0)
                        {
                            music.openFromFile("Sounds/music/Slingshot.wav");
                            music.play();
                        }
                        for (int k=0; k<room_count; k++)
                        {
                            room[k].is=false;
                        }
                        for (int k=0; k<template_types; k++)
                        {
                            temp_room_num+=cave[stage].quantity[k];
                        }
                        room[0].pos.setXY(0, 0);
                        room[0].is=true;
                        //std::cout<<temp_room_num;
                        for (int k=1; k<temp_room_num; k++)
                        {



                            int temp_room=rand()%k;

                            int temp_bool=false;
                            int temp_dir=rand()%4;
                            int temp_temp_room=temp_room;
                            int temp_temp_dir=temp_dir;
                            int temp_counter=0;

                            while (temp_bool==false&&temp_counter<room_count*4)
                            {

                                temp_bool=true;
                                temp_counter++;
                            for (int l=0; l<k; l++)
                            {
                                //std::cout << "test";
                                if (temp_temp_dir==0)
                                {
                                    if (room[l].pos.x==room[temp_temp_room].pos.x&&room[l].pos.y==room[temp_temp_room].pos.y-1)
                                    {
                                        temp_bool=false;
                                        l=k;
                                    }
                                }
                                else if (temp_temp_dir==1)
                                {
                                    if (room[l].pos.x==room[temp_temp_room].pos.x+1&&room[l].pos.y==room[temp_temp_room].pos.y)
                                    {
                                        temp_bool=false;
                                        l=k;
                                    }
                                }
                                else if (temp_temp_dir==2)
                                {
                                    if (room[l].pos.x==room[temp_temp_room].pos.x&&room[l].pos.y==room[temp_temp_room].pos.y+1)
                                    {
                                        temp_bool=false;
                                        l=k;
                                    }
                                }
                                else if (temp_temp_dir==3)
                                {
                                    if (room[l].pos.x==room[temp_temp_room].pos.x-1&&room[l].pos.y==room[temp_temp_room].pos.y)
                                    {
                                        temp_bool=false;
                                        l=k;
                                    }
                                }
                            }
                            if (temp_bool)
                            {//drop
                                if (temp_temp_dir==0)
                                {
                                    room[k].pos.x=room[temp_temp_room].pos.x;
                                    room[k].pos.y=room[temp_temp_room].pos.y-1;

                                }
                                else if (temp_temp_dir==1)
                                {
                                    room[k].pos.x=room[temp_temp_room].pos.x+1;
                                    room[k].pos.y=room[temp_temp_room].pos.y;
                                }
                                else if (temp_temp_dir==2)
                                {
                                    room[k].pos.x=room[temp_temp_room].pos.x;
                                    room[k].pos.y=room[temp_temp_room].pos.y+1;
                                }
                                else if (temp_temp_dir==3)
                                {
                                    room[k].pos.x=room[temp_temp_room].pos.x-1;
                                    room[k].pos.y=room[temp_temp_room].pos.y;
                                }
                                room[k].is=true;
                                //std::cout << room[k].pos.x << std::endl << room[k].pos.y << "\n\n";

                            }
                            else
                            {
                                temp_temp_dir++;
                                if (temp_temp_dir>=4)
                                {
                                    temp_temp_dir=0;
                                }
                                if (temp_temp_dir==temp_dir)
                                {
                                    temp_temp_room++;
                                }
                                if (temp_temp_room>=k)
                                {
                                    temp_temp_room=0;
                                }
                            }
                            }
                        }
                        int min_x=0;
                    int min_y=0;

                    int max_x=0;
                    int max_y=0;
//std::cout << "test1";
                    for (int k=0; k<room_count; k++)
                    {//visited
                        if (room[k].is)
                        {
                            if (min_x>round1(room[k].pos.x))
                            {
                                min_x=round1(room[k].pos.x);
                                //std::cout << "test1";
                            }
                            if (min_y>round1(room[k].pos.y))
                            {
                                min_y=round1(room[k].pos.y);
                                //std::cout << "test2";
                            }

                            if (max_x<round1(room[k].pos.x))
                            {
                                max_x=round1(room[k].pos.x);
                                //std::cout << "test3";
                            }
                            if (max_y<round1(room[k].pos.y))
                            {
                                max_y=round1(room[k].pos.y);
                                //std::cout << "test4";
                            }
                            //std::cout << room[k].pos.x;
                            //std::cout << room[k].pos.y;
                            //std::cout << "test";
                        }
                    }
                    //std::cout << "test2";
                    for (int k=0; k<room_count; k++)
                    {
                        room[k].pos.x-=min_x;
                        room[k].pos.y-=min_y;
                    }
                    max_x-=min_x;
                    max_y-=min_y;
                    int temp_spawn_room=0;

                                    //temp_spawn_room=0;
                                    bool tempBool=true;
                                    int temp_boss_room=-1;
                                    int temp_boss_type=0;//player.healthenemy[i][j].room player.roomposition
                                    for (int l=0; l<platform_types; l++)
                    {
                        for (int m=0; m<platform[l][0].quantity; m++)
                                {
                                    platform[l][m].is=false;
                                    platform[l][m].phase=0;
                                }
                    }

                    //int temp__=0;
                    //std::cout << "test";
                    //std::cout << "test3";particle
                        bool* temp_bool=new bool[temp_room_num];
                        for (int k=0; k<temp_room_num; k++)
                        {
                            temp_bool[k]=true;
                        }
                        int temp_max_prob=0;
                        for (int m=0; m<room_template[temp_boss_type][0].quantity; m++)
                                    {
                                        temp_max_prob+=room_template[temp_boss_type][m].probability;
                                    }
                                    int temp_prob=rand()%temp_max_prob;
                                    int temp_type=-1;
                                    while (temp_prob>=0)
                                    {
                                        temp_type++;
                                        temp_prob-=room_template[temp_boss_type][temp_type].probability;
                                    }
                                    //std::cout << "test";
                                    if (temp_type>=room_template[temp_boss_type][0].quantity)
                                    {
                                        temp_type=room_template[temp_boss_type][0].quantity-1;
                                    }
                                    //std::cout << "test4";
                        if (temp_boss_room>=0)
                        {
                            temp_bool[temp_boss_room]=false;
                            vec temp_pos=room[temp_boss_room].pos;

                            if (room[temp_boss_room].drop_count>0)
                            {
                                delete[] room[temp_boss_room].drop;
                            }

                                    room[temp_boss_room]=room_template[temp_boss_type][temp_type];

                                    //std::cout << "test1";
                                    if (room[temp_boss_room].drop_count>0)
                                    {

                                        room[temp_boss_room].drop=new Drop[room[temp_boss_room].drop_count];
                                    }
                                    //std::cout << "test3";
                                    for (int m=0; m<room_template[temp_boss_type][temp_type].drop_count; m++)
                                    {


                                        room[temp_boss_room].drop[m]=room_template[temp_boss_type][temp_type].drop[m];
                                        room[temp_boss_room].drop[m].position.pos.setXY(room_template[temp_boss_type][temp_type].drop[m].position.pos.x, room_template[temp_boss_type][temp_type].drop[m].position.pos.y);
                                        //std::cout << m << room_template[l][temp_type].drop[m].position.pos.x;

                                        if(!room_template[temp_boss_type][temp_type].drop_discovered[m])
                                        {
                                            room[temp_boss_room].drop[m].type=6+rand()%(item_types-6);
                                        }


                                    }
                                    room[temp_boss_room].pos=temp_pos;
                                    room[temp_boss_room].spawn=room_template[temp_boss_type][temp_type].spawn;
                                    room[temp_boss_room].visited=false;
                                    room[temp_boss_room].is=true;
                                    room[temp_boss_room].boss=room_template[temp_boss_type][temp_type].boss;
                                    //temp__=temp_type;
                        }
                        //std::cout << "test5";
                        //std::cout << "test02";
                        for (int k=0; k<temp_room_num; k++)
                        {
                            //if(k!=temp_boss_room)





                            int temp_=0;




                            //std::cout << "test5a";
                            //std::cout << "test";drop
                            int random_number=rand()%(temp_room_num-k);

                            for (int l=0; l<=random_number; l++)
                            {
                                temp_++;
                                if (temp_>=temp_room_num)
                                    {
                                        temp_=0;
                                    }
                                while (temp_bool[temp_]==false)
                                {
                                    //std::cout << "testt";
                                    temp_++;
                                    if (temp_>=temp_room_num)
                                    {
                                        temp_=0;
                                    }
                                }

                            }
                            //temp_bool[temp_]=false;

                            //std::cout << "test5b";
                            //std::cout << "test51";

                            //std::cout << "test52";
                            //std::cout << "TEST";


                            int temp_k=k;
                            //std::cout << "\n";

                            for (int l=0; l<template_types; l++)
                            {




//std::cout << "test5-0";
                                temp_k-=cave[stage].quantity[l];
//std::cout << "test5-1";
                                if (temp_k<0)
                                {
                                    //std::cout << l << " ";
                                    //std::cout << "test6a";

                                    //std::cout << "test";
                                    temp_max_prob=0;
                                    //std::cout << "test53";
                                    for (int m=0; m<room_template[l][0].quantity/*-bool(room_template[l][0].boss)*/; m++)
                                    {
                                        temp_max_prob+=room_template[l][m].probability;
                                    }
                                    //std::cout << "test54";
                                    //std::cout << temp_max_prob;
                                    temp_prob=0;
                                    if (temp_max_prob>0)
                                    {
                                        temp_prob=(rand()%temp_max_prob);
                                    }

                                    temp_type=-1;
                                    //std::cout << "test5-";
                                    //std::cout << "test1";
                                    //std::cout << "test1";
                                    while (temp_prob>=0)
                                    {

                                        temp_type++;

                                        //std::cout << "test";
                                        temp_prob-=room_template[l][temp_type].probability;
                                        //std::cout << "test1";
                                        /*while(room_template[l][temp_type].boss)
                                        {
                                            temp_type++;
                                        }*/
                                    }
                                    //std::cout << temp_type;
                                    //std::cout << "test6b";
                                    //std::cout << "test2";
                                    //std::cout << "test55";
                                    //std::cout << "test";
                                    if (temp_type>=room_template[l][0].quantity)
                                    {
                                        temp_type=room_template[l][0].quantity-1;
                                    }

                                    //std::cout << "test56";
                                    //if (temp_type<0)
                                    if (temp_type>=0)
                                    {
                                        //std::cout << "test56";
                                        temp_bool[temp_]=false;



                                    vec temp_pos=room[temp_].pos;
                                    if (room[temp_].drop_count>0)
                                    {
                                        delete[] room[temp_].drop;
                                    }
                                    room[temp_]=room_template[l][temp_type];
                                    //std::cout << "test57";
                                    //std::cout << "test1";
                                    //std::cout << temp_ << " " << room[temp_].background.length << "\n";
                                    if (room[temp_].drop_count>0)
                                    {


                                        room[temp_].drop=new Drop[room[temp_].drop_count];
                                    }
                                    //std::cout << "test58";
                                    //std::cout << "test3";
                                    for (int m=0; m<room_template[l][temp_type].drop_count; m++)
                                    {


                                        room[temp_].drop[m]=room_template[l][temp_type].drop[m];
                                        room[temp_].drop[m].position.pos.setXY(room_template[l][temp_type].drop[m].position.pos.x, room_template[l][temp_type].drop[m].position.pos.y);
                                        //std::cout << m << room_template[l][temp_type].drop[m].position.pos.x;

                                        if(!room_template[l][temp_type].drop_discovered[m])
                                        {
                                            room[temp_].drop[m].type=6+rand()%(item_types-6);
                                        }


                                    }
                                    //std::cout << "test59";
                                    room[temp_].pos=temp_pos;
                                    room[temp_].spawn=room_template[l][temp_type].spawn;
                                    room[temp_].visited=false;
                                    room[temp_].is=true;
                                    room[temp_].boss=room_template[l][temp_type].boss;
                                    //std::cout << "test500";
                                    //room[k].drop_discovered=room_template[l][temp_type].drop_discovered;
//std::cout << "test57";

                                    }
                                    break;
                                }

                                //std::cout << "test590";
                            }
                            //std::cout << "test590";



                            //std::cout << "teST";
                        }
                        //std::cout << "test6";

                        for (int k=max_x; k>=0&&tempBool; k--)
                    {
                        for (int l=0; l<room_count&&tempBool; l++)
                        {
                            if (room[l].is)
                            {
                                if (round1(room[l].pos.y)==max_y&&round1(room[l].pos.x)==k)
                                {
                                    //M.setBlock(round1(room[l].pos.x)*1280+595, round1(room[l].pos.y)*720+360, round1(room[l].pos.x)*1280+685, round1(room[l].pos.y)*720+720, 0);
                                    for (int m=0; m<platform[2][0].quantity; m++)
                                    {
                                        if (!platform[2][m].is)
                                        {
                                            //std::cout << "test";
                                            platform[2][m].pos.setXY(k*1280+590, max_y*720+691);
                                            platform[2][m].is=true;
                                            tempBool=false;
                                            //std::cout << k << " " << max_y << " ";
                                            break;
                                        }
                                    }
                                    for (int m=0; m<room_count; m++)
                                    {
                                        if (room[m].is)
                                        {
                                            if (room[m].boss)
                                            {

                                                if (!room[l].boss)
                                                {
                                                    vec temp_p;
                                                    temp_p=room[m].pos;
                                                    room[m].pos=room[l].pos;
                                                    room[l].pos=temp_p;
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    /*
                    for (int l=0; l<cave[stage].quantity[k]; l++)
                            {

                            }
                    */

                    //

                    //std::cout<<"test1a";
                    //std::cout << max_x << std::endl;
                    //std::cout << max_y;

                    M.create_noback((max_x+1)*1280, (max_y+2)*720);
                    M.setBlock(5, (max_y+2)*720-100, (max_x+1)*1280-5, (max_y+2)*720-3, start_game);
                    M.setBlock(0, (max_y+2)*720-5, (max_x+1)*1280, (max_y+2)*720, 1);
                    //std::cout<<"test2";


                    //toRespawn=true;drop
                                    temp_spawn_x=round1(room[0].pos.x)*1280+640;
                                    temp_spawn_y=round1(room[0].pos.y)*720+100;
                                    camera_x=round1(room[0].pos.x)*1280+640;
                                    camera_y=round1(room[0].pos.y)*720+360;


                    for (int k=0; k<=max_x&&!toRespawn; k++)
                    {
                        for (int l=0; l<room_count&&!toRespawn; l++)//onPlatform
                        {
                            if (room[l].is)
                            {
                                if (round1(room[l].pos.x)==k&&round1(room[l].pos.y)==0)
                                {
                                    //std::cout << l << k;
                                    toRespawn=true;
                                    temp_spawn_x=round1(room[l].pos.x)*1280+640;
                                    temp_spawn_y=100;
                                    camera_x=round1(room[l].pos.x)*1280+640;
                                    camera_y=360;
                                    temp_spawn_room=l;
                                    //k=max_x+1;
                                    //l=room_count;dropRoom
                                }
                            }
                        }
                    }//create_noback
                    //std::cout << "test1b";
                    M.setBlock(0, 0, (max_x+1)*1280, 1, 1);
                    M.setBlock(0, 0, 1, (max_y+2)*720, 1);
                    M.setBlock(0, (max_y+2)*720-5, (max_x+1)*1280, (max_y+2)*720, 1);
                    M.setBlock((max_x+1)*1280-5, (max_x+1)*1280, 1, (max_y+2)*720, 1);
                    //std::cout << temp_spawn_x;
                    for (int k=0; k<room_count; k++)
                    {
                        if (room[k].is)
                        {
                            //std::cout << k << " " << room[k].background.length;

                            //room[k].background.setFrame(rand()%room[k].background.f_count);
                            M.sprite[round1(room[k].pos.x)][round1(room[k].pos.y)].setTexture(room[k].background.texture[rand()%room[k].background.length]);
                            //std::cout << "test10d";
                            room[k].rectangle.setPosition(round1(room[k].pos.x)*1280+20, round1(room[k].pos.y)*720+20);
                            room[k].rectangle.setWH(1240, 680);
                            M.setBlock(round1(room[k].pos.x)*1280, round1(room[k].pos.y)*720, round1(room[k].pos.x)*1280+1280, round1(room[k].pos.y)*720+720, 1);
                            M.setBlock(round1(room[k].pos.x)*1280+30, round1(room[k].pos.y)*720+30, round1(room[k].pos.x)*1280+1280-30, round1(room[k].pos.y)*720+720-30, 0);
                            int temp_x=round1(room[k].pos.x)*1280;
                            int temp_y=round1(room[k].pos.y)*720;
                            //std::cout << "test10b";
                            for (int l=0; l<room[k].width; l++)
                            {
                                for (int m=0; l<room[k].height; l++)
                                {
                                    M.M[temp_x+l][temp_y+m]=room[k].M[l][m];
                                }
                            }
                            //std::cout << "test10c";
                            //M.setBlock(round1(room[k].pos.x)*1280+595, round1(room[k].pos.y)*720, round1(room[k].pos.x)*1280+685, round1(room[k].pos.y)*720+720, 0);
                            //M.setBlock(round1(room[k].pos.x)*1280, round1(room[k].pos.y)*720+315, round1(room[k].pos.x)*1280+1280, round1(room[k].pos.y)*720+405, 0);
                        }
                    }

                    //std::cout << "test1c";
                    for (int l=0; l<types; l++)
                    {
                        for (int m=0; m<enemy[l][0].quantity; m++)
                                {
                                    enemy[l][m].is=false;
                                    enemy[l][m].phase=0;
                                }
                    }
                    for (int l=0; l<drop_count; l++)
                            {
                                drop[l].is=false;
                            }
                            for (int l=0; l<projectiles_count; l++)
            {
                proj[l].is=false;
                proj[l].time=0;
                enemy_proj[l].is=false;
                enemy_proj[l].time=0;//droproom


            }
            //std::cout << "test1d";

                    for (int k=0; k<room_count; k++)
                    {
                        if (room[k].is)
                        {
                            for (int l=0; l<room_count; l++)
                            {
                                if (room[l].is)
                                {
                                    if (round1(room[l].pos.x)==round1(room[k].pos.x)+1)
                                    {
                                        if (round1(room[l].pos.y)==round1(room[k].pos.y))
                                        {
                                            //M.setBlock(round1(room[k].pos.x)*1280+640, round1(room[k].pos.y)*720+315, round1(room[k].pos.x)*1280+1280, round1(room[k].pos.y)*720+405, 0);
                                            for (int m=0; m<platform[3][0].quantity; m++)
                                            {
                                                if (!platform[3][m].is)
                                                {
                                                    platform[3][m].pos.setXY(round1(room[k].pos.x)*1280+1251, round1(room[k].pos.y)*720+310);
                                                    platform[3][m].is=true;
                                                    break;
                                                }
                                            }
                                        }
                                    }//M.M
                                    else if (round1(room[l].pos.x)==round1(room[k].pos.x)-1)
                                    {
                                        if (round1(room[l].pos.y)==round1(room[k].pos.y))
                                        {
                                            //M.setBlock(round1(room[k].pos.x)*1280, round1(room[k].pos.y)*720+315, round1(room[k].pos.x)*1280+640, round1(room[k].pos.y)*720+405, 0);
                                            for (int m=0; m<platform[3][0].quantity; m++)
                                            {
                                                if (!platform[3][m].is)
                                                {
                                                    platform[3][m].pos.setXY(round1(room[k].pos.x)*1280, round1(room[k].pos.y)*720+310);
                                                    platform[3][m].is=true;
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                    else if (round1(room[l].pos.x)==round1(room[k].pos.x))
                                    {
                                        if (round1(room[l].pos.y)==round1(room[k].pos.y)+1)
                                        {//rand
                                            //M.setBlock(round1(room[k].pos.x)*1280+595, round1(room[k].pos.y)*720+360, round1(room[k].pos.x)*1280+685, round1(room[k].pos.y)*720+720, 0);
                                            for (int m=0; m<platform[2][0].quantity; m++)
                                            {
                                                if (!platform[2][m].is)
                                                {
                                                    platform[2][m].pos.setXY(round1(room[k].pos.x)*1280+590, round1(room[k].pos.y)*720+691);
                                                    platform[2][m].is=true;
                                                    break;
                                                }
                                            }
                                        }
                                        else if (round1(room[l].pos.y)==round1(room[k].pos.y)-1)
                                        {
                                            //M.setBlock(round1(room[k].pos.x)*1280+595, round1(room[k].pos.y)*720, round1(room[k].pos.x)*1280+685, round1(room[k].pos.y)*720+360, 0);
                                            for (int m=0; m<platform[2][0].quantity; m++)
                                            {
                                                if (!platform[2][m].is)
                                                {
                                                    platform[2][m].pos.setXY(round1(room[k].pos.x)*1280+590, round1(room[k].pos.y)*720);
                                                    platform[2][m].is=true;
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            for (int l=0; l<room[k].platform_count; l++)
                            {
                                for (int m=0; m<platform[room[k].platforms[l].type][0].quantity; m++)
                                {
                                    if (!platform[room[k].platforms[l].type][m].is)
                                    {
                                        platform[room[k].platforms[l].type][m].pos.setXY(room[k].platforms[l].pos.x+room[k].pos.x*1280, room[k].platforms[l].pos.y+room[k].pos.y*720);
                                        platform[room[k].platforms[l].type][m].pos_finish.setXY(room[k].platforms[l].pos_finish.x+room[k].pos.x*1280, room[k].platforms[l].pos_finish.y+room[k].pos.y*720);
                                        platform[room[k].platforms[l].type][m].pos_start.setXY(room[k].platforms[l].pos_start.x+room[k].pos.x*1280, room[k].platforms[l].pos_start.y+room[k].pos.y*720);
                                        platform[room[k].platforms[l].type][m].speed=room[k].platforms[l].speed;
                                        platform[room[k].platforms[l].type][m].is=true;
                                        break;
                                    }
                                }
                            }


                            /*for (int l=0; l<room[k].spawn_count; l++)
                            {

                                int temp_weights=0;
                                //std::cout << "test0";
                                for (int m=0; m<types; m++)
                                {
                                    if (enemy[m][0].weight==room[k].spawn[l].weight)
                                    {
                                        temp_weights++;
                                    }
                                }
                                int random_robot=0;
                                if (temp_weights>0)
                                {
                                    random_robot=rand()%temp_weights;platform
                                }
                                temp_weights=0;

                                //std::cout << "test";
                                for (int temp_m=0; temp_m<types; temp_m++)
                                {

                                    if (enemy[temp_m][0].weight==room[k].spawn[l].weight)
                                    {
                                        temp_weights++;
                                    }
                                    if (temp_weights>=random_robot)
                                    {
                                        for (int m=0; m<enemy[temp_m][0].quantity; m++)
                                        {
                                            if (!enemy[temp_m][m].is)
                                            {
                                                enemy[temp_m][m].position.pos.setXY(room[k].spawn[l].position.pos.x+room[k].pos.x*1280, room[k].spawn[l].position.pos.y+room[k].pos.y*720);
                                                enemy[temp_m][m].position.speed=room[k].spawn[l].position.speed;
                                                enemy[temp_m][m].is=true;
                                                enemy[temp_m][m].armor=enemy[temp_m][m].max_armor;
                                                //enemy[temp_m][m].position.speed.y=1280;
                                                //enemy[temp_m][m].position.engine(enemy[temp_m][m].head_height, enemy[temp_m][m].height, enemy[temp_m][m].width, M);
                                                break;
                                            }
                                        }
                                        break;
                                    }

                                }
                                //std::cout << "test1";


                            }*/

                        }

                    }
                    //std::cout << "test1e";
                    //std::cout << "test1";

                    //std::cout<<"test3";


                    //
                    //for (int k=0; k<platform[2][0].quantity; k++)
                    //{

                    //}




                    }
                    else
                    {
                        resp=true;

                    }
                    //
                    //std::cout << "test2";
                    break;
                }
            }
        }
        //std::cout << "test6";
        //camera
//int i
    if (dmgToPlayer>0)
    {
        player.hit_sound.play();
        hurt_timer=6;
        if (dmgToPlayer < player.armor)
        {
            player.armor -= dmgToPlayer;
        }
        else
        {
            player.health -= (dmgToPlayer - player.armor);
            player.armor = 0;
        }
    }

        if (player.health<=0)
        {
            resp=true;
        }
        for (int i = 0; i < player.health; i++)
        {
            heart_s.setPosition (camera_x - player.position.pos.x + 12 + (i % 10) * 18 + width/2, camera_y - player.position.pos.y + 12 + i / 10 + height/2);
            window.draw (heart_s);
        }
        for (int j = 0; j < player.armor; j++)
        {
            armor_s.setPosition (camera_x - player.position.pos.x + 12 + (j % 10) * 18 + width/2, camera_y - player.position.pos.y + 34 + (j / 10) * 22 + height/2);
            window.draw (armor_s);
        }
        money.setPosition(camera_x - player.position.pos.x+width*3/2-100-to_str(player.money).length()*12, camera_y - player.position.pos.y + height/2+10);
        money_count.setPosition(camera_x - player.position.pos.x+width*3/2-60-to_str(player.money).length()*12, camera_y - player.position.pos.y + height/2+10);
        money_count.setString(to_str(player.money));
        window.draw(money);
        window.draw(money_count);

        dynamite.setPosition(camera_x - player.position.pos.x+width*3/2-100-to_str(player.dynamite).length()*12, camera_y - player.position.pos.y + height/2+40);
        dynamite_count.setPosition(camera_x - player.position.pos.x+width*3/2-60-to_str(player.dynamite).length()*12, camera_y - player.position.pos.y + height/2+40);
        dynamite_count.setString(to_str(player.dynamite));
        window.draw(dynamite);
        window.draw(dynamite_count);

        int boss_count=0;

        for (int i=0; i<types; i++)
        {
            for (int j=0; j<enemy[i][0].quantity; j++)
            {
                if (enemy[i][j].is)
                {
                    if (enemy[i][j].boss)
                    {
                        hp_sprite.setPosition(camera_x - player.position.pos.x+width/2+310, camera_y - player.position.pos.y + 10+15*boss_count + height/2);
                        hp_sprite.setScale(100.0*enemy[i][j].armor/enemy[i][j].max_armor, 10);
                        window.draw(hp_sprite);
                        bar_sprite.setPosition(camera_x - player.position.pos.x+width/2+310, camera_y - player.position.pos.y + 10+15*boss_count + height/2);
                        window.draw(bar_sprite);
                        boss_count++;
                    }
                }
            }
        }

        if (hurt_timer>0)
        {
            hurt_timer--;
            hurt.setFrame(hurt.frame_pos[hurt_timer]);
            hurt.setPR(1, camera_x - player.position.pos.x + width/2, camera_y - player.position.pos.y + height/2, 0);
            window.draw(hurt.sprite);
        }
        //spark
    }


        window.display();
    }
    return 0;
}
