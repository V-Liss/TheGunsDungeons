The Guns Dungeons, a 8-bit stylized rogueelike descendant of The Guns. Now with dynamic sub-step division matrix!

(Funny, I discovered the name "sub-step division matrix" after I actually made all those three games lol

(and still not sure it's called that way, feel free to correct me))

Same principles apply here, and most mechanics from The Guns were used.

### 🕹️ Core Features & Systems

* **procedural generation:** a stage is not a map, but rather an array of how many templates of a certain type (e.g. shop, easy room, hard room, etc.) should be in it. When generating a stage, the algorithm picks a room type, picks a random template of this type, and attaches it to a random previously generated room (while checking if it overlaps the existing rooms). All rooms have doors if they connect with other rooms, and the lowest-right room has a door down, taking you to the next stage (triggers when the player touches the specific atoms placed at the border)

* **dynamic static map:** yes, exactly. it's dynamic, even though it's static. A workaround my original engine. it's made of atoms in a static grid, but the objects can move or be destroyed. Flying platforms check for all entities standing on top of it, and try to move them up by 1 first. If all move, the platform moves up by 1 (rewrites itself 1 pixel higher). The engine is modified the way that checks with negative y speed are ignored, so that any entity can freely jump through the platform, but never fall through it.

* **destroyable objects:** There are objects on the map that take damage only from dynamite (unique throwable, look below). If it's destroyed, an animation is played and all the atoms in it are replaced with air.

* **dynamic doors:** doors are created when the player first enters the room and destroy themselves once there are no enemies.

* **8-way shooting:** to accommodate the 8-bit arcade game genre, I removed the mouth for aiming. Instead, aiming and shooting is done by arrows. If the weapon is fully auto, it fires when any arrow is pressed. Semi-automatic weapons fire when any arrow is released in the set direction. If a player presses two arrows orthogonal to each other (e.g. up + right), the weapon fires a projectile giving it 1/1,41 velocity and a PI/4 rotation in both directions. The weapon uses distinct animations for diagonal aiming and firing. If idle, the weapon is pointed flat wherever was the last direction of player movement or the last direction it was pointed if the player is still.

* **dynamite:** A unique explosive that can deal damage to blocks and enemies alike. Affected by gravity. Rotates, unless it has a wall on its side, in which case it's vertical, unless it has a wall under it, in which case it lies or slides flat. Priority order: check floor - check wall - rotation. Emits sparks from where the fuse is visually, even though the hitbox doesn't change.

* **shop:** Some rooms don't have enemies. Those have 4 procedurally generated items to buy for flash drives - weapons, health and armor, or unique passive item (e.g. Shotgun Shells gives 2 more projectiles, but less damage per projectile. Formula calculates the total damage to be multiplied by a rigid value). Flash drives are dropped from enemies.

* **boss 1:** And, of course, it features 2 unique bosses. The sentry gun fires slow projectiles and turns very slowly. When its health drops below half, it starts firing twice as fast, turning twice as fast, and dealing twice the damage on direct contact (since it's hot), but overheats and has to cool down. Visual animation for overheating.

* **boss 2:** Mortar. Fires projectiles calculated to hit where you are standing and deal splash damage. When the health drops below half, it starts firing inaccurately(need to check) and a lot faster. Both bosses give good loot.

Enjoy! Might optimize it later by having the engine calculate only the rectangle where the hitbox can possibly be. The game slows down with huge maps, so my intuition tells me that will fix it.
